/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/commandparser.cc
 * See ../LICENSE for license information
 */
#include "../include/commandparser.hh"

commandparser_c::commandparser_c (
  int argc,
  char *argv[]
  )
{
  this->argc = argc;
  this->argv = argv;
}

char **
commandparser_c::get_argv (
  void
  )
{
  return this->argv;
}

// validation shall be handled externally
int
commandparser_c::get_commands (
  std::vector<std::pair<command_t, std::string>> &command_vec
  )
{
  int  status            = 0;
  int  option_index      = 0;
  bool location_provided = false;
  char c;

  static struct option long_options[] =
  {
    {"help",     no_argument,       0, 'h'},
    {"verbose",  no_argument,       0, 'v'},
    {"date",     required_argument, 0, 'd'},
    {"location", required_argument, 0, 'l'},
    {"type",     required_argument, 0, 't'},
    {0, 0, 0, 0},
  };

  if (argc == 1) {
    status = 1; // no commands provided
    return status;
  }

  while ((c = getopt_long (this->argc, this->get_argv (), "hvl:d:t:", long_options, &option_index)) != -1)
  {
    switch (c) {
      // help
      case 'h':
      return status = 1; // help

      // verbose
      case 'v':
      command_vec.push_back(std::make_pair(verbose, ""));
      break;

      // location
      case 'l':
      location_provided = true;
      command_vec.push_back (std::make_pair (location, std::string (optarg)));
			break;

      // datetime
      case 'd':
      command_vec.push_back (std::make_pair (date, std::string (optarg)));
      break;

      // datatype
      case 't':
      command_vec.push_back (std::make_pair (type, std::string (optarg)));
      break;
    }
  }

  if (!location_provided) {
    return 2;
  }
  return status;
}

void
commandparser_c::get_meteo_enum_map (
  std::unordered_map <std::string, meteo_datatype_t> &enum_map
  )
{
  enum_map["temp"] = temp;
  enum_map["temp_kelvin"] = temp_kelvin;
  enum_map["temp_fahrenheit"] = temp_fahrenheit;
}

void
commandparser_c::get_hydro_enum_map (
  std::unordered_map <std::string, hydro_datatype_t> &enum_map
  )
{
  enum_map["level"] = level;
}
