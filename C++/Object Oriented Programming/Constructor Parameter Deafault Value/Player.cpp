#include "Player.h"

#include <iostream>
#include <string>

// Delegating Constructor
Player::Player(std::string name_val, int health_val, int xp_val)
    : name{name_val}, health{health_val}, xp{xp_val} {
  std::cout << "Three Args Constructor" << std::endl;
}

void Player::print_info() {
  std::cout << "Name: " << name << "\nHealth: " << health << "\nXp:" << xp
            << std::endl;
}
