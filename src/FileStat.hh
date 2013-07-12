#ifndef FILESTAT_HH
#define FILESTAT_HH

#include <string>
#include <sys/stat.h>
#include <sys/types.h>

// Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.

// File Description:
// File Stats - Metadata for files.
// See: D. Ryan Stephens, Christopher Diggins, Johathan Turkanis, and
//      Jeff Cogswell, "C++ Cookbook", O'Reilly Media, (2006), pg 368

// Authors: Mark G. Gray gray@lanl.gov

namespace ndatk
{

  class FileStat
  {
  public:

    explicit FileStat(std::string name); // named file
    FileStat(std::string name, std::string path); // named file in path

    // Queries
    std::string absolute_filepath(void) const;
    off_t file_size(void) const;
    std::string access_time(void) const;
    std::string modification_time(void) const;
 
  private:
    struct stat file_info;       // Directory info for file
    std::string file_name;       // Absolute file name
  };
}
#endif
