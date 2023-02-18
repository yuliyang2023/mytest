cmake_minimum_required(VERSION 3.17)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_BUILD_TYPE "Release")
if (APPLE)
    set(CMAKE_PREFIX_PATH "/Users/yuliyang/Qt5.14.2/5.14.2/clang_64/lib/cmake")
elseif(WIN32)
    set(CMAKE_PREFIX_PATH "D://Qt//Qt5.14.2//5.14.2//mingw73_64//lib//cmake")
else()
    set(CMAKE_PREFIX_PATH "/home/yuliyang/Qt5.14.2/5.14.2/gcc_64/lib/cmake")
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

set(QAPPLICATION_CLASS QApplication CACHE STRING "Inheritance class for SingleApplication")
add_subdirectory(singleapplication)

set(SOURCE
  quick.cpp skeleton.cpp flowlayout.cpp addbuttondialog.cpp addtabdialog.cpp)

#https://medium.com/codex/how-to-deploy-your-qt-cross-platform-applications-to-macos-operating-system-using-macdeployqt-281614688dcf
#https://github.com/shadowsocks/shadowsocks-qt5/issues/669
if (APPLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.shadowsocks.shadowsocks-qt5")
    set(MACOSX_BUNDLE_INFO_STRING "A cross-platform shadowsocks GUI client")
    set(MACOSX_BUNDLE_ICON_FILE "shadowsocks-qt5.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
    #    add_executable(${APP_NAME} MACOSX_BUNDLE ${SOURCE} "icons/shadowsocks-qt5.icns")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCE})
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message("APPLE Debug mode")
    else (CMAKE_BUILD_TYPE STREQUAL "Release")
        message("APPLE Release mode")
        add_custom_command(
          TARGET ${PROJECT_NAME}
          POST_BUILD
          COMMAND /Users/yuliyang/Qt5.14.2/5.14.2/clang_64/bin/macdeployqt ${PROJECT_NAME}.app -dmg
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
        )
    endif()
elseif(WIN32)
    add_executable(${PROJECT_NAME} ${SOURCE})
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message("WIN32 Debug mode")
    else (CMAKE_BUILD_TYPE STREQUAL "Release")
        message("WIN32 Release mode")
        add_custom_command(
          TARGET ${PROJECT_NAME}
          POST_BUILD
          COMMAND D:\\Qt\\Qt5.14.2\\5.14.2\\mingw73_64\\bin\\windeployqt.exe ${PROJECT_NAME}.exe
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
        )
    endif()
else()
    add_executable(${PROJECT_NAME} ${SOURCE})
endif()

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
      "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} SingleApplication::SingleApplication)
