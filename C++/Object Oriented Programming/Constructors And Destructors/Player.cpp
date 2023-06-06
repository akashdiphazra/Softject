#include "Player.h"

#include <iostream>
#include <string>

void Player::set_name(std::string name_val) { name = name_val; }

Player::Player() { std::cout << "No Args Constructor Called. " << std::endl; }

Player::Player(std::string name) {
  std::cout << "One Args Constructor Called. \nPlayer Name: " << name
            << std::endl;
}

Player::Player(std::string name, int health, int xp) {
  std::cout << "Three Args Construtor Called" << std::endl;
  std::cout << "Name: " << name << " Health: " << health << " Xp: " << xp
            << std::endl;
}

Player::~Player() {
  std::cout << "Destructors " << name << " Called." << std::endl;
}
