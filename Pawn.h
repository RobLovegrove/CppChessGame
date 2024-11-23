#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"
#include "Colour.h"
#include "Position.h"

class Pawn: public ChessPiece {

 private:
  bool pawn_not_capturing(Position c, Position t, ChessPiece* b[8][8], int one, int two, int starting_rank );
  
 public:
  Pawn(Colour colour) : ChessPiece(colour) {};
  bool try_move(Position current, Position target, ChessPiece* board[8][8]) override;
  
};

#endif
