/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/src/bike.cc
*/
#include "../include/bike.hh"

/*
  BikePrototypeFactory class
*/
BikePrototypeFactory::BikePrototypeFactory () {
  _prototypes[BikeType::mountain] = new MountainBike ("gooral", "stalowe");
  _prototypes[BikeType::road] = new RoadBike ("gooral", "shimano");
}

BikePrototypeFactory::~BikePrototypeFactory () {
  delete _prototypes[BikeType::mountain];
  delete _prototypes[BikeType::road];
}

Bike *
BikePrototypeFactory::create_bike (BikeType bike_type) {
  return _prototypes[bike_type]->clone ();
}

/*
  Bike class (prototype)
*/
void
Bike::take_the_bike_out (float kilometrage) {
  this->_bike_kilometrage = kilometrage;
  std::cout << "You took your " << _bike_name
    << " bike for a ride! You already rode it for " << _bike_kilometrage
    << " km." << std::endl;
}

/*
  MountainBike class
*/
Bike *
MountainBike::clone () const {
  return new MountainBike (*this);
}

/*
  RoadBike class
*/
Bike *
RoadBike::clone () const {
  return new RoadBike (*this);
}
