#include "LibraryTest.hh"

void LibraryTest::runTest(void)
{
  // Chart header info
  UT_ASSERT(x.get(Library::string_val::NAME) == string("early_universe"));
  UT_ASSERT(x.get(Library::string_val::DATE) == string("+3hrs"));

  UT_ASSERT(x.get(Library::string_val_x::ID, "H1") == "1001.62c");
  UT_ASSERT(x.get(Library::string_val_x::ID, "H-2") == "1002.66c");
  UT_ASSERT(x.get(Library::string_val_x::ID, "3h") == "1003.69c");
  UT_ASSERT(x.get(Library::string_val_x::ID, "He3") == "2003.66c");
  UT_ASSERT(x.get(Library::string_val_x::ID, "4-He") == "2004.62c");
  UT_ASSERT(x.get(Library::string_val_x::ID, "Li6") == "3006.66c");
  UT_ASSERT(x.get(Library::string_val_x::ID, "Li-7") == "3007.66c");
  UT_ASSERT(x.get(Library::string_val_x::ID, "4007") == "4007.35c");
}
