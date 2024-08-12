REM Edit the paths to match your installation of the prerequisites

SET PREREQUISITEDIR="C:\Software"

cmake -G "NMake Makefiles"^
 -DCMAKE_BUILD_TYPE=release^
 -DBOOST_ROOT=%PREREQUISITEDIR%\boost_1_85_0^
 -DBoost_USE_STATIC_LIBS=ON^
 -DEigen3_DIR=%PREREQUISITEDIR%\Eigen3\share\eigen3\cmake^
 -DGLEW_ROOT=%PREREQUISITEDIR%\glew-2.2.0^
 -DGLEW_STATIC=ON^
 -DGLM_INCLUDE_DIR=%PREREQUISITEDIR%\glm-1.0.1^
 -DwxWidgets_ROOT_DIR=%PREREQUISITEDIR%\wxWidgets-3.2.5^
 -DwxWidgets_CONFIGURATION=msw^
 ..
