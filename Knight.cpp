#include "Knight.h"
#include "Position.h"

using namespace std;

bool Knight::try_move(Position current, Position target, ChessPiece* board[8][8]) {

  if (current == target) return false;

  Position::Result result = current - target;

  int delta_f = abs(result.delta_file);
  int delta_r = abs(result.delta_rank);

  if ((delta_f == 2 && delta_r == 1) || (delta_r == 2 && delta_f == 1)) {
    ChessPiece* opponent_piece = board[target.get_file()][target.get_rank()];
    if (opponent_piece == nullptr || opponent_piece->get_colour() != this->colour) return true;
  }

  return false;
}
