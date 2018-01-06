# Locate GLM headers
#
# Input
#    GLM_INCLUDE - path searched before standard locations
#
# Output
#    GLM_INCLUDE_DIR - location of glm/glm.hpp, if found
#

FIND_PATH(GLM_INCLUDE_DIR "glm/glm.hpp" ${GLM_INCLUDE})
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLM DEFAULT_MSG GLM_INCLUDE_DIR)
