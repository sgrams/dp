/* 2020/05/23
 * Stanislaw Grams <sjg@fmdx.pl>
 * 01-singleton/src/singleton.cc
*/
#include <cista/serialization.h>
#include "../include/singleton.hh"

std::atomic<singleton_c *> singleton_c::singleton_instance{nullptr};
std::mutex                 singleton_c::singleton_mutex;

singleton_c::singleton_c () {
  // singleton is threaded-safe so should be constructor
#ifdef UNIT_TEST
  std::cout << "[ RUN      ] constructor was called!" << std::endl;
#endif
}

singleton_c::~singleton_c () {
  // singleton is threaded-safe so should be destructor
#ifdef UNIT_TEST
  std::cout << "[ RUN      ] destructor was called!" << std::endl;
#endif
}

void
singleton_c::delete_instance () {
  singleton_c *ptr = singleton_instance.load (std::memory_order_acquire);
  if (nullptr != ptr) {
    ptr = singleton_instance.load (std::memory_order_relaxed);
    if (nullptr != ptr) {
      delete ptr;
      singleton_instance.store (nullptr, std::memory_order_release);
      singleton_mutex.unlock ();
    }
  }
}

singleton_c *
singleton_c::fetch_instance () {
  singleton_c *ptr = singleton_instance.load (std::memory_order_acquire);
  if (nullptr == ptr) {
    std::lock_guard<std::mutex> lock (singleton_mutex);
    ptr = singleton_instance.load (std::memory_order_relaxed);
    if (nullptr == ptr) {
      ptr = new singleton_c ();
      singleton_instance.store (ptr, std::memory_order_release);

      // inc number of constructor_calls
      ptr->data.constructor_calls.fetch_add (1);
    }
  }
  // inc number of fetch functions calls
  ptr->data.fetch_calls.fetch_add (1);

  // fake load to make threads visible in top during launch
  std::this_thread::sleep_for (std::chrono::seconds (3));
  return ptr;
}

std::vector<unsigned char>
singleton_c::serialize () {
  singleton_c::trivial_data data;

  data.constructor_calls = this->data.constructor_calls.load ();
  data.fetch_calls = this->data.fetch_calls.load ();

  return cista::serialize (data);
}

void
singleton_c::deserialize (std::vector<unsigned char> &buffer) {
  singleton_c::trivial_data *data;

  data = cista::deserialize<singleton_c::trivial_data> (buffer);

  this->data.constructor_calls.store (data->constructor_calls);
  this->data.fetch_calls.store (data->fetch_calls);
}
