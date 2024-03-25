cmake_minimum_required(VERSION 3.27)
project(music_db)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(Python_ADDITIONAL_VERSIONS 3.11)
find_package (Python3 COMPONENTS Interpreter Development)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

include_directories(${Python_INCLUDE_DIRS})
add_executable(music_db
        main.cpp
        src/SQLiteDB.cpp
        includes/SQLiteDB.h
        includes/consts.h
        includes/models.h
        src/IMusic.cpp
        includes/IMusic.h
        includes/controllers.h
        src/controller.cpp
        includes/functiontools.h
        src/functiontools.cpp
)

target_link_libraries(music_db
        Qt::Core
        Qt::Gui
        Qt::Widgets
        sqlite3
)
