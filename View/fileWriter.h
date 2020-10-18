//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_FILEWRITER_H
#define DESIGN_DNA_FILEWRITER_H

#include "IWriter.h"
class FileWriter:public IWriter
{
public:
    FileWriter(std::string);
    /*virtual*/ void write(std::string);

private:
    std::string m_fileName;
};

inline FileWriter::FileWriter(std::string name):m_fileName(name) {}



#endif //DESIGN_DNA_FILEWRITER_H
