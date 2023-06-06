#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

void print_info(Player p) {
  std::cout << "Name: " << p.get_name() << "\nHealth: " << p.get_health()
            << "\nXp:" << p.get_xp() << std::endl;
}

int main() {
  Player empty;
  print_info(empty);
  std::cout << std::endl;

  Player frank("frank", 100);
  print_info(frank);

  std::cout << std::endl;
  Player villain("villian", 200, 350);
  print_info(villain);
  return 0;
}
