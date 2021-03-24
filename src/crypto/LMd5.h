
#ifndef _L_MD5_H
#define _L_MD5_H

#include <string>
#include <fstream>
#include "type.h"

using std::string;
using std::ifstream;

///
/// \brief The CLMd5 class 不懂的百度MD5，有现成的代码
///
class CLMd5
{
public:
    CLMd5();
    CLMd5(const void* input, size_t length);
    CLMd5(const string & str);
    CLMd5(ifstream & in);
    void update(const void* input, size_t length);
    void update(const string & str);
    void update(ifstream & in);
    const byte* digest();
    string toString();
    void reset();

private:
    void update(const byte* input, size_t length);
    void final();
    void transform(const byte block[64]);
    void encode(const uint32* input, byte* output, size_t length);
    void decode(const byte* input, uint32* output, size_t length);
    string bytesToHexString(const byte* input, size_t length);

    /* class uncopyable */
    CLMd5(const CLMd5 &);
    CLMd5 & operator=(const CLMd5 &);

private:
    uint32 _state[4]; // MD5运算要用到一个128位的MD5缓存器，用来保存中间变量和最终结果。该缓存器又可看成是4个32位的寄存器A、B、C、D
    uint32 _count[2]; /* number of bits, modulo 2^64 (low-order word first) 记录原始信息长度 _count[0]为数据低word*/
    byte _buffer[64]; /* input buffer */

    byte _digest[16]; /* message digest */
    bool _finished; //calculate finished ?

    static const byte PADDING[64]; /* padding for calculate */
    static const char HEX[16];
    enum { BUFFER_SIZE = 1024 };
};

#endif /*_L_MD5_H*/


