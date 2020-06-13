/*
 * meteodata-git
 * Stanislaw Grams <sjg@fmdx.pl>
 *
 * src/main.cc
 * See ../LICENSE for license information
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "../include/agent.hh"
#include "../include/data.hh"
#include "../include/helper.hh"
#include "../include/station.hh"
#include "../include/facade.hh"
#include "../include/commandparser.hh"
#include "../include/types.hh"

int
main (
  int argc,
  char *argv[]
  )
{
  int             status          = 0;
  bool            verbose_flag    = false;
  bool            datetime_issued = false;
  commandparser_c commparser      = commandparser_c (argc, argv);
  agent_c         *agent          = nullptr;

  std::vector<std::pair<command_t, std::string>> cmd_vec;
  std::vector<std::string>                       location_vec;
  std::vector<meteo_datatype_t>                  meteo_datatype_vec;
  std::vector<hydro_datatype_t>                  hydro_datatype_vec;
  std::unordered_map<std::string, meteo_datatype_t>    meteo_enum_map;
  std::unordered_map<std::string, hydro_datatype_t>    hydro_enum_map;

  status = commparser.get_commands (cmd_vec);
  if (status < 0) {
    helper_ns::error ("please double check command-line parameters");
    return status;
  } else if (status > 0) {
    helper_ns::print_help ();
    return status;
  }
  commparser.get_meteo_enum_map (meteo_enum_map);
  commparser.get_hydro_enum_map (hydro_enum_map);
  agent = agent_c::fetch_instance ();

  std::vector<std::pair<command_t, std::string>>::iterator cmd_iter;
  for (cmd_iter = cmd_vec.begin (); cmd_iter != cmd_vec.end (); cmd_iter++)
  {
    switch (cmd_iter->first) {
      case verbose:
        verbose_flag = true;
        helper_ns::verbose ("verbose mode enabled", verbose_flag);
        break;
      case location:
        helper_ns::verbose (cmd_iter->second + " location selected", verbose_flag);
        location_vec.push_back (cmd_iter->second);
        break;
      case date:
        if (datetime_issued != true) {
          // TODO: enable datetime issuing support
          //datetime_issued = true;
          //datetime = it.second;
        }
        break;
      case type:
        std::unordered_map<std::string, meteo_datatype_t>::iterator meteo_enum_map_it;
        std::unordered_map<std::string, hydro_datatype_t>::iterator hydro_enum_map_it;

        if ((meteo_enum_map_it = meteo_enum_map.find (cmd_iter->second)) == meteo_enum_map.end ()) {
        } else {
          meteo_datatype_vec.push_back (meteo_enum_map_it->second);
        }
        if ((hydro_enum_map_it = hydro_enum_map.find (cmd_iter->second)) == hydro_enum_map.end ()) {
        } else {
          hydro_datatype_vec.push_back (hydro_enum_map_it->second);
        }
        break;
    }
  }

  if (meteo_datatype_vec.size () == 0 &&
      hydro_datatype_vec.size () == 0) {
    helper_ns::error ("no datatype provided!");
  }

  station_facade_c *sf = nullptr;
  for (auto &loc_it: location_vec)
  {
    if (meteo_datatype_vec.size () != 0) {
      sf = new station_facade_c (agent, nullptr, nullptr, meteo);
      try {
        sf->find_station (loc_it);
        sf->fill_station_data ();

        for (auto &dty_it: meteo_datatype_vec)
        {
          helper_ns::verbose (
            "Printing data for station " +
            sf->get_station ()->get_name () +
            ", id = " +
            std::to_string (sf->get_station ()->get_number ()) +
            ", datatype = " +
            helper_ns::extract_str_from_meteo_enum_map (meteo_enum_map, dty_it),
            verbose_flag
            );

          meteo_station_c *tmp_station = (meteo_station_c *)sf->get_station();
          switch (dty_it) {
            case temp:
              helper_ns::message (tmp_station->get_cur_temp ().to_string ());
              break;
            case temp_kelvin:
              helper_ns::message (tmp_station->get_cur_temp_kelvin ().to_string ());
              break;
            case temp_fahrenheit:
              helper_ns::message (tmp_station->get_cur_temp_fahrenheit ().to_string ());
              break;
          }
        }
      } catch (...) {
        std::cerr << "Unable to prepare meteo measurements for " + loc_it << std::endl;
      }
      delete sf;
    }
    if (hydro_datatype_vec.size () != 0) {
      sf = new station_facade_c (agent, nullptr, nullptr, hydro);
      try {
        sf->find_station (loc_it);
        sf->fill_station_data ();
        for (auto &dty_it: hydro_datatype_vec)
        {
          helper_ns::verbose (
            "Parsing data for station " +
            sf->get_station ()->get_name () +
            ", id = " +
            std::to_string (sf->get_station ()->get_number ()) +
            ", datatype = " +
            helper_ns::extract_str_from_hydro_enum_map (hydro_enum_map, dty_it),
            verbose_flag
            );
          hydro_station_c *tmp_station = (hydro_station_c *)sf->get_station ();
          switch (dty_it) {
            case level:
              helper_ns::message (tmp_station->get_cur_level ().to_string ());
              break;
          }
        }
      } catch (...) {
        std::cerr << "Unable to prepare hydro measurements for " + loc_it << std::endl;
      }
      delete sf;
    }
  }
  agent_c::delete_instance ();

  return status;
}
