#include <iostream>

#include "Colour.h"

std::ostream& operator << (std::ostream& os, Colour colour) {
  
  if (colour == Colour::WHITE) {
    os  << "White";
  }
  else {
    os << "Black";
  }
  return os;
}
