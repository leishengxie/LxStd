#include "LCharacterEncodingUtil.h"
#include <QTextCodec>
#include <QFile>
#include <QLabel>
#include <QtDebug>

///////////////////////////////////////////// 相关概念 /////////////////////////////////////////////////
///1.字符
/// 字符(Character)是各种文字和符号的总称，包括各国家文字、标点符号、图形符号、数字等。

///2.字符集
/// 字符集(Character set)是多个字符的集合，字符集种类较多，每个字符集包含的字符个数不同。
/*
 * 常用字符集:ASCII字符集、GB2312字符集、GBK字符集、 USC-3字符集、Unicode字符集等。
 *
gb18030字符集兼容了gbk字符集，以两个字节表示一个文字。windows系统可能使用的就是这两种的一种。
unicode字符集以2个或以上的字节表示一个汉字。

UCS通用字符集（Universal Character Set, UCS）是由ISO制定的ISO 10646（或称ISO/IEC 10646）标准所定义的标准字符集。UCS-2用两个字节编码，UCS-4用4个字节编码。

*/

///3.字符编码
/// 字符编码（英语：Character encoding）也称字集码，是把字符集中的字符编码为指定集合中某一对象（例如：比特模式、自然数序列、8位组或者电脉冲）
/// ，以便文本在计算机中存储和通过通信网络的传递。
/*
 * 常用字符编码: ASCII编码、GB2312编码、GBK编码、UFT-8编码等字符编码。
 *
UTF编码：

UTF-8：UTF-8（8-bit Unicode Transformation Format）是一种针对Unicode的可变长度字符编码，又称万国码。UTF-8用1到6个字节编码UNICODE字符。
用在网页上可以同一页面显示中文简体繁体及其它语言（如英文，日文，韩文）。

UTF-16

UTF-32：UTF-32 (或 UCS-4)是一种将Unicode字符编码的协定，对每一个Unicode码位使用恰好32位元。
虽然每一个码位使用固定长定的字节看似方便，它并不如其它Unicode编码使用得广泛。

MBCS编码
为了扩充ASCII编码，以用于显示本国的语言，不同的国家和地区制定了不同的标准，由此产生了 GB2312, BIG5, JIS 等各自的编码标准。
这些使用 2 个字节来代表一个字符的各种汉字延伸编码方式，称为 ANSI 编码，又称为"MBCS（Muilti-Bytes Charecter Set，多字节字符集）"。
在简体中文系统下，ANSI 编码代表 GB2312 编码。所以在中文 windows下要转码成gb2312,gbk只需要把文本保存为ANSI 编码即可。

ISO-8859-1编码是单字节编码，向下兼容ASCII，其编码范围是0x00-0xFF。亦称为Latin1。

base64编码
有的电子邮件系统(比如国外信箱)不支持非英文字母(比如汉字)传输，这是历史原因造成的(认为只有美国会使用电子邮件?)。
因为一个英文字母使用ASCII编码来存储，占存储器的1个字节(8位)，实际上只用了7位2进制来存储，第一位并没有使用，设置为0，
所以，这样的系统认为凡是第一位是1的字节都是错误的。而有的编码方案(比如GB2312)不但使用多个字节编码一个字符，并且第一位经常是1，
于是邮件系统就把1换成0，这样收到邮件的人就会发现邮件乱码。
为了能让邮件系统正常的收发信件，就需要把由其他编码存储的符号转换成ASCII码来传输。
比如，在一端发送GB2312编码－>根据Base64规则－>转换成ASCII码，接收端收到ASCII码－>根据Base64规则－>还原到GB2312编码。
 */

///4.字节
///弄清字符与字节的概念很重要



/// Qt中
/*
 *
 * 典型例子
QString strHello="您好";
strHello.toLatin1(); //ISO-8859-1编码是单字节编码，向下兼容ASCII，其编码范围是0x00-0xFF。亦称为Latin1。 "汉字"不在latin1字符集中，所以结果无意义
strHello.toLocal8Bit(); //返回windows操作系统设置的字符集gb18030的编码
strHello.toUcs4(); //返回ucs4编码组成的QVector，一个汉字占用4字节
strHello.toUtf8(); //返回utf8编码的一串数字
*/

void test1()
{
    // QByteArray可以存储所有qt支持的字符集
    QTextCodec *gbk = QTextCodec::codecForName("gbk"); //定义局部编码
    QTextCodec *utf8 = QTextCodec::codecForName("utf-8");

    QFile file("test.txt"); //包含中文的文本，文本保存格式为utf-8
    file.open(QIODevice::ReadOnly);
    QByteArray readByte = file.readAll();
    QString strUniCode = utf8->toUnicode(readByte.data()); //utf-8 --> Unicode
    file.close();
    QString strUtf8 = QObject::trUtf8(readByte);    //utf-8
    QString strGBK = QString::fromLocal8Bit(gbk->fromUnicode(strUniCode));         // Unicode --> gbk

    //分别打印字符长度与字节长度
    qDebug() << "utf8:" << strUniCode << "  字符长度:" << strUniCode.length() << "  字节长度:" << strlen(strUniCode.toUtf8().data());
    qDebug() << "gbk:" << strGBK << "  字符长度:" << strGBK.length() << "  字节长度:" << strlen(strGBK.toLocal8Bit().data());
    qDebug() << "utf8:" << strUtf8 << "  字符长度:" << strUtf8.length() << "  字节长度:" << strlen(strUtf8.toUtf8().data());
    qDebug() << "\n";

}

CLCharacterEncodingUtil::CLCharacterEncodingUtil()
{

}
