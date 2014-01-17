#include <iostream>
#include <fstream>
#include <string>
#include "ndatk.hh"

using namespace std;

const char *zaids[] = { "1001", "1002", "3H", 
                        "235-U", "238U",
                        "242m1-Am", "Am242"  }; 
const char n = sizeof zaids / sizeof zaids[0];

int main(int argc, char *argv[])
{
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " Exsdir_filename library" << std::endl;
    exit(1);
  }

  cout << "Use Case 2:" << endl;
  cout << "Create Exsdir from filename on command line;" << endl;
  cout << "create Library from name and Exsdir;" << endl;
  cout << "retrieve file name and line number by isomer name." << endl;
  cout << "For each isomer temperature retrieve table name." 
       << endl << endl;

  ndatk::Exsdir x(argv[1]);     // parse filename
  cout << "Created Exsdir " << x.name()
       << " with " << x.number_of_tables() << " tables." << endl;

  ndatk::Library l(argv[2], x);
  cout << "Created Library " << l.name()
       << " with " << l.number_of_tables() << " tables." << endl;

  for (int i = 0; i < n; i++) {
    string s(zaids[i]);
    cout << s;
    string szaid = l.table_identifier(s);
    if (szaid == "") 
      cout << "Couldn't find " << s << " in Library!" << endl;
    else {
      cout << "(" << szaid <<"): " 
           << l.file_name() << "@" << l.address() << endl;
      vector<double> t = l.temperatures();
      cout << szaid << " has " << l.number_of_temperatures() 
           << " tables in " << l.name() << ":" << endl;
      for (int i = 0; i < l.number_of_temperatures(); i++) {
        double x = l.temperature(t[i]);
        cout << "T = " << x << " => SZAID = " << l.table_identifier() << endl;
      }
    }
  }
}
