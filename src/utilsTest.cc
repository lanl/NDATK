#include <string>
#include <sstream>
#include "utils.hh"
#include "utilsTest.hh"
#include <iostream>
using namespace std;
using namespace ndatk;

void utilsTest::runTest() {

  string digits("0123456789");
  string alphas("abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

  UT_ASSERT(is_space(' '));
  UT_ASSERT(is_space('\t'));
  UT_ASSERT(!not_space(' '));
  UT_ASSERT(!not_space('\t'));
  for (string::size_type i = 0; i < digits.size(); i++) {
    UT_ASSERT(!is_space(digits[i]));
    UT_ASSERT(not_space(digits[i]));
  }
  for (string::size_type i = 0; i < alphas.size(); i++) {
    UT_ASSERT(!is_space(alphas[i]));
    UT_ASSERT(not_space(alphas[i]));
  }

  UT_ASSERT(!is_all_alphas(digits));
  UT_ASSERT(is_all_alphas(alphas));
  UT_ASSERT(is_all_digits(digits));
  UT_ASSERT(!is_all_digits(alphas));
    
  UT_ASSERT(is_date("01/23/45"));
  UT_ASSERT(is_date("01/23/4567"));
  UT_ASSERT(!is_date("Jan 12"));
  UT_ASSERT(!is_date("01/23/456789"));

  UT_ASSERT(starts_with(string("Hello World!"), "Hello"));
  UT_ASSERT(!starts_with(string("Hello World!"), "hello"));
  UT_ASSERT(!starts_with(string("Hello World!"), "hELLO"));
  UT_ASSERT(!starts_with(string("Hello World!"), "Goodbye"));

  UT_ASSERT(starts_with_nocase(string("Hello World!"), "HELLO"));
  UT_ASSERT(starts_with_nocase(string("Hello World!"), "hello"));
  UT_ASSERT(starts_with_nocase(string("Hello World!"), "hELLO"));
  UT_ASSERT(!starts_with_nocase(string("Hello World!"), " Hello"));
  UT_ASSERT(!starts_with_nocase(string("Hello World!"), "Goodbye"));

  UT_ASSERT(cmp_nocase(string("Hello World!"), "HELLO WORLD!") == 0);
  UT_ASSERT(cmp_nocase(string("Hello World!"), "hello world!") == 0);

  // Test trim functions
  UT_ASSERT(ltrim("  \tLeft Trim  ") == "Left Trim  ");
  UT_ASSERT(rtrim("  Right Trim \t ") == "  Right Trim");
  UT_ASSERT(trim("\t  Both Trim\t  ") == "Both Trim");

  // Test title case
  UT_ASSERT(title("HELLO") == "Hello");
  UT_ASSERT(title("hello") == "Hello");
  UT_ASSERT(title("hElLo") == "Hello"); 

  // Test split on whitespace
  vector<string> v = split("Hello World!");
  UT_ASSERT(v.size() == 2);
  UT_ASSERT(v[0] == "Hello");
  UT_ASSERT(v[1] == "World!");

  // Test split on character
  vector<string> w = split(":foo:bar:baz:::", ':');
  UT_ASSERT(w.size() == 7);     // one more than delimiter count in string
  UT_ASSERT(w[0] == "");        // leading delimiter produces empty string
  UT_ASSERT(w[1] == "foo");
  UT_ASSERT(w[2] == "bar");
  UT_ASSERT(w[3] == "baz");
  UT_ASSERT(w[4] == "");        // successive delimiters produce empty string
  UT_ASSERT(w[5] == "");        // successive delimiters produce empty string
  UT_ASSERT(w[6] == "");        // trailing  delimiter produces empty string
  w = split("", ':');
  UT_ASSERT(w.size() == 1);     // empty string splits into one empty string
  UT_ASSERT(w[0] == "");

  istringstream s("# comment\n \n  line # comment\ntrailing\n");
  string line;
  UT_ASSERT(get_logical_line(s, line).good());
  UT_ASSERT(line == string("line"));

  istringstream s1("Now \"is the time\" for all good men");
  string first, second, third;
  s1 >> first;
  quoted_str(s1, second) >> third;
  UT_ASSERT(first == "Now");
  UT_ASSERT(second == "is the time");
  UT_ASSERT(third == "for");

  map<int, string> m;
  m[1] = "foo";
  m[7] = "bar";
  m[42] = "marvin";
  UT_ASSERT(map_at(m, 1) == "foo");
  UT_ASSERT(map_at(m, 7) == "bar");
  UT_ASSERT(map_at(m, 42) == "marvin");
    
  // Need extra parens to protect comma from macro expansion
  UT_ASSERT((lexical_cast<double, string>("0.0") == 0.0));
  UT_ASSERT((lexical_cast<string, double>(0.0) == "0"));
  UT_ASSERT((lexical_cast<int, string>("42") == 42));
  UT_ASSERT((lexical_cast<string, int>(42) == "42"));

  // Test some of the POSIX based functions
  UT_ASSERT(get_realpath(".") == get_cwd());
  UT_ASSERT(is_readable("utilsTest.cc"));
  UT_ASSERT(file_starts_with("utilsTest.cc", "using"));


}
