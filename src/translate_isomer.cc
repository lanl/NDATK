#include "translate_isomer.hh"
#include "utils.hh"

/* Recursive descent parser for isomer string.

   Translate isomer string to canonical SZA.
*/

namespace ndatk
{
  using namespace std;

  // Vector of chemical symbols indexed by atomic number.
  // See: "IUPAC Nomenclature of Inorganic Chemistry, Recommendations 2005"
  static vector<string> make_Z_to_symbol(void)
  {
    // C string literal concatenation gives C string of space delimited symbols
    // N.B. Each string MUST be space delimited for concatenation to work
    char periodic_table[] =
      " Neutron "
      " H                                                  He " 
      " Li Be                               B  C  N  O  F  Ne "
      " Na Mg                               Al Si P  S  Cl Ar "
      " K  Ca Sc Ti V  Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr "
      " Rb Sr Y  Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I  Xe "
      " Cs Ba La "                
               " Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu "
               " Hf Ta W  Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn "
      " Fr Ra Ac "
               " Th Pa U  Np Pu Am Cm Bk Cf Es Fm Md No Lr "
               " Rf Db Sg Bh Hs Mt Ds Rg Cn Nh Fl Mc Lv Ts Og ";

    vector<string> x;

    // Parse space delimited symbols into vector of strings
    char *p = periodic_table;
    do {                          // loop over symbols in periodic_table
      while (*p == ' ')
        p++;                      // skip over spaces before symbol
      char *s = p;                // start of symbol
      while (*p != ' ' && *p != '\0')
        p++;                      // skip over alphanums in symbol
      x.push_back(string(s, p-s)); // p past end of symbol
    } while (*p != '\0');
    return x;
  }
  const vector<string> Z_to_symbol = make_Z_to_symbol();

  // Map of atomic numbers indexed by chemical symbol
  static map<string, int> make_symbol_to_Z(void)
  {
    map<string, int> x;

    for (vector<string>::size_type i = 0; i < Z_to_symbol.size(); i++)
      x[Z_to_symbol[i]] = i;
    return x;
  }
  const map<string, int> symbol_to_Z = make_symbol_to_Z();

  // C = 'H'|'He'|...|'Og';
  static int translate_C(string s)
  {
    return symbol_to_Z.at(title(s)) * 1000; // may throw std::out_of_range
  }

  // N = [0-9],{0-9};
  static int translate_N(string s)
  {
    return lexical_cast<int, string>(s); // may throw std::bad_cast
  }

  // Nm = N, 'm', N | N;
  static int translate_Nm(string s)
  {
    string::size_type m;
    string::size_type e = s.size();
    string l;                   // substring left of 'm'
    string r;                   // substring right of 'm'
    int im;

    if ((m = s.find('m')) != s.npos) {
      l = s.substr(0, m);
      if (++m < e)
        r = s.substr(m);
      else                      // interpret trailing m as first excited state
        r = "1";
      im = 1000000 * translate_N(r) + translate_N(l);
    } else {
      im = translate_N(s);
    }
    return im;
  }

  // C_Nm = C, '-', Nm | C, Nm
  static int translate_C_Nm(string s)
  {
    string::size_type d;
    string::size_type e = s.size();
    string l;                   // substring left symbol
    string r;                   // substring right remaining characters

    if ((d = s.find('-')) != s.npos) { // Split input at '-'
      l = s.substr(0, d);
      if (++d < e)
        r = s.substr(d);
      else
        r = "0";
    } else {                    // Split input after initial letters
      for (d = 0; d < e && isalpha(s[d]); d++);
      l = s.substr(0, d);
      r = s.substr(d);
    }
    return translate_C(l) + translate_Nm(r);
  }

  // Nm_C = Nm, '-', C | Nm, C;
  static int translate_Nm_C(string s)
  {
    string::size_type e = s.size();
    string::size_type d;
    string l;                   // substring left characters
    string r;                   // substring right symbol

    if ((d = s.find('-')) != s.npos) { // Split input at '-'
      l = s.substr(0, d);
      if (++d < e)
        r = s.substr(d);
      else
        r = "0";
    } else {                    // Split input before final letters
      for (d = 0; d < e && isalpha(s[e-d-1]); d++);
      l = s.substr(0, e-d);
      r = s.substr(e-d);
    }
    return translate_Nm(l) + translate_C(r);
  }

  // Isomer = C | N | C_Nm | Nm_C | Nm
  extern int translate_isomer(string s)
  {
    if (is_all_alphas(s)) {
      return translate_C(s);
    } else if (is_all_digits(s)) {
      int i = translate_N(s);
      if (i < 1000)             // Assume Z
        return i * 1000;
      else
        return i;
    } else if (isalpha(s[0])) {
      return translate_C_Nm(s);
    } else if (isalpha(s[s.size()-1])) {
      return translate_Nm_C(s);
    } else {
      return translate_Nm(s);
    }
  }
}
