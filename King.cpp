#include "King.h"
#include "Position.h"
#include <cmath>

using namespace std;

bool King::try_move(Position current, Position target, ChessPiece* board[8][8]) {

  if (current == target) return false;

  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->get_colour() == target_piece->get_colour()) return false;

  Position::Result result = current - target;

  if (abs(result.delta_file) > 1 || abs(result.delta_rank) > 1) return false;

  if (target_piece == nullptr || target_piece->get_colour() != this->colour) return true;
  return false;
}
 