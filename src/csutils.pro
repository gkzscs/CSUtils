QT += widgets svg websockets
CONFIG += c++11 precompile_header
TEMPLATE = lib
TARGET = csutils

CONFIG += force_debug_info

INCLUDEPATH += $$PWD/Component

PRECOMPILED_HEADER += csutils_stable.h

DEFINES += CSUTILS_LIB

include($$(AOS_KERNEL_ROOT)/projects/aos-kernel-dynamic-lib-install.pri)
include($$(AOS_KERNEL_ROOT)/projects/loggingservice.pri)


win32 {

LIBS += \
    -lUser32

}


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
    Component/qtmaterialcheckbox.h \
    Component/qtmaterialcheckbox_p.h \
    Component/qtmaterialcircularprogress.h \
    Component/qtmaterialcircularprogress_internal.h \
    Component/qtmaterialcircularprogress_p.h \
    Component/qtmaterialcombobox.h \
    Component/qtmaterialcombobox_p.h \
    Component/qtmaterialflatbutton.h \
    Component/qtmaterialflatbutton_internal.h \
    Component/qtmaterialflatbutton_p.h \
    Component/qtmaterialhboxlayoutcomponentgroup.h \
    Component/qtmaterialhboxlayoutcomponentgroup_p.h \
    Component/qtmaterialiconbutton.h \
    Component/qtmaterialiconbutton_p.h \
    Component/qtmateriallineedit.h \
    Component/qtmateriallineedit_p.h \
    Component/qtmaterialprogress.h \
    Component/qtmaterialprogress_internal.h \
    Component/qtmaterialprogress_p.h \
    Component/qtmaterialradiobutton.h \
    Component/qtmaterialradiobutton_p.h \
    Component/qtmaterialraisedbutton.h \
    Component/qtmaterialraisedbutton_p.h \
    Component/qtmaterialscrollbar.h \
    Component/qtmaterialscrollbar_internal.h \
    Component/qtmaterialscrollbar_p.h \
    Component/qtmaterialslider.h \
    Component/qtmaterialslider_internal.h \
    Component/qtmaterialslider_p.h \
    Component/qtmaterialsnackbar.h \
    Component/qtmaterialsnackbar_internal.h \
    Component/qtmaterialsnackbar_p.h \
    Component/qtmaterialstatusbutton_p.h \
    Component/qtmaterialtext.h \
    Component/qtmaterialtext_p.h \
    Component/qtmaterialtextbutton.h \
    Component/qtmaterialtextbutton_p.h \
    Component/qtmaterialtoggle.h \
    Component/qtmaterialtoggle_internal.h \
    Component/qtmaterialtoggle_p.h \
    Component/qtmaterialstatusbutton.h \
    Control/Base/cmessagebubble.h \
    Control/Base/cstitlebar.h   \
    Control/Base/csadjustablewgt.h  \
    Control/Base/csmessagebox.h \
    Control/Base/cswidget.h   \
    Control/Base/csmainwnd.h    \
    Control/GeoMap/geo_map_menu.h   \
    Control/GeoMap/geo_map_action.h \
    Control/csformcard.h \
    Control/csscrollarea.h \
    Control/csfoldbox.h \
    Control/cspairctrl.h    \
    Control/cspairctrl_impl.hpp  \
    Control/cstree.h    \
    Control/cstreeitem.h    \
    Control/csmulticolumnlabel.h    \
    Control/cstablelabel.h  \
    Control/cssharedcombobox.h  \
    Core/cscontainer.h \
    Core/cscontainer_impl.hpp \
    Core/csutils.h \
    Core/csappevent.h   \
    Core/csintvalidator.h   \
    Layout/csgridlayout.h \
    Layout/cshboxlayout.h \
    Layout/cslayout.h \
    Layout/csvboxlayout.h \
    Layout/cs_form_layout.h \
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
    ArtWare/csplayerprogress.h  \
    ArtWare/csprogressbar.h \
    ArtWare/csgcsbattery.h  \
    ArtWare/cs_bubble_tooltip.h   \
    ArtWare/cs_wind_vane.h          \
    ArtWare/cs_progress_ring.h  \
    Animation/csanimation.h \
    Animation/cswaitanimation.h \
    Layout/qtmaterialhboxlayout.h \
    Layout/qtmaterialhboxlayout_p.h \
    csutils_global.h \
    csutils_stable.h \
    qtmaterialcombobox_p.h \

