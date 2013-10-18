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
            if (xml.name() == "action" || xml.name() == "delay")
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

    if(xml.name() == "delay")
    {
        xml.readNext();
        ListOfCommand->push(cmdFactory.CreateCommand(std::string("delay"),xml.text().toString().toInt()));
        std::cout<<std::string("delay")<<endl;
        std::cout<<xml.text().toString().toInt()<<endl;
    }
    else
    {
        if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "action")// || (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == "delay"))
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
    }
    /*//while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "delay"))
    //{
        if(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "delay"))//xml.tokenType() == QXmlStreamReader::StartElement)
        {
            //if(xml.name() == "delay")
            //{
             //   xml.readNext();
                ListOfCommand->push(cmdFactory.CreateCommand(std::string("delay"),xml.text().toString().toInt()));
                //cout<<xml.text().toString().toStdString()<<endl;
           // }
                xml.readNext();

        }*/

    //}
    //return ListOfCommand;
}

