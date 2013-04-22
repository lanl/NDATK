#! /usr/bin/env python
"""Chart of the Nuclides"""

__author__ = "Mark G. Gray"
__copyright__ = "Copyright 2013"
__credits__ = ["Mark G. Gray"]

__version__ = "1.0"
__maintainer__ = "Mark G. Gray"
__email__ = "gray@lanl.gov"
__status__ = "Development"

class NuclidesChart(object):
    """Chart of the Nuclides"""
    def __init__(self, f):
        """Parse f for peroidic table and chart of the nuclides"""
        self.elements = []
        self.nuclides = {}
        state = ""
        for line in f:
            s = line.strip()    # Trim whitespace
            if len(s) > 0 and not s.startswith('#'):
                if s.startswith("[PERIODIC TABLE]"):
                    state = "pt"
                elif s.startswith("[CHART OF THE NUCLIDES]"):
                    state = "cn"
                elif state == "pt":
                    sf = s.split()
                    self.elements.append((sf[1], float(sf[2]), sf[3]))
                elif state == "cn":
                    sf = s.split()
                    self.nuclides[int(sf[0])] = (float(sf[1]), float(sf[2]),
                                                 float(sf[3]))

    def get_string_val_n(self, key, n):
        """return string value by key and index"""
        if key == "SYMBOL":
            return self.elements[n][0]
        elif key == "NAME":
            return self.elements[n][2]
        else:
            raise KeyError, "%s invalid key!" % key

    def get_float_val_n(self, key, n):
        """return float value by key and index"""
        if key == "AT_WGT":
            if n < len(self.elements):
                return self.elements[n][1]
            else:
                return self.nuclides[n][0] * self.elements[0][1]
        elif key == "AWR":
            if n < len(self.elements):
                return self.elements[n][1] / self.elements[0][1]
            else:
                return self.nuclides[n][0]
        elif key == "ABUNDANCE":
            return self.nuclides[n][1]
        elif key == "HALF_LIFE":
            return self.nuclides[n][2]
        else:
            raise KeyError, "%s invalid key!" % key

        
if __name__ == "__main__":
    import sys
    a = NuclidesChart(open(sys.argv[1]))

    for i in range(10):
        print i, a.get_string_val_n("SYMBOL", i), a.get_float_val_n("AWR", i)

        
    print a.get_float_val_n("AT_WGT", 1001)
    print a.get_float_val_n("ABUNDANCE", 17035)
    print a.get_float_val_n("HALF_LIFE", 92235)
