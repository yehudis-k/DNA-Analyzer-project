//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_CONSOLWRITER_H
#define DESIGN_DNA_CONSOLWRITER_H
#include "IWriter.h"
class ConsolWriter:public IWriter
{
public:
    /*virtual*/ void write(std::string);
};
#endif //DESIGN_DNA_CONSOLWRITER_H
