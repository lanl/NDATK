#ifndef EXSDIR_HH
#define EXSDIR_HH

/**
   \file Exsdir.hh

   Extended cross section directory.

   \author Mark G. Gray <gray@lanl.gov>
   Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.
*/

#include <string>
#include <vector>
#include <map>
#include <istream>
#include "CuratedData.hh"

namespace ndatk
{
  /**
     \class Exsdir
     Extended cross section directory.
  */
  class Exsdir: public CuratedData
  {
  public:

    // Default constructor
    Exsdir(void): CuratedData(), order(), directory() {}

    /**
       Construct Exsdir from named file.

       \param[in] filename string
    */
    explicit Exsdir(const std::string filename);

    /** 
        Read Exsdir from stream.

        \param[in] s std::istream
        \param[in,out] e Exsdir
        \return std::istream
    */
    friend std::istream &operator>>(std::istream &s, Exsdir &e);

    /**
        Is object in valid state?

        \return true if object in valid state.
    */
    bool is_valid(void) const;

    /**
       Data file type.

       \return data file type std::string
    */
    std::string type(void) const { return std::string("ndatk_exsdir_1.0"); }

    /** 
        Number of tables.

        \return number of tables in directory.
    */
    int number_of_tables(void) const;

    /**
       Table identifier by index.
       
       \param[in] i int
       \return table identifier std::string
    */
    std::string table_identifier(int i) const;

    /**
       Table identifier by (partial) name.

       \param[in] name std::string
       \return table identifier std::string
    */
    std::string table_identifier(std::string name) const;
    
    /**
       Line or record number by table identifier.

       \param[in] id std::string
       \return line or record int
    */
    int address(std::string id) const;

    /**
       Length of binary data block or zero by table identifier.

       \param[in] id std::string
       \return length int
    */
    int table_length(std::string id) const;

    ///\return Length of binary record or zero by table identifier
    int record_length(std::string id) const;
    
    ///\return Number of binary entries per record or zero by table identifier
    int entries_per_record(std::string id) const;

    ///\return File name by table identifier
    std::string file_name(std::string id) const;

    ///\return Directory access route or zero by table identifier
    std::string access_route(std::string id) const;

    ///\return Probability table flag by table identifier
    bool probability_table_flag(std::string id) const;

    ///\return Atomic weight (u) by table identifier
    double atomic_weight(std::string id) const;

    ///\return Atomic weight ratio by table identifier
    double atomic_weight_ratio(std::string id) const;

    ///\return Temperature (MeV) by table identifier
    double temperature(std::string id) const;

    /// Define const_iterator type for Library
    typedef std::vector<std::string>::const_iterator const_iterator;
    
    /// Const_iterator to start of table identifiers
    const_iterator begin(void) const;

    /// Const_iterator to end of table identifiers
    const_iterator end(void) const;

  private:

    std::istream& get_xsdir(std::istream &s);

    // Exsdir list of table Ids
    typedef std::vector<std::string> Id_vector;
    Id_vector order;            // Identifier order

    /// XSDIR directory data
    struct DirectoryData
    {
      double awr;               // atomic weight ratio
      std::string name;         // file name
      std::string route;        // access route
      int type;                 // file type
      int address;              // address
      int tbl_len;              // table length
      int rcd_len;              // record length
      int epr;                  // number of entries per record
      double temp;              // temperature
      std::string ptable;       // probability table flag
    };
    typedef std::map<std::string, DirectoryData> Directory_map;
    Directory_map directory;    // Directory
  };
}
#endif
