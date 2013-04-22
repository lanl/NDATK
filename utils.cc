#include "utils.hh"

namespace ndatk {
  using namespace std;

  /* Compare two strings ignoring case.
   *
   * See B. Stroustrup, "The C++ Programming Language, 3ed, p. 591
   */
  int cmp_nocase(const string &s1, const string &s2)
  {
    typedef string::const_iterator iter;
    iter p1;
    iter p2;

    for (p1 = s1.begin(), p2 = s2.begin(); 
         p1 != s1.end() && p2 != s2.begin(); p1++, p2++)
      if (toupper(*p1) != toupper(*p2))
        return (toupper(*p1) < toupper(*p2)) ? -1: 1;
    return s2.size() - s1.size();
  }

  /* Compare the start of the first string with the second, ignoring case.
   */
  bool starts_with_nocase(const string &s1, const string &s2)
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

  /* Split string into vector of words.
   *
   * See "Accelerated C++" p. 103
   */
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

  /* Get Logical Line
   *
   * Get line from stream,
   * truncate after comment character ('#'),
   * trim leading, following whitespace,
   * append next logical line from stream if 
   * line ends in continuation characters ('\' or '+').
   * Returns stream as I/O status.
   */
  std::istream &get_logical_line(std::istream &s, std::string &line)
  {
    while (getline(s, line)) {
        string::iterator j = line.end();
        line.erase(find(line.begin(), j, '#'), j); // truncate at comment
        trim(line);                     // trim surrounding spaces
        j = line.end() - 1;             // pointer to last char
        if (*j == '\\' || *j == '+') {  // concatenate next line
          *j = ' ';
          std::string next_line;
          if (!get_logical_line(s, next_line)) return s;
          line.append(next_line);
        }
        if (line.size() != 0) return s;
      }
    return s;
  }
}
