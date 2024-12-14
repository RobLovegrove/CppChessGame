#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <string>
#include <cstdint>
#include <optional>

#include "ChessPiece.h"
#include "Colour.h"
#include "Position.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

/*
Most significant bit to least significant bit:
Game over flag - set to one if game is over
White kingside flag - set to one if white can castle kignside
White queenside flag - set to one if white can castle queenside
Black kingside flag - set to one if black can castle kignside
Black queenside flag - set to one if black can castle queenside
Loading active player flag - set to one if loading active player
Loading castling rights flag - set to one if loading castling rights
Active player flag - set to one if it is black's turn
*/

const uint8_t GAME_OVER = 0b10000000;
const uint8_t WHITE_KINGSIDE = 0b01000000;
const uint8_t WHITE_QUEENSIDE = 0b00100000;
const uint8_t BLACK_KINGSIDE = 0b00010000;
const uint8_t BLACK_QUEENSIDE = 0b00001000;
const uint8_t LOADING_ACTIVE_PLAYER = 0b00000100;
const uint8_t LOADING_CASTLING_RIGHTS = 0b00000010;
const uint8_t BLACKS_TURN = 0b00000001;
const uint8_t NILL = 0b00000000;

class ChessGame {

/* - - - - - - - - PRIVATE ATTRIBUTES AND METHODS - - - - - - - - - - */

 private:

  struct Pieces {
    Pawn* pawn = nullptr;
    Rook* rook = nullptr;
    Knight* knight = nullptr;
    Bishop* bishop = nullptr;
    Queen* queen = nullptr;
    King* king = nullptr;
  };

  struct Square {
    ChessPiece* piece;
    std::optional<Colour> colour;
  };

  Pieces black_pieces;
  Pieces white_pieces;

  ChessPiece* board[8][8];

  /*
    Attribute: game_state

    8 bits representing the state of the game:
    Each bit is described via global constants declared above

  */
  uint8_t game_state;

  /*
    Attribute: attempting_castling

    8 bits passed via reference to ChessPiece's on try_move
    If king/rook castle, this attribute is updated to flag to ChessGame class
    that a piece is attempting to castle

  */
  uint8_t attempting_castling = NILL;

  /* LOAD GAME HELPER FUNCTIONS */

  void reset_pieces(Pieces pieces);
  void delete_pieces(Pieces pieces);
  void delete_piece(Pieces pieces, ChessPiece* chess_piece);

  /*
    Method: load_position

    Helper function for parsing FEN string
    Takes a given charcter from board position section of FEN string
    Adds spaces if character is number 1 to 8
    Adds a black piece to board if correct lower case letter via assign_piece()
    Adds a white piece to board if correct upper case letter via assign_piece()
  */
  void load_position(const char, int& file, int& rank);

  /*
    Method: assign_piece

    Called via load_position function
    Takes a given upper case letter and Colour
    Adds piece corresponding to character passing colour into piece constructor
    Increments reference to loadState()'s file for each piece added
  */
  void assign_piece(const char, int& file, const int rank, const Colour&, Pieces&);

  /*
    Method: loading_complete

    Output's that the board state has been loaded on successful parsing of FEN
    Checks whether the provided FEN string is a position already in checkmate
    or stalemate
  */
  void loading_complete();

  /* SUBMIT MOVE HELPER FUNCTIONS */

  /*
    Method: is_valid_square

    First helper function called by submitMove()
    Ensures each move string provided to submitMove() is exactly 2 characters
    and does not reference a position outside the 8x8 chess board

    Returns:
    bool: True if string is 2 characters long and within chessboard
          False if not
  */
  bool is_valid_square(const char*) const;

  /*
    Method: is_legal_move
    Called by submit move after each move string is validated and converted into
    a Position Class containing an int for file and int for rank
    Ensures the provided move is a legal chess move

    Params:
      start: Of type Position
          File and rank of starting square
      end: Of type Position
          File and rank of final square
      output: of type bool
          If true will output whether move is legal or not
          If false will not output whether move is legal or not

    Returns:
    bool: True if the move is legal
          False if the move is illegal
  */
  bool is_legal_move(Position start, Position end, const bool output);

