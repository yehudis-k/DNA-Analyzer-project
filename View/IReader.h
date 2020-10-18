//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_IREADER_H
#define DESIGN_DNA_IREADER_H

#include <string>
class IReader
{
public:
    virtual std::string read() = 0;
};
#endif //DESIGN_DNA_IREADER_H
