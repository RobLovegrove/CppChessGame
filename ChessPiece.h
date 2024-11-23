#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "Colour.h"
#include "Position.h"
#include <iostream>

class ChessPiece {

protected:
  Colour colour;
  ChessPiece(Colour colour) : colour(colour) {};

public:
  Colour get_colour() { return colour; }
  virtual bool try_move(Position current, Position target, ChessPiece* board[8][8]) = 0;
};

#endif
