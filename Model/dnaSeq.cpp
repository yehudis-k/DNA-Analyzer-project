//
// Created by student on 01/06/2020.
//
#include "dnaSeq.h"
#include "except.h"
#include <cstring>

//typedef enum {A=0, C=1, G=2, T=3} e_chars;
//char chars[4]={'T', 'G', 'C', 'A'};

DnaSequence::Nucleotide* DnaSequence::convert(const char * c)
{
    Nucleotide* tmp=new Nucleotide[strlen(c)+1];
    for (size_t i = 0; i < strlen(c); i++) {
        try
        {
            tmp[i]=c[i];
        }
        catch (ValidError& er)
        {
            delete [] tmp;
            throw;
        }
    }
    return tmp;
}

DnaSequence::Nucleotide* DnaSequence::convert(const std::string& str) {
    return convert(str.c_str());
}

DnaSequence* DnaSequence::mySlice(size_t start, size_t end)
{
    std::string sliced;
    //char* sliced=new char[end-start+1];
    if (start>end)
        return NULL;
    for(size_t i=start;i<end;i++)
    {
        sliced.push_back(m_seq[i]);
    }
    DnaSequence* new_dna = new DnaSequence(sliced);
    return new_dna;
}

DnaSequence DnaSequence::pair() {
    char* my_pair=new char[length+1];
    for(size_t i=0;i<length;i++)
    {
        switch (m_seq[i])
        {
            case 'A':
                my_pair[i]='T';
                break;
            case 'G':
                my_pair[i]='C';
                break;
            case 'C':
                my_pair[i]='G';
                break;
            case 'T':
                my_pair[i]='A';
                break;
        }
    }
    DnaSequence new_dna(my_pair);
    return new_dna;
}

size_t DnaSequence::find(DnaSequence sub)
{
    return getSeq().find(sub.getSeq());
}

size_t DnaSequence::count(DnaSequence sub)
{
    std::string a=getSeq();
    std::string b=sub.getSeq();
    size_t count=0;
    size_t index=0;
    index=a.find(b);
    if(index>length)
    {
        return 0;
    }
    count++;
    for(size_t i=0;i<length;i++)
    {
        index=a.find(b,index+1);
        if(index>length)
            break;
        count++;
    }
    return count;
}

std::vector<size_t> DnaSequence::findAll(DnaSequence sub)
{
    std::vector<size_t> vec;
    size_t index=0;
    index=getSeq().find(sub.getSeq());
    if(index>length)
    {
        return vec;
    }
    vec.push_back(index);
    for(size_t i=0;i<length;i++)
    {
        index=getSeq().find(sub.getSeq(), index+1);
        if(index>length)
            break;
        vec.push_back(index);
    }
    return vec;
}

std::vector<DnaSequence> DnaSequence::findConsensusSeq()
{
    std::string a=getSeq();
    std::vector<size_t> begin_indexes=findAll((char*)"ATG");
    std::vector<size_t> end1;
    std::vector<size_t> end2;
    std::vector<size_t> end3;
    end1=findAll((char*) "TAG");
    end2=findAll((char*)"TAA");
    end3=findAll((char*)"TGA");
    std::vector<DnaSequence> res;
    for(size_t i=0;i<begin_indexes.size();i++)
    {
        for (size_t j=0;j<end1.size();j++)
        {
            if(((end1[j]-begin_indexes[i])%3==0)&&(end1[j]>begin_indexes[i]))
            {
                res.push_back(*mySlice(begin_indexes[i],end1[j]+3));
            }
        }
        for (size_t k=0;k<end2.size();k++)
        {
            if(((end2[k]-begin_indexes[i])%3==0)&&(end2[k]>begin_indexes[i]))
            {
                res.push_back(*mySlice(begin_indexes[i],end2[k]+3));
            }
        }
        for (size_t l=0;l<end3.size();l++)
        {
            if(((end3[l]-begin_indexes[i])%3==0)&&(end3[l]>begin_indexes[i]))
            {
                res.push_back(*mySlice(begin_indexes[i],end3[l]+3));
            }
        }
    }
    return res;
}

/*void writeToFile(DnaSequence dna, const char* filename)
{
    std::ofstream my_file;
    my_file.open(filename);
    if(my_file.is_open())
    {
        my_file<<dna.getSeq();
        my_file.close();
    }
    else
    {
        std::cout<<"Unable to open file"<<std::endl;
        throw OpenFileError();
    }
}

DnaSequence readFromFile(const char* filename)
{
    std::string str;
    std::ifstream my_file;
    my_file.open(filename);
    if(my_file.is_open()) {
        getline(my_file, str);
        my_file.close();
        return DnaSequence(str);
    }
    else
    {
        std::cout<<"Unable to open file"<<std::endl;
        throw OpenFileError();
    }
}*/