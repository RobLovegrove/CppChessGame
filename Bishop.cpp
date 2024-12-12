#include "Bishop.h"
#include "Position.h"
#include "ChessGame.h"
#include <cmath>

using namespace std;

bool Bishop::try_move(
  Position start, Position end, ChessPiece* board[8][8], uint8_t* castling) {

  return try_bishop_moves(start, end, board);
}