#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main(int argc, char** argv) {
  std::string a("SATOR AREPO TENET OPERA ROTAS");
  a.erase(std::remove(std::begin(a), std::end(a), ' '), std::end(a));

  std::string b;
  std::copy(std::crbegin(a), std::crend(a), std::back_inserter(b));

  std::cout << std::boolalpha << (a == b) << '\n';
  return 0;
}
