# $Id: CMakeLists.txt 130 2017-11-28 14:41:54Z dw $

message("-- Configuring mdash")

set(common_sources
    circular.cpp
    dash.cpp
    dash_cli.cpp
    dash_exception.cpp
    dash_options.cpp
    dash_sim.cpp
    state_trajectory.cpp
    torsion_data.cpp
    trajectory.cpp
)

set(gui_sources
    bout_panel.cpp
    dash_app.cpp
    dash_fbgui.cpp
    dash_gui.cpp
    dash_options_dialog.cpp
    dash_state_panel.cpp
    frequency_panel.cpp
    histogram.cpp
    log.cpp
    manual_gui.cpp
    pca_legend.cpp
    pca_options_dialog.cpp
    pca_panel.cpp
    plot_canvas_2d.cpp
    plot_canvas_3d.cpp
    repex_state_panel.cpp
    scree_plot_panel.cpp
    similarity_panel.cpp
    summary_panel.cpp
    tiled_pager_panel.cpp
    tiled_pager_panel_fbui.cpp
    torsion_histogram_panel.cpp
    torsion_state_panel.cpp
    trackball_canvas.cpp
    trajectory_options_dialog.cpp
    trajectory_panel.cpp
    viewer_gui.cpp
    viewer_options.cpp
)

set(cli_sources
    main.cpp
)

set(amber_sources
    amber_options.cpp
    amber_trajectory_reader.cpp
    external.cpp
)

set(amber_gui_sources
    amber_dialog.cpp
)

option(BUILD_GUI "Build graphical interface" ON)
option(BUILD_AMBER "Build AMBER interface" ON)
option(GLEW_STATIC "Link to static GLEW library" OFF)

if (GLEW_STATIC)
    add_definitions(-DGLEW_STATIC)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(BUILD_AMBER OFF)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:LIBCMT")
endif()

if (BUILD_AMBER)
    set(DASH_BOOST_VERSION 1.64)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-Wno-unused-parameter)
    endif()
else()
    set(DASH_BOOST_VERSION 1.50)
endif()

if (BUILD_GUI)
    if(BUILD_AMBER)
        add_executable(mdash ${common_sources} ${gui_sources} ${amber_sources} ${amber_gui_sources})
    else()
        add_executable(mdash ${common_sources} ${gui_sources})
    endif()

    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set_target_properties(mdash PROPERTIES WIN32_EXECUTABLE 1)
    endif()
else()
    if (BUILD_AMBER)
        add_executable(mdash ${common_sources} ${cli_sources} ${amber_sources})
    else()
        add_executable(mdash ${common_sources} ${cli_sources})
    endif()
endif()

if (NOT BUILD_GUI)
    add_definitions(-DNOGUI)
endif()

if (NOT BUILD_AMBER)
    add_definitions(-DNOAMBER)
endif()

include_directories(..)
target_link_libraries(mdash cmdlib)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(Boost ${DASH_BOOST_VERSION} REQUIRED program_options filesystem system regex iostreams bzip2 zlib)
else()
    find_package(Boost ${DASH_BOOST_VERSION} REQUIRED program_options filesystem system regex iostreams)
endif()

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(mdash ${Boost_LIBRARIES})

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND Boost_USE_STATIC_LIBS)
    target_link_libraries(mdash bz2 z)
endif()

include(FindPkgConfig OPTIONAL RESULT_VARIABLE PkgConfig)

if (NOT PkgConfig-NOTFOUND)
    pkg_check_modules(EIGEN3 eigen3)
    include_directories(${EIGEN3_INCLUDE_DIRS})
endif()

if (NOT EIGEN3_FOUND)
    find_package(Eigen3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

if (BUILD_GUI)
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(wxWidgets_EXCLUDE_COMMON_LIBRARIES TRUE)
        find_package(wxWidgets REQUIRED adv base core html gl png zlib)
    else()
        find_package(wxWidgets REQUIRED adv base core html gl)
    endif()

    include(${wxWidgets_USE_FILE})
    target_link_libraries(mdash ${wxWidgets_LIBRARIES})

    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(mdash ${OPENGL_LIBRARIES})

    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(mdash ${GLEW_LIBRARIES})

    find_package(GLM REQUIRED)
    include_directories(${GLM_INCLUDE_DIR})

    include_directories(../wxfreechart/include)
    target_link_libraries(mdash wxfreechart)
endif()

install(TARGETS mdash DESTINATION ${BIN_INSTALL_DIR})
install(PROGRAMS amberdash DESTINATION ${BIN_INSTALL_DIR})
install(FILES mdash.pdf mdash.html DESTINATION ${DOC_INSTALL_DIR})

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
  install(FILES mdash.info DESTINATION ${INFO_INSTALL_DIR})
  install(FILES mdash.1 amberdash.1 DESTINATION ${MAN1_INSTALL_DIR})
endif()
