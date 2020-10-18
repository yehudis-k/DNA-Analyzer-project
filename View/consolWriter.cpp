//
// Created by student on 10/08/2020.
//
#include <iostream>
#include "consolWriter.h"
#define BOLDYELLOW  "\033[1m\033[33m"

void ConsolWriter::write(std::string str) {
    std::cout<<str;
}
