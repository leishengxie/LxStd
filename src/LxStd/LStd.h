#ifndef __LSTD_FUNC_H__
#define __LSTD_FUNC_H__

#include <string>
#include <memory> // shared_ptr 
#include <vector>
#include <fstream>

#ifdef WIN32
#include <process.h>
#endif

using namespace std;

namespace lx {

}

///
/// \brief The CLStd class 封装一些常用但无法归类的函数
///
class CLStd
{

public:

    std::string cvtIntToStr(const int n);
    int convertStrToInt(char *str, int sign);
    //string formatBytes(double dByteNum, unsigned char unValidDigit);

    //判断是否全部为数字
    bool isDigit(const std::string &src);

    //判断大端小端
    bool isBigDebian();

    //用自己的方式实现strcat函数功能
    char* strcat(char *dst,const char *src);

    double random(double start, double end);


    ///
    /// \brief printArray
    /// \param aSrc //eg: int m_aConnCounters[20] = { 1, 2, 5, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 6, 5, 0, 0, 0, 0, 1 };
    /// \return
    ///
    std::string printArray(char aSrc[])
    {

        char buf[256]={0};
        int ret = 0;

        for(int i = 0; i < 20; ++i)
        {
            //ret += sprintf(buf + ret, " %d", m_aConnCounters[i]);
            // 连接数组元素
            ret += sprintf(buf + ret, "%d", aSrc[i]);
        }
        return buf; // result 12511111101116500001
    }



    string getBaseName(string fileName);


    // 打印十六进制数据
    void public_print_hex(unsigned char *buff, unsigned int buff_len);

    static bool saveFileData(string filePath, char* fileData);

    string& replace_all_distinct(string& str, const string& old_value, const string& new_value);


    string& replace_all(string& str, const string& old_value, const string& new_value);

    bool checkIsStr(string strA, string strB);

    string subCString(std::string all, string a, string b);

    string& replace_all_distinct_list(string& str, string old_vlaue_Arr[], int num, const string& new_value);

    string replaceHTML(string str);
    //字符串分割函数
    std::vector<std::string> split(std::string str, std::string pattern);

//    二进制 Binary system
//    八进制 Octal number system
//    十进制 Decimal system
//    十六进制 Hexadecimal
    ///
    /// \brief 数值转16进制字符，eg: 10 --> A   主要应用'A', '0'的ASCII值
    /// \param x 数值
    /// \return
    ///
    unsigned char toHex(const unsigned char &x)
    {
        return x > 9 ? x - 10 + 'A' : x + '0';
    }

    // 16进制字符转数值
    unsigned char fromHex(const unsigned char &x)
    {
        return isdigit(x) ? x - '0' : x - 'A' + 10;
    }

    string urlEncode(const char *sIn);

    string urlDecode(const char *sIn);
}; // end namespace lstd


#endif //__LSTD_FUNC_H__
