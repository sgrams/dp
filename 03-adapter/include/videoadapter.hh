/* 2020/06/06
 * Stanislaw Grams <sjg@fmdx.pl>
 * 03-adapter/include/videoadapter.hh
*/
#ifndef _VIDEOADAPTER_H_
#define _VIDEOADAPTER_H_
#include "vga.hh"
#include "hdmi.hh"
#include <regex>
#include <iostream>

class HdmiToVga : public Hdmi {
  public:
    HdmiToVga (Hdmi in_hdmi_plug); // Adapter - adaptee
    HdmiToVga (Vga out_vga_plug);  // Adapter - target

    std::string get_the_stream ();
};

#endif // _VIDEOADAPTER_H_
