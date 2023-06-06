#ifndef _SHALLOW_H_
#define _SHALLOW_H_
#include <iostream>
#include <string>

class Shallow {
 private:
  int *data;

 public:
  void set_data_value(int d);
  int get_data_value();
  Shallow(int d);
  Shallow(const Shallow &source);
  ~Shallow();
};
#endif
