//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_LIST_H
#define DESIGN_DNA_LIST_H
#include "../../Controller/ICommand.h"
class List:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>) {return true;}
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return "";}

private:
    std::string getStatus(SharedPtr<DnaData>);
};
#endif //DESIGN_DNA_LIST_H
