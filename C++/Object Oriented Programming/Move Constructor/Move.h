#ifndef _MOVE_H_
#define _MOVE_H_
#include <iostream>
#include <string>

class Move {
 private:
  int *data;

 public:
  void set_data_value(int d);
  int get_data_value();
  // Constructor
  Move(int d);
  // Copy Constructor
  Move(const Move &source);
  // Move Constructor
  Move(Move &&source) noexcept;
  // Destructor
  ~Move();
};
#endif
