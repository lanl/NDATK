#ifndef CURATEDDATA_HH
#define CURATEDDATA_HH

#include <string>

// Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.

// File Description:
// Curated Data - Provide provenance for subclasses.
// See: Jon Bentley, "More Programming Pearls", Addison-Wesley 1988, pg. 40
//      Sudha Ram and Jun Liu, "A New Perspective on Semantics of
//                              Data Provenance", Univ. of Az.

// Authors: Mark G. Gray gray@lanl.gov

namespace ndatk
{

  // Data release provenance
  class CuratedData
  {
  public:

    // Queries
    std::string identifier(void) const; // identifier
    std::string how(void) const;        // did it come to be?
    std::string what(void) const;       // is it?
    std::string when(void) const;       // did it come to be?
    std::string where(void) const;      // is its file?
    std::string which(void) const;      // tool(s) did it come from?
    std::string who(void) const;        // made it?
    std::string why(void) const;        // was it made?

    // Required dtor
    virtual ~CuratedData(void) = 0;

  protected:

    std::string id;             // (unique) name 
    // W7 Model
    std::string action;         // workflow description
    std::string description;    // information
    std::string date;           // source, process, release date(s)
    std::string location;       // data file location
    std::string instrument;     // code/process list
    std::string agent;          // author(s)
    std::string reason;         // purpose

  };
}
#endif
