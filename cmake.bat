REM Edit the paths to match your installation of the prerequisites

SET PREREQUISITEDIR="C:\Software"

cmake -G "NMake Makefiles"^
 -DCMAKE_BUILD_TYPE=release^
 -DBOOST_ROOT=%PREREQUISITEDIR%\boost_1_76_0^
 -DBoost_USE_STATIC_LIBS=ON^
 -DEigen3_DIR=%PREREQUISITEDIR%\Eigen3\share\eigen3\cmake^
 -DGLEW_ROOT=%PREREQUISITEDIR%\glew-2.1.0^
 -DGLEW_STATIC=ON^
 -DGLM_INCLUDE_DIR=%PREREQUISITEDIR%\glm-0.9.9.8^
 -DwxWidgets_ROOT_DIR=%PREREQUISITEDIR%\wxWidgets-3.1.5^
 -DwxWidgets_CONFIGURATION=msw^
 ..
