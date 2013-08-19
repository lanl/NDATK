#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <string>
#include <vector>
#include <istream>
#include "CuratedData.hh"
#include "Exsdir.hh"

namespace ndatk
{
  // Library of tables
  class Library: public CuratedData
  {
  public:

    // Construct Library from table identifier and Exsdir
    Library(std::string id, const Exsdir &e);

    // Construct Library from vector of table identifiers and Exsdir
    Library(const std::vector<std::string>  &ids_, const Exsdir &e);

    // Is object in valid state?
    bool is_valid(void) const;

    // Data file type
    std::string type(void) const;

    // Number of tables 
    int number_of_tables(void) const;

    // Return and rememeber table identifier for name
    std::string table_identifier(std::string name);

    // Return current table identifier
    std::string table_identifier(void) const;

    // Line or record number of current table identifier
    int address(void) const;

    // Length of binary data block or zero of current table identifier
    int table_length(void) const;

    // Length of binary record or zero of current table identifier
    int record_length(void) const;
    
    // Number of binary entries per record or zero of current table identifier
    int entries_per_record(void) const;

    // File name of current table identifier
    std::string file_name(void) const;

    // Directory access route or zero of current table identifier
    std::string access_route(void) const;

    // Probability table flag of current table identifier
    bool probability_table_flag(void) const;

    // Atomic weight (u) of current table identifier
    double atomic_weight(void) const;

    // Atomic weight ratio of current table identifier
    double atomic_weight_ratio(void) const;

    // Temperature (MeV) of current table identifier
    double temperature(void) const;

    // Define const_iterator type for Library
    typedef std::vector<std::string>::const_iterator const_iterator;

    // Const_iterator to start of table identifiers
    const_iterator begin(void) const;

    // Const_iterator to end of table identifiers
    const_iterator end(void) const;

  private:

    static std::string type_;
    void parse(std::istream &s);

    typedef std::vector<std::string> TableIdentifiers;
    TableIdentifiers ids;                // table identifiers
    const Exsdir &e;
    std::string current_isomer;
  };
}
#endif
