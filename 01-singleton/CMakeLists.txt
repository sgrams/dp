## 2020/05/23
## Stanislaw Grams <sjg@fmdx.pl>
## 01-singleton/CMakeLists.txt
cmake_minimum_required(VERSION 3.0.0)
project (singleton)

find_package(GTest REQUIRED)
enable_testing()

set(LIBSINGLETON_SRC
  src/singleton.cc
  include/singleton.hh
  )

add_library(singleton SHARED
  ${LIBSINGLETON_SRC}
  )

add_subdirectory(test)
