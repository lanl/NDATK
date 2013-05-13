#include <fstream>
#include <algorithm>
#include <functional>

#include "Library.hh"
#include "utils.hh"
#include "translate_Isomer.hh"

namespace ndatk
{
  using namespace std;

  // Construct Library of tables from input stream
  void Library::parse(istream &s)
  {
    string line;
    enum states {START, IDS};
    states state = START;
    string id_;

    while (get_logical_line(s, line)) {
      if (starts_with_nocase(line, "NAME:")) {
        get_logical_line(s, id);
      } else if (starts_with_nocase(line, "DATE:")) {
        get_logical_line(s, date);
      } else if (starts_with_nocase(line, "INFO:")) {
        get_logical_line(s, info);
      } else if (starts_with_nocase(line, "IDS:")) {
        state = IDS;
      } else if (state == IDS) {
        istringstream iline(line);
        iline >> id_;
        ids.push_back(id_);
      }
    }
  }

  Library::Library(istream &s)
  {
    Library::parse(s);
  }

  Library::Library(string filename)
  {
    ifstream s(filename.c_str());
    Library::parse(s);
    s.close();
  }

  // Return table identifier isomer name
  string Library::table_identifier(string name) const
  {
    int sza = translate_Isomer(name);
    ostringstream o;

    o << sza;
    string os(o.str());
    
    for (vector<string>::const_iterator p = ids.begin();
         p != ids.end(); p++) {
      if (starts_with_nocase(*p, os))
        return *p;
      }
    return string("");
  }

}
