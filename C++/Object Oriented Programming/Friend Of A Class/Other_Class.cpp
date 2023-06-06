#include "Other_Class.h"

#include <iostream>

#include "Player.h"

void Other_class::display_player(Player &p) {
  std::cout << "Player Name (Other_class): " << p.name << std::endl;
  std::cout << "Player Health (Other_class): " << p.health << std::endl;
  std::cout << "Player Xp (Other_class): " << p.xp << std::endl;
}
