cmake_minimum_required(VERSION 3.12)
project(AlphaAmazons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(AlphaAmazons botzone.cpp common/Action.h common/ChessBoard.h common/ChessBoard.cpp bot/EvalField.cpp bot/EvalField.h bot/MCTree.cpp bot/MCTree.h bot/Bot.cpp bot/Bot.h control/Player.h bot/OpeningBook.cpp bot/OpeningBook.h common/Logger.h common/Logger.cpp)
target_link_libraries(AlphaAmazons Qt5::Core)
target_link_libraries(AlphaAmazons Qt5::Widgets)


cmake_minimum_required(VERSION 3.12)
project(OpeningGenerate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(OpeningGenerate opening/generator.cpp common/ChessBoard.h common/ChessBoard.cpp common/Action.h bot/EvalField.h bot/EvalField.cpp bot/MCTree.h bot/MCTree.cpp opening/GTree.cpp opening/GTree.h common/Logger.h common/Logger.cpp)


cmake_minimum_required(VERSION 3.12)
project(MergedBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(MergedBot AlphaAmazons.cpp)


cmake_minimum_required(VERSION 3.12)
project(AmazonsGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(AmazonsGame common/Action.h common/ChessBoard.h common/ChessBoard.cpp bot/EvalField.cpp bot/EvalField.h bot/MCTree.cpp bot/MCTree.h bot/Bot.cpp bot/Bot.h control/Player.h bot/OpeningBook.cpp bot/OpeningBook.h common/Logger.h common/Logger.cpp control/Judger.cpp control/Judger.h)
