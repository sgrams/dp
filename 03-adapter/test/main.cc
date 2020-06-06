/* 2020/06/06
 * Stanislaw Grams <sjg@fmdx.pl>
 * 03-adapter/test/main.cc
*/
#include <iostream>
#include <gtest/gtest.h>
#include "../include/vga.hh"
#include "../include/hdmi.hh"
#include "../include/videoadapter.hh"

TEST (utadapter_init, in_hdmi_plug) {
  // arrange
  Hdmi hdmi_source = Hdmi ("xbox");
  HdmiToVga hdmi_to_vga (hdmi_source);

  // assert
  ASSERT_NE (hdmi_source.video_stream, hdmi_to_vga.get_the_stream ());
  ASSERT_EQ (hdmi_to_vga.get_the_stream (), std::string("Your converted stream is: analogue video format"));
}

TEST (utadapter_init, out_vga_plug) {
  // arrange
  Vga vga_output = Vga ("tv");
  HdmiToVga hdmi_to_vga (vga_output);

  // assert
  ASSERT_EQ (hdmi_to_vga.get_format (), vga_output.get_format ());
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
