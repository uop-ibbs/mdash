# $Id: CMakeLists.txt 132 2017-12-19 15:01:25Z dw $

cmake_minimum_required(VERSION 3.1.0)
cmake_policy(SET CMP0048 NEW)

project(MDash VERSION 3.1.0 LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

set(BIN_INSTALL_DIR       bin)
set(DOC_INSTALL_DIR       share/doc/mdash-${PROJECT_VERSION})
set(INFO_INSTALL_DIR      share/info)
set(MAN1_INSTALL_DIR      share/man/man1)
set(EXAMPLES_INSTALL_DIR  share/doc/mdash-${PROJECT_VERSION}/examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_subdirectory(src/cmdlib)
add_subdirectory(src/dash)
add_subdirectory(examples)
add_subdirectory(test)

if (BUILD_GUI)
    add_subdirectory(src/wxfreechart/src)
endif()

install(FILES README.md INSTALL.md LICENSE DESTINATION ${DOC_INSTALL_DIR})
