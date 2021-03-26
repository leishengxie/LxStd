#include "LRegExpUtil.h"


/****
表达式	说明
\r, \n	代表回车和换行符
\t	制表符
\\	代表 "\" 本身
\^	匹配 ^ 符号本身
\$	匹配 $ 符号本身

元字符	说明
.	匹配除了换行符以外的任意字符
\w	匹配字母、数字、下划线、汉字
\s	匹配任意的空白符
\b	单词的开始或结尾
\~	匹配字符串的开始
$	匹配字符串的结束

表达式	说明
[ ]	包含一系列字符
[^ ]	包含之外一系列字符

{n}	表达式重复n次，比如："\w{2}" 相当于 "\w\w"；"a{5}" 相当于 "aaaaa"
{m,n}	表达式至少重复m次，最多重复n次，比如："ba{1,3}"可以匹配 "ba"或"baa"或"baaa
{m,}	表达式至少重复m次，比如："\w\d{2,}"可以匹配 "a12","_456","M12344"...
?	匹配表达式0次或者1次，相当于 {0,1}，比如："a[cd]?"可以匹配 "a","ac","ad"
+	表达式至少出现1次，相当于 {1,}，比如："a+b"可以匹配 "ab","aab","aaab"...
*	表达式不出现或出现任意次，相当于 {0,}，比如："\^*b"可以匹配 "b","^^^b"...


例子	 解释
[abc]	方括号中间是几个字母，表示a,b,c这三个单独的字符
[^abc]	除了a,b,c以外的字符
[a-z]	横杠表示范围，匹配a到z之间(包括a和z)的所有单个字符
[a-zA-Z]	a到z、A到Z的所有单个字符
^	在一行最前
$	在一行的最后
\s	匹配任意空白字符
\S	匹配任意非空白的字符
\d	任意数字
\D	任意非数字
\w	任意单字字符（字母、数字或下划线）
\W	任意非单字字符
(a|b)	a或b
a?	?代表0个或1个
a*	*代表0个或1个或多个
a+	+代表1个或多个
a{3}	3个a
a{3,}	3个或大于3个a
a{3,6}	a的个数在3和6之间(包括3和6)



***********/
/*

//用正则表达式验证文本有效性
//你可以使用QRegExp::exactMatch来判断一个字符串是否符合一个pattern。
void testRegexMatch()
{
    QString pattern(".*=.*");
    QRegExp rx(pattern);

    bool match = rx.exactMatch("a=3");
    qDebug() << match;                      // True

    match = rx.exactMatch("a/2");
    qDebug() << match;                      // False
}

//用正则表达式提取数据
//你可以利用利用正则表达式从一个字符串里提取特定的字段或数据。例如，你可以用以下代码从"a=100"里提取"a"和"100"。
void testRegexCapture()
{
    QString pattern("(.*)=(.*)");
    QRegExp rx(pattern);

    QString str("a=100");
    int pos = str.indexOf(rx);              // 0, position of the first match.
                                            // Returns -1 if str is not found.
                                            // You can also use rx.indexIn(str);
    qDebug() << pos;
    if ( pos >= 0 )
    {
        qDebug() << rx.matchedLength();     // 5, length of the last matched string
                                            // or -1 if there was no match
        qDebug() << rx.capturedTexts();     // QStringList("a=100", "a", "100"),
                                            //   0: text matching pattern
                                            //   1: text captured by the 1st ()
                                            //   2: text captured by the 2nd ()

        qDebug() << rx.cap(0);              // a=100, text matching pattern //cap--captured 捕获 cap(0)捕获全部
        qDebug() << rx.cap(1);              // a, text captured by the nth () 这里的得到了a
        qDebug() << rx.cap(2);              // 100, 这里的得到了100

        qDebug() << rx.pos(0);              // 0, position of the nth captured text
        qDebug() << rx.pos(1);              // 0
        qDebug() << rx.pos(2);              // 2
    }
}

//用正则表达式修改文本
void testModfy()
{
    // 你可以把字符串中匹配的字符串替换成"一般字符串"
    QString s = "a=100";
        s.replace(QRegExp("(.*)="), "b=");
        qDebug() << s;                          // b=100
        //或是把字符串中匹配的字符串替换"提取的字符串"
        QString s = "a=100";
            s.replace(QRegExp("(.*)=(.*)"), "\\1\\2=\\2");  // \1 is rx.cap(1), \2 is rx.cap(2)
            qDebug() << s;                                  // a100=100
            //把正则表达式转换成C/C++ string的小工具
            //没有Python的"""或是C#的@。标准的正则表达式因为出现一些特殊字符，在C/C++代码里使用时，必须进行转换。例如："(\S+)\s*=\s*(\S*)"必须转换成"(\\S+)\\s*=\\s*(\\S*)"

            //Qt的SDK里包含一个很帮的GUI工具，可以方便我们进行这类转换并测试你的表达式。在Linux下，它的路径是/usr/local/Trolltech/Qt-4.5.3/examples/tools/regexp/regexp
}

// qt帮助文档里的例子说明
void qtHelp()
{
    // --1
    QRegExp rx("(\\d+)"); //匹配至少一个数字
    QString str = "Offsets: 12 14 99 231 7";
    QStringList list;
    int pos = 0;

    while ((pos = rx.indexIn(str, pos)) != -1) {
        list << rx.cap(1); //获取匹配的第一个值
        pos += rx.matchedLength();
    }
    // list: ["12", "14", "99", "231", "7"]

    // --2
    rx = QRegExp("*.txt");
    rx.setPatternSyntax(QRegExp::Wildcard);
    rx.exactMatch("README.txt");        // returns true //exact 准确的，精密的；精确的
    rx.exactMatch("welcome.txt.bak");   // returns false

    // --3
    rx = QRegExp("^\\d\\d?$");    // match integers 0 to 99 // ^表示开头 $表示结束
    rx.indexIn("123");          // returns -1 (no match)
    rx.indexIn("-6");           // returns -1 (no match)
    rx.indexIn("6");            // returns 0 (matched at position 0)

    // --4
    rx = QRegExp("^\\S+$");       // match strings without whitespace
    rx.indexIn("Hello world");  // returns -1 (no match)
    rx.indexIn("This_is-OK");   // returns 0 (matched at position 0)

    // --5
    rx = QRegExp("\\b(mail|letter|correspondence)\\b"); //匹配一个单词边界，也就是指单词和空格间的位置
    rx.indexIn("I sent you an email");     // returns -1 (no match)
    rx.indexIn("Please write the letter"); // returns 17

    // --6
    rx = QRegExp("&(?!amp;)");      // match ampersands but not &amp;  //(?!) 匹配&除&amp;之外
    QString line1 = "This & that";
    line1.replace(rx, "&amp;"); // line1 == "This &amp; that"
    QString line2 = "His &amp; hers & theirs";
    line2.replace(rx, "&amp;"); // line2 == "His &amp; hers &amp; theirs"

    // --7
    str = "One Eric another Eirik, and an Ericsson. "
                  "How many Eiriks, Eric?";
    rx = QRegExp("\\b(Eric|Eirik)\\b"); // match Eric or Eirik
    int pos = 0;    // where we are in the string
    int count = 0;  // how many Eric and Eirik's we've counted
    while (pos >= 0) {
        pos = rx.indexIn(str, pos);
        if (pos >= 0) {
            ++pos;      // move along in str //pos += rx.matchedLength()
            ++count;    // count our Eric or Eirik
        }
    }

    // --8
    str = "Digia Plc\tqt.digia.com\tFinland";
    QString company, web, country;
    rx.setPattern("^([^\t]+)\t([^\t]+)\t([^\t]+)$");
    if (rx.indexIn(str) != -1) {
        company = rx.cap(1);
        web = rx.cap(2);
        country = rx.cap(3);
    }
}
*/

CLRegExpUtil::CLRegExpUtil()
{

}
