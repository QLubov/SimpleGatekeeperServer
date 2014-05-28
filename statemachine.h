#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <QMap>
#include <QVector>
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
    QMap<Node, Transition>::iterator mLastAddedElement;
    QMap<Node, Transition> mStateTable;
public:
    StateMachine();
    bool DoTransition(Trigger trigger, GatekeeperListener* listener, const H323RasPDU& pdu);
    void insert( const Node& key, const Transition & value );
    void AddLastAction();
};

#endif // STATEMACHINE_H
