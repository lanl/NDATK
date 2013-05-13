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
    std::string id(void) const; // Artifact identifier
    std::string date(void) const; // Artifact date
    std::string info(void) const; // Artifact information
    virtual ~CuratedData(void) = 0;

  protected:

    std::string id_;           // Artifact name
    std::string date_;         // Artifact date
    std::string info_;         // Artifact info
  };
}
#endif
