#! /usr/bin/env python
"""Library of Tables

Container for library of table IDs together with a map to ID metadata"""

__author__ = "Mark G. Gray"
__copyright__ = "Copyright 2013"
__credits__ = ["Mark G. Gray"]

__version__ = "1.0"
__maintainer__ = "Mark G. Gray"
__email__ = "gray@lanl.gov"
__status__ = "Development"

import re

            
class Library(object):
    # See MCNP6 Manual, Appendix F, Section II
    (AWR, FILE, ROUTE, TYPE, ADDRESS, TBL_LEN,
     RCD_LEN, EPR, TEMP, PTABLE) = range(10)
    TYPES = (float, str, str, int, int, int,
             int, int, float, str)
    def __init__(self, f):
        """Initialize Library from (e)xsdir records in f"""
        self.l = []             # List of ID in library
        self.d = {}             # Dictionary of ID meta-data
        self.parse(f)

    def parse(self, f):
        """Parse f for the following three sections:

        DATAPATH
        ATOMIC WEIGHT RATIOS
        DIRECTORY
        INCLUDE

        Update Library from DIRECTORY records"""

        date = re.compile(r'\d\d/\d\d/\d\d\d\d')
        state = ""
        for line in f:
            s = line.strip()           # Trim whitespace
            if len(s) > 0:             # Process nonblank nondate lines
                while s.endswith('+'): # Add continuation line
                    s = " ".join((s[:-1], f.next().strip()))
                # Process section keys
                key = s.lower()                # Canonicalize case
                if key.startswith("datapath"): # First section
                    if s.find('=') == -1:      # Optional '=' missing
                        fields = s.split()
                        self.datapath(fields[1])
                    else:
                        fields = s.spit('=')
                        self.datapath(fields[1].strip())
                elif key == "atomic weight ratios": # Second section
                    state = "awr"
                elif date.match(key):
                    self.date = key
                elif key == "directory": # Third section
                    state = "dir"
                elif key.startswith("include"): # Parse include file
                    fields = s.split()
                    f1 = open(fields[1])
                    self.parse(f1)
                    f1.close()
            # Process section data
                elif state == "awr":
                    pass            # Ignore awr records
                elif state == "dir":
                    fields = s.split()
                    zaid = fields[0]
                    self.l.append(zaid)
                    self.d[zaid] = tuple([t(v) for t, v in
                                          zip(Library.TYPES, fields[1:])])

    def make_library(self, pred):
        """Create a library object based on pred"""
        r = Library([])
        r.l = [z for z in self.l if pred(self, z)] # Filter zaids on pred
        r.d = self.d            # Reference Dictionary of ID meta-data
        return r

            
if __name__ == "__main__":
    import sys

    # Some test data from xsdir.lanl2006
    xsdir_dir = [
        "DIRECTORY",
        "1001.62c  0.999170 actia 0 1 1 10128 0 0 2.5301E-08",
        "1002.66c  1.996800 endf66a 0 1 2545 10270 0 0 2.5301E-08",
        "1003.69c  2.989596 t16_2003 0 1 1 11206 0 0 2.5301E-08",
        "2003.66c  2.989032 endf66a 0 1 6583 9679 0 0 2.5301E-08",
        "2004.62c  3.968219 actia 0 1 2545 5524 0 0 2.5301E-08"]

    d = Library(xsdir_dir)

    for zaid in d.l:
        print zaid, d.d[zaid][Library.AWR], d.d[zaid][Library.FILE], d.d[zaid][Library.TEMP]

    if len(sys.argv) == 2: 
        f = open(sys.argv[1])
        d2 = Library(f)

        print d2.date

        def pred(l, zaid):
            """Example predicate for library creation"""
            return l.d[zaid][Library.FILE].split('/')[0] == 'endf71x'

        endf71x = d2.make_library(pred)

        for za in endf71x.l:
            print za, endf71x.d[za][Library.FILE]
