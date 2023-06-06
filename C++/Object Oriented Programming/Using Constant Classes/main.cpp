#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

int main() {
  const Player villain{"Villain", 100, 55};
  std::cout << villain.get_name() << std::endl;
  Player hero{"Hero", 100, 15};
  std::cout << hero.get_name() << std::endl;
  Player *spiderman = new Player{"Spiderman", 200, 10};
  std::cout << spiderman->get_name() << std::endl;
  delete spiderman;
  return 0;
}
