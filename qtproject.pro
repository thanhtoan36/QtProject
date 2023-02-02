QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/ColorFilterPanelControl/colorfilterpanelcontrol.cpp \
    src/ColorPickerPanelControl/colorpickerpanelcontrol.cpp \
    src/EncoderPanelControl/encoderpanelcontrol.cpp \
    src/GroupLibPanelContol/grouplibpanelcontrol.cpp \
    src/InputNumPanelControl/inputnumpanelcontrol.cpp \
    src/IntensityControl/intensitycontrol.cpp \
    src/PalettePanelControl/palettepanelcontrol.cpp \
    src/PantiltPanelControl/pantiltpanelcontrol.cpp \
    src/PlaybackPanelControl/playbackpanelcontrol.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/ColorFilterPanelControl/colorfilterpanelcontrol.hpp \
    include/ColorFilterPanelControl/define.hpp \
    include/ColorPickerPanelControl/colorpickerpanelcontrol.hpp \
    include/ColorPickerPanelControl/define.hpp \
    include/EncoderPanelControl/define.hpp \
    include/EncoderPanelControl/encoderpanelcontrol.hpp \
    include/GroupLibPanelContol/define.hpp \
    include/GroupLibPanelContol/grouplibpanelcontrol.hpp \
    include/InputNumPanelControl/define.hpp \
    include/InputNumPanelControl/inputnumpanelcontrol.hpp \
    include/IntensityControl/define.hpp \
    include/IntensityControl/intensitycontrol.hpp \
    include/PalettePanelControl/define.hpp \
    include/PalettePanelControl/palettepanelcontrol.hpp \
    include/PantiltPanelControl/define.hpp \
    include/PantiltPanelControl/pantiltpanelcontrol.hpp \
    include/PlaybackPanelControl/define.hpp \
    include/PlaybackPanelControl/playbackpanelcontrol.hpp \
    include/mainwindow.h

INCLUDEPATH += \
    include/

FORMS += \
    form/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
