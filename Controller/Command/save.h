//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_SAVE_H
#define DESIGN_DNA_SAVE_H
#include "../../Controller/ICommand.h"
class Save:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    static std::string getDefaultName(const std::string&);
    std::string m_message;
    std::string m_file_name;
    SharedPtr<DnaData> m_dna;
};
#endif //DESIGN_DNA_SAVE_H
