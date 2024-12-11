#include "Pawn.h"
#include "Colour.h"
#include "ChessGame.h"

using namespace std;

// METHODS
bool Pawn::try_move(
  Position start, 
  Position end, 
  ChessPiece* board[8][8], 
  uint8_t* castling) {

  ChessPiece* target_piece = board[end.get_file()][end.get_rank()];

  // Not capturing piece
  if (target_piece == nullptr && end.get_file() == start.get_file()) {
    if (colour == Colour::WHITE) {
      return handle_not_capturing(start, end, board, 1, 2, 1);
    }
    else {
      return handle_not_capturing(start, end, board, -1, -2, 6);
    }
  }
  // Capturing piece
  else if (target_piece != nullptr) {
    if (colour == Colour::WHITE) {
      return handle_capturing(start, end, board, 1);
    }
    else {
      return handle_capturing(start, end, board, -1);
    }
  }
  return false; 
}

// HELPER FUNCTIONS

bool Pawn::handle_not_capturing(
  Position start, 
  Position end, 
  ChessPiece* b[8][8], int one, int two, int starting_rank ) {

  // Pawn is moving forwards one square
  if (end.get_rank() == start.get_rank() + one) return true;

  // Pawn is on starting rank and moving fowards two squares
  if (start.get_rank() == starting_rank && 
      end.get_rank() == start.get_rank() + two ) {
    
    // First sqaure in front of pawn is also empty
    if (b[start.get_file()+one][start.get_rank()+one] == nullptr) return true;

  }
  return false;

}

bool Pawn::handle_capturing(
  Position start, Position end, ChessPiece* b[8][8], int one) {

  if (b[end.get_file()][end.get_rank()]->get_colour() != this->colour) {
    if ((end.get_file() == start.get_file() - 1) || 
        end.get_file() == start.get_file() + 1) { 
      // Pawn is trying to capture piece either side of current file
      // Check if target is one rank ahead of pawn
      if (end.get_rank() == start.get_rank() + one) return true; 
    }
  }
  return false;
}