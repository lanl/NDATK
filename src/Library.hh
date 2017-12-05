#ifndef LIBRARY_HH
#define LIBRARY_HH

/**
   \file Library.hh

   Library of isomer tables.

   \author Mark G. Gray <gray@lanl.gov>

   Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.
*/

#include <string>
#include <map>
#include <vector>
#include <istream>
#include <functional>

#include "CuratedData.hh"
#include "Exsdir.hh"

namespace ndatk
{
  /**
     \class Library

     Library of isomer tables.

     Table identifiers by canonical SZA (10^6 * nuclear state + 10^3 * 
     atomic number + mass number).

  */
  class Library: public CuratedData
  {
  public:

    /**
       Initialize Library by name and Exsdir.

       Search Exsdir for library name, open and read associated
       library file, and provide table meta-data for specified SZAs in
       library.

       \param[in] id std::string
       \param[in] e Exsdir
    */
    Library(std::string id, const Exsdir &e);

    /**
       Initialize Library by input stream and Exsdir.

       read input stream for library data, and provide table meta-data 
       for specified SZAs in library using Exsdir.

       \param[in] s std::istream
       \param[in] e Exsdir
    */
    Library(std::istream &s, const Exsdir &e);

    /**
       Data file type.

       \return type std::string
    */
    std::string type(void) const { return std::string("ndatk_library_1.0"); }

    /** Set table identifier matching name and return match.

        \param[in] name std::string
        \return Actual ID found or "" if no match
        \note Subsequent queries for record data will throw exceptions
        if ID returned is "".
    */
    std::string table_identifier(std::string name);

    /** Set temperature matching temp and return match.
        
        \param[in] temp double
        \return nearest available temperature matching temp.
        \note Set current table_identifier to nearest temperature.
    */
    double temperature(double temp);

    /**
       Number of tables in Library.

       \return number of tables int
    */
    int number_of_tables(void) const {return ids.size();} 

    /// Return current table identifier
    std::string table_identifier(void) const;

    /// Line or record number of current table identifier
    int address(void) const;

    /// Length of binary data block or zero of current table identifier
    int table_length(void) const;

    /// Length of binary record or zero of current table identifier
    int record_length(void) const;
    
    /// Number of entries per record or zero of current table identifier
    int entries_per_record(void) const;

    /// File name of current table identifier
    std::string file_name(void) const;

    /// Absolute file name of current table identifier
    std::string abs_file_name(void) const;

    /// Directory access route or zero of current table identifier
    std::string access_route(void) const;

    /// Probability table flag of current table identifier
    bool probability_table_flag(void) const;

    /// Atomic weight (u) of current table identifier
    double atomic_weight(void) const;

    /// Atomic weight ratio of current table identifier
    double atomic_weight_ratio(void) const;

    /// Temperature (MeV) of current table identifier
    double temperature(void) const;

    /// Return number of temperatures for set SZA
    int number_of_temperatures(void) const {return szaids.size();}

    /// Return vector of temperatures for set SZA
    std::vector<double> temperatures(void) const;

    /**
       Library composition of map.

       Filter composition map c through avaliable library tables.
    */
    std::map<int, double> comp_of(const std::map<int, double> &c) const;

    /**
       Library composition of name from f.

       Return {{sza, 1.0}} if sza=translate_isomer(name) is in library
       otherwise composition returned by f(name) filtered through library.

       \param[in] name Table or f name.
       \param[in] f Callback returning composition map for name.
       \returns Compsition map of name in library.
     */
    std::map<int, double> 
    comp_of(std::string name,
            std::function<std::map<int, double>(std::string)> f) const;

  private:

    typedef std::map<double, std::string> temp_map;
    typedef std::multimap<int, std::string> TableIdentifiers;

    static std::string type_;
    void parse(std::istream &s);

    TableIdentifiers ids;                // table identifiers
    const Exsdir &e;
    temp_map szaids;
    std::string current_isomer;
  };
}
/**
   \example use0_Library.cc
   Use case for single temperature Library class.

   \example use2_Library.cc
   Use case for multi-temperature Library class.
*/
#endif
