//
// Created by student on 22/09/2020.
//

#ifndef DESIGN_DNA_CONCAT_H
#define DESIGN_DNA_CONCAT_H
#include "../../Controller/ICommand.h"
class Concat:public ICommand
{
public:
    /*virtual*/ bool setParams(std::vector<std::string>);
    /*virtual*/ std::string execute();
    /*virtual*/ std::string getDocumentation() const;
    /*virtual*/ std::string getMessage() const {return m_message;}

private:
    static std::string getDefaultName(const std::string&, const std::string&);
    static SharedPtr<DnaData> concatInPlace(SharedPtr<DnaData>, SharedPtr<DnaData>);
    static SharedPtr<DnaData> createConcat(SharedPtr<DnaData>, SharedPtr<DnaData>, std::string);

    std::string m_message;
    SharedPtr<DnaData> m_first_seq;
    SharedPtr<DnaData> m_second_seq;
    std::string m_new_name;
    bool m_in_place = false;
};
#endif //DESIGN_DNA_CONCAT_H
