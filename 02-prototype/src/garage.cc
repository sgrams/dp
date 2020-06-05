/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/src/garage.cc
*/
#include "../include/garage.hh"

/*
 Garage class (prototype)
*/
void
Garage::whats_my_capacity () {
  std::cout << "I can keep " << this->_garage_capacity << " bikes!" << std::endl;
}

void
Garage::make_some_room () {
  std::cout << ":(" << std::endl;
}

/*
  CompactGarage class
*/
void
CompactGarage::make_some_room () {
  int add = 1;
  this->_garage_capacity += add;
  std::cout << "GIMME "<< add << " MORE BIKES" << std::endl;
}

Garage *
CompactGarage::clone () const {
  return new CompactGarage (*this);
}

/*
  OversizedGarage class
*/
void
OversizedGarage::make_some_room () {
  int add = 5;
  this->_garage_capacity += add;
  std::cout << "GIMME "<< add << " MORE BIKES" << std::endl;
}

Garage *
OversizedGarage::clone () const {
  return new OversizedGarage (*this);
}
