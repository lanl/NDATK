#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>

#include "Library.hh"
#include "utils.hh"
#include "translate_isomer.hh"

namespace ndatk
{
  using namespace std;

  // Construct Library of tables from input stream
  void Library::parse(istream &s)
  {
    string line;
    int sza;
    string id;

    this->get_header(s);
    while (get_logical_line(s, line)) {
      if (starts_with_nocase(line, "IDS:")) {
        while (get_logical_line(s, line)) {
          if (starts_with_nocase(line, "%%")) {
            break;
          } else {
            istringstream r(line);
            r >> sza >> id;
            ids.insert(Library::TableIdentifiers::value_type(sza, id));
          }
        }
      }
    }
  }

  // Construct library from stream and Exsdir
  Library::Library(istream &s, const Exsdir &x): CuratedData(), ids(), e(x)
  {
    Library::parse(s);
  }

  // Construct library from id and Exsdir
  Library::Library(string id, const Exsdir &x): CuratedData(), ids(), e(x) 
  {
    string filename = e.file_name(id);
    ifstream s(filename.c_str());
    if (!s) {
      string e("Cannot open file ");
      e += filename + "!";
      throw ifstream::failure(e.c_str());
    }
    Library::parse(s);
    s.close();
  }

  // Number of tables
  int Library::number_of_tables(void) const
  {
    return ids.size();
  }

  // Return table identifier isomer name
  string Library::table_identifier(string name)
  {
    string::size_type d;
    string result(""); 

    if ((d = name.find('.')) != name.npos) { // Policy: lookup name in Exsdir
      int sza = translate_isomer(name.substr(0,d));
      string s = lexical_cast<string, int>(sza) + name.substr(d);
      result = e.table_identifier(s);
    } else {                    // Policy: lookup name in Library
      int sza = translate_isomer(name);
      typedef pair<Library::TableIdentifiers::const_iterator, 
                   Library::TableIdentifiers::const_iterator> ip_type;
      ip_type ip = ids.equal_range(sza);
      szaids.clear();
      for (Library::TableIdentifiers::const_iterator it = ip.first; 
           it != ip.second; ++it) 
        szaids.push_back(it->second);
      if (!szaids.empty())
        result = szaids[0];
    }
    if (result != "")               // Change only if valid
      current_isomer = result;
    return result;
  }

  std::string Library::table_identifier(void) const
  {
    return current_isomer;
  }

  // Line or record number by table identifier
  int Library::address(void) const
  {
    return e.address(current_isomer);
  }
  // Length of binary data block or zero by table identifier
  int Library::table_length(void) const
  {
    return e.table_length(current_isomer);
  }

  // Length of binary record or zero by table identifier
  int Library::record_length(void) const
  {
    return e.record_length(current_isomer);
  }
    
  // Number of binary entries per record or zero by table identifier
  int Library::entries_per_record(void) const
  {
    return e.entries_per_record(current_isomer);
  }

  // File name by table identifier
  std::string Library::file_name(void) const
  {
    return e.file_name(current_isomer);
  }

  // Directory access route or zero by table identifier
  std::string Library::access_route(void) const
  {
    return e.access_route(current_isomer);
  }

  // Probability table flag by table identifier
  bool Library::probability_table_flag(void) const
  {
    return e.probability_table_flag(current_isomer);
  }

  // Atomic weight (u) by table identifier
  double Library::atomic_weight(void) const
  {
    return e.atomic_weight(current_isomer);
  }

  // Atomic weight ratio by table identifier
  double Library::atomic_weight_ratio(void) const
  {
    return e.atomic_weight_ratio(current_isomer);
  }

  // Temperature (MeV) by table identifier
  double Library::temperature(void) const
  {
    return e.temperature(current_isomer);
  }

}
