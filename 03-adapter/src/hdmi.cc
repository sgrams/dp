/* 2020/06/06
 * Stanislaw Grams <sjg@fmdx.pl>
 * 03-adapter/src/hdmi.cc
*/
#include "../include/hdmi.hh"
Hdmi::Hdmi (std::string name) {
  this->name = name;
}

void
Hdmi::set_format (std::string format) {
  this->video_format = format;
}

std::string &
Hdmi::get_format () {
  return this->video_format;
}
