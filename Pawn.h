#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"
#include "Colour.h"
#include "Position.h"

class Pawn: public ChessPiece {

 private:
 /*
  Method: handle_not_capturing
  Ensures pawn only moves forward on current file if not capturing
  Only moving forward 2 if on starting rank

  Params:
    start: Of type Position, file and rank of starting square
    end: Of type Position, file and rank of ending square 
    board[8][8]: 8x8 board of pointers to ChessPiece's 
    one: Int - Sets direction pawn can move. +1 if white, -1 if black
    starting rank: Of type Int, 1 if white, 6 if black

  Returns:
    bool: True if Pawn can move forward
          False if not
 */
  bool handle_not_capturing(
    Position start, Position end, ChessPiece* board[8][8], 
    int one, int starting_rank);
    
  /*
  Method: handle_capturing
  Ensures pawn only captures by moving one square diagonally

  Params:
    start: Of type Position, file and rank of starting square
    end: Of type Position, file and rank of ending square 
    board[8][8]: 8x8 board of pointers to ChessPiece's 
    one: Int - Sets direction pawn can move. +1 if white, -1 if black

  Returns:
    bool: True if Pawn can caprture diagonally
          False if not
 */
  bool handle_capturing(
    Position start, Position end, ChessPiece* b[8][8], int one);

 public:
   /*
    Pawn Constructor with one paramter
    Sets the Pawn's colour attribute to a given Colour enum 
    via ChessPiece constructor

    Param:
      colour: Of type colour, sets colour of ChessPiece
  */
  Pawn(Colour colour) : ChessPiece(colour) {};

  /*
    Method: get_type 
    Overrides ChessPiece's pure virtual getter method to return "Pawn"

    Returns:
      Const char*: Returns const char* "Pawn"
  */
  const char* get_type() const override { return "Pawn"; }

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
        Not changed by Pawn

    Returns:
      bool: True if Pawn can path to end square
            False if not
  */
  bool try_move(
    Position start, Position end, ChessPiece* b[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
