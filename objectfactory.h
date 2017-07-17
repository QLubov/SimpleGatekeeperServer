#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H
#include <QMap>
#include <QString>


#define REG(className) ObjectFactory::AddClass(#className, new MetaCreator<className>)

class LoadedObject;
class Creator
{
public:
    virtual LoadedObject* Create() = 0;
    virtual ~Creator() { }
};

template <class  T>
class MetaCreator : public Creator
{
    virtual LoadedObject* Create()
    {
        return new T;
    }
};

class ObjectFactory
{
    QMap <QString, Creator*> mDictionary;
    ObjectFactory(){}

    ObjectFactory(const ObjectFactory&);
    void operator=(const ObjectFactory&);
    static ObjectFactory& Instance();
public:
    ~ObjectFactory(){}
    static LoadedObject* CreateObject(const QString& className);
    static void AddClass(const QString& className, Creator* creator);
};

#endif // ACTIONFACTORY_H
