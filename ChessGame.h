#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <string>
#include "ChessPiece.h"
#include "Colour.h"
#include "Position.h"

const uint8_t GAME_OVER = 0b10000;
const uint8_t WHITE_KINGSIDE = 0b01000;
const uint8_t WHITE_QUEENSIDE = 0b00100;
const uint8_t BLACK_KINGSIDE = 0b00010;
const uint8_t BLACK_QUEENSIDE = 0b00001;
const uint8_t NILL = 0b00000;

class ChessGame {

 private:
  ChessPiece* board[8][8];
  Colour active_player;

  enum {POSITION, ACTIVE_PLAYER, CASTLING} state;

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
  void loadState(const char* current_position);
  void submitMove(const char* start_square, const char* end_square);
  bool is_check(Colour _active_player, ChessPiece* b[8][8]) const;

  void print_board();

  ~ChessGame();
  ChessGame();
  
};

#endif
