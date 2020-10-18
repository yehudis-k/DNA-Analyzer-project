//
// Created by student on 16/09/2020.
//

#include "delete.h"

bool Delete::setParams(std::vector<std::string> params) {
    if (params.size() != 2) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }

    SharedPtr<DnaData> dna;
    if (isId(params[1])) // get DNA to delete
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

std::string Delete::getDocumentation() const{
    return "Deletes the sequence.\n"
           "Delete accepts a name or ID of a sequence, and after confirming with the user - deletes it.";
}


std::string Delete::execute() {
    std::string output = getOutput(m_dna);

    ConsolWriter writer;
    ConsolReader reader;
    writer.write("Are you sure you want to delete "+m_dna->getName()+": "+m_dna->getDna()+"?\n");
    if (!confirm())
        return "Cancelled. Nothing was deleted";
    std::string stat = m_dna->getStatus();
    DnaCollection::deleteDna(m_dna);

    if (stat == "new")
        DnaCollection::reduceNew();
    else if (stat == "up to date")
        DnaCollection::reduceUpToDate();
    else if (stat == "modified")
        DnaCollection::reduceModified();

    //DnaCollection::updateCache(SharedPtr<DnaData>());
    return "Deleted: " + output;
}
