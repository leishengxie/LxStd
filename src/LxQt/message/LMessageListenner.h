#ifndef LMESSAGE_LISTENNER_H
#define LMESSAGE_LISTENNER_H

//观察者-抽象


class LMessageListenner
{
public:
    LMessageListenner();
    ~LMessageListenner();

    virtual void requreRefrsh() = 0;
};

#endif // LMESSAGE_LISTENNER_H
