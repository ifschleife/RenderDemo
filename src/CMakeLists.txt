set(SOURCES
	main.cpp
    MainWindow.cpp
    Viewport.cpp
    #renderdemo.cpp
    #Splitter.cpp
    #ViewportPane.cpp
    #ViewportTitleBar.cpp
    )

set(HEADERS
    #renderdemo.h
    MainWindow.h
    #Splitter.h
    Viewport.h
    #ViewportPane.h
    #ViewportTitleBar.h
    )

set(UI_FILES
    MainWindow.ui
    Viewport.ui
    )

set(QRC_FILES
    ../res/res.qrc)

find_package(Qt5Widgets REQUIRED)

include_directories(${QT_INCLUDES})

link_directories(${QT_LIBRARIES})

add_executable(RenderDemo WIN32
    ${SOURCES} ${HEADERS} ${UI_FILES} ${QRC_FILES})

qt5_use_modules(RenderDemo Widgets)
