#include "utils.hh"
#include "translate_isomer.hh"
#include "translate_isomerTest.hh"

using namespace std;
using namespace ndatk;

void translate_isomerTest::runTest()
{
  // spot check Z_to_symbol for a handful of elements
  UT_ASSERT(Z_to_symbol[1] == string("H"));
  UT_ASSERT(Z_to_symbol[2] == string("He"));
  UT_ASSERT(Z_to_symbol[26] == string("Fe"));
  UT_ASSERT(Z_to_symbol[92] == string("U"));
  UT_ASSERT(Z_to_symbol[94] == string("Pu"));

  // Spot check symbol_to_Z for a handful of elements
  // N.B. cannot use operator[] with const map!!!
  UT_ASSERT(symbol_to_Z.at(string("H")) == 1);
  UT_ASSERT(symbol_to_Z.at(string("He")) == 2);
  UT_ASSERT(symbol_to_Z.at(string("Fe")) == 26);
  UT_ASSERT(symbol_to_Z.at(string("U")) == 92);
  UT_ASSERT(symbol_to_Z.at(string("Pu")) == 94);
  
  // Check H...Es
  for (int Z = 1; Z < 100; Z++) { 
    int Z0 = Z*1000;            // canonical element SZA
    UT_ASSERT(calculate_SZA(Z) == Z0);
    UT_ASSERT(extract_S(Z0) == 0);
    UT_ASSERT(extract_Z(Z0) == Z);
    UT_ASSERT(extract_A(Z0) == 0);
    UT_ASSERT(is_element(Z0));
    UT_ASSERT(ground_state(Z0) == Z0);
    string C = Z_to_symbol[Z];
    UT_ASSERT(map_at(symbol_to_Z, C) == Z); 
    UT_ASSERT(translate_isomer(C) == Z0); 
    // Check Z <= A < 2.5*Z (H..Es)
    for (int A = Z; A < 2.5*Z; A++) {
      int ZA = Z*1000+A;        // canonical ground state SZA
      UT_ASSERT(calculate_SZA(Z, A) == ZA);
      UT_ASSERT(extract_Z(ZA) == Z);
      UT_ASSERT(extract_A(ZA) == A);
      UT_ASSERT(!is_element(ZA));
      UT_ASSERT(ground_state(ZA) == ZA);
      string N = lexical_cast<string, int>(A);
      string C_N = C + N;
      string N_C = N + C;
      UT_ASSERT(translate_isomer(C_N) == ZA);
      UT_ASSERT(translate_isomer(N_C) == ZA);
      C_N = C + "-" + N;
      N_C = N + "-" + C;
      UT_ASSERT(translate_isomer(C_N) == ZA);
      UT_ASSERT(translate_isomer(N_C) == ZA);
      // Check a few excited states
      for (int S = 0; S < 3; S++) {
        int SZA = S*1000000+Z*1000+A; // canonical SZA
        UT_ASSERT(extract_S(SZA) == S);
        UT_ASSERT(extract_Z(SZA) == Z);
        UT_ASSERT(extract_A(SZA) == A);
        UT_ASSERT(!is_element(SZA));
        UT_ASSERT(ground_state(SZA) == ZA);
        string Nm = lexical_cast<string, int>(A) + "m" 
          + lexical_cast<string, int>(S);
        string C_Nm = C + "-" + Nm;
        string Nm_C = Nm + "-" + C;
        UT_ASSERT(translate_isomer(C_Nm) == SZA);
        UT_ASSERT(translate_isomer(Nm_C) == SZA);
        C_Nm = C + Nm;
        Nm_C = Nm + C;
        UT_ASSERT(translate_isomer(C_Nm) == SZA);
        UT_ASSERT(translate_isomer(Nm_C) == SZA);
      }
    }
  }
}
