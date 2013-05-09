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
  std::cout << x.get(ndatk::Chart::string_val::NAME) << std::endl
            << x.get(ndatk::Chart::string_val::DATE) << std::endl
            << x.get(ndatk::Chart::string_val::INFO) << std::endl;

  // Print Periodic Table entries for the first 10 elements
  std::cout << "Read " << 
    x.get(ndatk::Chart::int_val::NUM_ELEMENTS) << 
    " elements" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << i << ": " << 
      x.get(ndatk::Chart::string_val_n::SYMBOL, i) <<
      " " << x.get(ndatk::Chart::float_val_n::AWR, i) << 
      " " << x.get(ndatk::Chart::float_val_n::AT_WGT, i) <<
      " " << x.get(ndatk::Chart::string_val_n::NAME, i) << std::endl;
  }

  // Print Chart of the Nuclides entries for H isotopes
  std::cout << "Read " << 
    x.get(ndatk::Chart::int_val::NUM_NUCLIDES) <<
    " nuclides" << std::endl;
  for (int i = 1001; i < 1007; i++) {
    std::cout << i << 
      ": " << x.get(ndatk::Chart::float_val_n::AWR, i) <<
      " " << x.get(ndatk::Chart::float_val_n::AT_WGT, i) <<
      " " << x.get(ndatk::Chart::float_val_n::ABUNDANCE, i) <<
      " " << x.get(ndatk::Chart::float_val_n::HALF_LIFE, i) << std::endl;
  }
  std::vector<int> v = x.get(ndatk::Chart::int_vec_n::ISOTOPES, 1);
  std::cout << v.size() << " Isotopes of H: ";
  for (unsigned int i = 0; i < v.size(); i++)
    std::cout << v[i] << " ";
  std::cout << std::endl;

  // Print Chart of the Nuclides entries for U isotopes
  for (int i = 92217; i < 92243; i++) {
    std::cout << i << 
      ": " << x.get(ndatk::Chart::float_val_n::AWR, i) <<
      " " << x.get(ndatk::Chart::float_val_n::AT_WGT, i) <<
      " " << x.get(ndatk::Chart::float_val_n::ABUNDANCE, i) <<
      " " << x.get(ndatk::Chart::float_val_n::HALF_LIFE, i) << std::endl;
  }

  for (int i = 1; i < x.get(ndatk::Chart::int_val::NUM_ELEMENTS); i++) {
    std::string symbol = x.get(ndatk::Chart::string_val_n::SYMBOL, i);
    std::vector<int> za = x.get(ndatk::Chart::int_vec_x::ISOTOPES, symbol);
    double abundance;
    double sum_abundance = 0.0;
    double avg_awr = 0.0;
    for (int i = 0; i < za.size(); i++) {
      abundance = x.get(ndatk::Chart::float_val_n::ABUNDANCE, za[i]);
      if (abundance != 0.0) {
        sum_abundance += abundance;
        avg_awr += abundance * x.get(ndatk::Chart::float_val_n::AWR, za[i]);
      }
    }
    std::cout << symbol << ": " << 
      "At " << sum_abundance * 100.0 << " percent abundance, " <<
      " AWR = " << avg_awr << " compared to " <<
      x.get(ndatk::Chart::float_val_x::AWR, symbol) << std::endl;
  }
  return 0;
  
}
