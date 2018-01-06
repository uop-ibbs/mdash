# $Id: CMakeLists.txt 109 2017-06-29 16:21:24Z dw $

message("-- Configuring cmdlib")

set(sources
    exception.cpp
    pca.cpp
)

add_library(cmdlib ${sources})

include(FindPkgConfig OPTIONAL RESULT_VARIABLE PkgConfig)

if (NOT PkgConfig-NOTFOUND)
    pkg_check_modules(EIGEN3 eigen3)
    include_directories(${EIGEN3_INCLUDE_DIRS})
endif()

if (NOT EIGEN3_FOUND)
    find_package(Eigen3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

include_directories(..)
