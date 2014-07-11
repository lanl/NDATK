#include "utils.hh"
#include "Finder.hh"

namespace ndatk {
  using namespace std;

  // Construct finder by path string
  
  Finder::Finder(const string &path): path_list(split(path))
  {
  }
   
  Finder::Finder(void): path_list() 
  {
  }

  void Finder::push_front(const std::string &path)
  {
    vector<string> front(split(path));

    // Add path_list to the end of front
    for (vector<string>::const_iterator p = path_list.begin();
         p != path_list.end(); p++)
      front.push_back(*p);
    // and copy front to path_list
    path_list = front;
           
  }

  void Finder::push_back(const std::string &path)
  { 
    vector<string> back(split(path));

    // Add back to the end of path_list
    for (vector<string>::const_iterator p = back.begin();
         p != back.end(); p++)
      path_list.push_back(*p);
  }

  string Finder::abs_path(const std::string &name) const
  {
    if (starts_with(name, "/") && is_readable(name)) {
      return get_realpath(name);
    } else {
      for (vector<string>::const_iterator p = path_list.begin();
           p != path_list.end(); p++) {
        string f;
        if (*p == "")
          f = name;
        else if (*((*p).rbegin()) == '/') // No back mf in C++03
          f = *p + name;
        else
          f = *p + "/" + name;
        if (is_readable(f))
          return get_realpath(f);
      }
    }
    return string("");
  }

  string Finder::abs_path(const std::string &name,
                         const std::string &magic) const
  {
    string f;
    if ((f = abs_path(name)) != "" && file_starts_with(f, magic))
      return f;
    else
      return string("");
  }
}
