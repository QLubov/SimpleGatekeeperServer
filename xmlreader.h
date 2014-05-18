#ifndef XMLREADER_H
#define XMLREADER_H

#include <iostream>
#include <QtXml/QDomDocument>
#include <QFile>
#include "Action.h"
#include "statemachine.h"


class XMLReader
{
public:
    XMLReader(){}
    ~XMLReader(){}
    QMap< Node, Transition> ReadFile(QFile *);
private:
    QVector<Action*> ParseActions(QDomElement& actions);
    void ParseNode(QDomElement& node, QMap< Node, Transition >& table, State& previousState );
};

#endif // XMLREADER_H
