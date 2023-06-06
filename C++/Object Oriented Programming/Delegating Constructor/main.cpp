#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

int main() {
  Player empty;
  Player frank("frank");
  frank.print_info();
  std::cout << std::endl;
  Player villain("villian");
  villain.print_info();
  return 0;
}
