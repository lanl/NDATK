#include <iostream>
#include <fstream>
#include <string>
#include "Chart.hh"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " filename" << std::endl;
    exit(1);
  }

  ndatk::Chart x(argv[1]);     // parse filename

  // Print file header
  std::cout << x.name() << std::endl;
  for (int i = 0; i < x.number_of_events(); i++)
    std::cout << x.event(i) << std::endl;

  // Print Periodic Table entries for the first 10 elements
  std::cout << "Read " << 
    x.number_of_elements() << 
    " elements" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << i << ": " << 
      x.chemical_symbol(i) <<
      " " << x.atomic_weight_ratio(i) << 
      " " << x.atomic_weight(i) <<
      " " << x.element_name(i) << std::endl;
  }

  // Print Chart of the Nuclides entries for H isotopes
  std::cout << "Read " << 
    x.number_of_nuclides() <<
    " nuclides" << std::endl;
  for (int i = 1001; i < 1007; i++) {
    std::cout << i << 
      ": " << x.atomic_weight_ratio(i) <<
      " " << x.atomic_weight(i) <<
      " " << x.natural_abundance(i) <<
      " " << x.half_life(i) << std::endl;
  }
  std::vector<int> v = x.isotopes(1);
  std::cout << v.size() << " Isotopes of H: ";
  for (unsigned int i = 0; i < v.size(); i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;

  // Print Chart of the Nuclides entries for U isotopes
  for (int i = 92217; i < 92243; i++) {
    std::cout << i << 
      ": " << x.atomic_weight_ratio(i) <<
      " " << x.atomic_weight(i) <<
      " " << x.natural_abundance(i) <<
      " " << x.half_life(i) << std::endl;
  }

  return 0;
}
