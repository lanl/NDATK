#include <iostream>
#include "utils.hh"

using namespace ndatk;

int main(int argc, char**argv) {

  std::string s = " \tHello World! \t ";
  std::cout << ':' << s << ":\n";
  std::cout << ':' << ltrim(s) << ":\n";
  std::cout << ':' << rtrim(s) << ":\n";
  std::cout << starts_with_nocase(s, "HELLO") << "\n";
  std::cout << get_env("USER") << std::endl;
  std::cout << get_cwd() << std::endl;
}
