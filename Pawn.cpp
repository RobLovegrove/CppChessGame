#include "Pawn.h"
#include "Colour.h"

using namespace std;

// METHODS
bool Pawn::try_move(Position current, Position target, ChessPiece* board[8][8]) {

  if (current == target) return false;

  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->colour == target_piece->get_colour()) return false;

  // Not capturing piece
  if (board[target.get_file()][target.get_rank()] == nullptr && target.get_file() == current.get_file()) {
    if (colour == Colour::WHITE) {
      return handle_not_capturing(current, target, board, 1, 2, 1);
    }
    else {
      return handle_not_capturing(current, target, board, -1, -2, 6);
    }
  }
  // Capturing piece
  else if (board[target.get_file()][target.get_rank()] != nullptr) {
    if (colour == Colour::WHITE) {
      return handle_capturing(current, target, board, 1);
    }
    else {
      return handle_capturing(current, target, board, -1);
    }
  }
  return false; 
}

// HELPER FUNCTIONS

bool Pawn::handle_not_capturing(Position c, Position t, ChessPiece* b[8][8], int one, int two, int starting_rank ) {

  // Pawn is moving forwards one square
  if (t.get_rank() == c.get_rank() + one) return true;

  // Pawn is on starting rank and moving fowards two squares
  if (c.get_rank() == starting_rank && t.get_rank() == c.get_rank() + two ) {
    
    // First sqaure in front of pawn is also empty
    if (b[c.get_file()+one][c.get_rank()+one] == nullptr) return true;

  }
  return false;

}

bool Pawn::handle_capturing(Position c, Position t, ChessPiece* b[8][8], int one) {

  if (b[t.get_file()][t.get_rank()]->get_colour() != this->colour) {
    if ((t.get_file() == c.get_file() - 1) || t.get_file() == c.get_file() + 1) { 
      // Pawn is trying to capture piece either side of current file
      // Check if target is one rank ahead of pawn
      if (t.get_rank() == c.get_rank() + one) return true; 
    }
  }
  return false;
}