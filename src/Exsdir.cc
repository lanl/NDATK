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
        date = line;
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
    id = filename;
    info = "Exsdir";
  }


  // Number of tables
  int Exsdir::number_of_tables(void) const
  {
    return order.size();
  }

  // Table identifier by index
  string Exsdir::table_identifier(int i) const
  {
    return order.at(i);
  }

  // Line or record number by table identifier
  int Exsdir::address(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.address;
  }

  // Length of binary data block or zero by table identifier
  int Exsdir::table_length(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.tbl_len;
  }

  // Lenght of binary record or zero by table identifier
  int Exsdir::record_length(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.rcd_len;
  }

  // Number of binary entries per record or zero by table identifier 
  int Exsdir::entries_per_record(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.epr;
  }

  // File name by table identifier
  string Exsdir::file_name(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.name;
  }

  // Directory access route by identifier
  string Exsdir::access_route(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.route;
  }

  // Probability table flag by table identifier
  bool Exsdir::probability_table_flag(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.ptable == "ptable";
  }

  // Atomic weight by table identifier
  double Exsdir::atomic_weight(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.awr * neutron_mass;
  }

  // Atomic weight ratio by table identifier
  double Exsdir::atomic_weight_ratio(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.awr;
  }

  // Temperature by table identifier
  double Exsdir::temperature(string id) const
  {
    DirectoryData d = map_at(directory, id);
    return d.temp;
  }

}
      
