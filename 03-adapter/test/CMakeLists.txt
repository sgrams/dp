## 2020/06/06
## Stanislaw Grams <sjg@fmdx.pl>
## 03-adapter/test/CMakeLists.txt
add_executable(utadapter
  main.cc
  )

set(UTADAPTER_SRC
  main.cc
  )

target_link_libraries(utadapter
  PRIVATE
  adapter
  ${GTEST_LIBRARIES}
  )

enable_testing()

GTEST_ADD_TESTS(
  utadapter
  ""
  ${UTADAPTER_SRC}
  )
