#include <iostream>

#include "Player.h"
using namespace std;

int main() {
  Player p1(113);
  Player p2(343);
  Player p3{p1 + p2};
  cout << p3.total_players() << endl;
  return 0;
}
