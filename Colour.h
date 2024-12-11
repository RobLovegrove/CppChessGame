#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>

enum class Colour { WHITE, BLACK };

/*
Method: Colour output operator overloading
Outputs a Colour to ostream&:
    If WHITE outputs White
    else outputs Black
*/
std::ostream& operator << (std::ostream& os, Colour colour);

#endif
