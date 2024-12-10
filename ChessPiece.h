#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "Colour.h"
#include "Position.h"

class ChessGame; // Forward declaration

enum class Type {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
std::ostream& operator << (std::ostream& os, Type type);

class ChessPiece {

protected:
  Colour colour;
  ChessPiece(Colour colour) : colour(colour) {};
  ChessPiece() {}

public:
  bool operator==(uint8_t value) const;
  bool operator!=(uint8_t value) const;
  friend std::ostream& operator << (std::ostream& os, const ChessPiece& piece);
  Colour get_colour() const { return colour; }
  virtual Type get_type() const = 0;
  virtual bool try_move(Position current, Position target, ChessPiece* board[8][8], const ChessGame* game, uint8_t* castling = nullptr) = 0;

  virtual ~ChessPiece() {};
};

#endif
