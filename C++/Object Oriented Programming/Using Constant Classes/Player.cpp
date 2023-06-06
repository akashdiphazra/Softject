#include "Player.h"

#include <iostream>
#include <string>

std::string Player::get_name() const { return name; }

Player::Player() : Player{"None", 100, 300} {}

Player::Player(std::string name_val) : Player{name_val, 0, 0} {}

// Delegating Constructor
Player::Player(std::string name_val, int health_val, int xp_val)
    : name{name_val}, health{health_val}, xp{xp_val} {}
