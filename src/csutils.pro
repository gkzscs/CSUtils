QT += widgets svg websockets
CONFIG += c++11 precompile_header
TEMPLATE = lib
TARGET = csutils

PRECOMPILED_HEADER += csutils_stable.h

DEFINES += CSUTILS_LIB


HEADERS += \
    Control/csformcard.h \
    Control/csline.h \
    Control/csscrollarea.h \
    Control/cswidget.h \
    Control/csfoldbox.h \
    Core/cscontainer.h \
    Core/csutils.h \
    Core/csappevent.h   \
    Layout/csgridlayout.h \
    Layout/cshboxlayout.h \
    Layout/cslayout.h \
    Layout/csvboxlayout.h \
    Communication/csipchelper.h \
    Communication/csappconnector.h \
    Communication/cslocalclient.h \
    Communication/cslocalserver.h \
    csutils_global.h \
    csutils_stable.h


SOURCES += \
    Control/csformcard.cpp \
    Control/csline.cpp \
    Control/csscrollarea.cpp \
    Control/cswidget.cpp \
    Control/csfoldbox.cpp   \
    Core/cscontainer.cpp \
    Core/csutils.cpp \
    Core/csappevent.cpp \
    Layout/csgridlayout.cpp \
    Layout/cshboxlayout.cpp \
    Layout/cslayout.cpp \
    Layout/csvboxlayout.cpp \
    Communication/csipchelper.cpp \
    Communication/csappconnector.cpp \
    Communication/cslocalclient.cpp \
    Communication/cslocalserver.cpp


DEBUG_DIR = $$PWD/lib_x64/win/Debug/debug

win32: {
    dllInst.files += $$DEBUG_DIR/*.dll
    dllInst.path += $$PWD/../bin
    libInst.files += $$DEBUG_DIR/*.lib
    libInst.path += $$PWD/../lib
    INSTALLS += dllInst libInst
}
