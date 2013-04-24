#include <iostream>
#include <fstream>
#include <string>
#include "library.hh"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " filename" << std::endl;
    exit(1);
  }

  ndatk::Library x(argv[1]);     // parse filename

  // Print file header
  std::cout << x.get(ndatk::Library::string_val::NAME) << std::endl
            << x.get(ndatk::Library::string_val::DATE) << std::endl
            << x.get(ndatk::Library::string_val::INFO) << std::endl;

  //Print first 10 entries

  for (int i = 0; i != 10; i++) {
    std::string id = x.get(ndatk::Library::string_val_n::ID, i);
    std::cout << id << ":"
              << " " << x.get(ndatk::Library::string_val_x::NAME, id)
              << " " << x.get(ndatk::Library::int_val_x::ADDRESS, id)
              << " " << x.get(ndatk::Library::float_val_x::AT_WGT, id)
              << " " << x.get(ndatk::Library::float_val_x::TEMP, id)
              << std::endl;
  }
  return 0;
}
