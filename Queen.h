#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Colour.h"

class Queen: public Rook, public Bishop {

 private:

 public:
  Queen(Colour colour) : ChessPiece(colour) {};

  Type get_type() const override { return Type::QUEEN; }
  bool try_move(
    Position current, Position target, ChessPiece* board[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
