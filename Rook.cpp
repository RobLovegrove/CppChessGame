#include "Rook.h"
#include "King.h"
#include "ChessGame.h"
using namespace std;

bool Rook::try_move(
  Position start, Position end, ChessPiece* b[8][8], uint8_t* castling) {

  ChessPiece* target_piece = b[end.get_file()][end.get_rank()];

  Position::Result result = start - end;
  int rank;
  (this->colour == Colour::WHITE) ? rank = 0 : rank = 7;

  // Handle castling by rook moving onto own king
  if (target_piece != nullptr) {
    if (dynamic_cast<King*>(target_piece) && 
        target_piece->get_colour() == this->colour) {
      if (end.get_rank() == rank && end.get_file() == 4) {
        return handle_rook_castling(
          result.delta_file, 
          result.delta_rank, start, b, rank, castling);
      }
      return false;
    }
  }
  return try_rook_moves(start, end, b);
}

bool Rook::try_rook_moves(
  Position start, Position end, ChessPiece* board[8][8]) {
    
  if (start.get_rank() == end.get_rank()) {
    if (start.get_file() < end.get_file()) {
      return handle_file_move(start, end, board, 1);
    }
    return handle_file_move(start, end, board, -1);
  }

  if (start.get_file() == end.get_file()) {
    if (start.get_rank() < end.get_rank()) {
      return handle_rank_move(start, end, board, 1);
    }
    return handle_rank_move(start, end, board, -1);
  }
  return false;
}

bool Rook::handle_file_move(
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

bool Rook::handle_rank_move(
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

bool Rook::handle_rook_castling(
  int delta_file, int delta_rank, Position start, 
  ChessPiece* b[8][8], int rank, uint8_t* castling) {
  
  int increment = delta_file / abs(delta_file);
  int distance_to_edge;
  (delta_file > 0) ? distance_to_edge = 4 : distance_to_edge = 3;

  // Check this is in relevant corner
  int file = 4 - (distance_to_edge * increment);
  if (start != Position(file, rank)) return false;

  // Check path to corner is clear
  for (int i = 1; i < distance_to_edge; i++) {
    if (b[4 - (i * increment)][rank] != nullptr) return false;
  }

  /* 
  Update ChessGame's attempting_castling attribute by setting flag 
  corresponding to the colour and direction to 1
  */
  if (castling != nullptr) {
    if (increment > 0) {
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