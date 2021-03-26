#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T20:34:18
#
#-------------------------------------------------

QT       += core gui multimedia xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32{
    QT       += axcontainer
}

# target name, not include suffix name
TARGET = LxQt

TEMPLATE = lib
#app - create a app makefile --defult
#lib - create a lib makefile
#vcapp - create a app of Visual Studio project
#vclib - create a lib of Visual Studio project

CONFIG += c++11

#预处理程序定义
DEFINES += LX_QT

# 指明编译的目标文件的输出路径
#工程的所在目录

#DESTDIR = ../bin #编译的所在目录

CONFIG(debug, debug|release){

    # DEBUG base name add 'd' suffix
    TARGET = $$join(TARGET,,,d)

}
DESTDIR = $$PWD/lib

RC_FILE += version.rc
#warning: if not use .rc file, the dll name will rename to TARGET+major.dll
#, becase the created rc. OriginalFilename is changed to TARGET+major.dll
#VERSION = 0.1.0.0
#QMAKE_TARGET_PRODUCT = LQtTool.dll
#QMAKE_TARGET_COMPANY = Lx
#QMAKE_TARGET_DESCRIPTION = tool
## 版权信息
#QMAKE_TARGET_COPYRIGHT = Lx
## 中文（简体）
#RC_LANG = 0x0004

win32{
CONFIG(debug, debug|release) {
            #target_path = ./build_/dist
            #TARGET = LQtTool
        } else {
            #target_path = ./build_/debug
            #TARGET = LQtToold
        }
        #MOC_DIR = $$target_path/moc
        #RCC_DIR = $$target_path/rcc
        #OBJECTS_DIR = $$target_path/obj
        #DEFINES  += WIN32   #vc6,nmake不会主动包含WIN32 需要手动定add
        #system(xcopy *.h ..\include /s)

    #src_dir = $$HEADERS
    #dst_dir = $$PWD\\..\\include\\
    #dst_dir = $$DESTDIR

    #和上面的语句之间需要留一个空行，否则会出error
    #src_dir ~= s,/,\\,g
    #dst_dir ~= s,/,\\,g
    #system(xcopy $$src_dir $$dst_dir /y /s)
}

win32{
#1-在项目构建前执行命令
#    system(.\copy_head.bat)
#优化后的表达式如下，这样此命令只会在构建前执
#!build_pass:system(.\copy_head.bat)

#2-在链接前后执行，(只有在源码修改导致重新链接成目标文件时才会执
#在链接执行前执行命令cmd
#QMAKE_PRE_LINK += .\copy_head.bat
#在链接执行后执行命令cmd
#QMAKE_POST_LINK += .\copy_head.bat

#3-在构建前后插入命 使用的QMake变量是QMAKE_EXTRA_TARGETS和PRE_TARGETDEPENS变量
#eg:
# 构造自定义生成目标对象
#mybuild.target=pre_build_cmds
#win32{
#mybuild.commands=$$PWD/UpdatePluginLib.cmd
#}else{
#}
# 加入到自定义目标对象列表#QMAKE_EXTRA_TARGETS += mybuild

# 加入到构建依赖列表最前面，会最先被执行，这里必须写目标对象名称，不能是mybuild
#PRE_TARGETDEPS += pre_build_cmds
}

contains(QMAKE_COMPILER, gcc) { #由于使用mingw应该用sh
    message("qmake compiler is gcc")
}

contains(QMAKE_COMPILER, msvc) {
    message("qmake compiler is msvc")
    }

contains(DEFINES, USE_QT4){
    message("use qt4")
}else{
    message("use qt5")
}

# 头文件搜索路径INCLUDEPATH:

#qmake将会退exit
#count( DEFINES, 5 ) {        CONFIG += debug    }error( "qmake exit" )

#
#exists( /local/qt/qmake/main.cpp ) {        SOURCES += main.cpp    }message( "local/qt/qmake/main.cpp exists_" )
#!exists( main.cpp ) { error( "no main.cpp file found" ) }

#
#isEmpty( CONFIG ) {        CONFIG += qt warn_on debug    }message( "CONFIG_ is empty" )

#
#system( ls /bin ) {        SOURCES += bin/main.cpp        HEADERS += bin/main.h    }

#
#infile( filename, var, val )

#本库头文件包含路径
#INCLUDEPATH += $$PWD\src
#依赖库的头文件包含路径
#INCLUDEPATH += $$PWD\..\LStdTool\include
#INCLUDEPATH += $$PWD\..\LStdTool\src

#程序编译时依赖的相关路径
#DEPENDPATH += $$PWD\src
#程序编译时依赖的相关路径
#DEPENDPATH += $$PWD\..\LStdTool\include
#DEPENDPATH += $$PWD\..\LStdTool\src

#modules
#include($$PWD/../LStdTool/LStdTool.pri)
#include(LQtTool.pri)
include(src/src.pri)


# 要执行copy_head.bat需要清除项目重新构建
# 定义输出路径
#{不可换行
#win32{
#system(.\copy_head.bat)
#}

    #CONFIG += debug_and_release #一万个草泥马

#Qt5.14为什么$$HEADERS会多出Other files目录
#需要添加构建步骤make install  #添加构建-->Make-->填入参数install即可
#eg jom.exe install in" F:\work\pro\LxMultiMedia\build-TTS_msc-qt5_6
#每次构建都会执行, 注意$$HEADERS的值，应放在最后
# 注意先选择单个构建，如果全部构建会等所有构建完成才会执行make install
CONFIG(release, debug|release) {
#target.sources
#target.path = $$[QT_INSTALL_EXAMPLES]/tools/echoplugin
target.path = $$PWD/bin
sources.files = $$HEADERS
sources.path = $$PWD/include
INSTALLS += target sources
}

#$$()或$${}：获取环境变量；
#$$：展开变量；
#$()：将会把$()传入Makefile中，在Makefile中使用$()
#$$[]：从qmake中获取属性，qmake中内置了很多属性，如下：


DISTFILES += \
    $$files(conf/*.conf)


