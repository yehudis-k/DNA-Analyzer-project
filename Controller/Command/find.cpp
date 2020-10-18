//
// Created by student on 10/08/2020.
//
#include <sstream>
#include "find.h"

std::string Find::getDocumentation() const{
    return "Finds the first appearance of a subsequence within a larger sequence.\n"
           "Find accepts a name or ID of the sequence, and either a name/ID of an existing subsequence or an expressed subsequence\n"
           "and prints the index of first appearance.";
}

bool Find::setParams(std::vector<std::string> params) {
    if (params.size() != 3) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }

    SharedPtr<DnaData> dna;
    if (isId(params[1])) // get DNA to find in
        dna = DnaCollection::getByID(getId(params[1]));
    else
        dna = DnaCollection::getByName(params[1]);

    if (!dna) {
        m_message = "Error! DNA not found";
        return false;
    }
    m_dna = dna;

    DnaSequence dna_seq = dna->getSequence();

    std::string sub; // get subsequence
    if (isId(params[2]))
        m_subseq = DnaCollection::getByID(getId(params[2]))->getDna();
    else
        m_subseq = params[2];

    return true;
}


std::string Find::execute() {
    DnaSequence dna_seq = m_dna->getSequence();
    size_t index = dna_seq.find(m_subseq);

    if (index == -1)
        return "not found";

    std::string output(std::to_string(index));
    return output;
}
