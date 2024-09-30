QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += uitools

CONFIG += c++17
CONFIG += console
CONFIG += sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BinarySystem.cpp \
    DecimalSystem.cpp \
    HexadecimalSystem.cpp \
    OctalSystem.cpp \
    desktop.cpp \
    main.cpp \
    mobile.cpp \
    mobileandroid.cpp

HEADERS += \
    BinarySystem.h \
    DecimalSystem.h \
    HexadecimalSystem.h \
    Library.h \
    OctalSystem.h \
    desktop.h \
    mobile.h \
    mobileandroid.h \
    testingForInput.h

FORMS += \
    desktop.ui \
    mobile.ui \
    mobileandroid.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
    translations/CalculusSystem_ru_RU.ts

RESOURCES += \
    resources.qrc
