#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H
#include <QMap>
#include "action.h"


#define REG(className) ActionFactory::AddClass(#className, new MetaCreator<className>)

class Creator
{
public:
    virtual Action* Create() = 0;
};

template <class  T>
class MetaCreator : public Creator
{
    virtual Action* Create()
    {
        return new T;
    }
};

class ActionFactory
{
    QMap <QString, Creator*> mDictionary;
    ActionFactory(){}
    static ActionFactory& Instance();
public:
    ~ActionFactory(){}
    static Action* CreateAction(const QString& className);
    static void AddClass(const QString& className, Creator* creator);
};

#endif // ACTIONFACTORY_H
