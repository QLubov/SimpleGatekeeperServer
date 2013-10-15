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

   // LogManager &log = LogManager::Instance();
    //QObject::connect(command, SIGNAL(error()), &log, SIGNAL(exit()));
    if(!std::strcmp(type.c_str(), "GRQ"))
    {
        command = new GRQCommand(GRQ);
        return command;
    }
    if(!std::strcmp(type.c_str(), "GCF"))
    {
        command = new GCFCommand(GCF);
        return command;
    }
    if(!std::strcmp(type.c_str(), "GRJ"))
    {
        command = new GRJCommand(GRJ);
        return command;
    }
    if(!std::strcmp(type.c_str(), "RRQ"))
    {
        command = new RRQCommand(RRQ);
        return command;
    }
    if(!std::strcmp(type.c_str(), "RCF"))
    {
        command = new RCFCommand(RCF);
        return command;
    }
    if(!std::strcmp(type.c_str(), "RRJ"))
    {
        command = new RRJCommand(RRJ);
        return command;
    }
    if(!std::strcmp(type.c_str(), "URQ"))
    {
        command = new URQCommand(URQ);
        return command;
    }
    if(!std::strcmp(type.c_str(), "UCF"))
    {
        command = new UCFCommand(UCF);
        return command;
    }
    if(!std::strcmp(type.c_str(), "URJ"))
    {
        command = new URJCommand(URJ);
        return command;
    }
    return NULL;


}

