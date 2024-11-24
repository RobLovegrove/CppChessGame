#include "Rook.h"

using namespace std;

bool Rook::try_move(Position current, Position target, ChessPiece* board[8][8]) {

  if (current == target) return false;

  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->colour == target_piece->get_colour()) return false;

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