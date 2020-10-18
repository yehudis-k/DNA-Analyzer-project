//
// Created by student on 10/08/2020.
//

#include "len.h"

std::string Len::getDocumentation() const{
    return "Prints the length of a DNA sequence.\n"
           "Len accepts a name or ID of the sequence.";
}

bool Len::setParams(std::vector<std::string> params) {
    if (params.size() != 2) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }

    SharedPtr<DnaData> dna;
    if (isId(params[1])) // get DNA
        dna = DnaCollection::getByID(getId(params[1]));
    else
        dna = DnaCollection::getByName(params[1]);

    if (!dna) {
        m_message = "Error! DNA not found";
        return false;
    }
    m_dna = dna;
    return true;
}


std::string Len::execute() {
    std::string output(std::to_string(m_dna->getSequence().getLen()));
    return output;
}
