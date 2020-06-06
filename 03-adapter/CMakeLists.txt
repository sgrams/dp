## 2020/06/06
## Stanislaw Grams <sjg@fmdx.pl>
## 03-adapter/CMakeLists.txt
cmake_minimum_required(VERSION 3.0.0)
project (adapter)

find_package(GTest REQUIRED)
enable_testing()

set(LIBADAPTER_SRC
  src/vga.cc
  src/hdmi.cc
  src/videoadapter.cc
  include/vga.hh
  include/hdmi.hh
  include/videoadapter.hh
  include/macro.hh
  )

add_library(adapter SHARED
  ${LIBADAPTER_SRC}
  )

add_subdirectory(test)
