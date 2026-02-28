cmake_minimum_required(VERSION 3.16)

project(GeneticTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

qt_standard_project_setup()

qt_add_executable(GeneticTest
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(GeneticTest
    PRIVATE
    Qt6::Widgets
    Qt6::Charts
)

set_target_properties(GeneticTest PROPERTIES
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GeneticTest
    RUNTIME DESTINATION bin
)

target_sources(GeneticTest PRIVATE
    main.cpp
    mainwindow.cpp
)
