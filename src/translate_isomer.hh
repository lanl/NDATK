#ifndef TRANSLATE_ISOMER_HH
#define TRANSLATE_ISOMER_HH

/**
   \file translate_isomer.hh

   Translate and canonicalize isomer designators.

   \author Mark G. Gray <gray@lanl.gov>
   Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.
*/

#include <vector>
#include <string>
#include <map>


namespace ndatk
{
  /** 
      Chemical symbols std::string indexed by int atomic number in
      std::vector.
  */
  extern const std::vector<std::string> Z_to_symbol;

  /** 
      Atomic number int indexed by chemical symbol std::string in
      std::map.
  */
  extern const std::map<std::string, int> symbol_to_Z;

  /**
     Translate isomer string to canonial SZA.

     \param[in] isomer std::string
     \return int SZA

     ISO/IEC 14977 EBNF of recognized input strings:
     \code
     Isomer = C                   (* Chemical symbol *)
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
     \endcode
  */
  extern int translate_isomer(std::string isomer);

  /**
     Extract S from canonical SZA.
     
     \param[in] sza int
     \return state int
  */
  inline int extract_S(int sza) { return sza/1000000; }

  /**
     Extract Z from canonical SZA.

     \param[in] sza int
     \return atomic number int
  */
  inline int extract_Z(int sza) { return (sza%1000000)/1000; }

  /** 
      Extract A from canonical SZA.

      \param[in] sza int
      \return mass number int
  */
  inline int extract_A(int sza) { return sza%1000; }

  /** 
      Calculate canonical SZA from state, atomic, mass numbers.
      
      \param[in] Z int atomic number
      \param[in] A int mass number
      \param[in] S int state
      \return sza int
  */
  inline int calculate_SZA(int Z, int A=0, int S=0) {
    return S*1000000+Z*1000+A;
  }

}
#endif
