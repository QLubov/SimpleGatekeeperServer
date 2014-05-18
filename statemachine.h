#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <QMap>
#include <QPair>
#include <QString>
#include "action.h"

class GatekeeperListener;

enum Trigger
{
    tGRQ,
    tRRQ,
    tURQ,
    tARQ,
    tLRQ,
    tBRQ,
    tINVALID,
};

QString TriggerToString(Trigger trigger);

class State
{
    QString mName;
public:
    State(const QString& name = "INIT")
        : mName(name)
    {
        static int StateID = 0;
        mState = StateID++;
    }
    int mState;
    bool operator < (const State& state) const
    {
        return mState < state.mState;
    }
    QString GetName() const {return mName;}

    static const State INIT_STATE;
};


typedef QPair< State, QVector< Action* > > Transition;
typedef QPair< State, Trigger > Node;

class StateMachine
{
    State mCurrentState;
public:
    QMap< Node, Transition > mStateMap;
    StateMachine(QMap< Node, Transition >& stateMap);
    bool DoTransition(Trigger trigger, GatekeeperListener* listener, const H323RasPDU& pdu);
};

#endif // STATEMACHINE_H
