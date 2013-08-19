#include <string>
#include "ChartTest.hh"
#include "utils.hh"

void ChartTest::runTest(void)
{
  // Chart header info
  UT_ASSERT(x.type() == "ndatk_chart_1.0");
  UT_ASSERT(x.name() == "early_universe");
  UT_ASSERT(starts_with(x.event(0), "+3hrs"));

  // Chart element info
  UT_ASSERT(x.number_of_elements() == 5);
  UT_ASSERT(x.chemical_symbol(1) == "H");
  UT_ASSERT(x.element_name(1) == "hydrogen");

  UT_ASSERT(x.chemical_symbol(2) == "He");
  UT_ASSERT(x.element_name(2) == "helium");

  // Chart symbol translation 
  for (int z = 0; z < x.number_of_elements(); z++) {
    string symbol = x.chemical_symbol(z);
    UT_ASSERT(x.element_name(symbol) == x.element_name(z));
  }

  // Chart nuclide info
  UT_ASSERT(x.number_of_nuclides() == 9);
  UT_ASSERT(x.atomic_weight_ratio(1001) == 0.999167);
  UT_ASSERT(x.natural_abundance(1001) == 0.999850);
  UT_ASSERT(x.half_life(1001) == 4.336200e+17);

  // Chart nuclide name translation
  UT_ASSERT(x.atomic_weight("1001") == x.atomic_weight(1001));
  UT_ASSERT(x.atomic_weight("H-1") == x.atomic_weight(1001));
  UT_ASSERT(x.atomic_weight("h1") == x.atomic_weight(1001));
  UT_ASSERT(x.atomic_weight("1H") == x.atomic_weight(1001));
  UT_ASSERT(x.atomic_weight("1-H") == x.atomic_weight(1001));

  UT_ASSERT(x.atomic_weight("2003") == x.atomic_weight(2003));
  UT_ASSERT(x.atomic_weight("he-3") == x.atomic_weight(2003));
  UT_ASSERT(x.atomic_weight("He3") == x.atomic_weight(2003));
  UT_ASSERT(x.atomic_weight("3he") == x.atomic_weight(2003));
  UT_ASSERT(x.atomic_weight("3-He") == x.atomic_weight(2003));

            
}
