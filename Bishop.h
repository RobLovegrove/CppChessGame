#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"
#include "Colour.h"

class Bishop: virtual public ChessPiece {

 protected:
  bool try_bishop_moves(
    Position start, Position end, ChessPiece* board[8][8]);
  Bishop() {}

 public:
  Bishop(Colour colour) : ChessPiece(colour) {};
  
  Type get_type() const override { return Type::BISHOP; }
  bool try_move(
    Position start, Position end, ChessPiece* board[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
