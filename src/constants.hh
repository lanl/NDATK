#ifndef CONSTANTS_HH
#define CONSTANTS_HH

/**
   \file constants.hh

   Fundamental General Physical Constants.

   A subset of Fundamental General Physical Constants in units
   appropriate for ndatk:
   - Length: centimeter (1/100 m)
   - Mass: atomic mass unit ((1e-3 kg/mol)/avogadro_constant) 
   - Time: shake (1e-8 s)
   - Energy: million electron volts (1e+6 elementary_charge V)
   - Temperature: million electron volts (1e+6 elementary_charge V)

   The constants are taken from the back page of "Nuclides and
   Isotopes", 16ed, which is based on P. J. Molar and B. N. Taylor's
   "CODATA Recommended Values of the Fundamental Physical Constants:
   1998", Rev. Mod. Phys. \b 72 (2000).

   \author Mark G. Gray <gray@lanl.gov>
   Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.
*/

namespace ndatk
{
  /// Atomic mass unit (MeV)
  const double atomic_mass_unit = 9.31494013e+2;
  /// Avogadro constant (1/mol)
  const double avogadro_constant = 6.02214199e+23;
  /// Boltzmann constant (MeV/K)
  const double boltzmann_constant = 8.617342e-11;
  /// Electron rest mass (u)
  const double electron_mass = 5.485799110e-4;
  /// Elementary charge (C)
  const double elementary_charge = 1.602176462e-19;
  /// Neutron rest mass (u)
  const double neutron_mass = 1.00866491578;
  /// Plank constant (MeV sh)
  const double plank_constant = 4.13566727e-29;
  /// Proton rest mass (u)
  const double proton_mass  = 1.00727646688;
  /// Speed of light (cm/sh)
  const double speed_of_light = 2.99792458e+2;
}

#endif
