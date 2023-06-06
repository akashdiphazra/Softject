#include "Player.h"

#include <iostream>
#include <string>

std::string Player::get_name() { return name; }
int Player::get_health() { return health; }
int Player::get_xp() { return xp; }

Player::Player(std::string name_val, int health_val, int xp_val)
    : name{name_val}, health{health_val}, xp{xp_val} {
  std::cout << "Three Args Constructor" << std::endl;
}

// Copy Constructor Implementaion Using Player Class
Player::Player(const Player &source)
    // : name(source.name), health(source.health), xp{source.xp}
    : Player(source.name, source.health, source.xp) {  // Using Delegating Constructor
  std::cout << "Copy Constructor Made A Copy Of " << source.name << std::endl;
}

Player::~Player() { std::cout << name << " Destructor Called. " << std::endl; }