  /*
    Method: check_basic_rules of type const
    Ensures basic rulse of a chess move are being conformed to for a given
    move

    Params:
      start: Of type Position
          File and rank of starting square
      end: Of type Position
          File and rank of final square
      output: of type bool
          If true will output if basic rules are followed
          If false will not output anything

    Returns:
    bool: True if the basic rules are being followed
          False if not
  */
  bool check_basic_rules(Position start, Position end, const bool output) const;

  /*
    Method: is_castling_legal of type const
    Called by is_legal_move when piece is trying to castle
    Ensures the king has the relevant castling rights
    Ensures the king does not start, move through or end in check on castling
    If castling is illegal, resets attempting_castling back to NIL

    Params:
      start: Of type Position
          File and rank of starting square
      end: Of type Position
          File and rank of final square
      output: of type bool
          If true will output if castling is legal
          If false will not output anything
          
    Returns:
    bool: True if castling is legal
          False if not
  */
  bool is_castling_legal(Position start, Position end, const bool output);

  /*
    Method: is_check
    Called to check whether current active_player is in check
          
    Returns:
    bool: True if king in check
          False if not
  */
  bool is_check();

  /*
    Method: is_square_attacked
    Checks whether the non active_player can move to a given Position
    (i.e. whether a given square is under attack)

    Params:
      target: Of type position, location of square to be checked
          
    Returns:
    bool: True if a given board has a king in check
          False if not
  */
  bool is_square_attacked(Position target);

  /*
    Method: can_move
    Loops through board checking each piece belonging to active player
    If piece can move returns true
    If no piece is found that can move, returns false

    Returns:
    bool: True if a active player on this ChessGame's board can move
          False if not
  */
  bool can_move();

  /*
    Method: update_castling_rights
    If a rook or king has moved from starting square,
    the relevant game_state flag is updated to represent
    the removal of castling rights
  */
  void update_castling_rights(Position start, Position end);

  /*
    Method: castle
    If a given legal move is a castling move, correct rook and king are moved to 
    correct position on the board
    attempting_castling is reset back to NIL
  */
  void castle();

  /*
    Method: make_move
    Applies a given legal move to the ChessGames board
    If move is capturing a piece, the captured piece is deleted from the heap
  */
  void make_move(Position start, Position end);

  /*
    Method: output_successful_move of type const
    Outputs when a successful move is made in form:
    < Active colour > < piece > moves from  < start sqaure > to < end square >
    
    If move involves capture, the following is added to the end of line:
      taking < opponent colour > < opponent piece >
  */
  void output_successful_move(Position start, Position end) const;

  /*
    Method: output_unsuccessful_move of type const
    Outputs when an unsuccessful move is made in form:
    < Active colour > < piece > cannot move to  < end sqaure >!
  */
  void output_unsuccessful_move(Position start, Position end) const;


/* - - - - - - - - PUBLIC ATTRIBUTES AND METHODS - - - - - - - - - - */

 public:

  /*
    Method: loadState
    Parses the first three elements of a given FEN string:
      Board position, 
      Active colour,
      Castling rights
    It then parses the string keeping track of what part of the string is 
    being parsed via second and third least significant bits in game_state
    Board position is passed into ChessGame's board[8][8]
    Active_player and castling rights are saved to relevant bits of game_state

    Params:
      FEN_string: const char* pointing to the start of the FEN string
  */
  void loadState(const char* FEN_string);

  /*
    Method: submitMove
    Takes two char* values denoting the start square and end square of 
    the desired move
    Checks if the move is valid and legal
    Outputs result and if legal updates ChessGame's board[8][8]

    Params:
      start_square: Of type const char* represents starting sqaure of move
      end_square: Of type const char* represents end square of move
      
  */
  void submitMove(const char* start_square, const char* end_square);

  /*
    Method: display_board
    Displays a board in an 8x8 grid with the current position
    Uppercase letters used to represent white pieces
    Lower case letters used to represent black pieces
    Letter N is used to represent Knights (K represents King)
    Board displayed to terminal      
  */
  void display_board();

  /*
    ChessGame Constructor
    Sets all ChessPiece pointers in the board[8][8] to be nullptrs
    Sets the game state to NILL (0b00000000)
  */
  ChessGame();

  /*
    ChessGame Destructor
    Loops through ChessGame board[8][8] calling delete on any ChessPiece pointer
    not current set to nullptr via deallocate memory helper function
  */
  ~ChessGame();
};

#endif




