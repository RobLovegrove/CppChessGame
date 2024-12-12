#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"
#include "Colour.h"

class Rook: public ChessPiece {

  /* - - - - - - - PRIVATE METHODS - - - - - - - -- - */

 private:    
    /*
    Method: handle_rook_castling
    Called if Rook attempting to castle by moving onto own King
    Ensures this Rook is still in correct corner
    Ensures no pieces between rook and king
    Update ChessGame's attempting_castling attribute by setting flag 
    corresponding to the colour and direction to 1

    Params:
      delta_file: Of type int, Difference between start file and end file
      board[8][8]: 8x8 board of pointers to ChessPiece's
        ChessPiece* points to nullptr when square is empty
      castling: Of type uin8_t
        Reference to ChessGame's attempting_castling attribute
        If Rook is attempting to castle, this parameter is updated to 
        inform ChessGame of potential castling move 
        Flag of corresponding colour and castling direction set to 1 

    Returns:
      bool: True is Rook/King can csatle
            False if not
  */
  bool handle_rook_castling(
    int delta_file, int delta_rank, Position start, ChessPiece* b[8][8],
    int rank, uint8_t* castling);


  /* - - - - - - - PUBLIC METHODS - - - - - - - -- - */

 public:
  /*
    Rook Constructor with one paramter
    Sets the Rooks's colour attribute to a given Colour enum 
    via ChessPiece constructor

    Param:
      colour: Of type colour, sets colour of ChessPiece
  */
  Rook(Colour colour) : ChessPiece(colour) {}

  /*
    Method: get_type 
    Overrides ChessPiece's pure virtual getter method to return "Rook"

    Returns:
      Const char*: Returns const char* "Rook"
  */
  const char* get_type() const override { return "Rook"; }

  /*
    Method: try_move 
    Overrides ChessPiece's pure virtual method 
    Returns true or false depending on whether Rook can path from 
    a given start square to a given end sqaure

    Params:
      start: Of type Position, file and rank of starting square
      end: Of type Position, file and rank of ending square
      board[8][8]: 8x8 board of pointers to ChessPiece's
        ChessPiece* points to nullptr when square is empty
      castling: Of type uin8_t
        Reference to ChessGame's attempting_castling attribute
        If Rook is attempting to castle, this parameter is updated to 
        inform ChessGame of potential castling move 
        Flag of corresponding colour and castling direction set to 1 

    Returns:
      bool: True if Rook can path to end square
            False if not
  */
  bool try_move(
    Position current, Position target, ChessPiece* b[8][8], 
    uint8_t* castling = nullptr) override;
};

#endif
