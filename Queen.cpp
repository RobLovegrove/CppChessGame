#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

using namespace std;

bool Queen::try_move(Position current, Position target, ChessPiece* board[8][8]) {

  if (current == target) return false;

  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->colour == target_piece->get_colour()) return false;

  if (try_rook_moves(target_piece, current, target, board)) return true;
  if (try_bishop_moves(target_piece, current, target, board)) return true;

  return false;
}
