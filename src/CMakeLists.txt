set(SOURCES
	main.cpp
	renderdemo.cpp
	Splitter.cpp
	ViewportPane.cpp
	ViewportTitleBar.cpp)

set(HEADERS
	renderdemo.h
	Splitter.h
	Viewport.h
    ViewportPane.h
	ViewportTitleBar.h)

#cmake 3.0 only:
#set(QRC_FILES
#    ../res/styles.qrc)

find_package(Qt5Widgets REQUIRED)

#cmake 2.8 solution:
qt5_add_resources(QRC_FILES ../res/styles.qrc)

include_directories(${QT_INCLUDES})

link_directories(${QT_LIBRARIES})

add_executable(RenderDemo WIN32
    ${SOURCES} ${HEADERS} ${QRC_FILES})

qt5_use_modules(RenderDemo Widgets)
