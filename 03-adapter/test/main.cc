/* 2020/06/06
 * Stanislaw Grams <sjg@fmdx.pl>
 * 03-adapter/test/main.cc
*/
#include <iostream>
#include <gtest/gtest.h>
#include "../include/vga.hh"
#include "../include/hdmi.hh"
#include "../include/videoadapter.hh"

TEST (utadapter_init, adpater_fail) {
  // arrange
  // assert
  // cleanup
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
