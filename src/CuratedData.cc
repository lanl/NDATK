#include <stdexcept>
#include "CuratedData.hh"

namespace ndatk
{
  using namespace std;

  // Artifact identifier
  string CuratedData::identifier(void) const
  {
    return id;
  }

  // Artifact processing
  string CuratedData::how(void) const
  {
    return action;
  }

  // Artifact information
  string CuratedData::what(void) const
  {
    return description;
  }

  // Artifact source, process, release date(s)
  string CuratedData::when(void) const
  {
    return date;
  }

  // Artifact file location
  string CuratedData::where(void) const
  {
    return location;
  }

  // Artifact creation/processing code(s)
  string CuratedData::which(void) const
  {
    return instrument;
  }

  // Artifact author(s)
  string CuratedData::who(void) const
  {
    return agent;
  }

  // Artifact purpose
  string CuratedData::why(void) const
  {
    return reason;
  }

  // Required base class dtor
  CuratedData::~CuratedData(void) {}
}
