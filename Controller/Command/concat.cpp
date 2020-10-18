//
// Created by student on 22/09/2020.
//

#include "concat.h"
std::string Concat::getDocumentation() const{
    return "Concatenates two sequences.\n"
           "Concat accepts a name or ID of one sequence, and a name or ID of another sequence.\n"
           "It will concatenate the second sequence at the end of to the first one in place if a colon doesn't appear after the arguments.\n"
           "Otherwise, a name for a new concatenated sequence can be given by the user after the colon - with a @.\n"
           "If provided @@ instead - a default name will be given.";
}

std::string Concat::getDefaultName(const std::string& first_name, const std::string& second_name)
{
    size_t number = 1;
    std::string new_name = first_name + "_" + second_name + "_c";
    while (!isValidName(new_name + std::to_string(number)))
        number++;
    new_name += std::to_string(number);

    return new_name;
}

SharedPtr<DnaData> Concat::concatInPlace(SharedPtr<DnaData> first, SharedPtr<DnaData> second) {
    std::string seq = first->getDna() + second->getDna();
    SharedPtr<DnaSequence> new_dna(new DnaSequence(seq));
    if (!new_dna)
        return SharedPtr<DnaData>();
    first->setSequence(new_dna);
    if (first->getStatus() == "up to date") {
        first->setStatus("modified");
        DnaCollection::addModified();
        DnaCollection::reduceUpToDate();
    }
    return first;
}


SharedPtr<DnaData> Concat::createConcat(SharedPtr<DnaData> first, SharedPtr<DnaData> second, std::string new_name) {
    std::string seq = first->getDna() + second->getDna();
    SharedPtr<DnaSequence> new_dna(new DnaSequence(seq));
    if (!new_dna)
        return SharedPtr<DnaData>();
    SharedPtr<DnaData> concat(new DnaData(new_name, new_dna->getSeq()));
    concat->setStatus("new");
    return concat;
}

bool Concat::setParams(std::vector<std::string> params) {
    if ((params.size() != 3) && (params.size() != 5)) {// too many or too little arguments
        m_message = "Invalid number of arguments";
        return false;
    }

    SharedPtr<DnaData> dna1;
    if (isId(params[1])) // get first DNA
        dna1 = DnaCollection::getByID(getId(params[1]));
    else
        dna1 = DnaCollection::getByName(params[1]);

    if (!dna1) {
        m_message = "Error! DNA not found";
        return false;
    }
    m_first_seq = dna1;

    SharedPtr<DnaData> dna2;
    if (isId(params[2])) // get second DNA
        dna2 = DnaCollection::getByID(getId(params[2]));
    else
        dna2 = DnaCollection::getByName(params[2]);

    if (!dna2) {
        m_message = "Error! DNA not found";
        return false;
    }
    m_second_seq = dna2;

    if (params.size() == 3)
        m_in_place = true;
    else
    {
        m_in_place = false;
        if (params[3] != ":") { // not : after parameters
            m_message = "Invalid argument, expected :";
            return false;
        }
        m_new_name = params[4];
        if (m_new_name[0] != '@') { // not @ first char
            m_message = "Invalid argument sequence name";
            return false;
        }
        if (m_new_name[1] == '@') { // @ second char - use default name
            m_new_name = getDefaultName(m_first_seq->getName(), m_second_seq->getName());
            //std::cout<<"default name: "<<m_new_name<<std::endl;
        }
        else {
            m_new_name = m_new_name.substr(1); // a new name given
            if (!isValidName(m_new_name)) {
                m_message = "DNA sequence name already exists";
                return false;
            }
        }
    }
    return true;
}

std::string Concat::execute() {
    if (m_in_place) {
        m_first_seq = concatInPlace(m_first_seq, m_second_seq);

        //DnaCollection::updateCache(m_first_seq);
        return getOutput(m_first_seq);
    }
    std::cout<<"default name: "<<m_new_name<<std::endl;
    SharedPtr<DnaData> new_dna = createConcat(m_first_seq, m_second_seq, m_new_name);

    bool checkAdd = DnaCollection::addDna(new_dna);
    if (!checkAdd)
    {
        new_dna->~DnaData();
        return "Error creating sliced dna";
    }
    DnaCollection::addNew();
    //DnaCollection::updateCache(new_dna);
    return getOutput(new_dna);
}


