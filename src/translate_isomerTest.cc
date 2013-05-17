#include "utils.hh"
#include "translate_isomer.hh"
#include "translate_isomerTest.hh"

using namespace std;
using namespace ndatk;

void translate_isomerTest::runTest()
{

  for (int Z = 1; Z < 100; Z++) {
    int Z0 = Z*1000;
    UT_ASSERT(calculate_SZA(Z) == Z0);
    UT_ASSERT(extract_S(Z0) == 0);
    UT_ASSERT(extract_Z(Z0) == Z);
    UT_ASSERT(extract_A(Z0) == 0);
    string C = Z_to_symbol[Z];
    UT_ASSERT(map_at(symbol_to_Z, C) == Z); 
    UT_ASSERT(translate_isomer(C) == Z0); 
    for (int A = 1; A < 100; A++) {
      int ZA = Z*1000+A;
      UT_ASSERT(calculate_SZA(Z, A) == ZA);
      UT_ASSERT(extract_Z(ZA) == Z);
      UT_ASSERT(extract_A(ZA) == A);
      string N = lexical_cast<string, int>(A);
      string C_N = C + N;
      string N_C = N + C;
      UT_ASSERT(translate_isomer(C_N) == ZA);
      UT_ASSERT(translate_isomer(N_C) == ZA);
      C_N = C + "-" + N;
      N_C = N + "-" + C;
      UT_ASSERT(translate_isomer(C_N) == ZA);
      UT_ASSERT(translate_isomer(N_C) == ZA);
      for (int S = 0; S < 3; S++) {
        int SZA = S*1000000+Z*1000+A;
        UT_ASSERT(extract_S(SZA) == S);
        UT_ASSERT(extract_Z(SZA) == Z);
        UT_ASSERT(extract_A(SZA) == A);
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
