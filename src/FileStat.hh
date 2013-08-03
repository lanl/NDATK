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

    explicit FileStat(std::string name); // File name
    FileStat(std::string name, std::string path); // File name and path

    // Queries
    std::string absolute_filepath(void) const; // File absolute canonical path
    short mode_bits(void) const;               // File permissions
    short num_link(void) const;                // File links
    short uid(void) const;                     // File user id
    short gid(void) const;                     // File group id
    off_t file_size(void) const;               // File size
    // See ctime documentation for format strings
    std::string access_time(const char *fmt) const; // File access time
    std::string modification_time(const char *fmt) const; // File mod time
    std::string creation_time(const char *fmt) const;     // File create time

    // Provenance data of Release event
    std::string location_of_release() const;
    std::string time_of_release() const;
    std::string agent_of_release() const;

  private:
    struct stat file_info;       // Directory info for file
    std::string file_name;       // Absolute file name
  };
}
#endif
