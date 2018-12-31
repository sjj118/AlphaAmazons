cmake_minimum_required(VERSION 3.12)
project(AlphaAmazons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(AlphaAmazons botzone/main.cpp botzone/Action.h botzone/ChessBoard.h botzone/ChessBoard.cpp botzone/EvalField.cpp botzone/EvalField.h botzone/MCTree.cpp botzone/MCTree.h botzone/Bot.cpp botzone/Bot.h botzone/Player.h botzone/OpeningBook.cpp botzone/OpeningBook.h botzone/Logger.h botzone/Logger.cpp)
target_link_libraries(AlphaAmazons Qt5::Core)
target_link_libraries(AlphaAmazons Qt5::Widgets)


cmake_minimum_required(VERSION 3.12)
project(OpeningGenerate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(OpeningGenerate opening/generator.cpp botzone/ChessBoard.h botzone/ChessBoard.cpp botzone/Action.h botzone/EvalField.h botzone/EvalField.cpp botzone/MCTree.h botzone/MCTree.cpp opening/GTree.cpp opening/GTree.h botzone/Logger.h botzone/Logger.cpp)


cmake_minimum_required(VERSION 3.12)
project(MergedBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(MergedBot AlphaAmazons.cpp)