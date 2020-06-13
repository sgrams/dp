/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/station.hh
 * See ../LICENSE for license information
 */
#ifndef METEODATA_STATION_H
#define METEODATA_STATION_H
#include <cstdint>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include "types.hh"

class measurement_c { // Decorator (base class)
  private:
    float value = 0.00;
  public:
    virtual ~measurement_c () {};

    void set_value (float value) {
      this->value = value;
    };

    float get_value () const {
      return value;
    };

    virtual std::string to_string () const = 0;
};

class measurement_impl_c : public measurement_c {
  public:
    std::string to_string () const override {
      std::stringstream stream;
      stream << std::fixed << std::setprecision (2) << this->get_value ();
      return stream.str ();
    };
};

class measurement_temp_celsius_c: public measurement_c {
  public:
    std::string to_string () const override {
      float celsius = this->get_value ();
      std::stringstream stream;
      stream << std::fixed << std::setprecision (2) << celsius;
      return stream.str () + " °C";
    };
};

class measurement_temp_fahrenheit_c : public measurement_c {
  public:
    std::string to_string () const override {
      float fahrenheit = this->get_value () * 1.8 + 32.0;
      std::stringstream stream;
      stream << std::fixed << std::setprecision (2) << fahrenheit;
      return stream.str () + " °F";
    };
};

class measurement_temp_kelvin_c : public measurement_c {
  public:
    std::string to_string () const override {
      float kelvin = this->get_value () + 293.15;
      std::stringstream stream;
      stream << std::fixed << std::setprecision (2) << kelvin;
      return stream.str () + " °K";
    };
};

class station_c { // Prototype
  protected:
    std::string             name;
    uint64_t                number = 0;
    flavour_t               flavour;

  public:
    std::string  get_name ();
    void         set_name (std::string name);

    uint64_t     get_number ();
    void         set_number (uint64_t number);

    flavour_t    get_flavour ();

    station_c (
      flavour_t flavour
      ) {
      this->flavour = flavour;
    };
    virtual ~station_c () {};

    // common interface
    virtual station_c *clone () const = 0;
    //virtual void get_presentation () = 0;
};

class meteo_station_c : public station_c {
  private:
    data_vec_t temp;        // 48 hours

  public:
    meteo_station_c (
      ) : station_c (meteo) {};
    ~meteo_station_c () {};

    measurement_temp_celsius_c    get_cur_temp ();
    measurement_temp_kelvin_c     get_cur_temp_kelvin ();
    measurement_temp_fahrenheit_c get_cur_temp_fahrenheit ();

    station_c *clone () const override {
      return new meteo_station_c (*this);
    };
    //void  get_presentation () override;
    void  set_data (
      data_vec_t &temp
      );
};

class hydro_station_c : public station_c {
  private:
    // water level
    data_vec_t level;  // 144 hours (3 days)

  public:
    hydro_station_c (
      ) : station_c (hydro)
    {};
    ~hydro_station_c () {};

    measurement_impl_c get_cur_level ();

    station_c *clone () const override {
      return new hydro_station_c (*this);
    };

    //void  get_presentation () override;
    void  set_data (
      data_vec_t &level
      //data_vec_t &discharge
      );
};
#endif // METEODATA_STATION_H
