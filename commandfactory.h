#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
#pragma once
//#include <QObject>
//#include <command.h>
//#include <string.h>
#include "enumOfStates.h"
#include <grqcommand.h>
#include <gcfcommand.h>
#include <grjcommand.h>
#include <rrqcommand.h>
#include <rcfcommand.h>
#include <rrjcommand.h>
#include <urqcommand.h>
#include <ucfcommand.h>
#include <urjcommand.h>
#include <delaycommand.h>
class CommandFactory
{
public:
    CommandFactory(){}
    ~CommandFactory(){}
    //GRQCommand* CreateGRQCommand();
    //GCFCommand* CreateGCFCommand();
    Command* CreateCommand(std::string &type, int value = 0);
};

#endif // COMMANDFACTORY_H
