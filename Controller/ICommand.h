//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_ICOMMAND_H
#define DESIGN_DNA_ICOMMAND_H

#include <iostream>
#include <vector>
#include <string>
#include "../Model/dnaCollection.h"
#include "utilities.h"
class ICommand
{
public:
    virtual bool setParams(std::vector<std::string>)=0;
    virtual std::string execute()=0;
    virtual std::string getDocumentation()const=0;
    virtual std::string getMessage()const =0;
};

#endif //DESIGN_DNA_ICOMMAND_H
