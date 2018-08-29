#include <ctime>
#include <ios>                  // for I/O exceptions
#include <limits.h>
#include <cstdlib>
#include <cstring>
#include <pwd.h>
#include "utils.hh"
#include "FileStat.hh"

namespace ndatk {
  
  using namespace std;

  // Construct file metadata by name
  FileStat::FileStat(string name)
  {
    char real_name[PATH_MAX];     // Absolute canonical path name

    if (starts_with(name, "/")) { // Try name as absolute path
      realpath(name.c_str(), real_name);
    } else {                    // Try name relative to CWD
      string tmp_name;

      tmp_name = get_cwd() + "/" + name;     // concatenate cwd and name
      realpath(tmp_name.c_str(), real_name); // canonicalize name
    }

    if (stat(real_name, &file_info) != 0) { // Check existence and get info
      string s("File ");

      throw ios_base::failure(s+real_name+" not found!");
    }
    file_name = real_name;
  }

  // Construct file metadata by name and search path
  FileStat::FileStat(string name, string path)
  {
    char real_name[PATH_MAX];     // Absolute canonical path name

    if (starts_with(name, "/")) { // Try name as absolute path
      realpath(name.c_str(), real_name); // Canonicalize
      if (stat(real_name, &file_info) != 0) {
        string s("File ");

        throw ios_base::failure(s+real_name+" not found!");
      }
    } else {                    // Try name relative to path
      vector<string>::const_iterator i;
      vector<string> p = split(path, ':');
      string tmp_name;

      for (i = p.begin(); i != p.end(); i++) {
        if (*i == "" || *i == ".") // Try name relative to CWD
          tmp_name = get_cwd() + "/" + name;
        else
          tmp_name = *i + "/" + name;
        realpath(tmp_name.c_str(), real_name); // Canonicalize
        if (stat(real_name, &file_info) == 0)
          break;
      }
      if (i == p.end()) {       // tried all paths without success
        string s("File ");

        throw ios_base::failure(s+name+" not found in "+path+"!");
      }
    }
    file_name = real_name;
  }

  // File absolute canonical path name
  string FileStat::absolute_filepath(void) const
  {
    return file_name;
  }

  // File mode bits
  short FileStat::mode_bits(void) const
  {
    return file_info.st_mode;
  }

  // File number of links
  short FileStat::num_link(void) const
  {
    return file_info.st_nlink;
  }

  // File owner id
  short FileStat::uid(void) const
  {
    return file_info.st_uid;
  }

  // File group id
  short FileStat::gid(void) const
  {
    return file_info.st_gid;
  }

  // File size in characters
  off_t FileStat::file_size(void) const
  {
    return file_info.st_size;
  }

  // File time last accessed
  string FileStat::access_time(const char *fmt) const
  {
    char t[20];
    strftime(t, 20, fmt, localtime(&file_info.st_atime));
    string s(t);
    return trim(s);
  }

  // File time last modified
  string FileStat::modification_time(const char *fmt) const
  {
    char t[20];
    strftime(t, 20, fmt, localtime(&file_info.st_mtime));
    string s(t);
    return trim(s);
  }

  // File time originally created
  string FileStat::creation_time(const char *fmt) const
  {
    char t[20];
    strftime(t, 20, fmt, localtime(&file_info.st_ctime));
    string s(t);
    return trim(s);
  }

  // Provenance data of Release event
  string FileStat::location_of_release(void) const
  {
    string loc(get_hostname());
    
    return loc + ":" + this->file_name;
  }

  string FileStat::time_of_release(void) const
  {
    return this->modification_time("%Y-%m-%d");
  }

  string FileStat::agent_of_release(void) const
  {
    struct passwd *pwd;

    pwd = getpwuid(file_info.st_uid);
    if (pwd-> pw_gecos != 0)    // return real name
      return string(pwd->pw_gecos); 
    else                        // return user name
      return string(pwd->pw_name);
  } 
}
