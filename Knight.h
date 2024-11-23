#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"
#include "Colour.h"

class Knight: public ChessPiece {

 private:

 public:
  Knight(Colour colour) : ChessPiece(colour) {};
  bool try_move(Position current, Position target, ChessPiece* board[8][8]) override;
};

#endif
