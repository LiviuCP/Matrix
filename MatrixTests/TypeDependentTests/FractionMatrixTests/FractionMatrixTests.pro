QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_fractionmatrixtests.cpp

QMAKE_LFLAGS = "-Wl,-rpath,\'$$top_srcdir/ThirdParty/Fractions/lib\'"

LIBS += -L"$$top_srcdir/ThirdParty/Fractions/lib" -lFractionLib
INCLUDEPATH += $$top_srcdir/ThirdParty/Fractions/include
