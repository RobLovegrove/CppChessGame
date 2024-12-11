#include "Knight.h"
#include "Position.h"
#include "ChessGame.h"

using namespace std;

bool Knight::try_move(Position current, Position target, ChessPiece* board[8][8], uint8_t* castling) {

  if (current == target) return false;
 
  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->colour == target_piece->get_colour()) return false;

  Position::Result result = current - target;

  int delta_f = abs(result.delta_file);
  int delta_r = abs(result.delta_rank);

  if ((delta_f == 2 && delta_r == 1) || (delta_r == 2 && delta_f == 1)) {
    if (target_piece == nullptr || target_piece->get_colour() != this->colour) return true;
  }

  return false;
}
