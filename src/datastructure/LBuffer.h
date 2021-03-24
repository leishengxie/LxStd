#ifndef V_NET_BUFFER_H_
#define V_NET_BUFFER_H_

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "def/type.h"

#define DEAULT_CACHE_SIZE				20 * 1024

class CLBuffer
{
public:
    CLBuffer(int nDefaultSize = DEAULT_CACHE_SIZE);
    CLBuffer(const CLBuffer & src);
    virtual ~CLBuffer();
public:
    CLBuffer & operator<<(std::string & str);
    CLBuffer & operator<<(char* str);
    unsigned char* Begin(); //began offset
    unsigned char* End(); //end offset
    void MoveEndPos(int nPos); //end offset + npos
    void MoveBeginPos(int nPos); //began offset + npos
    void Skip(int nPos);
    void SetBeginPos(int nPos);
    void SetEndPos(int nPos);
    int GetBeginPos();
    int GetEndPos();
    int DataSize(); //return m_nEndPos - m_nBeginPos;
    int FreeSize();
    int Capacity();
    bool EnsureFreeSpace(int size = DEAULT_CACHE_SIZE);
    void Clear();
    void Erase(int nPos); //?
public:
    void Write(std::string & str);
    void Write(const unsigned char* pBuf, int length);
    void WriteLine(std::string str);
    void WriteChar(unsigned char c);
    void WriteUInt16(unsigned int i);
    void WriteUInt24(unsigned int i);
    void WriteUInt32(unsigned int i);
    void WriteReverseUInt32(unsigned int i);
    void WriteInt64(int64 i);
    void WriteDouble(double d);
    void Write(CLBuffer & buffer);
    void WriteUInt32ToString(unsigned int i);
public:
    char ReadChar();
    unsigned char ReadUChar();
    int ReadInt16();
    unsigned int ReadUInt16();
    unsigned int ReadUInt24();
    int ReadInt32(); //?
    unsigned int ReadUInt32();
    unsigned int ReadReverseUInt24();
    unsigned int ReadReverseUInt32();
    double ReadDouble();
    int64 ReadInt64();
    uint64 ReadUInt64();
    std::string ReadString(int length);
    std::string ReadLine();
    bool IsFindValue(char* pValue, int nSize);
    int FindValue(char* pValue, int pos = 0);
public:
    unsigned char GetUChar(int start = 0);
    int64 GetInt64(int start = 0);
    unsigned int GetUInt32(int start = 0);
    unsigned int GetUInt16(int start = 0);
    unsigned int GetUInt24(int start = 0);
    bool GetBuffer(int pos, int nReadSize, CLBuffer* pBuffer);
    std::string GetString(int pos, int nReadSize);
private:
    int				m_nBeginPos;
    int				m_nEndPos;
    unsigned char*	m_pData;
    int				m_nBufferSize;
};


#endif // V_NET_BUFFER_H_
