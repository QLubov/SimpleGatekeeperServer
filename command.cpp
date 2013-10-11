#include "command.h"

Command::Command(int state)
{
    mState = state;
}

Command::~Command()
{
}

bool Command::ValidateState(int state)
{
    return mState == state;
}

