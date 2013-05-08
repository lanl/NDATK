#include <string>
#include "ChartTest.hh"

void ChartTest::runTest(void)
{
  // Chart header info
  UT_ASSERT(x.get(Chart::string_val::NAME) == string("early_universe"));
  UT_ASSERT(x.get(Chart::string_val::DATE) == string("+3hrs"));

  // Chart element info
  UT_ASSERT(x.get(Chart::string_val_n::SYMBOL, 0) == string("n"));
  UT_ASSERT(x.get(Chart::string_val_n::NAME, 0) == string("neutron"));

  UT_ASSERT(x.get(Chart::string_val_n::SYMBOL, 2) == string("He"));
  UT_ASSERT(x.get(Chart::string_val_n::NAME, 2) == string("helium"));
}
