#ifndef LNOTIFIER_H
#define LNOTIFIER_H
#include "LMessageListenner.h"


//主题 - 抽象

class LNotifier
{
public:
    LNotifier();
    ~LNotifier();

public:
    virtual void addListenner(LMessageListenner* listenner) = 0;
    virtual void removeListenner(LMessageListenner* listenner) = 0;
    virtual void notify() = 0;


};

#endif // LNOTIFIER_H
