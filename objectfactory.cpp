#include "objectfactory.h"

ObjectFactory &ObjectFactory::Instance()
{
    static ObjectFactory inst;
    return inst;
}

LoadedObject *ObjectFactory::CreateObject(const QString &className)
{
    ObjectFactory& factory = Instance();
    if(factory.mDictionary.contains(className))
        return factory.mDictionary[className]->Create();
    return NULL;
}

void ObjectFactory::AddClass(const QString &className, Creator *creator)
{
    ObjectFactory& factory = Instance();
    factory.mDictionary.insert(className, creator);
}
