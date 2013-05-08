#include "translate_Isomer.hh"
#include "utils.hh"

/* Recursive descent parser for isomer string.

   Translate isomer string to canonical SZA.
*/

namespace ndatk
{
  using namespace std;

  /* Vector of chemical symbols indexed by atomic number.
 
     Since C++98 does not have useful initialization semantics 
     for const static containers, must create a factory function
     for initialization.
  */
  static const vector<string> make_Z_to_symbol(void)
  {
    vector<string> x;

    x.push_back("");           // Should this be "n" or "g"?
    x.push_back("H");
    x.push_back("He");
    x.push_back("Li");
    x.push_back("Be");
    x.push_back("B");
    x.push_back("C");
    x.push_back("N");
    x.push_back("O");
    x.push_back("F");
    x.push_back("Ne");
    x.push_back("Na");
    x.push_back("Mg");
    x.push_back("Al");
    x.push_back("Si");
    x.push_back("P");
    x.push_back("S");
    x.push_back("Cl");
    x.push_back("Ar");
    x.push_back("K");
    x.push_back("Ca");
    x.push_back("Sc");
    x.push_back("Ti");
    x.push_back("V");
    x.push_back("Cr");
    x.push_back("Mn");
    x.push_back("Fe");
    x.push_back("Co");
    x.push_back("Ni");
    x.push_back("Cu");
    x.push_back("Zn");
    x.push_back("Ga");
    x.push_back("Ge");
    x.push_back("As");
    x.push_back("Se");
    x.push_back("Br");
    x.push_back("Kr");
    x.push_back("Rb");
    x.push_back("Sr");
    x.push_back("Y");
    x.push_back("Zr");
    x.push_back("Nb");
    x.push_back("Mo");
    x.push_back("Tc");
    x.push_back("Ru");
    x.push_back("Rh");
    x.push_back("Pd");
    x.push_back("Ag");
    x.push_back("Cd");
    x.push_back("In");
    x.push_back("Sn");
    x.push_back("Sb");
    x.push_back("Te");
    x.push_back("I");
    x.push_back("Xe");
    x.push_back("Cs");
    x.push_back("Ba");
    x.push_back("La");
    x.push_back("Ce");
    x.push_back("Pr");
    x.push_back("Nd");
    x.push_back("Pm");
    x.push_back("Sm");
    x.push_back("Eu");
    x.push_back("Gd");
    x.push_back("Tb");
    x.push_back("Dy");
    x.push_back("Ho");
    x.push_back("Er");
    x.push_back("Tm");
    x.push_back("Yb");
    x.push_back("Lu");
    x.push_back("Hf");
    x.push_back("Ta");
    x.push_back("W");
    x.push_back("Re");
    x.push_back("Os");
    x.push_back("Ir");
    x.push_back("Pt");
    x.push_back("Au");
    x.push_back("Hg");
    x.push_back("Tl");
    x.push_back("Pb");
    x.push_back("Bi");
    x.push_back("Po");
    x.push_back("At");
    x.push_back("Rn");
    x.push_back("Fr");
    x.push_back("Ra");
    x.push_back("Ac");
    x.push_back("Th");
    x.push_back("Pa");
    x.push_back("U");
    x.push_back("Np");
    x.push_back("Pu");
    x.push_back("Am");
    x.push_back("Cm");
    x.push_back("Bk");
    x.push_back("Cf");
    x.push_back("Es");
    x.push_back("Fm");
    x.push_back("Md");
    x.push_back("No");
    x.push_back("Lr");
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

  // C = 'H'|'He'|...|'Lr';
  static int translate_C(string s)
  {
    return map_at(symbol_to_Z, title(s)) * 1000; 
  }

  // N = [0-9],{0-9};
  static int translate_N(string s)
  {
    int i;
    if (!from_string(i, s))
      throw invalid_argument("Cannot convert string to int!");
    return i;
  }

  // Nm = N, 'm', N | N;
  static int translate_Nm(string s)
  {
    string::size_type m;
    string::size_type e = s.size();
    string l;
    string r;
    int im;

    if ((m = s.find('m')) != s.npos) {
      l = s.substr(0, m);
      if (++m < e)
        r = s.substr(m);
      else
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
    string l;
    string r;

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
    string l;
    string r;

    if ((d = s.find('-')) != s.npos) { // Split input at '-'
      l = s.substr(0, d);
      if (++d < e)
        r = s.substr(d);
      else
        r = "0";
    } else {                    // Split input before final letters
      for (d = e-1; 0 < d && isalpha(s[d]); d--);
      l = s.substr(0, d+1);
      r = s.substr(d+1);
    }
    return translate_Nm(l) + translate_C(r);
  }

  // Isomer = C | N | C_Nm | Nm_C | Nm
  extern int translate_Isomer(string s)
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
