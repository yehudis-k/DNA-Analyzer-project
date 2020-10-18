//
// Created by student on 10/08/2020.
//

#include "quit.h"
#include "../../View/consolWriter.h"
#include "../../View/consolReader.h"
#include "../../View/CLI.h"

std::string Quit::getDocumentation() const{
    return "Exits the application after confirming with the user.";
}

std::string Quit::execute() {
    ConsolReader reader;
    ConsolWriter writer;
    std::string modified = std::to_string(DnaCollection::getCountStatus()["modified"]);
    std::string new_ = std::to_string(DnaCollection::getCountStatus()["new"]);
    writer.write("There are "+modified+" modified and "+new_+" new sequences. Are you sure you want to quit?\n");
    if (!confirm())
        return "Cancelled. Not quitting";
    CLI::stopRun();
    return "Thank you for using DNA Analyzer";
}

bool Quit::setParams(std::vector<std::string> params) {
    return true;
}
