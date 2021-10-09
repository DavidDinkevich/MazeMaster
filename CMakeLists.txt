cmake_minimum_required(VERSION 3.20)
project(MazeMaster)

set(CMAKE_CXX_STANDARD 20)

include_directories(headers)

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(SFML src/main.cpp src/engine.cpp headers/engine.hpp headers/graphs/gridgraph.hpp src/graphs/gridgraph.cpp headers/graphs/mazegraph.hpp src/graphs/mazegraph.cpp headers/graphs/mazerenderer.hpp src/graphs/mazerenderer.cpp headers/graphs/astarsolver.hpp src/graphs/astarsolver.cpp headers/gui/button.hpp src/gui/button.cpp headers/gui/startupwindow.hpp src/gui/startupwindow.cpp headers/gui/mainwindow.hpp src/gui/mainwindow.cpp headers/graphs/obstaclegraph.hpp src/graphs/obstaclegraph.cpp headers/graphs/graph.hpp src/graphs/obstaclegraphrenderer.cpp headers/graphs/obstaclegraphrenderer.hpp src/graphs/graphrenderer.cpp headers/graphs/graphrenderer.hpp)
target_link_libraries (SFML sfml-graphics sfml-window sfml-system)
