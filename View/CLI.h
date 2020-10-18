//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_CLI_H
#define DESIGN_DNA_CLI_H

#define BOLDYELLOW  "\033[1m\033[33m"
#define RESET   "\033[0m"


#include "UI.h"

class CLI:public UI
{
public:
    CLI();
    /*virtual*/ void run(callback);
    /*virtual*/ void init();
    /*virtual*/ void shutDown();
    static void stopRun();

private:
    static std::string readInput(SharedPtr<IReader>);
    static std::vector<std::string> parseInput(const std::string&);
    static std::vector<std::string> setLastReferenceInParams(std::vector<std::string>&);
    static void updateLastReference(const std::string&);
    static bool m_run;
    SharedPtr<IReader> m_reader;
    SharedPtr<IWriter> m_writer;
};

#endif //DESIGN_DNA_CLI_H
