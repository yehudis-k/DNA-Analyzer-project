//
// Created by student on 10/08/2020.
//

#include "fileReader.h"
#include <fstream>
std::string FileReader::read() {
    std::fstream dna_file(m_fileName.c_str());
    if(!dna_file.is_open()) {
        throw std::exception();
    }
    std::string str;
    std::string res = "";
    while (getline(dna_file, str))
        res += str;
    dna_file.close();
    return res;
}