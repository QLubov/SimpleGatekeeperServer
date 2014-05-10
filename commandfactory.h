#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
#include "command.h"
class CommandFactory
{
public:
    CommandFactory(){}
    ~CommandFactory(){}    
    Command* CreateCommand(std::string &type, int value = 0);
};

#endif // COMMANDFACTORY_H
