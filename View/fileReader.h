//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_FILEREADER_H
#define DESIGN_DNA_FILEREADER_H

#include "IReader.h"
class FileReader:public IReader
{
public:
    FileReader(std::string);
    /*virtual*/ std::string read();

private:
    std::string m_fileName;
};

inline FileReader::FileReader(std::string str): m_fileName(str){}



#endif //DESIGN_DNA_FILEREADER_H
