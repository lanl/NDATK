#include "FinderTest.hh"
#include "utils.hh"

void FinderTest::runTest(void)
{

  // Test default construction
  UT_ASSERT(x.get_path() == "");
  
  // Test push back, push front
  x.set_path("foo:bar");
  UT_ASSERT(x.get_path() == "foo:bar");

  x.set_path("!!:baz:omega");
  UT_ASSERT(x.get_path() == "foo:bar:baz:omega");

  x.set_path("alpha:.:!!");
  UT_ASSERT(x.get_path() == "alpha:.:foo:bar:baz:omega");

  // Test search with good path
  UT_ASSERT(x.abs_path("FinderTest.cc") == get_cwd() + "/FinderTest.cc");

  // Test search with good path and good magic string
  UT_ASSERT(x.abs_path("FinderTest.cc", "void") == 
            get_cwd() + "/FinderTest.cc");

  // Test search with good path but bad magic string
  UT_ASSERT(x.abs_path("FinderTest.cc", "foo") == "");

  // Test clearing path, not finding local file
  x.set_path("");
  UT_ASSERT(x.get_path() == "");
  UT_ASSERT(x.abs_path("FinderTest.cc") == "");

  // Test basic environment addition to path
  x.set_path("$PATH");
  UT_ASSERT(x.get_path() == get_env("PATH"));
}
            
