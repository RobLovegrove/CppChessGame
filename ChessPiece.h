#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <cstdint>
#include "Colour.h"
#include "Position.h"

class ChessPiece {

/* - - - - - - - PRIVATE METHODS - - - - - - - -- - */

private:
   /*
    Method: handle_rook_file_move
    Called by try_rook_moves
    Checks if path between start file and end file is clear 
    Ensures end square does not contain own piece

    Returns:
      bool: True if piece can path to end square via file
            False if not
  */
  bool handle_rook_file_move(
    Position current, Position target, ChessPiece* b[8][8], int direction);

   /*
    Method: handle_rook_rank_move
    Called by try_rook_moves
    Checks if path between start rank and end rank is clear 
    Ensures end square does not contain own piece

    Returns:
      bool: True if piece can path to end square via rank
            False if not
  */
  bool handle_rook_rank_move(
    Position current, Position target, ChessPiece* b[8][8], int direction);


/* - - - - - - - PROTECTED METHODS - - - - - - - -- - */

protected:
  Colour colour;

  /*
    ChessPiece Constructor with one paramter
    Sets the ChessPiece's colour attribute to a given Colour enum

    Param:
      colour: Of type colour, sets colour of ChessPiece
  */
  ChessPiece(Colour colour) : colour(colour) {};

  /*
    Method: try_bishop_moves
    Tests whether a piece can path from a given start to a given end like
    a bishop (on the diagonals)

    Params: 
      start: Of type Position
            File and rank of starting square
      end: Of type Position
          File and rank of final square
      board: 2D array (8x8) containing pointers to chess pieces
            Empty sqaures contain nullptr
    
    Returns:
      bool: True if bishop can path from start to end
            False if bishop cannot path from start to end
  */
  bool try_bishop_moves(
  Position start, Position end, ChessPiece* board[8][8]);

  /*
    Method: try_rook_moves
    Checks if start file equals end file or start rank equals end rank
    If not returns false
    Otherwise calls handle_rank_move or handle_file_move

    Returns:
      bool: True if Rook can path to end square
            False if not
  */
  bool try_rook_moves(Position current, Position target, ChessPiece* b[8][8]);


/* - - - - - - - - PUBLIC METHODS - - - - - - - -- - */

public:
  /*
    Method: Equal to operator overloading

    Overrides the equal operator to enable direct comparison between ChessPiece 
    and active_player flag
    ChessPiece's colour attribute is cast to int from enum 
    0 for WHITE and 1 for BLACK
    This is then compared to Active player flag of ChessGame's game_state
    0b00000000 for WHITE and 0b00000001 for BLACK

    Returns:
      bool: True if Colour enum and game flag are equal
            False if not
  */
  bool operator==(uint8_t value) const;

  /*
    Method: Not equal to operator overloading

    Overrides the "not equal" operator to enable direct comparison between ChessPiece 
    and active_player flag
    ChessPiece's colour attribute is cast to int from enum 
    0 for WHITE and 1 for BLACK
    This is then compared to Active player flag of ChessGame's game_state
    0b00000000 for WHITE and 0b00000001 for BLACK

    Returns:
      bool: True if Colour enum and game flag are not equal
            False if they are
  */
  bool operator!=(uint8_t value) const;

  /*
    Method: ChessPiece output operator overloading
    Outputs a ChessPiece in the given form:

    < Piece Colour >'s < Piece type >
  */
  friend std::ostream& operator << (std::ostream& os, const ChessPiece& piece);

  /*
    Method: get_colour 
    Getter method to return this ChessPiece's Colour

    Returns:
      Colour: This ChessPiece's colour attribute
  */
  Colour get_colour() const { return colour; }

  /*
    Method: get_type 
    Pure virtual getter method to return this ChessPiece's type in form 
    of const char*
    Overriden by derived classes

    Returns:
      Const char*: Returns const char* describing the derived piece type
  */
  virtual const char* get_type() const = 0;
  
  /*
    Method: try_move 
    Pure virtual method that returns true or false depending on whether derived
    class can path from a given start square to a given end sqaure

    Params:
      start: Of type Position, file and rank of starting square
      end: Of type Position, file and rank of ending square
      board[8][8]: 8x8 board of pointers to ChessPiece's
        ChessPiece* points to nullptr when square is empty
      castling: Of type uin8_t
        Reference to ChessGame's attempting_castling attribute
        If king or rook are attempting to castle, this parameter is updated to 
        inform ChessGame of potential castling move 
        Flag of corresponding colour and castling direction set to 1 

    Returns:
      bool: True if Piece can path to end square
            False if not
  */
  virtual bool try_move(
    Position start, Position end, ChessPiece* board[8][8], 
    uint8_t* castling = nullptr) = 0;

  /*
    ChessPiece virtual default destructor
    Ensures proper destruction of child classes
  */
  virtual ~ChessPiece() {};

};

#endif
