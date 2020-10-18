//
// Created by student on 15/09/2020.
//

#include "findall.h"
#include <vector>

std::string FindAll::getDocumentation() const{
    return "Finds all the appearances of a subsequence within a larger sequence.\n"
           "FindAll accepts a name or ID of the sequence, and either a name/ID of an existing subsequence or an expressed subsequence\n"
           "and prints the indexes.";
}


bool FindAll::setParams(std::vector<std::string> params) {
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


std::string FindAll::execute() {
    DnaSequence dna_seq = m_dna->getSequence();
    std::vector<size_t> indexes = dna_seq.findAll(m_subseq);

    std::string output = "";
    for (std::vector<std::size_t>::const_iterator i = indexes.begin(); i != indexes.end(); ++i)
        output += std::to_string(*i) + " ";
    if (output == "")
        return "No indexes found - not a subsequence";

    return output;
}
