#ifndef CURATEDDATA_HH
#define CURATEDDATA_HH

/**
   \file CuratedData.hh

   Data file type, identifier, and provenance descriptions.

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
     history.  Type is a string found in the first logical line of 
     curated data files that signifies the kind of data they contain.  
     Name is a string found in the second logical line of curated data 
     files that signifies its unique identifier.  History is a sequence 
     of paragraphs found in curated data files that document events in 
     the data's history.

     According to the W-7 model of curated data, data creation,
     transformation, and validation occurs as a series of events that
     may take data as input and produce data as output.  Each of these
     events can be characterized by answers to what, why, where, when,
     who, which, and how questions; the set of characterizations
     constitutes the data's provenance.

     \dot
     digraph w7 {
     label="W-7 model of event description.";
     center=1;
     ratio=fill;
     node[shape=diamond, fontsize=10];
     edge[fontsize=10];
     Who[label="Who?"];
     How[label="How?"];
     Why[label="Why?"];
     Where[label="Where?"];
     Which[label="Which?"];
     When[label="When?"];
     node[shape=box, fontsize=10];
     Agent; Action; Location; Instrument; Time; Reason;
     node[shape=oval];
     Event0[color=blue, fontcolor=blue];
     Event1[label="Event1\n<What?>"]; 

     Agent -> Who[dir=back,label="+"];
     Who -> Event1[dir=back,label="*"];
     Action -> How[label="1"];
     How -> Event1[label="1"]; 
     Event1 -> Why[label="*"];
     Why -> Reason[label="+"];
     Event1 -> Where[label="*"];
     Where -> Location[label="+"];
     Event1 -> When[label="*"];
     When -> Time[label="1"];
     Event1 -> Which[label="*"];
     Which -> Instrument[label="*"];
     node[shape=plaintext];
     Event2[label="..."];
     Event1 -> data1;
     node[fontcolor=blue];
     edge[color=blue];
     Event0 -> data0 -> Event1;
     data1 -> Event2;

     {rank=min; Agent; Action; Location}
     {rank=same; Who; How; Where}
     {rank=same; Event0; data0; Event1; data1; Event2}
     {rank=same; When; Which; Why}
     {rank=max; Time; Instrument; Reason}
     }
     \enddot
     
     An ndatk::CuratedData event is implemented as a free form paragraph
     containing the relevant parts of the W-7 model.
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
    std::string history(void) const;

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
