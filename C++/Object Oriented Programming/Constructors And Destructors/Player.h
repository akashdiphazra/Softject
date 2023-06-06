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
  void set_name(std::string name_val);
  Player();
  Player(std::string name);
  Player(std::string name, int health, int xp);
  ~Player();
};
#endif
