#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Colour.h"

class Queen: public ChessPiece {
  
 public:
    /*
    Queen Constructor with one paramter
    Sets the Queen's colour attribute to a given Colour enum 
    via ChessPiece constructor

    Param:
      colour: Of type colour, sets colour of ChessPiece
  */
  Queen(Colour colour) : ChessPiece(colour) {};
  
  /*
    Method: get_type 
    Overrides ChessPiece's pure virtual getter method to return "Pawn"

    Returns:
      Const char*: Returns const char* "Pawn"
  */
  const char* get_type() const override { return "Queen"; }

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
        Not changed by Queen

    Returns:
      bool: True if Queen can path to end square
            False if not
  */
  bool try_move(
    Position current, Position target, ChessPiece* board[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
