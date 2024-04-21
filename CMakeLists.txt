cmake_minimum_required(VERSION 3.16.0)

find_package(ECM REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

set(CMAKE_CXX_STANDARD 17)

find_package(KF5Plasma REQUIRED)
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Quick Concurrent)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS Plasma)
find_package(KF5WindowSystem)

plasma_install_package(plasmoid org.kde.I3Pager)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

SET(BUILD_SHARED_LIBS OFF)
add_subdirectory(i3ipc++)

target_compile_options(i3ipc++ PRIVATE -fexceptions -fPIC -Wno-deprecated-declarations)
add_subdirectory(src)
