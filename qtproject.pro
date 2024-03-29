QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/playbackControl/listWidgetGridLineOverlay.cpp \
    src/playbackControl/markingPickerPopup.cpp \
    src/playbackControl/playbackControlHorizon.cpp \
    src/playbackControl/playbackRowDelegate.cpp \
    src/testDataParser.cpp \
    src/baseComponent/dynamicStyleSheet.cpp \
    src/baseComponent/gridBackground.cpp \
    src/colorFilterControl/colorFilterControlHorizon.cpp \
    src/encoderControl/customEncoder.cpp \
    src/encoderControl/encoderControlHorizon.cpp \
    src/encoderControl/encoderControl.cpp \
    src/groupControl/groupControlHorizon.cpp \
    src/inputNumControl/inputNumControlHorizon.cpp \
    src/intensityControl/intensityControlHorizon.cpp \
    src/libraryControl/libraryControlHorizon.cpp \
    src/paletteControl/paletteControlHorizon.cpp \
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
    src/groupControl/groupControl.cpp \
    src/inputNumControl/inputNumControl.cpp \
    src/intensityControl/intensityControl.cpp \
    src/paletteControl/paletteControl.cpp \
    src/trackControl/trackControl.cpp \
    src/playbackControl/playbackControl.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/ultility.cpp

HEADERS += \
    include/baseComponent/customButtonBase.h \
    include/baseComponent/customToggleButtonBase.h \
    include/baseComponent/gridBackground.h \
    include/baseComponent/panelControlBase.h \
    include/baseComponent/panelWindow.h \
    include/baseComponent/customPushButton.h \
    include/baseComponent/selectButton.h \
    include/baseComponent/titleSelectButton.h \
    include/baseComponent/toggleButton.h \
    include/colorFilterControl/colorFilterControl.h \
    include/colorFilterControl/colorFilterControlHorizon.h \
    include/colorFilterControl/colorFilterControl_datatypes.h \
    include/colorFilterControl/colorFilterControl_define.h \
    include/colorPickerControl/cieaux.h \
    include/colorPickerControl/ciemaker.h \
    include/colorPickerControl/colorPickerControl.h \
    include/colorPickerControl/colorPickerControlHorizon.h \
    include/colorPickerControl/colorPickerControl_datatypes.h \
    include/colorPickerControl/colorPickerControl_define.h \
    include/colorPickerControl/customColorPickerRGB.h \
    include/colorPickerControl/customColorPickerXY.h \
    include/encoderControl/customEncoder.h \
    include/encoderControl/encoderControl.h \
    include/encoderControl/encoderControlHorizon.h \
    include/encoderControl/encoderControl_datatypes.h \
    include/encoderControl/encoderControl_define.h \
    include/groupControl/groupControl.h \
    include/groupControl/groupControlHorizon.h \
    include/groupControl/groupControl_datatypes.h \
    include/groupControl/groupControl_define.h \
    include/inputNumControl/inputNumControl.h \
    include/inputNumControl/inputNumControlHorizon.h \
    include/inputNumControl/inputNumControl_datatypes.h \
    include/inputNumControl/inputNumControl_define.h \
    include/intensityControl/intensityControl.h \
    include/intensityControl/intensityControl_define.h \
    include/intensityControl/intensityControlHorizon.h \
    include/libraryControl/libraryControl.h \
    include/libraryControl/libraryControlHorizon.h \
    include/libraryControl/libraryControl_datatypes.h \
    include/libraryControl/libraryControl_define.h \
    include/paletteControl/paletteControl.h \
    include/paletteControl/paletteControlHorizon.h \
    include/paletteControl/paletteControl_datatypes.h \
    include/paletteControl/paletteControl_define.h \
    include/playbackControl/listWidgetGridLineOverlay.h \
    include/playbackControl/markingPickerPopup.h \
    include/playbackControl/playbackControlHorizon.h \
    include/playbackControl/playbackRowDelegate.h \
    include/testDataParser.h \
    include/trackControl/pantiltControl.h \
    include/trackControl/trackControl.h \
    include/trackControl/trackControlHorizon.h \
    include/trackControl/trackControl_datatypes.h \
    include/trackControl/trackControl_define.h \
    include/playbackControl/playbackControl.h \
    include/playbackControl/playbackControl_datatypes.h \
    include/playbackControl/playbackControl_define.h \
    include/mainwindow.h \
    include/utility.h \
    include/baseComponent/dynamicStyleSheet.h

INCLUDEPATH += \
    include/

FORMS += \
    form/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
