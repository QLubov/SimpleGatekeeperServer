#ifndef LOADEDOBJECT_H
#define LOADEDOBJECT_H

class QDomNode;
class LoadedObject
{
public:
    LoadedObject(){}
    virtual ~LoadedObject(){}
    virtual bool OnLoad(QDomNode& node) = 0;
};

#endif // LOADEDOBJECT_H
