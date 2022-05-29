QT       += core gui opengl widgets openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asteroide.cpp \
    main.cpp \
    mainwindow.cpp \
    myglwidget.cpp \
    station.cpp \
    stb_image.cpp \
    vaisseau.cpp \
    webcam.cpp

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)/lib \
    -lopencv_core455 \
    -lopencv_highgui455 \
    -lopencv_imgproc455 \
    -lopencv_videoio455 \
    -lopencv_features2d455 \
    -lopencv_calib3d455 \
    -lopencv_objdetect455

HEADERS += \
    asteroide.h \
    mainwindow.h \
    myglwidget.h \
    station.h \
    vaisseau.h \
    webcam.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
