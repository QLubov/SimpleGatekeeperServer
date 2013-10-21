#ifndef XMLREADER_H
#define XMLREADER_H
#pragma once

#include <queue>
#include <iostream>
#include <QXmlStreamReader>
#include <QFile>
#include <command.h>
#include <commandfactory.h>

class XMLReader
{
public:
    XMLReader(){}
    ~XMLReader(){}
    std::queue<Command*>* ReadFile(QFile *);
private:
    void parseAction(QXmlStreamReader&, std::queue<Command*>*);
};

#endif // XMLREADER_H
