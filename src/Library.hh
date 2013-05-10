#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <string>
#include <vector>
#include <istream>
#include "CuratedData.hh"

namespace ndatk
{
  // Library of tables
  class Library: public CuratedData
  {
  public:
    Library(std::istream& s);
    Library(std::string filename);

    // Queries
    typedef CuratedData::string_val string_val;
    std::string get(string_val::key k) const { 
      return CuratedData::get(k); }

    struct string_val_x {
      enum key {
        ID                      // Table identifier
      };
    };
    std::string get(string_val_x::key, std::string name) const;

  private:

    void parse(std::istream &s);

    typedef std::vector<std::string> Table;

    Table ids;                // table identifiers
  };
}
#endif
