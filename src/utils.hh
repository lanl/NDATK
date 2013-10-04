#ifndef UTILS_HH
#define UTILS_HH

/**
   \file utils.hh

   Utility routines.

   These functions augment missing features in C++03 that should be in
   the standard library, or wrap C features with an STL interface for
   C++.  Several of the features are available in Boost, Loki, C++11,
   or will be available in C++14.

   \author Mark G. Gray <gray@lanl.gov>
   Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.
*/

#include <stdexcept>
#include <typeinfo>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <istream>
#include <sstream>
#include <map>

/**
   \namespace ndatk

   Nuclear Data Access Tool Kit.

   The Nuclear Data Access Tool Kit provides an API to identify
   continuous energy neutron transport tables consistent with a
   multigroup library name and state, atomic, and mass number
   designation.

*/
namespace ndatk {

  /** 
      Is character whitespace?

      Necessary disambiguation of polymorphic isspace in cctype.

      \param[in] c a character.
      \return true if c is whitespace.
      \see "Accelerated C++", pg 103
   */
  inline bool is_space(char c) {
    return isspace(c);
  }

  /**
     Is character not whitespace?

     Necessary disambiguation of polymorphic isspace in cctype.

     \param[in] c a character.
     \return true if c isn't whitespace.
     \see "Accelerated C++", pg 103  
   */
  inline bool not_space(char c) {
    return !isspace(c);
  }

  /**
     Is string all alphas?

     \param[in] s a std::string.
     \return true if s is all alphas.
  */
  extern bool is_all_alphas(const std::string &s);

  /** 
      Is string all digits?

      \param[in] s a std::string.
      \return true if s is all digits.
  */
  extern bool is_all_digits(const std::string &s);

  /**
     Is string date?
     
     \param[in] s a std::string.
     \return true if s matches "\d\d/\d\d/\d\d".
  */
  extern bool is_date(const std::string &s);

  /** 
      Does first string start with second string?

      \param[in] s1 a full std::string.
      \param[in] s2 a sub std::string.
      \return true if s1 starts with s2.
  */
  inline bool starts_with(std::string s1, std::string s2) {
    return 0 == s1.compare(0, s2.size(), s2);
  }

  /**
     Do strings match ignoring case?

     \param[in] s1 a std::string.
     \param[in] s2 a std::string.
     \return true if s1 matches s2 ignoring case.
  */
  extern int cmp_nocase(const std::string &s1, const std::string &s2);

  /** 
      Does first string start with second string ignoring case?

      \param[in] s1 a std::string.
      \param[in] s2 a std::string.
      \return true if s1 starts with s2 ignoring case.
  */
  extern bool starts_with_nocase(const std::string &s1, const std::string &s2);

  /** 
      Trim initial whitespace from string.

      \param[in] x a std::string.
      \return substring of x without leading whitespace.
  */
  inline std::string ltrim(const std::string &x) {
    std::string s(x);
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space)); 
    return s;
  }

  /**
     Trim trailing whitespace from string.

     \param[in] x a std::string.
     \return substring of x without trailing whitespace.
  */
  inline std::string rtrim(const std::string &x) {
    std::string s(x);
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    return s;
  }

  /** 
      Trim whitespace surrounding string.

      \param[in] s a std::string.
      \return substring of s without surrounding whitespace.
  */
  inline std::string trim(const std::string &s) {
    return ltrim(rtrim(s));
  }

  /**
     Parse value from "name: value" string.

     \param[in] s a std::string of form "name: value".
     \return value substring.
  */
  inline std::string value(const std::string &s)
  {
    return trim(s.substr(s.find(':')+1));
  }

  /**
     Capitalize first character, lowercase others.
     
     \param[in] s a std::string.
     \return Camelcase s.
  */
  extern std::string title(const std::string s);
 
  /**
     Split space delimited string into vector of tokens.
     
     \param[in] s a std::string, space delimited.
     \return std::vector of std::string tokens.
  */
  extern std::vector<std::string> split(const std::string &s);

  /**
     Split character delimited string into vector of tokens.

     \param[in] s a character delimited std::string.
     \param[in] c a character delimiter.
     \return std::vector of std::string tokens.
  */
  extern std::vector<std::string> split(const std::string &s, char c);

  /**
     Get Logical line from stream.

     Skip blank lines, truncate lines after comment character ('#'),
     append next logical line if current line ends in continuation
     characters ('\' or '+') and trim surrounding whitespace.

     \param[in,out] s a std::istream.
     \param[out] line a std::string.
     \return std::istream.
  */
  extern std::istream &get_logical_line(std::istream &s, std::string &line);

  /**
     Get quoted string from stream.
     
     \param[in,out] is a std::istream.
     \param[out] s a std::string;
     \return std::istream.
  */
  extern std::istream &quoted_str(std::istream &is, std::string &s);

  /** 
      Const accessor to value from associative container by key.

      C++ prior to C++11 does not provide a const accessor for its map
      like containers.  This routine provides that functionality.

      \param[in] container an associative container of type T.
      \param[in] key a T::value_type::first_type.
      \return value a T::value_type::second_type.
      \exception Throws std::out_of_range if key not in T.
   
      \see: http://jeetworks.org/node/111
      \remarks This could be replaced by map::at in C++11.
   */
  template <typename T>
  const typename T::value_type::second_type &
  map_at(const T &container, const typename T::value_type::first_type key)
  {
    typename T::const_iterator it = container.find(key); // O(lg n)
    if (it == container.end()) {
      throw std::out_of_range("Key not found in map!");
    }
    return it -> second;
  }

  /** 
      Convert Source type to Target type through stringstream.
   
      \param[in] arg a Source.
      \return arg as Target type.
      \see "Exceptional C++ Style: 40 new engineering puzzles, 
           programming problems, and solutions" pg 18
      \remarks This could be replaced by boost::lexical_cast.
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

  /**
     Wrap POSIX getenv (environment) with C++ interface.
     
     \param[in] name a std::string.
     \return environment value as string.
  */
  extern std::string get_env(const std::string name);

  /**
     Wrap POSIX getcwd (current working directory) with C++ interface.

     \return current working directory as string.
  */
  extern std::string get_cwd(void);

  /**
     Wrap POSIX gethostname with C++ interface.

     \return hostname as string.
  */
  extern std::string get_hostname(void);
}
#endif
