# MIT License
#
# Copyright(c) 2021 Chris Hennes <chennes@pioneerlibrarysystem.org>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
	cmake_minimum_required (VERSION 3.14)
	# For using generators in the install() command to execute windeployqt
else()
	cmake_minimum_required (VERSION 3.11)
	# For using FetchContent to pull the Catch2 test code from GitHub
endif()

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 2)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
project ("QtUIXmlCleaner" VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(CPP20 "Activate C++20 code paths." OFF)
if(CPP20)
	set(CMAKE_CXX_STANDARD 20)
else()
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

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
set(CPACK_PACKAGE_CHECKSUM "SHA256")
set(CPACK_PACKAGE_EXECUTABLES QtUIXmlCleaner QtUIXmlCleaner)

include(CPack)
