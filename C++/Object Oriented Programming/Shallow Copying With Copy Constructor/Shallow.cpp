#include "Shallow.h"

#include <iostream>
#include <string>

void Shallow::set_data_value(int d) { *data = d; }
int Shallow::get_data_value() { return *data; }

Shallow::Shallow(int d) {
  data = new int;
  *data = d;
}

// Shallow Copy Constructor
Shallow::Shallow(const Shallow &source) : data(source.data) {
  std::cout << "Copy Constructor - Shallow Copy." << std::endl;
}

Shallow::~Shallow() {
  delete data;
  std::cout << "Destructor Releasing Data. " << std::endl;
}
