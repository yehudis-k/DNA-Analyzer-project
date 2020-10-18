//
// Created by student on 21/09/2020.
//

#ifndef DESIGN_DNA_RENAME_H
#define DESIGN_DNA_RENAME_H
#include "../../Controller/ICommand.h"
class Rename:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}
private:
    std::string m_message;
    std::string m_new_name;
    std::string m_old_name;
    SharedPtr<DnaData> m_dna;
};
#endif //DESIGN_DNA_RENAME_H
