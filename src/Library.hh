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
    std::string table_id(std::string name) const;

  private:

    void parse(std::istream &s);

    typedef std::vector<std::string> Table;

    Table ids;                // table identifiers
  };
}
#endif
