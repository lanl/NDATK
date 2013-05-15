#include <ios>
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

  // Read a Chart of the Nuclides from a stream
  istream &operator>>(istream &s, Chart &c)
  {
    string line;
    enum states {START, TABLE, CHART}; // Parser states
    states state = START;

    int sza;
    
    while (get_logical_line(s, line)) {
      if (starts_with_nocase(line, "NAME:")) {
        get_logical_line(s, c.id);
      } else if (starts_with_nocase(line, "DATE:")) {
        get_logical_line(s, c.date);
      } else if (starts_with_nocase(line, "INFO:")) {
        get_logical_line(s, c.info);
      } else if (starts_with_nocase(line, "PERIODIC_TABLE:")) {
        state = TABLE;
      } else if (starts_with_nocase(line, "CHART_OF_THE_NUCLIDES:")) {
        state = CHART;
      } else if (state == TABLE) {
        // function split: tokenize line into words
        istringstream iline(line);
        Chart::ElementData e;
        iline >> sza >> e.symbol >> e.at_wgt >> e.name;
        c.element.push_back(e);
      } else if (state == CHART) {
        // function split: tokenize line into words
        istringstream iline(line);
        Chart::NuclideData n;
        iline >> sza >> n.awr >> n.abundance >> n.half_life;
        c.nuclide.insert(Chart::Nuclide_map::value_type(sza, n));
      }
    }
    return s;
  }

  // Construct Chart from data on filename
  Chart::Chart(string filename)
  {
    ifstream s;
    // s.exceptions(ifstream::failbit);
    s.open(filename.c_str());
    s >> *this;
    s.close();
  }

  // Construct Chart from id and Exsdir
  Chart::Chart(string id, Exsdir &e)
  {
    string filename = e.table_identifier(id);
    ifstream s;
    // s.exceptions(ifstream::failbit);
    s.open(filename.c_str());
    s >> *this;
    s.close();
  }    

  // Number of elements in element
  int Chart::number_of_elements(void) const
  {
    return element.size();
  }

  // Number of nuclides in nuclide
  int Chart::number_of_nuclides(void) const
  {
    return nuclide.size();
  }
  
  // Vector of isotopes in element by atomic number
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

  // Vector of isotopes in element by chemical symbol
  vector<int> Chart::isotopes(string name) const
  {
    int sza = translate_Isomer(name);
    return this->isotopes(sza);
  }

  // Vector of isomers in nuclide by atomic & mass number
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

  // Vector of isomers in nuclide by isomer name 
  vector<int> Chart::isomers(string name) const
  {
    int sza = translate_Isomer(name);
    return this->isomers(sza);
  }
 
  // Chemical symbol by atomic number
  string Chart::chemical_symbol(int Z) const
  {
    int n = canonicalize(Z);
    return element.at(n).symbol;
  }
  // Element name by atomic number
  string Chart::element_name(int Z) const
  {
    int n = canonicalize(Z);
    return element.at(n).name;
  }

  // Element name by isomer name
  string Chart::element_name(string name) const
  {
    int sza = translate_Isomer(name);
    return this->element_name(sza);
  }
     
  // Atomic weight by state, mass & atomic number
  double Chart::atomic_weight(int sza) const
  {
    unsigned int n = canonicalize(sza);
    if (n < element.size()) { 
      return element.at(n).at_wgt;
    } else {
      NuclideData d = map_at(nuclide, n);
      return d.awr * neutron_mass;
    }
  }

  // Atomic weight by isomer name
  double Chart::atomic_weight(string name) const
  {
    int sza = translate_Isomer(name);
    return this->atomic_weight(sza);
  }

  // Atomic weight ratio by state, atomic & mass number
  double Chart::atomic_weight_ratio(int sza) const
  {
    unsigned int n = canonicalize(sza);
    if (n < element.size()) {
      return element.at(n).at_wgt / neutron_mass;
    } else {
      NuclideData d = map_at(nuclide, n);
      return d.awr;
    }
  }
  
  // Atomic weight ratio by isomer name
  double Chart::atomic_weight_ratio(string name) const
  {
    int sza = translate_Isomer(name);
    return this->atomic_weight_ratio(sza);
  }

  // Atom percent natural abundances by state, atomic & mass number
  double Chart::natural_abundance(int sza) const
  {
    int n = canonicalize(sza);
    NuclideData d = map_at(nuclide, n);
    return d.abundance;
  }

  // Atom percent abundances by isomer name
  double Chart::natural_abundance(string name) const
  {
    int sza = translate_Isomer(name);
    return this->natural_abundance(sza);
  }

  // Half life by state, atomic, mass number
  double Chart::half_life(int sza) const
  {
    unsigned int n = canonicalize(sza);
    NuclideData d = map_at(nuclide, n);
    return d.half_life;
  }

  // Half life by isomer name
  double Chart::half_life(string name) const
  {
    int sza = translate_Isomer(name);
    return this->half_life(sza);
  }
}
