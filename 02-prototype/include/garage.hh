/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/include/garage.hh
*/
#ifndef _GARAGE_H_
#define _GARAGE_H_
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <memory>
#include "bike.hh"
/*
  DeepGarageData class
*/
class DeepGarageData {
  protected:
    std::vector <Bike *> _deep_data;
  public:
    DeepGarageData (std::vector <Bike *> *deep_data);
    ~DeepGarageData();

    // operators
    bool operator== (const DeepGarageData &dgd);

    // interfaces
    std::vector <Bike *> *get_deep_data ();
};

/*
  Garage class (prototype)
*/
class Garage {
  protected:
    std::string    _garage_name;
    unsigned       _garage_capacity{0};

  public:
    DeepGarageData *_garage_content;

    Garage (
      std::string name,
      int capacity,
      DeepGarageData &content):
      _garage_name (name),
      _garage_capacity (capacity) {
        if (content.get_deep_data ()->size () > capacity) {
          throw std::invalid_argument ("Most likely your garage is too small!");
        }
        this->_garage_content = new DeepGarageData (content.get_deep_data ());
      };
    ~Garage () {
      delete this->_garage_content;
    };

    // operators
    bool operator== (const Garage &g);

    // interfaces
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
      DeepGarageData &content,
      std::string owner):
      Garage (name, capacity, content),
      _garage_owner (owner) {
        if (content.get_deep_data ()->size () > capacity) {
          throw std::invalid_argument ("Most likely your garage is too small!");
        }
      }

    Garage *clone () const override;
    void make_some_room () override;
};

/*
  OversizedGarage class
*/
class OversizedGarage : public CompactGarage {
  public:
    OversizedGarage (
      std::string name,
      int capacity,
      DeepGarageData &content,
      std::string owner):
      CompactGarage (name, capacity, content, owner) {}
    Garage *clone () const override;
    void make_some_room () override;
};
#endif // _GARAGE_H_
