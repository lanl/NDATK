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
#include <set>
#include <istream>
#include "CuratedData.hh"
#include "Finder.hh"

namespace ndatk
{
  /**
     \class Exsdir
     Extended cross section directory.

     The ndatk::Exsdir uses a ndatk::Finder to locate its curated data file,
     any include file in that file, and in returning the absolute path of 
     files in its directory.

     Since an ndatk::Exsdir reads files which can include files, recursive
     includes are possible.  This class avoids infinite recursive includes
     by maintaining a set of included files so far and a test to include a 
     file only if it is not in that set.
  */
  class Exsdir: public CuratedData
  {
  public:

    // Default data path
    static const std::string default_path;
    
    // Default constructor
    Exsdir(void);

    /**
       Construct Exsdir from named file.

       \param[in] filename string
       \param[in] path string
    */
    Exsdir(const std::string filename,
           const std::string path=Exsdir::default_path);

    /** 
        Read Exsdir from stream.

        \param[in] s std::istream
        \param[in,out] e Exsdir
        \return std::istream
    */
    friend std::istream &operator>>(std::istream &s, Exsdir &e);

    /**
       Set file search path.

       \param[in] path std::string Search path
    */
    void set_path(const std::string path) {
      aFinder.set_path(path);
    }
      
    /**
        Is object in valid state?

        \return true if object in valid state.
    */
    bool is_valid(void) const;

    /**
       Data file type.

       \return data file type std::string
    */
    std::string type(void) const override { return std::string("ndatk_exsdir_1.0"); }

    /** 
        Number of tables.

        \return number of tables in directory.
    */
    auto number_of_tables(void) const { return order.size(); }

    /**
       Table identifier by index.
       
       \param[in] i int
       \return table identifier std::string
    */
    std::string table_identifier(int i) const { return order.at(i); }

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
       \note O(n) operation
    */
    int address(std::string id) const;

    /**
       Cache directory data for id.

       \param[in] id std::string
       \note O(ln(n)) operation
    */
    void at(std::string id) const;

    /**
       Length of binary data block or zero by table identifier.

       \param[in] id std::string
       \return length int
    */
    int table_length(std::string id) const;

    /**
       Length of binary record or zero by table identifier.

       \param[in] id std::string
       \return int 
    */
    int record_length(std::string id) const;
    
    /**
       Number of binary entries per record or zero by table identifier.

       \param[in] id std::string
       \return int
    */
    int entries_per_record(std::string id) const;

    /**
       File name by table identifier.

       \param[in] id std::string
       \return std::string
    */
    std::string file_name(std::string id) const;

    /**
       Absolute path to file by id with magic string.

       \param[in] id std::string
       \return std::string
    */
    std::string abs_file_name(std::string id) const;

    /**
       Absolute path to file by id with magic string.
       
       \param[in] id std::string
       \param[in] magic std::string
       \return std::string
    */
    std::string abs_file_name(std::string id, std::string magic) const;

    /**
       Directory access route or zero by table identifier.

       \param[in] id std::string
       \return std::string
    */
    std::string access_route(std::string id) const;

    /**
       Probability table flag by table identifier.

       \param[in] id std::string
       \return std::string
    */
    bool probability_table_flag(std::string id) const;

    /**
       Atomic weight (u) by table identifier.

       \param[in] id std::string
       \return double
    */
    double atomic_weight(std::string id) const;

    /**
       Atomic weight ratio by table identifier.

       \param[in] id std::string
       \return double
    */
    double atomic_weight_ratio(std::string id) const;

    /**
       Temperature (MeV) by table identifier.

       \param[in] id std::string
       \return double
    */
    double temperature(std::string id) const;

    /// Define const_iterator type for Library
    typedef std::vector<std::string>::const_iterator const_iterator;
    
    /// Const_iterator to start of table identifiers
    const_iterator begin(void) const;

    /// Const_iterator to end of table identifiers
    const_iterator end(void) const;

    /// Path string
    std::string get_path(void) const {
      return aFinder.get_path();
    }
    
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
    mutable std::string current_id;     // Cached identifier
    mutable DirectoryData current_data; // Cached directory data
    std::set<std::string> include_guard; // limit include recursion
    Finder aFinder;                      // file search object
  };
}
#endif
