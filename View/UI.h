//
// Created by student on 21/09/2020.
//

#ifndef DESIGN_DNA_UI_H
#define DESIGN_DNA_UI_H

#include "../View/IWriter.h"
#include "../View/IReader.h"
#include "../Libraries/Shared_Pointer/SharedPtr.h"
#include <string>
#include <vector>

typedef std::string (*callback)(std::vector<std::string>);

class UI
{
public:
    virtual void run(callback)=0;
    virtual void init()=0;
    virtual void shutDown()=0;
};
#endif //DESIGN_DNA_UI_H
