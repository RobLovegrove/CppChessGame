#include "King.h"
#include "Position.h"
#include <cmath>

using namespace std;

bool King::try_move(Position current, Position target, ChessPiece* board[8][8]) {

  if (current == target) return false;

  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->colour == target_piece->get_colour()) return false;

  Position::Result result = current - target;

  int rank;
  (this->colour == Colour::WHITE) ? rank = 0 : rank = 7;

  if (abs(result.delta_file) == 2 && result.delta_rank == 0 && current.get_rank() == rank) {
    // Attempting to castle
    
  }

  if (abs(result.delta_file) > 1 || abs(result.delta_rank) > 1) return false;

  if (target_piece == nullptr || target_piece->get_colour() != this->colour) return true;
  return false;
}
  