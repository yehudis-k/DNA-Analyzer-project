//
// Created by student on 14/09/2020.
//

#include "utilities.h"

bool isId(std::string param) {
    try {
        stoi(param.substr(1));
    }
    catch (std::exception) {
        return false;
    }
    return param[0] == '#';
}

size_t getId(std::string param) {
    return stoi(param.substr(1));
}

bool isValidName(std::string param) {
    return !DnaCollection::nameExists(param);
}

bool isValidId(size_t param) {
    SharedPtr<DnaData> dna = DnaCollection::getByID(param);
    return !dna;
}

std::string getOutput(SharedPtr<DnaData> dna)
{
    std::string my_dna = dna->getDna();
    if (my_dna.length() < 40)
        return "[" + std::to_string(dna->getId()) + "] " + dna->getName() + ": " + my_dna;
    else
        return "[" + std::to_string(dna->getId()) + "] " + dna->getName() + ": " + my_dna.substr(0, 32) + "..." + my_dna.substr(my_dna.length()-3, 3);

}

bool confirm() {
    ConsolWriter writer;
    ConsolReader reader;
    writer.write("Please confirm by 'y' or 'Y', or cancel by 'n' or 'N':\n");
    writer.write(BOLDYELLOW);
    writer.write("> confirm >>> ");
    writer.write(RESET);
    std::string response = reader.read();
    while (true) {
        if (response == "n" || response == "N")
            return false;

        else if (response == "y" || response == "Y") {
            return true;
        }
        writer.write("You have typed an invalid response. Please either confirm by 'y'/'Y', or cancel by 'n'/'N'\n");
        writer.write(BOLDYELLOW);
        writer.write("> confirm >>> ");
        writer.write(RESET);
        response = reader.read();
    }
}
