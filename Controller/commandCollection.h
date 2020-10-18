//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_COMMANDCOLLECTION_H
#define DESIGN_DNA_COMMANDCOLLECTION_H

#include "ICommand.h"
#include "../Controller/Command/dup.h"
#include "../Controller/Command/help.h"
#include "../Controller/Command/len.h"
#include "../Controller/Command/list.h"
#include "../Controller/Command/find.h"
#include "../Controller/Command/load.h"
#include "../Controller/Command/new.h"
#include "../Controller/Command/quit.h"
#include "../Controller/Command/replace.h"
#include "../Controller/Command/save.h"
#include "../Controller/Command/show.h"
#include "../Controller/Command/slice.h"
#include "../Controller/Command/count.h"
#include "../Controller/Command/findall.h"
#include "../Controller/Command/delete.h"
#include "../Controller/Command/rename.h"
#include "../Controller/Command/reEnum.h"
#include "../Controller/Command/concat.h"
#include "../Controller/Command/pair.h"

#include "../Libraries/Hash_Map/hashmap.h"
#include "../Libraries/Shared_Pointer/SharedPtr.h"

class CommandCollection
{
public:
    static SharedPtr<ICommand> getCommand(const std::string&);
    static std::vector<std::string> getAllCommands();

private:
    static HashMap<SharedPtr<ICommand>> initializeMap();
    static HashMap<SharedPtr<ICommand>> m_commandMap;
    static std::vector<std::string> m_allCommands;
};

#endif //DESIGN_DNA_COMMANDCOLLECTION_H
