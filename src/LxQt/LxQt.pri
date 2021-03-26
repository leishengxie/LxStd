
include($$PWD/widgets/widgets.pri)
include($$PWD/core/core.pri)
include($$PWD/network/network.pri)

SOURCES +=\
    $$PWD/message/LMessageListenner.cpp \
    $$PWD/message/LNotificationCenter.cpp \
    $$PWD/message/LNotifier.cpp \
    $$PWD/delegate/LDelegateSpinbox.cpp \
    $$PWD/util/L9GridImageUtil.cpp \
    $$PWD/util/LFileOperateUtil.cpp \
    $$PWD/util/LXmlOperateUtil.cpp \
    $$PWD/util/LRegExpUtil.cpp \
    $$PWD/util/LCharacterEncodingUtil.cpp \
    $$PWD/LQt.cpp \
    $$PWD/util/LDrawUtil.cpp \
    $$PWD/delegate/LDelegateBase.cpp

HEADERS  += \
    $$PWD/message/LMessageListenner.h \
    $$PWD/message/LNotificationCenter.h \
    $$PWD/message/LNotifier.h \
    $$PWD/delegate/LDelegateSpinbox.h \
    $$PWD/LQtDefine.h \
    $$PWD/util/L9GridImageUtil.h \
    $$PWD/util/LFileOperateUtil.h \
    $$PWD/util/LXmlOperateUtil.h \
    $$PWD/util/LRegExpUtil.h \
    $$PWD/util/LCharacterEncodingUtil.h \
    $$PWD/LQt.h \
    $$PWD/util/LDrawUtil.h \
    $$PWD/delegate/LDelegateBase.h

