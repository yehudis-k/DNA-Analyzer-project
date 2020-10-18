//
// Created by student on 14/09/2020.
//

#ifndef DESIGN_DNA_UTILITIES_H
#define DESIGN_DNA_UTILITIES_H
#define BOLDYELLOW  "\033[1m\033[33m"
#define RESET   "\033[0m"

#include <string>
#include <sstream>
#include "../View/consolReader.h"
#include "../View/consolWriter.h"
#include "../Model/dnaCollection.h"

bool isId(std::string param);
size_t getId(std::string param);
bool isValidName(std::string param);
bool isValidId(size_t param);
std::string getOutput(SharedPtr<DnaData> dna);
bool confirm();

#endif //DESIGN_DNA_UTILITIES_H
