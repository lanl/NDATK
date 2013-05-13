#include "LibraryTest.hh"

void LibraryTest::runTest(void)
{
  // Library header info
  UT_ASSERT(x.identifier() == "early_universe");
  UT_ASSERT(x.process_date() == "+3hrs");

  // Lookup table_identifiers by isomer names 
  UT_ASSERT(x.table_identifier("H1") == "1001.62c");
  UT_ASSERT(x.table_identifier("H-2") == "1002.66c");
  UT_ASSERT(x.table_identifier("3h") == "1003.69c");
  UT_ASSERT(x.table_identifier("He3") == "2003.66c");
  UT_ASSERT(x.table_identifier("4-He") == "2004.62c");
  UT_ASSERT(x.table_identifier("Li6") == "3006.66c");
  UT_ASSERT(x.table_identifier("Li-7") == "3007.66c");
  UT_ASSERT(x.table_identifier("4007") == "4007.35c");
}
