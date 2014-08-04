set(SOURCES
	main.cpp
	renderdemo.cpp
	Splitter.cpp
	Viewport.cpp
	ViewportTitleBar.cpp)

set(HEADERS
	renderdemo.h
	Splitter.h
	Viewport.h
	ViewportTitleBar.h)

find_package(Qt5Widgets REQUIRED)

include_directories(${QT_INCLUDES})

link_directories(${QT_LIBRARIES})

add_executable(RenderDemo WIN32
	${SOURCES} ${HEADERS})

qt5_use_modules(RenderDemo Widgets)
