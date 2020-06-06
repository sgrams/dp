/* 2020/06/06
 * Stanislaw Grams <sjg@fmdx.pl>
 * 03-adapter/include/vga.hh
*/
#ifndef _VGA_H_
#define _VGA_H_
#include <string>

class Vga {
  private:
    std::string video_format{"analogue"};
    std::string name;

  public:
    std::string video_stream;

    Vga () {};
    Vga (std::string name);
    // interfaces
    void        set_vga_video_stream (std::string video_stream);
    std::string &get_format ();
    void        set_format (std::string format);
};

#endif // _VGA_H_
