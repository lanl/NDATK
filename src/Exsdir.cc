#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Exsdir.hh"
#include "utils.hh"
#include "constants.hh"

namespace ndatk
{
  using namespace std;

  // Parse extended cross section directory
  void Exsdir::parse(istream &s)
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
        date_ = line;
      } else if (starts_with_nocase(line, "DIRECTORY")) {
        state = DIR;
      } else if (starts_with_nocase(line, "INCLUDE")) {
        fields = split(line);
        ifstream f1(fields[1].c_str());
        parse(f1);
        f1.close();
      } else if (state == AWR) {
        continue;               // TODO: add AWR parse here
      } else if (state == DIR) {
        string id;
        DirectoryData d;
        istringstream r(line);
        r >> id >> d.awr >> d.name >> d.route >> d.type
          >> d.address >> d.tbl_len >> d.rcd_len >> d.epr
          >> d.temp >> d.ptable;
        directory.insert(Directory_map::value_type(id, d));
        order.push_back(id);
      }
    }
  }

  // Construct Exsdir from data in stream
  Exsdir::Exsdir(istream &s)
  {
    Exsdir::parse(s);
  }

  // Construct Exsdir from data on named file
  Exsdir::Exsdir(const string filename)
  {
    ifstream s(filename.c_str());
    Exsdir::parse(s);
    s.close();
    id_ = filename;
    info_ = "Exsdir";
  }


  // Number of table identifiers
  int Exsdir::num_id(void) const
  {
    return order.size();
  }

  // Table identifier by index
  string Exsdir::table_id(int i) const
  {
    return order.at(i);
  }

  int Exsdir::address(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.address;
  }

  int Exsdir::tbl_len(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.tbl_len;
  }

  int Exsdir::rcd_len(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.rcd_len;
  }

  int Exsdir::epr(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.epr;
  }

  string Exsdir::name(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.name;
  }

  string Exsdir::route(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.route;
  }

  bool Exsdir::ptable(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.ptable == "ptable";
  }

  double Exsdir::at_wgt(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.awr * neutron_mass;
  }

  double Exsdir::awr(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.awr;
  }

  double Exsdir::temp(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.temp;
  }

}
      
