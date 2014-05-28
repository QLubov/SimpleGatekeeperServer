#include "xmlreader.h"
#include "actionfactory.h"
#include <QVector>
#include <stdio.h>
using namespace std;


void PrintTable( QMap< Node, Transition >& table )
{
    QMap<Node,Transition>::iterator it;
    cout << "PRINT TABLE:" << endl;
    for(it = table.begin(); it != table.end(); ++it)
    {
        Node node = it.key();
        Transition trans = it.value();

        cout << "Node: " << node.first.GetName().toStdString() << "\t" << "Trigger: " << node.second << "\t ID: " << node.first.mState << endl;
        cout << "Tran: " << trans.first.GetName().toStdString() << "\t";
        for(size_t i = 0; i < trans.second.size(); ++i)
        {
            cout << trans.second[i]->GetName().toStdString() << " ";
        }
        cout << endl;
    }
}

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

StateMachine XMLReader::ReadFile(QFile *xmlFile)
{
    StateMachine stateMachine;

    QDomDocument doc;
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout<<"Cann't open XML-file"<<endl;
        return stateMachine;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(xmlFile, true, &errorStr, &errorLine, &errorColumn))
    {
        cout << "Parse error: xml is incorrect"<<endl;
    }
    QDomElement scenario = doc.documentElement();
    State previousState = State::INIT_STATE;
    for( QDomElement elem = scenario.firstChildElement("node"); !elem.isNull(); elem = elem.nextSiblingElement("node") )
    {
        ParseNode(elem, stateMachine, previousState);
    }
    stateMachine.AddLastAction();
    xmlFile->close();
    return stateMachine;
}

void XMLReader::ParseNode(QDomElement& node, StateMachine& table, State& state )
{
    QString name = node.attribute("name");

    State newState(name);

    Trigger trigger = StringToTrigger(name);
    QVector<Action*> actions = ParseActions(node.firstChildElement("actions"));

    table.insert(Node(state ,trigger), Transition(newState, actions));
    state = newState;
}

QVector<Action *> XMLReader::ParseActions(QDomElement& actions)
{
    QVector<Action*> actionArray;

    QDomNodeList actionNodes = actions.childNodes();
    for ( int i = 0; i < actionNodes.count(); ++i )
    {
        QString actionName = actionNodes.item(i).nodeName();
        Action* action = ActionFactory::CreateAction(actionName);
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

