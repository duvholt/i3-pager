cmake_minimum_required(VERSION 3.16.0)

project(I3Pager)

find_package(ECM REQUIRED NO_MODULE)

set(CMAKE_CXX_STANDARD 17)
set(QT_MAJOR_VERSION "6")
set(QT_MIN_VERSION "6.4.0")
set(KF_MIN_VERSION "6.0.0")
set(KF_MAJOR_VERSION "6")

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH})

include(ECMQtDeclareLoggingCategory)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION}
  CONFIG REQUIRED
  Quick
  Concurrent
  # Plugin
  Widgets
)
find_package(KF${KF_MAJOR_VERSION} ${KF6_MIN_VERSION}
  REQUIRED COMPONENTS
  WindowSystem
  # Pulled in by Plasma
  Config

)
find_package(Plasma)


plasma_install_package(plasmoid org.kde.I3Pager)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

SET(BUILD_SHARED_LIBS OFF)
add_subdirectory(i3ipc++)

target_compile_options(i3ipc++ PRIVATE -fexceptions -fPIC -Wno-deprecated-declarations)
add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
