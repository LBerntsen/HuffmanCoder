cmake_minimum_required(VERSION 3.27)
project(HuffmanCoder)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(src)

add_executable(HuffmanCoder
        src/core/app.cpp
        src/core/app.h
        src/core/main.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/gui/mainwindow.ui
        src/Resources/mainwindow.qrc
        src/core/PriorityQueue.cpp
        src/core/PriorityQueue.h
        src/core/Node.cpp
        src/core/Node.h)

target_link_libraries(HuffmanCoder
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets)
