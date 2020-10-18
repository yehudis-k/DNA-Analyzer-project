//
// Created by student on 10/08/2020.
//

#include "list.h"

std::string List::getDocumentation() const{
    return "Lists all sequences in the system, with all details.\n"
           "List does not accept any arguments.";
}

std::string List::getStatus(SharedPtr<DnaData> dna) {
    if (dna->getStatus() == "up to date")
        return "-";
    else if (dna->getStatus() == "modified")
        return "*";
    else if (dna->getStatus() == "new")
        return "^";
}

std::string List::execute() {
    std::string res = "";
    std::vector<std::string> all_dna = DnaCollection::getAllIds();
    for (size_t i = 0; i<all_dna.size(); i++) {
        SharedPtr<DnaData> dna = DnaCollection::getByID(stoi(all_dna[i]));
        res += getStatus(dna) + " " + getOutput(dna) + "\n";
    }
    return res;
}