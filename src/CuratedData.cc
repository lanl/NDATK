#include <stdexcept>
#include "CuratedData.hh"
#include "utils.hh"

namespace ndatk
{
  using namespace std;

  // Send CuratedData to stream
  ostream & operator<<(ostream &out, const CuratedData &x)
  {
    CuratedData::Provenance_map::const_iterator i;

    out << "name: " << x.id << endl;
    out << "%%" << endl;
    for(i = x.m.begin(); i != x.m.end(); i++) {
      out << "event: " << i->first << endl;
      const CuratedData::W7 *y = &(i->second);
      if (y->action != "") 
        out << "action: " << y->action << endl;
      if (y->time != "") 
        out << "time: " << y->time << endl;
      if (y->location != "") 
        out << "location: " << y->location << endl;
      if (y->instrument != "") 
        out << "instrument: " << y->instrument << endl;
      if (y->agent != "") 
        out << "agent: " << y->agent << endl;
      if (y->reason != "") 
        out << "reason: " << y->reason << endl;
      out << "%%" << endl;
    }
    return out;
  }

  // Artifact identifier
  string CuratedData::identifier(void) const
  {
    return id;
  }

  // Provenance events list
  vector<string> CuratedData::events(void) const
  {
    vector<string> ret;
    CuratedData::Provenance_map::const_iterator i;
    for(i = m.begin(); i != m.end(); i++)
      ret.push_back(i->first);
    return ret;
  }

  // Artifact processing
  string CuratedData::action_of(string event) const
  {
    W7 s = map_at(m, event);
    return s.action;
  }

  // Artifact source, process, release date(s)
  string CuratedData::time_of(string event) const
  {
    W7 s = map_at(m, event);
    return s.time;
  }

  // Artifact file location
  string CuratedData::location_of(string event) const
  {
    W7 s = map_at(m, event);
    return s.location;
  }

  // Artifact creation/processing code(s)
  string CuratedData::instrument_of(string event) const
  {
    W7 s = map_at(m, event);
    return s.instrument;
  }

  // Artifact author(s)
  string CuratedData::agent_of(string event) const
  {
    W7 s = map_at(m, event);
    return s.agent;
  }

  // Artifact purpose
  string CuratedData::reason_for(string event) const
  {
    W7 s = map_at(m, event);
    return s.reason;
  }

  // Required base class dtor
  CuratedData::~CuratedData(void) {}
}
