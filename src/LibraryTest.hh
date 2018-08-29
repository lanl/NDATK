#include <string>
#include <sstream>
#include "UnitTest.hh"
#include "Library.hh"

using namespace std;
using namespace ndatk;

static Exsdir exsdir_data(void)
{

static istringstream exsdir_dat(
"type: ndatk_exsdir_1.0\n"
"name: test_exsdir\n"
"atomic weight ratios\n"
"   0001  1.000000   0001  1.000000\n"
"   1000  0.99931697 1001   0.99916733   1002   1.99679968\n"   
"   1003   2.99013997 1004   3.99320563   1005   4.99205575\n"
"   1006   5.99301364 1007   6.99216250\n"
"09/03/2008\n"
"directory\n"
"1001.80c 0.999167 endf71x/H/1001.710nc 0 1 4 17969 0 0 2.530100E-08\n"
"1001.81c 0.999167 endf71x/H/1001.711nc 0 1 4 17969 0 0 5.170400E-08\n"
"1001.82c 0.999167 endf71x/H/1001.712nc 0 1 4 17969 0 0 7.755600E-08\n"
"1001.83c 0.999167 endf71x/H/1001.713nc 0 1 4 17969 0 0 1.034100E-07\n"
"1001.84c 0.999167 endf71x/H/1001.714nc 0 1 4 17969 0 0 2.154300E-07\n"
"1001.85c 0.999167 endf71x/H/1001.715nc 0 1 4 17969 0 0 8.617400E-12\n"
"1001.86c 0.999167 endf71x/H/1001.716nc 0 1 4 17969 0 0 2.154300E-08\n"
"1002.80c 1.9968 endf71x/H/1002.710nc 0 1 4 10452 0 0 2.530100E-08\n"
"1002.81c 1.9968 endf71x/H/1002.711nc 0 1 4 10618 0 0 5.170400E-08\n"
"1002.82c 1.9968 endf71x/H/1002.712nc 0 1 4 10683 0 0 7.755600E-08\n"
"1002.83c 1.9968 endf71x/H/1002.713nc 0 1 4 10772 0 0 1.034100E-07\n"
"1002.84c 1.9968 endf71x/H/1002.714nc 0 1 4 10904 0 0 2.154300E-07\n"
"1002.85c 1.9968 endf71x/H/1002.715nc 0 1 4 9704 0 0 8.617400E-12\n"
"1002.86c 1.9968 endf71x/H/1002.716nc 0 1 4 10409 0 0 2.154300E-08\n"
"1003.80c 2.989596 endf71x/H/1003.710nc 0 1 4 11728 0 0 2.530100E-08\n"
"1003.81c 2.989596 endf71x/H/1003.711nc 0 1 4 11828 0 0 5.170400E-08\n"
"1003.82c 2.989596 endf71x/H/1003.712nc 0 1 4 11883 0 0 7.755600E-08\n"
"1003.83c 2.989596 endf71x/H/1003.713nc 0 1 4 11908 0 0 1.034100E-07\n"
"1003.84c 2.989596 endf71x/H/1003.714nc 0 1 4 11978 0 0 2.154300E-07\n"
"1003.85c 2.989596 endf71x/H/1003.715nc 0 1 4 10833 0 0 8.617400E-12\n"
"1003.86c 2.989596 endf71x/H/1003.716nc 0 1 4 11708 0 0 2.154300E-08\n");

  Exsdir result;
  
  exsdir_dat >> result;
  return result;
}

static istringstream library_data(
"type: ndatk_library_1.0\n"
"name: test_library\n"
"ids:\n"
"1001 1001.80c\n"
"1002 1002.80c\n"
"1003 1003.80c\n"
"1001 1001.81c\n"
"1002 1002.81c\n"
"1002 1002.81c\n"
"1003 1003.80c\n"
"1003 1003.81c\n"
"1003 1003.82c\n"
"%%\n");


class LibraryTest: public UnitTest
{
public:
  LibraryTest(): x(exsdir_data()), y(library_data, x) {} 
  void runTest();
  map<int, double> comp(string name) const;

private:
  Exsdir x;
  Library y;
};

