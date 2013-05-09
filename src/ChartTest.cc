#include <string>
#include "ChartTest.hh"

void ChartTest::runTest(void)
{
  // Chart header info
  UT_ASSERT(x.get(Chart::string_val::NAME) == string("early_universe"));
  UT_ASSERT(x.get(Chart::string_val::DATE) == string("+3hrs"));

  // Chart element info
  UT_ASSERT(x.get(Chart::int_val::NUM_ELEMENTS) == 5);
  UT_ASSERT(x.get(Chart::string_val_n::SYMBOL, 1) == string("H"));
  UT_ASSERT(x.get(Chart::string_val_n::NAME, 1) == string("hydrogen"));

  UT_ASSERT(x.get(Chart::string_val_n::SYMBOL, 2) == string("He"));
  UT_ASSERT(x.get(Chart::string_val_n::NAME, 2) == string("helium"));


  for (int z = 0; z < x.get(Chart::int_val::NUM_ELEMENTS); z++) {
    string symbol = x.get(Chart::string_val_n::SYMBOL, z);
    UT_ASSERT(x.get(Chart::string_val_x::NAME, symbol) ==
              x.get(Chart::string_val_n::NAME, z));
  }
}
