#include <QtXml/QDomDocument>
#include "options.h"

OptionManager &OptionManager::Instance()
{
    static OptionManager instance;
    return instance;
}

void OptionManager::SetOptionsMap(const QMap<QString, QString>& map)
{
    mOptionsMap = map;
}

QString OptionManager::GetOption(const QString &name) const
{
    if(mOptionsMap.contains(name))
        return mOptionsMap.value(name);
    return "";
}

bool OptionManager::Options::OnLoad(QDomNode &node)
{
    QDomNodeList options = node.childNodes();
    for(size_t i = 0; i < options.count(); ++i)
    {
        QDomNode item = options.item(i);
        mOptionsMap.insert(item.nodeName(), item.nodeValue());
    }
    return true;
}
