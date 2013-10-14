#include "commandfactory.h"

/*GCFCommand* CommandFactory::CreateGCFCommand()
{
    return new GCFCommand;
}
GRQCommand* CommandFactory::CreateGRQCommand()
{
    return new GRQCommand;
}*/
Command* CommandFactory::CreateCommand(std::string &type)
{
    Command *command;
    if(!std::strcmp(type.c_str(), "GRQ"))
    {
        command = new GRQCommand(0);
        return command;
    }
    if(!std::strcmp(type.c_str(), "GCF"))
    {
        command = new GCFCommand(1);
        return command;
    }
    if(!std::strcmp(type.c_str(), "GRJ"))
    {
        command = new GRJCommand(2);
        return command;
    }
    if(!std::strcmp(type.c_str(), "RRQ"))
    {
        command = new RRQCommand(3);
        return command;
    }
    if(!std::strcmp(type.c_str(), "RCF"))
    {
        command = new RCFCommand(4);
        return command;
    }
    if(!std::strcmp(type.c_str(), "RRJ"))
    {
        command = new RRJCommand(5);
        return command;
    }
    return NULL;


}

