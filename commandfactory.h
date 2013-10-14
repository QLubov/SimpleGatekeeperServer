#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
#pragma once
//#include <command.h>
//#include <string.h>
#include "enumOfStates.h"
#include <grqcommand.h>
#include <gcfcommand.h>
#include <grjcommand.h>
#include <rrqcommand.h>
#include <rcfcommand.h>
#include <rrjcommand.h>
class CommandFactory
{
public:
    CommandFactory(){}
    ~CommandFactory(){}
    //GRQCommand* CreateGRQCommand();
    //GCFCommand* CreateGCFCommand();
    Command* CreateCommand(std::string &type);
};

#endif // COMMANDFACTORY_H
