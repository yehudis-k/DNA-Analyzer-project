//
// Created by student on 10/08/2020.
//

#include "replace.h"

std::string Replace::getDocumentation() const{
    return "Replaces a letter in the sequence with a different one.\n"
           "Replace accepts a name or ID of the sequence, a index and the new letter. It can get more than one single replacement.\n"
           "It will modify the sequence in place if a colon doesn't appear after the argumants.\n"
           "Otherwise, a name for a new modified sequence can be given by the user after the colon - with a @.\n"
           "If provided @@ instead - a default name will be given.";
}

std::string Replace::getDefaultName(const std::string& old_name)
{
    size_t number = 1;
    std::string new_name = old_name + "_r";
    while (!isValidName(new_name + std::to_string(number)))
        number++;
    new_name += std::to_string(number);

    return new_name;
}

SharedPtr<DnaData> Replace::replaceInPlace(SharedPtr<DnaData> dna, const std::string& replaced) {
    SharedPtr<DnaSequence> replace(new DnaSequence(replaced));
    if (!replace)
        return SharedPtr<DnaData>();
    dna->setSequence(replace);
    if (dna->getStatus() == "up to date") {
        dna->setStatus("modified");
        DnaCollection::addModified();
        DnaCollection::reduceUpToDate();
    }

    return dna;
}

SharedPtr<DnaData> Replace::createReplaced(std::string replaced, std::string new_name) {
    SharedPtr<DnaData> new_dna(new DnaData(new_name, replaced));
    if (!new_dna)
       return SharedPtr<DnaData>();
    return new_dna;
}


bool Replace::setParams(std::vector<std::string> params) {
    if (params.size() % 2 != 0) {
        m_message = "Invalid number of arguments";
        return false;
    }

    if (params.size() == 2) {
        m_message = "No replacements given";
        return false;
    }

    m_indexes.clear();
    m_new_letters.clear();

    SharedPtr<DnaData> dna;
    if (isId(params[1])) // get DNA to replace
        dna = DnaCollection::getByID(getId(params[1]));
    else
        dna = DnaCollection::getByName(params[1]);

    if (!dna) {
        m_message = "Error! DNA not found";
        return false;
    }
    m_dna = dna;

    if (params[params.size()-2] != ":")
        m_in_place = true;
    else
    {
        m_in_place = false;
        m_new_name = params[params.size()-1];
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
    size_t i = 2;
    while ((i < params.size()-1) && (params[i] != ":")) {
        size_t index = stoi(params[i]);
        if (index > m_dna->getDna().size()-1) {
            m_message = "Index out of range";
            return false;
        }
        m_indexes.push_back(index);
        m_new_letters.push_back(params[i+1]);
        i+=2;
    }

    return true;
}

std::string Replace::execute() {
    // replace in sequence
    std::string replaced = m_dna->getDna();
    for (int i=0; i<m_indexes.size(); i++) {
        replaced[m_indexes[i]] = m_new_letters[i][0];
    }

    try {
        SharedPtr<DnaSequence> test(new DnaSequence(replaced));
    }
    catch (ValidError) {
        return "Error! Invalid DNA Nucleotide";
    }

    if (m_in_place) {
        m_dna = replaceInPlace(m_dna, replaced);
        //DnaCollection::updateCache(m_dna);
        return getOutput(m_dna);
    }

    SharedPtr<DnaData> new_dna = createReplaced(replaced, m_new_name);

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
