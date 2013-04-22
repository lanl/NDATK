#ifdef LIBRARY_HH
#define LIBRARY_HH

#include <istream>
#include <string>

namespace ndatk
{
  class Library
  {
  public:
    Library(const std::string &filename);
    Library(std::istream &s);

  private:

    // XSDIR directory data
    struct DirectoryData
    {
      double awr;               // atomic weight ratio
      string name;              // file name
      string route;             // access route
      int type;                 // file type
      int address;              // address
      int tbl_len;              // table length
      int rcd_len;              // record length
      int epr;                  // number of entries per record
      double temp;              // temperature
      string ptable;            // probability table flag
    };
    typedef std::map<std::string, DirectoryData> Directory_map;
    typedef std::vector<string> Id_vector;

    string name;                // Library name
    string date;                // Creation date
    string info;                // Information string
    Directory_map directory;    // Directory
    Id_vector order;            // Identifier order
  }
    

}
#endif
