#include "LibraryTest.hh"

void LibraryTest::runTest(void)
{
  // Lookup table_identifiers by isomer names 
  UT_ASSERT(y.table_identifier("1001") == "1001.80c");
  UT_ASSERT(y.atomic_weight_ratio() == 0.999167);
  UT_ASSERT(y.file_name() == "endf71x/H/1001.710nc");
  UT_ASSERT(y.temperature() == 2.530100e-8);
    
  UT_ASSERT(y.table_identifier("H1") == "1001.80c");
  UT_ASSERT(y.table_identifier("H-2") == "1002.80c");
  UT_ASSERT(y.table_identifier("3h") == "1003.80c");

  UT_ASSERT(y.table_identifier("1001.81c") == "1001.81c");
  UT_ASSERT(y.file_name() == "endf71x/H/1001.711nc");
  UT_ASSERT(y.temperature() == 5.170400e-8);
}
