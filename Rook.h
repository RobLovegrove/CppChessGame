#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"
#include "Colour.h"

class Rook: public ChessPiece {

 private:

 public:
  Rook(Colour colour) : ChessPiece(colour) {};
  bool try_move(Position current, Position target, ChessPiece* board[8][8]) override;
};

#endif
