# CMakeList.txt : CMake project for QtUIXmlCleaner
#

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Xml REQUIRED)

# Add source to this project's executable.

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/QtUIXmlCleaner.rc")
add_executable (QtUIXmlCleaner WIN32
    "QtUIXmlCleaner.cpp" 
    "QtUIXmlCleaner.h" 
    "MainWindow.ui" 
    "MainWindow.h" 
    "MainWindow.cpp" 
    "Cleaner.cpp" 
    "Cleaner.h" 
    "GridItem.cpp" 
    "GridItem.h" 
    "Helpers.cpp" 
    "Helpers.h" 
    "ui_icon.svg"
    ${APP_ICON_RESOURCE_WINDOWS}
)

target_link_libraries(QtUIXmlCleaner Qt5::Widgets Qt5::Xml)

install(TARGETS QtUIXmlCleaner DESTINATION bin)

if(WIN32)
    include(Windeployqt)
    windeployqt(QtUIXmlCleaner)
endif()
