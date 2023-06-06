#include "Player.h"

#include <iostream>
#include <string>

void Player::set_name(std::string name_val) { name = name_val; }
std::string Player::get_name() { return name; }

Player::Player(std::string name_val) {
  name = name_val;
  health = 100;
  xp = 300;
}

Player::Player(std::string name_val, int health_val, int xp_val) {
  name = name_val;
  health = health_val;
  xp = xp_val;
}

void Player::print_info() {
  std::cout << "Name: " << name << "\nHealth: " << health << "\nXp:" << xp
            << std::endl;
}

Player::~Player() { std::cout << name << " Object Destoryed" << std::endl; }
