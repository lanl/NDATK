#include <string>

#include "ChartTest.hh"
#include "utils.hh"

void ChartTest::runTest(void)
{
  // Chart header info
  UT_ASSERT(x.type() == "ndatk_chart_1.0");
  UT_ASSERT(x.name() == "early_universe");
  UT_ASSERT(starts_with(x.event(0), "+3hrs"));

  // Chart element info
  UT_ASSERT(x.number_of_elements() == 5);
  UT_ASSERT(x.chemical_symbol(1) == "H");
  UT_ASSERT(x.element_name(1) == "hydrogen");

  UT_ASSERT(x.chemical_symbol(2) == "He");
  UT_ASSERT(x.element_name(2) == "helium");

  // Chart symbol translation 
  for (int z = 0; z < x.number_of_elements(); z++) {
    string symbol = x.chemical_symbol(z);
    UT_ASSERT(x.element_name(symbol) == x.element_name(z));
  }

  // Chart nuclide info
  UT_ASSERT(x.number_of_nuclides() == 9);
  UT_ASSERT(x.atomic_weight_ratio(1001) == 0.999167);
  UT_ASSERT(x.natural_abundance(1001) == 0.999850);
  UT_ASSERT(x.half_life(1001) == 4.336200e+17);

  // Chart nuclide name translation
  UT_ASSERT(x.atomic_weight("1001") == x.atomic_weight(1001));
  UT_ASSERT(x.atomic_weight("H-1") == x.atomic_weight(1001));
  UT_ASSERT(x.atomic_weight("h1") == x.atomic_weight(1001));
  UT_ASSERT(x.atomic_weight("1H") == x.atomic_weight(1001));
  UT_ASSERT(x.atomic_weight("1-H") == x.atomic_weight(1001));

  UT_ASSERT(x.atomic_weight("2003") == x.atomic_weight(2003));
  UT_ASSERT(x.atomic_weight("he-3") == x.atomic_weight(2003));
  UT_ASSERT(x.atomic_weight("He3") == x.atomic_weight(2003));
  UT_ASSERT(x.atomic_weight("3he") == x.atomic_weight(2003));
  UT_ASSERT(x.atomic_weight("3-He") == x.atomic_weight(2003));

  // Create some atom composition maps using
  // values copied from ChartTest::chart_dat
  map<int, double> H1{{1001, 1.0}};
  map<int, double> H{{1001, 0.999850}, {1002, 0.000150}};
  map<int, double> He4{{2004, 1.0}};
  map<int, double> He{{2003, 0.000001}, {2004, 0.999999}};
  map<int, double> Li{{3006, 0.075900}, {3007, 0.924100}};

  // Atom composition
  UT_ASSERT(x.atom_comp_of("1001") == H1); 
  UT_ASSERT(x.atom_comp_of("H") == H);
  UT_ASSERT(x.atom_comp_of("2004") == He4);
  UT_ASSERT(x.atom_comp_of("2000") == He);
  UT_ASSERT(x.atom_comp_of("Li") == Li);

  // Create some mass composition maps
  // values calculated by ndatk.py prototype
  map<int, double> mH{{1001, 0.999735623351062}, 
      {1002, 0.0002997352662605792}};
  map<int, double> mHe{{2003, 7.53517121605419e-07}, 
      {2004, 0.9999990686469464}};
  map<int, double> mLi{{3006, 0.0657755107208508}, 
      {3007, 0.9340857440036178}};

  // Mass composition
  UT_ASSERT(x.mass_comp_of("1001") == H1); 
  UT_ASSERT(x.mass_comp_of("H") == mH);
  UT_ASSERT(x.mass_comp_of("2004") == He4);
  UT_ASSERT(x.mass_comp_of("2000") == mHe);
  UT_ASSERT(x.mass_comp_of("Li") == mLi);

}
