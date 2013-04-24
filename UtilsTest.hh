#include <string>
#include <sstream>
#include "UnitTest.hh"
#include "utils.hh"

using namespace std;
using namespace ndatk;

class UtilsTest: public UnitTest {

public:

  void runTest() {

    string lt("  \tLeft Trim  "); 
    UT_ASSERT(ltrim(lt) == string("Left Trim  "));

    string rt("  Right Trim \t ");
    UT_ASSERT(rtrim(rt) == string("  Right Trim"));

    string bt("  Both Trim  ");
    UT_ASSERT(trim(bt) == string("Both Trim"));

    UT_ASSERT(cmp_nocase(string("Hello World!"), "HELLO WORLD!") == 0);

    UT_ASSERT(starts_with_nocase(string("Hello World!"), "HELLO"));
    UT_ASSERT(starts_with_nocase(string("Hello World!"), "hello"));
    UT_ASSERT(starts_with_nocase(string("Hello World!"), "hELLO"));
    UT_ASSERT(!starts_with_nocase(string("Hello World!"), " Hello"));
    UT_ASSERT(!starts_with_nocase(string("Hello World!"), "Goodbye"));

    UT_ASSERT(is_date("01/23/45"));
    UT_ASSERT(is_date("01/23/4567"));
    UT_ASSERT(!is_date("Jan 12"));
    UT_ASSERT(!is_date("01/23/456789"));

    istringstream s("# comment\n \nline # comment\n \n");
    string line;
    UT_ASSERT(get_logical_line(s, line).good());
    UT_ASSERT(line == string("line"));
  }
};
