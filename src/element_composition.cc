#include "element_composition.hh"

#include <functional>

namespace ndatk
{
  using namespace std;

  // natural atom composition of name from Chart in Library
  map<int, double> ndi_atom_comp_of(string name, const Library &l, 
                                    const Chart &c)
  {
    function<map<int, double>(string)> f = bind(&Chart::atom_comp_of, c,
                                               placeholders::_1);
    return l.comp_of(name, f);
  }

  // natural mass composition of name from Chart in Library
  map<int, double> ndi_mass_comp_of(string name, const Library &l, 
                                    const Chart &c)
  {
    function<map<int, double>(string)> f = bind(&Chart::mass_comp_of, c,
                                               placeholders::_1);
    return l.comp_of(name, f);
  }
}
