#include <string>
#include "ChartTest.hh"

void ChartTest::runTest(void)
{
  // Chart header info
  UT_ASSERT(x.id() == "early_universe");
  UT_ASSERT(x.date() == "+3hrs");

  // Chart element info
  UT_ASSERT(x.num_elements() == 5);
  UT_ASSERT(x.symbol(1) == "H");
  UT_ASSERT(x.name(1) == "hydrogen");

  UT_ASSERT(x.symbol(2) == "He");
  UT_ASSERT(x.name(2) == "helium");


  for (int z = 0; z < x.num_elements(); z++) {
    string symbol = x.symbol(z);
    UT_ASSERT(x.name(symbol) == x.name(z));
  }
}
