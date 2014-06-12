#ifndef XMLREADER_H
#define XMLREADER_H

#include <iostream>
#include <QtXml/QDomDocument>
#include <QFile>
#include "Action.h"
#include "statemachine.h"


class XMLReader
{
    QDomDocument doc;
    bool mIsValid;
public:
    XMLReader(const QString& scenarioName);
    ~XMLReader(){}
    LoadedObject* Parse(const QString& objectName);
    bool IsValid() const {return mIsValid;}
};

#endif // XMLREADER_H
