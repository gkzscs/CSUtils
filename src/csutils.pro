QT += widgets websockets svg
CONFIG += c++11 precompile_header
TEMPLATE = lib
TARGET = csutils

PRECOMPILED_HEADER += csutils_stable.h

DEFINES += CSUTILS_LIB


#INCLUDEPATH += \
#    Core    \
#    Layout  \
#    Control


HEADERS += \
    Control/csformcard.h \
    Control/cslabelcontrol.h \
    Control/cssplitline.h \
    Control/cswgtcontainer.h \
    Core/cscontainer.h \
    Layout/csgridlayout.h \
    Layout/cshboxlayout.h \
    Layout/cslayout.h \
    Layout/csvboxlayout.h \
    csutils_global.h \
    Core/csutils.h  \
    Control/cswidget.h \
    Control/csscrollarea.h \
    csutils_stable.h


SOURCES += \
    Control/csformcard.cpp \
    Control/cslabelcontrol.cpp \
    Control/cssplitline.cpp \
    Control/cswgtcontainer.cpp \
    Core/cscontainer.cpp \
    Core/csutils.cpp \
    Control/cswidget.cpp    \
    Control/csscrollarea.cpp \
    Layout/csgridlayout.cpp \
    Layout/cshboxlayout.cpp \
    Layout/cslayout.cpp \
    Layout/csvboxlayout.cpp



DEBUG_DIR = $$PWD/lib_x64/Desktop_Qt_5_12_6_MSVC2017_64bit/Debug/debug

win32: {
    dllInst.files += $$DEBUG_DIR/*.dll
    dllInst.path += $$PWD/../bin
    libInst.files += $$DEBUG_DIR/*.lib
    libInst.path += $$PWD/../lib
    INSTALLS += dllInst libInst
}
