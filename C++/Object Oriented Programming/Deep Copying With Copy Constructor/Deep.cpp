#include "Deep.h"

#include <iostream>
#include <string>

void Deep::set_data_value(int d) { *data = d; }
int Deep::get_data_value() { return *data; }
Deep::Deep(int d) {
  data = new int;
  *data = d;
}

// Deep Copy Constructor
Deep::Deep(const Deep &source) : Deep(*source.data) {
  std::cout << "Copy Constructor - Deep Copy." << std::endl;
}

Deep::~Deep() {
  delete data;
  std::cout << "Destructor Releasing Data. " << std::endl;
}
