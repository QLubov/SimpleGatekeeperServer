#ifndef COMMAND_H
#define COMMAND_H

#include <QString.h>

class Command
{    
    int mState;
public:
    Command(int state);
    virtual ~Command();
    virtual void execute() = 0;
    virtual QString GetName() = 0;
};

#endif // COMMAND_H
