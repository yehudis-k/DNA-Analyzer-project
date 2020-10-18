//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_HELP_H
#define DESIGN_DNA_HELP_H
#include "../ICommand.h"
#include "../../Controller/commandCollection.h"
class Help:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    static std::string getCommandsList();
    std::string m_message;
    std::string m_command = "";
};
#endif //DESIGN_DNA_HELP_H
