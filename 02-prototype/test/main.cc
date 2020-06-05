/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/main.cc
*/
#include <iostream>
#include <cstdint>
#include <thread>
#include <future>
#include <numeric>
#include <vector>
#include <gtest/gtest.h>
#include "../include/prototype.hh"

TEST (utprototype_init, main) {
  // arrange
  // act
  // assert
  ASSERT_TRUE (1<2);
}
int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
