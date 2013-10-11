#ifndef SIMPLEENDPOINT_H
#define SIMPLEENDPOINT_H
#pragma once
#include <h323.h>

class EndPoint : public H323EndPoint
{    
public:
    EndPoint();
    ~EndPoint(){}

};

#endif // SIMPLEENDPOINT_H
