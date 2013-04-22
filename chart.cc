#include <sstream>
#include <stdexcept>
#include "chart.hh"
#include "utils.hh"

namespace ndatk
{
  // Canonicalize: convert z000 to z; pass other sza unchanged
  int canonicalize(int sza)
  {
    if (sza % 1000 == 0)  
      return sza/1000;          // Z000 -> Z
    else 
      return sza;
  }

  using namespace std;

  // Construct Chart of the Nuclides from input stream
  NuclidesChart::NuclidesChart(istream &s)
  {
    string line;
    enum states {START, TABLE, CHART}; // Parser states
    states state = START;

    int sza;
    ElementData e;
    NuclideData n;

    // function getlogicalline: get line with continuation
    while (getline(s, line)) {
      trim(line);      // remove leading, trailing whitespace
      if (line.size() > 0 && line[0] != '#') {
        if (starts_with_nocase(line, "NAME:")) {
          getline(s, line);
          trim(line);
          name = line;
        } else if (starts_with_nocase(line, "NAME:")) {
          getline(s, line);
          trim(line);
          name = line;
        } else if (starts_with_nocase(line, "NAME:")) {
          getline(s, line);
          trim(line);
          name = line;
        } else if (starts_with_nocase(line, "PERIODIC_TABLE:")) {
          state = TABLE;
        } else if (starts_with_nocase(line, "CHART_OF_THE_NUCLIDES:")) {
          state = CHART;
        } else if (state == TABLE) {
          // function split: tokenize line into words
          istringstream iline(line);
          iline >> sza >> e.symbol >> e.at_wgt >> e.name;
          element.push_back(e);
        } else if (state == CHART) {
          // function split: tokenize line into words
          istringstream iline(line);
          iline >> sza >> n.awr >> n.abundance >> n.half_life;
          nuclide.insert(Nuclide_map::value_type(sza, n));
        }
      }
    }
  }

  // Return string value based on key
  string NuclidesChart::get_string_val(string_val key) const
  {
    switch (key) {
    case LIBRARY:
      return name;
      break;
    case DATE:
      return date;
      break;
    case INFO:
      return info;
      break;
    default:
      throw out_of_range("Key not found!");
    }
  }

  // Return int value based on key
  int NuclidesChart::get_int_val(int_val key) const
  {
    switch (key) {
    case NUM_ELEMENTS:
      return element.size();
      break;
    case NUM_NUCLIDES:
      return nuclide.size();
      break;
    default:
      throw out_of_range("Key not found!");
    }
  }
        
  // Return string value based on key and index
  string NuclidesChart::get_string_val_n(string_val_n key, int sza) const
  {
    int n = canonicalize(sza);             // Canonicalize SZA
    switch (key) {
    case SYMBOL:
      return element.at(n).symbol;
      break;
    case NAME:
      return element.at(n).name;
      break;
    default:
      throw out_of_range("Key not found!");
    }
  }

  // Return double value based on key and index
  double NuclidesChart::get_float_val_n(float_val_n key, int sza) const
  {
    int n = canonicalize(sza);
    if (n < element.size()) {  // Element data
      switch(key) {
      case AT_WGT:
        return element.at(n).at_wgt;
        break;
      case AWR:
        return element.at(n).at_wgt / element.at(0).at_wgt;
        break;
      default:
        throw out_of_range("Key not found!");
      }
    } else {
      NuclideData d = map_at(nuclide, n);
      switch (key) {            // Nuclide data
      case  AT_WGT:
        return d.awr * element.at(0).at_wgt;
        break;
      case AWR:
        return d.awr;
        break;
      case ABUNDANCE:
        return d.abundance;
        break;
      case HALF_LIFE:
        return d.half_life;
        break;
      default:
        throw out_of_range("Key not found!");
      }
    }
  }
}
