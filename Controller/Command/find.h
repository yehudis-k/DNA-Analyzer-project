//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_FIND_H
#define DESIGN_DNA_FIND_H
#include "../../Controller/ICommand.h"
class Find:public ICommand
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
#endif //DESIGN_DNA_FIND_H
