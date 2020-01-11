# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = YYSportEditer

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

-lgcc_s.so.1

INCLUDEPATH += "./include"
INCLUDEPATH += "./include/libopenshot"
INCLUDEPATH += "./include/libopenshot/Qt"
INCLUDEPATH += "./include/libopenshot-audio"

win32{
    #DEFINES += _WIN32_WINNT=0x600
    INCLUDEPATH += "D:/project/msys32/mingw32/i686-w64-mingw32/include"

    CONFIG(debug, debug|release){
        DEFINES += JUCE_FORCE_DEBUG
        LIBS += $$PWD/lib/Debug/libopenshot-audio.dll.a
        LIBS += $$PWD/lib/Debug/libopenshot.dll.a
    } else{
        LIBS += $$PWD/lib/Release/libopenshot-audio.dll.a
        LIBS += $$PWD/lib/Release/libopenshot.dll.a
    }
}

mac{
    INCLUDEPATH += $$PWD/include/mac/zmq
    INCLUDEPATH += /usr/local/include
    INCLUDEPATH += /usr/local/Cellar/jsoncpp/1.9.1/include

    CONFIG(debug, debug|release) {
        #DEFINES += JUCE_FORCE_DEBUG
        #DEFINES += DOXYGEN
        DEFINES += DEBUG
        LIBS += $$PWD/lib/mac/libopenshot-audio.0.1.8.dylib
        LIBS += $$PWD/lib/mac/libopenshot.0.2.3.dylib
        LIBS += $$PWD/lib/mac/libgomp.1.dylib
    } else {
        DEFINES += NODEBUG
        LIBS += $$PWD/lib/mac/libopenshot-audio.0.1.8.dylib
        LIBS += $$PWD/lib/mac/libopenshot.0.2.3.dylib
        LIBS += $$PWD/lib/mac/libgomp.1.dylib
    }
}


HEADERS = $$PWD/MainWindow.h \
   $$PWD/PlayerDemo.h \
   #$$PWD/PlayerPrivate.h \
   #$$PWD/VideoCacheThread.h \
   #$$PWD/VideoPlaybackThread.h \
   #$$PWD/VideoRenderer.h \
   $$PWD/VideoWidget.h \

SOURCES = $$PWD/main.cpp \
   $$PWD/MainWindow.cpp \
   $$PWD/PlayerDemo.cpp \
   #$$PWD/PlayerPrivate.cpp \
   #$$PWD/VideoCacheThread.cpp \
   #$$PWD/VideoPlaybackThread.cpp \
   #$$PWD/VideoRenderer.cpp \
   $$PWD/VideoWidget.cpp

DEFINES += DEBUG

FORMS += \
    MainWindow.ui
