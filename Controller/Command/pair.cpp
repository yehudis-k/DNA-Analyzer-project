//
// Created by student on 22/09/2020.
//

#include "pair.h"

std::string Pair::getDocumentation() const{
    return "Pairs the sequence: each T is replaced by an A (and vice versa) and each C is replaced by a G (and vice versa).\n"
           "Pair accepts a name or ID of the sequence to pair.\n"
           "It will replave the  original sequence if a colon doesn't appear after the arguments.\n"
           "Otherwise, a name for a new pairing sequence can be given by the user after the colon - with a @.\n"
           "If provided @@ instead - a default name will be given.";
}

std::string Pair::getDefaultName(const std::string& old_name)
{
    size_t number = 1;
    std::string new_name = old_name + "_p";
    while (!isValidName(new_name + std::to_string(number)))
        number++;
    new_name += std::to_string(number);

    return new_name;
}

SharedPtr<DnaData> Pair::pairInPlace(SharedPtr<DnaData> dna) {
    DnaSequence my_dna = dna->getSequence();
    SharedPtr<DnaSequence> paired(new DnaSequence(my_dna.pair()));
    if (!paired)
        return SharedPtr<DnaData>();
    dna->setSequence(paired);
    if (dna->getStatus() == "up to date") {
        dna->setStatus("modified");
        DnaCollection::addModified();
        DnaCollection::reduceUpToDate();
    }

    return dna;
}

SharedPtr<DnaData> Pair::createPaired(SharedPtr<DnaData> dna, std::string new_name) {
    DnaSequence my_dna = dna->getSequence();
    SharedPtr<DnaSequence> new_dna(new DnaSequence(my_dna.pair()));
    if (!new_dna)
        return SharedPtr<DnaData>();
    SharedPtr<DnaData> paired(new DnaData(new_name, new_dna->getSeq()));
    return paired;
}


bool Pair::setParams(std::vector<std::string> params) {
    if ((params.size() != 2) && (params.size() != 4)) {// too many or too little arguments
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

    if (params.size() == 2)
        m_in_place = true;
    else
    {
        m_in_place = false;
        if (params[2] != ":") { // not : after parameters
            m_message = "Invalid argument, expected :";
            return false;
        }
        m_new_name = params[3];
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

std::string Pair::execute() {
    if (m_in_place) {
        m_dna = pairInPlace(m_dna);
        //DnaCollection::updateCache(m_dna);
        return getOutput(m_dna);
    }
    SharedPtr<DnaData> new_dna = createPaired(m_dna, m_new_name);

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