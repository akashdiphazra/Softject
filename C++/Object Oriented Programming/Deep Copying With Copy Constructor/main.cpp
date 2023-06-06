#include <iostream>
#include <string>
#include <vector>

#include "Deep.h"

void display(Deep s) {
  std::cout << "Value: " << s.get_data_value() << std::endl;
}

int main() {
  Deep obj1(100);
  display(obj1);
  std::cout << std::endl;
  Deep obj2(1000);
  display(obj2);
}
