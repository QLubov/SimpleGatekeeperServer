#include "commandfactory.h"

Command* CommandFactory::CreateCommand(std::string &type, int value)
{
    Command *command;

    if(type == "delay")// !std::strcmp(type.c_str(), "delay"))
    {
        command = new DelayCommand(delay, value);
        return command;
    }

    if(type == "GRQ")// !std::strcmp(type.c_str(), "GRQ"))
    {
        command = new GRQCommand(GRQ);
        return command;
    }
    if(type == "GCF")// !std::strcmp(type.c_str(), "GCF"))
    {
        command = new GCFCommand(GCF);
        return command;
    }
    if(type == "GRJ")// !std::strcmp(type.c_str(), "GRJ"))
    {
        command = new GRJCommand(GRJ);
        return command;
    }
    if(type == "RRQ")// !std::strcmp(type.c_str(), "RRQ"))
    {
        command = new RRQCommand(RRQ);
        return command;
    }
    if(type == "RCF")// !std::strcmp(type.c_str(), "RCF"))
    {
        command = new RCFCommand(RCF);
        return command;
    }
    if(type == "RRJ")// !std::strcmp(type.c_str(), "RRJ"))
    {
        command = new RRJCommand(RRJ);
        return command;
    }
    if(type == "URQ")// !std::strcmp(type.c_str(), "URQ"))
    {
        command = new URQCommand(URQ);
        return command;
    }
    if(type == "UCF")// !std::strcmp(type.c_str(), "UCF"))
    {
        command = new UCFCommand(UCF);
        return command;
    }
    if(type == "URJ")// !std::strcmp(type.c_str(), "URJ"))
    {
        command = new URJCommand(URJ);
        return command;
    }
    return NULL;


}

