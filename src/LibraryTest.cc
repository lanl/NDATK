#include <iostream>
#include "LibraryTest.hh"

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
}
