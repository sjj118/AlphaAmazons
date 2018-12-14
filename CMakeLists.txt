cmake_minimum_required(VERSION 3.12)
project(AlphaAmazons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(AlphaAmazons main.cpp Action.h ChessBoard.h ChessBoard.cpp Action.cpp EvalField.cpp EvalField.h MCTree.cpp MCTree.h)
target_link_libraries(AlphaAmazons Qt5::Core)
target_link_libraries(AlphaAmazons Qt5::Widgets)