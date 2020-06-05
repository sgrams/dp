/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/include/garage.hh
*/
#ifndef _GARAGE_H_
#define _GARAGE_H_
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "bike.hh"

/*
  Garage class (prototype)
*/
class Garage {
  protected:
    std::string        _garage_name;
    unsigned           _garage_capacity{0};

  public:
    Garage (
      std::string name,
      int capacity,
      std::vector<Bike *> &content):
      _garage_name (name),
      _garage_capacity (capacity),
      _garage_content (content) {
        if (content.size () > capacity) {
          throw std::invalid_argument ("Most likely your garage is too small!");
        }
      }

    std::vector <Bike *> &_garage_content;

    // interfaces
    virtual ~Garage () {};
    virtual Garage *clone () const = 0;
    virtual void whats_my_capacity ();
    virtual void make_some_room ();
};

/*
  CompactGarage class
*/
class CompactGarage : public Garage {
  private:
    std::string _garage_owner;

  public:
    CompactGarage (
      std::string name,
      int capacity,
      std::vector<Bike *> content,
      std::string owner):
      Garage (name, capacity, content),
      _garage_owner (owner) {
        if (content.size () > capacity) {
          throw std::invalid_argument ("Most likely your garage is too small!");
        }
      }

    Garage *clone () const override;
    void make_some_room ();
};

/*
  OversizedGarage class
*/
class OversizedGarage : public CompactGarage {
    Garage *clone () const override;
    void make_some_room ();
};
#endif // _GARAGE_H_
