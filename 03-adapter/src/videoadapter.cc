/* 2020/06/06
 * Stanislaw Grams <sjg@fmdx.pl>
 * 03-adapter/src/videoadapter.cc
*/
#include "../include/videoadapter.hh"

HdmiToVga::HdmiToVga (Hdmi in_hdmi_plug) {
  // initialize with adaptee values
  this->set_format ("analogue");
  this->video_stream = in_hdmi_plug.video_stream;

  // perform conversion (turbo-lazy DAC below)
  this->video_stream = "analogue video format";
}

HdmiToVga::HdmiToVga (Vga out_vga_plug) {
  // already initialized (plugging the target)
  std::string old_format = this->get_format ();
  this->set_format (out_vga_plug.get_format ());
}

std::string
HdmiToVga::get_the_stream () {
  return "Your converted stream is: " + this->video_stream;
}
