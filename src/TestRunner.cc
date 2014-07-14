#include <iostream>
#include "LibraryTest.hh"
#include "ChartTest.hh"
#include "ExsdirTest.hh"
#include "FinderTest.hh"
#include "translate_isomerTest.hh"
#include "utilsTest.hh"

int main()
{

  utilsTest test1; test1.runTest();
  translate_isomerTest test5; test5.runTest();
  ChartTest test2; test2.runTest();
  ExsdirTest test3; test3.runTest();
  LibraryTest test4; test4.runTest();
  FinderTest test6; test6.runTest();

  std::cout << "SUCCESS!" << std::endl;
  std::cout << UnitTest::getNumSuccess() << " tests completed." << std::endl;
  return 0;
}
