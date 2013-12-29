project(plasma-ponycountdownplasma)
 
find_package(KDE4 REQUIRED)

include(KDE4Defaults)
 
add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )
 
set(ponycountdownplasma_SRCS qdbusnotification.cpp 
			     qtimespan.cpp
			     filedownloader.cpp 
			     ponycountdownplasma.cpp)
			     

kde4_add_plugin(plasma_applet_ponycountdownplasma ${ponycountdownplasma_SRCS})

target_link_libraries(plasma_applet_ponycountdownplasma 
		      ${QT_QTNETWORK_LIBRARY}
                      ${KDE4_PLASMA_LIBS} 
                      ${KDE4_KDEUI_LIBS}
                      qjson)
 
install(TARGETS plasma_applet_ponycountdownplasma
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma_applet_ponycountdownplasma.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})


kde4_install_icons(${ICON_INSTALL_DIR})
kde4_update_iconcache()
