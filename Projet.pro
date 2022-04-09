# configuration Qt
QT       += core gui opengl widgets openglwidgets
TEMPLATE  = app
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

# fichiers sources/headers/ressources
SOURCES += main.cpp myglwidget.cpp \
    asteroide.cpp \
    galaxy.cpp \
    station.cpp
HEADERS += \
    asteroide.h \
    galaxy.h \
    myglwidget.h \
    station.h

RESOURCES += \
    res/textures.qrc
