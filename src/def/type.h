/***********
 *
 * 宏-类型
 *
 *
 */
#pragma once

#include <stdint.h>
#include <iostream>

//1.1    编译器运行操作系统
//
//l        WINDOWS : _WIN32、WIN32;
//
//l        UNIX / LINUX:  unix、__unix、__unix__;
//
//l        SunOS / SOLARIS: __SVR4、__svr4__、sun、__sun、__sun__、sparc、__sparc、__sparc__;
//
//l        HPUX : __hppa、__hppa__、__hpux、__hpux__、_HPUX_SOURCE;
//
//l        AIX : _AIX、_AIX32、_AIX41、_AIX43、_AIX51、_AIX52;
//
//l        LINUX : linux、__linux、__linux__、__gnu_linux__;
//
//l        CPU : __x86_64、__x86_64__(Intel); __amd64、__amd64__(AMD); sparc、  __sparc、__sparc__;



//[unsigned] char
//[unsigned] short
//[unsigned] int
//[unsigned] long
//[unsigned] long int
//[unsigned] long long
//float
//double
//long double
//wchar_t(c99)
//bool(c++增加的数据类型, c中没有bool类型)

//long long定义方式可以用于gcc / g++，不受平台限制，但不能用于VC6.0。
//__int64是Win32平台编译器64位长整型的定义方式，不能用于Linux。

//vs 32bit: sizeof(pointer) == 4 bytes
//vs 64bit: sizeof(pointer) == 8 bytes



//////////////////////////////////////////////////////////////////////////
// 小写风格
typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;
typedef long long			int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef unsigned char		byte;
typedef unsigned char       uchar;
typedef unsigned int		uint;
typedef unsigned short		word;
typedef unsigned int		dword;
typedef long long			longlong;

typedef wchar_t				wchar;

///////////////////////////////////////////////////////////////////////////////
// 大写风格
typedef unsigned char       UCHAR;
typedef char                CHAR;
typedef UCHAR               U8;
typedef CHAR                S8;
typedef unsigned short      U16;
typedef short               S16;
typedef unsigned int        U32;
typedef int                 S32;
typedef unsigned long       U64;
typedef long                S64;
typedef UCHAR               Status;
typedef UCHAR               BOOL;
typedef float               FLOAT;

typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef unsigned int		UINT;
typedef unsigned int		DWORD;

//如果使用宽字节
#ifdef  _UNICODE
typedef std::wstring	tstring;
typedef wchar			tchar;
#else
typedef std::string		tstring;
typedef char			tchar;
#endif

#ifdef _WIN32
#define LLSTRING "%I64d"
#else
#define LLSTRING "%lld"
#endif
