//
// Created by student on 21/09/2020.
//

#include "rename.h"

std::string Rename::getDocumentation() const{
    return "Renames a sequence.\n"
           "Replace accepts a name or ID of the sequence to rename, and a new name beginning with a @.";
}

bool Rename::setParams(std::vector<std::string> params) {
    if (params.size() != 3) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }
    SharedPtr<DnaData> dna;
    if (isId(params[1])) // get DNA to rename
        dna = DnaCollection::getByID(getId(params[1]));
    else
        dna = DnaCollection::getByName(params[1]);

    if (!dna) {
        m_message = "Error! DNA not found";
        return false;
    }
    m_dna = dna;
    if (params[2][0] != '@') {
        m_message = "invalid argument, expected @";
        return false;
    }
    m_new_name = params[2].substr(1);
    if (!isValidName(m_new_name)) {
        m_message = "DNA sequence name already exists";
        return false;
    }
    m_old_name = m_dna->getName();
    return true;
}

std::string Rename::execute() {
    bool success = DnaCollection::setName(m_dna, m_new_name);
    if (!success)
        return "Error renaming sequence";
    //DnaCollection::updateCache(m_dna);
    return m_old_name + " renamed to " + m_new_name;
}
