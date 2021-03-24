
#pragma once

#define AES_BLOCK_SIZE 16

/*
AES算法（即 Rijndael 算法）是一个对称分组密码算法。数据分组长度必须是 128 bits，使用的密钥长度为 128，192 或 256 bits。
对于三种不同密钥长度的 AES 算法，分别称为“AES-128”、“AES-192”、“AES-256”。（Rijndael 的设计还可以处理其它的分组长度和密钥长度，
但 AES 标准中没有采用）
*/
///
/// \brief The CLAes class AES的ECB加解密方法
///
class CLAes
{
public:
    CLAes();
    CLAes(unsigned char* key);
    virtual ~CLAes();


    ///
    /// \brief cipher 加密
    /// \param input 明文 需要填充为16字节的倍数
    /// \param length 明文的长度，如果为0则当做字符串处理，则需要获取明文的真实长度
    /// \return 密文 不能直接使用字符串输出，因为加密后的数组内容可能有'\0'，字符串会被截断。
    ///
    void* cipher(void* input, int length=0);

    ///
    /// \brief InvCipher 解密
    /// \param input 必须传入，必须是16的整数倍
    /// \param length 必须传入，必须是16的整数倍
    /// \return 明文
    ///
    void* invCipher(void* input, int length);




private:
    ///
    /// \brief cipher 加密
    /// \param input 大小必须是16字节
    /// \return
    ///
    unsigned char* cipher(unsigned char* input);

    unsigned char* invCipher(unsigned char* input);


	void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);
    unsigned char GF28Multi(unsigned char multiple, unsigned char b);

	void SubBytes(unsigned char state[][4]);
    void shiftRows(unsigned char state[][4]);
    void mixColumns(unsigned char state[][4]);
	void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

	void InvSubBytes(unsigned char state[][4]);
	void InvShiftRows(unsigned char state[][4]);
	void InvMixColumns(unsigned char state[][4]);

private:
    unsigned char m_aSbox[256];
    unsigned char InvSbox[256];
    unsigned char w[11][4][4];

    // cbc模式加密需要的向量
    unsigned char m_aVector[AES_BLOCK_SIZE];
};


