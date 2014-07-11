#ifndef FINDER_HH
#define FINDER_HH

#include <string>
#include <vector>

// Copyright Los Alamos National Laboratory 2014.  All Rights Reserved.

// File Description:
// Find files - Locate readable files on path starting with magic string.

// Authors: Mark G. Gray gray@lanl.gov

namespace ndatk
{

  class Finder
  {
  public:

    explicit Finder(const std::string &path); // Search path
    Finder(void);

    void push_front(const std::string &path); // add path to front of list
    void push_back(const std::string &path); // add path to back of list

    // Queries
    std::string abs_path(const std::string &file) const;
    std::string abs_path(const std::string &file,
                         const std::string &magic) const;

  private:
    std::vector<std::string> path_list;
  };
}
#endif
