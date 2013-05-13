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
        get_logical_line(s, id_);
      } else if (starts_with_nocase(line, "DATE:")) {
        get_logical_line(s, date_);
      } else if (starts_with_nocase(line, "INFO:")) {
        get_logical_line(s, info_);
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

  int Chart::num_elements(void) const
  {
    return element.size();
  }

  int Chart::num_nuclides(void) const
  {
    return nuclide.size();
  }
  
  vector<int> Chart::isotopes(int Z) const
  {
    vector<int> result;
    int n = canonicalize(Z);
    for (Nuclide_map::const_iterator it = nuclide.begin();
         it != nuclide.end(); it++)
      if (it->first/1000 == n)
        result.push_back(it->first);
      return result;
  }

  vector<int> Chart::isotopes(string name) const
  {
    int sza = translate_Isomer(name);
    return this->isotopes(sza);
  }

  vector<int> Chart::isomers(int sza) const
  {
    vector<int> result;
    int n = canonicalize(sza);
    for (Nuclide_map::const_iterator it = nuclide.begin();
         it != nuclide.end(); it++)
      if (it->first % 1000000 == n % 1000000)
        result.push_back(it->first);
    return result;
  }

  vector<int> Chart::isomers(string name) const
  {
    int sza = translate_Isomer(name);
    return this->isomers(sza);
  }
 
  string Chart::symbol(int Z) const
  {
    int n = canonicalize(Z);
    return element.at(n).symbol;
  }
  
  string Chart::name(int Z) const
  {
    int n = canonicalize(Z);
    return element.at(n).name;
  }
  string Chart::name(string name) const
  {
    int sza = translate_Isomer(name);
    return this->name(sza);
  }
     
  double Chart::at_wgt(int sza) const
  {
    unsigned int n = canonicalize(sza);
    if (n < element.size()) { 
      return element.at(n).at_wgt;
    } else {
      NuclideData d = map_at(nuclide, n);
      return d.awr * neutron_mass;
    }
  }

  double Chart::at_wgt(string name) const
  {
    int sza = translate_Isomer(name);
    return this->at_wgt(sza);
  }

  double Chart::awr(int sza) const
  {
    unsigned int n = canonicalize(sza);
    if (n < element.size()) {
      return element.at(n).at_wgt / neutron_mass;
    } else {
      NuclideData d = map_at(nuclide, n);
      return d.awr;
    }
  }
  
  double Chart::awr(string name) const
  {
    int sza = translate_Isomer(name);
    return this->awr(sza);
  }

  double Chart::half_life(int sza) const
  {
    unsigned int n = canonicalize(sza);
    NuclideData d = map_at(nuclide, n);
    return d.half_life;
  }

  double Chart::half_life(string name) const
  {
    int sza = translate_Isomer(name);
    return this->half_life(sza);
  }
}
