#ifndef LNOTIFICATIONCENTER_H
#define LNOTIFICATIONCENTER_H
#include <list>
#include "LNotifier.h"
#include "LMessageListenner.h"

using namespace std;

class LNotificationCenter : public LNotifier
{


    LNotificationCenter();
    ~LNotificationCenter();

public:
    static LNotificationCenter* getInstance();

    virtual void addListenner(LMessageListenner* listenner)
    {
        m_listenners.push_back(listenner);
    }

    virtual void removeListenner(LMessageListenner* listenner)
    {
        //if contains();
        m_listenners.remove(listenner);
        //delete listenner;
    }

    virtual void notify()
    {
        list <LMessageListenner*> ::iterator it = m_listenners.begin();
        for (; it != m_listenners.end(); ++it)
        {
            (*it)->requreRefrsh();
        }
    }

private:
    static LNotificationCenter* m_pLNotificationCenter;

private:
    list<LMessageListenner*> m_listenners;

};

#endif // LNOTIFICATIONCENTER_H
