# CMakeList.txt : CMake project for QtUIXmlCleaner
#

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Add source to this project's executable.
add_executable (QtUIXmlCleaner "QtUIXmlCleaner.cpp" "QtUIXmlCleaner.h" "MainWindow.ui" "MainWindow.h" "MainWindow.cpp")

target_link_libraries(QtUIXmlCleaner Qt5::Widgets)

install(TARGETS QtUIXmlCleaner DESTINATION bin)

if(WIN32)
    include(Windeployqt)
    windeployqt(QtUIXmlCleaner)
endif()
