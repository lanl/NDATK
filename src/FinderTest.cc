#include "FinderTest.hh"
#include "utils.hh"
#include <iostream>

void FinderTest::runTest(void)
{

  // Test default construction
  UT_ASSERT(x.to_string() == "");
  
  // Test push back, push front
  x.push_back("foo:bar");
  UT_ASSERT(x.to_string() == "foo:bar");

  x.push_back("baz:omega");
  UT_ASSERT(x.to_string() == "foo:bar:baz:omega");

  x.push_front("alpha:.");
  UT_ASSERT(x.to_string() == "alpha:.:foo:bar:baz:omega");

  // Test search with good path
  UT_ASSERT(x.abs_path("FinderTest.cc") == get_cwd() + "/FinderTest.cc");

  // Test search with good path and good magic string
  UT_ASSERT(x.abs_path("FinderTest.cc", "void") == 
            get_cwd() + "/FinderTest.cc");

  // Test search with good path but bad magic string
  UT_ASSERT(x.abs_path("FinderTest.cc", "foo") == "");

  // Test basic environment addition to path
  x.clear();
  x.push_back_env("PATH");
  UT_ASSERT(x.to_string() == get_env("PATH"));
}
            
