#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

void display_active_players() {
  std::cout << "Active Players: " << Player::get_num_player() << std::endl;
}

int main() {
  display_active_players();
  Player hero{"Hero"};
  display_active_players();
  {
    Player frank("Frank");
    display_active_players();
  }
  display_active_players();
  Player *player = new Player("Enemy", 250, 500);
  display_active_players();
  delete player;
  display_active_players();
  return 0;
}
