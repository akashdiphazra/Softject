#include <iostream>
#include <string>
#include <vector>

#include "Shallow.h"

void display(Shallow s) { std::cout << s.get_data_value() << std::endl; }

int main() {
  Shallow obj1(100);
  display(obj1);
  std::cout << std::endl;
  Shallow obj2(1000);
  display(obj2);
}
