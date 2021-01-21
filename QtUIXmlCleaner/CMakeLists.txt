# CMakeList.txt : CMake project for QtUIXmlCleaner, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Add source to this project's executable.
add_executable (QtUIXmlCleaner "QtUIXmlCleaner.cpp" "QtUIXmlCleaner.h" "MainWindow.ui" "MainWindow.h" "MainWindow.cpp")

target_link_libraries(QtUIXmlCleaner Qt5::Widgets)