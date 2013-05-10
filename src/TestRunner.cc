#include <iostream>
#include "utilsTest.hh"
#include "LibraryTest.hh"
#include "ChartTest.hh"
#include "ExsdirTest.hh"

int main()
{

  utilsTest test1;
  ChartTest test2;
  ExsdirTest test3;
  LibraryTest test4;

  test1.runTest();
  test2.runTest();
  test3.runTest();
  test4.runTest();

  std::cout << "SUCCESS!" << std::endl;
  std::cout << UnitTest::getNumSuccess() << " tests completed." << std::endl;
  return 0;
}
