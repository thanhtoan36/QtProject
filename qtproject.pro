QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/encoderControl/encoderControlHorizon.cpp \
    src/encoderControl/encoderSlider.cpp \
    src/encoderControl/encoderControl.cpp \
    src/intensityControl/intensityControlHorizon.cpp \
    src/trackControl/pantiltControl.cpp \
    src/trackControl/trackControlHorizon.cpp \
    src/colorPickerControl/cieaux.cpp \
    src/colorPickerControl/ciemaker.cpp \
    src/colorPickerControl/colorPickerControlHorizon.cpp \
    src/colorPickerControl/customColorPickerRGB.cpp \
    src/colorPickerControl/customColorPickerXY.cpp \
    src/libraryControl/libraryControl.cpp \
    src/baseComponent/customToggleButtonBase.cpp \
    src/baseComponent/panelControlBase.cpp \
    src/baseComponent/panelWindow.cpp \
    src/baseComponent/customButtonBase.cpp \
    src/baseComponent/customPushButton.cpp \
    src/baseComponent/selectButton.cpp \
    src/baseComponent/titleSelectButton.cpp \
    src/baseComponent/toggleButton.cpp \
    src/colorFilterControl/colorFilterControl.cpp \
    src/colorPickerControl/colorPickerControl.cpp \
    src/groupLibControl/groupLibControl.cpp \
    src/inputNumControl/inputNumControl.cpp \
    src/intensityControl/intensityControl.cpp \
    src/loghandler.cpp \
    src/paletteControl/paletteControl.cpp \
    src/trackControl/trackControl.cpp \
    src/playbackControl/playbackControl.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/ultility.cpp

HEADERS += \
    include/baseComponent/customButtonBase.h \
    include/baseComponent/customToggleButtonBase.h \
    include/baseComponent/designPolicyDefine.h \
    include/baseComponent/panelControlBase.h \
    include/baseComponent/panelWindow.h \
    include/baseComponent/customPushButton.h \
    include/baseComponent/selectButton.h \
    include/baseComponent/titleSelectButton.h \
    include/baseComponent/toggleButton.h \
    include/colorFilterControl/colorFilterControl.hpp \
    include/colorFilterControl/colorFilterControl_datatypes.h \
    include/colorFilterControl/colorFilterControl_define.hpp \
    include/colorPickerControl/cieaux.h \
    include/colorPickerControl/ciemaker.h \
    include/colorPickerControl/colorPickerControl.hpp \
    include/colorPickerControl/colorPickerControlHorizon.h \
    include/colorPickerControl/colorPickerControlHorizon_define.h \
    include/colorPickerControl/colorPickerControl_datatypes.h \
    include/colorPickerControl/colorPickerControl_define.hpp \
    include/colorPickerControl/customColorPickerRGB.h \
    include/colorPickerControl/customColorPickerXY.h \
    include/encoderControl/encoderControl.hpp \
    include/encoderControl/encoderControlHorizon.h \
    include/encoderControl/encoderControl_datatypes.h \
    include/encoderControl/encoderControl_define.hpp \
    include/encoderControl/encoderSlider.h \
    include/groupLibContol/groupLibControl.hpp \
    include/groupLibContol/groupLibControl_define.hpp \
    include/inputNumControl/inputNumControl.hpp \
    include/inputNumControl/inputNumControl_datatypes.h \
    include/inputNumControl/inputNumControl_define.hpp \
    include/intensityControl/intensityControl.hpp \
    include/intensityControl/intensityControl_datatypes.h \
    include/intensityControl/intensityControl_define.hpp \
    include/intensityControl/intensityControlHorizon.h \
    include/libraryControl/libraryControl.hpp \
    include/libraryControl/libraryControl_datatypes.h \
    include/libraryControl/libraryControl_define.h \
    include/loghandler.h \
    include/paletteControl/paletteControl.hpp \
    include/paletteControl/paletteControl_datatypes.h \
    include/paletteControl/paletteControl_define.hpp \
    include/trackControl/pantiltControl.h \
    include/trackControl/trackControl.hpp \
    include/trackControl/trackControlHorizon.h \
    include/trackControl/trackControl_datatypes.h \
    include/trackControl/trackControl_define.hpp \
    include/playbackControl/playbackControl.hpp \
    include/playbackControl/playbackControl_datatypes.h \
    include/playbackControl/playbackControl_define.hpp \
    include/mainwindow.h \
    include/utility.h

INCLUDEPATH += \
    include/

FORMS += \
    form/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc \
    resources.qrc
