//
// Created by student on 22/09/2020.
//

#ifndef DESIGN_DNA_PAIR_H
#define DESIGN_DNA_PAIR_H
#include "../../Controller/ICommand.h"
class Pair:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    static std::string getDefaultName(const std::string&);
    static SharedPtr<DnaData> pairInPlace(SharedPtr<DnaData>);
    static SharedPtr<DnaData> createPaired(SharedPtr<DnaData>, std::string);

    std::string m_message;
    SharedPtr<DnaData> m_dna;
    std::string m_new_name;
    bool m_in_place = false;
};

#endif //DESIGN_DNA_PAIR_H
