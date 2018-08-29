#include <iostream>
#include "LibraryTest.hh"

map<int, double> LibraryTest::comp(string name) const
{
  map<int, double> empty;
  map<int, double> H1{{1001, 1.0}};
  map<int, double> H{{1001, 0.999850}, {1002, 0.000150}};
  map<int, double> HO{{1001, 0.999850}, {1002, 0.000150}, {8000, 1.0}};
  map<int, double> He{{2003, 0.000001}, {2004, 0.999999}};
  if (name == "empty")
    return empty;
  else if (name == "H1")
    return H1;
  else if (name == "H")
    return H;
  else if (name == "HO")
    return HO;
  else if (name == "He")
    return He;
  return empty;
}
      
void LibraryTest::runTest(void)
{

  UT_ASSERT(y.type() == "ndatk_library_1.0");

  // Set table identifier from library
  UT_ASSERT(y.table_identifier("H1") == "1001.80c");
  UT_ASSERT(y.atomic_weight_ratio() == 0.999167);
  UT_ASSERT(y.file_name() == "endf71x/H/1001.710nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 2.530100e-8); // Should default to room temp

  UT_ASSERT(y.number_of_temperatures() == 2); // Two temps for H1

  // Check below lowest temp
  UT_ASSERT(y.temperature(0.0) == 2.530100e-8);
  UT_ASSERT(y.atomic_weight_ratio() == 0.999167);
  UT_ASSERT(y.file_name() == "endf71x/H/1001.710nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 2.530100e-8);

  // Check between two temps but near lowest temp
  UT_ASSERT(y.temperature(3.0e-8) == 2.530100e-8);
  UT_ASSERT(y.atomic_weight_ratio() == 0.999167);
  UT_ASSERT(y.file_name() == "endf71x/H/1001.710nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 2.530100e-8);

  // Check between two temps but near highest temp
  UT_ASSERT(y.temperature(4.0e-8) == 5.170400e-8);
  UT_ASSERT(y.atomic_weight_ratio() == 0.999167);
  UT_ASSERT(y.file_name() == "endf71x/H/1001.711nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 5.170400e-8);

  // Check above highest temp
  UT_ASSERT(y.temperature(1.0) == 5.170400e-8);
  UT_ASSERT(y.atomic_weight_ratio() == 0.999167);
  UT_ASSERT(y.file_name() == "endf71x/H/1001.711nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 5.170400e-8);

  // Set table identifier from Library
  UT_ASSERT(y.table_identifier("H-2") == "1002.80c");
  UT_ASSERT(y.atomic_weight_ratio() == 1.9968);
  UT_ASSERT(y.file_name() == "endf71x/H/1002.710nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 2.530100e-8); // Should default to room temp

  UT_ASSERT(y.number_of_temperatures() == 2);

  // Set table identifier from Library
  UT_ASSERT(y.table_identifier("3h") == "1003.80c");
  UT_ASSERT(y.atomic_weight_ratio() == 2.989596);
  UT_ASSERT(y.file_name() == "endf71x/H/1003.710nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 2.530100e-8);

  UT_ASSERT(y.number_of_temperatures() == 3);

  // Check below lowest temp
  UT_ASSERT(y.temperature(2.0e-8) == 2.530100e-8);
  UT_ASSERT(y.atomic_weight_ratio() == 2.989596);
  UT_ASSERT(y.file_name() == "endf71x/H/1003.710nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 2.530100e-8);

  // Check above lowest temp
  UT_ASSERT(y.temperature(3.0e-8) == 2.530100e-8);
  UT_ASSERT(y.atomic_weight_ratio() == 2.989596);
  UT_ASSERT(y.file_name() == "endf71x/H/1003.710nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 2.530100e-8);

  // Check below mid temp
  UT_ASSERT(y.temperature(5.170400e-8) == 5.170400e-8);
  UT_ASSERT(y.atomic_weight_ratio() == 2.989596);
  UT_ASSERT(y.file_name() == "endf71x/H/1003.711nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 5.170400e-8);

  // Check above highest temp
  UT_ASSERT(y.temperature(8.0e-8) == 7.755600e-8);
  UT_ASSERT(y.atomic_weight_ratio() == 2.989596);
  UT_ASSERT(y.file_name() == "endf71x/H/1003.712nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 7.755600e-8);

  // Set table identifier from Exsdir
  UT_ASSERT(y.table_identifier("1001.81c") == "1001.81c");
  UT_ASSERT(y.atomic_weight_ratio() == 0.999167);
  UT_ASSERT(y.file_name() == "endf71x/H/1001.711nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 5.170400e-8);
  UT_ASSERT(y.number_of_temperatures() == 1);

  // Set table identifier from Exsdir
  UT_ASSERT(y.table_identifier("H3.86c") == "1003.86c");
  UT_ASSERT(y.atomic_weight_ratio() == 2.989596);
  UT_ASSERT(y.file_name() == "endf71x/H/1003.716nc");
  UT_ASSERT(y.address() == 4); 
  UT_ASSERT(y.temperature() == 2.154300e-8);
  UT_ASSERT(y.number_of_temperatures() == 1);
  UT_ASSERT(y.temperature(0.0) == 2.154300e-8);
  UT_ASSERT(y.temperature(1.0) == 2.154300e-8);

  // Create a few atom composition maps
  // using Library::comp
  map<int, double> empty = comp("empty");
  map<int, double> H1 = comp("H1");
  map<int, double> H = comp("H");
  map<int, double> HO = comp("HO");
  map<int, double> He = comp("He");

  // Filter composition maps through library
  UT_ASSERT(y.comp_of(H1) == H1);
  UT_ASSERT(y.comp_of(H) == H);
  UT_ASSERT(y.comp_of(HO) == H);
  UT_ASSERT(y.comp_of(He) == empty);

  // Bind member function to name suitable for use in Library::comp_of
  function<map<int, double>(string)> f = bind(&LibraryTest::comp, this, 
                                              placeholders::_1);

  // Use function to resolve names
  UT_ASSERT(y.comp_of("empty", f) == empty);
  UT_ASSERT(y.comp_of("H1", f) == H1);
  UT_ASSERT(y.comp_of("H", f) == H);
  UT_ASSERT(y.comp_of("HO", f) == H);
  UT_ASSERT(y.comp_of("He", f) == empty);

}
