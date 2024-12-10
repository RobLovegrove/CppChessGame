#include "Rook.h"
#include "ChessGame.h"
using namespace std;

bool Rook::try_move(Position current, Position target, ChessPiece* board[8][8], const ChessGame* game, uint8_t* castling) {

  if (current == target) return false;

  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->colour == target_piece->get_colour()) {
    if (target_piece->get_type() != Type::KING) return false;
  }

  // Handle castling by rook moving onto own king
  Position::Result result = current - target;
  int rank;
  (this->colour == Colour::WHITE) ? rank = 0 : rank = 7;
  if (target_piece != nullptr) {
    if (target_piece->get_type() == Type::KING && target_piece->get_colour() == this->colour) {
      if (target.get_rank() == rank && target.get_file() == 4) {
        return handle_rook_castling(result.delta_file, result.delta_rank, current, board, rank, game, castling);
      }
      return false;
    }
  }
  return try_rook_moves(target_piece, current, target, board);
}


bool Rook::try_rook_moves(ChessPiece* target_piece, Position current, Position target, ChessPiece* board[8][8]) {
  if (current.get_rank() == target.get_rank()) {
    if (current.get_file() < target.get_file()) {
      return handle_file_move(current, target, board, 1);
    }
    return handle_file_move(current, target, board, -1);
  }

  if (current.get_file() == target.get_file()) {
    if (current.get_rank() < target.get_rank()) {
      return handle_rank_move(current, target, board, 1);
    }
    return handle_rank_move(current, target, board, -1);
  }
  return false;
}

bool Rook::handle_file_move(Position current, Position target, ChessPiece* board[8][8], int direction) {
  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  int distance = abs(target.get_file() - current.get_file());
  int rank = current.get_rank();

  for (int i = 1; i <= distance; i++) {
    if (i == distance && (target_piece == nullptr || target_piece->get_colour() != this->colour)) return true;
    if (board[current.get_file() + (direction * i)][rank] != NULL) {
      return false;
    } 
  }
  return false;
}

bool Rook::handle_rank_move(Position current, Position target, ChessPiece* board[8][8], int direction) {  
  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  int distance = abs(target.get_rank() - current.get_rank());
  int file = current.get_file();

  for (int i = 1; i <= distance; i++) {
    if (i == distance && (target_piece == nullptr || target_piece->get_colour() != this->colour)) return true;
    if (board[file][current.get_rank() + (direction * i)] != NULL) {
      return false;
    } 
  }
  return false;
}

bool Rook::handle_rook_castling(int df, int dr, Position start, ChessPiece* b[8][8], int r, const ChessGame* g, uint8_t* c) {
  
  int increment = df / abs(df);
  int distance_to_edge;
  (df > 0) ? distance_to_edge = 4 : distance_to_edge = 3;
  // Check self is in relevant corner
  int file = 4 - (distance_to_edge * increment);
  if (start != Position(file, r)) return false;

  // Check path to corner is clear
  for (int i = 1; i < distance_to_edge; i++) {
    if (b[4 - (i * increment)][r] != nullptr) return false;
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
      tmp_board[4 - (i*increment)][r] = tmp_board[4 - ((i-1)*increment)][r];
      tmp_board[4 - ((i-1)*increment)][r] = nullptr;
      if (g->is_check(tmp_board)) return false;
    }
  }

  if (c != nullptr) {
    if (increment > 0) {
      (this->colour == Colour::WHITE) ? *c = WHITE_QUEENSIDE : *c = BLACK_QUEENSIDE;
    }
    else {
      (this->colour == Colour::WHITE) ? *c = WHITE_KINGSIDE : *c = BLACK_KINGSIDE;
    }
  }
  return true;
}