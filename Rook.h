#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"
#include "Colour.h"

class Rook: virtual public ChessPiece {

 private:
  bool handle_file_move(Position current, Position target, ChessPiece* board[8][8], int direction);
  bool handle_rank_move(Position current, Position target, ChessPiece* board[8][8], int direction);
  bool handle_rook_castling(int delta_file, int delta_rank, Position start, ChessPiece* b[8][8], int rank, const ChessGame* game, uint8_t* castling);

protected:
  bool try_rook_moves(ChessPiece* target_piece, Position current, Position target, ChessPiece* board[8][8]);
  Rook() {}

 public:
  Rook(Colour colour) : ChessPiece(colour) {}

  Type get_type() const override { return Type::ROOK; }
  bool try_move(Position current, Position target, ChessPiece* board[8][8], const ChessGame* game, uint8_t* castling = nullptr) override;
};

#endif
