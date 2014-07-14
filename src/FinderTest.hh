#include "UnitTest.hh"
#include "Finder.hh"

using namespace std;
using namespace ndatk;

class FinderTest: public UnitTest
{
public:
  FinderTest(): x(Finder()) {}
  void runTest();
private:
    Finder x;
};
