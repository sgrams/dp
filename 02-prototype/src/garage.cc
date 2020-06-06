/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/src/garage.cc
*/
#include "../include/garage.hh"
/*
  DeepGarageData class
*/
DeepGarageData::DeepGarageData (std::vector <Bike *> *deep_data) {
  if (deep_data == nullptr) {
    throw std::invalid_argument ("deep_data is a nullptr!");
  }

  for (auto const & it : *deep_data) {
    this->_deep_data.push_back (it->clone ());
  }
}

DeepGarageData::~DeepGarageData () {
  for (auto const & it : this->_deep_data) {
    delete it;
  }
}

bool
DeepGarageData::operator== (const DeepGarageData &dgd) {
  bool rv = true;

  if (this->_deep_data.size () == dgd._deep_data.size ()) {
    if (this->_deep_data != dgd._deep_data) {
      rv = false;
    }
  } else {
    rv = false;
  }

  return rv;
}

std::vector <Bike *> *
DeepGarageData::get_deep_data () {
  return &(this->_deep_data);
}

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

bool
Garage::operator== (const Garage &g) {
  bool rv = true;

  rv &= g._garage_name       == this->_garage_name;
  rv &= g._garage_capacity   == this->_garage_capacity;
  rv &= *(g._garage_content) == *(this->_garage_content);

  return rv;
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
  CompactGarage *rv = new CompactGarage (*this);
  rv->_garage_content = new DeepGarageData (this->_garage_content->get_deep_data ());
  return rv;
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
  OversizedGarage *rv = new OversizedGarage (*this);
  rv->_garage_content = new DeepGarageData (this->_garage_content->get_deep_data ());
  return rv;
}
