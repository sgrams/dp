/* 2020/06/05
 * Stanislaw Grams <sjg@fmdx.pl>
 * 02-prototype/include/bike.hh
*/
#ifndef _BIKE_H_
#define _BIKE_H_
#include <unordered_map>
#include <string>
#include <iostream>

enum BikeType {
  trek,
  specialized,
  giant,
  kross,
  rondo,
  merida
};

/*
  Bike class (prototype)
*/
class Bike {
  protected:
    std::string _bike_name;
    float       _bike_kilometrage{0.0};

  public:
    Bike ();
    Bike (std::string name);

    virtual ~Bike () {};
    virtual Bike *clone () const = 0;
    virtual void set_kilometrage (float kilometrage);
    virtual std::string take_the_bike_out ();
};

/*
  MountainBike class
*/
class MountainBike : public Bike {
  private:
    std::string _bike_fenders;

  public:
    MountainBike (std::string name, std::string fenders) :
      Bike (name), _bike_fenders(fenders) {};

    Bike *clone () const override;
};

/*
  RoadBike class
*/
class RoadBike : public Bike {
  private:
    std::string _bike_derailleurs;

  public:
    RoadBike (std::string name, std::string derailleurs) :
      Bike (name), _bike_derailleurs(derailleurs) {};

    Bike *clone () const override;
};

/*
  BikePrototypeFactory class
*/
class BikePrototypeFactory {
  private:
    std::unordered_map<BikeType, Bike *, std::hash<int>> _prototypes;

  public:
    BikePrototypeFactory ();
    ~BikePrototypeFactory ();

    Bike *create_bike (BikeType bike_type);
};
#endif // _BIKE_H_
