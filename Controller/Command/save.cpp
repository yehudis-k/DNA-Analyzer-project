//
// Created by student on 10/08/2020.
//

#include "save.h"
#include "../../View/fileWriter.h"

std::string Save::getDocumentation() const{
    return "Saves a DNA sequence to a text file.\n"
           "Save accepts a name or ID of the sequence to save.\n"
           "A name for the new file can be given by the user after the sequence to be saved - with a @.\n"
           "If not provided - a default name will be given.";
}

std::string Save::getDefaultName(const std::string& param) {
    if (isId(param)) {
        if (DnaCollection::getNameById(stoi(param.substr(1))) == "")
            throw DNAExist();
        return DnaCollection::getNameById(stoi(param.substr(1)));
    }
    else
        return param;
}

bool Save::setParams(std::vector<std::string> params) {
    if ((params.size() < 2) || (params.size() > 3)) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }

    if (params.size() == 2)// filename not given - use sequence name
        m_file_name = getDefaultName(params[1]);
    else
        m_file_name = params[2];

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
    return true;
}

std::string Save::execute() {
    FileWriter writer(m_file_name);
    writer.write(m_dna->getDna());
    //DnaCollection::updateCache(m_dna);
    std::string stat = m_dna->getStatus();
    m_dna->setStatus("up to date");

    DnaCollection::addUpToDate();
    if (stat == "new")
        DnaCollection::reduceNew();
    else if (stat == "modified")
        DnaCollection::reduceModified();

    return m_dna->getName() + " saved!";
}

