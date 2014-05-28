#include <QVector>
#include <iostream>
#include "statemachine.h"

const State State::INIT_STATE;

StateMachine::StateMachine()
    : mCurrentState(State::INIT_STATE)
{
}

bool StateMachine::DoTransition(Trigger trigger, GatekeeperListener* listener, const H323RasPDU& pdu)
{
    Node node(mCurrentState, trigger);

    if (mStateTable.contains(node))
    {
        mCurrentState = mStateTable[node].first;
        QVector <Action*> actions = mStateTable[node].second;
        for(size_t i = 0; i < actions.size(); ++i)
            actions[i]->execute(listener, pdu);
        return true;
    }
    std::cout << " DoTransition::false ><\" " << std::endl;
    return false;
}

void StateMachine::AddLastAction()
{
    mLastAddedElement->second.push_back(new EndAction());
}

void StateMachine::insert(const Node &key, const Transition &value)
{
    mLastAddedElement = mStateTable.insert(key, value);
}


QString TriggerToString(Trigger trigger)
{
    switch (trigger) {
    case tGRQ:
        return "tGRQ";
        break;
    case tRRQ:
        return "tRRQ";
        break;
    case tURQ:
        return "tURQ";
        break;
    default:
        return "tXXX";
        break;
    }
}
