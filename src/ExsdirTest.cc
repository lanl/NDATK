#include <string>
#include "ExsdirTest.hh"

void ExsdirTest::runTest(void)
{
  // Exsdir header info
  UT_ASSERT(x.get(Exsdir::string_val::DATE) == string("09/03/2008"));

  // Exsdir table info
  string id = x.get(Exsdir::string_val_n::ID, 0);
  UT_ASSERT(x.get(Exsdir::string_val_x::NAME, id) == 
            string("endf71x/H/1001.710nc"));
  UT_ASSERT(x.get(Exsdir::int_val_x::ADDRESS, id) == 4);

 }
