#ifndef CURATEDDATA_HH
#define CURATEDDATA_HH

#include <string>

namespace ndatk
{

  // Data source provenance
  class CuratedData
  {
  public:

    // Queries
    struct string_val {
      enum key {
        NAME,                   // Library name
        DATE,                   // Library date
        INFO                    // Library Info
      };
    };
    std::string get(string_val::key)const;

  protected:

    std::string name;           // Library name
    std::string date;           // Library date
    std::string info;           // Library info
  };
}
#endif
