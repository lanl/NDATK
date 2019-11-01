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

     Find the first readable file in the user specified search path 
     optionally starting with a magic string; return absolute path to file.

     Names starting with "/" are resolved as absolute paths; names starting
     with  "./", or "../" are resolved against the current working directory.
     All other names are appended to the each element of the user 
     specified search path list and tried until a readable file starting 
     with an optional magic string is found.  If no match is found, 
     the absolute path returned is "".

     The search path is specified by the following IOS/IEC 14977 EBNF 
     grammar:
     \code
     SEARCH_PATH = '"', ELEMENTS, '"';
     ELEMENTS = empty
              | ELEMENT, {':' ELEMENT};
     ELEMENT = ENVIRONMENT
             | CURRENT_PATH                   (* previous path value *)
             | posix_path;
     ENVIRONMENT = '$', {[A-Za-z0-9._-]}-;    (* environment variable value *)
     CURRENT_PATH = '!!';
     \endcode

     Standard POSIX conformant path names are added to the search path
     literally.  Environment variable values, signified by a leading '$' 
     are parsed as a search path and added to the search path
     wherever they appear as an element.  The special string "!!" is 
     replaced with the current path wherever it appears.

     \note The empty string "" sets an empty search path; when the path is 
     empty names not starting with "/", "./", or "../" will never be found.
     The current working directory can be specified in the search path by 
     either "." or "".  The search path format is based on the standard UNIX
     PATH environment variable; the use of "!!" to signify the former search
     path in a new path specification is modeled after its use in modern UNIX
     shells to signify the previous command.
   */
  class Finder
  {

  public:

    /**
       Initialize Finder with empty path.
    */
    Finder(void) = default;

    /**
       Initialize Finder with colon delimited search path.

       \param[in] path std::string
    */
    explicit Finder(const std::string &path);

    // Commands
    /**
       Set colon delimited path string as search path.

       Elements starting with "$" are replaced by the named environment
       variable value, if it exists.  The element "!!" is replaced by the
       current search path.

       \param[in] path std::string
    */
    void set_path(const std::string &path); // set path to parsed string

    // Queries
    /**
       Absolute path of readable file in path list.

       \param[in] file std::string
       \return absoulute path string
     */
    std::string abs_path(const std::string &file) const;

    /**
       Absoulte path of readable file in path list
       that starts with the magic string.

       \param[in] file std::string
       \param[in] magic std::string
       \return absolute path string
    */
    std::string abs_path(const std::string &file,
                         const std::string &magic) const;

    /**
       Path list as colon delimited string

       \return path string
     */
    std::string get_path(void) const;

  private:

    /**
       Parse path string according to current path and environment

       \param[in] path colon delimited path
       \return vector of expanded path 
    */
    std::vector<std::string> parse_path(const std::string &path) const;

    std::vector<std::string> path_list; // path list

  };
}
#endif
