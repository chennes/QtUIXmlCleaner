# CMakeList.txt : CMake project for QtUIXmlCleaner
#

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(UI_SRCS
    "QtUIXmlCleaner.cpp" 
    "QtUIXmlCleaner.h" 
    "MainWindow.ui" 
    "MainWindow.h" 
    "MainWindow.cpp"
)

set(CPP_SRCS
    "Cleaner.cpp" 
    "Cleaner.h" 
    "GridItem.cpp" 
    "GridItem.h" 
    "Helpers.cpp" 
    "Helpers.h"
)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/QtUIXmlCleaner.rc")
add_executable (QtUIXmlCleaner WIN32 MACOSX_BUNDLE
    ${UI_SRCS}
    ${CPP_SRCS}
    "ui_icon.svg"
    ${APP_ICON_RESOURCE_WINDOWS}
)

target_link_libraries(QtUIXmlCleaner Qt5::Widgets)

install(TARGETS QtUIXmlCleaner DESTINATION bin)

if(WIN32)
    include(Windeployqt)
    windeployqt(QtUIXmlCleaner)
endif()

if(BUILD_TESTING)
  add_subdirectory(Tests)
endif()