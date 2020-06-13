/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/parser.cc
 * See ../LICENSE for license information
 */
#include "../include/facade.hh"

void
station_facade_c::set_strategy (flavour_t flavour) {
  if (flavour == meteo) {
    this->strategy = std::make_unique<meteo_strategy_c>(meteo_strategy_c (this->agent));
  } else if (flavour == hydro) {
    this->strategy = std::make_unique<hydro_strategy_c>(hydro_strategy_c (this->agent));
  }
}

void
station_facade_c::find_station (std::string name) {
  if (station->get_number () == 0) {
    this->set_strategy (station->get_flavour ());
    try {
      std::pair<std::string, uint64_t> info = strategy->find_station (name);
      station->set_name (info.first);
      station->set_number (info.second);
    } catch (...) {
      throw std::invalid_argument ("unable to match ID to a requested station!, double-check your inputs!");
    }
  }
}

void
station_facade_c::fill_station_data () {
  try {
    this->strategy->fill_station_data (this->station, &this->json, this->agent, this->data);
  } catch (...) {
    std::cerr << "Unable to fill station with data!" << std::endl;
  }
}

station_c *
station_facade_c::get_station () {
  return this->station;
}

void
meteo_strategy_c::converter (station_c *station, json_c *json) {
  // temperature parser
  data_vec_t temp_data_vec;

  json_c json_tmp = *json;
  json_c json_tmp_temp = json_tmp[PATH_TEMP_AUTO_REC];
  json_c::iterator json_it;

  for (json_it = json_tmp_temp.begin (); json_it < json_tmp_temp.end (); ++json_it)
  {
    std::pair<timestamp_t, float> data;
    //data.first  = std::chrono((*json_it)["date"].dump().c_str ());
    data.first  = 0;
    data.second = std::atof ((*json_it)["value"].dump ().c_str ());
    temp_data_vec.push_back (data);
  }
  ((meteo_station_c *)station)->set_data (temp_data_vec);
}

void
hydro_strategy_c::converter (station_c *station, json_c *json) {
  // water level parser
  data_vec_t level_data_vec;

  json_c json_tmp = *json;
  json_c json_tmp_level = json_tmp[PATH_WATER_LEVEL];
  json_c::iterator json_it;

  for (json_it = json_tmp_level.begin (); json_it < json_tmp_level.end (); ++json_it)
  {
    std::pair<timestamp_t, float> data;
    //data.first  = std::chrono((*json_it)["date"].dump().c_str ());
    data.first  = 0;
    data.second = std::atof ((*json_it)["value"].dump ().c_str ());
    level_data_vec.push_back (data);
  }
  ((hydro_station_c *)station)->set_data (level_data_vec);
}
