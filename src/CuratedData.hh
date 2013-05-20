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
    std::string identifier(void) const; // Artifact identifier
    std::string process_date(void) const; // Artifact date
    std::string information(void) const; // Artifact information
    virtual ~CuratedData(void) = 0;

  protected:

    std::string id;           // Artifact name
    std::string date;         // Artifact date
    std::string info;         // Artifact info
  };
}
#endif
