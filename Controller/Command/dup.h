//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_DUP_H
#define DESIGN_DNA_DUP_H

#include "../../Controller/ICommand.h"
class Dup:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    static std::string getDefaultName(const std::string&);
    SharedPtr<DnaData> m_dna;
    std::string m_new_name;
    std::string m_message;
};
#endif //DESIGN_DNA_DUP_H
