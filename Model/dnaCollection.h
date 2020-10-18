//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_DNACOLLECTION_H
#define DESIGN_DNA_DNACOLLECTION_H

#include "dnaData.h"
#include "../Libraries/Shared_Pointer/SharedPtr.h"
#include "../Libraries/Hash_Map/hashmap.h"
#include <map>
#include <algorithm>

class DnaCollection
{
public:
    static bool addDna(SharedPtr<DnaData>);
    static SharedPtr<DnaData> getByID(size_t);
    static SharedPtr<DnaData> getByName(const std::string&);
    static std::string getNameById(size_t);
    static void deleteDna(SharedPtr<DnaData>);
    static bool setName(SharedPtr<DnaData>, std::string);
    static bool setId(SharedPtr<DnaData>, size_t);
    static std::vector<std::string> getAllIds();
    static bool nameExists(std::string);
    static std::vector<SharedPtr<DnaData> > getAllSeqs();

    static void addNew(int add=1) { m_count_status_map["new"] += add;}
    static void reduceNew(int red=1) { m_count_status_map["new"] -= red;}
    static void addModified(int add=1) { m_count_status_map["modified"] += add;}
    static void reduceModified(int red=1) { m_count_status_map["modified"] -= red;}
    static void addUpToDate(int add=1) { m_count_status_map["up to date"] += add;}
    static void reduceUpToDate(int red=1) { m_count_status_map["up to date"] -= red;}
    static HashMap<size_t> getCountStatus();

private:
    static HashMap<size_t> initializeCountMap();

    static HashMap<std::string> s_id_to_name;
    static HashMap<SharedPtr<DnaData> > s_name_to_dna;
    static HashMap<size_t> m_count_status_map;
};

inline SharedPtr<DnaData> DnaCollection::getByID(size_t id) {
    std::string id_as_string = std::to_string(id);
    if (s_id_to_name.contains(id_as_string))
        return getByName(s_id_to_name[id_as_string]);
    return SharedPtr<DnaData>();
}
inline SharedPtr<DnaData> DnaCollection::getByName(const std::string& name) {
    if (s_name_to_dna.contains(name))
        return s_name_to_dna[name];
    return SharedPtr<DnaData>();
}

inline std::string DnaCollection::getNameById(size_t id) {
    if (s_id_to_name.empty())
        return "";
    std::string id_as_string = std::to_string(id);
    if (s_id_to_name.contains(id_as_string))
        return s_id_to_name[id_as_string];
    return "";
}

inline void DnaCollection::deleteDna(SharedPtr<DnaData> dna) {
    s_name_to_dna.remove(dna->getName());
    s_id_to_name.remove(std::to_string(dna->getId()));
    dna->~DnaData();
}

inline bool DnaCollection::setName(SharedPtr<DnaData> dna, std::string new_name) {
    if (s_name_to_dna.contains(new_name))
        return false;
    s_name_to_dna.remove(dna->getName());
    dna->setName(new_name);
    s_id_to_name[std::to_string(dna->getId())] = new_name;
    s_name_to_dna.insert(new_name, dna);
    return true;
}

inline bool DnaCollection::setId(SharedPtr<DnaData> dna, size_t new_id) {
    if (s_id_to_name.contains(std::to_string(new_id)))
        return false;
    s_id_to_name.remove(std::to_string(dna->getId()));
    dna->setId(new_id);
    s_id_to_name.insert(std::to_string(new_id), dna->getName());
    return true;
}

inline std::vector<std::string> DnaCollection::getAllIds() {
    std::vector<std::string> res = s_id_to_name.keys();
    std::sort(res.begin(), res.end());
    return res;
}

//inline void DnaCollection::updateCache(SharedPtr<DnaData> cache) {
//    m_cache = cache;
//}

inline bool DnaCollection::nameExists(std::string name) {
    if (s_name_to_dna.empty())
        return false;
    return s_name_to_dna.contains(name);
}

inline std::vector<SharedPtr<DnaData> > DnaCollection::getAllSeqs() {
    return s_name_to_dna.values();
}

inline HashMap<size_t> DnaCollection::getCountStatus() {
    return m_count_status_map;
}



#endif //DESIGN_DNA_DNACOLLECTION_H
