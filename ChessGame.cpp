#include <iostream>
#include <string>
#include <cassert>

// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq

#include "ChessGame.h"
#include "Colour.h"
#include "Position.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

using namespace std;

// CONSTRUCTOR
ChessGame::ChessGame() {
  for (int file = 0; file < 8; file++){
    for (int rank = 0; rank < 8; rank++) {
      board[file][rank] = nullptr;
    }
  }

  active_player = Colour::WHITE;
  game_over = false;
  state = ChessGame::POSITION;
  white_casting = Castling::BOTH;
  black_castling = Castling::BOTH;
}

// DESTRUCTORS
ChessGame::~ChessGame() {
  for (int file = 0; file < 8; file++){
    for (int rank = 0; rank < 8; rank++) {
      deallocate_memory(file, rank);
    }
  }
}

// METHODS

void ChessGame::loadState(const char* current_position) {

  state = POSITION;
  game_over = false;
  
  int rank = 7;
  int file = 0;
  
  for (int i = 0; current_position[i] != '\0'; i++) {

    if (state == POSITION) {
      load_position(current_position[i], file, rank);
    }
    
    else if (state == ACTIVE_PLAYER) {

      if (current_position[i] == 'w') {
	      active_player = Colour::WHITE;
	      state = CASTLING;
      }
      else if (current_position[i] == 'b') {
	      active_player = Colour::BLACK;
	      state = CASTLING;
      }
    }
    
    else if (state == CASTLING) {
      
      if (current_position[i] == '-') {
        white_casting = Castling::NIL;
        black_castling = Castling::NIL;
        loading_complete();
        return;
      }

      if (current_position[i] == 'K') white_casting = Castling::KINGSIDE;

      else if (current_position[i] == 'Q') {
        if (current_position[i-1] == 'K') white_casting = Castling::BOTH;
        else white_casting = Castling::QUEENSIDE;
      }

      if (current_position[i] == 'k') black_castling = Castling::KINGSIDE;

      else if (current_position[i] == 'q') {
        if (current_position[i-1] == 'k') black_castling = Castling::BOTH;
        else black_castling = Castling::QUEENSIDE;
        loading_complete();
        return;
      }
    }
  }
}

void ChessGame::submitMove(const char* start_square, const char* end_square) {

  // Check move string format is correct and within board limits
  if (!is_valid_square(start_square) || !is_valid_square(end_square)) {
    cout << "Invalid square" << endl;
    return;
  }

  // Convert sqaure to Position class
  Position start(start_square[0] - 'A', start_square[1] - '1');
  Position end(end_square[0] - 'A', end_square[1] - '1');

  ChessPiece* chess_piece = board[start.get_file()][start.get_rank()];
  ChessPiece* opponent_piece = board[end.get_file()][end.get_rank()];

  // Check if move is a legal chess move
  if (is_legal_move(chess_piece, opponent_piece, start, end)) {

    // Stalemate function will likely be recursive
    output_successful_move(chess_piece, opponent_piece, start, end);

    // Remove captured piece from board
    if (opponent_piece != nullptr) {
      delete opponent_piece;
      opponent_piece = nullptr;
    }

    // Make move
    board[end.get_file()][end.get_rank()] = chess_piece;
    board[start.get_file()][start.get_rank()] = nullptr;

    // Move successfully made, change current player
    if (active_player == Colour::WHITE) active_player = Colour::BLACK;
    else active_player = Colour::WHITE;

    // Check if new active_player is in check
    if (is_check(active_player, board)) {
      cout << active_player << " is in check";
      if (!can_move(active_player, board)) {
        cout << "mate";
        game_over = true;
      }
      cout << endl;
    }
    else if (!can_move(active_player, board)) {
      cout << active_player << " is in stalemate" << endl;
      game_over = true;
    }
  }
}

// HELPER MEHODS

void ChessGame::deallocate_memory(int file, int rank) {
  if (board[file][rank] != nullptr) {
    delete board[file][rank];
  }
}

void ChessGame::load_position(char c, int& file, int& rank) {
  if (c == '/') {
    rank--;
    file = 0;
  }
  
  if (c > '0' && c < '9') {
    int num_blank_squares = c - '0';
    for (int j = 0; j < num_blank_squares; j++) {
      deallocate_memory(file, rank);
      board[file][rank] = nullptr;
      file++;
    }
  }
  
  if (c >= 'B' && c <= 'R') {
    assign_piece(c, file, rank, Colour::WHITE);
  }
  
  if (c >= 'b' && c <= 'r') {
    char uppercase = c - 32; // Converts lowercase char to uppercase char
    assign_piece(uppercase, file, rank, Colour::BLACK);
  }
  
  if (rank == 0 && file == 8) state = ACTIVE_PLAYER;
      
}

void ChessGame::assign_piece(char c, int &file, int rank, Colour colour) {

  deallocate_memory(file, rank);

  switch (c) {
  case 'P':
    {
      Pawn* pawn = new Pawn(colour);
      assert(pawn);
      board[file][rank] = pawn;
      file++;
      break;
    }
  case 'R':
    {
      Rook* rook = new Rook(colour);
      assert(rook);
      board[file][rank] = rook;
      file++;
      break;
    }
  case 'N':
    {
      Knight* knight = new Knight(colour);
      assert(knight);
      board[file][rank] = knight;
      file++;
      break;
    }
  case 'B':
    {
      Bishop* bishop = new Bishop(colour);
      assert(bishop);
      board[file][rank] = bishop;
      file++;
      break;
    }
  case 'Q':
    {
      Queen* queen = new Queen(colour);
      assert(queen);
      board[file][rank] = queen;
      file++;
      break;
    }
  case 'K':
    {
      King* king = new King(colour);
      assert(king);
      board[file][rank] = king;
      file++;
      break;
    }
  default:
    cout << "Char found in string that does not equal a chess piece" << endl;
    assert(false);
  }
}

