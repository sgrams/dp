## 2020/06/05
## Stanislaw Grams <sjg@fmdx.pl>
## 02-prototype/CMakeLists.txt
cmake_minimum_required(VERSION 3.0.0)
project (prototype)

find_package(GTest REQUIRED)
enable_testing()

set(LIBPROTOTYPE_SRC
  src/prototype.cc
  include/prototype.hh
  include/macro.hh
  )

add_library(prototype SHARED
  ${LIBPROTOTYPE_SRC}
  )

add_subdirectory(test)
