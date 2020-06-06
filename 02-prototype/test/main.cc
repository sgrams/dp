/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/main.cc
*/
#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <gtest/gtest.h>
#include "../include/garage.hh"
#include "../include/bike.hh"

TEST (utprototype_init, garage_fail) {
  // arrange
  BikePrototypeFactory bkf;
  std::vector<Bike *>  bikes;

  for (int bike_type = trek; bike_type != merida; ++bike_type)
  {
    bikes.push_back (bkf.create_bike (static_cast<BikeType> (bike_type)));
  }
  DeepGarageData dgd = DeepGarageData (&bikes);

  try {
    // act
    CompactGarage g1 = CompactGarage ("g1", 0, dgd, "sjg");
    FAIL () << "Expected std::invalid_argument";
  } catch (std::invalid_argument const &err) {
    // assert
    EXPECT_EQ (err.what (), std::string ("Most likely your garage is too small!"));
  }

  for (auto const * it : bikes) {
    delete it;
  }
}

TEST (utprototype_clone, deep_copy_test) {
  // arrange
  BikePrototypeFactory bkf;
  std::vector<Bike *>  bikes;

  for (int bike_type = trek; bike_type != merida; ++bike_type)
  {
    bikes.push_back (bkf.create_bike (static_cast<BikeType> (bike_type)));
  }

  DeepGarageData dgd = DeepGarageData (&bikes);

  for (auto const * it : bikes) {
    delete it;
  }

  // act 1
  std::shared_ptr<Garage> g1 (new CompactGarage ("g1", 5, dgd, "sjg"));
  std::shared_ptr<Garage> g2 ((CompactGarage *)g1->clone ());

  // assert
  ASSERT_NE (g1, g2);

  // act 2
  std::vector<Bike *> *g1_bikes = g1->_garage_content->get_deep_data ();
  std::vector<Bike *> *g2_bikes = g2->_garage_content->get_deep_data ();
  g1_bikes->at(0)->set_kilometrage (0.2);
  std::cout << g1_bikes->at(0)->take_the_bike_out () << std::endl;
  std::cout << g2_bikes->at(0)->take_the_bike_out () << std::endl;
  std::cout << g2_bikes->at(0)->take_the_bike_out () << std::endl;
  std::cout << g2_bikes->at(0)->take_the_bike_out () << std::endl;
  std::cout << g1_bikes->at(0)->take_the_bike_out () << std::endl;
  bool identical = *g1 == *g2;
  ASSERT_FALSE (identical);
}


TEST (utprototype_clone, shallow_copy_test) {
  // arrange
  BikePrototypeFactory bkf;
  std::vector<Bike *>  bikes;

  for (int bike_type = trek; bike_type != merida; ++bike_type)
  {
    bikes.push_back (bkf.create_bike (static_cast<BikeType> (bike_type)));
  }

  DeepGarageData dgd = DeepGarageData (&bikes);

  for (auto const * it : bikes) {
    delete it;
  }

  // act 1
  std::shared_ptr<Garage> g1 (new OversizedGarage ("g1", 100, dgd, "sjg"));
  std::shared_ptr<Garage> g2 = g1;

  // assert
  ASSERT_EQ (g1, g1);

  // act 2
  std::vector<Bike *> *g1_bikes = g1->_garage_content->get_deep_data ();
  std::vector<Bike *> *g2_bikes = g2->_garage_content->get_deep_data ();
  g1_bikes->at(0)->set_kilometrage (0.2);
  std::cout << g1_bikes->at(0)->take_the_bike_out () << std::endl;
  std::cout << g2_bikes->at(0)->take_the_bike_out () << std::endl;
  std::cout << g2_bikes->at(0)->take_the_bike_out () << std::endl;
  std::cout << g2_bikes->at(0)->take_the_bike_out () << std::endl;
  std::cout << g1_bikes->at(0)->take_the_bike_out () << std::endl;
  bool identical = *g1 == *g2;
  ASSERT_TRUE (identical);

}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
