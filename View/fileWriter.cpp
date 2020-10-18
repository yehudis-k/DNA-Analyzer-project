//
// Created by student on 10/08/2020.
//
#include <fstream>
#include "fileWriter.h"
void FileWriter::write(std::string str) {
    std::ofstream file;
    file.open((m_fileName+".txt").c_str());
    if (!file.is_open())
        throw;
    file<<str;
    file.close();
}