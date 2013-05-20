#include <stdexcept>
#include "CuratedData.hh"

namespace ndatk
{
  using namespace std;

  // Required base class dtor
  CuratedData::~CuratedData(void) {};

  // Artifact identifier
  string CuratedData::identifier(void) const
  {
    return id;
  }

  // Artifact process date
  string CuratedData::process_date(void) const
  {
    return date;
  }

  // Artifact information
  string CuratedData::information(void) const
  {
    return info;
  }
}
