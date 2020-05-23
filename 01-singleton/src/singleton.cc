/* 2020/05/23
 * Stanislaw Grams <sjg@fmdx.pl>
 * 01-singleton/src/singleton.cc
*/
#include "../include/singleton.hh"

std::atomic<singleton_c *> singleton_c::singleton_instance{nullptr};
std::mutex                 singleton_c::singleton_mutex;

singleton_c::singleton_c () {
  // singleton is threaded-safe so should be the prints
  std::cout << "constructor was called!" << std::endl;
}

singleton_c *
singleton_c::get_instance () {
  singleton_c *ptr = singleton_instance.load (std::memory_order_acquire);
  if (nullptr == ptr) {
    std::lock_guard<std::mutex> lock (singleton_mutex);
    ptr = singleton_instance.load (std::memory_order_relaxed);
    if (nullptr == ptr) {
      ptr = new singleton_c ();
      singleton_instance.store (ptr, std::memory_order_release);
    }
  }
  return ptr;
}
