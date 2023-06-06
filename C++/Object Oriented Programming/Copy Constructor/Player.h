#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <string>

class Player {
 private:
  std::string name;
  int health;
  int xp;

 public:
  std::string get_name();
  int get_health();
  int get_xp();
  // Three Args Constructor
  Player(std::string name_val = "None", int health_val = 0, int xp_val = 0);
  // Copy constructor
  Player(const Player &source);
  // Destructor
  ~Player();
};
#endif
