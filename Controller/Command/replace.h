//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_REPLACE_H
#define DESIGN_DNA_REPLACE_H
#include "../../Controller/ICommand.h"
class Replace:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    static std::string getDefaultName(const std::string&);
    static SharedPtr<DnaData> replaceInPlace(SharedPtr<DnaData>, const std::string&);
    static SharedPtr<DnaData> createReplaced(std::string, std::string);

    std::string m_message;
    SharedPtr<DnaData> m_dna;
    std::string m_new_name;
    bool m_in_place = false;
    std::vector<size_t> m_indexes;
    std::vector<std::string> m_new_letters;
};
#endif //DESIGN_DNA_REPLACE_H
