## 2020/05/23
## Stanislaw Grams <sjg@fmdx.pl>
## 01-singleton/test/CMakeLists.txt
add_executable(utsingleton
  main.cc
  )

set(UTSINGLETON_SRC
  main.cc
  )

target_link_libraries(utsingleton
  PRIVATE
  singleton
  ${GTEST_LIBRARIES}
  )

enable_testing()

GTEST_ADD_TESTS(
  utsingleton
  ""
  ${UTSINGLETON_SRC}
  )
