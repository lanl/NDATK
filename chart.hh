#ifndef CHART_HH
#define CHART_HH

#include <string>
#include <vector>
#include <map>
#include <istream>

namespace ndatk
{
  class NuclidesChart
  {
  public:
    NuclidesChart(std::istream &s);

    // Queries
    enum string_val {
      LIBRARY,                  // Library name
      DATE,                     // Library date
      INFO                      // Library Info
    };
    std::string get_string_val(string_val key)const;

    enum int_val {
      NUM_ELEMENTS,             // Number of elements in table
      NUM_NUCLIDES              // Number of nuclides in chart
    };
    int get_int_val(int_val key) const;

    enum string_val_n {
      NAME,                      // Element name by Z or Z000
      SYMBOL                   // Element symbol by Z or Z000
    };
    std::string get_string_val_n(string_val_n key, int sza) const;

    enum float_val_n {
      AT_WGT,                   // Atomic weight (u) by Z or SZA
      AWR,                      // Atomic weight ratio by Z or SZA
      ABUNDANCE,                // Atom percent abundance by SZA
      HALF_LIFE                 // Half life (s) by SZA
    };
    double get_float_val_n(float_val_n key, int sza) const;

  private:
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

    std::string name;           // Library name
    std::string date;           // Library date
    std::string info;           // Library info
    Element_vector element;     // Periodic Table
    Nuclide_map nuclide;        // Chart of the Nuclides

    };
}
#endif
