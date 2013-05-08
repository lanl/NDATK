#include <iostream>
#include <string>
#include "translate_Isomer.hh"

using namespace std;
using namespace ndatk;

const char *zaids[] = { "1", "h", "H", "1000", "U", "u", "Am", "95",
                        "h1", "1002", "2H", "235-U", "235U",
                        "103000", "1001m0", "am-242m1", "2095240", 
                        "240m1-Am" }; 
const char n = sizeof zaids / sizeof zaids[0];
int main()
{
  for (int i = 0; i < n; i++) {
    string s = zaids[i];
    cout << s << ": ";
    cout << translate_Isomer(s) << endl;
  }
  return 0;
}
