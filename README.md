# QtUIXmlCleaner
A small GUI app to clean a Qt UI file so that it is suitable for use in a text-based version control system.

Based on a [discussion at the FreeCAD Forums](https://forum.freecadweb.org/viewtopic.php?f=10&t=54503), and a [Python script](https://github.com/davidosterberg/Qt-UI-file-sorter) by @davidosterberg.

## Installing on Windows
On GitHub navigate to the Releases page: a .exe installer is available for the releases: download and run it. 

## Building from source
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
