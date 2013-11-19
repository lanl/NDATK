#include <iostream>
#include <iomanip>
#include "FileStat.hh"

int main(int argc, char *argv[])
{
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " file" << std::endl;
    exit(1);
  }

  ndatk::FileStat s(argv[1]);
  std::cout << s.absolute_filepath() << std::endl;
  std::cout << std::oct << s.mode_bits() << std::endl;
  std::cout << s.num_link() << std::endl;
  std::cout << s.file_size() << std::endl; 
  std::cout << s.access_time("%m/%d/%Y") << std::endl;
}
