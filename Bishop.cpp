#include "Bishop.h"
#include "Position.h"
#include "ChessGame.h"
#include <cmath>

using namespace std;

bool Bishop::try_move(
  Position start, Position end, ChessPiece* board[8][8], uint8_t* castling) {

  return try_bishop_moves(start, end, board);
}

bool Bishop::try_bishop_moves(
  Position start, Position end, ChessPiece* board[8][8]) {

  ChessPiece* target_piece = board[end.get_file()][end.get_rank()];
  
  Position::Result result = start / end;

  // Check that the mod of the gradient between 
  // the starting position and the target position is 1
  if (fabs(result.gradient) != 1) return false;
  
  // Calculate an increment for both file and rank as change / abs(change)
  int distance = abs(result.delta_file);
  int file_increment = result.delta_file / distance;
  int rank_increment = result.delta_rank / distance;
  
  for (int i = 1; i <= distance; i++) {
    if (i == distance && 
    (target_piece == nullptr || target_piece->get_colour() != this->colour)) 
    return true;

    // Increment along diagonal towards end square
    int f = start.get_file() + (file_increment * i);
    int r = start.get_rank() + (rank_increment * i);
    if (board[f][r] != NULL) {
      // If sqaure on path to end is not empty return false
      return false;
    } 
  }
  return false;
}