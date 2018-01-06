# Locate Eigen3 headers
#
# Input
#    EIGEN3_INCLUDE - path searched before standard locations
#
# Output
#    EIGEN3_INCLUDE_DIR - location of "Eigen/Core", if found
#

FIND_PATH(EIGEN3_INCLUDE_DIR "Eigen/Core" PATHS ${EIGEN3_INCLUDE} PATH_SUFFIXES eigen3)
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EIGEN3 DEFAULT_MSG EIGEN3_INCLUDE_DIR)
