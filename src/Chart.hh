#ifndef CHART_HH
#define CHART_HH

/**
   \file Chart.hh

   Periodic table and chart of the nuclides database.

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

     Periodic table and chart of the nuclides database.

     Provide code access to curated data from the periodic table
     and chart of the nuclides.  Typical sources for this data:
         1) "Nuclides and Isotopes: Chart of the Nuclides"
         2) ENDF/B-VII, MF=1, MT=451

     Provides element names, chemical symbols, and atomic weights by 
     atomic number.  Provides nuclide atomic weights, natural abundances,
     and half-lives by canonical SZA (10^6 * nuclear state + 10^3 * 
     atomic number + mass number).

     Most of the query member functions are by name, which may throw 
     an exception if name cannot be translated, or by canonical Z or SZA, 
     which may throw an exception if it's not in data set.
  */
  class Chart: public CuratedData
  {
  public:

    /**
       Initialize empty Chart.

       Chart may be subsequently filled from file using operator>>.
    */
    Chart(void): CuratedData(), elements(), nuclides() {}

    /**
       Initialize Chart from named file.

       \param[in] filename Name of file.
       \exception ifstream::failure If I/O fails.
    */
    explicit Chart(std::string filename);

    /**
       Initialize Chart from identifier in Exsdir.

       \param[in] id Identifier in Exsdir.
       \param[in] e Exsdir.
       \exception ifstream::failure If I/O fails.
    */
    Chart(std::string id, Exsdir &e);

    /**
       Populate Chart from stream.

       \param[in] s std::istream
       \param[in,out] c Chart
       \return std::istream
    */
    friend std::istream &operator>>(std::istream &s, Chart &c);

    // Queries:
    /**
       Chart data file type.

       \return Chart file magic string.
    */
    std::string type(void) const override { return std::string("ndatk_chart_1.0"); }

    /**
       Number of elements in Chart.

       \return Number of elements in Chart
    */
    int number_of_elements(void) const;

    /** 
        Number of nuclides in Chart
        
        \return Number of nuclides in Chart
    */
    int number_of_nuclides(void) const;

    /** 
        Vector of isotopes in element by atomic number in Chart.

        \param[in] Z Atomic number of element.
        \return Vector of isotopes (canonical SZA) in element.
        \exception std::out_of_range If Z not in Chart.
    */
    std::vector<int> isotopes(int Z) const;

    /**
       Vector of isotopes in element by chemical symbol in Chart.

       \param[in] name IUPAC chemical symbol of element.
       \return Vector of isotopes (canonical SZA) in element.
       \exception std::out_of_range if chemical symbol not in symbol_to_Z
       \exception std::out_of_range If Z not in Chart.
    */
    std::vector<int> isotopes(std::string symbol) const;

    /** 
        Vector of isomers of nuclide by canonical ZA in Chart.
        
        \param[in] ZA canonical ZA of nuclide
        \return Vector of isomers of ZA.
        \exception std::out_of_range if ZA not in chart.
    */
    std::vector<int> isomers(int ZA) const;

    /**
        Vector of isomers of name in Chart.

        \param[in] name Name of nuclide.
        \return Vector of isomers of name.
        \exception std::bad_cast If S, Z, or A not integer.
        \exception std::out_of_range If chemical symbol not in symbol_to_Z
        \exception std::out_of_range If SZA not in Chart.
    */
    std::vector<int> isomers(std::string name) const;

    /** 
        Chemical symbol by atomic number in Chart.
    */
    std::string chemical_symbol(int Z) const;

    /** 
        Element name by atomic number in Chart.

        \param[in] Z Atomic number of element.
        \return Name of element with atomic number Z.
        \exception std::out_of_range If Z not in Chart.
    */
    std::string element_name(int Z) const;

    /**
       Element name by symbol in Chart.
       
       \param[in] symbol IUPAC chemical symbol of element.
       \returns Element name.
       \exception std::out_of_range If chemical symbol not in symbol_to_Z
       \exception std::out_of_range If Z not in Chart.
    */
    std::string element_name(std::string symbol) const;

    /**
       Atomic weight (u) by canonical SZA in Chart.

       \param[in] sza Nuclide or element canonical SZA.
       \return Atomic weight (u) of sza.
       \exception std::out_of_range if sza not in Chart.
    */
    double atomic_weight(int sza) const;

    /**
       Atomic weight (u) by name in Chart.

       \param[in] name Nuclide or element name.
       \return Atomic weight (u) of name.
       \exception std::bad_cast If S, Z, or A not integer.
       \exception std::out_of_range If chemical symbol not in symbol_to_Z 
       \exception std::out_of_range If sza not in Chart.
    */
    double atomic_weight(std::string name) const;

    /**
       Atomic weight ratio by canonical SZA in Chart.

       \param[in] sza Nuclide or element canonical SZA.
       \return Atomic weight ratio of nuclide or element.
       \exception std::out_of_range if sza not in Chart.
    */
    double atomic_weight_ratio(int sza) const;

    /**
       Atomic weight ratio by isomer name in Chart.

       \param[in] name Nuclide or element name.
       \return Atomic weight (u) of name.
       \exception std::bad_cast If S, Z, or A not integer.
       \exception std::out_of_range If chemical symbol not in symbol_to_Z.
       \exception std::out_of_range if sza not in Chart.
    */
    double atomic_weight_ratio(std::string name) const;

    /**
       Atom percent abundances by canonical SZA in chart.

       \param[in] Nuclide canonical SZA.
       \return Nuclide's natural atom abundance.
       \exception std::out_of_range if sza not in Chart.
    */
    double natural_abundance(int sza) const;

    /**
       Atom percent abundances by isomer name in Chart.

       \param[in] name Nuclide name.
       \return Atomic natural abundance of nuclide.
       \exception std::bad_cast If S, Z, or A not integer.
       \exception std::out_of_range If chemical symbol not in symbol_to_Z.
       \exception std::out_of_range if sza not in Chart.
    */
    double natural_abundance(std::string name) const;

    /**
       Half life (s) by canonical SZA in Chart.

       \param[in] sza Canonical SZA of nuclide.
       \return Half-life of nuclide SZA. 
       \exception std::out_of_range if sza not in Chart.
    */
    double half_life(int sza) const;

    /**
       Half life (s) of nuclide  name in Chart.

       \param[in] name Nuclide name.
       \return Half life of nuclide name.
       \exception std::bad_cast If S, Z, or A not integer.
       \exception std::out_of_range If chemical symbol not in symbol_to_Z.
       \exception std::out_of_range if sza not in Chart.
    */
    double half_life(std::string name) const;
    
    /** 
        Atom composition of isomer name in Chart.

        Return map {{sza, 1.0}} if name is nuclide, 
               map {{isotope, atom_frac},...} if name is element.

        \param[in] name Nuclide or element name.
        \return Composition map of isotope: atom fraction.
        \exception std::bad_cast If S, Z, or A not integer.
        \exception std::out_of_range If chemical symbol not in symbol_to_Z.
        \exception std::out_of_range if sza not in Chart.
    */
    std::map<int, double> atom_comp_of(std::string name) const;

    /** 
        Mass composition of isomer name in Chart.

        Return map {{sza, 1.0}} if name is nuclide, 
               map {{isotope, mass_frac},...} if name is element.

        \param[in] name Nuclide or element name.
        \return Composition map of isotope: mass fraction.
        \exception std::bad_cast If S, Z, or A not integer.
        \exception std::out_of_range If chemical symbol not in symbol_to_Z.
        \exception std::out_of_range if sza not in Chart.
    */
    std::map<int, double> mass_comp_of(std::string name) const;

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
