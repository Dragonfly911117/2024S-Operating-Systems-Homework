cmake_minimum_required(VERSION 3.27.0 FATAL_ERROR)

# Ref:
# https://gitlab.com/christophacham/cmake-kernel-module
# https://gitioc.upc.edu/open-source/xenomai-cmake/blob/master/cmake-modules/FindKernelHeaders.cmake
# https://stackoverflow.com/questions/50877135/cmake-specify-linux-kernel-module-output-build-directory

project(driver VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Module info
add_definitions(-D__KERNEL__ -DMODULE)

# Find the kernel release
execute_process(
        COMMAND uname -r
        OUTPUT_VARIABLE KERNEL_RELEASE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Find the headers
set(KERNEL_BUILD_DIR /lib/modules/${KERNEL_RELEASE}/build)

message(STATUS "Kernel release: ${KERNEL_RELEASE}")
message(STATUS "Kernel headers: ${KERNEL_BUILD_DIR}")
message(STATUS " CMAKE_CURRENT_BINARY_DIR :${CMAKE_BUILD}")
set(KBUILD_CMD make -C ${KERNEL_BUILD_DIR} modules M=${CMAKE_CURRENT_BINARY_DIR} src=${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "KBUILD_CMD ${KBUILD_CMD}")

file(GLOB DRIVER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

set(KBUILD_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Kbuild)
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Kbuild)
    file(WRITE ${KBUILD_FILE} "")
endif ()

file(READ ${KBUILD_FILE} KBUILD_CONTENTS)

foreach (DRIVER_FILE ${DRIVER_FILES})
    get_filename_component(FILE_NAME ${DRIVER_FILE} NAME_WE)
    add_custom_command(OUTPUT ${FILE_NAME}.ko
            COMMAND ${KBUILD_CMD}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS ${FILE_NAME} VERBATIM
    )
    string(FIND "${KBUILD_CONTENTS}" "obj-m += ${FILE_NAME}.o" POSITION)
    if(${POSITION} EQUAL -1)
        file(APPEND ${KBUILD_FILE} "obj-m += ${FILE_NAME}.o\n")
    endif()
    add_custom_target(${FILE_NAME} ALL DEPENDS ${FILE_NAME}.ko)
endforeach ()
