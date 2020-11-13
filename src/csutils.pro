QT += widgets websockets svg
CONFIG += c++11 precompile_header
TEMPLATE = lib
TARGET = csutils

PRECOMPILED_HEADER += stable.h

DEFINES += CSUTILS_LIB


INCLUDEPATH += \
    csutils


HEADERS += \
    csutils_global.h \
    csutils/csutils.h \
    csutils/cswidget.h \
    csutils/csscrollarea.h \
    stable.h


SOURCES += \
    csutils/csutils.cpp \
    csutils/cswidget.cpp    \
    csutils/csscrollarea.cpp


DEBUG_DIR = $$PWD/lib_x64/Desktop_Qt_5_12_6_MSVC2017_64bit/Debug/debug

win32: {
    inst.files += $$DEBUG_DIR/*.dll
    inst.path = $$PWD/../bin
    INSTALLS += inst
}
