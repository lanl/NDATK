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

    explicit Exsdir(const std::string filename);
    explicit Exsdir(std::istream &s);

    // Queries

    // Number of table
    int number_of_tables(void) const;

    // Table identifier by index
    std::string table_identifier(int i) const;

    // Line or record number by table identifier
    int address(std::string id) const;

    // Length of binary data block or zero by table identifier
    int table_length(std::string id) const;

    // Length of binary record or zero by table identifier
    int record_length(std::string id) const;
    
    // Number of binary entries per record or zero by table identifier
    int entries_per_record(std::string id) const;

    // File name by table identifier
    std::string file_name(std::string id) const;

    // Directory access route or zero by table identifier
    std::string access_route(std::string id) const;

    // Probability table flag by table identifier
    bool probability_table_flag(std::string id) const;

    // Atomic weight (u) by table identifier
    double atomic_weight(std::string id) const;

    // Atomic weight ratio by table identifier
    double atomic_weight_ratio(std::string id) const;

    // Temperature (MeV) by table identifier
    double temperature(std::string id) const;

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
