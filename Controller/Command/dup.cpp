//
// Created by student on 10/08/2020.
//
#include "dup.h"

std::string Dup::getDefaultName(const std::string& old_name)
{
    size_t num = 1;
    std::string new_name = old_name + "_";
    for (; !isValidName(new_name + std::to_string(num)); ++num);
    return new_name + std::to_string(num);
}

std::string Dup::getDocumentation() const{
    return "Duplicates the sequence.\n"
           "Dup accepts a name or ID of a sequence and duplicates it.\n"
           "A new name for the duplicated sequence can be given by the user after the sequence itself - with a @.\n"
           "If not provided - a default name will be given.";
}


bool Dup::setParams(std::vector<std::string> params) {
    if ((params.size() < 2) || (params.size() > 3)) { // too many or too little arguments
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

    if (params.size() == 2) {
        m_new_name = getDefaultName(dna->getName());
    } else
        m_new_name = params[2].substr(1);

    return true;
}


std::string Dup::execute()  {
    std::string seq = m_dna->getDna();
    SharedPtr<DnaData> dup_dna(new DnaData(m_new_name, seq));
    bool checkAdd = DnaCollection::addDna(dup_dna);
    if (!checkAdd)
    {
        dup_dna->~DnaData();
        return "Error duplicating dna";
    }
    DnaCollection::addNew();
    //DnaCollection::updateCache(m_dna);
    return getOutput(dup_dna);
}