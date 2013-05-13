#include <stdexcept>
#include "CuratedData.hh"

namespace ndatk
{
  using namespace std;

  // Required base class dtor
  CuratedData::~CuratedData(void) {};

  string CuratedData::id(void) const
  {
    return id_;
  }

  string CuratedData::date(void) const
  {
    return date_;
  }

  string CuratedData::info(void) const
  {
    return info_;
  }
}
