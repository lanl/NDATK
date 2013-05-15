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

 }
