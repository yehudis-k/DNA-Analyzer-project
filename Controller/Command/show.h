//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_SHOW_H
#define DESIGN_DNA_SHOW_H
#include "../../Controller/ICommand.h"
class Show:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    std::string m_message;
    size_t m_num_chars;
    SharedPtr<DnaData> m_dna;
};
#endif //DESIGN_DNA_SHOW_H
