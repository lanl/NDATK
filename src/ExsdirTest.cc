#include <string>
#include "ExsdirTest.hh"

void ExsdirTest::runTest(void)
{
  // Exsdir header info
  UT_ASSERT(x.process_date() == "09/03/2008");

  // Exsdir table info
  UT_ASSERT(x.number_of_tables() == 21);
  string id = x.table_identifier(0);
  UT_ASSERT(x.file_name(id) == "endf71x/H/1001.710nc");
  UT_ASSERT(x.address(id) == 4);
  UT_ASSERT(x.table_identifier("1003") == "1003.80c");

  UT_ASSERT(x.table_identifier("1001") == "1001.80c");
  UT_ASSERT(x.atomic_weight_ratio("1001.80c") == 0.999167);
  UT_ASSERT(x.file_name("1001.80c") == "endf71x/H/1001.710nc");
  UT_ASSERT(x.address("1001.80c") == 4); 
  UT_ASSERT(x.temperature("1001.80c") == 2.530100e-8);
    
  UT_ASSERT(x.table_identifier("1002.80c") == "1002.80c");
  UT_ASSERT(x.atomic_weight_ratio("1002.80c") == 1.9968);
  UT_ASSERT(x.file_name("1002.80c") == "endf71x/H/1002.710nc");
  UT_ASSERT(x.address("1002.80c") == 4); 
  UT_ASSERT(x.temperature("1002.80c") == 2.530100e-8);

  UT_ASSERT(x.table_identifier("1003") == "1003.80c");
  UT_ASSERT(x.atomic_weight_ratio("1003.80c") == 2.989596);
  UT_ASSERT(x.file_name("1003.80c") == "endf71x/H/1003.710nc");
  UT_ASSERT(x.address("1003.80c") == 4); 
  UT_ASSERT(x.temperature("1003.80c") == 2.530100e-8);

  UT_ASSERT(x.atomic_weight_ratio("1001.81c") == 0.999167);
  UT_ASSERT(x.file_name("1001.81c") == "endf71x/H/1001.711nc");
  UT_ASSERT(x.address("1001.81c") == 4); 
  UT_ASSERT(x.temperature("1001.81c") == 5.170400e-8);

  UT_ASSERT(x.atomic_weight_ratio("1003.86c") == 2.989596);
  UT_ASSERT(x.file_name("1003.86c") == "endf71x/H/1003.716nc");
  UT_ASSERT(x.address("1003.86c") == 4); 
  UT_ASSERT(x.temperature("1003.86c") == 2.154300e-8);
}
