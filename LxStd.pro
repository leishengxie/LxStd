
TARGET = LxStd

TEMPLATE = lib


CONFIG += c++11

#预处理程序定义
DEFINES += LX_STD_LIB


CONFIG(debug, debug|release){

    # DEBUG base name add 'd' suffix
    TARGET = $$join(TARGET,,,d)

}
DESTDIR = $$PWD/lib

RC_FILE += version.rc



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






include(LxStd.pri)


CONFIG(release, debug|release) {
#target.sources
#target.path = $$[QT_INSTALL_EXAMPLES]/tools/echoplugin
target.path = $$PWD/lib
#headers.files = LxStd.h LStd.h
headers.files = $$HEADERS
headers.path = $$PWD/include
INSTALLS += target headers
}


DISTFILES += \
    $$files(conf/*.conf)
