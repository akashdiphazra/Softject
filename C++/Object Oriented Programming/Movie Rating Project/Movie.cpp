#include "Movie.h"

#include <iostream>

// Implemention of the construcor
Movie::Movie(std::string name_val, std::string rating_val, int watched_val)
    : name(name_val), rating(rating_val), watched(watched_val) {}

// Implemention of the copy constructor
Movie::Movie(const Movie &source)
    : Movie{source.name, source.rating, source.watched} {}

// Implementation of the destructor
Movie::~Movie() {}

// Implementation of the display method
// should just insert the movie attributes to cout
void Movie::display() const {
  std::cout << name << ", " << rating << ", " << watched << std::endl;
}
