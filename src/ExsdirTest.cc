#include <string>
#include "ExsdirTest.hh"

void ExsdirTest::runTest(void)
{
  // Exsdir header info
  UT_ASSERT(x.process_date() == "09/03/2008");

  // Exsdir table info
  string id = x.table_identifier(0);
  UT_ASSERT(x.file_name(id) == "endf71x/H/1001.710nc");
  UT_ASSERT(x.address(id) == 4);

 }
