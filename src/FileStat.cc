#include <ctime>
#include <ios>                  // for I/O exceptions
#include "utils.hh"
#include "FileStat.hh"

namespace ndatk {
  
  using namespace std;

  // Construct file metadata by name
  FileStat::FileStat(string name)
  {
    if (stat(name.c_str(), &file_info) != 0) {
      string s("File ");
      throw ios_base::failure(s+name+" not found!");
    }

    if (starts_with(name, "/")) { // Absolute path
      file_name = name;
    } else {                    // Relative path
      file_name = get_cwd() + "/" + name;
    }
  }

  // Construct file metadata by name and search path
  FileStat::FileStat(string name, string path)
  {
    typedef vector<string>::const_iterator iter;
    iter i;
    vector<string> p = split(path, ':');
    for (i = p.begin(); i != p.end(); i++) {
      if (*i == "")
        file_name = string("./") + name;
      else
        file_name = *i + "/" + name;
      if (stat(file_name.c_str(), &file_info) == 0)
        break;
    }
    if (i == p.end()) {
      string s("File ");
      throw ios_base::failure(s+name+" not found in "+path+"!");
    }
  }

  string FileStat::absolute_filepath(void) const
  {
    return file_name;
  }

  off_t FileStat::file_size(void) const
  {
    return file_info.st_size;
  }

  string FileStat::access_time(void) const
  {
    std::string s(std::ctime(&file_info.st_atime));
    return trim(s);
  }

  string FileStat::modification_time(void) const
  {
    std::string s(std::ctime(&file_info.st_mtime));
    return trim(s);
  }
}
