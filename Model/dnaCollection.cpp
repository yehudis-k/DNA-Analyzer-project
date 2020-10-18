//
// Created by student on 10/08/2020.
//

#include "dnaCollection.h"

HashMap<std::string> DnaCollection::s_id_to_name;
HashMap<SharedPtr<DnaData> > DnaCollection::s_name_to_dna;
HashMap<size_t> DnaCollection::m_count_status_map = initializeCountMap();


HashMap<size_t> DnaCollection::initializeCountMap() {
    HashMap<size_t> tmp_map;
    tmp_map.insert("new", 0);
    tmp_map.insert("modified", 0);
    tmp_map.insert("up to date", 0);
    return tmp_map;
}

bool DnaCollection::addDna(SharedPtr<DnaData> dna) {
    if (!s_name_to_dna.contains(dna->getName()))
    {
        std::string id = std::to_string(dna->getId());
        std::string name = dna->getName();
        s_name_to_dna.insert(name, dna);
        s_id_to_name.insert(id, name);
        return true;
    }
    return false;
}


