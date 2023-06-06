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
  std::string get_name() const;
  Player();
  Player(std::string name_val);
  Player(std::string name_val, int health_val, int xp_val);
};
#endif
