#include <string>
#include "ChartTest.hh"

void ChartTest::runTest(void)
{
  // Chart header info
  UT_ASSERT(x.identifier() == "early_universe");
  UT_ASSERT(x.process_date() == "+3hrs");

  // Chart element info
  UT_ASSERT(x.number_of_elements() == 5);
  UT_ASSERT(x.chemical_symbol(1) == "H");
  UT_ASSERT(x.element_name(1) == "hydrogen");

  UT_ASSERT(x.chemical_symbol(2) == "He");
  UT_ASSERT(x.element_name(2) == "helium");


  for (int z = 0; z < x.number_of_elements(); z++) {
    string symbol = x.chemical_symbol(z);
    UT_ASSERT(x.element_name(symbol) == x.element_name(z));
  }
}
