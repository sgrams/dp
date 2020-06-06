/* 2020/06/06
 * Stanislaw Grams <sjg@fmdx.pl>
 * 03-adapter/src/vga.cc
*/
#include "../include/vga.hh"

Vga::Vga (std::string name) {
  this->name = name;
}

void
Vga::set_format (std::string format) {
  this->video_format = format;
}

std::string &
Vga::get_format () {
  return this->video_format;
}

void
Vga::set_vga_video_stream (std::string video_stream) {
  this->video_stream = video_stream;
}
