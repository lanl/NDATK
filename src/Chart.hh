#ifndef CHART_HH
#define CHART_HH

#include <string>
#include <vector>
#include <map>
#include <istream>
#include "CuratedData.hh"

namespace ndatk
{
  // Chart of the nuclides
  class Chart: public CuratedData
  {
  public:
    Chart(std::istream& s);
    Chart(std::string filename);

    // Queries
    typedef CuratedData::string_val string_val;
    std::string get(string_val::key k) const { 
      return CuratedData::get(k); }

    struct int_val {
      enum key {
        NUM_ELEMENTS,           // Number of elements in table
        NUM_NUCLIDES            // Number of nuclides in chart
      };
    };
    int get(int_val::key) const;
    
    struct int_vec_n {
      enum key {
        ISOTOPES,               // Vector of isotopes in element
        ISOMERS                 // Vector of isomers in isotope
      };
    };
    std::vector<int> get(int_vec_n::key, int sza) const;

    struct string_val_n {
      enum key {
        NAME,                   // Element name by Z or Z000
        SYMBOL                  // Element symbol by Z or Z000
      };
    };
    std::string get(string_val_n::key, int sza) const;

    struct string_val_x {
      enum key {
        NAME                   // Element name by symbol
      };
    };
    std::string get(string_val_x::key, std::string symbol);

    struct float_val_n {
      enum key {
        AT_WGT,                 // Atomic weight (u) by Z or SZA
        AWR,                    // Atomic weight ratio by Z or SZA
        ABUNDANCE,              // Atom percent abundance by SZA
        HALF_LIFE               // Half life (s) by SZA
      };
    };
    double get(float_val_n::key, int sza) const;

    struct float_val_x {
      enum key {
        AT_WGT,                 // Atomic weight (u) by isotope name
        AWR,                    // Atomic weight ratio by isotope name
        ABUNDANCE,              // Atom percent abundance by isotope name
        HALF_LIFE               // Half life (s) by isotope name
      };
    };
    double get(float_val_x::key, std::string name) const;
        
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
