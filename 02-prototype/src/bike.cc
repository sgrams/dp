/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/src/bike.cc
*/
#include "../include/bike.hh"

/*
  BikePrototypeFactory class
*/
BikePrototypeFactory::BikePrototypeFactory () {
  _prototypes[BikeType::trek]        = new MountainBike ("trek", "steel");
  _prototypes[BikeType::specialized] = new MountainBike ("specialized", "steel");
  _prototypes[BikeType::giant]       = new MountainBike ("giant", "plastic");
  _prototypes[BikeType::kross]       = new RoadBike ("kross", "shimano");
  _prototypes[BikeType::rondo]       = new RoadBike ("rondo", "shimano");
  _prototypes[BikeType::merida]      = new RoadBike ("merida", "sram");
}

BikePrototypeFactory::~BikePrototypeFactory () {
  delete _prototypes[BikeType::trek];
  delete _prototypes[BikeType::specialized];
  delete _prototypes[BikeType::giant];
  delete _prototypes[BikeType::kross];
  delete _prototypes[BikeType::rondo];
  delete _prototypes[BikeType::merida];
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
