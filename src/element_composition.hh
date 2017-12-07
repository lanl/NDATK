#ifndef ELEMENT_COMPOSITION_HH
#define ELEMENT_COMPOSITION_HH

/**
   \file element_composition.hh

   Expand element names into isotopic compositions.

   \author Mark G. Gray <gray@lanl.gov>
   Copyright Los Alamos National Laboratory 2017.  All Rights Reserved.
*/

#include <map>
#include <string>

#include "Library.hh"
#include "Chart.hh"

namespace ndatk
{
  /** 
      Atom composition of isomer name in Library according to Chart.

      Return map {{sza, 1.0}} if name is nuclide or element in Library, 
             map {{isotope, atom_frac},...} if name is element and 95%
             of its components are in library, else map {{}}.

      \param[in] name Nuclide or element name.
      \return Composition map of isotope: atom fraction.
      \exception std::bad_cast If S, Z, or A not integer.
      \exception std::out_of_range If chemical symbol not in symbol_to_Z.
      \exception std::out_of_range if sza not in Chart.
  */
  std::map<int, double> ndi_atom_comp_of(std::string name, 
                                         const Library &l, const Chart &c);

  /** 
      Mass composition of isomer name in Library according to Chart.

      Return map {{sza, 1.0}} if name is nuclide or element in Library, 
             map {{isotope, mass_frac},...} if name is element and 95% 
             of its components are in Library, else map {{}}.

      \param[in] name Nuclide or element name.
      \return Composition map of isotope: mass fraction.
      \exception std::bad_cast If S, Z, or A not integer.
      \exception std::out_of_range If chemical symbol not in symbol_to_Z.
      \exception std::out_of_range if sza not in Chart.
  */
  std::map<int, double> ndi_mass_comp_of(std::string name, 
                                         const Library &l, const Chart &c);

}
#endif
