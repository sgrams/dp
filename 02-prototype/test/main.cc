/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/main.cc
*/
#include <iostream>
#include <cstdint>
#include <gtest/gtest.h>
#include "../include/garage.hh"
#include "../include/bike.hh"



TEST (utprototype_init, garage_fail) {
  // arrange
  BikePrototypeFactory bkf;
  std::vector<Bike *> bikes;

  // one more than 0 should be enough to throw an exception
  bikes.push_back (bkf.create_bike (BikeType::specialized));

  try {
    // act
    CompactGarage g1 = CompactGarage ("g1", 0, bikes, "sjg");
    FAIL () << "Expected std::invalid_argument";
  } catch (std::invalid_argument const &err) {
    // assert
    EXPECT_EQ (err.what (), std::string ("Most likely your garage is too small!"));
  }

  delete bikes[0];
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
