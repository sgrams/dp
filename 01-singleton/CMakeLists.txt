## 2020/05/23
## Stanislaw Grams <sjg@fmdx.pl>
## 01-singleton/CMakeLists.txt
cmake_minimum_required(VERSION 3.0.0)
project (singleton)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
enable_testing()

add_subdirectory(lib/cista)

set(LIBSINGLETON_SRC
  src/singleton.cc
  include/singleton.hh
  include/macro.hh
  )

add_library(singleton SHARED
  ${LIBSINGLETON_SRC}
  )

target_link_libraries(singleton
  cista
  )

add_subdirectory(test)
