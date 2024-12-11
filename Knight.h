#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"
#include "Colour.h"

class Knight: public ChessPiece {

 private:

 public:
  /*
    Knight Constructor with one paramter
    Sets the Knight's colour attribute to a given Colour enum 
    via ChessPiece constructor

    Param:
      colour: Of type colour, sets colour of ChessPiece
  */
  Knight(Colour colour) : ChessPiece(colour) {};
  
  /*
    Method: get_type 
    Overrides ChessPiece's pure virtual getter method to return "Knight"

    Returns:
      Const char*: Returns const char* "Knight"
  */
  const char* get_type() const override { return "Knight"; }

  /*
    Method: try_move 
    Overrides ChessPiece's pure virtual method 
    Returns true or false depending on whether Knight can path from 
    a given start square to a given end sqaure

    Params:
      start: Of type Position, file and rank of starting square
      end: Of type Position, file and rank of ending square
      board[8][8]: 8x8 board of pointers to ChessPiece's
        ChessPiece* points to nullptr when square is empty
      castling: Of type uin8_t
        Reference to ChessGame's attempting_castling attribute
        Not changed by Knight

    Returns:
      bool: True if Knight can path to end square
            False if not
  */
  bool try_move(
    Position current, Position target, ChessPiece* board[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
