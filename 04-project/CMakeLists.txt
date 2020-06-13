##
## meteodata-git
## Stanislaw Grams <sjg@fmdx.pl>
##
## CMakeLists.txt
## See LICENSE for license information
##

###
## source code
##
cmake_minimum_required (VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
project (meteodata)

# pkg-config
find_package (PkgConfig REQUIRED)

# output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory (src)   ## bin
#add_subdirectory (test)  ## unit tests
