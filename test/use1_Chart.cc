#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "ndatk.hh"

using namespace std;

void usage(char *name)
{
    cout << "Usage: " << name << 
      " [-v] [-p eps] filename" << endl;
    exit(1);
}

int main(int argc, char *argv[])
{
  bool verbose = false;
  double eps = 0.001;
  int i;

  if (argc < 2) 
    usage(argv[0]);
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-p") == 0) { // expect precision double next
      if (!(++i < argc))
        usage(argv[0]);
      eps = atof(argv[i]);
    } else if (strcmp(argv[i], "-v") == 0) { // verbose output
      verbose = true;
    } else {                    // assume filename
      break;
    }
  }
  cout << "Use Case 1:" << endl;
  cout << "Create Exsdir from filename on command line;" << endl;
  cout << "create Chart from name and Exsdir;" << endl;
  cout << "calculate elemental awr from isotopic abundances and awr."
            << endl << endl;

  ndatk::Exsdir e(argv[i]);
  cout << "Created Exsdir " << e.identifier() 
       << " with " << e.number_of_tables() << " tables." << endl;

  ndatk::Chart x("chart", e);     // parse filename
  cout << "Created Chart " << x.identifier()
       << " with " << x.number_of_elements() << " elements" 
       << " and " << x.number_of_nuclides() << " nuclides." << endl;

  cout << "Print data file header." << endl;
  cout << x.identifier() << endl
            << x.process_date() << endl
            << x.information() << endl;
  cout << endl;

  if (verbose)
    cout << "For all elements:" << endl;
  else
    cout << "For elements where the relative difference in "
              << " abundance or awr exceeds " << eps << ":" << endl;
  for (int i = 1; i < x.number_of_elements(); i++) {
    string symbol = x.chemical_symbol(i);
    vector<int> za = x.isotopes(symbol);
    double abundance;
    double sum_abundance = 0.0;
    double avg_awr = 0.0;
    double awr = x.atomic_weight_ratio(symbol);
    for (int i = 0; i < za.size(); i++) {
      abundance = x.natural_abundance(za[i]);
      if (abundance != 0.0) {
        sum_abundance += abundance;
        avg_awr += abundance * x.atomic_weight_ratio(za[i]);
      }
    }
    if (verbose ||
        fabs(sum_abundance - 1.0) > eps || 
        fabs(awr - avg_awr)/awr > eps) { 
      cout << symbol << ": " << 
        "At " << sum_abundance * 100.0 << " percent abundance, " <<
        " AWR = " << avg_awr << " compared to " << 
        awr << endl;
    }
  }
  return 0;
}
