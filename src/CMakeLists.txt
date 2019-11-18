set(plasmoidplugin_SRCS
        plugin.cpp
        plugin.h
        i3pager.cpp
        i3pager.h)

add_library(plasmoidplugin SHARED ${plasmoidplugin_SRCS})

include_directories(${I3IPCpp_INCLUDE_DIRS})
link_directories(${I3IPCpp_LIBRARY_DIRS})
target_link_libraries(plasmoidplugin Qt5::Quick Qt5::Widgets KF5::Plasma KF5::WindowSystem ${I3IPCpp_LIBRARIES})

# add_library(i3ipc++ STATIC ${I3IPCpp_LIBRARIES})
# target_link_libraries(plasmoidplugin Qt5::Quick KF5::Plasma KF5::LibTaskManager)

install(TARGETS plasmoidplugin DESTINATION ${QML_INSTALL_DIR}/I3Pager)
install(FILES qmldir DESTINATION ${QML_INSTALL_DIR}/I3Pager)
