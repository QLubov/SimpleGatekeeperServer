#include <xmlreader.h>

using namespace std;

queue<Command*>* XMLReader::ReadFile(QFile *xmlFile)
{
    queue<Command*> *ListOfCommand = new queue<Command*>;
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout<<"Cann't open XML-file"<<endl;
        return ListOfCommand;
    }
    QXmlStreamReader xml(xmlFile);
    //queue<Command*> *ListOfCommand = new queue<Command*>;
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "scenario")
                continue;
            if (xml.name() == "action")
                parseAction(xml, ListOfCommand);
        }
    }
    xml.clear();
    xmlFile->close();
    return ListOfCommand;
}

void XMLReader::parseAction(QXmlStreamReader& xml, queue<Command*>* ListOfCommand)
{
    CommandFactory cmdFactory;
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "action")
            return ;//ListOfCommand;
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "action"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "type")
            {
                xml.readNext();
                ListOfCommand->push(cmdFactory.CreateCommand(xml.text().toString().toStdString()));
                //cout<<xml.text().toString().toStdString()<<endl;
            }
        }
        xml.readNext();
    }
    //return ListOfCommand;
}

