cmake_minimum_required(VERSION 3.27)
project(SimpleImageProcessing)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/applications/*.c)
file(GLOB_RECURSE KERNEL_MODULE_SRC_FILES ${SRC_DIR}/kernel_modules/*.c)

foreach (SRC_FILE ${SRC_FILES})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/applications)
    get_filename_component(FILE_NAME ${SRC_FILE} NAME_WE)
    add_executable(${FILE_NAME} ${SRC_FILE})
    target_include_directories(${FILE_NAME} PRIVATE ${INCLUDE_DIR})
    message(STATUS "Adding executable: ${FILE_NAME}")
endforeach ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_custom_command(
        OUTPUT make_kernel_modules
        COMMAND mkdir -p ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/kernel_modules
        COMMAND cd ${SRC_DIR}/kernel_modules
        COMMAND make
)

add_custom_command(
        OUTPUT clean_kernel_modules
        COMMAND cd ${SRC_DIR}/kernel_modules
        COMMAND make clean
)

add_custom_target(mkm ALL DEPENDS make_kernel_modules)
add_custom_target(ckm ALL DEPENDS clean_kernel_modules)
set_target_properties(mkm PROPERTIES EXCLUDE_FROM_ALL TRUE)
set_target_properties(ckm PROPERTIES EXCLUDE_FROM_ALL TRUE)
