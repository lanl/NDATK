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
      Chemical symbols (std::string) indexed by atomic number (int) in
      std::vector.
  */
  extern const std::vector<std::string> Z_to_symbol;

  /** 
      Atomic number (int) indexed by chemical symbol (std::string) in
      std::map.
  */
  extern const std::map<std::string, int> symbol_to_Z;

  /**
     Translate isomer name to canonial SZA.

     This routine will translate lowercase (e.g. he) and uppercase (e.g. HE)
     chemical symbols in support of legacy input to the IUPAC correct title 
     case (e.g. He) for elements.  Because of this it cannot translate 
     subatomics name like n for neutron (ambiguous with Nitrogen) nor 
     atomic nicknames like p for proton (ambiguous with Phosphorus).

     \param[in] isomer Isomer name to translate.
     \return Canonical SZA of isomer name.
     \exception std::bad_cast If S, Z, or A not integer.
     \exception std::out_of_range If chemical symbol not in symbol_to_Z.

     ISO/IEC 14977 EBNF of recognized input strings:
     \code
     Isomer = C                   (* Chemical symbol *)
            | N                   (* Z | ZA | SZA *)
            | C_Nm                (* C[-]A[mS] *) 
            | Nm_C                (* A[mS][-]C *)
            | Nm;                 (* ZA[mS] *)
     C      = 'H'|'He'|...|'Og';  (* symbol_to_Z's keys *)
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
     
     \param[in] sza Canonical SZA to extract state number from.
     \return The state number of canonical SZA.
  */
  inline int extract_S(int sza) { return sza/1000000; }

  /**
     Extract Z from canonical SZA.

     \param[in] sza Canonical SZA to extract atomic number from.
     \return The atomic number of canonical SZA.
  */
  inline int extract_Z(int sza) { return (sza%1000000)/1000; }

  /** 
      Extract A from canonical SZA.

      \param[in] sza Canonical SZA to extract mass number from.
      \return The mass number of canonical SZA.
  */
  inline int extract_A(int sza) { return sza%1000; }

  /**
     Calculate ground state of canonical SZA.

     \param[in] sza Canonical SZA to extract ground state from.
     \return ZA The ground state of canonical SZA.
  */
  inline int ground_state(int sza) { return sza%1000000; }

  /** 
      Calculate canonical SZA from state, atomic, mass numbers.
      
      \param[in] Z The atomic number of nuclide.
      \param[in] A The mass number of nuclide.
      \param[in] S The state number of nuclide.
      \return The canonical SZA of nuclide.
  */
  inline int calculate_SZA(int Z, int A=0, int S=0) {
    return S*1000000+Z*1000+A;
  }

  /**
     Return true if canonical sza is element.

     N.B. Excited state makes no sense for element.

     \param[in] sza The canonical SZA to be tested.
     \return Value true if canonical SZA is element else false.
  */
  inline bool is_element(int sza) { 
    return extract_S(sza) == 0 && extract_A(sza) == 0;
  }
}
#endif
