//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_SLICE_H
#define DESIGN_DNA_SLICE_H
#include "../../Controller/ICommand.h"
class Slice:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    static std::string getDefaultName(const std::string&);
    static SharedPtr<DnaData> sliceInPlace(SharedPtr<DnaData>, size_t, size_t);
    static SharedPtr<DnaData> createSliced(SharedPtr<DnaData>, std::string, size_t, size_t);

    std::string m_message;
    SharedPtr<DnaData> m_dna;
    std::string m_new_name;
    bool m_in_place = false;
    size_t m_start;
    size_t m_end;
};
#endif //DESIGN_DNA_SLICE_H
