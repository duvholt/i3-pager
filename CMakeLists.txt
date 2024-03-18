cmake_minimum_required(VERSION 3.16.0)

project(I3Pager)

set(QT_MIN_VERSION "6.6.0")
set(KF6_MIN_VERSION "6.0.0")
set(QT_NO_CREATE_VERSIONLESS_FUNCTIONS True)

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(ECMGenerateQmlTypes)
include(ECMMarkNonGuiExecutable)
include(ECMQmlModule)

find_package(Qt6 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Quick Widgets)
find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS WindowSystem Package)

include(/usr/lib/cmake/Plasma/PlasmaMacros.cmake)

plasma_install_package(plasmoid org.kde.I3Pager)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

SET(BUILD_SHARED_LIBS OFF)
add_subdirectory(i3ipc++)

target_compile_options(i3ipc++ PRIVATE -fexceptions -fPIC -Wno-deprecated-declarations)
add_subdirectory(src)
