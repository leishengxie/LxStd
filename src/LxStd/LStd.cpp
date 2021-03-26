#ifndef WIN32
#include "regex.h"
#else
#include <regex>
#endif // !WIN32

#pragma warning (disable:4996)

#include <assert.h>
#include <stdarg.h>
#include "LStd.h"






// 生成一个随机数
double CLStd::random(double start, double end)
{
    #ifdef WIN32
    return start + (end - start)*rand() / (RAND_MAX + 1.0);
#else
    return 0;
#endif
}


///
/// \brief CLStd::getBaseName 去除文件后缀 只留文件名
/// \param fileName
/// \return
///
string CLStd::getBaseName(string fileName)
{
    int pos = fileName.rfind(".");
    if (pos > 0)
        return fileName.substr(0, pos);
    else
        return fileName;
}

/***********过滤字母数字，128-256******/
char * print16(char *str)
{
	int strLength = strlen(str);
	char buf16[16] = { 0 };
	char *str16;
	int j = 0;

	for (int i = 0; i < strLength; i++)
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
		{
			buf16[j] = str[i];
			j++;
		}
	}
	str16 = new char[strlen(buf16) + 1];
	strcpy(str16, buf16);
	return str16;

}

/************************************************************************/
/*把十六进制字符串ptr 转换成十进制数                                     */
/************************************************************************/
//function 1
int ChangeNum1(char *str, int length)
{
	char  revstr[16] = { 0 };  //根据十六进制字符串的长度，这里注意数组不要越界
	int   num[16] = { 0 };
	int   count = 1;
	int   iResult = 0;
	strcpy(revstr, str);
	for (int i = length - 1; i >= 0; i--)
	{
		if ((revstr[i] >= '0') && (revstr[i] <= '9'))
			num[i] = revstr[i] - 48;//字符0的ASCII值为48
		else if ((revstr[i] >= 'a') && (revstr[i] <= 'f'))
			num[i] = revstr[i] - 'a' + 10;
		else if ((revstr[i] >= 'A') && (revstr[i] <= 'F'))
			num[i] = revstr[i] - 'A' + 10;
		else
			num[i] = 0;
		iResult = iResult + num[i] * count;
		count = count * 16;//十六进制(如果是八进制就在这里乘以8)    
	}
	return iResult;

}





/*
1. 什么是大端,什么是小端:

所谓的大端模式，是指数据的低位保存在内存的高地址中，而数据的高位，保存在内存的低地址中；

所谓的小端模式，是指数据的低位保存在内存的低地址中，而数据的高位保存在内存的高地址中。

2.为什么会有大小端:

为什么会有大小端模式之分呢？这是因为在计算机系统中，我们是以字节为单位的，每个地址单元都对应着一个字节，一个字节为8bit。但是在C语言中除了8bit的char之外，
还有16bit的short型，32bit的long型（要看具体的编译器），另外，对于位数大于8位的处理器，例如16位或者32位的处理器，由于寄存器宽度大于一个字节，
那么必然存在着一个如果将多个字节安排的问题。因此就导致了大端存储模式和小端存储模式。例如一个16bit的short型x，在内存中的地址为0x0010，x的值为0x1122，
那么0x11为高字节，0x22为低字节。对于大端模式，就将0x11放在低地址中，即0x0010中，0x22放在高地址中，即0x0011中。小端模式，刚好相反。
我们常用的X86结构是小端模式，而KEIL C51则为大端模式。很多的ARM，DSP都为小端模式。有些ARM处理器还可以由硬件来选择是大端模式还是小端模式。
*/

/*
ntel的80x86系列芯片是唯一还在坚持使用小端的芯片，ARM芯片默认采用小端，但可以切换为大端；而MIPS等芯片要么采用全部大端的方式储存，
要么提供选项支持大端——可以在大小端之间切换。另外，对于大小端的处理也和编译器的实现有关，
在C语言中，默认是小端（但在一些对于单片机的实现中却是基于大端，比如Keil 51C），Java是平台无关的，默认是大端。在网络上传输数据普遍采用的都是大端
*/

