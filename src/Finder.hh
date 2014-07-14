#ifndef FINDER_HH
#define FINDER_HH

/**
   \file Finder.hh

   Find readable file in path starting with magic string and 
   return absolute path.

   \author Mark G. Gray <gray@lanl.gov>

   Copyright Los Alamos National Laboratory 2014.  All Rights Reserved.
*/

#include <string>
#include <vector>

namespace ndatk
{

  /**
     \class Finder

     Find readable file in path optionally starting with magic string;
     return absolute path to file.

   */
  class Finder
  {
  public:

    /**
       Initialize Finder.
    */
    Finder(void);

    /**
       Initialize Finder with colon delimited search path.

       \param[in] path std::string
    */
    explicit Finder(const std::string &path);

    // Commands
    /**
       Add colon delimited path to the start of path list.

       \param[in] path std::string
    */
    void push_front(const std::string &path); // add path to front of list
    /**
       Add colon delimited path to the start of path list.

       \param[in] path std::string
    */
    void push_back(const std::string &path); // add path to back of list
    /**
       Add colon delimited path from environment variable 
       to the end of path list.

       \param[in] env_var std::string
    */
    void push_front_env(const std::string &env_var);
    /**
       Add colon delimited path from environment variable 
       to the start of path list.

       \param[in] env_var std::string
    */
    void push_back_env(const std::string &env_var);
    /**
       Clear path list.
    */
    void clear(void);

    // Queries
    /**
       Absolute path of readable file in path list.

       \return absoulute path string
     */
    std::string abs_path(const std::string &file) const;
    /**
       Absoulte path of readable file in path list
       that starts with the magic string.

       \return absolute path string
    */
    std::string abs_path(const std::string &file,
                         const std::string &magic) const;
    /**
       Path list as colon delimited string

       \return path string
     */
    std::string to_string(void) const;

  private:
    std::vector<std::string> path_list; // path list
  };
}
#endif
