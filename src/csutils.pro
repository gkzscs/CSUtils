QT += widgets svg websockets
CONFIG += c++11 precompile_header
TEMPLATE = lib
TARGET = csutils

#CONFIG += force_debug_info

INCLUDEPATH += $$PWD/Component

PRECOMPILED_HEADER += csutils_stable.h

DEFINES += CSUTILS_LIB

include($$(AOS_KERNEL_ROOT)/projects/aos-kernel-dynamic-lib-install.pri)

LIBS += \
    -lUser32

HEADERS += \
    Component/lib/qtmaterialcheckable.h \
    Component/lib/qtmaterialcheckable_internal.h \
    Component/lib/qtmaterialcheckable_p.h \
    Component/lib/qtmaterialoverlaywidget.h \
    Component/lib/qtmaterialripple.h \
    Component/lib/qtmaterialrippleoverlay.h \
    Component/lib/qtmaterialstatetransition.h \
    Component/lib/qtmaterialstatetransitionevent.h \
    Component/lib/qtmaterialstyle.h \
    Component/lib/qtmaterialstyle_p.h \
    Component/lib/qtmaterialtheme.h \
    Component/lib/qtmaterialtheme_p.h \
    Component/qtmaterialcircularprogress.h \
    Component/qtmaterialcircularprogress_internal.h \
    Component/qtmaterialcircularprogress_p.h \
    Control/Base/cstitlebar.h   \
    Control/Base/csadjustablewgt.h  \
    Control/Base/csmessagebox.h \
    Control/Base/cswidget.h   \
    Control/Base/csmainwnd.h    \
    Control/csformcard.h \
    Control/csscrollarea.h \
    Control/csfoldbox.h \
    Control/cspairctrl.h    \
    Control/cspairctrl_impl.hpp  \
    Control/cstree.h    \
    Control/cstreeitem.h    \
    Core/cscontainer.h \
    Core/cscontainer_impl.hpp \
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
    ArtWare/csartware.h \
    ArtWare/csline.h \
    ArtWare/csswitchbutton.h    \
    ArtWare/csbatteryartware.h \
    ArtWare/cscarrierartware.h \
    ArtWare/cssectorlinkartware.h   \
    ArtWare/cslinkqualityartware.h  \
    ArtWare/csacceleratorartware.h  \
    ArtWare/cswindartware.h \
    Animation/csanimation.h \
    Animation/cswaitanimation.h \
    csutils_global.h \
    csutils_stable.h

SOURCES += \
    Component/lib/qtmaterialcheckable.cpp \
    Component/lib/qtmaterialcheckable_internal.cpp \
    Component/lib/qtmaterialoverlaywidget.cpp \
    Component/lib/qtmaterialripple.cpp \
    Component/lib/qtmaterialrippleoverlay.cpp \
    Component/lib/qtmaterialstatetransition.cpp \
    Component/lib/qtmaterialstyle.cpp \
    Component/lib/qtmaterialtheme.cpp \
    Component/qtmaterialcircularprogress.cpp \
    Component/qtmaterialcircularprogress_internal.cpp \
    Control/Base/cstitlebar.cpp \
    Control/Base/csadjustablewgt.cpp    \
    Control/Base/csmessagebox.cpp \
    Control/Base/cswidget.cpp   \
    Control/Base/csmainwnd.cpp  \
    Control/csformcard.cpp \
    Control/csscrollarea.cpp \
    Control/csfoldbox.cpp   \
    Control/cstree.cpp  \
    Control/cstreeitem.cpp  \
    Core/csutils.cpp \
    Core/csappevent.cpp \
    Layout/csgridlayout.cpp \
    Layout/cshboxlayout.cpp \
    Layout/cslayout.cpp \
    Layout/csvboxlayout.cpp \
    Communication/csipchelper.cpp \
    Communication/csappconnector.cpp \
    Communication/cslocalclient.cpp \
    Communication/cslocalserver.cpp \
    ArtWare/csartware.cpp   \
    ArtWare/csline.cpp \
    ArtWare/csswitchbutton.cpp  \
    ArtWare/csbatteryartware.cpp    \
    ArtWare/cscarrierartware.cpp    \
    ArtWare/cssectorlinkartware.cpp   \
    ArtWare/cslinkqualityartware.cpp  \
    ArtWare/csacceleratorartware.cpp  \
    ArtWare/cswindartware.cpp \
    Animation/csanimation.cpp   \
    Animation/cswaitanimation.cpp

copyDynamicLibrary(csutils)
