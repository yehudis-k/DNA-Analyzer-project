//
// Created by student on 10/08/2020.
//

#include <cstring>
#include "CLI.h"
#include "consolReader.h"
#include "consolWriter.h"
#include "cache.h"

bool CLI::m_run = true;

void CLI::run(callback executeCommand) {
    while (m_run)
    {
        m_writer->write(BOLDYELLOW);
        m_writer->write("\n> cmd >>> ");
        m_writer->write(RESET);

        std::string input = readInput(m_reader);
        if (input == "")
            continue;
        std::vector<std::string> parsed = parseInput(input);

        parsed = setLastReferenceInParams(parsed);

        std::string output = (*executeCommand)(parsed);

        updateLastReference(output);

        m_writer->write(output);
        m_writer->write("\n");
    }
    m_writer->write(BOLDYELLOW);
    m_writer->write("\nGOODBYE\n");
    m_writer->write(RESET);
}

inline std::string CLI::readInput(SharedPtr<IReader> reader){
    return reader->read();
}

std::vector<std::string> CLI::parseInput(const std::string& command){
    std::vector<std::string> parsed;
    char* c = const_cast<char*>(command.c_str());
    char* current = strtok(c, " ");
    while (current != nullptr)
    {
        parsed.emplace_back(current);
        current = strtok(nullptr, " ");
    }
    return parsed;
}

void CLI::stopRun() {
    m_run = false;
}



void CLI::init() {
    std::system("clear");
    m_writer->write(BOLDYELLOW);
    m_writer->write("---Welcome to DNA Analyzer---\n\n");
    m_writer->write(RESET);

}

void CLI::shutDown() {
    m_writer->write("Shutting down... Goodbye\n");
}

std::vector<std::string> CLI::setLastReferenceInParams(std::vector<std::string>& parsed) {
    for (size_t i=0; i<parsed.size(); ++i) {
        if (parsed[i] == "##") {
            parsed[i] = "#"+std::to_string(Cache::getCache());
        }
    }
    return parsed;
}

void CLI::updateLastReference(const std::string& output) {
    if (output[0] == '[')
        Cache::updateCache(stoi(output.substr(1, output.find(']'))));
}

CLI::CLI() : m_reader(new ConsolReader), m_writer(new ConsolWriter) { }


