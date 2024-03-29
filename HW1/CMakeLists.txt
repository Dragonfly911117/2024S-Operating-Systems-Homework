cmake_minimum_required(VERSION 3.27)
project(HW1)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SRC_FILES ${SRC_DIR}/applications/*.c)

foreach (SRC_FILE ${SRC_FILES})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/applications)
    get_filename_component(FILE_NAME ${SRC_FILE} NAME_WE)
    add_executable(${FILE_NAME} ${SRC_FILE})
    target_include_directories(${FILE_NAME} PRIVATE ${INCLUDE_DIR})
endforeach ()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory("${SRC_DIR}/kernel_modules" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel_modules)