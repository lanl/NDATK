#include <string>
#include "UnitTest.hh"
#include "chart.hh"

using namespace std;
using namespace ndatk;

class ChartTest: public UnitTest {

public:

  void runTest() {
    
    Chart x("chart.dat");

    // Chart header info
    UT_ASSERT(x.get(Chart::string_val::NAME) == string("endf-b/vii"));
    UT_ASSERT(x.get(Chart::string_val::DATE) == string("04/01/2013"));

    // Chart element info
    UT_ASSERT(x.get(Chart::string_val_n::SYMBOL, 0) == string("n"));
    UT_ASSERT(x.get(Chart::string_val_n::NAME, 0) == string("neutron"));

    UT_ASSERT(x.get(Chart::string_val_n::SYMBOL, 92) == string("U"));
    UT_ASSERT(x.get(Chart::string_val_n::NAME, 92) == string("uranium"));

  }
};
