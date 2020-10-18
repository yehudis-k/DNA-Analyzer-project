//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_NEW_H
#define DESIGN_DNA_NEW_H
#include "../../Controller/ICommand.h"


class New:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}
    static void setCounter(size_t c) {s_counter = c;}

private:
    static std::string getDefaultName();
    static size_t s_counter;
    std::string m_message;
    std::string m_new_name;
    std::string m_new_sequence;
};
#endif //DESIGN_DNA_NEW_H
