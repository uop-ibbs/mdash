# $Id: configure.ac 134 2017-12-19 17:18:22Z dw $
#
# Process this file with "autoconf -I/usr/share/aclocal" to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([mdash],[3.1.0])
AC_CONFIG_SRCDIR([src/dash/main.cpp])

AC_LANG(C++)

dnl Check for enable-debug
m4_include([ax_check_enable_debug.m4])
AX_CHECK_ENABLE_DEBUG

AC_PROG_MKDIR_P
AC_PROG_INSTALL

dnl Check for compiler
AC_PROG_CXX

dnl Checks for compiler flags
m4_include([ax_check_preproc_flag.m4])

AX_CHECK_PREPROC_FLAG([-MM], [DEPFLAGS="-MM"], [DEPFLAGS="-M"])

m4_include([ax_require_defined.m4])
m4_include([ax_append_flag.m4])
m4_include([ax_cflags_warn_all.m4])

AX_CXXFLAGS_WARN_ALL(CXX_WARNINGS)

m4_include([ax_check_compile_flag.m4])

AX_CHECK_COMPILE_FLAG([-Wextra], [CXX_WARNINGS="$CXX_WARNINGS -Wextra"])
AX_CHECK_COMPILE_FLAG([-Wpedantic], [CXX_PEDANTIC="-Wpedantic"])

AX_CHECK_COMPILE_FLAG([-std=c++11], [CXX_STD="-std=c++11"])

if test "x$CXX_STD" = x; then
    AX_CHECK_COMPILE_FLAG([-std=c++0x], [CXX_STD="-std=c++0x"],
        AC_MSG_ERROR([*** A compiler with support for C++11 language features is required.]))
fi

if test "x$ax_enable_debug" = "xno"; then
    if test "x$GXX" = "xyes" ; then
        CXX_OPTIMIZE="-O3"
    else
        CXX_OPTIMIZE="-O"
    fi
else
    CXX_OPTIMIZE=""
fi

if `echo $CXXFLAGS | grep -- "-O" >/dev/null`; then
    dnl don't overide -O flags in user-specified CXXFLAGS
    CXX_OPTIMIZE=""
fi

dnl Decide whether to build AMBER interface
AC_ARG_ENABLE([amber],
    [AS_HELP_STRING([--disable-amber],[do not build the AMBER interface])],
    [enable_amber=${enableval}],
    [enable_amber=yes])

if test "x$enable_amber" = "xno"; then
    BUILD_AMBER='#'
    AMBER_DEFINES="-DNOAMBER"
    BOOST_VERSION=1.53
else
    BUILD_AMBER=
    BOOST_VERSION=1.64
    BOOST_WARNINGS="-Wno-unused-parameter"
fi

dnl Check for Boost libraries
m4_include([ax_boost_base.m4])
m4_include([ax_boost_program_options.m4])
m4_include([ax_boost_filesystem.m4])
m4_include([ax_boost_system.m4])
m4_include([ax_boost_regex.m4])
m4_include([ax_boost_iostreams.m4])

