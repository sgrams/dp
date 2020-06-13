/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/types.hh
 * See ../LICENSE for license information
 */
#ifndef METEODATA_TYPES_H
#define METEODATA_TYPES_H
#include <chrono>
#include <vector>
#include <algorithm>

typedef enum meteo_datatype {
  temp,
  temp_kelvin,
  temp_fahrenheit
} meteo_datatype_t;

typedef enum hydro_datatype {
  level
} hydro_datatype_t;

typedef enum command {
  verbose  = 0x01,
  location = 0x02,
  date     = 0x03,
  type     = 0x04,
} command_t;

typedef enum flavour {
  meteo,
  hydro
} flavour_t;

typedef std::time_t timestamp_t;
typedef std::vector<std::pair<timestamp_t, float>> data_vec_t;

#endif // METEODATA_TYPES_H
