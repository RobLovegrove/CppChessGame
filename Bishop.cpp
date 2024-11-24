#include "Bishop.h"
#include "Position.h"
#include <cmath>

using namespace std;

bool Bishop::try_move(Position current, Position target, ChessPiece* board[8][8]) {

  if (current == target) return false;

  ChessPiece* target_piece = board[target.get_file()][target.get_rank()];
  if (target_piece != nullptr && this->get_colour() == target_piece->get_colour()) return false;

  return try_bishop_moves(target_piece, current, target, board);
}

bool Bishop::try_bishop_moves(ChessPiece* target_piece, Position current, Position target, ChessPiece* board[8][8]) {
  Position::Result result = current / target;

  // Check that the mod of the gradient between the starting position and the target position is 1
  if (fabs(result.gradient) != 1) return false;
  
  int distance = abs(result.delta_file);
  int file_increment = result.delta_file / distance;
  int rank_increment = result.delta_rank / distance;
  
  for (int i = 1; i <= distance; i++) {
    if (i == distance && (target_piece == nullptr || target_piece->get_colour() != this->colour)) return true;
    if (board[current.get_file() + (file_increment * i)][current.get_rank() + (rank_increment * i)] != NULL) {
      return false;
    } 
  }
  return false;
}