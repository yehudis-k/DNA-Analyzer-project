//
// Created by student on 10/08/2020.
//

#include <algorithm>
#include "help.h"

std::string Help::getDocumentation() const{
    return "Helps you get to know DNA Analyzer.\n"
           "Help accepts a name of a command, and prints an explanation of it.\n"
           "If a command is not provided, prints all available commands.";
}

std::string Help::getCommandsList() {
    std::vector<std::string> command_list = CommandCollection::getAllCommands();
    std::sort(command_list.begin(), command_list.end());
    std::string res = "All available commands in alphabetical order:\n";
    for (size_t i = 0; i<command_list.size();i++)
        res+=command_list[i]+"\n";
    return res;
}

bool Help::setParams(std::vector<std::string> params) {
    if (params.size() > 2) {
        m_message = "Invalid number of arguments";
        return false;
    }

    if (params.size() == 1)
        m_command = "";
    else {
        try {
            CommandCollection::getCommand(params[1]);
        }
        catch (ValidError) {
            m_message = "Error! Command not found";
            return false;
        }
        m_command = params[1];
    }
    return true;
}

std::string Help::execute() {
    if (m_command == "")
        return getCommandsList();
    return CommandCollection::getCommand(m_command)->getDocumentation();

}
