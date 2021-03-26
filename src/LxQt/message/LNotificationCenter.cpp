#include "LNotificationCenter.h"

LNotificationCenter* LNotificationCenter::m_pLNotificationCenter = nullptr;

LNotificationCenter::LNotificationCenter()
{

}

LNotificationCenter::~LNotificationCenter()
{

}

LNotificationCenter *LNotificationCenter::getInstance()
{
    if (m_pLNotificationCenter == nullptr)
    {
        m_pLNotificationCenter = new LNotificationCenter();
    }
    return m_pLNotificationCenter;
}

