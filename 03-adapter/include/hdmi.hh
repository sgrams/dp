/* 2020/06/06
 * Stanislaw Grams <sjg@fmdx.pl>
 * 03-adapter/include/hdmi.hh
*/
#ifndef _HDMI_H_
#define _HDMI_H_
#include <string>

class Hdmi {
  private:
    std::string video_format{"digital"};
    std::string name;

  public:
    std::string video_stream{"digital video stream"};

    Hdmi () {};
    Hdmi (std::string name);
    // interfaces
    std::string &get_hdmi_video_stream ();
    std::string &get_format ();
    void        set_format (std::string format);
};

#endif // _HDMI_H_
