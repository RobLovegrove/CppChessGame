#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <string>
#include "ChessPiece.h"
#include "Colour.h"
#include "Position.h"

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

 private:
  ChessPiece* board[8][8];

  uint8_t game_state;
  uint8_t attempting_castling = NILL;

  /* LOAD GAME HELPER FUNCTIONS */
  void deallocate_memory(const int file, const int rank);
  void load_position(const char, int& file, int& rank);
  void assign_piece(const char, int& file, const int rank, const Colour&);
  void loading_complete();

  /* SUBMIT MOVE HELPER FUNCTIONS */
  bool is_valid_square(const char*) const;
  bool is_legal_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end);
  bool try_move(ChessPiece* chess_piece, Position start, Position end, ChessPiece* b[8][8], bool output);
  bool is_check(ChessPiece* b[8][8]) const;
  bool can_move();

  void castle();
  void make_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end);
  void update_castling_rights(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start);

  void output_successful_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end);
  void output_unsuccessful_move(ChessPiece* chess_piece, Position start, Position end);

 public:
  void loadState(const char* current_char);
  void submitMove(const char* start_square, const char* end_square);

  void print_board();

  ~ChessGame();
  ChessGame();
  
};

#endif
