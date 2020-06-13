/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/commandparser.hh
 * See ../LICENSE for license information
 */
#ifndef METEODATA_COMMANDPARSER_H
#define METEODATA_COMMANDPARSER_H
#include <stdexcept>
#include <cstdint>
#include <getopt.h>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include "helper.hh"
#include "types.hh"

class commandparser_c {
  private:
  int               argc;
  char              **argv;
  std::vector<command_t> commands;

  public:
  // constructors
  commandparser_c (int argc, char **argv);

  void set_argc   (int argc);
  int  get_argc   (void);
  void set_argv   (char **argv);
  char **get_argv (void);

  // parser methods
  int get_commands (std::vector<std::pair<command_t, std::string>> &command_vec);
  void get_meteo_enum_map (std::unordered_map <std::string, meteo_datatype_t> &enum_map);
  void get_hydro_enum_map (std::unordered_map <std::string, hydro_datatype_t> &enum_map);
};
#endif // METEODATA_COMMANDPARSER_H
