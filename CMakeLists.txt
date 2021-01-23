# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
	message("On ${CMAKE_HOST_SYSTEM_NAME}, CMake 3.14 is the minimum required version.")
	cmake_minimum_required (VERSION 3.14)
else()
	message("On ${CMAKE_HOST_SYSTEM_NAME}, CMake 3.10 is the minimum required version.")
	cmake_minimum_required (VERSION 3.10)
endif()

project ("QtUIXmlCleaner")

include(CTest)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include sub-projects.
add_subdirectory ("QtUIXmlCleaner")

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "Pioneer Library System")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/PackageDescription.txt")
#set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/QtUIXMLCleaner/NSIS_HeaderImage150x57.bmp")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/chennes/QtUIXMLCleaner")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_EXECUTABLES QtUIXmlCleaner QtUIXmlCleaner)

include(CPack)
