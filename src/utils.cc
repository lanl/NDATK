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

namespace ndatk {
  using namespace std;

  // Is string blank or all alphas?
  bool is_all_alphas(const string &s)
  {
    for (string::size_type i = 0; i < s.size(); i++)
      if (!isalpha(s[i]))
        return false;
    return true;
  }

  // Is string blank or all decimal digits?
  bool is_all_digits(const string &s)
  {
    for (string::size_type i = 0; i < s.size(); i++)
      if (!isdigit(s[i]))
        return false;
    return true;
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
    typedef string::const_iterator iter;
    iter p1;
    iter p2;

    for (p1 = s1.begin(), p2 = s2.begin(); 
         p1 != s1.end() && p2 != s2.begin(); p1++, p2++)
      if (toupper(*p1) != toupper(*p2))
        return (toupper(*p1) < toupper(*p2)) ? -1: 1;
    return s2.size() > s1.size() ? 1 : -1;
  }

  // Compare the start of the first string with the second, ignoring case.
  bool starts_with_nocase(const string &s1, const string s2)
  {
    typedef string::const_iterator iter;
    iter p1;
    iter p2;

    for (p1 = s1.begin(), p2 = s2.begin(); 
         p1 != s2.end() && p2 != s2.end(); p1++, p2++)
      if (toupper(*p1) != toupper(*p2))
        return false;
    return (s2.size() > s1.size()) ? false: true;
  }

  // Capitalize first character, lowercase remaining characters
  string title(const string &s)
  {
    string t = s;
	t[0] = toupper(t[0]);   // Uppercase first character
	for (auto i = 1; i < t.size(); i++)
        t[i] = tolower(t[i]);   // Lowercase remaining characters
    return t;
  }

  // Split space delimited string into vector of words.
  // See "Accelerated C++" p. 103
  vector<string> split(const string &s)
  {
    typedef string::const_iterator iter;
    iter i, j, k;
    vector<string> ret;
    
    for (i = s.begin(), k = s.end(); i != k; i = j) {
      i = find_if(i, k, not_space); // find begin of next word
      j = find_if(i, k, is_space);  // find end of next word
      if (i != k)
        ret.push_back(string(i, j));
    }
    return ret;
  }

  // Split character delimited string into vector of words.
  vector<string> split(const string &s, char c)
  {
    string::size_type start;
    string::size_type end;
    vector<string> ret;
    
    for (start = 0; (end = s.find(c, start)) != string::npos; start = end+1)
      ret.push_back(s.substr(start, end-start));
    ret.push_back(s.substr(start));
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

  // Get quoted string from stream
  istream &quoted_str(istream &is, string &s)
  {
    char c;
    is >> c;
    if (c == '\"') {
      s = "";
      bool end = false;
      do {
        if (is.get(c)) {
          switch(c) {
          case '\"':
            end = true;
            break;
          case '\\':
            if (is.get(c)) s += c;
            break;
          default:
            s += c;
            break;
          }
        } else {
          end = true;
        }
      } while (!end);
    } else {
      is.putback(c);
      is >> s;
    }
    return is;
  }

  // Does first logical line of file contain magic string?
  bool file_starts_with(const string &filename, const string& magic)
  {
    ifstream s(filename.c_str());
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
    char buf[PATH_MAX];
#if _WIN32
    if (_getcwd(buf, PATH_MAX))
#else
	if (getcwd(buf, PATH_MAX))
#endif
      return string(buf);
    else
      return string("");
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
#if _WIN32
    return _access_s(filename.c_str(), 4) == 0;
#else
	return access(filename.c_str(), R_OK) == 0;
#endif
  }

  // Wrap POSIX realpath
  string get_realpath(const string &path)
  {
    char buf[PATH_MAX];
    if (realpath(path.c_str(), buf)) {
      return string(buf);
    } else {
      return string("");
    }
  }
}
