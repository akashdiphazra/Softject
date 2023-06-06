#include "Move.h"

#include <iostream>
#include <string>

void Move::set_data_value(int d) { *data = d; }
int Move::get_data_value() { return *data; }

Move::Move(int d) {
  data = new int;
  *data = d;
  std::cout << "Constructor For: " << d << std::endl;
}

// Copy Constructor
Move::Move(const Move &source) : Move{*source.data} {
  std::cout << "Copy Constructor  - Deep Copy For: " << *data << std::endl;
}

// Move Constructor
Move::Move(Move &&source) noexcept : data{source.data} {
  source.data = nullptr;
  std::cout << "Move Constructor - Moving Resource: " << *data << std::endl;
}

Move::~Move() {
  if (data != nullptr) {
    std::cout << "Destructor Freeing Data For: " << *data << std::endl;
  } else {
    std::cout << "Destructor Freeing Data For Nullptr" << std::endl;
  }
  delete data;
}
