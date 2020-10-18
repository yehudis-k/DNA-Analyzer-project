//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_IWRITER_H
#define DESIGN_DNA_IWRITER_H

#include <string>
class IWriter
{
public:
    virtual void write(std::string) = 0;
};
#endif //DESIGN_DNA_IWRITER_H
