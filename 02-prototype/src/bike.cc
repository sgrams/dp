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
Bike::Bike () {
}

Bike::Bike (std::string name) {
  this->_bike_name = name;
}

void
Bike::set_kilometrage (float kilometrage) {
  this->_bike_kilometrage = kilometrage;
}

std::string
Bike::take_the_bike_out () {
  this->_bike_kilometrage += 100.0;

  std::string out = std::string ("You took your " +
      this->_bike_name +
      " bike for a ride! You already rode it for " +
      std::to_string (this->_bike_kilometrage) +
      " km.");
  return out;
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
