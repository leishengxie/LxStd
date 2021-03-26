#include <QString>
#include <QtTest>
#include <QtDebug>
#include "LAesEx.h"
#include "Base64.h"
#include "LMd5.h"
#include "LStd.h"


/// ---   结果可视化-AutoTest插件 --------
//每一个私有槽都是一个测试函数，但有4种私有槽不能作为测试函数，它们由测试框架执行，可为整个测试程序或当前测试函数进行初始化和清除操作。
//initTestCase()：在第一个测试函数执行前调用。
//cleanupTestCase()：在最后一个测试函数执行后调用。
//init()：在每一个测试函数执行前调用。
//cleanup()：在每一个测试函数执行后调用。
//如果initTestCase()函数执行失败，任何测试函数都不会执行。如果init()函数执行失败，紧随其后的测试函数不会被执行，测试会继续处理下一个测试函数。

///
/// \brief The LibUnitTestTest class
///
class LibUnitTestTest : public QObject
{
    Q_OBJECT

public:
    LibUnitTestTest();

private Q_SLOTS:
    void testCase1();
    void testAesBcb();
    void testMD5();
    void testLstdFunc();

};


LibUnitTestTest::LibUnitTestTest()
{

}


void LibUnitTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

void LibUnitTestTest::testAesBcb()
{
    string strSrc = "leisx12345678911";
    const char g_key[17] = "asdfwetyhjuytrfd";
    const char g_iv[17] =
    {
        0x30, 0x31, 0x30, 0x32, 0x30, 0x33, 0x30, 0x34,
        0x30, 0x35, 0x30, 0x36, 0x30, 0x37, 0x30, 0x38
    };

    /// ----- 加密 ------
    size_t length = strSrc.length();
    int block_num = length / BLOCK_SIZE + 1;
    //明文
    char* szDataIn = new char[block_num * BLOCK_SIZE + 1];
    memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);
    strcpy(szDataIn, strSrc.c_str());

    //进行PKCS7Padding填充。
    int k = length % BLOCK_SIZE;
    int j = length / BLOCK_SIZE;
    int padding = BLOCK_SIZE - k;
    for (int i = 0; i < padding; i++)
    {
        szDataIn[j * BLOCK_SIZE + k + i] = padding;
    }
    szDataIn[block_num * BLOCK_SIZE] = '\0';

    //加密后的密文
    char *szDataOut = new char[block_num * BLOCK_SIZE + 1];
    memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);

    //进行进行AES的CBC模式加密
    CLAesEx aes;
    aes.makeKey(g_key, g_iv, 16, 16);
    aes.encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, CLAesEx::CBC);
    string strEncryptResult = base64_encode((unsigned char*)szDataOut,
        block_num * BLOCK_SIZE);
    delete[] szDataIn;
    delete[] szDataOut;

    qDebug() << "finish encrypt:" << strEncryptResult.c_str();


    /// ---- 解密 --- ///
    /// \brief strData
    /*
    string strData = base64_decode(strEncryptResult);
    size_t length = strData.length();
    //密文
    char *szDataIn = new char[length + 1];
    memcpy(szDataIn, strData.c_str(), length + 1);
    //明文
    char *szDataOut = new char[length + 1];
    memcpy(szDataOut, strData.c_str(), length + 1);

    //进行AES的CBC模式解密
    CLAesEx aes;
    aes.makeKey(g_key, g_iv, 16, 16);
    aes.decrypt(szDataIn, szDataOut, length, AES::CBC);

    //去PKCS7Padding填充
    if (0x00 < szDataOut[length - 1] <= 0x16)
    {
        int tmp = szDataOut[length - 1];
        for (int i = length - 1; i >= length - tmp; i--)
        {
            if (szDataOut[i] != tmp)
            {
                memset(szDataOut, 0, length);
                cout << "去填充失败！解密出错！！" << endl;
                break;
            }
            else
                szDataOut[i] = 0;
        }
    }
    string strDest(szDataOut);
    delete[] szDataIn;
    delete[] szDataOut;
    return strDest;
    */
}

void LibUnitTestTest::testMD5()
{
    CLMd5 md5;
    md5.update("abc");
    qDebug() << "finish md5:" << md5.toString().c_str();

    ifstream in;
    in.open("D:\\test.txt");
    md5.reset();
    md5.update(in);
    qDebug() << "finish md5:" << md5.toString().c_str();
}

void LibUnitTestTest::testLstdFunc()
{
    //lstd::saveFileData("hello.txt", "1234443");
}








/// must
///
QTEST_APPLESS_MAIN(LibUnitTestTest)


///must
#include "tst_libunittesttest.moc"
