#ifndef EXSDIR_HH
#define EXSDIR_HH

#include <string>
#include <vector>
#include <map>
#include <istream>
#include "CuratedData.hh"

namespace ndatk
{
  // Extended cross section directory
  class Exsdir: public CuratedData
  {
  public:

    Exsdir(const std::string filename);
    Exsdir(std::istream &s);

    // Queries
    typedef CuratedData::string_val string_val;
    std::string get(string_val::key k) const { return CuratedData::get(k); }

    struct string_val_n {
      enum key {
        ID                      // ID by index
      };
    };
    std::string get(string_val_n::key, int i) const;

    struct int_val_x {
      enum key {
        ADDRESS,                // Line or Record number by ID
        TBL_LEN,                // Length of data block by ID
        RCD_LEN,                // Length of Type 2 file record by ID
        EPR                     // Number of Type 2 entries per record by ID
      };
    };
    int get(int_val_x::key, std::string id) const;

    struct string_val_x {
      enum key {
        NAME,                   // File name by ID
        ROUTE,                  // Access Route by ID
        PTABLE                  // Probability Table Flag by ID
      };
    };
    std::string get(string_val_x::key, std::string id) const;

    struct float_val_x {
      enum key {
        AT_WGT,                 // Atomic weight (u) by ID
        AWR,                    // Atomic weight ratio by ID
        TEMP                    // Temperature (MeV) by ID
      };
    };
    double get(float_val_x::key, std::string id) const;

  private:

    void parse(std::istream& s);

    // Exsdir list of table Ids
    typedef std::vector<std::string> Id_vector;

    // XSDIR directory data
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
    Id_vector order;            // Identifier order
  };
}
#endif
