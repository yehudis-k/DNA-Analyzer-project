//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_QUIT_H
#define DESIGN_DNA_QUIT_H
#include "../../Controller/ICommand.h"

class Quit : public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    std::string m_message;
};
#endif //DESIGN_DNA_QUIT_H
