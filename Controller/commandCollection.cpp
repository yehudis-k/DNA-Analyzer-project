//
// Created by student on 21/09/2020.
//
#include "commandCollection.h"


std::vector<std::string> CommandCollection::m_allCommands;
HashMap<SharedPtr<ICommand>> CommandCollection::m_commandMap = initializeMap();

HashMap<SharedPtr<ICommand>> CommandCollection::initializeMap() {
    HashMap<SharedPtr<ICommand>> tmp_map;
    tmp_map.insert("new", SharedPtr<ICommand>(new New()));
    m_allCommands.emplace_back("new");
    tmp_map.insert("load", SharedPtr<ICommand>(new Load()));
    m_allCommands.emplace_back("load");
    tmp_map.insert("save", SharedPtr<ICommand>(new Save()));
    m_allCommands.emplace_back("save");
    tmp_map.insert("len", SharedPtr<ICommand>(new Len()));
    m_allCommands.emplace_back("len");
    tmp_map.insert("find", SharedPtr<ICommand>(new Find()));
    m_allCommands.emplace_back("find");
    tmp_map.insert("count", SharedPtr<ICommand>(new Count()));
    m_allCommands.emplace_back("count");
    tmp_map.insert("findAll", SharedPtr<ICommand>(new FindAll()));
    m_allCommands.emplace_back("findAll");
    tmp_map.insert("slice", SharedPtr<ICommand>(new Slice()));
    m_allCommands.emplace_back("slice");
    tmp_map.insert("del", SharedPtr<ICommand>(new Delete()));
    m_allCommands.emplace_back("del");
    tmp_map.insert("quit", SharedPtr<ICommand>(new Quit()));
    m_allCommands.emplace_back("quit");
    tmp_map.insert("dup", SharedPtr<ICommand>(new Dup()));
    m_allCommands.emplace_back("dup");
    tmp_map.insert("help", SharedPtr<ICommand>(new Help()));
    m_allCommands.emplace_back("help");
    tmp_map.insert("rename", SharedPtr<ICommand>(new Rename()));
    m_allCommands.emplace_back("rename");
    tmp_map.insert("reEnum", SharedPtr<ICommand>(new ReEnum()));
    m_allCommands.emplace_back("reEnum");
    tmp_map.insert("concat", SharedPtr<ICommand>(new Concat()));
    m_allCommands.emplace_back("concat");
    tmp_map.insert("pair", SharedPtr<ICommand>(new Pair()));
    m_allCommands.emplace_back("pair");
    tmp_map.insert("replace", SharedPtr<ICommand>(new Replace()));
    m_allCommands.emplace_back("replace");
    tmp_map.insert("show", SharedPtr<ICommand>(new Show()));
    m_allCommands.emplace_back("show");
    tmp_map.insert("list", SharedPtr<ICommand>(new List()));
    m_allCommands.emplace_back("list");

    return tmp_map;
}

SharedPtr<ICommand> CommandCollection::getCommand(const std::string& str){
    if (m_commandMap.contains(str))
        return m_commandMap[str];
    else
        throw ValidError();
}

std::vector<std::string> CommandCollection::getAllCommands() {
    return m_allCommands;
}
