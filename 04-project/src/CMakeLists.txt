##
## meteodata-git
## Stanislaw Grams <sjg@fmdx.pl>
##
## src/CMakeLists.txt
## See LICENSE for license information
##

# libcurl
pkg_check_modules(LIBCURL REQUIRED libcurl)
include_directories(${LIBCURL_INCLUDE_DIRS})
link_directories(${LIBCURL_LIBRARY_DIRS})
add_definitions(${LIBCURL_CFLAGS_OTHER})

# nlohmann/json
find_package (nlohmann_json REQUIRED)

## build flags
set (CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -Wall -pedantic"
  )

## src
set (SRC_FILES
  # *.cc, *.c
  agent.cc
  commandparser.cc
  data.cc
  helper.cc
  main.cc
  facade.cc
  station.cc

  # *.hh, *.h
  ../include/agent.hh
  ../include/commandparser.hh
  ../include/data.hh
  ../include/helper.hh
  ../include/facade.hh
  ../include/station.hh
  ../include/types.hh
  )

## lib
set (LIBS
  ${LIBCURL_LIBRARIES}
  nlohmann_json::nlohmann_json
  )

## executable
add_executable (
  meteodata
  ${SRC_FILES}
  )

target_link_libraries (
  meteodata
  ${LIBS})
