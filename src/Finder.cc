#include "utils.hh"
#include "Finder.hh"

namespace ndatk {
  using namespace std;

  // Construct a Finder with empty search path
  Finder::Finder(void): path_list() 
  {
  }

  // Construct a Finder with colon delimited path string.
  Finder::Finder(const string &path): path_list()
  {
    path_list = parse_path(path);
  }
   
  // Set a Finder's search path to colon delimited path string.
  void Finder::set_path(const std::string &path)
  {
    path_list = parse_path(path);
  }
          
  // Return absolute path of first readable file with name in search path.
  string Finder::abs_path(const std::string &name) const
  {
    if ((starts_with(name, "/") || // absolute path
         starts_with(name, "./") || // relative to CWD
         starts_with(name, "../")) && // relative to CWD
        is_readable(name)) {
      return get_realpath(name); // absolute path of name
    } else {
      for (vector<string>::const_iterator p = path_list.begin();
           p != path_list.end(); p++) {
        string f;
        if (*p == "")
          f = name;
        else if (p->rbegin()[0] == '/') // No back() in C++03 string
          f = *p + name;
        else
          f = *p + "/" + name;
        if (is_readable(f))
          return get_realpath(f);
      }
    }
    return string("");          // readable name not found
  }

  // Return absolute path of first readable file with name in search path
  // starting with magic string.
  string Finder::abs_path(const std::string &name,
                         const std::string &magic) const
  {
    if ((starts_with(name, "/") || // absolute path
         starts_with(name, "./") || // relative to CWD
         starts_with(name, "../")) && // relative to CWD
        is_readable(name) && 
        file_starts_with(name, magic)) {
      return get_realpath(name);
    } else {
      for (vector<string>::const_iterator p = path_list.begin();
           p != path_list.end(); p++) {
        string f;
        if (*p == "")
          f = name;
        else if (p->rbegin()[0] == '/') // No back() in C++03 string
          f = *p + name;
        else
          f = *p + "/" + name;
        if (is_readable(f) && file_starts_with(f, magic))
          return get_realpath(f);
      }
    }
    return string("");          // readable name not found
  }

  // Convert search path to colon delimited string.
  string Finder::get_path(void) const
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

  // Parse colon delimited path string and return vector of elements.
  vector<string> Finder::parse_path(const string &path) const
  {
    vector<string> new_path;
    vector<string> in_path(split(path, ':')); // tokenize path

    if (path != "") {
      // Copy in_path to new_path, expanding CURRENT_PATH and ENVIRONMENT
      for (vector<string>::const_iterator p = in_path.begin();
           p != in_path.end(); p++) {
        if (*p == "!!") { // insert CURRENT_PATH here
          new_path.insert(new_path.end(), path_list.begin(), path_list.end());
        } else if (starts_with(*p,"$")) { // insert ENVIRONMENT variable here
          string env(get_env(p->substr(1)));
          if (env != "") {
            vector<string> env_path(parse_path(env));
            new_path.insert(new_path.end(), env_path.begin(), env_path.end());
          }
        } else {                  // insert value here
          new_path.push_back(*p);
        }
      }
    }
    return new_path;
  }
}
