//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_CONSOLREADER_H
#define DESIGN_DNA_CONSOLREADER_H
#include "IReader.h"

class ConsolReader:public IReader
{
public:
    //explicit ConsolReader(const std::string& message = "cmd");
    /*virtual*/ std::string read();

private:
    //std::string m_message;
};

//inline ConsolReader::ConsolReader(const std::string& message) : m_message(message) {}
#endif //DESIGN_DNA_CONSOLREADER_H
