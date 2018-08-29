#ifndef NDATK_HH
#define NDATK_HH
/**
   \file ndatk.hh

   Convenience include file for ndatk library.

   \author Mark G. Gray <gray@lanl.gov>
   Copyright Los Alamos National Laboratory 2013.  All Rights Reserved.
*/

/**
   \mainpage Nuclear Data Access Tool Kit

   \section intro Introduction 

   The Nuclear Data Access Tool Kit (ndatk) provides an application
   programming interface (API) to nuclear constants and index to
   continuous energy nuclear data table meta-data.  Basic physical
   constants are defined in constants.hh, while element and isotope
   scalar data is available from curated data files through the
   ndatk::Chart class.  The ndatk::Exsdir class provides a traditional
   state, atomic, and mass number identifier (SZAID) index to nuclear
   data cross section table meta-data; the ndatk::Library class groups
   subsets of available SZAIDs by release vintage and correspondence
   to multigroup libraries.

   \section back Background

   In fiscal year 2012 users of the Monte Carlo Applications Tool Kit
   (MCATK) recognized a need to compare multigroup and continuous
   energy neutron transport calculations.  Since the inception of the
   Nuclear Data Interface (NDI), multigroup neutron transport tables
   have been released as libraries with tables identified by library
   name and target state, atomic, and mass numbers (SZA), while
   historically continuous energy neutron transport data has been
   released as individual nuclide tables identified by target state,
   atomic and mass number identifiers (SZAIDs), making cross
   comparison calculations difficult.

   Consequently Terry Adams's "FY13 Multi-Temp ToolKit Proposed
   Efforts" identified a need to: "... create a stand-alone
   routine/library that will return a continuous energy ZAID (sic)
   when given a multigroup ZAID.  This converter may also handle
   conversions from atomic to isotopic ZAIDs."

   On December 10, 2012 various MCATK stakeholders met to discuss
   requirements for this stand alone routine/library.  They decided it must:

   - Support curated data managed by the Nuclear Data Team.\n
   The data files which define the translations must be created,
   tested, managed, and documented in accordance with the standards
   the Nuclear Data Team uses for production nuclear data files.  The
   code library must support this curation.
   - Provide continuous energy data libraries analogous to multigroup
   data libraries.\n
   The code library should translate the multigroup table specification by
   data library name and target state, atomic, and mass numbers (SZA) into
   their corresponding continuous energy SZAID.
   - Translate between continuous energy and multigroup SZAIDs.
   The code library should translate continuous energy SZAIDs to
   multigroup SZAIDs, and vice versa, mapping equivalent continuous
   energy tables to multigroup tables.
   - Provide a polyvalent-program pattern including:
     - An object-oriented C++ library API.
     - A flat C/FORTRAN library API.
     - A command line program interface.
     - A scripting interpreter interface.\n
   - Provide NDI SZA translation features.\n
   The code library should accept SZA specification as a canonical
   integer or chemical symbol, mass number, and possibly state, in at least 
   the formats supported by NDI.
   - Provide NDI multi-temperature features.\n
   The code library should accept library name, SZA, and temperature
   as a specification of a continuous energy SZAID in the same format
   supported by NDI.

   On January 23, 2013 the Nuclear Data Team's program, project and
   line management met with the team and authorized the design,
   implementation, and delivery of the Nuclear Data Access Took Kit
   (ndatk).

   This document describes the C++ library API of ndatk.
*/

// Level 4
#include "element_composition.hh"

// Level 3
#include "Chart.hh"
#include "Library.hh"

// Level 2
#include "Exsdir.hh"
#include "translate_isomer.hh"

// Level 1
#include "CuratedData.hh"
#include "Finder.hh"
#include "constants.hh"
#include "utils.hh"
#include "FileStat.hh"

#endif
