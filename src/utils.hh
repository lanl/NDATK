#ifndef UTILS_HH
#define UTILS_HH

#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <istream>
#include <sstream>
#include <map>

namespace ndatk {

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

  // Is string all alphas?
  extern bool is_all_alphas(const std::string &s);

  // Is string all digits?
  extern bool is_all_digits(const std::string &s);

  // Compare string to date pattern
  extern bool is_date(const std::string &);

  // Compare start of first string with second
  inline bool starts_with(std::string s1, std::string s2) {
    return 0 == s1.compare(0, s2.size(), s2);
  }

  // Compare two strings; ingnore case.
  extern int cmp_nocase(const std::string &, const std::string &);

  // Compare start of first string with second; ignore case.
  extern bool starts_with_nocase(const std::string &, const std::string &);

  // Erase initial whitespace from string.
  inline std::string ltrim(const std::string &x) {
    std::string s(x);
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space)); 
    return s;
  }

  // Erase trailing whitespace from string.
  inline std::string rtrim(const std::string &x) {
    std::string s(x);
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    return s;
  }

  // Erase whitespace surrounding string.
  inline std::string trim(const std::string &s) {
    return ltrim(rtrim(s));
  }

  // Capitalize first character, lowercase others
  extern std::string title(const std::string s);
 
  // Split string into vector of words.
  extern std::vector<std::string> split(const std::string &s);

  // Get Logical line from stream.
  extern std::istream &get_logical_line(std::istream &s, std::string &line);

  // Get quoted string from stream.
  extern std::istream &quoted_str(std::istream &is, std::string &s);

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

  /* Convert Source to Target type through stringstream.

     "Exceptional C++ Style: 40 new engineering puzzles, 
      programming problems, and solutions" pg 18
   */
  template <typename Target, typename Source>
  Target lexical_cast(Source arg)
  {
    std::stringstream interpreter;
    Target result;

    if (!(interpreter << arg) ||
        !(interpreter >> result) ||
        !(interpreter >> std::ws).eof())
      throw std::bad_cast();
    return result;
  }

}
#endif
