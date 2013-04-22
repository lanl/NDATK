#include <iostream>
#include <fstream>
#include <string>
#include "chart.hh"


int main(int argc, char *argv[])
{

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " filename" << std::endl;
    exit(1);
  }
  std::ifstream f(argv[1]);     // open filename

  ndatk::NuclidesChart x(f);     // parse f

  std::cout << "Read " << 
    x.get_int_val(ndatk::NuclidesChart::NUM_ELEMENTS) << 
    " elements" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << i << ": " << 
      x.get_string_val_n(ndatk::NuclidesChart::SYMBOL, i) <<
      " " << x.get_float_val_n(ndatk::NuclidesChart::AWR, i) << 
      " " << x.get_float_val_n(ndatk::NuclidesChart::AT_WGT, i) <<
      " " << x.get_string_val_n(ndatk::NuclidesChart::NAME, i) << std::endl;
  }

  std::cout << "Read " << 
    x.get_int_val(ndatk::NuclidesChart::NUM_NUCLIDES) <<
    " nuclides" << std::endl;
  for (int i = 1001; i < 1007; i++) {
    std::cout << i << 
      ": " << x.get_float_val_n(ndatk::NuclidesChart::AWR, i) <<
      " " << x.get_float_val_n(ndatk::NuclidesChart::AT_WGT, i) <<
      " " << x.get_float_val_n(ndatk::NuclidesChart::ABUNDANCE, i) <<
      " " << x.get_float_val_n(ndatk::NuclidesChart::HALF_LIFE, i) << std::endl;
  }
  return 0;
}
