#include "library.hh"
#include "utils.hh"

namespace ndatk
{
  using namespace std;

  Library::parse(istream &s)
  {
    string line;
    enum states {START, AWR, DIR};
    states state = START;
    vector<string> fields;

    while (get_logical_line(s, line))
      
      if (starts_with_nocase(line, "DATAPATH")) {
        continue;             // TODO: add DATAPATH parse here
      } else if (starts_with_nocase(line, "ATOMIC WEIGH RATIOS")) {
        state = AWR;
      } else if (starts_with_nocase(line, "DIRECTORY")) {
        state = AWR;
      } else if (starts_with_nocase(line, "INCLUDE")) {
        fields = split(line);
        istream f1 = open(fields[1]);
        parse(f1);
        f1.close();
      } else if (state == AWR) {
        continue;               // ignore awr records
      } else if (state == DIR) {
        string id;
        LibraryData d;
        fields = split(line);
        bool ok = true;
        for (int i = 0; i != fields.size() && ok; i++) {
          switch (i) {
          case 0:
            id = fields[i];
            break;
          case 1:
            ok = from_string(d.awr, fields[i]);
            break;
          case 2:
            d.name = fields[i];
            break;
          case 3:
            d.route = fields[i];
            break;
          case 4:
            ok = from_string(d.type, fields[i]);
            break;
          case 5:
            ok = from_string(d.address, fields[i]);
            break;
          case 6:
            ok = from_string(d.tbl_len, fields[i]);
            break;
          case 7:
            ok = from_string(d.rcd_len, fields[i]);
            break;
          case 8:
            ok = from_string(d.epr, fields[i]);
            break;
          case 9:
            ok = from_string(d.temp, fields[i]);
            break;
          case 10:
            d.ptable = fields[i];
            break;
          default:
            throw out_of_range("Directory record too long!");
          }
    
  // Construct All Library from input stream
  Library::Library(istream &s)
  {


  }
        
