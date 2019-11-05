#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Exsdir.hh"
#include "utils.hh"
#include "constants.hh"

namespace ndatk
{
  using namespace std;

  const Exsdir::PathList_t Exsdir::default_path = {
#if _WIN32
    "C:\\Users\\Public\\NuclearData\\ndatk\\1.0.2",
    "C:\\Users\\Public\\NuclearData\\ndatk\\data" 
#else
    "/opt/local/codes/data/nuclear/ndatk/data"
    "/opt/local/codes/data/nuclear/ndatk/1.0.2"
    "/usr/projects/data/nuclear/ndatk/data"
    "/usr/projects/data/nuclear/ndatk/1.0.2"
    "/usr/gapps/lanl-data/nuclear/ndatk/data"
    "/usr/gapps/lanl-data/nuclear/ndatk/1.0.2"
#endif
  };

  istream& Exsdir::get_xsdir(istream& s)
  {
    string line;
    enum states {START, AWR, DIR};
    states state = START;
    vector<string> fields;

    while (get_logical_line(s, line)) {
      if (starts_with_nocase(line, "DATAPATH")) {
        continue;               // TODO: add DATAPATH parse here
      } else if (starts_with_nocase(line, "ATOMIC WEIGHT RATIOS")) {
        state = AWR;
      } else if (is_date(line)) {
        continue;
      } else if (starts_with_nocase(line, "DIRECTORY")) {
        state = DIR;
      } else if (starts_with_nocase(line, "INCLUDE")) {
        fields = split(line);
        // Include file if not already included
        if (include_guard.find(fields[1]) == include_guard.end()) {
          include_guard.insert(fields[1]); // add to include list
          // Should I check for a provenance type?
          ifstream f1(aFinder.abs_path(fields[1]).c_str());
          if (!f1) {
            string e("Cannot open file ");
            e += fields[1] + "!";
            throw ifstream::failure(e.c_str());
          }
          get_xsdir(f1);
          f1.close();
        }
      } else if (state == AWR) {
        continue;               // TODO: add AWR parse here
      } else if (state == DIR) {
        string id;
        Exsdir::DirectoryData d;
        istringstream r(line);
        r >> id >> d.awr >> d.name >> d.route >> d.type
          >> d.address >> d.tbl_len >> d.rcd_len >> d.epr
          >> d.temp >> d.ptable;
        directory.insert(Exsdir::Directory_map::value_type(id, d));
        order.push_back(id);
      }
    }
    return s;
  }

  // Read an Extended cross section directory from a stream
  istream &operator>>(istream &s, Exsdir &e)
  {
    e.get_header(s);
    e.get_xsdir(s);
    return s;
  }

  // Default construct Exsdir
  Exsdir::Exsdir(void): aFinder(Exsdir::default_path)
  {
  }

  // Construct Exsdir from data on named file with optional path
  Exsdir::Exsdir(const string& filename,
                 const PathList_t& path): aFinder(path)
  {
    string abs_filename(aFinder.abs_path(filename, type()));

    ifstream s(abs_filename);
    if (!s) {
      string e("Cannot open file ");
      e += filename + "  " + abs_filename + "[ " + aFinder.get_path() + "] !";
      throw ifstream::failure(e.c_str());
    }
    include_guard.insert(filename); // add filename to include list
    s >> *this;
    s.close();
  }

  // Is object in valid state?
  bool Exsdir::is_valid(void) const
  {
      return std::none_of(order.begin(), order.end(), [&](const auto& n) { return directory.find(n) == directory.end(); });
  }

  // Table identifier by (partial) name
  string Exsdir::table_identifier(string prefix) const
  {
	  auto p = find_if(order.begin(), order.end(), [=](const std::string& name) { return starts_with(name, prefix); });
      return p != order.end() ? *p : std::string{};
  }

  void Exsdir::at(string id) const
  {
    if (id != current_id) {
      current_data = map_at(directory, id);
      current_id = id;
    }
    return;
  } 

  // Line or record number by table identifier
  int Exsdir::address(string id) const
  {
    this->at(id);
    return current_data.address;
  }

  // Length of binary data block or zero by table identifier
  int Exsdir::table_length(string id) const
  {
    this->at(id);
    return current_data.tbl_len;
  }

  // Length of binary record or zero by table identifier
  int Exsdir::record_length(string id) const
  {
    this->at(id);
    return current_data.rcd_len;
  }

  // Number of binary entries per record or zero by table identifier 
  int Exsdir::entries_per_record(string id) const
  {
    this->at(id);
    return current_data.epr;
  }

  // File name by table identifier
  string Exsdir::file_name(string id) const
  {
    this->at(id);
    return current_data.name;
  }

  // Absolute path to readable file by table identifier
  // N.B. This routine does not use access route!!!
  string Exsdir::abs_file_name(string id) const
  {
    this->at(id);
    return aFinder.abs_path(current_data.name);
  }

  // Absolute path to readable file with magic string by table identifier
  string Exsdir::abs_file_name(string id, string magic) const
  {
    this->at(id);
    return aFinder.abs_path(current_data.name, magic);
  }

  // Directory access route by identifier
  string Exsdir::access_route(string id) const
  {
    this->at(id);
    return current_data.route;
  }

  // Probability table flag by table identifier
  bool Exsdir::probability_table_flag(string id) const
  {
    this->at(id);
    return current_data.ptable == "ptable";
  }

  // Atomic weight by table identifier
  double Exsdir::atomic_weight(string id) const
  {
    this->at(id);
    return current_data.awr * neutron_mass;
  }

  // Atomic weight ratio by table identifier
  double Exsdir::atomic_weight_ratio(string id) const
  {
    this->at(id);
    return current_data.awr;
  }

  // Temperature by table identifier
  double Exsdir::temperature(string id) const
  {
    this->at(id);
    return current_data.temp;
  }

  // Iterator to start of table identifiers in Exsdir
  Exsdir::const_iterator Exsdir::begin(void) const
  {
    return order.begin();
  }

  // Iterator to end of table identifiers in Exsdir
  Exsdir::const_iterator Exsdir::end(void) const
  {
    return order.end();
  }

}
      
