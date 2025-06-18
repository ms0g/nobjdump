cmake_minimum_required(VERSION 3.17.0)
project(nobjdump VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)

if (APPLE)
    add_compile_options(-gdwarf-4)
endif ()

set(SOURCES
        src/decoder.c src/decoder.h
        src/opcodeTable.c src/opcodeTable.h)

add_executable(${PROJECT_NAME} src/main.c ${SOURCES})