SOURCES += \
    Component/lib/qtmaterialcheckable.cpp \
    Component/lib/qtmaterialcheckable_internal.cpp \
    Component/lib/qtmaterialoverlaywidget.cpp \
    Component/lib/qtmaterialripple.cpp \
    Component/lib/qtmaterialrippleoverlay.cpp \
    Component/lib/qtmaterialstatetransition.cpp \
    Component/lib/qtmaterialstyle.cpp \
    Component/lib/qtmaterialtheme.cpp \
    Component/qtmaterialcheckbox.cpp \
    Component/qtmaterialcircularprogress.cpp \
    Component/qtmaterialcircularprogress_internal.cpp \
    Component/qtmaterialcombobox.cpp \
    Component/qtmaterialflatbutton.cpp \
    Component/qtmaterialflatbutton_internal.cpp \
    Component/qtmaterialhboxlayoutcomponentgroup.cpp \
    Component/qtmaterialiconbutton.cpp \
    Component/qtmateriallineedit.cpp \
    Component/qtmaterialprogress.cpp \
    Component/qtmaterialprogress_internal.cpp \
    Component/qtmaterialradiobutton.cpp \
    Component/qtmaterialraisedbutton.cpp \
    Component/qtmaterialscrollbar.cpp \
    Component/qtmaterialscrollbar_internal.cpp \
    Component/qtmaterialslider.cpp \
    Component/qtmaterialslider_internal.cpp \
    Component/qtmaterialsnackbar.cpp \
    Component/qtmaterialsnackbar_internal.cpp \
    Component/qtmaterialtext.cpp \
    Component/qtmaterialtextbutton.cpp \
    Component/qtmaterialtoggle.cpp \
    Component/qtmaterialtoggle_internal.cpp \
    Component/qtmaterialstatusbutton.cpp \
    Control/Base/cmessagebubble.cpp \
    Control/Base/cstitlebar.cpp \
    Control/Base/csadjustablewgt.cpp    \
    Control/Base/csmessagebox.cpp \
    Control/Base/cswidget.cpp   \
    Control/Base/csmainwnd.cpp  \
    Control/GeoMap/geo_map_menu.cpp   \
    Control/GeoMap/geo_map_action.cpp \
    Control/csformcard.cpp \
    Control/csscrollarea.cpp \
    Control/csfoldbox.cpp   \
    Control/cstree.cpp  \
    Control/cstreeitem.cpp  \
    Control/csmulticolumnlabel.cpp    \
    Control/cstablelabel.cpp  \
    Control/cssharedcombobox.cpp  \
    Core/csutils.cpp \
    Core/csappevent.cpp \
    Core/csintvalidator.cpp   \
    Layout/csgridlayout.cpp \
    Layout/cshboxlayout.cpp \
    Layout/cslayout.cpp \
    Layout/csvboxlayout.cpp \
    Layout/cs_form_layout.cpp \
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
    ArtWare/csplayerprogress.cpp  \
    ArtWare/csprogressbar.cpp   \
    ArtWare/csgcsbattery.cpp  \
    ArtWare/cs_bubble_tooltip.cpp   \
    ArtWare/cs_wind_vane.cpp    \
    ArtWare/cs_progress_ring.cpp  \
    Animation/csanimation.cpp   \
    Animation/cswaitanimation.cpp \
    Layout/qtmaterialhboxlayout.cpp

# Copy resource files
win32 {
    src_dir = $$PWD/config/*.*

    CONFIG(debug, debug|release) {
        dst_dir = $$(AOSDK_KERNEL_ROOT)/../debug/
    } else {
        dst_dir = $$(AOSDK_KERNEL_ROOT)/../release/
    }

    src_dir ~= s,/,\\,g
    dst_dir ~= s,/,\\,g
    system(xcopy $$src_dir $$dst_dir /y /e)
}

unix {

    src_dir = $$PWD/config/*.*

    CONFIG(debug, debug|release) {
        dst_dir = $$(AOSDK_KERNEL_ROOT)/../debug/
    } else {
        dst_dir = $$(AOSDK_KERNEL_ROOT)/../release/
    }

    src_dir ~= s,/,\\,g
    dst_dir ~= s,/,\\,g
    system(cp $$src_dir $$dst_dir)
}

copyDynamicLibrary(csutils)

RESOURCES += \
    Component/resource.qrc
