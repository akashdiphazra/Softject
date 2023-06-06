#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

int main() {
  Player frank("frank");
  frank.print_info();

  Player *new_player = new Player("Gabbar", 400, 500);
  std::cout << std::endl;
  new_player->print_info();
  delete new_player;
  return 0;
}
