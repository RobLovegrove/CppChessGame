#include "ChessPiece.h"

#include <iostream>
#include <cmath>

using namespace std;

std::ostream& operator << (ostream& os, const ChessPiece& piece) {
    os << piece.colour << "'s " << piece.get_type();
    return os;
}

bool ChessPiece::operator==(uint8_t value) const {
    // Compare the piece's colour with the active player bit
    // Casting colour to int will be 0 for WHITE and 1 for BLACK
    // Active player flag will be 0b00000000 for WHITE and 0b00000001 for BLACK
    return static_cast<int>(colour) == value;
}

bool ChessPiece::operator!=(uint8_t value) const {
    // Compare the piece's colour with the active player bit
    // Casting colour to int will be 0 for WHITE and 1 for BLACK
    // Active player flag will be 0b00000000 for WHITE and 0b00000001 for BLACK
    return static_cast<int>(colour) != value;
}

bool ChessPiece::try_bishop_moves(
  Position start, Position end, ChessPiece* board[8][8]) {

  ChessPiece* target_piece = board[end.get_file()][end.get_rank()];
  
  Position::Result result = start / end;

  // Check that the mod of the gradient between 
  // the starting position and the target position is 1
  if (fabs(result.gradient) != 1) return false;
  
  // Calculate an increment for both file and rank as change / abs(change)
  int distance = abs(result.delta_file);
  int file_increment = result.delta_file / distance;
  int rank_increment = result.delta_rank / distance;
  
  for (int i = 1; i <= distance; i++) {
    if (i == distance && 
    (target_piece == nullptr || target_piece->get_colour() != this->colour)) 
    return true;

    // Increment along diagonal towards end square
    int f = start.get_file() + (file_increment * i);
    int r = start.get_rank() + (rank_increment * i);
    if (board[f][r] != NULL) {
      // If sqaure on path to end is not empty return false
      return false;
    } 
  }
  return false;
}

bool ChessPiece::try_rook_moves(
  Position start, Position end, ChessPiece* board[8][8]) {
    
  if (start.get_rank() == end.get_rank()) {
    if (start.get_file() < end.get_file()) {
      return handle_rook_file_move(start, end, board, 1);
    }
    return handle_rook_file_move(start, end, board, -1);
  }

  if (start.get_file() == end.get_file()) {
    if (start.get_rank() < end.get_rank()) {
      return handle_rook_rank_move(start, end, board, 1);
    }
    return handle_rook_rank_move(start, end, board, -1);
  }
  return false;
}

bool ChessPiece::handle_rook_file_move(
  Position start, Position end, ChessPiece* board[8][8], int direction) {

  ChessPiece* target_piece = board[end.get_file()][end.get_rank()];
  int distance = abs(end.get_file() - start.get_file());
  int rank = start.get_rank();

  for (int i = 1; i <= distance; i++) {
    if (i == distance && 
        (target_piece == nullptr || target_piece->get_colour() != this->colour)) 
        return true;
    if (board[start.get_file() + (direction * i)][rank] != NULL) {
      return false;
    } 
  }
  return false;
}

bool ChessPiece::handle_rook_rank_move(
  Position start, Position end, ChessPiece* board[8][8], int direction) {  

  ChessPiece* target_piece = board[end.get_file()][end.get_rank()];

  int distance = abs(end.get_rank() - start.get_rank());
  int file = start.get_file();

  for (int i = 1; i <= distance; i++) {
    if (i == distance) {
      if (target_piece == nullptr || target_piece->get_colour() != this->colour) {
        return true;
      }
    }
    if (board[file][start.get_rank() + (direction * i)] != NULL) {
      return false;
    } 
  }
  return false;
}