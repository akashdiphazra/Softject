#ifndef PLAYER_H
#define PLAYER_H

class Player {
 private:
  int num_of_players{};

 public:
  Player(int num_player) { num_of_players = num_player; }
  int total_players() const { return num_of_players; }
};
Player operator+(const Player &p1, const Player &p2);
#endif
