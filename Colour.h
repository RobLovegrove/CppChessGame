#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>

enum class Colour { WHITE, BLACK };

std::ostream& operator << (std::ostream& os, Colour colour);

#endif
