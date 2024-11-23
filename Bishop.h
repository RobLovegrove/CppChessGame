#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"
#include "Colour.h"

class Bishop: public ChessPiece {

 private:

 public:
  Bishop(Colour colour) : ChessPiece(colour) {};
  bool try_move(Position current, Position target, ChessPiece* board[8][8]) override;
};

#endif
