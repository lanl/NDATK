#include "utils.hh"
#include "Finder.hh"

namespace ndatk {
  using namespace std;

  // Construct finder with empty path list
  Finder::Finder(void): path_list() 
  {
  }

  // Construct finder with colon delimited path string.
  Finder::Finder(const string &path): path_list(split(path, ':'))
  {
  }
   
  // Add colon delimited path to start of path list
  void Finder::push_front(const std::string &path)
  {
    vector<string> front(split(path, ':'));

    // Add path_list to the end of front
    for (vector<string>::const_iterator p = path_list.begin();
         p != path_list.end(); p++)
      front.push_back(*p);
    // and copy front to path_list
    path_list = front;
           
  }

  // Add colon delimited path to end of path list
  void Finder::push_back(const std::string &path)
  { 
    vector<string> back(split(path, ':'));

    // Add back to the end of path_list
    for (vector<string>::const_iterator p = back.begin();
         p != back.end(); p++)
      path_list.push_back(*p);
  }

  // Add colon delimited path from environment to start of path list.
  void Finder::push_front_env(const std::string &env_var)
  {
    string s = get_env(env_var);
    if (s != "")
      push_front(s);
  }

  // Add colon delimited path from environment to end of path list.
  void Finder::push_back_env(const std::string &env_var)
  {
    string s = get_env(env_var);
    if (s != "")
      push_back(s);
  }

  // Clear path list
  void Finder::clear(void)
  {
    path_list.clear();
  }

  // Return absolute path of first readable file with name in path list. 
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
        else if (p->rbegin()[0] == '/') // No back mf in C++03
          f = *p + name;
        else
          f = *p + "/" + name;
        if (is_readable(f))
          return get_realpath(f);
      }
    }
    return string("");
  }

  // Return absolute path of first readable file with name in path list 
  // starting with magic.
  string Finder::abs_path(const std::string &name,
                         const std::string &magic) const
  {
    if (starts_with(name, "/") && 
        is_readable(name) && 
        file_starts_with(name, magic)) {
      return get_realpath(name);
    } else {
      for (vector<string>::const_iterator p = path_list.begin();
           p != path_list.end(); p++) {
        string f;
        if (*p == "")
          f = name;
        else if (p->rbegin()[0] == '/') // No back mf in C++03
          f = *p + name;
        else
          f = *p + "/" + name;
        if (is_readable(f) && file_starts_with(f, magic))
          return get_realpath(f);
      }
    }
    return string("");
}

  // Convert path list to colon delimited string.
  string Finder::to_string(void) const
  {
    string s;
    for (vector<string>::const_iterator p = path_list.begin();
         p != path_list.end(); p++) {
      if (s != "")
        s += ":";
      s += *p;
    }
    return s;
  }
}
