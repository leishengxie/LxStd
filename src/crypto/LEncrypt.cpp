#include "LEncrypt.h"
#include <string.h>

//单个字符异或运算
char makecodeChar(char c, int key){
    return c = c^key;
}
//单个字符解密
char cutcodeChar(char c, int key){
    return c^key;
}

LEncrypt::LEncrypt()
{
}


LEncrypt::~LEncrypt()
{
}

///
/// \brief LEncrypt::makeCode 加密
/// \param pstr
/// \param pkey
///
void LEncrypt::makeCode(char *pstr, int *pkey)
{
    int len = strlen(pstr);//获取长度
    for (int i = 0; i < len; i++)
        *(pstr + i) = makecodeChar(*(pstr + i), pkey[i % 5]);
}

///
/// \brief LEncrypt::cuteCode 解密
/// \param pstr
/// \param pkey
///
void LEncrypt::cuteCode(char *pstr, int *pkey)
{
    int len = strlen(pstr);
    for (int i = 0; i < len; i++)
        *(pstr + i) = cutcodeChar(*(pstr + i), pkey[i % 5]);
}

