cmake_minimum_required(VERSION 3.5)

project(YYSportEditer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories("./include")
include_directories("./include/libopenshot-audio")
include_directories("./include/libopenshot")
include_directories("./include/libopenshot/Qt")

IF (WIN32)
    link_directories("./lib/win32")
ELSEIF (APPLE)
    link_directories("./lib/mac")
ELSE (UNIX)
ENDIF()

if(ANDROID)
  add_library(YYSportEditer SHARED
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    AudioPlaybackThread.cpp
    VideoCacheThread.h
    AudioPlaybackThread.h
    VideoPlaybackThread.cpp
    VideoPlaybackThread.h
    VideoRenderer.cpp
    PlayerDemo.cpp
    VideoRenderer.h
    PlayerDemo.h
    VideoRenderWidget.cpp
    PlayerPrivate.cpp
    VideoRenderWidget.h
    PlayerPrivate.h
    VideoCacheThread.cpp
  )
else()
  add_executable(YYSportEditer
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    AudioPlaybackThread.cpp
    VideoCacheThread.h
    AudioPlaybackThread.h
    VideoPlaybackThread.cpp
    VideoPlaybackThread.h
    VideoRenderer.cpp
    PlayerDemo.cpp
    VideoRenderer.h
    PlayerDemo.h
    VideoRenderWidget.cpp
    PlayerPrivate.cpp
    VideoRenderWidget.h
    PlayerPrivate.h
    VideoCacheThread.cpp
  )
endif()

IF (WIN32)
    link_directories("./lib/win32")
    target_link_libraries(YYSportEditer libgomp.dll.a libopenshot.dll.a libopenshot-audio.dll.a Qt5::Widgets)
ELSEIF (APPLE)
    link_directories("./lib/mac")
    target_link_libraries(YYSportEditer libopenshot.dylib libopenshot-audio.dylib Qt5::Widgets)
ELSE (UNIX)
    target_link_libraries(YYSportEditer libopenshot.dylib libopenshot-audio.dylib Qt5::Widgets)
ENDIF()

#target_link_libraries(YYSportEditer PRIVATE Qt5::Widgets)
