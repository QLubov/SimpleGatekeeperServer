#include <iostream>
#include <QtXml/QDomDocument>
#include "scenario.h"
#include "statemachine.h"
#include "objectfactory.h"

using namespace std;

Trigger StringToTrigger(const QString &trigger)
{
    if (trigger == "GRQ")
        return tGRQ;
    if (trigger == "RRQ")
        return tRRQ;
    if (trigger == "URQ")
        return tURQ;
    if (trigger == "ARQ")
        return tARQ;
    if (trigger == "BRQ")
        return tBRQ;
    if (trigger == "LRQ")
        return tLRQ;

    return tINVALID;
}

QVector<Action *> Scenario::ParseActions(QDomElement &actions)
{
    QVector<Action*> actionArray;

    QDomNodeList actionNodes = actions.childNodes();
    for ( int i = 0; i < actionNodes.count(); ++i )
    {
        QString actionName = actionNodes.item(i).nodeName();
        LoadedObject* object = ObjectFactory::CreateObject(actionName);
        Action* action = static_cast<Action*>(object);
        action->OnLoad(actionNodes.item(i));
        if(!action)
        {
            cout << "Action with name" << actionName.toStdString() << " not found" << endl;
            for(size_t i = 0; i < actionArray.size(); ++i)
                delete actionArray[i];
            return QVector<Action*>();
        }
        actionArray.push_back(action);
    }
    return actionArray;
}

void Scenario::ParseNode(QDomElement &node, StateMachine &table, State &previousState)
{
    QString name = node.attribute("name");

    State newState(name);

    Trigger trigger = StringToTrigger(name);
    QVector<Action*> actions = ParseActions(node.firstChildElement("Actions"));

    table.insert(Node(previousState ,trigger), Transition(newState, actions));
    previousState = newState;
}

bool Scenario::OnLoad(QDomNode &node)
{
    State previousState = State::INIT_STATE;
    for( QDomElement elem = node.firstChildElement("Node"); !elem.isNull(); elem = elem.nextSiblingElement("Node") )
    {
        ParseNode(elem, mStateMachine, previousState);
    }
    mStateMachine.AddLastAction();

    return true;
}
