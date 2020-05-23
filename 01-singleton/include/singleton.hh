/* 2020/05/23
 * Stanislaw Grams <sjg@fmdx.pl>
 * 01-singleton/include/singleton.hh
*/
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <string>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>

class singleton_c {
  public:
    static singleton_c *              get_instance ();

  private:
    singleton_c ();
    static std::atomic<singleton_c *> singleton_instance;
    static std::mutex                 singleton_mutex;
};

#endif // _SINGLETON_H_
