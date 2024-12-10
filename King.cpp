#include <cmath>
#include "King.h"
#include "Position.h"
#include "ChessGame.h"

using namespace std;

bool King::try_move(Position current, Position target, ChessPiece* board[8][8], const ChessGame* game, uint8_t* castling) {

  if (current == target) return false;

  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->colour == target_piece->get_colour()) {
    if (target_piece->get_type() != Type::ROOK) return false;
  }

  Position::Result result = current - target;

  int rank;
  (this->colour == Colour::WHITE) ? rank = 0 : rank = 7;

  // Handle castling
  if (current.get_rank() == rank && current.get_file() == 4) {
    if (abs(result.delta_file) >= 2 && result.delta_rank == 0) {
      // Castling by moving king two or more squares laterally
      return handle_castling(result.delta_file, result.delta_rank, board, rank, game, castling);
    }
  }

  if (abs(result.delta_file) > 1 || abs(result.delta_rank) > 1) return false;

  if (target_piece == nullptr || target_piece->get_colour() != this->colour) return true;

  return false;
}

bool King::handle_castling(int df, int dr, ChessPiece* b[8][8], int r, const ChessGame* g, uint8_t* c) {
  
  int increment = df / abs(df);
  int distance_to_edge;
  (df < 0) ? distance_to_edge = 4 : distance_to_edge = 3;

  // Check the relevant corner contains a rook
  if (b[4 + (distance_to_edge * increment)][r]->get_type() != Type::ROOK) {
    return false;
  }

  // Check path to corner is clear
  for (int i = 1; i < distance_to_edge; i++) {
    if (b[4 + (i * increment)][r] != nullptr) return false;
  }

  // Make a tmp board
  ChessPiece* tmp_board[8][8];
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      tmp_board[x][y] = b[x][y];
    }
  }

  // Check if king moves through check 
  for (int i = 0; i < 3; i++) {
    if (i == 0) {
      if (g->is_check(b)) return false;
    }
    else {
      // Move king to next square
      tmp_board[4 + (i*increment)][r] = tmp_board[4 + ((i-1)*increment)][r];
      tmp_board[4 + ((i-1)*increment)][r] = nullptr;
      if (g->is_check(tmp_board)) return false;
    }
  }

  if (c != nullptr) {
    if (increment < 0) {
      (this->colour == Colour::WHITE) ? *c = WHITE_QUEENSIDE : *c = BLACK_QUEENSIDE;
    }
    else {
      (this->colour == Colour::WHITE) ? *c = WHITE_KINGSIDE : *c = BLACK_KINGSIDE;
    }
  }
  
  return true;
}