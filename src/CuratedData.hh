#ifndef CURATEDDATA_HH
#define CURATEDDATA_HH

#include <iostream>
#include <string>
#include <vector>

// Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.

// File Description:
// Curated Data - Provide provenance for subclasses.
// See: Jon Bentley, "More Programming Pearls", Addison-Wesley 1988, pg. 40
//      Sudha Ram and Jun Liu, "A New Perspective on Semantics of
//                              Data Provenance", Univ. of Az.

// Authors: Mark G. Gray <gray@lanl.gov>

namespace ndatk
{
  // Data provenance
  class CuratedData
  {
  protected:
    typedef std::vector<std::string> ProvenanceVector;
  public:
    typedef ProvenanceVector::size_type size_type;

    // Queries
    std::string name(void) const;          // identifier
    virtual std::string type(void) const = 0; // Data file type
    size_type number_of_events(void) const;
    std::string event(size_type) const; // event description

    // Required virtual dtor
    virtual ~CuratedData(void) = 0;

  protected:

    // I/O for CuratedData: to be used by derived classes only
    std::ostream& put_header(std::ostream& out) const;
    std::istream& get_header(std::istream& in);
    static std::string begin_provenance;
    static std::string end_provenance;
    std::ostream& put_ProvenanceVector(std::ostream &out) const;
    std::istream& append_ProvenanceVector(std::istream &in);

    std::string name_;             // unique name
    ProvenanceVector provenance; // provenance paragraphs 

  };
}
#endif
