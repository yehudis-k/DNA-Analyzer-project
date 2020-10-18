//
// Created by student on 10/08/2020.
//

#include "show.h"

std::string Show::getDocumentation() const{
    return "Shows the sequence with all its details.\n"
           "Show accepts a name or ID of the sequence, and optionally a number of chars to show.\n"
           "It prints the ID, name, status and the sequence.";
}


bool Show::setParams(std::vector<std::string> params) {
    if ((params.size() < 2) || (params.size() > 3)) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }

    SharedPtr<DnaData> dna;
    if (isId(params[1]))
        dna = DnaCollection::getByID(getId(params[1]));
    else
        dna = DnaCollection::getByName(params[1]);

    if (!dna) {
        m_message = "Error! DNA not found";
        return false;
    }
    m_dna = dna;

    if (params.size() == 2)// num chars not given - use default 99
        m_num_chars = 99;
    else
        m_num_chars = stoi(params[2]) > m_dna->getDna().size() ? m_dna->getDna().size() : stoi(params[2]);

    return true;
}

std::string Show::execute() {
    std::string seq = m_dna->getDna().substr(0, m_num_chars);
    if (m_num_chars > 99) {
        for (size_t i=99; i<seq.size();i+=99)
            seq.insert(i, "\n");
    }

    return "["+std::to_string(m_dna->getId())+"] "+m_dna->getName()+" status: "+m_dna->getStatus()+"\n"+seq;
}
