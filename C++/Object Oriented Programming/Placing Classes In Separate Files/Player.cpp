#include "Player.h"

Player operator+(const Player &p1, const Player &p2) {
  return (p1.total_players() + p2.total_players());
}
