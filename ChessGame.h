#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <string>
#include "ChessPiece.h"
#include "Colour.h"
#include "Position.h"

enum class Castling {BOTH, KINGSIDE, QUEENSIDE, NIL};

class ChessGame {

 private:
  ChessPiece* board[8][8];
  Colour active_player;
  bool game_over;
  enum {POSITION, ACTIVE_PLAYER, CASTLING} state;

  Castling white_casting;
  Castling black_castling;

  void deallocate_memory(int file, int rank);
  void load_position(char c, int& file, int& rank);
  void assign_piece(char c, int &file, int rank, Colour colour);
  void loading_complete();
  bool is_valid_square(const char* sqaure);
  bool is_legal_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end);
  void output_successful_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end);
  void output_unsuccessful_move(ChessPiece* chess_piece, Position start, Position end);
  bool is_check(Colour _active_player, ChessPiece* b[8][8]);
  bool try_move(ChessPiece* chess_piece, Position start, Position end, ChessPiece* b[8][8], bool output);
  bool can_move(Colour active_player, ChessPiece* b[8][8]);

 public:
  void loadState(const char* current_position);
  void submitMove(const char* start_square, const char* end_square);

  ~ChessGame();
  ChessGame();
  
};

#endif
