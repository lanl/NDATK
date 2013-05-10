#include <string>
#include <sstream>
#include "UnitTest.hh"
#include "Library.hh"

using namespace std;
using namespace ndatk;

static istringstream library_dat(
  "NAME:\n"
  "early_universe\n"
  "DATE:\n"
  "+3hrs\n"
  "INFO:\n"
  "Truncated lanl2006\n"
  "IDS:\n"
  "1001.62c\n"
  "1002.66c\n"
  "1003.69c\n"
  "2003.66c\n"
  "2004.62c\n"
  "3006.66c\n"
  "3007.66c\n"
  "4007.35c\n");

class LibraryTest: public UnitTest
{
public:
  LibraryTest(): x(library_dat) {}; 
  void runTest();

private:
  Library x;
};

