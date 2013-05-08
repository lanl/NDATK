#include <stdexcept>
#include "provendata.hh"

namespace ndatk
{
  using namespace std;

  // Return string value based on key
  string ProvenData::get(string_val::key k) const
  {
    switch (k) {
    case string_val::NAME:
      return name;
      break;
    case string_val::DATE:
      return date;
      break;
    case string_val::INFO:
      return info;
      break;
    default:
      throw out_of_range("Key not found!");
    }
  }
}
