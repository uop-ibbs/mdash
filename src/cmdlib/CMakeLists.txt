# $Id: CMakeLists.txt 109 2017-06-29 16:21:24Z dw $

message("-- Configuring cmdlib")

set(sources
    exception.cpp
    pca.cpp
)

add_library(cmdlib ${sources})

find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(cmdlib Eigen3::Eigen)

include_directories(..)
