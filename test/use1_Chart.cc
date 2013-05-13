#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Chart.hh"

void usage(char *name)
{
    std::cout << "Usage: " << name << 
      " [-v] [-p eps] filename" << std::endl;
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
  ndatk::Chart x(argv[i]);     // parse filename

  std::cout << "Use Case 1:" << std::endl;
  std::cout << "Calculate elemental awr from isotopic abundances and awr."
            << std::endl << std::endl;

  std::cout << "Print data file header." << std::endl;
  std::cout << x.identifier() << std::endl
            << x.process_date() << std::endl
            << x.information() << std::endl;
  std::cout << std::endl;

  if (verbose)
    std::cout << "For all elements:" << std::endl;
  else
    std::cout << "For elements where the relative difference in "
              << " abundance or awr exceeds " << eps << ":" << std::endl;
  for (int i = 1; i < x.number_of_elements(); i++) {
    std::string symbol = x.chemical_symbol(i);
    std::vector<int> za = x.isotopes(symbol);
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
      std::cout << symbol << ": " << 
        "At " << sum_abundance * 100.0 << " percent abundance, " <<
        " AWR = " << avg_awr << " compared to " << 
        awr << std::endl;
    }
  }
  return 0;
}
