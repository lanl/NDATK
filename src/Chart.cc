#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Chart.hh"
#include "translate_isomer.hh"
#include "utils.hh"
#include "constants.hh"

// Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.

// File Description:
// Chart - Provide periodic table and chart of the nuclides data
// See: "Nuclides and Isotopes", 16ed

// Authors: Mark G. Gray <gray@lanl.gov>

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

    c.get_header(s);

    // Read rest of file
    while (get_logical_line(s, line)) {
      if (starts_with_nocase(line, CuratedData::begin_provenance)) {
        c.append_ProvenanceVector(s);
      } else if (starts_with_nocase(line, "periodic_table:")) {
        // c.append_ElementVector(s);
        while (get_logical_line(s, line)) {
          if (starts_with_nocase(line, "%%")) {
            break;
          } else {
            istringstream iline(line);
            int sza;
            Chart::ElementData e;
            iline >> sza >> e.symbol >> e.at_wgt >> e.name;
            c.elements.push_back(e);
          }
        }
      } else if (starts_with_nocase(line, "chart_of_the_nuclides:")) {
        // c.append_NuclideMap(s);
        while (get_logical_line(s, line)) {
          if (starts_with_nocase(line, "%%")) {
            break;
          } else {
            istringstream iline(line);
            Chart::NuclideData n;
            int sza;
            iline >> sza >> n.awr >> n.abundance >> n.half_life;
            c.nuclides.insert(Chart::NuclideMap::value_type(sza, n));
          }
        }
      } else {
        continue;               // Ignore unrecognized line
      }
    }
    return s;
  }

  // Construct Chart from data on filename
  Chart::Chart(string filename)
  {
    ifstream s(filename.c_str());
    if (!s) {
      string e("Cannot open file ");
      e += filename + "!";
      throw ifstream::failure(e.c_str());
    }
    s >> *this;
    s.close();
  }

  // Construct Chart from id and Exsdir
  Chart::Chart(string id, Exsdir &e)
  {
    string filename = e.abs_file_name(id, type());
    ifstream s(filename.c_str());
    if (!s) {
      string e("Cannot open file ");
      e += filename + "!";
      throw ifstream::failure(e.c_str());
    }
    s >> *this;
    s.close();
  }    

  // Number of elements in element
  int Chart::number_of_elements(void) const
  {
    return elements.size();
  }

  // Number of nuclides in nuclide
  int Chart::number_of_nuclides(void) const
  {
    return nuclides.size();
  }
  
  // Vector of isotopes in element by atomic number
  vector<int> Chart::isotopes(int Z) const
  {
    vector<int> result;
    int n = canonicalize(Z);
    for (NuclideMap::const_iterator it = nuclides.begin();
         it != nuclides.end(); it++)
      if (it->first/1000 == n)
        result.push_back(it->first);
      return result;
  }

  // Vector of isotopes in element by chemical symbol
  vector<int> Chart::isotopes(string name) const
  {
    int sza = translate_isomer(name);
    return this->isotopes(sza);
  }

  // Vector of isomers in nuclide by atomic & mass number
  vector<int> Chart::isomers(int sza) const
  {
    vector<int> result;
    int n = canonicalize(sza);
    for (NuclideMap::const_iterator it = nuclides.begin();
         it != nuclides.end(); it++)
      if (it->first % 1000000 == n % 1000000)
        result.push_back(it->first);
    return result;
  }

  // Vector of isomers in nuclide by isomer name 
  vector<int> Chart::isomers(string name) const
  {
    int sza = translate_isomer(name);
    return this->isomers(sza);
  }
 
  // Chemical symbol by atomic number
  string Chart::chemical_symbol(int Z) const
  {
    int n = canonicalize(Z);
    return elements.at(n).symbol;
  }
  // Element name by atomic number
  string Chart::element_name(int Z) const
  {
    int n = canonicalize(Z);
    return elements.at(n).name;
  }

  // Element name by isomer name
  string Chart::element_name(string name) const
  {
    int sza = translate_isomer(name);
    return this->element_name(sza);
  }
     
  // Atomic weight by state, mass & atomic number
  double Chart::atomic_weight(int sza) const
  {
    unsigned int n = canonicalize(sza);
    if (n < elements.size()) { 
      return elements.at(n).at_wgt;
    } else {
      NuclideData d = map_at(nuclides, n);
      return d.awr * neutron_mass;
    }
  }

  // Atomic weight by isomer name
  double Chart::atomic_weight(string name) const
  {
    int sza = translate_isomer(name);
    return this->atomic_weight(sza);
  }

  // Atomic weight ratio by state, atomic & mass number
  double Chart::atomic_weight_ratio(int sza) const
  {
    unsigned int n = canonicalize(sza);
    if (n < elements.size()) {
      return elements.at(n).at_wgt / neutron_mass;
    } else {
      NuclideData d = map_at(nuclides, n);
      return d.awr;
    }
  }
  
  // Atomic weight ratio by isomer name
  double Chart::atomic_weight_ratio(string name) const
  {
    int sza = translate_isomer(name);
    return this->atomic_weight_ratio(sza);
  }

  // Atom percent natural abundances by state, atomic & mass number
  double Chart::natural_abundance(int sza) const
  {
    int n = canonicalize(sza);
    NuclideData d = map_at(nuclides, n);
    return d.abundance;
  }

  // Atom percent abundances by isomer name
  double Chart::natural_abundance(string name) const
  {
    int sza = translate_isomer(name);
    return this->natural_abundance(sza);
  }

  // Half life by state, atomic, mass number
  double Chart::half_life(int sza) const
  {
    unsigned int n = canonicalize(sza);
    NuclideData d = map_at(nuclides, n);
    return d.half_life;
  }

  // Half life by isomer name
  double Chart::half_life(string name) const
  {
    int sza = translate_isomer(name);
    return this->half_life(sza);
  }

  // Atom composition of isomer name
  map<int, double> Chart::atom_comp_of(string name) const
  {
    map<int, double> result;
 
    int sza = translate_isomer(name);
    if (nuclides.find(ground_state(sza)) != nuclides.end())
      result[sza] = 1.0;
    else if (is_element(sza))
      for (auto isotope: isotopes(extract_Z(sza))) {
        double NA = natural_abundance(isotope);
        if (NA > 0.0)
          result[isotope] = NA;
      }
    return result;
  }

  // Mass composition of isomer name
  map<int, double> Chart::mass_comp_of(string name) const
  {
    map<int, double> result;
 
    int sza = translate_isomer(name);
    if (nuclides.find(ground_state(sza)) != nuclides.end())
      result[sza] = 1.0;
    else if (is_element(sza)) {
      double atomic_weight_element = atomic_weight(sza);
      for (auto isotope: isotopes(extract_Z(sza))) {
        double NA = natural_abundance(isotope);
        if (NA > 0.0)
          result[isotope] = NA * 
            atomic_weight(isotope)/atomic_weight_element;
      }
    }
    return result;
  }
}
