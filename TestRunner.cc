#include <iostream>
#include "UtilsTest.hh"
#include "ChartTest.hh"
#include "LibraryTest.hh"

int main()
{

  UtilsTest test1;
  ChartTest test2;
  LibraryTest test3;

  test1.runTest();
  test2.runTest();
  test3.runTest();

  std::cout << "SUCCESS!" << std::endl;
  std::cout << UnitTest::getNumSuccess() << " tests completed." << std::endl;
  return 0;
}
