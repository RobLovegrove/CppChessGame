#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include "Colour.h"

class King: public ChessPiece {

 private:
  bool handle_castling(
    int delta_file, ChessPiece* b[8][8], int rank, uint8_t* castling);

 public:
  King(Colour colour) : ChessPiece(colour) {};

  Type get_type() const override { return Type::KING; }
  bool try_move(
    Position current, Position target, ChessPiece* board[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
