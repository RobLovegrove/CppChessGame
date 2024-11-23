#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include "Colour.h"

class King: public ChessPiece {

 private:

 public:
  King(Colour colour) : ChessPiece(colour) {};
  bool try_move(Position current, Position target, ChessPiece* board[8][8]) override;
};

#endif
