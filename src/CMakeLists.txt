set(I3PagerPlugin_SRCS
        plugin.cpp
        plugin.h
        i3pager.cpp
        i3pager.h
        i3listener.cpp
        i3listener.h
        workspace.cpp
        workspace.h)

add_library(I3PagerPlugin SHARED ${I3PagerPlugin_SRCS})
target_compile_options(I3PagerPlugin PRIVATE -fexceptions)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

if (CI_ERRORS)
        target_compile_options(I3PagerPlugin PRIVATE -Werror -Wall -Wextra -pedantic-errors)
endif()

include_directories(${I3IPCpp_INCLUDE_DIRS})
link_directories(${I3IPCpp_LIBRARY_DIRS})

target_link_libraries(I3PagerPlugin
  Qt${QT_MAJOR_VERSION}Quick
  Qt${QT_MAJOR_VERSION}::Widgets
  KF${KF_MAJOR_VERSION}::WindowSystem
  ${I3IPCpp_LIBRARIES}
  Plasma::Plasma)

# install plugin
install(TARGETS  I3PagerPlugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/private/I3Pager)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/private/I3Pager)
