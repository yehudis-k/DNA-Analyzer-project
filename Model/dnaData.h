//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_DNADATA_H
#define DESIGN_DNA_DNADATA_H

#include "dnaSeq.h"
#include "../Libraries/Shared_Pointer/SharedPtr.h"
#include <string>
class DnaData
{
public:
    DnaData(std::string, std::string);
    std::string getDna()const ;
    std::string getName()const;
    size_t getId()const;
    std::string getStatus()const;
    const DnaSequence getSequence()const;
    void setSequence (SharedPtr<DnaSequence>);
    void setName(std::string);
    void setId(size_t);
    static void decreaseId(){s_static_id--;}
    static void setStaticId(size_t id){s_static_id=id;}
    void setStatus(std::string status) {m_status = status;}

private:
    std::string m_status;
    std::string m_name;
    size_t m_id;
    DnaSequence m_dna;
    static size_t s_static_id;
};

inline DnaData::DnaData(std::string name, std::string seq):m_name(name),m_dna(seq), m_id(s_static_id++), m_status("new") {}


inline std::string DnaData::getName()const {
    return m_name;
}

inline size_t DnaData::getId()const {
    return m_id;
}

inline std::string DnaData::getDna() const{
    return m_dna.getSeq();
}

inline std::string DnaData::getStatus() const {
    return m_status;
}

inline const DnaSequence DnaData:: getSequence() const
{
    return m_dna;
}

inline void DnaData::setSequence(SharedPtr<DnaSequence> seq) {
    m_dna.~DnaSequence();
    m_dna = *seq;
}

inline void DnaData::setName(std::string new_name) {
    m_name = new_name;
}

inline void DnaData::setId(size_t new_id) {
    m_id = new_id;
}



#endif //DESIGN_DNA_DNADATA_H
