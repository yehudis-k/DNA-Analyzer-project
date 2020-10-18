//
// Created by student on 10/08/2020.
//

#include "slice.h"

std::string Slice::getDocumentation() const{
    return "Slices a sequence.\n"
           "Slice accepts a name or ID of the sequence, a start index and an end index.\n"
           "It will slice the sequence in place if a colon doesn't appear after the indexes.\n"
           "Otherwise, a name for a new sliced sequence can be given by the user after the colon - with a @.\n"
           "If provided @@ instead - a default name will be given.";
}

SharedPtr<DnaData> Slice::sliceInPlace(SharedPtr<DnaData> dna, size_t start, size_t end) {
    DnaSequence my_dna = dna->getSequence();
    SharedPtr<DnaSequence> new_dna(my_dna.mySlice(start, end));
    if (!new_dna)
        return SharedPtr<DnaData>();
    dna->setSequence(new_dna);
    if (dna->getStatus() == "up to date") {
        dna->setStatus("modified");
        DnaCollection::addModified();
        DnaCollection::reduceUpToDate();
    }

    return dna;
}

SharedPtr<DnaData> Slice::createSliced(SharedPtr<DnaData> dna, std::string new_name,  size_t start, size_t end) {
    DnaSequence my_dna = dna->getSequence();
    SharedPtr<DnaSequence> new_dna(my_dna.mySlice(start, end));
    if (!new_dna)
        return SharedPtr<DnaData>();
    SharedPtr<DnaData> sliced(new DnaData(new_name, new_dna->getSeq()));
    return sliced;
}

std::string Slice::getDefaultName(const std::string& old_name)
{
    size_t number = 1;
    std::string new_name = old_name + "_s";
    while (!isValidName(new_name + std::to_string(number)))
        number++;
    new_name += std::to_string(number);

    return new_name;
}

bool Slice::setParams(std::vector<std::string> params) {
    if ((params.size() != 4) && (params.size() != 6)) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }

    SharedPtr<DnaData> dna;
    if (isId(params[1])) // get DNA to slice
        dna = DnaCollection::getByID(getId(params[1]));
    else
        dna = DnaCollection::getByName(params[1]);

    if (!dna) {
        m_message = "Error! DNA not found";
        return false;
    }
    m_dna = dna;

    m_start = stoi(params[2]);
    m_end = stoi(params[3]);

    if ((m_start > m_end)||(m_start == m_end)) {
        m_message = "Error! invalid index";
        return false;
    }

    if ((m_start > m_dna->getDna().length()) || (m_end > m_dna->getDna().length())) {
        m_message = "Error! index out of range";
        return false;
    }

    if (params.size() == 4)
        m_in_place = true;
    else
    {
        m_in_place = false;
        if (params[4] != ":") { // not : after parameters
            m_message = "Invalid argument, expected :";
            return false;
        }
        m_new_name = params[5];
        if (m_new_name[0] != '@') { // not @ first char
            m_message = "Invalid argument sequence name";
            return false;
        }
        if (m_new_name[1] == '@') { // @ second char - use default name
            m_new_name = getDefaultName(dna->getName());
        }
        else {
            m_new_name = m_new_name.substr(1); // a new name given
            if (!isValidName(m_new_name)) {
                m_message = "DNA sequence name already exists";
                return false;
            }
        }
    }
    return true;
}


std::string Slice::execute() {
    if (m_in_place) {
        m_dna = sliceInPlace(m_dna, m_start, m_end);
        //DnaCollection::updateCache(m_dna);
        return getOutput(m_dna);
    }

    SharedPtr<DnaData> new_dna = createSliced(m_dna, m_new_name, m_start, m_end);

    bool checkAdd = DnaCollection::addDna(new_dna);
    if (!checkAdd)
    {
        new_dna->~DnaData();
        return "Error creating sliced dna";
    }
    DnaCollection::addNew();
    //DnaCollection::updateCache(new_dna);
    return getOutput(new_dna);
}
