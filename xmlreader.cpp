#include "xmlreader.h"
#include "logmanager.h"
#include "objectfactory.h"
#include "options.h"
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

XMLReader::XMLReader(const QString &scenarioName)
    : mIsValid(true)
{
    QFile xmlFile(scenarioName);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        LOG("Cann't open XML-file");
        mIsValid = false;
        return;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&xmlFile, true, &errorStr, &errorLine, &errorColumn))
    {
        LOG("Parse error: xml is incorrect\nError: " + errorStr + "\nLine: " + QString::number(errorLine) + "\nColumn: " + QString::number(errorColumn));
        mIsValid = false;
    }

    xmlFile.close();
}

LoadedObject* XMLReader::Parse(const QString& objectName)
{        
    QDomElement testCase = doc.firstChildElement("TestCase");
    if(testCase.isNull())
    {
        LOG("'TestCase' doesn't exist in xml");
        return NULL;
    }

    QDomElement objectNode = testCase.firstChildElement(objectName);
    if(objectNode.isNull())
    {
        LOG("Object node " + objectName + " doesn't exist in xml");
        return NULL;
    }

    LoadedObject* object = ObjectFactory::CreateObject(objectName);
    if(object)
    {
        if(object->OnLoad(objectNode))
            return object;
        LOG("Object " + objectName + " wasn't loaded");
    }
    else
        LOG(objectName + " class doesn't register in factory");
    delete object;
    return NULL;
}

