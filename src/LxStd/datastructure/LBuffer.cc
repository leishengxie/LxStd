
#include "LBuffer.h"
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)


    CLBuffer::CLBuffer(int nDefaultSize)
	{
		m_nBeginPos = 0;
		m_nEndPos = 0;
		m_pData = (unsigned char*)malloc(nDefaultSize);
		if (m_pData == NULL)
		{
			m_nBufferSize = 0;
		}
		else
		{
            memset(m_pData, 0, nDefaultSize);
			m_nBufferSize = nDefaultSize;
		}
	}

    CLBuffer::CLBuffer(const CLBuffer& src)
	{
		m_nBeginPos = 0;
		m_nEndPos = 0;
		m_pData = NULL;
		m_nBufferSize = 0;
		m_nBeginPos = 0;
		m_nEndPos = 0;
        this->Write((CLBuffer&)src);
	}

    CLBuffer::~CLBuffer()
	{
		if (m_pData != NULL)
			free(m_pData);
	}

    CLBuffer& CLBuffer::operator<<(std::string & str)
	{
		if (str.length() > 0)
			Write((const unsigned char*)(str.c_str()), str.length());
		return *this;
	}

    CLBuffer&  CLBuffer::operator<<(char* str)
	{
		int len = strlen(str);
		if (len > 0)
			Write((const unsigned char*)str, len);
		return *this;
	}

    unsigned char* CLBuffer::Begin()
	{
		return m_pData + m_nBeginPos;
	}

    unsigned char* CLBuffer::End()
	{
		return m_pData + m_nEndPos;
	}

    void CLBuffer::MoveEndPos(int nPos)
	{
		m_nEndPos += nPos;
	}

    void CLBuffer::MoveBeginPos(int nPos)
	{
		m_nBeginPos += nPos;
	}

    void CLBuffer::Skip(int nPos)
	{
		MoveBeginPos(nPos);
	}

    void CLBuffer::SetBeginPos(int nPos)
	{
		m_nBeginPos = nPos;
	}

    void CLBuffer::SetEndPos(int nPos)
	{
		m_nEndPos = nPos;
	}

    int CLBuffer::GetBeginPos()
	{
		return m_nBeginPos;
	}

    int CLBuffer::GetEndPos()
	{
		return m_nEndPos;
	}

    int CLBuffer::DataSize()
	{
		return m_nEndPos - m_nBeginPos;
	}

    int CLBuffer::FreeSize()
	{
		return m_nBufferSize - m_nEndPos;
	}

    int CLBuffer::Capacity()
	{
		return m_nBufferSize;
	}

    bool CLBuffer::EnsureFreeSpace(int size)
	{
		if (FreeSize() < size)
		{
			int nTempSize = m_nBufferSize;
			while (nTempSize < size + m_nEndPos)
			{
				if (nTempSize == 0)
					nTempSize += 1024;
				else
					nTempSize = nTempSize * 2;
			}
			unsigned char* pData = (unsigned char*)malloc(nTempSize);
			if (pData == NULL)
				return false;
			m_nBufferSize = nTempSize;
			memset(pData, 0, nTempSize);
			memcpy(pData, m_pData, m_nEndPos);
			free(m_pData);
			m_pData = pData;
		}
		return true;
	}

    void CLBuffer::Clear()
	{
		memset(m_pData, 0, m_nBufferSize);
		m_nEndPos = 0;
		m_nBeginPos = 0;
	}

    void CLBuffer::Erase(int nPos)
	{
		if (nPos == 0)
			return;
		m_nBeginPos -= nPos;
		m_nEndPos -= nPos;
		if (m_nBeginPos < 0)
			m_nBeginPos = 0;
		if (m_nEndPos < 0)
			m_nEndPos = 0;
		unsigned char* pBegin = Begin();
		memmove(pBegin, pBegin + nPos, m_nEndPos);
		memset(m_pData + m_nEndPos, 0, m_nBufferSize - m_nEndPos);
	}

    void CLBuffer::Write(std::string& str)
	{
		Write((const unsigned char*)str.c_str(), str.length());
	}

    void CLBuffer::WriteLine(std::string str)
	{
		str.append("\r\n");
		Write(str);
	}

    void CLBuffer::Write(const unsigned char* pBuf, int length)
	{
		if (length <= 0)
			return;
		EnsureFreeSpace(length);
		if (FreeSize() < length)
			return;
		unsigned char* pEnd = End();
		memcpy(pEnd, pBuf, length);
		MoveEndPos(length);
	}

    void CLBuffer::WriteChar(unsigned char c)
	{
		Write((unsigned char*)&c, 1);
	}

    void CLBuffer::WriteUInt16(unsigned int i)
	{
		WriteChar(*((unsigned char*)&i + 1));
		WriteChar(*((unsigned char*)&i));
	}

    void CLBuffer::WriteUInt24(unsigned int i)
	{
		WriteChar(*((unsigned char*)&i + 2));
		WriteChar(*((unsigned char*)&i + 1));
		WriteChar(*((unsigned char*)&i));
	}

    void CLBuffer::WriteUInt32(unsigned int i)
	{
		WriteChar(*((unsigned char*)&i + 3));
		WriteChar(*((unsigned char*)&i + 2));
		WriteChar(*((unsigned char*)&i + 1));
		WriteChar(*((unsigned char*)&i));
	}

    void CLBuffer::WriteUInt32ToString(unsigned int i)
	{
		char val[10] = { 0 };
		sprintf(val, "%d", i);
		Write((const unsigned char*)val, strlen(val));
	}

    void CLBuffer::WriteReverseUInt32(unsigned int i)
	{
		Write((unsigned char*)&i, 4);
	}

    void CLBuffer::WriteInt64(int64 i)
	{
		WriteChar(*((unsigned char*)&i + 7));
		WriteChar(*((unsigned char*)&i + 6));
		WriteChar(*((unsigned char*)&i + 5));
		WriteChar(*((unsigned char*)&i + 4));
		WriteChar(*((unsigned char*)&i + 3));
		WriteChar(*((unsigned char*)&i + 2));
		WriteChar(*((unsigned char*)&i + 1));
		WriteChar(*((unsigned char*)&i));
	}

    void CLBuffer::WriteDouble(double d)
	{
		WriteChar(*((unsigned char*)&d + 7));
		WriteChar(*((unsigned char*)&d + 6));
		WriteChar(*((unsigned char*)&d + 5));
		WriteChar(*((unsigned char*)&d + 4));
		WriteChar(*((unsigned char*)&d + 3));
		WriteChar(*((unsigned char*)&d + 2));
		WriteChar(*((unsigned char*)&d + 1));
		WriteChar(*((unsigned char*)&d));
	}

    void CLBuffer::Write(CLBuffer& pBuffer)
	{
		unsigned char* pBegin = pBuffer.Begin();
		Write(pBegin, pBuffer.DataSize());
	}

    char CLBuffer::ReadChar()
	{
		char c = *Begin();
		MoveBeginPos(1);
		return c;
	}

    unsigned char CLBuffer::ReadUChar()
	{
		return ReadChar();
	}

    int CLBuffer::ReadInt16()
	{
		unsigned char* p = (unsigned char*)Begin();
		unsigned int ret = (p[0] << 8) | p[1];
		MoveBeginPos(2);
		return ret;
	}

    unsigned int CLBuffer::ReadUInt16()
	{
		return ReadInt16();
	}

    unsigned int CLBuffer::ReadUInt24()
	{
		unsigned char* p = (unsigned char*)Begin();
		unsigned int ret = (p[0] << 16) | (p[1] << 8) | p[2];
		MoveBeginPos(3);
		return ret;
	}

    int CLBuffer::ReadInt32()
	{
		unsigned char* p = (unsigned char*)Begin();
		unsigned int ret = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
		MoveBeginPos(4);
		return ret;
	}

    unsigned int CLBuffer::ReadUInt32()
	{
		return ReadInt32();
	}

    unsigned int CLBuffer::ReadReverseUInt24()
	{
		unsigned char* p = (unsigned char *)Begin();
		unsigned int ret = (p[2] << 16) | (p[1] << 8) | p[0];
		MoveBeginPos(3);
		return ret;
	}

    unsigned int CLBuffer::ReadReverseUInt32()
	{
		unsigned char* p = (unsigned char*)Begin();
		unsigned int ret = (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
		MoveBeginPos(4);
		return ret;
	}

    double CLBuffer::ReadDouble()
	{
		unsigned char* p = (unsigned char*)Begin();
		double ret;
		unsigned char* pd = (unsigned char*)&ret;
		pd[0] = p[7];
		pd[1] = p[6];
		pd[2] = p[5];
		pd[3] = p[4];
		pd[4] = p[3];
		pd[5] = p[2];
		pd[6] = p[1];
		pd[7] = p[0];
		MoveBeginPos(8);
		return ret;
	}

    int64 CLBuffer::ReadInt64()
	{
		unsigned char* p = (unsigned char*)Begin();
        int64 ret = p[0] * 0x100000000000000 + p[1] * 0x1000000000000 + p[2] * 0x10000000000 + p[3] * 0x100000000 + p[4] * 0x1000000 + p[5] * 0x10000 + p[6] * 0x100 + p[7];
		MoveBeginPos(8);
		return ret;
	}

    uint64 CLBuffer::ReadUInt64()
	{
		return ReadInt64();
	}

    std::string CLBuffer::ReadString(int length)
	{
		std::string str((char*)Begin(), length);
		MoveBeginPos(length);
		return str;
	}

    std::string CLBuffer::ReadLine()
	{
		unsigned char* p = (unsigned char*)Begin();
		unsigned int index = 0;
		while (p != (unsigned char*)End() && p + 1 != (unsigned char*)End())
		{
			if (*p == '\r' && *(p + 1) == '\n')
			{
				std::string str((char*)Begin(), index);
				MoveBeginPos(index + 2);
				return str;
			}
			index++;
			p++;
		}
		p = (unsigned char*)Begin();
		index = 0;
		while (p != (unsigned char*)End())
		{
			if (*p == '\n')
			{
				std::string str((char*)Begin(), index);
				MoveBeginPos(index + 1);
				return str;
			}
			index++;
			p++;
		}
		return (char*)"";
	}

    bool CLBuffer::IsFindValue(char* pValue, int nSize)
	{
		if (this->DataSize() < nSize)
			return false;
		char* p = (char*)Begin();
		if (strncmp(p, pValue, nSize) == 0)
			return true;
		return false;
	}

    int CLBuffer::FindValue(char* pValue, int pos)
	{
		int nSize = strlen(pValue);
		if (this->DataSize() < nSize)
			return -1;
		pos += GetBeginPos();
		char* p = (char*)Begin() + (pos - GetBeginPos());
		int curPos = +pos;
		while (curPos <= (GetEndPos() - nSize))
		{
			if (strncmp(p, pValue, nSize) == 0)
				return curPos - GetBeginPos();
			p++;
			curPos++;
		}
		return -1;
	}

    unsigned char CLBuffer::GetUChar(int start)
	{
		return Begin()[start];
	}

    int64 CLBuffer::GetInt64(int start)
	{
		unsigned char* p = (unsigned char*)Begin() + start;
		int64 ret = p[0] * 0x100000000000000 + p[1] * 0x1000000000000 + p[2] * 0x10000000000 + p[3] * 0x100000000 + p[4] * 0x1000000 + p[5] * 0x10000 + p[6] * 0x100 + p[7];
		return ret;
	}

    unsigned int CLBuffer::GetUInt32(int start)
	{
		unsigned char* p = (unsigned char*)Begin() + start;
		unsigned int ret = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
		return ret;
	}

    unsigned int CLBuffer::GetUInt16(int start)
	{
		unsigned char* p = (unsigned char*)Begin() + start;
		unsigned int ret = (p[0] << 8) | p[1];
		return ret;
	}

    unsigned int CLBuffer::GetUInt24(int start)
	{
		unsigned char* p = (unsigned char*)Begin() + start;
		unsigned int ret = (p[0] << 16) | (p[1] << 8) | p[2];
		return ret;
	}

    bool CLBuffer::GetBuffer(int pos, int nReadSize, CLBuffer* pBuffer)
	{
		if (pos > DataSize() || nReadSize > DataSize() - pos)
			return false;
		pBuffer->Write(Begin() + pos, nReadSize);
		return true;
	}

    std::string CLBuffer::GetString(int pos, int nReadSize)
	{
		if (pos > DataSize() || nReadSize > DataSize() - pos)
			return "";
		std::string str((char*)Begin() + pos, nReadSize);
		return str;
	}


