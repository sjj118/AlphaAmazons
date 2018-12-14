cmake_minimum_required(VERSION 3.12)
project(AlphaAmazons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(AlphaAmazons cpp/main.cpp cpp/Action.h cpp/ChessBoard.h cpp/ChessBoard.cpp cpp/Action.cpp cpp/EvalField.cpp cpp/EvalField.h cpp/MCTree.cpp cpp/MCTree.h)
target_link_libraries(AlphaAmazons Qt5::Core)
target_link_libraries(AlphaAmazons Qt5::Widgets)