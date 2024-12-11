#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"
#include "Colour.h"
#include "Position.h"

class Pawn: public ChessPiece {

 private:
  bool handle_not_capturing(
    Position start, Position end, ChessPiece* b[8][8], int one, 
    int two, int starting_rank);
    
  bool handle_capturing(
    Position start, Position end, ChessPiece* b[8][8], int one);

 public:
  Pawn(Colour colour) : ChessPiece(colour) {};

  Type get_type() const override { return Type::PAWN; }
  bool try_move(
    Position start, Position end, ChessPiece* b[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
