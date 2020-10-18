//
// Created by student on 10/08/2020.
//
#include <iostream>
#include "consolReader.h"
#define BOLDYELLOW  "\033[1m\033[33m"
#define RESET   "\033[0m"


std::string ConsolReader::read() {
    //std::cout<<BOLDYELLOW<<"> "<<m_message<<" >>> "<<RESET;
    std::string command;
    getline(std::cin, command);
    return command;
}
