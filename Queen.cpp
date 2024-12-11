#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "ChessGame.h"

using namespace std;

bool Queen::try_move(
  Position current, 
  Position target, 
  ChessPiece* board[8][8], 
  uint8_t* castling) {

  if (try_rook_moves(current, target, board)) return true;
  if (try_bishop_moves(current, target, board)) return true;

  return false;
}
