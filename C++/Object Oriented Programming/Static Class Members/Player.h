#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <string>

class Player {
 private:
  static int num_players;  // Only accessible within this class
  std::string name;
  int health;
  int xp;

 public:
  std::string get_name();
  int get_health();
  int get_xp();
  // Default Constructor
  Player(std::string name_val = "None", int health_val = 0, int xp_val = 0);
  // Copy Constructor
  Player(const Player &source);
  // Destructor
  ~Player();
  // Static Function has only access to statics variables
  static int get_num_player();
};
#endif
