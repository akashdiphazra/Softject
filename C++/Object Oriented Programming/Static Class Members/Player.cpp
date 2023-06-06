#include "Player.h"

#include <iostream>
#include <string>

int Player::num_players{0};

std::string Player::get_name() { return name; }
int Player::get_health() { return health; }
int Player::get_xp() { return xp; }

Player::Player(std::string name_val, int health_val, int xp_val)
    : name{name_val}, health{health_val}, xp{xp_val} {
  ++num_players;
}

Player::Player(const Player &source)
    : Player(source.name, source.health, source.xp) {}

int Player::get_num_player() { return num_players; }

Player::~Player() { --num_players; }
