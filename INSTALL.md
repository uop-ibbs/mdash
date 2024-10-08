MDASH, Release 3.1.2, August 2024.
===================================

This is a maintenance release to enable MDASH to be built with the
latest versions of its third-party dependencies. There are no
substantive changes to the software itself. This will be the final
numbered release. Future changes will be made only to the source code.


Downloading and verifying the release files
-------------------------------------------

The latest release is provided at
[GitHub](https://github.com/uop-ibbs/mdash/releases/latest) as
source code archives

    mdash-3.1.2.tar.bz2
    mdash-3.1.2.zip

a Flatpak

    mdash-3.1.2.flatpak

and a Windows installer

    mdash-3.1.2.exe

The file `SHA512SUMS` contains the SHA512 checksum for each file. To
verify the checksums use the command

    sha512sum -c SHA512SUMS --ignore-missing

The release files are signed with the
[GPG public key](https://raw.githubusercontent.com/uop-ibbs/mdash/master/pubkey2.asc)
with primary key fingerprint 96AB F6CF 3930 C28A 2814 76B7 0422 9F49 21A6 6DE4
and subkey fingerprint 5048 5F1B 6AA9 1C89 DACA A97A 9C63 1370 82B1 05E5.
The signatures are in the files with .asc extensions.

To verify a signature, first import the public key:

    gpg --import pubkey2.asc

then use the command:

    gpg --verify mdash-x.y.z.tar.bz2.asc

replacing the name of the file as appropriate. If all is well this
should produce output along the lines of:

    gpg: Signature made Fri 17 Sep 2021 14:50:00 BST
    gpg:                using RSA key 50485F1B6AA91C89DACAA97A9C63137082B105E5
    gpg: Good signature from "David Whitley (Github Signing Key) <31848565+dcwhitley@users.noreply.github.com>" [unknown]
    gpg: WARNING: This key is not certified with a trusted signature!
    gpg:          There is no indication that the signature belongs to the owner.
    Primary key fingerprint: 96AB F6CF 3930 C28A 2814  76B7 0422 9F49 21A6 6DE4
         Subkey fingerprint: 5048 5F1B 6AA9 1C89 DACA  A97A 9C63 1370 82B1 05E5

The warning is expected and can be ignored.

(Note that the earlier version 3.1.0 release files were signed with the [GPG
public key](https://raw.githubusercontent.com/uop-ibbs/mdash/master/pubkey.asc) with
fingerprint 0C66 53A8 6507 A92D CD07 B878 BBD9 D1DB 4E10 D89E.)


Installing the Linux Flatpak binary
-----------------------------------

First ensure that Flatpak is installed from your system's software
manager (check that the `flatpak` command is present - some
distributions install it by default, some don't). Instructions for
each Linux distribution are provided at
[Flatpak](https://flatpak.org/setup/).

To install the MDASH Flatpak use the command:

    flatpak install mdash-3.1.2.flatpak

This should place an MDASH icon among your system's applications which
will launch the MDASH gui. Alternatively, use the command:

    flatpak run io.github.uop_ibbs.Mdash [mdash options]


Installing the Windows binary package
-------------------------------------

Windows users should run the file mdash-3.1.2.exe to install MDASH
under `C:\Program Files (x86)\mdash-3.1.2`.


Extracting the source code
--------------------------

Use one of the commands

    tar xf mdash-x.y.z.tar.bz2
    unzip mdash-x.y.z.zip

to unpack the archive into a directory `mdash-x.y.z`.


Building MDASH on Windows
-------------------------

If you wish to use MDASH on Windows you are *strongly* advised to
use the binary installer and avoid building from the source code.

The simplest way to build MDASH on Windows is to use the [MSYS2
environment](https://www.msys2.org/). This is a much-improved
successor to Cygwin and the various versions of MinGW, and is highly
recommended. See the [Distribution-specific notes](#user-content-distribution-specific-notes)
for details on setting up MSYS2 and installing the prerequisites, then
follow the instructions for installing on GNU/Linux.

Alternatively, masochists may build MDASH using the Visual Studio
command-line tools by following the instructions in
[Building on Windows with Visual Studio](#user-content-building-on-windows-with-visual-studio).


Prerequisites
-------------

The following packages are required to build MDASH from source code.
They are provided by the package managers in the major GNU/Linux
distributions.

### [Boost](<http://www.boost.org>)

In addition to the Boost headers, the Boost program-options,
filesystem and iostreams libraries are required.

The GNU/Linux build includes an interface to read trajectories
generated by [AMBER](http://ambermd.org). This requires version 1.64
of the Boost libraries, released April 2017. If this is not yet
available via your package manager, it must be installed manually
following the instructions on the Boost website. Only the required
libraries (program-options, filesystem and iostreams) need to be
compiled, though others may be included by the build process as
dependencies. The AMBER interface can be disabled by using the
'--disable-amber' configure option, in which case an earlier version
of the Boost libraries will suffice.


### [Eigen](<http://eigen.tuxfamily.org>)

The Eigen linear algebra library is used to calculate principal
components.


### Compression and image libraries (zlib, bzip2, png)

The zlib, bzip2, and png development packages are required to deal
with compressed input files and to save images from the GUI in PNG
format.


### OpenGL (GL, GLEW, GLM)

OpenGL is required for the display of principal components in the
graphical version of MDASH. It is not required for the command-line
version of MDASH, which is built by using the `--disable-gui`
configure option.

GLEW, the OpenGL Extension Wrangler Library, is available from
<http://glew.sourceforge.net/>.

GLM, the OpenGL Maths Library, is a header-only library available from
<http://glm.g-truc.net>.


### [wxWidgets](<http://www.wxwidgets.org>)

The wxWidgets toolkit is required for the graphical version of
MDASH. It is not required for the command-line version of MDASH, which
is built by using the `--disable-gui` configure option.

There was a period during which the stable version of wxWidgets failed
to keep pace with changes in the Open GL libraries and the adoption of
Wayland in place of X11, requiring a more recent version of wxWidgets
from the unstable branch than the stable version provided with the
main Linux distribution was required (>= 3.1.5 at least). Older
versions wxWidgets, particularly with Wayland caused the MDASH GUI to
segfault on startup. In that case the latest version of wxWidgets
should be built from source. A workaround for RHEL is suggested in the
[Distribution-specific
notes](#user-content-distribution-specific-notes). Recent Linux
distributions with wxWidgets >= 3.2.2 should be fine.

If wxWidgets is built from source, ensure that OpenGL support is
included (use the `--with-opengl` option when configuring wxWidgets).


### [wxFreeChart](<http://wxcode.sourceforge.net/components/freechart/>)

A (mildly) modified version of wxFreeChart is provided in the
`mdash-x.y.z/src/wxfreechart` directory. This code is distributed
under the wxWindows Library Licence, Version 3.1 (GPLv2+ with
an exception allowing static linking).


### Installing the prerequisites

The following commands can be used to install the prerequisites.

RHEL-8.x:

(Enable the Power Tools and EPEL repositories.)

    sudo dnf install boost169-devel boost169-program-options \
        boost169-filesystem boost169-iostreams eigen3-devel zlib-devel \
        bzip2-devel libpng-devel mesa-libGL-devel mesa-libGLU-devel \
        glew-devel glm-devel


RHEL-7.x:

(Enable the EPEL repository.)

    sudo yum install boost169-devel boost169-program-options \
            boost169-filesystem boost169-iostreams eigen3-devel zlib-devel \
            bzip2-devel libpng-devel mesa-libGL-devel mesa-libGLU-devel \
            glew-devel glm-devel wxGTK3 wxGTK3-devel wxGTK3-gl


Ubuntu-20.04:

    sudo apt install libboost-dev libboost-program-options-dev \
        libboost-filesystem-dev libboost-iostreams-dev libeigen3-dev \
        libbz2-dev zlib1g-dev libpng-dev libgl1-mesa-dev \
        libglu1-mesa-dev libglew-dev libglm-dev libwxgtk3.0-gtk3-dev


OpenSUSE Leap 15.x:

    sudo zypper install boost-devel libboost_program_options-devel \
        libboost_filesystem-devel libboost_iostreams-devel eigen3-devel \
        libbz2-devel Mesa-libGL-devel glu-devel glew-devel glm-devel \
        wxWidgets-3_0-devel


Building MDASH on GNU/Linux
---------------------------

Follow the usual incantation:

    cd mdash-x.y.z
    mkdir build
    cd build
    ../configure
    make
    make check
    make install

The configure step may fail if the prerequisites are not installed in
standard locations. In that case, use the command

    ../configure --help

to list the options available, and re-run configure with the
appropriate paths specified.

The default build creates a program with a graphical interface. To
build a command-line only version, not requiring any graphics
libraries, use:

    ../configure --disable-gui

The GNU/Linux build includes an interface to read trajectories
generated by AMBER (http://ambermd.org). This requires the AmberTools
`cpptraj` program to be present on the PATH. To disable this feature,
use:

    ../configure --disable-amber


`make` builds the executable `mdash-x.y.z/build/src/dash/mdash`. The
Perl script `amberdash` is provided in `mdash-x.y.z/src/dash`. These
can be run in-place or moved to somewhere more convenient. The files
`mdash.pdf`, `mdash.html` and `mdash.info` in the directory
`mdash-x.y.z/src/mdash` contain documentation in the indicated
formats.

`make check` runs some rudimentary test cases. Depending on the
version of Eigen3, some of the checks may fail with differences in the
signs of the principal components. As the PCs are only defined up to a
change of sign, these may be ignored.

`make install` is optional. It copies the programs `mdash` and
`amberdash` to `PREFIX/bin`, the pdf and html manuals to
`PREFIX/share/doc/mdash-x.y.z`, and installs the 'info' manual in
`PREFIX/share/info`. This requires write access to the `PREFIX`
directory (specified by the `--prefix` configure option; default
`/usr/local`).

`make uninstall` is also provided.


Building with CMake
-------------------

Support is provided for cmake builds, though this is less well
tested. Follow the standard procedure:

    cd mdash-x.y.z
    mkdir build
    cd build
    cmake ..
    make
    make check
    make install

Aspects of the build are controlled by the following variables
(specified with -D on the cmake command line):

    BUILD_GUI[=ON]
    BUILD_AMBER[=ON]
    BOOST_ROOT        boost installation directory

For example:

    cmake -DBUILD_GUI=OFF -DBOOST_ROOT=/opt/modules/boost/1.76.0 ..


Building on Windows with Visual Studio
--------------------------------------

This should only be considered by experienced developers, it is
definitely not for the faint-hearted. The main obstacle is in setting
up the prerequisites. Although there are relatively few of these, it
is extremely easy to end up with incompatible versions of the Boost
and wxWidgets libraries, so follow these instructions closely. The
strategy is to use a pre-compiled version of the Boost libraries and
build the wxWidgets libraries from source code to match. Start by
creating a folder to contain all the prerequisites, referred to below
as MDASHREQ.

### Boost

From the [Boost home page](www.boost.org) select `More Downloads` then
follow the `Windows Binaries` link. From `DEPENDENCY_VERSIONS.txt`
match your version of Visual Studio to an msvc version. Then download
the 32-bit version of the corresponding Boost libraries. For Visual
Studio 2022, for example, use `Boost_1_85_0_msvc_14.3-32.exe`. Run the
.exe and install the libraries in MDASHREQ.

### wxWidgets

Download the source code for the latest stable release from the wxWidgets
[downloads](https://wxwidgets.org/downloads/) page. Choose the .zip or
.7z archive and uncompress it in MDASHREQ.

Open the Visual Studio x86 Native Tools Command Prompt and run these commands:

    cd MDASHREQ\wxWidgets-3.2.5\build\msw
    nmake /f makefile.vc BUILD=release

replacing the wxWidgets version as appropriate.

### Eigen

Although Eigen is a header-only library, the package must be 'built'
to generate the build files that CMake requires. From the [Eigen home
page](<http://eigen.tuxfamily.org>) download the .zip file for the
latest stable release (3.4.0) and unpack it somewhere other than
MDASHREQ. Open the Visual Studio Native Tools Command Prompt and use
the following commands:

    cd path\to\eigen-3.4.0
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=MDASHREQ\Eigen3 ..
    cmake --build . --target install

### GLEW

From the [GLEW home page](http://glew.sourceforge.net) follow the link
to `Binaries: Windows 32-bit and 64-bit` to download the latest
version (glew-2.2.0-win32.zip). Unpack the .zip file in MDASHREQ.

### GLM

From the [GLM home page](https://github.com/g-truc/glm/releases)
download the .zip file for the latest stable release (glm-1.0.1.zip).
Unpack the .zip file in MDASHREQ.


The result should be a folder containing these subfolders (version
numbers may vary):

    wxWidgets-3.2.5
    boost-1_85_0
    Eigen3
    glew-2.2.0
    glm-1.0.1

### CMake

Download and install the latest stable version of CMake from
https://cmake.org/download/.


With the prerequisites in place, the actual build is straightforward.

	1. Download and unpack the source code distribution
       mdash-x.y.z.zip.

	2. Edit the file `cmake.bat` in the `mdash-x.y.z` directory so
       that the paths match your installation of the prerequisites.
       Optionally, insert a line

           -DCMAKE_INSTALL_PREFIX=c:\<prefix>^

       to install MDASH somewhere other than the default location,
       C:\Program Files (x86), which requires administrator
       privileges.

	3. Open the Visual Studio x86 Native Tools Command Prompt.

	4. In the command window, change to the `mdash-x.y.z` directory
       and run the following commands:

           mkdir build
           cd build
           ..\cmake.bat
           nmake
           nmake install

       The final install step is optional. The executable build\src\dash\mdash.exe
       may simply be moved to somewhere more convenient.


Distribution-specific notes
---------------------------

### RHEL-8.x, RHEL-9.x

If built against the distribution-provided version of wxWidgets the
MDASH GUI will immediately crash with a segfault. Setting the
environment variable

    GDK_BACKEND=x11

before starting MDASH will avoid this.


### RHEL-7.x

The `wx-config` script provided in the EPEL wxWidgets 3.0.x packages
is actually called `wx-config-3.0`. This has to be specified in the
configure command, *i.e.* use

    ../configure --with-wx-config=/usr/bin/wx-config-3.0


### Ubuntu-14.04

A bug in the version of Eigen (3.2.0) distributed with Ubuntu 14.04
causes the PCA calculation to fail with an unhandled exception.
Therefore a later version of Eigen must be used. As Eigen is a
header-only affair, this is easy. Simply download the latest version
of Eigen from eigen.tuxfamily.org, unpack it, and use the configure
option

    ../configure --with-eigen-include=path-to-eigen

where `path-to-eigen` is the parent of the directory named `Eigen`.


### MSYS2

Follow the instructions at https://msys2.github.io/ to install and
update MSYS2. Then use the following command in the MSYS2 UCRT64 shell
to install the build tools and prerequisites for MDASH:

    pacman -S mingw-w64-ucrt-x86_64-gcc \
			  mingw-w64-ucrt-x86_64-make \
			  mingw-w64-ucrt-x86_64-pkgconf \
			  mingw-w64-ucrt-x86_64-boost \
              mingw-w64-ucrt-x86_64-eigen3 \
              mingw-w64-ucrt-x86_64-wxWidgets3.2 \
              mingw-w64-ucrt-x86_64-glew \
              mingw-w64-ucrt-x86_64-glm

To build MDASH, follow the instructions above for installing on
GNU/Linux, specifying the location of the Boost libraries and
disabling the AMBER interface in the configuration step:

    ../configure --with-boost=/ucrt64 --disable-amber

Use the command

	mingw32-make install

to compile, link and install MDASH. The default installation prefix in
the MSYS2 UCRT64 environmant is /ucrt64, so the executable is
installed as /ucrt64/bin/mdash.exe.

The (optional) make check command will fail as the output files
(mdash-3.1.2/build/test/\*.out) will have DOS line endings, whereas
the expected output files (mdash-3.1.2/test/\*.exp) have Unix line
endings. Either inspect the files visually for real differences or
convert the output files with dos2unix and run diff by hand on the
corresponding pairs of files to check them.

The resulting mdash executable is a native Windows program, which can
be run from the MSYS2 UCRT64 shell. It can also be run directly from
Windows, via 'Run' or a Command Window, provided c:\msys64\ucrt64\bin
is added to the PATH environment variable.


Amberdash
---------

The Perl script `amberdash` runs MDASH on trajectories generated by
[Amber](http://ambermd.org). Documentation in POD format is included
in the file. To read it use the command

    perldoc amberdash

The script calls `mdash` and `cpptraj`. If they are not on the PATH,
specify their full pathnames at the top of the script.