bool CLStd::isBigDebian()
{
	short int x;
	char x0, x1;
	x = 0x1122;
	x0 = ((char *)&x)[0];  //低地址单元
	x1 = ((char *)&x)[1];  //高地址单元
	printf("x0=0x%x,x1=0x%x", x0, x1);// 若x0=0x11,则是大端; 若x0=0x22,则是小端......
	if (x0 == 0x11)
	{
		return true;
	}
	return false;
}


/*******************************************
 *	打印十六进制数据
 *	@buff: 存放十六进制数据的缓存
 *  @buff_len: 缓存大小
********************************************/
void CLStd::public_print_hex(unsigned char *buff, unsigned int buff_len)
{
    unsigned int index = 0;
    unsigned char tmp = 0;

    printf("\nbuff_len is %d, buff is\n", buff_len);
    for (index=0; index<buff_len; index++)
    {
        // 高4位
        tmp = buff[index];
        tmp &= 0xf0;
        tmp >>= 4;
        printf(" %x", tmp);

        // 低4位
        tmp = buff[index];
        tmp &= 0x0f;
        printf("%x", tmp);
    }
    printf("\nbuff over\n");
}


///
/// \brief CLStd::saveFileData 写入文件内容 不存在则创建  覆盖写入
/// \param filePath 文件路径
/// \param fileData 文件内容
/// \return
///
bool CLStd::saveFileData(string filePath, char *fileData)
{
    ofstream outfile(filePath, ios::out);//ios::app表示在原文件末尾追加
    outfile.write(fileData, strlen(fileData));
    outfile.close();
    return true;
}

