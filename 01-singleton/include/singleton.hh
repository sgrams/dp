/* 2020/05/23
 * Stanislaw Grams <sjg@fmdx.pl>
 * 01-singleton/include/singleton.hh
*/
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <string>
#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <memory>
#include <string>
#include <queue>
#include <algorithm>
#include "../include/macro.hh"

class singleton_c {
    struct singleton_data {
      std::atomic<int>   constructor_calls{0};
      std::atomic<int>   fetch_calls{0};
    };

    struct trivial_data {
      int constructor_calls;
      int fetch_calls;
    };

  public:
    static singleton_c         *fetch_instance ();
    static void                delete_instance ();
    std::vector<unsigned char> serialize ();
    void                       deserialize (std::vector<unsigned char> &buffer);

    struct singleton_data data;

  private:
    singleton_c ();
    ~singleton_c ();
    static std::atomic<singleton_c *> singleton_instance;
    static std::mutex                 singleton_mutex;
};

#endif // _SINGLETON_H_
