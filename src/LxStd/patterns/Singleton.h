#ifndef __CSSINGLETON_H__
#define __CSSINGLETON_H__

#include <list>
#include <algorithm>

class CSingletonBase
{
	class InstanceTable : public std::list < CSingletonBase * >
	{
	public:
		InstanceTable()
			: m_bIsCleared(false)
		{

        }

		~InstanceTable()
		{
			m_bIsCleared = true;
			//for_each(begin(), end(), destroyInstance);
		}

	public:
		static void destroyInstance(CSingletonBase *pInstance)
		{
			try
			{
				delete pInstance; 
				pInstance = NULL;
			}
			catch (...)
			{
			}
		}

	public:
		bool m_bIsCleared;
	};

protected:
	CSingletonBase()
	{
		_sInstanceTable.push_back(this);
	}

	virtual ~CSingletonBase()
	{
		if (!_sInstanceTable.m_bIsCleared)
		{
			_sInstanceTable.remove(this);
		}
	}

private:
	static InstanceTable _sInstanceTable;
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
template <typename T>
class CSingleton : public CSingletonBase
{
public:
	static T* getInstance()
	{
		if (_sSingleton == nullptr)
		{
			_sSingleton = new (std::nothrow) T();
		}
		return _sSingleton;
	}

protected:
	CSingleton()
	{

    }

	virtual ~CSingleton()
	{
		_sSingleton = nullptr;
    }

private:
	static T* _sSingleton;
};

template<typename T> T* CSingleton<T>::_sSingleton = nullptr;

#endif
