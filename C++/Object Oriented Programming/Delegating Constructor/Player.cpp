#include "Player.h"

#include <iostream>
#include <string>

Player::Player() : Player{"None", 100, 300} {
  std::cout << "No Args Constructor" << std::endl;
}

Player::Player(std::string name_val) : Player{name_val, 0, 0} {
  std::cout << "one Args Constructor" << std::endl;
}

// Delegating Constructor
Player::Player(std::string name_val, int health_val, int xp_val)
    : name{name_val}, health{health_val}, xp{xp_val} {
  std::cout << "Three Args Constructor" << std::endl;
}

void Player::print_info() {
  std::cout << "Name: " << name << "\nHealth: " << health << "\nXp:" << xp
            << std::endl;
}
