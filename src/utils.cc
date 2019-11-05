#include <cstdlib>
#include <cstdio>
#if _WIN32
#include <process.h>
#include <windows.h>
#define PATH_MAX _MAX_PATH
#include <direct.h>
#include <io.h>
bool realpath(const char* rel, char* abs) { return _fullpath(abs, rel, _MAX_PATH) != NULL; }
#pragma warning( disable : 4244 4996)
#else
#include <unistd.h>
#endif
#include <limits.h>
#include "utils.hh"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

namespace ndatk {
  using namespace std;

  // Is string blank or all alphas?
  bool is_all_alphas(const string &s)
  {
      return boost::algorithm::all(s, boost::algorithm::is_alpha());
  }

  // Is string blank or all decimal digits?
  bool is_all_digits(const string &s)
  {
      return boost::algorithm::all(s, boost::algorithm::is_digit());
  }

  // Compare start of string to pattern "\d\d/\d\d/\d\d"
  bool is_date(const string &s)
  {

    if (s.size() < 8 || s.size() > 10) return false;

    for (string::size_type i = 0;  i < 8; i++) {
      switch (i) {
      case 2:
      case 5:
        if (s[i] != '/') return false;
        break;
      default:
        if (!isdigit(s[i])) return false;
      }
    }
    return true;
  }
            
  // Compare two strings ignoring case.
  //
  // See B. Stroustrup, "The C++ Programming Language, 3ed, p. 591
  int cmp_nocase(const string &s1, const string &s2)
  {
      return boost::algorithm::iequals(s1, s2) ? 0 : 1;
  }

  // Compare the start of the first string with the second, ignoring case.
  bool starts_with_nocase(const string &s1, const string s2)
  {
      return boost::algorithm::istarts_with(s1, s2);
  }

  // Capitalize first character, lowercase remaining characters
  string title(const string &s)
  {
      auto result = boost::algorithm::to_lower_copy(s);
      result[0] = ::toupper(result[0]);   // Uppercase first character
      return result;
  }

  // Split space delimited string into vector of words.
  // See "Accelerated C++" p. 103
  std::vector<std::string> split(const string &s)
  {
    std::vector<std::string> ret;
    boost::algorithm::split(ret, s, boost::algorithm::is_space(), boost::algorithm::token_compress_off);
    return ret;
  }

  // Split character delimited string into vector of words.
  std::vector<std::string> split(const string &s, char c)
  {
      std::string delim{ c };
      std::vector<std::string> ret;
      boost::algorithm::split(ret, s, boost::algorithm::is_any_of(delim), boost::algorithm::token_compress_off);
      return ret;
  }

  // Get Logical Line
  //
  // Get physical line from stream,
  // truncate at comment character ('#'),
  // trim leading, following whitespace,
  // repeat until non-empty; 
  // append next logical line from stream if non-empty 
  // line ends in continuation characters '\' or '+'.
  // Returns stream as I/O status.
  istream &get_logical_line(istream &s, string &line)
  {
      while (getline(s, line)) {
        string::iterator j = line.end();
        line.erase(find(line.begin(), j, '#'), j); // remove trailing comment
        line = trim(line);      // remove surrounding spaces
        if (!line.empty()) {    // got non-blank stripped physical line
          j = line.end() - 1;             
          if (*j == '\\' || *j == '+') {  // concatenate rest of line
            *j = ' ';
            string rest;        // continuation line(s)
            get_logical_line(s, rest);
            line.append(rest);
          }
          break;                // got non-blank stripped logical line
        }
        // got blank stripped physical line; process next physical line
    }          
    return s;
  }

  // Does first logical line of file contain magic string?
  bool file_starts_with(const string &filename, const string& magic)
  {
      if (filename.empty()) { return false; }
    ifstream s(filename);
    string first_line;
    if (s && get_logical_line(s, first_line))
      return first_line.find(magic) != string::npos;
    else
      return false;
  }

  // Wrap POSIX getenv to get environment string with C++ interface
  string get_env(const std::string &name)
  {
    const char *buf = getenv(name.c_str());
    if (buf != NULL)
      return string(buf);
    else
      return string("");
  }

  // Wrap POSIX getcwd to get current working directory with C++ interface
  string get_cwd(void)
  {
      return boost::filesystem::current_path().string();
  }

  // Wrap POSIX gethostname
  string get_hostname(void)
  {
#if defined _WIN32
	  return "localhost";
#elif defined __APPLE__
    auto name = getenv("HOSTNAME");
    return name ? std::string{name} : std::string{};
#elif defined __linux__
    char buf[HOST_NAME_MAX];
    return gethostname(buf, HOST_NAME_MAX) ? string{""} : string{buf};
#else
    return {};
#endif
  }

  // Wrap POSIX access to test if file exists and is readable
  bool is_readable(const string &filename)
  {
//     auto accessFlags = boost::filesystem::status(filename).permissions();
//     return (accessFlags & boost::filesystem::perms::others_read) != boost::filesystem::perms::no_perms;
#if _WIN32
    return _access_s(filename.c_str(), 4) == 0;
#else
	return access(filename.c_str(), R_OK) == 0;
#endif
  }

}
