QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_qpointfmatrixtests.cpp

DEFINES = QT

INCLUDEPATH += ../../../MatrixLib/Matrix
INCLUDEPATH += ../../../MatrixLib/Utils
