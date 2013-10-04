#ifndef CHART_HH
#define CHART_HH

/**
   \file Chart.hh

   Periodic table and chart of the nuclides.

   \author Mark G. Gray <gray@lanl.gov>

   \see "Nuclides and Isotopes", 16ed.

   Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.
*/

#include <istream>
#include <string>
#include <vector>
#include <map>

#include "CuratedData.hh"
#include "Exsdir.hh"

namespace ndatk
{
  /**
     \class Chart

     Periodic table and chart of the nuclides.

     Elements name, chemical symbol, and atomic weight by atomic
     number.
     Nuclide atomic weight, natural abundance, and half-life by
     canonical SZA (10^6 * nuclear state + 10^3 * atomic number + mass
     number).

  */
  class Chart: public CuratedData
  {
  public:

    /**
       Initialize Chart.
    */
    Chart(void): CuratedData(), elements(), nuclides() {}
    /**
       Initialize Chart from file

       \param[in] filename std::string
    */
    explicit Chart(std::string filename);

    /**
       Initialize Chart from identifier and Exsdir.

       \param[in] id std::string
       \param[in] e Exsdir
    */
    Chart(std::string id, Exsdir &e);

    /**
       Initialize Chart from stream.

       \param[in] s std::istream
       \param[in,out] c Chart
       \return std::istream
    */
    friend std::istream &operator>>(std::istream &s, Chart &c);

    // Queries:
    /**
       Data file type.

       \return type std::string
    */
    std::string type(void) const { return std::string("ndatk_chart_1.0"); }

    /**
       Number of elements in Chart.

       \return number of elements int
    */
    int number_of_elements(void) const;

    /** Number of nuclides in Chart
        
        \return number of nuclides int
    */
    int number_of_nuclides(void) const;

    /** 
        Vector of isotopes in element by atomic number.

    */
    std::vector<int> isotopes(int Z) const;
    /**
       Vector of isotopes in element by chemical symbol.
    */
    std::vector<int> isotopes(std::string symbol) const;

    /** 
        Vector of isomers in isotope by canonical ZA.
    */
    std::vector<int> isomers(int ZA) const;

    /**
        Vector of isomers in isotope by isomer name.
    */
    std::vector<int> isomers(std::string name) const;

    /** 
        Chemical symbol by atomic number.
    */
    std::string chemical_symbol(int Z) const;

    /** 
        Element name by atomic number.
    */
    std::string element_name(int Z) const;

    /**
       Element name by isomer name.
    */
    std::string element_name(std::string symbol) const;

    /**
       Atomic weight (u) by canonical SZA.
    */
    double atomic_weight(int sza) const;

    /**
       Atomic weight (u) by isomer name.
    */
    double atomic_weight(std::string name) const;

    /**
       Atomic weight ratio by canonical SZA.
    */
    double atomic_weight_ratio(int sza) const;

    /**
       Atomic weight ratio by canonical SZA.isomer name.
    */
    double atomic_weight_ratio(std::string name) const;

    /**
       Atom percent abundances by canonical SZA.
    */
    double natural_abundance(int sza) const;

    /**
       Atom percent abundances by isomer name.
    */
    double natural_abundance(std::string name) const;

    /**
       Half life (s) by canonical SZA.
    */
    double half_life(int sza) const;

    /**
       Half life (s) by isomer name.
    */
    double half_life(std::string name) const;

  private:

    /// Periodic Table Values.
    struct ElementData
    {
      std::string symbol;
      double at_wgt;
      std::string name;
    };
    typedef std::vector<ElementData> ElementVector;
    ElementVector elements;     // Periodic Table

    /// Chart of the Nuclides Values.
    struct NuclideData
    {
      double awr;
      double abundance;
      double half_life;
    };
    typedef std::map<int, NuclideData> NuclideMap;
    NuclideMap nuclides;        // Chart of the Nuclides

    };
}

/**
   \example use1_Chart.cc

   Use case for ndatk::Chart class.

   - Create ndatk::Exsdir from filename on command line.
   - Create ndatk::Chart from name and ndatk::Exsdir
   - For every element in ndatk::Chart\n
     sum_abundance = 0.0\n
     avg_awr = 0.0
     - For every isotope of element in ndatk::Chart\n
       sum_abundance += abundance\n
       avg_awr += abundance * awr
     - Compare sum_abudance to 1; avg_awr to element's awr
*/
#endif
