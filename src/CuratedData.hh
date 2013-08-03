#ifndef CURATEDDATA_HH
#define CURATEDDATA_HH

#include <iostream>
#include <string>
#include <vector>
#include <map>

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
    friend std::ostream& operator<<(std::ostream &out, const CuratedData &x);
  public:

    // Queries
    std::string identifier(void) const;          // identifier
    std::vector<std::string> events(void) const; // Provenance events
    std::string action_of(std::string event) const;
    std::string time_of(std::string event) const;
    std::string location_of(std::string event) const;
    std::string instrument_of(std::string event) const;
    std::string agent_of(std::string event) const;
    std::string reason_for(std::string event) const;

    // Required virtual dtor
    virtual ~CuratedData(void) = 0;

  protected:

    struct W7
    {
      std::string action;       // How did event occur?
      std::string time;         // When did event occur?
      std::string location;     // Where did event occur?
      std::string instrument;   // Which tools were used in event?
      std::string agent;        // Who caused event?
      std::string reason;       // Why was event?
    };
    typedef std::map<std::string, W7> Provenance_map;
    
    std::string id;             // (unique) name 
    Provenance_map m;           // map of events to their descriptors
  };
}
#endif
