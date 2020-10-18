//
// Created by student on 10/08/2020.
//

#include "new.h"

size_t New::s_counter = 1;

std::string New::getDocumentation() const{
    return "Creates a new DNA sequence.\n"
           "New accepts sequence and adds it to the system.\n"
           "A name for the new sequence can be given by the user after the sequence - with a @.\n"
           "If not provided - a default name will be given.";
}

std::string New::getDefaultName()
{
    while (!isValidName("seq"+std::to_string(s_counter)))
        s_counter++;

    s_counter++;
    return "seq"+std::to_string(s_counter-1);
}


bool New::setParams(std::vector<std::string> params) {
    if ((params.size() < 2) || (params.size() > 3)) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }

    if (params.size() == 2)
        m_new_name = getDefaultName();
    else {
        if (params[2][0] != '@') {
            m_message = "Invalid argument sequence name";
            return false;
        }
        m_new_name = params[2].substr(1);
    }

    if (!isValidName(m_new_name)) {
        m_message = "DNA sequence name already exists";
        return false;
    }
    m_new_sequence = params[1];
    return true;
}


std::string New::execute() {
    // create new DnaData object
    SharedPtr<DnaData> dna;
    try {
        dna = SharedPtr<DnaData>(new DnaData(m_new_name, m_new_sequence));
    }
    catch (ValidError& e) {
        dna->decreaseId();
        s_counter--;
        return "Error! Invalid DNA Nucleotide";
    }

    bool checkAdd = DnaCollection::addDna(dna);
    if (!checkAdd)
    {
        dna->~DnaData();
        return "Error adding dna";
    }
    DnaCollection::addNew();
    //DnaCollection::updateCache(dna);
    return getOutput(dna);
}
