#ifndef CHART_HH
#define CHART_HH

#include <istream>
#include <string>
#include <vector>
#include <map>

#include "CuratedData.hh"
#include "Exsdir.hh"

namespace ndatk
{
  // Chart of the nuclides
  class Chart: public CuratedData
  {
  public:
    Chart(void): CuratedData(), element(), nuclide() {}
    explicit Chart(std::string filename);
    Chart(std::string id, Exsdir &e);

    friend std::istream &operator>>(std::istream &s, Chart &c);

    // Queries:
    // Number of elements in Chart
    int number_of_elements(void) const;

    // Number of nuclides in Chart
    int number_of_nuclides(void) const;

    // Vector of isotopes in element by atomic number or isomer name
    std::vector<int> isotopes(int Z) const;
    std::vector<int> isotopes(std::string symbol) const;

    // Vector of isomers in isotope by atomic & mass number or isomer name
    std::vector<int> isomers(int ZA) const;
    std::vector<int> isomers(std::string name) const;

    // Chemical symbol by atomic number
    std::string chemical_symbol(int Z) const;

    // Element name by atomic number or isomer name
    std::string element_name(int Z) const;
    std::string element_name(std::string symbol) const;

    // Atomic weight (u) by state & atomic & mass number or isomer name
    double atomic_weight(int sza) const;
    double atomic_weight(std::string name) const;

    // Atomic weight ratio by state & atomic & mass number or isomer name
    double atomic_weight_ratio(int sza) const;
    double atomic_weight_ratio(std::string name) const;

    // Atom percent abundances by state & atomic & mass number or isomer name
    double natural_abundance(int sza) const;
    double natural_abundance(std::string name) const;

    // Half life (s) by state & atomic & mass number or isomer name
    double half_life(int sza) const;
    double half_life(std::string name) const;

  private:

    // Periodic Table Values
    struct ElementData
    {
      std::string symbol;
      double at_wgt;
      std::string name;
    };
    typedef std::vector<ElementData> Element_vector;
    Element_vector element;     // Periodic Table

    // Chart of the Nuclides Values
    struct NuclideData
    {
      double awr;
      double abundance;
      double half_life;
    };
    typedef std::map<int, NuclideData> Nuclide_map;
    Nuclide_map nuclide;        // Chart of the Nuclides

    };
}
#endif
