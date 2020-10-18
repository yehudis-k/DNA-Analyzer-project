//
// Created by student on 10/08/2020.
//

#include "manager.h"


std::string Manager::execCommand(std::vector<std::string> params) {
    SharedPtr<ICommand> command;
    try {
        command = CommandCollection::getCommand(params[0]);
    }
    catch (ValidError& e) {
        return "Command not found... Enter again";
    }
//    for (size_t i=0; i<params.size(); ++i) {
//        if (params[i] == "##") {
//            if (!DnaCollection::getCache())
//                return "Error! Unable to find requested sequence";
//            params[i] = DnaCollection::getCache()->getName();
//        }
//    }
    if (!command->setParams(params)) {
        return command->getMessage();
    }

    return command->execute();
}

