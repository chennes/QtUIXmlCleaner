# QtUIXmlCleaner
A small GUI app to clean a Qt UI file so that it is suitable for use in a text-based version control system. It is capable of re-ordering the elements in a QGridLayout to be in row-column order, and of removing some XML properties that are sometimes (though not always!) extraneous. Use caution when removing the properties, and verify that no UI behavior has changed unexpectedly.

![Screenshot of QtUIXmlCleaner](Screenshot.png)

Based on a [discussion at the FreeCAD Forums](https://forum.freecadweb.org/viewtopic.php?f=10&t=54503), and a [Python script](https://github.com/davidosterberg/Qt-UI-file-sorter) by @davidosterberg.

## Installing on Windows
Download either the standalone 7-zip file or the installer executable file from the [releases page](https://github.com/chennes/QtUIXmlCleaner/releases/tag/v1.0.2).

## Building from source

### Important CMake options
This software uses the CMake cross-platform build system. Some CMake variables that control the compilation of various features are:
* `Qt5_DIR` - The location of the cmake folder in your Qt5 installation.
* `BUILD_TESTING` - Defaults to true, downloads Catch2 and builds the unit testing framework.
* `BUILD_DOCUMENTATION` - Defaults to false. if true, and you have Doxygen installed, build the developer documentation.
* `CMAKE_INSTALL_PREFIX` - If you build the install target, this is the location of the compiled binaries.
* `WINDEPLOYQT_EXECUTABLE` - Windows only. Sets the location of windeployqt.exe, which you should find in your Qt binaries directory.

### Windows
Version 1.0 of the software was developed on Windows 10 using Visual Studio 2019, CMake >=3.14, and Qt5. To build the distributable package you will also need NSIS. To build the source:
1. Clone this repository
1. Run CMake on the resulting directory
    * Set Qt5_DIR to the location of your Qt5Config.cmake file (if using the FreeCAD LibPack, that will be $LIBPACKDIR/lib/cmake/Qt5/)
    * Set WINDEPLOYQT_EXECUTABLE to the location of windeployqt.exe (if using the FreeCAD LibPack, that will be $LIBPACKDIR/bin/windeployqt.exe)
    * Optionally, set CMAKE_INSTALL_PREFIX to an installation directory
1. Open the generated project file in Visual Studio
1. Build the ALL_BUILD target and note the final location of the .exe
1. Right click on the ALL_BUILD target, choose "Properties", navigate to "Debugging", and set Command to the built executable.
1. You can now run from the debugger, e.g. by pressing F5, etc.
1. (Optional) build the INSTALL target. The executable and all necessary auxilliary files will be copied to CMAKE_INSTALL_PREFIX.
1. (Optional) build the PACKAGE target. A distributable installer executable will be created in your build folder.

### Linux
You will need a recent C++17 compiler, CMake >= 3.11, and Qt5. 
1. Clone this repository
1. Create an empty build directory on your system in a convenient location
1. In a terminal, change to the build directory
1. Run `cmake /path/to/clone`
1. Run `make`
1. (Optional) Run `make test` to verify that everything is working as expected
1. (Optional) Run `make install`