void ChessGame::loading_complete() {
  cout << "A new board state is loaded!" << endl;

  if (is_check(active_player, board)) {
    if (!can_move(active_player, board)) {
      cout << active_player << " is in checkmate";
      game_over = true;
    }
    cout << endl;
  }
  else if (!can_move(active_player, board)) {
    cout << active_player << " is in stalemate" << endl;
    game_over = true;
  }
}

bool ChessGame::is_valid_square(const char* sqaure) {

  if (strlen(sqaure) != 2) return false;
  if (sqaure[0] < 'A' || sqaure[0] > 'H') return false;
  if (sqaure[1] < '1' || sqaure[1] > '8') return false;

  return true;
}

bool ChessGame::is_legal_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end) {

  // Game is already over
  if (game_over == true) {
    cout << "The game is already over!" << endl;
    return false;
  }

  // No piece at starting location
  if (chess_piece == nullptr) {
    cout << "There is no piece at position " << static_cast<char>(start.get_file() + 'A');
    cout << start.get_rank() + 1 << "!" << endl;
    return false;
  }
  
  // Piece is not active colour
  if (chess_piece->get_colour() != active_player) {
    cout << "It is not " << chess_piece->get_colour();
    cout << "'s turn to move!" << endl;
    return false;
  }

  // Start and end location are the same
  if (start == end) {
    output_unsuccessful_move(chess_piece, start, end);
    return false;
  }
  
  // Opponent piece is the same colour as piece being moved
  if (opponent_piece != nullptr && chess_piece->get_colour() == opponent_piece->get_colour()) {
    output_unsuccessful_move(chess_piece, start, end);
    return false;
  }

  // Try move
  return try_move(chess_piece, start, end, board, true);

}

void ChessGame::output_successful_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end) {

    cout << chess_piece->get_colour() << "'s " << chess_piece->get_type();
    cout << " moves from " << static_cast<char>(start.get_file() + 'A');
    cout << start.get_rank() + 1 << " to " << static_cast<char>(end.get_file() + 'A');
    cout << end.get_rank() + 1;
    
    if (opponent_piece != nullptr && opponent_piece->get_colour() != chess_piece->get_colour()) {
      cout << " taking " << opponent_piece->get_colour() << "'s " << opponent_piece->get_type();
    }

    cout << endl;
}

void ChessGame::output_unsuccessful_move(ChessPiece* chess_piece, Position start, Position end) {
  cout << chess_piece->get_colour() << "'s " << chess_piece->get_type(); 
  cout << " cannot move to " << static_cast<char>(end.get_file() + 'A');
  cout << end.get_rank() + 1 << "!" << endl;
}

bool ChessGame::is_check(Colour _active_player, ChessPiece* b[8][8]) {
  ChessPiece* king = nullptr;
  Position king_position(-1, -1); 

  for (int file = 0; file < 8; file++) {
    for (int rank = 0; rank < 8; rank++) {
      if (b[file][rank] != nullptr) {
        if (b[file][rank]->get_type() == Type::KING && b[file][rank]->get_colour() == _active_player) {
          king_position = Position(file, rank);
          king = b[file][rank];
          break;
        }
      }
    }
  }

  if (king == nullptr || king_position == Position(-1,-1)) {
    cout << "Error: Unable to find king";
    return false;
  }

  if (_active_player == Colour::WHITE) _active_player = Colour::BLACK;
  else _active_player = Colour::WHITE;

  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      if (b[file][rank] != nullptr && b[file][rank]->get_colour() == _active_player) {
        if (b[file][rank]->try_move(Position(file, rank), king_position, b)) return true;
      }
    }
  }
  return false;
}

bool ChessGame::try_move(ChessPiece* chess_piece, Position start, Position end, ChessPiece* b[8][8], bool output) {
  
  if (chess_piece->try_move(start, end, b)) {

    // Check if move puts self in check
    ChessPiece* tmp_board[8][8];
    for (int file = 0; file < 8; file++) {
      for (int rank = 0; rank < 8; rank++) {
        tmp_board[file][rank] = b[file][rank];
      }
    }
    // Make move on tmp_board
    tmp_board[end.get_file()][end.get_rank()] = chess_piece;
    tmp_board[start.get_file()][start.get_rank()] = nullptr;

    if (is_check(active_player, tmp_board)) {
      if (output) output_unsuccessful_move(chess_piece, start, end);
      return false;
    }
    return true;
  }
  
  if (output) output_unsuccessful_move(chess_piece, start, end);
  return false;
}

bool ChessGame::can_move(Colour _active_player, ChessPiece* b[8][8]) {
  
  // Find next active piece
  for (int file = 0; file < 8; file++) {
    for (int rank = 0; rank < 8; rank++) {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (b[file][rank] != nullptr && b[file][rank]->get_colour() == _active_player) {
            if (try_move(b[file][rank], Position(file, rank), Position(i, j), b, false)) return true;
          }
        }
      }
    }
  }  
  return false;
}