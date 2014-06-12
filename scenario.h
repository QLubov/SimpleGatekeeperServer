#ifndef SCENARIO_H
#define SCENARIO_H
#include <QVector>
#include "loadedobject.h"
#include "action.h"
#include "statemachine.h"

class QDomElement;
class Scenario : public LoadedObject
{
    StateMachine mStateMachine;
    QVector<Action*> ParseActions(QDomElement& actions);
    void ParseNode(QDomElement& node, StateMachine& table, State& previousState );
public:
    virtual bool OnLoad(QDomNode& node);
    StateMachine& GetStateMachine() {return mStateMachine;}
};

#endif // SCENARIO_H
