cmake_minimum_required(VERSION 3.17.0)
project(nobjdump VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

if (APPLE)
    add_compile_options(-gdwarf-4)
endif ()

set(SOURCES
        src/decoder.cpp src/decoder.h
        src/opcodeTable.cpp src/opcodeTable.h)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
