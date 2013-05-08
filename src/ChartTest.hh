#include <string>
#include <sstream>
#include "UnitTest.hh"
#include "Chart.hh"

using namespace std;
using namespace ndatk;

static istringstream cd( 
  "NAME:\n"
  "early_universe\n"
  "DATE:\n"
  "+3hrs\n"
  "INFO:\n"
  "Element data: \"Nuclides and Isotopes\" 16ed, Nuclide Data: ENDF-B/VII\n"
  "PERIODIC_TABLE:\n"
  "# See: \"Nuclides and Isotopes\" 16ed. p 0\n"
  "# Z sym at_wgt(u) name\n"
  "0 n 1.00866491578 neutron\n"
  "1 H 1.00794 hydrogen\n"
  "2 He 4.002602 helium\n"
  "3 Li 6.941 lithium\n"
  "4 Be 9.012182 beryllium\n"
  "CHART_OF_THE_NUCLIDES:\n"
  "# See: ENDF/B-VII, MF=1, MT=451\n" 
  "#    sza        awr        abu half-life(s)\n"
  "       1   1.000000   0.000000 6.139000e+02\n"
  "    1001   0.999167   0.999850 4.336200e+17\n"
  "    1002   1.996799   0.000150 4.336200e+17\n"
  "    1003   2.990139   0.000000 3.885235e+08\n"
  "    2003   2.990120   0.000001 4.336200e+17\n"
  "    2004   3.968218   0.999999 4.336200e+17\n"
  "    3006   5.963450   0.075900 4.336200e+17\n"
  "    3007   6.955733   0.924100 4.336200e+17\n"
  "    4007   6.956651   0.000000 4.598208e+06\n");

class ChartTest: public UnitTest 
{

public:

  ChartTest(): x(cd) {}

  void runTest();

private:

  Chart x;

};
