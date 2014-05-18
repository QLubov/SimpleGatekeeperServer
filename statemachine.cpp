#include <QVector>
#include <iostream>
#include "statemachine.h"

const State State::INIT_STATE;

StateMachine::StateMachine(QMap< Node, Transition >& stateMap)
    : mStateMap(stateMap),
      mCurrentState( State::INIT_STATE )
{

}

bool StateMachine::DoTransition(Trigger trigger, GatekeeperListener* listener, const H323RasPDU& pdu)
{
    Node node(mCurrentState,trigger);

    if (mStateMap.contains(node))
    {
        mCurrentState = mStateMap[node].first;
        QVector <Action*> actions = mStateMap[node].second;
        for(size_t i = 0; i < actions.size(); ++i)
            actions[i]->execute(listener, pdu);
        return true;
    }
    std::cout << " DoTransition::false ><\" " << std::endl;
    return false;
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
