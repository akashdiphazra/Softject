#include <iostream>
#include <string>

#include "Friend_Class.h"
#include "Other_Class.h"
#include "Player.h"

void display_player(Player &p) {
  std::cout << "Player Name (main):" << p.name << std::endl;
  std::cout << "Player health (main): " << p.health << std::endl;
  std::cout << "Plyer xp (main): " << p.xp << std::endl;
}

using namespace std;

int main() {
  Player hero{"Hero", 100, 35};
  display_player(hero);

  std::cout << std::endl;
  Other_class other;
  other.display_player(hero);

  std::cout << std::endl;
  Friend_class friend_class;
  friend_class.set_hero_name(hero, "SUPER HERO");
  friend_class.display_player(hero);

  return 0;
}
