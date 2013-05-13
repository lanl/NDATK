#include "LibraryTest.hh"

void LibraryTest::runTest(void)
{
  // Chart header info
  UT_ASSERT(x.id() == "early_universe");
  UT_ASSERT(x.date() == "+3hrs");

  UT_ASSERT(x.table_id("H1") == "1001.62c");
  UT_ASSERT(x.table_id("H-2") == "1002.66c");
  UT_ASSERT(x.table_id("3h") == "1003.69c");
  UT_ASSERT(x.table_id("He3") == "2003.66c");
  UT_ASSERT(x.table_id("4-He") == "2004.62c");
  UT_ASSERT(x.table_id("Li6") == "3006.66c");
  UT_ASSERT(x.table_id("Li-7") == "3007.66c");
  UT_ASSERT(x.table_id("4007") == "4007.35c");
}
