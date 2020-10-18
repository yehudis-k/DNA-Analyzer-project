//
// Created by student on 10/08/2020.
//

#include "load.h"
#include "../../View/fileReader.h"

std::string Load::getDocumentation() const{
    return "Loads a DNA sequence from a file.\n"
           "Load accepts a name of a file, loads the sequence and adds it to the system.\n"
           "A new name for the loaded sequence can be given by the user after the filename - with a @.\n"
           "If not provided - a default name will be given.";
}


std::string Load::getDefaultName(const std::string& filename)
{
    size_t number = 1;
    std::string new_name = filename.substr(0, filename.rfind('.'));
    if (!isValidName(new_name)) {
        while (!isValidName(new_name + "_" + std::to_string(number)))
            number++;
        new_name += "_" + std::to_string(number);
    }
    return new_name;
}


bool Load::setParams(std::vector<std::string> params) {
    if ((params.size() < 2) || (params.size() > 3)) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }
    if (params.size() == 2)
        m_new_name = getDefaultName(params[1]);
    else
        m_new_name = params[2];
    m_file_name = params[1];
    return true;
}


std::string Load::execute() {
    std::string str;
    FileReader reader(m_file_name);
    try {
        str = reader.read();
    }
    catch (std::exception){ // exception happened while reading file
        return "Error! file not found";
    }

    std::string dna_seq = str;
    SharedPtr<DnaData> dna(new DnaData(m_new_name, dna_seq));
    bool checkAdd = DnaCollection::addDna(dna);
    if (!checkAdd)
    {
        dna->~DnaData();
        return "Error loading dna";
    }
    dna->setStatus("up to date");
    DnaCollection::addUpToDate();
    //DnaCollection::updateCache(dna);
    return getOutput(dna);
}

