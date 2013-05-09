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
    name = filename;
    info = "Exsdir";
  }

  // Return string value based on key and index
  string Exsdir::get(string_val_n::key k, int i) const
  {
    switch(k) {
    case string_val_n::ID:
      return order.at(i);
      break;
    default:
      throw out_of_range("Key not found");
    }
    return string("");          // Should never get here!
  }

  // Return integer value based on key and name
  int Exsdir::get(int_val_x::key k, string name) const
  {
    DirectoryData d = map_at(directory, name);
    switch(k) {
    case int_val_x::ADDRESS:
      return d.address;
      break;
    case int_val_x::TBL_LEN:
      return d.tbl_len;
      break;
    case int_val_x::RCD_LEN:
      return d.rcd_len;
      break;
    case int_val_x::EPR:
      return d.epr;
      break;
    default:
      throw out_of_range("Key not found");
    }
    return 0;                   // Should never get here!
  }

  // Return string value based on key and name
  string Exsdir::get(string_val_x::key k, string name) const 
  {
    DirectoryData d = map_at(directory, name);
    switch(k) {
    case string_val_x::NAME:
      return d.name;
      break;
    case string_val_x::ROUTE:
      return d.route;
      break;
    case string_val_x::PTABLE:
      return d.ptable;
      break;
    default:
      throw out_of_range("Key not found");
    }
    return string("");
  }

  // Return double value based on key and name
  double Exsdir::get(float_val_x::key k, string name) const
  {
    DirectoryData d = map_at(directory, name);
    switch(k) {
    case float_val_x::AT_WGT:
      return d.awr * Mass_n;
      break;
    case float_val_x::AWR:
      return d.awr;
      break;
    case float_val_x::TEMP:
      return d.temp;
      break;
    default:
      throw out_of_range("Key not found!");
    }
    return 0.0;
  }
}
      
