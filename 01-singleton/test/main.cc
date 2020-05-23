/* 2020/02/22
 * Stanislaw Grams <sjg@fmdx.pl>
 * 01-singleton/main.cc
*/
#include <iostream>
#include <cstdint>
#include <gtest/gtest.h>
#include "../include/singleton.hh"

TEST (utsingleton, init) {
  // arrange
  // act
  // assert
  // release
}

TEST (utsingleton, threading) {
  // arrange
  // act
  // assert
  // release
}

TEST (utsingleton, serialization_first) {
  // arrange
  // act
  // assert
  // release
}

TEST (utsingleton, serialization_second) {
  // arrange
  // act
  // assert
  // release
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  std::cout << "test";
  return RUN_ALL_TESTS ();
}

/*
  singleton_c *singleton_1 = singleton_c::get_instance ();
  singleton_c *singleton_2 = singleton_c::get_instance ();

  if (singleton_1 == singleton_2) {
    std::cout << "singleton_1 is equal to singleton_2, addr = "
      << std::to_address (singleton_1)
      << std::endl;
  }

  return 0;
}
*/
