set(plasmoidplugin_SRCS
        plugin.cpp
        plugin.h
        i3pager.cpp
        i3pager.h
        i3listener.cpp
        i3listener.h
        workspace.cpp
        workspace.h)

add_library(plasmoidplugin SHARED ${plasmoidplugin_SRCS})
target_compile_options(plasmoidplugin PRIVATE -fexceptions)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DQT_NO_DEBUG_OUTPUT")

if (CI_ERRORS)
        target_compile_options(plasmoidplugin PRIVATE -Werror -Wall -Wextra -pedantic-errors)
endif()

include_directories(${I3IPCpp_INCLUDE_DIRS})
link_directories(${I3IPCpp_LIBRARY_DIRS})
target_link_libraries(plasmoidplugin Qt5::Quick Qt5::Widgets KF5::Plasma KF5::WindowSystem ${I3IPCpp_LIBRARIES})

install(TARGETS plasmoidplugin DESTINATION ${QML_INSTALL_DIR}/I3Pager)
install(FILES qmldir DESTINATION ${QML_INSTALL_DIR}/I3Pager)
