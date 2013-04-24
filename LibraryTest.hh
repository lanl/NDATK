#include <string>
#include "UnitTest.hh"
#include "library.hh"

using namespace std;
using namespace ndatk;

class LibraryTest: public UnitTest {

public:

  void runTest() {
    
    Library x("xsdir.inc");

    // Library header info
    UT_ASSERT(x.get(Library::string_val::NAME) == string("xsdir.inc"));
    UT_ASSERT(x.get(Library::string_val::DATE) == string("09/03/2008"));

    // Library table info
    string id = x.get(Library::string_val_n::ID, 0);
    UT_ASSERT(x.get(Library::string_val_x::NAME, id) == 
              string("endf71x/H/1001.710nc"));
    UT_ASSERT(x.get(Library::int_val_x::ADDRESS, id) == 4);

  }
};
