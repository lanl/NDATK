#include "CuratedData.hh"
#include "utils.hh"

// Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.

// File Description:
// Curated Data - Provide provenance for subclasses.
// See: Jon Bentley, "More Programming Pearls", Addison-Wesley 1988, pg. 40
//      Sudha Ram and Jun Liu, "A New Perspective on Semantics of
//                              Data Provenance", Univ. of Az.

// Authors: Mark G. Gray <gray@lanl.gov>

namespace ndatk
{
  using namespace std;

  // Put header to ostream out

  // All CuratedData files begin with:
  // type: type_value
  // name: name_value
  ostream& CuratedData::put_header(ostream& out) const
  {
    out << "type: " << type() << endl; // First logical line
    out << "name: " << name_ << endl;   // second logical line
    return out;
  }

  // Get header from ostream out
  istream& CuratedData::get_header(istream& in)
  {
    string line;

    // Check first logical line for type: value;
    // match value against type parameter
    if (get_logical_line(in, line)) {
      if (!starts_with_nocase(line, "type:") || type() != value(line)) {
        string e("Bad file format: expected 'type: ");
        e += type() + "' found '" + line + "' in first logical line!";
        throw istream::failure(e.c_str());
      }
    } else {
      string e("Cannot read first logical line!");
      throw istream::failure(e.c_str());
    }
    
    // Check second logical line for name: value;
    // store value in name
    if (get_logical_line(in, line)) {
      if (!starts_with_nocase(line, "name:")) {
        string e("Bad file format: expected 'name: value' found '");
        e += line + "' in second logical line!";
        throw istream::failure(e.c_str());
      } else {
        name_ = value(line);
      }
    } else {
      string e("Cannot read second logical line!");
      throw istream::failure(e.c_str());
    }
    return in;
  }

  // Delimiters for input file provenance section
  string CuratedData::begin_provenance = "provenance:";
  string CuratedData::end_provenance = "%%";

  // Put ProvenanceVector to ostream out

  // CuratedData files may contain sections of:
  // provenance:
  // lines of text
  // %%
  ostream& CuratedData::put_ProvenanceVector(ostream& out) const
  {
    ProvenanceVector::const_iterator i;

    for(i = provenance.begin(); i != provenance.end(); i++) {
      out << begin_provenance << endl 
          << *i << endl 
          << end_provenance << endl;
    }
    return out;
  }

  // Append to ProvenanceVector from istream in
  istream& CuratedData::append_ProvenanceVector(istream &in)
  {
    string line;
    string paragraph;
    
    while (get_logical_line(in, line)) {
      if (starts_with_nocase(line, begin_provenance)) {
        continue;
      } else if (starts_with_nocase(line, end_provenance)) {
        provenance.push_back(paragraph);
        break;
      } else {
        paragraph += line + "\n"; // Accumulate lines separated by newlines
      }
    }
  return in;
  }

  // Artifact identifier
  string CuratedData::name(void) const
  {
    return name_;
  }

  CuratedData::size_type CuratedData::number_of_events(void) const
  {
    return provenance.size();
  }

  // Provenance events list
  string CuratedData::event(CuratedData::size_type i) const
  {
    return provenance.at(i);
  }

  // Provenance history
  string CuratedData::history(void) const
  {
    string e;
    for (ProvenanceVector::const_iterator i = provenance.begin();
         i != provenance.end(); i++)
      e += *i + "\n";
    return e;
  }

}
