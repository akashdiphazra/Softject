#include "Friend_Class.h"

#include <iostream>

class Player;
void Friend_class::set_hero_name(Player &p, std::string name) { p.name = name; }

void Friend_class::display_player(Player &p) {
  std::cout << "Player Name (Friend Class): " << p.name << std::endl;
  std::cout << "Player Health (Friend Class): " << p.health << std::endl;
  std::cout << "Player Xp (Friend Class): " << p.xp << std::endl;
}
