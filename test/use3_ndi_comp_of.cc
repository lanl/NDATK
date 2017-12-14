#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "ndatk.hh"

using namespace std;

// Some nuclide and elemental names from lanl06ex
const vector<string> names{
  "1001", "C", "12000", "14000", "17",
    "18000", "K", "20000", "22000", "23",
    "24000", "Fe", "56Fe", "28000", "29",
    "31000", "Zr", "42000", "47000", "48",
    "49000", "Xe", "63000", "64000", "72",
    "74000", "Ir", "82000", "U-235", "1095242" 
    };

// Stream map to string
string comp_str(const map<int, double> &c)
{
  stringstream s;
  s << fixed << setprecision(5);
  for (auto &name: c)
    s << name.first << ":" << name.second << " ";
  return s.str();
}

int main(int argc, char *argv[])
{
  // Parse Command line
  bool m = false;
  while (--argc > 0 && (*++argv)[0] == '-')
    while (int c = *++argv[0])
      switch (c) {
      case 'm':
        m = true;
        break;
      default:
        cerr << "use3_ndi_comp_of: illegal option  " << c << endl;
        exit(1);
      }
  if (argc != 2) {
    cerr << "Usage: use3_ndi_comp_of [-m] "
         << " Exsdir_filename library" << endl;
    exit(1);
  }

  // Print explanatory header
  cout << "Use Case 3:" << endl;
  cout << "Create Exsdir from filename on command line;" << endl;
  cout << "create Library from name and Exsdir;" << endl;
  cout << "create Chart from name and Exsdir;" << endl;
  if (m)
    cout << "retrieve mass composition of name in library.";
  else
    cout << "retrieve atom composition of name in library.";
  cout << endl << endl;

  // Parse Exsdir filename
  ndatk::Exsdir x(argv[0]);
  cout << "Created Exsdir " << x.name()
       << " with " << x.number_of_tables() << " tables." << endl;

  // Parse Library filename
  ndatk::Library l(argv[1], x);
  cout << "Created Library " << l.name()
       << " with " << l.number_of_tables() << " tables." << endl;

  // Parse Chart filename
  ndatk::Chart c("chart", x);
  cout << "Created Chart " << c.name()
       << " with " << c.number_of_elements() << " elements" 
       << " and " << c.number_of_nuclides() << " nuclides." << endl;

  // Expand names into their compositions
  cout << endl;
  if (m)
    cout << "Expand names into mass composition according to Library:";
  else
    cout << "Expand names into atom composition according to Library:";
  cout << endl;
  for (auto name: names) {
    cout << setw(7) << name << " -> " ;
    if (m)
      cout << "m " << comp_str(ndatk::ndi_mass_comp_of(name, l, c));
    else
      cout << "a " << comp_str(ndatk::ndi_atom_comp_of(name, l, c));
    cout << endl;
  }
}
