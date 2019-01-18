cmake_minimum_required(VERSION 3.12)
project(AlphaAmazons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(AlphaAmazons botzone.cpp common/Action.h common/ChessBoard.h common/ChessBoard.cpp bot/EvalField.cpp bot/EvalField.h bot/MCTree.cpp bot/MCTree.h bot/Bot.cpp bot/Bot.h common/Player.h common/Logger.h common/Logger.cpp)


cmake_minimum_required(VERSION 3.12)
project(MergedBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(MergedBot merged.cpp)


cmake_minimum_required(VERSION 3.12)
project(AmazonsGame)

set(CMAKE_CXX_STANDARD 17)
set(Qt5_DIR "/usr/local/Cellar/qt/5.12.0/clang_64/lib/cmake/Qt5")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED Core Widgets)

get_target_property(QtCore_location Qt5::Core LOCATION)
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")
foreach (plugin ${Qt5Network_PLUGINS})
    get_target_property(_loc ${plugin} LOCATION)
    message("Plugin ${plugin} is at location ${_loc}")
endforeach ()

add_executable(AmazonsGame common/Action.h common/ChessBoard.h common/ChessBoard.cpp bot/EvalField.cpp bot/EvalField.h bot/MCTree.cpp bot/MCTree.h bot/Bot.cpp bot/Bot.h common/Player.h common/Logger.h common/Logger.cpp ui/Menu.cpp ui/Menu.h AmazonsGame.cpp ui/GameWindow.cpp ui/GameWindow.h)
target_link_libraries(AmazonsGame Qt5::Core)
target_link_libraries(AmazonsGame Qt5::Widgets)

