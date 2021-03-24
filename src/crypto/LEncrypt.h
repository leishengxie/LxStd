#pragma once


///
/// \brief The LEncrypt class 自定义的一些简单古老的加密方法
///
class LEncrypt
{
public:
    LEncrypt();
    ~LEncrypt();

    static void makeCode(char* pstr, int* pkey);
    static void cuteCode(char* pstr, int* pkey);

};


