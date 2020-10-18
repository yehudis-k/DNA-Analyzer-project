//
// Created by student on 15/09/2020.
//

#ifndef DESIGN_DNA_FINDALL_H
#define DESIGN_DNA_FINDALL_H
#include "../../Controller/ICommand.h"
class FindAll:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}
private:
    std::string m_message;
    SharedPtr<DnaData> m_dna;
    std::string m_subseq;
};
#endif //DESIGN_DNA_FINDALL_H
