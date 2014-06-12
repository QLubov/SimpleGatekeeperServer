#ifndef OPTIONS_H
#define OPTIONS_H
#include <QString>
#include "loadedobject.h"
#include <QMap>

class OptionManager
{
    OptionManager(){}
    OptionManager(const OptionManager&);
    OptionManager& operator=(const OptionManager&);
    QMap< QString, QString > mOptionsMap;
public:

    class Options : public LoadedObject
    {
        QMap< QString, QString > mOptionsMap;
    public:
        virtual bool OnLoad(QDomNode& node);
        QMap< QString, QString > GetMap() const {return mOptionsMap;}
    };

    static OptionManager& Instance();
    void SetOptionsMap(const QMap< QString, QString >& map);
    QString GetOption(const QString& name) const;
};

#endif // OPTIONS_H
