/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/data.cc
 * See ../LICENSE for license information
 */
#include "../include/data.hh"

void
data_c::clear ()
{
  this->buffer.clear ();
  this->size = 0;
}