AX_BOOST_BASE([$BOOST_VERSION],[BOOST_INCLUDES="$BOOST_CPPFLAGS"],[AC_MSG_ERROR([Can't find the Boost libraries.])])

AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_FILESYSTEM
AX_BOOST_SYSTEM
AX_BOOST_REGEX
AX_BOOST_IOSTREAMS

dnl Check for pkg-config
m4_include([pkg.m4])
PKG_PROG_PKG_CONFIG

dnl Check for Eigen header files
AC_ARG_WITH(eigen_include, AS_HELP_STRING([--with-eigen-include=PATH], [location of Eigen include files]))

dnl Check user-supplied location if given, otherwise check pkg-config location
if test "x$with_eigen_include" != "x"; then
    AC_CHECK_HEADERS([$with_eigen_include/Eigen/Core],[have_eigen3=yes],[have_eigen3=no])

    if test "x$have_eigen3" = "xyes"; then
        EIGEN_INCLUDES="-I$with_eigen_include"
    fi
else
    PKG_CHECK_MODULES([EIGEN],[eigen3],[have_eigen3=yes],[have_eigen3=no])

    if test "x$have_eigen3" = "xyes"; then
        EIGEN_INCLUDES="$EIGEN_CFLAGS"
    fi
fi

if test "x$have_eigen3" = "xno"; then
    AC_MSG_ERROR([Can't find the Eigen header files. Use --with-eigen-include to specify their location.])
fi

dnl Check for sufficiently recent Eigen version
dnl Eigen 3.2.0 (supplied with Ubuntu 14.04) throws exception in PCA ctor
AC_MSG_CHECKING([for EIGEN version 3.2.1 or later])

save_CXXFLAGS="$CXXFLAGS"
CXXFLAGS="$EIGEN_CFLAGS"

AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
    @%:@include <Eigen/Core>
    ]], [[
    #if EIGEN_VERSION_AT_LEAST(3,2,1)
    // OK
    #else
    #  error EIGEN version is too old
    #endif
    ]])],[
        AC_MSG_RESULT(yes)
    ],[
        AC_MSG_RESULT(no)
        AC_MSG_ERROR([Eigen version 3.2.1 or later is required.])
    ])

CXXFLAGS="$save_CXXFLAGS"

dnl Decide whether to build GUI or CLI
AC_ARG_ENABLE([gui],
    [AS_HELP_STRING([--disable-gui],[do not build the graphical interface])],
    [enable_gui=${enableval}],
    [enable_gui=yes])

if test "x$enable_gui" = "xyes"; then
    BUILD_GUI_TRUE=
    BUILD_GUI_FALSE='#'
else
    BUILD_GUI_TRUE='#'
    BUILD_GUI_FALSE=
fi

dnl Check for wxWidgets
dnl sets $WX_CPPFLAGS $WX_CXXFLAGS $WX_LIBS

dnl uncomment next line on ubuntu
#m4_include([wxwin.m4])
dnl uncomment next line on rhel
m4_include([wxwin3.m4])

reqwx=3.0.0

AC_ARG_WITH(wx-static,AS_HELP_STRING([--with-wx-static],[link with static wxWidgets libraries]))

wx_static=""
if test "x$with_wx_static" = "xyes"; then
    wx_static="--static"
fi

wx_args="$wx_static"

#WX_DEBUG_CONFIGURE=1
WX_CONFIG_OPTIONS

if test "x$enable_gui" = "xyes"; then
    WX_CONFIG_CHECK([$reqwx],[wxWin=1],,[base,core,adv,html,gl],[$wx_args])

    if test "$wxWin" != 1; then
        AC_MSG_ERROR([
            The requested wxWidgets configuration could not be found.
            If the wx-config script is installed but not on the path,
            specify its location with the --wx-config option, and
            ensure that the wxWidgets version is $reqwx or above.
        ])
    fi
fi

#WX_STANDARD_OPTIONS_SUMMARY_MSG

dnl Check for GL, GLU and GLEW
m4_include([ax_save_flags_with_prefix.m4])
m4_include([ax_restore_flags_with_prefix.m4])
m4_include([ax_check_gl.m4])
m4_include([ax_check_glu.m4])

if test "x$enable_gui" = "xyes"; then
    AX_CHECK_GL([have_gl=yes],AC_MSG_ERROR(["Can't find a working GL installation"]))
    AX_CHECK_GLU([have_glu=yes],AC_MSG_ERROR(["Can't find a working GLU installation"]))
    PKG_CHECK_MODULES([GLEW],[glew],[],[AC_MSG_ERROR([Can't find GLEW with pkg-config.])])
fi

dnl Check for GLM headers
AC_ARG_WITH(glm_include, AS_HELP_STRING([--with-glm-include=PATH], [location of GLM include files]))

if test "x$enable_gui" = "xyes"; then
    # Check user-supplied location if given, otherwise check standard locations
    if test "x$with_glm_include" != "x"; then
        AC_CHECK_HEADER([$with_glm_include/glm/glm.hpp],[have_glm=yes],[have_glm=no])

        if test "x$have_glm" = "xyes"; then
            GLM_INCLUDES="-I$with_glm_include"
        fi
    else
        AC_CHECK_HEADER([glm/glm.hpp],[have_glm=yes],[have_glm=no])
    fi

    if test "x$have_glm" = "xno"; then
        AC_MSG_ERROR([Can't find the GLM header files. Use --with-glm-include to specify their location.])
    fi
fi

AC_SUBST(DEPFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(CXX_STD)
AC_SUBST(CXX_WARNINGS)
AC_SUBST(CXX_PEDANTIC)
AC_SUBST(CXX_SECURITY)
AC_SUBST(CXX_OPTIMIZE)
AC_SUBST(AMBER_DEFINES)
AC_SUBST(BOOST_INCLUDES)
AC_SUBST(BOOST_WARNINGS)
AC_SUBST(EIGEN_INCLUDES)
AC_SUBST(BUILD_GUI_TRUE)
AC_SUBST(BUILD_GUI_FALSE)
AC_SUBST(GLM_INCLUDES)
AC_SUBST(BUILD_AMBER)

AC_CONFIG_FILES([Makefile src/dash/Makefile src/cmdlib/Makefile src/wxfreechart/src/Makefile examples/Makefile test/Makefile])
AC_OUTPUT
