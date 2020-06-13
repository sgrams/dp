/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/station.cc
 * See ../LICENSE for license information
 */
#include "../include/station.hh"

std::string
station_c::get_name (
  )
{
  return this->name;
}

void
station_c::set_name (
  std::string name
  )
{
  if (name.empty ()) {
    throw std::invalid_argument ("name was set incorrectly");
    return;
  }
  this->name = name;
  return;
}

uint64_t
station_c::get_number (
  )
{
  return this->number;
}

void
station_c::set_number (
  uint64_t number
  )
{
  if (number > 0) {
    this->number = number;
  }
}

flavour_t
station_c::get_flavour (
  )
{
  return this->flavour;
}


void
meteo_station_c::set_data (
  data_vec_t &temp
  )
{
  this->temp        = temp;
}

measurement_temp_celsius_c
meteo_station_c::get_cur_temp () {
  measurement_temp_celsius_c rv;
  rv.set_value (this->temp.back().second);
  return rv;
}

measurement_temp_kelvin_c
meteo_station_c::get_cur_temp_kelvin () {
  measurement_temp_kelvin_c rv;
  rv.set_value (this->temp.back().second);
  return rv;
}

measurement_temp_fahrenheit_c
meteo_station_c::get_cur_temp_fahrenheit () {
  measurement_temp_fahrenheit_c rv;
  rv.set_value (this->temp.back().second);
  return rv;
}

measurement_impl_c
hydro_station_c::get_cur_level () {
  measurement_impl_c rv;
  rv.set_value (this->level.back ().second);
  return rv;
}

void
hydro_station_c::set_data (
  data_vec_t &level
  )
{
  this->level     = level;
}