#include "actionfactory.h"

ActionFactory &ActionFactory::Instance()
{
    static ActionFactory inst;
    return inst;
}

Action *ActionFactory::CreateAction(const QString &className)
{
    ActionFactory& factory = Instance();
    if(factory.mDictionary.contains(className))
        return factory.mDictionary[className]->Create();
    return NULL;
}

void ActionFactory::AddClass(const QString &className, Creator *creator)
{
    ActionFactory& factory = Instance();
    factory.mDictionary.insert(className, creator);
}
