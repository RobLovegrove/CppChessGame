#include "Pawn.h"
#include "Colour.h"

using namespace std;

bool Pawn::try_move(Position current, Position target, ChessPiece* board[8][8]) {

  // Not capturing piece
  if (board[target.get_file()][target.get_rank()] == NULL && target.get_file() == current.get_file()) {
    if (colour == Colour::WHITE) {
      return pawn_not_capturing(current, target, board, 1, 2, 1);
    }
    else {
      return pawn_not_capturing(current, target, board, -1, -2, 6);
    }
  }
  // Capturing piece
  else if (target.get_file()) {
    
  }  
}

bool Pawn::pawn_not_capturing(Position c, Position t, ChessPiece* b[8][8], int one, int two, int starting_rank ) {

  // Pawn is moving forwards one square
  if (t.get_rank() == c.get_rank() + one) return true;

  // Pawn is on starting rank and moving fowards two squares
  if (c.get_rank() == starting_rank && t.get_rank() == c.get_rank() + two ) {
    
    // First sqaure in front of pawn is empty
    if (b[c.get_file()+one][c.get_rank()+one] == NULL) return true;
 
  }
  return false;

}
