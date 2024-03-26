cmake_minimum_required(VERSION 3.27)
project(music_db)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/home/massonskyi/CLionProjects/untitled2/taglib-2.0/taglib")
set(taglib_include_dirs
        lib/taglib/toolkit
        lib/taglib/asf
        lib/taglib/mpeg
        lib/taglib/ogg
        lib/taglib/ogg/flac
        lib/taglib/flac
        lib/taglib/mpc
        lib/taglib/mp4
        lib/taglib/ogg/vorbis
        lib/taglib/ogg/speex
        lib/taglib/ogg/opus
        lib/taglib/mpeg/id3v2
        lib/taglib/mpeg/id3v2/frames
        lib/taglib/mpeg/id3v1
        lib/taglib/ape
        lib/taglib/wavpack
        lib/taglib/trueaudio
        lib/taglib/riff
        lib/taglib/riff/aiff
        lib/taglib/riff/wav
        lib/taglib/mod
        lib/taglib/s3m
        lib/taglib/it
        lib/taglib/xm
        lib/taglib/dsf
        lib/taglib/dsdiff
)

list(TRANSFORM taglib_include_dirs PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)
find_package(Python REQUIRED)
find_package(pybind11 REQUIRED)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${taglib_include_dirs})
include_directories(${pybind11_INCLUDE_DIRS})

include_directories(
        lib/taglib
        lib/taglib/toolkit
        lib/taglib/ape
        lib/taglib/mpeg
        lib/taglib/mpeg/id3v1
        lib/taglib/mpeg/id3v2
        lib/taglib/mpeg/id3v2/frames
        lib/taglib/bindings/c/
)

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
        includes/hpp/out.hpp
)

target_link_libraries(music_db
        Qt::Core
        Qt::Gui
        Qt::Widgets
        sqlite3
        tag
        ${PYTHON_LIBRARIES}
        ${pybind11_LIBRARIES}
        Python::Python
)