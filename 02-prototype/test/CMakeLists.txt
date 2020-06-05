## 2020/06/05
## Stanislaw Grams <sjg@fmdx.pl>
## 02-prototype/test/CMakeLists.txt
add_executable(utprototype
  main.cc
  )

set(UTPROTOTYPE_SRC
  main.cc
  )

target_link_libraries(utprototype
  PRIVATE
  prototype
  ${GTEST_LIBRARIES}
  )

enable_testing()

GTEST_ADD_TESTS(
  utprototype
  ""
  ${UTPROTOTYPE_SRC}
  )
