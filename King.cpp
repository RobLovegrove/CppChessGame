#include <cmath>
#include "King.h"
#include "Rook.h"
#include "Queen.h"
#include "Position.h"
#include "ChessGame.h"

using namespace std;

bool King::try_move(
  Position current, Position target, 
  ChessPiece* board[8][8], uint8_t* castling) {
  
  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];

  Position::Result result = current - target;

  int rank;
  (this->colour == Colour::WHITE) ? rank = 0 : rank = 7;

  // Handle castling
  if (current.get_rank() == rank && current.get_file() == 4) {
    if (abs(result.delta_file) >= 2 && result.delta_rank == 0) {
      // Castling by moving king two or more squares horizontally
      return handle_castling(result.delta_file, board, rank, castling);
    }
  }

  // If not castling King can only move at most 1 square in any direction
  if (abs(result.delta_file) > 1 || abs(result.delta_rank) > 1) return false;

  if (target_piece == nullptr || target_piece->get_colour() != this->colour) 
    return true;

  return false;
}

bool King::handle_castling(
  int delta_file, ChessPiece* b[8][8], int rank, uint8_t* castling) {
  
  int increment = delta_file / abs(delta_file);
  int distance_to_edge;
  (delta_file < 0) ? distance_to_edge = 4 : distance_to_edge = 3;

  // Check the relevant corner contains a rook
  ChessPiece* rook = b[4 + (distance_to_edge * increment)][rank];
  if (dynamic_cast<Rook*>(rook) && !dynamic_cast<Queen*>(rook)) {
    return false;
  }

  // Check path to corner is clear
  for (int i = 1; i < distance_to_edge; i++) {
    if (b[4 + (i * increment)][rank] != nullptr) return false;
  }

  /* 
  Update ChessGame's attempting_castling attribute by setting flag 
  corresponding to the colour and direction to 1
  */
  if (castling != nullptr) {
    if (increment < 0) {
      (this->colour == Colour::WHITE) 
      ? *castling = WHITE_QUEENSIDE : *castling = BLACK_QUEENSIDE;
    }
    else {
      (this->colour == Colour::WHITE) 
      ? *castling = WHITE_KINGSIDE : *castling = BLACK_KINGSIDE;
    }
  }
  
  return true;
}