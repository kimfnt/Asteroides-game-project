QT       += core gui opengl widgets openglwidgets
CONFIG += c++17

# ajout des libs au linker
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

# nom de l'exe genere
TARGET 	  = PROJET ASTEROIDES

SOURCES += \
    asteroide.cpp \
    galaxy.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    myglwidget.cpp \
    settingsdialog.cpp \
    station.cpp

HEADERS += \
    asteroide.h \
    galaxy.h \
    mainwindow.h \
    menuwindow.h \
    myglwidget.h \
    settingsdialog.h \
    station.h

FORMS += \
    mainwindow.ui \
    menuwindow.ui \
    settingsdialog.ui

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include


LIBS += -lopengl32 -lglu32 \
    -L$$(OPENCV_DIR)\lib \
    -lopencv_core455 \
    -lopencv_highgui455 \
    -lopencv_imgproc455 \
    -lopencv_imgcodecs455\
    -lopencv_videoio455 \
    -lopencv_features2d455 \
    -lopencv_calib3d455 \
    -lopencv_objdetect455 \

RESOURCES += \
    res/textures.qrc
