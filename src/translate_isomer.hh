#ifndef TRANSLATE_ISOMER_HH
#define TRANSLATE_ISOMER_HH

#include <vector>
#include <string>
#include <map>

/* Isomer = C                   (* Chemical symbol *)
          | N                   (* Z | ZA | SZA *)
          | C_Nm                (* C[-]A[mS] *) 
          | Nm_C                (* A[mS][-]C *)
          | Nm;                 (* ZA[mS] *)
   C      = 'H'|'He'|...|'Lw';
   N      = D,{D};
   D      = '0'|'1'|...|'9';
   C_Nm   = C, '-', Nm
          | C, Nm;
   Nm_C   = Nm, '-', C
          | Nm, C;
   Nm     = N
          | N, 'm', N;
*/

namespace ndatk
{
  // Chemical symbols indexed by atomic number.
  extern const std::vector<std::string> Z_to_symbol;

  // Atomic number indexed by chemical symbol.
  extern const std::map<std::string, int> symbol_to_Z;

  // Translate isomer string to canonial SZA.
  extern int translate_isomer(std::string isomer);

  // Extract S from canonical SZA.
  inline int extract_S(int sza) { return sza/1000000; }

  // Extract Z from canonical SZA.
  inline int extract_Z(int sza) { return (sza%1000000)/1000; }

  // Extract A from canonical SZA.
  inline int extract_A(int sza) { return sza%1000; }

  // Calculate canonical SZA from state, atomic, mass numbers
  inline int calculate_SZA(int Z, int A=0, int S=0) {
    return S*1000000+Z*1000+A;
  }

}
#endif
