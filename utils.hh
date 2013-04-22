#ifndef UTILS_HH
#define UTILS_HH

#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <istream>
#include <sstream>

namespace ndatk {

  /* Const accessor to map.
   *
   * See: http://jeetworks.org/node/111
   */
  template <typename T>
  const typename T::value_type::second_type &
  map_at(const T &container, const typename T::value_type::first_type key)
  {
    typename T::const_iterator it = container.find(key);
    if (it == container.end()) {
      throw std::out_of_range("Key not found in map!");
    }
    return it -> second;
  }

  /* Convert string to T
   *
   */
  template <typename T>
  bool from_string(T &t, const std::string &s)
  {
    std::istringstream iss(s);
    return !(iss >> t).fail();
  }

  /* Return true if c is whitespace.
   *
   * Necessary disambiguation of polymorphic isspace in cctype.
   * See "Accelerated C++", pg 103  
   */
  inline bool is_space(char c) {
    return isspace(c);
  }

  /* Return true if c isn't whitespace.
   *
   * Necessary disambiguation of polymorphic isspace in cctype.
   * See "Accelerated C++", pg 103  
   */
  inline bool not_space(char c) {
    return !isspace(c);
  }

  // Erase initial whitespace from string.
  inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space)); 
    return s;
  }

  // Erase trailing whitespace from string.
  inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    return s;
  }

  // Erase whitespace surrounding string.
  inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
  }

  // Compare two strings; ingnore case.
  extern int cmp_nocase(const std::string &, const std::string &);

  // Compare start of first string with second; ignore case.
  extern bool starts_with_nocase(const std::string &, const std::string &);

  // Split string into vector of words.
  extern std::vector<std::string> split(const std::string &s);

  // Get Logical line from stream.
  extern std::istream &get_logical_line(std::istream &s, std::string &line);
}
#endif
