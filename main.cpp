//
// Created by student on 11/08/2020.
//
//g++ -ansi -pedantic -Wall -Wconversion main.cpp Model/*.cpp Controller/Command/*.cpp  View/*.cpp Controller/*.cpp

#include "Controller/manager.h"
#include "View/CLI.h"
int main()
{
    SharedPtr<UI> cli(new CLI);
    Manager m(cli);
    m.runSystem();
    return 0;
}

