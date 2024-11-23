#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <string>
#include "ChessPiece.h"
#include "Colour.h"
#include "Position.h"

class ChessGame {

 private:
  ChessPiece* board[8][8];
  Colour active_player;
  void assign_piece(char c, int &file, int rank, Colour colour);
  bool is_valid_square(const char* sqaure);
  void is_legal_move(Position start, Position end);
  
 public:
  void loadState(const char* current_position);
  void submitMove(const char* start_square, const char* end_square);
  ~ChessGame();
  
  
};

#endif
