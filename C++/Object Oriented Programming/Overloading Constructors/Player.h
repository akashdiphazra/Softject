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
  std::string get_name();
  Player(std::string name_val);
  Player(std::string name_val, int health_val, int xp_val);
  void print_info();
  ~Player();
};
#endif
