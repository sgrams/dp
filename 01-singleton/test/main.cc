/* 2020/02/22
 * Stanislaw Grams <sjg@fmdx.pl>
 * 01-singleton/main.cc
*/
#include <iostream>
#include <cstdint>
#include <thread>
#include <future>
#include <numeric>
#include <vector>
#include <gtest/gtest.h>
#include "../include/singleton.hh"

TEST (utsingleton_init, main) {
  // arrange
  singleton_c * singleton_ptr = nullptr;

  // act
  singleton_ptr = singleton_c::fetch_instance ();

  // assert
  ASSERT_NE (singleton_ptr, nullptr);

  // cleanup
  singleton_c::delete_instance ();
}

bool threading_tests_helper (int threads) {
  singleton_c * singleton_ptr     = nullptr;
  bool          is_retval_correct = true;
  std::vector<std::future<singleton_c *>> future_vec;

  // run threads
  for (int i = 0; i < threads; i++)
  {
    future_vec.push_back (
        std::async (std::launch::async, singleton_c::fetch_instance)
      );
  }

  // gather values from all ran threads
  for (auto &f : future_vec)
  {
    f.wait ();

    if (nullptr == singleton_ptr) {
      // load singleton for the first time (real init)
      singleton_ptr = f.get ();
      continue;
    }
    if (f.get () != singleton_ptr) {
      // fail if returned ptr is different than existing
      is_retval_correct = false;
    }
  }
  std::cerr << "[ RUN      ]"
    << " ptr == " << singleton_ptr
    << "; fetch_calls = " << singleton_ptr->data.fetch_calls
    << "; constructor_calls = " << singleton_ptr->data.constructor_calls
    << std::endl;

  // cleanup
  singleton_c::delete_instance ();

  // return
  return is_retval_correct;
}

TEST (utsingleton_threading, 512_threads) {
  // assert
  ASSERT_TRUE (threading_tests_helper (512));
}

TEST (utsingleton_threading, 8192_threads) {
  // assert
  ASSERT_TRUE (threading_tests_helper (8192));
}

TEST (utsingleton_threading, 16384_threads) {
  // assert
  ASSERT_TRUE (threading_tests_helper (16384));
}

TEST (utsingleton_serialization, test_for_values) {
  // arrange
  singleton_c *singleton_ptr    = singleton_c::fetch_instance ();

  // save sate of singleton data
  int fetch_calls_before_serial = singleton_ptr->data.fetch_calls.load ();

  // serialize
  std::vector<unsigned char> buffer = singleton_ptr->serialize ();
  std::cerr << "[ serial   ]"
    << " ptr == " << singleton_ptr
    << "; fetch_calls = " << singleton_ptr->data.fetch_calls
    << "; constructor_calls = " << singleton_ptr->data.constructor_calls
    << std::endl;

  // change state of singleton data
  singleton_ptr->data.fetch_calls = 1337;

  std::cerr << "[ -------- ]"
    << " ptr == " << singleton_ptr
    << "; fetch_calls = " << singleton_ptr->data.fetch_calls
    << "; constructor_calls = " << singleton_ptr->data.constructor_calls
    << std::endl;

  // save state of singleton data
  int fetch_calls_after_serial = singleton_ptr->data.fetch_calls.load ();

  // deserialize
  singleton_ptr->deserialize (buffer);
  std::cerr << "[ deserial ]"
    << " ptr == " << singleton_ptr
    << "; fetch_calls = " << singleton_ptr->data.fetch_calls
    << "; constructor_calls = " << singleton_ptr->data.constructor_calls
    << std::endl;

  // save sate of singleton data
  int fetch_calls_after_deserial = singleton_ptr->data.fetch_calls.load ();

  // assert
  ASSERT_NE (fetch_calls_before_serial, fetch_calls_after_serial);
  ASSERT_EQ (fetch_calls_before_serial, fetch_calls_after_deserial);

  // release
  singleton_c::delete_instance ();
}

int main (int argc, char **argv) {
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
