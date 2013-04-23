#include <fstream>
#include <sstream>
#include <stdexcept>
#include "library.hh"
#include "utils.hh"

namespace ndatk
{
  using namespace std;

  // Mass of neutron (U)
  static const double m_n = 1.00866491578; // "Nuclides and Isotopes" 16ed

  // Parse (e)xsdir
  void Library::parse(istream &s)
  {
    string line;
    enum states {START, AWR, DIR};
    states state = START;
    vector<string> fields;

    while (get_logical_line(s, line)) {
      if (starts_with_nocase(line, "DATAPATH")) {
        continue;             // TODO: add DATAPATH parse here
      } else if (starts_with_nocase(line, "ATOMIC WEIGH RATIOS")) {
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
        continue;               // ignore awr records
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

  // Construct Library from data in stream
  Library::Library(istream& s)
  {
    Library::parse(s);
  }

  // Construct Library from data on filename
  Library::Library(const string filename)
  {
    ifstream s(filename.c_str());
    Library::parse(s);
    s.close();
    name = filename;
    info = "(e)xsdir";
  }

  // Return string value based on key
  string Library::get(string_val::key k) const
  {
    switch (k) {
    case string_val::NAME:
      return name;
      break;
    case string_val::DATE:
      return date;
      break;
    case string_val::INFO:
      return info;
      break;
    default:
      throw out_of_range("Key not found!");
    }
  }

  string Library::get(string_val_n::key k, int i) const
  {
    switch (k) {
    case string_val_n::ID:
      return order.at(i);
      break;
    default:
      throw out_of_range("Key not found!");
    }
  }

  int Library::get(int_val_x::key k, string id) const
  {
    DirectoryData d = map_at(directory, id);
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
      throw out_of_range("Key not found!");
    }
  }
      
  std::string Library::get(string_val_x::key k, string id) const
  {
    DirectoryData d = map_at(directory, id);
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
      throw out_of_range("Key not found!");
    }
  }

  double Library::get(float_val_x::key k, string id) const
  {
    DirectoryData d = map_at(directory, id);
    switch(k) {
    case float_val_x::AT_WGT:
      return d.awr * m_n;
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
  }
}
