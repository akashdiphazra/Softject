#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

int main() {
  Player empty;
  Player frank("frank");
  frank.print_info();

  std::cout << std::endl;
  Player hero("hero", 100);
  hero.print_info();

  std::cout << std::endl;
  Player villain("villian", 200, 300);
  villain.print_info();
  return 0;
}
