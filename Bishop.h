#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"
#include "Colour.h"

class Bishop: public ChessPiece {

 public:
   /*
    Method: Bishop constructor
    Constructs an instance of the Bishop Class
    Passes a Colour class into the parent class ChessPiece's constructor 

    Params: 
      colour: Enum Class Colour, can be WHITE or BLACK
  */
  Bishop(Colour colour) : ChessPiece(colour) {};

  /*
    Method: get_type
    Overriding of parent's pure virtual function
    Returns the const char* "Bishop"

    Returns:
      const char*: "Bishop"
  */
  const char* get_type() const override { return "Bishop"; }

  /*
    Method: try_move
    Overriding of parent's pure virtual function
    Tests whether a bishop can path from a given start to a given end 

    Returns:
      bool: True if bishop can path from start to end
            False if bishop cannot path from start to end
  */
  bool try_move(
    Position start, Position end, ChessPiece* board[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
