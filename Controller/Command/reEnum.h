//
// Created by student on 21/09/2020.
//

#ifndef DESIGN_DNA_REENUM_H
#define DESIGN_DNA_REENUM_H
#include "../../Controller/ICommand.h"
class ReEnum:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>){return true;};
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}
private:
    std::string m_message;
};
#endif //DESIGN_DNA_REENUM_H
