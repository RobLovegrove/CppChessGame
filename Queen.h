#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Colour.h"

class Queen: public ChessPiece {

 private:

 public:
  Queen(Colour colour) : ChessPiece(colour) {};
  bool try_move(Position current, Position target, ChessPiece* board[8][8]) override;
};

#endif
