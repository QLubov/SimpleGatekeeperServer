#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
#pragma once

#include "enumOfStates.h"
#include "grqcommand.h"
#include "gcfcommand.h"
#include "grjcommand.h"
#include "rrqcommand.h"
#include "rcfcommand.h"
#include "rrjcommand.h"
#include "urqcommand.h"
#include "ucfcommand.h"
#include "urjcommand.h"
#include "delaycommand.h"

class CommandFactory
{
public:
    CommandFactory(){}
    ~CommandFactory(){}    
    Command* CreateCommand(std::string &type, int value = 0);
};

#endif // COMMANDFACTORY_H