/**
* 说明：字符串替换（不循环重复替换）
* 参数：1总字符串 2要替换的字符 3替换成的字符
* 返回：替换后的字符串
*/
string &CLStd::replace_all_distinct(string &str, const string &old_value, const string &new_value)
{
    for (string::size_type pos(0); pos != string::npos; pos += new_value.length()){
        if ((pos = str.find(old_value, pos)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else  break;
    }
    return   str;
}

/**
* 说明：字符串替换（循环重复替换）
* 参数：1总字符串 2要替换的字符 3替换成的字符
* 返回：替换后的字符串
*/
string &CLStd::replace_all(string &str, const string &old_value, const string &new_value)
{
    while (true) {
        string::size_type pos(0);
        if ((pos = str.find(old_value)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else break;
    }
    return str;
}

/**
* 说明：判断是否包含子串（A中是否包含B）
* 参数：A总字符串  B子串
* 返回：true包含 /false不包含
*/
bool CLStd::checkIsStr(string strA, string strB)
{
    string::size_type idx = strA.find(strB);
    if (idx != string::npos)
    {
        return true;
    }
    else {
        return false;
    }
}

/**
* 说明：截取字符串（从A到B中间的字符串）
* 参数：all总字符串  a开始字符串  b结束字符串
* 返回：处理后的字符串
*/
string CLStd::subCString(string all, string a, string b)
{
    int ix = all.find(a);
    int iy = all.find(b);
    ix += strlen(a.c_str());
    iy = iy - ix;
    all = all.substr(ix, iy);
    return all;
}

/**
* 说明：多字符串替换（不循环重复替换）
* 参数：str总字符串  old_vlaue_Arr要替换的字符（string[]类型）num要替换字符串的个数  new_value替换成的字符
* 返回：替换后的字符串
*/
string &CLStd::replace_all_distinct_list(string &str, string old_vlaue_Arr[], int num, const string &new_value)
{
    for (int i = 0; i < num; i++) {
        const string& old_value = old_vlaue_Arr[i];
        for (string::size_type pos(0); pos != string::npos; pos += new_value.length()){
            if ((pos = str.find(old_value, pos)) != string::npos)
                str.replace(pos, old_value.length(), new_value);
            else  break;
        }
    }
    return   str;
}

/**
* 说明：将字符串中的html标签转义
* 参数：需要转义的字符串
* 返回：处理后的字符串
*/
string CLStd::replaceHTML(string str)
{
    string strAryy[4]{ "</div>", "<em>", "</em>", "</p>"};
    string replStr = replace_all_distinct_list(str, strAryy, 4, "");
    replStr = replace_all_distinct(replStr, "&nbsp;", " ");
    replStr = replace_all_distinct(replStr, "<br />", "\r\n");
    return replStr.c_str();
}

std::vector<string> CLStd::split(string str, string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    int size = str.size();

    for (int i = 0; i<size; i++)
    {
        pos = str.find(pattern, i);
        if (pos<size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

/**
* 说明：中文转为浏览器识别的特殊编码
* 参数：带转换字符串
* 返回：处理后的字符串
*/
string CLStd::urlEncode(const char *sIn)
{
    string sOut;
    for (size_t ix = 0; ix < strlen(sIn); ix++)
    {
        unsigned char buf[4];
        memset(buf, 0, 4);
        if (isalnum((unsigned char)sIn[ix]))
        {
            buf[0] = sIn[ix];
        }
        else
        {
            buf[0] = '%';
            buf[1] = toHex((unsigned char)sIn[ix] >> 4);
            buf[2] = toHex((unsigned char)sIn[ix] % 16);
        }
        sOut += (char *)buf;
    }
    return sOut;
}

/**
* 说明：浏览器识别的特殊编码转为中文
* 参数：带转换字符串
* 返回：处理后的字符串
*/
string CLStd::urlDecode(const char *sIn)
{
    string sOut;
    for (size_t ix = 0; ix < strlen(sIn); ix++)
    {
        unsigned char ch = 0;
        if (sIn[ix] == '%')
        {
            ch = (fromHex(sIn[ix + 1]) << 4);
            ch |= fromHex(sIn[ix + 2]);
            ix += 2;
        }
        else if (sIn[ix] == '+')
        {
            ch = ' ';
        }
        else
        {
            ch = sIn[ix];
        }
        sOut += (char)ch;
    }

    return sOut;
}




string CLStd::cvtIntToStr(const int n)
{
    // 方法一， 本方法需要知道结果字节长度大小， int类型格式化成十进制后， 其字节大小不会超过32个字节
        char ch[32];
        sprintf(ch, "%d", n);
        std::string szResult = ch;
        return szResult;


}


int CLStd::convertStrToInt(char *str, int sign)
{
    int nResult = 0;
    int nStrLength = strlen(str);

    for (int i = 0; i < nStrLength; ++i)
    {
        int iAScill = str[i];
        if (iAScill >= '0' && iAScill <= '9')
        {
            nResult = nResult*sign + iAScill - '0';
        }
        if ((iAScill >= 'A' && iAScill <= 'Z'))
        {
            nResult = nResult*sign + iAScill - 'A' + 10;
        }
        if (iAScill >= 'a' && iAScill <= 'z')
        {
            nResult = nResult*sign + iAScill - 'a' + 10;
        }
    }
    return nResult;
}

//string CLStd::formatBytes(double dByteNum, unsigned char unValidDigit)
//{
//    string strUnit = "B";
//    double dNumber = dByteNum;
//    double dDivisor = 1024;
//    if (dNumber >= dDivisor)
//    {
//        strUnit = "KB";
//        dNumber = dNumber / dDivisor;
//    }
//    if (dNumber >= dDivisor)
//    {
//        strUnit = "MB";
//        dNumber = dNumber / dDivisor;
//    }
//    if (dNumber >= dDivisor)
//    {
//        strUnit = "GB";
//        dNumber = dNumber / dDivisor;
//    }
//    if (dNumber >= dDivisor)
//    {
//        strUnit = "TB";
//        dNumber = dNumber / dDivisor;
//    }

//    return CLStd::format("%f%s", dNumber, strUnit.c_str());
//}

bool CLStd::isDigit(const string &src)
{
    if (src.empty()) return false;

    for (int i = 0; i < (int)src.length(); i++)
    {
        char ch = src[i];
        if (ch < '0' || ch > '9')
            return false;
    }

    return true;
}

char *CLStd::strcat(char *dst, const char *src)
{
    char *p=dst;  //下面的操作会改变目的指针指向，先定义一个指针记录dst
    while(*p!='\0')p++;
    while(*src != '\0')*p++=*src++;
     *p='\0';
    return dst;
    //
}
