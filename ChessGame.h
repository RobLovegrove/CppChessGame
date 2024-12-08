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

*/

const uint8_t GAME_OVER = 0b1000000;
const uint8_t WHITE_KINGSIDE = 0b0100000;
const uint8_t WHITE_QUEENSIDE = 0b0010000;
const uint8_t BLACK_KINGSIDE = 0b0001000;
const uint8_t BLACK_QUEENSIDE = 0b0000100;
const uint8_t LOADING_ACTIVE_PLAYER = 0b0000010;
const uint8_t LOADING_CASTLING_RIGHTS = 0b0000001;
const uint8_t NILL = 0b0000000;

class ChessGame {

 private:
  ChessPiece* board[8][8];
  Colour active_player;

  uint8_t game_state;
  uint8_t attempting_castling = NILL;

  void deallocate_memory(int file, int rank);
  void load_position(char c, int& file, int& rank);
  void assign_piece(char c, int &file, int rank, Colour colour);
  void loading_complete();
  bool is_valid_square(const char* sqaure);
  bool is_legal_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end);
  void output_successful_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end);
  void output_unsuccessful_move(ChessPiece* chess_piece, Position start, Position end);
  bool try_move(ChessPiece* chess_piece, Position start, Position end, ChessPiece* b[8][8], bool output);
  bool can_move(Colour active_player, ChessPiece* b[8][8]);

 public:
  void loadState(const char* current_char);
  void submitMove(const char* start_square, const char* end_square);
  bool is_check(Colour _active_player, ChessPiece* b[8][8]) const;

  void print_board();

  ~ChessGame();
  ChessGame();
  
};

#endif
