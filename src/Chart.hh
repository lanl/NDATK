#ifndef CHART_HH
#define CHART_HH

#include <istream>
#include <string>
#include <vector>
#include <map>

#include "CuratedData.hh"

namespace ndatk
{
  // Chart of the nuclides
  class Chart: public CuratedData
  {
  public:
    explicit Chart(std::istream& s);
    explicit Chart(std::string filename);

    // Queries:
    // Number of elements in Chart
    int num_elements(void) const;

    // Number of nuclides in Chart
    int num_nuclides(void) const;

    // Vector of isotopes in element by:
    std::vector<int> isotopes(int Z) const; // atomic number
    std::vector<int> isotopes(std::string symbol) const; // chemical symbol

    // Vector of isomers in isotope by:
    std::vector<int> isomers(int ZA) const; // atomic & mass number
    std::vector<int> isomers(std::string name) const; // isotopic name

    // Chemical symbol by atomic number
    std::string symbol(int Z) const;

    // Element name by:
    std::string name(int Z) const; // atomic number
    std::string name(std::string symbol) const; // chemical symbol

    // Atomic weight (u) by:
    double at_wgt(int sza) const; // state & atomic & mass number
    double at_wgt(std::string name) const; // isomer name

    // Atomic weight ratio by:
    double awr(int sza) const;  // state & atomic & mass number
    double awr(std::string name) const; // isomer name

    // Atom percent abundances by:
    double abundance(int sza) const; // state & atomic & mass number
    double abundance(std::string name) const; // isomer name

    // Half life (s) by:
    double half_life(int sza) const; // state & atomic & mass number
    double half_life(std::string name) const; // isomer name

  private:

    void parse(std::istream& s);

    // Periodic Table Values
    struct ElementData
    {
      std::string symbol;
      double at_wgt;
      std::string name;
    };
    typedef std::vector<ElementData> Element_vector;

    // Chart of the Nuclides Values
    struct NuclideData
    {
      double awr;
      double abundance;
      double half_life;
    };
    typedef std::map<int, NuclideData> Nuclide_map;

    Element_vector element;     // Periodic Table
    Nuclide_map nuclide;        // Chart of the Nuclides

    };
}
#endif
