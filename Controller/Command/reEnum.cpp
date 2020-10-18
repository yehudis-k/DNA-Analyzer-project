//
// Created by student on 21/09/2020.
//

#include "reEnum.h"
#include "new.h"

std::string ReEnum::getDocumentation() const{
    return "Re-enumerates all the sequences.\n"
           "The original order is kept.";
}

std::string ReEnum::execute() {
    std::vector<std::string> ids = DnaCollection::getAllIds();
    std::vector<std::string>::iterator it = ids.begin();
    size_t curr_id = 1;
    for(; it!=ids.end(); ++it) {
        DnaCollection::setId(DnaCollection::getByID(stoi(*it)), curr_id);
        curr_id++;
    }
    DnaData::setStaticId(curr_id);
    return "reEnum completed";
}