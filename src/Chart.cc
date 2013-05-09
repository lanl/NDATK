#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Chart.hh"
#include "translate_Isomer.hh"
#include "utils.hh"
#include "constants.hh"

namespace ndatk
{
  using namespace std;

  // Canonicalize: convert z000 to z; pass other sza unchanged
  int canonicalize(int sza)
  {
    if (sza % 1000 == 0)  
      return sza/1000;          // Z000 -> Z
    else 
      return sza;
  }

  // Construct Chart of the Nuclides from input stream
  void Chart::parse(istream &s)
  {
    string line;
    enum states {START, TABLE, CHART}; // Parser states
    states state = START;

    int sza;
    ElementData e;
    NuclideData n;

    while (get_logical_line(s, line)) {
      if (starts_with_nocase(line, "NAME:")) {
        get_logical_line(s, name);
      } else if (starts_with_nocase(line, "DATE:")) {
        get_logical_line(s, date);
      } else if (starts_with_nocase(line, "INFO:")) {
        get_logical_line(s, info);
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

  // Construct Chart from data in stream
  Chart::Chart(std::istream& s)
  {
    Chart::parse(s);
  }

  // Construct Chart from data on filename
  Chart::Chart(std::string filename)
  {
    std::ifstream s(filename.c_str());
    Chart::parse(s);
    s.close();
  }

  // Return int value based on key
  int Chart::get(int_val::key k) const
  {
    switch (k) {
    case int_val::NUM_ELEMENTS:
      return element.size();
      break;
    case int_val::NUM_NUCLIDES:
      return nuclide.size();
      break;
    default:
      throw out_of_range("Key not found!");
    }
    return 0;
  }

  // Return vector of ints based on key
  vector<int> Chart::get(int_vec_n::key k, int sza) const
  {
    vector<int> v;
    int n = canonicalize(sza);
    switch(k) {
    case int_vec_n::ISOTOPES:
      for (Nuclide_map::const_iterator it = nuclide.begin();
           it != nuclide.end(); it++)
        if (it->first/1000 == n)
          v.push_back(it->first);
      return v;
      break;
    case int_vec_n::ISOMERS:
      for (Nuclide_map::const_iterator it = nuclide.begin();
           it != nuclide.end(); it++)
        if (it->first % 1000000 == n % 1000000)
          v.push_back(it->first);
      return v;
      break;
    default:
      throw out_of_range("Key not found!");
    }
    return v;
  }
        
  // Return string value based on key and index
  string Chart::get(string_val_n::key k, int sza) const
  {
    int n = canonicalize(sza);             // Canonicalize SZA
    switch (k) {
    case string_val_n::SYMBOL:
      return element.at(n).symbol;
      break;
    case string_val_n::NAME:
      return element.at(n).name;
      break;
    default:
      throw out_of_range("Key not found!");
    }
    return string("");
  }

  // Return string value based on key and name
  string Chart::get(string_val_x::key k, string c)
  {
    int sza = translate_Isomer(c);
    switch(k) {
    case string_val_x::NAME:
      return element.at(extract_Z(sza)).name;
      break;
    default:
      string s = "Key ";
      s += c + " not recognized!"; 
      throw out_of_range(s);
    }
  }

  // Return double value based on key and index
  double Chart::get(float_val_n::key k, int sza) const
  {
    unsigned int n = canonicalize(sza);
    if (n < element.size()) {  // Element data
      switch(k) {
      case float_val_n::AT_WGT:
        return element.at(n).at_wgt;
        break;
      case float_val_n::AWR:
        return element.at(n).at_wgt / Mass_n;
        break;
      default:
        throw out_of_range("Key not found!");
      }
    } else {
      NuclideData d = map_at(nuclide, n);
      switch (k) {            // Nuclide data
      case  float_val_n::AT_WGT:
        return d.awr * Mass_n;
        break;
      case float_val_n::AWR:
        return d.awr;
        break;
      case float_val_n::ABUNDANCE:
        return d.abundance;
        break;
      case float_val_n::HALF_LIFE:
        return d.half_life;
        break;
      default:
        throw out_of_range("Key not found!");
      }
    }
    return 0.0;
  }

  // Return double value based on key and name
  double Chart::get(float_val_x::key k, string name) const
  {
    int sza = translate_Isomer(name);
    if (extract_A(sza) == 0) {  // Element data
      int z = extract_Z(sza);
      switch(k) {
      case float_val_n::AT_WGT:
        return element.at(z).at_wgt;
        break;
      case float_val_n::AWR:
        return element.at(z).at_wgt / Mass_n;
        break;
      default:
        throw out_of_range("Key not found!");
      }
    } else {
      NuclideData d = map_at(nuclide, sza);
      switch (k) {            // Nuclide data
      case  float_val_n::AT_WGT:
        return d.awr * Mass_n;
        break;
      case float_val_n::AWR:
        return d.awr;
        break;
      case float_val_n::ABUNDANCE:
        return d.abundance;
        break;
      case float_val_n::HALF_LIFE:
        return d.half_life;
        break;
      default:
        throw out_of_range("Key not found!");
      }
    }
    return 0.0;
  }
}
