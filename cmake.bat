REM Edit the paths to match your installation of the prerequisites

SET PREREQUISITEDIR="C:\Software"

cmake -G "NMake Makefiles"^
 -DCMAKE_BUILD_TYPE=release^
 -DBOOST_ROOT=%PREREQUISITEDIR%\boost_1_64_0^
 -DBoost_USE_STATIC_LIBS=ON^
 -DEIGEN3_INCLUDE_DIR=%PREREQUISITEDIR%\eigen-3.3.3^
 -DGLEW_INCLUDE_DIR=%PREREQUISITEDIR%\glew-2.0.0\include^
 -DGLEW_LIBRARY=%PREREQUISITEDIR%\glew-2.0.0\lib\Release\Win32\glew32s.lib^
 -DGLEW_STATIC=ON^
 -DGLM_INCLUDE_DIR=%PREREQUISITEDIR%\glm-0.9.8.4^
 -DwxWidgets_ROOT_DIR=%PREREQUISITEDIR%\wxWidgets-3.1.0^
 -DwxWidgets_CONFIGURATION=msw^
 ..
