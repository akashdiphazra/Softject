#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

int main() {
  {
    Player slayer;
    slayer.set_name("Slayer");
  }
  {
    Player frank;
    frank.set_name("Frank");
    Player hero("Hero");
    hero.set_name("Hero");
    Player villain("Villain", 100, 12);
    villain.set_name("Villain");
  }
  Player *enemy = new Player;
  enemy->set_name("Enemy");
  Player *level_boss = new Player("Level Boss", 1000, 300);
  level_boss->set_name("Level Boss");
  delete enemy;
  delete level_boss;
  return 0;
}
