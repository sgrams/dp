/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/data.hh
 * See ../LICENSE for license information
 */
#ifndef METEODATA_DATA_H
#define METEODATA_DATA_H
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <memory>

class data_c {
  public:
  std::string buffer;
  size_t      size;

  void clear ();
};
#endif // METEODATA_DATA_H
