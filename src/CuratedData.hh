#ifndef CURATEDDATA_HH
#define CURATEDDATA_HH

/**
   \file CuratedData.hh

   Data file type and provenance descriptions.

   \author Mark G. Gray <gray@lanl.gov>
   \see Jon Bentley, "More Programming Pearls", Addison-Wesley 1988, pg. 40
        Sudha Ram and Jun Liu, "A New Perspective on Semantics of
                             Data Provenance", Univ. of Az.

   Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.
*/

#include <iostream>
#include <string>
#include <vector>

namespace ndatk
{
  /**
     \class CuratedData

     Curated Data.
  
     The ndatk::CuratedData abstract base class provides derived
     classes which represent curated data files with type, name, and
     history.   Type is a string that adorns curated data files
     which specifies the type of data they contain.  Name is a string
     that adorns curated data files which specifies an identifier.
     History is a list of free form texts which answer what, why,
     where, when, who, which, and how for each major event affecting
     the data's evolution.
  */
  class CuratedData
  {
  protected:
    /// Provenance story.
    typedef std::vector<std::string> ProvenanceVector;

  public:
    /// Provenance story size 
    typedef ProvenanceVector::size_type size_type;

    // Queries

    /**
       Data file type.

       \return data file type string
    */
    virtual std::string type(void) const = 0;
    /**
       Data file identifier.
       
       \return data file identifier string
    */
    std::string name(void) const;
    /**
       Number of events in provenance.

       \return size_type number of events
    */
    size_type number_of_events(void) const;
    /**
       The i'th event.

       \param[in] i size_type
       \return std::string description of event
    */
    std::string event(size_type i) const;
    /** The event history.

        \return std::string description of events
    */
    std::string events(void) const;

    /// Required virtual dtor
    virtual ~CuratedData(void) = 0;

  protected:

    /**
       Output header to stream.

       \param[in,out] out std::ostream
       \return std::ostream
    */
    std::ostream& put_header(std::ostream& out) const;
    /**
       Input header from stream.
       
       \param[in,out] in std::istream
       \return std::istream
    */
    std::istream& get_header(std::istream& in);
    /**
       Output provenance to stream.

       \param[in,out] out std::ostream
       \return std::ostream
    */
    std::ostream& put_ProvenanceVector(std::ostream &out) const;
    /**
       Input provenance from stream.

       \param[in,out] in std::istream
       \return std::istream
    */
    std::istream& append_ProvenanceVector(std::istream &in);

    static std::string begin_provenance; ///< Provenance section title 
    static std::string end_provenance;   ///< Provenance section terminator 
    std::string name_;                   ///< Unique identifier
    ProvenanceVector provenance; ///< Event description paragraphs 

  };
}
#endif
