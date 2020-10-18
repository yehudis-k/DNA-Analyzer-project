//
// Created by student on 16/09/2020.
//

#ifndef DESIGN_DNA_DELETE_H
#define DESIGN_DNA_DELETE_H
#define BOLDYELLOW  "\033[1m\033[33m"
#define RESET   "\033[0m"

#include "../../Controller/ICommand.h"
#include "../../Model/dnaCollection.h"
#include "../../View/consolReader.h"
#include "../../View/consolWriter.h"
#include <iostream>
class Delete:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    SharedPtr<DnaData> m_dna;
    std::string m_message;
};
#endif //DESIGN_DNA_DELETE_H
