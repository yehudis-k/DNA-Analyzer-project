//
// Created by student on 10/08/2020.
//

#ifndef DESIGN_DNA_MANAGER_H
#define DESIGN_DNA_MANAGER_H

#include "../View/CLI.h"
#include "../View/UI.h"
#include "../Libraries/Shared_Pointer/SharedPtr.h"
#include "commandCollection.h"


class Manager
{
public:
    Manager(const SharedPtr<UI>&);
    void runSystem();
    static std::string execCommand(std::vector<std::string>);

private:
    void initSystem();
    void shutDown();
    SharedPtr<IReader> m_reader;
    SharedPtr<IWriter> m_writer;
    SharedPtr<UI> m_ui;
};

inline Manager::Manager(const SharedPtr<UI>& ui):
    //m_reader(new ConsolReader),
    //m_writer(new ConsolWriter),
    m_ui(ui) {}


inline void Manager::runSystem() {
    initSystem();
    m_ui->run(&execCommand);
    shutDown();
}


inline void Manager::initSystem() {
    m_ui->init();
}

inline void Manager::shutDown() {
    m_ui->shutDown();
}

#endif //DESIGN_DNA_MANAGER_H
