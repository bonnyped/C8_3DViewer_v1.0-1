QT       += core gui opengl openglwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(3rdparty/QtGifImage/src/gifimage/qtgifimage.pri)

CONFIG += c++17
CONFIG+=sdk_no_version_check 
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../3d_parser_obj.c \
    ../affine_transformations.c \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
    styleviewer.cpp

HEADERS += \
    ../three_d_viewer.h \
    mainwindow.h \
    myopenglwidget.h \
    styleviewer.h

FORMS += \
    mainwindow.ui
ICON = resources/hamlet.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

!isEmpty(IS_LINUX): LIBS += -lGL

RESOURCES += \
    resources/res.qrc








