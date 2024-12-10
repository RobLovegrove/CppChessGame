#include <iostream>
#include <cstring>
#include <cassert>
#include <bitset>

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
  game_state = NILL;
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

void ChessGame::loadState(const char* current_char) {

  game_state = NILL;
  
  int rank = 7;
  int file = 0;
  
  for (int i = 0; current_char[i] != '\0'; i++) {    

    if (!game_state) { //If gamestate NILL, parse piece position
      load_position(current_char[i], file, rank);
    }
    
    else if (game_state & LOADING_ACTIVE_PLAYER) {
      if (current_char[i] == 'w') {
        // Active player set to white by default
	      game_state |= LOADING_CASTLING_RIGHTS;
        game_state &= ~LOADING_ACTIVE_PLAYER;
      }
      else if (current_char[i] == 'b') {
        game_state |= BLACKS_TURN;
	      game_state |= LOADING_CASTLING_RIGHTS;
        game_state &= ~LOADING_ACTIVE_PLAYER;
      }
    }
    
    else if (game_state & LOADING_CASTLING_RIGHTS) {
      
      if (current_char[i] == '-') {
        // Castling rights set to none as default
        loading_complete();
        return;
      }

      // Add castling rights
      if (current_char[i] == 'K') game_state |= WHITE_KINGSIDE;
      else if (current_char[i] == 'Q') game_state |= WHITE_QUEENSIDE;
      else if (current_char[i] == 'k') game_state |= BLACK_KINGSIDE;
      else if (current_char[i] == 'q') game_state |= BLACK_QUEENSIDE;
    }
  }
  loading_complete();
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
  ChessPiece* target_piece = board[end.get_file()][end.get_rank()];

  // Check if move is a legal chess move
  if (is_legal_move(chess_piece, target_piece, start, end)) {
     
    if (attempting_castling != NILL) {
      // Castling
      switch (attempting_castling)
      {
      case WHITE_KINGSIDE:
        // Move king
        board[6][0] = board[4][0];
        board[4][0] = nullptr;
        // Move rook
        board[5][0] = board[7][0];
        board[7][0] = nullptr;
        cout << chess_piece->get_colour() << " castles kingside";
        break;
      case WHITE_QUEENSIDE:
        // Move king
        board[2][0] = board[4][0];
        board[4][0] = nullptr;
        // Move rook
        board[3][0] = board[0][0];
        board[0][0] = nullptr;
        cout << chess_piece->get_colour() << " castles queenside";
        break;
      case BLACK_KINGSIDE:
        // Move king
        board[6][7] = board[4][7];
        board[4][7] = nullptr;
        // Move rook
        board[5][7] = board[7][7];
        board[7][7] = nullptr;
        cout << chess_piece->get_colour() << " castles kingside";
        break;
      case BLACK_QUEENSIDE:
        // Move king
        board[2][7] = board[4][7];
        board[4][7] = nullptr;
        // Move rook
        board[3][7] = board[0][7];
        board[0][7] = nullptr;
        cout << chess_piece->get_colour() << " castles queenside";
        break;
      default:
        cout << "Error not passed correct castling type";
        break;
      }
      // Reset attempting_castling
      attempting_castling = NILL;
    }
    else {
      output_successful_move(chess_piece, target_piece, start, end);

      // Remove captured piece from board
      if (target_piece != nullptr) {
        delete target_piece;
        target_piece = nullptr;
      }

      // Make move
      board[end.get_file()][end.get_rank()] = chess_piece;
      board[start.get_file()][start.get_rank()] = nullptr;

    }

    // Bitwise removal of castling rights on king move
    if (chess_piece->get_type() == Type::KING) {
      if (game_state & BLACKS_TURN) game_state &= ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);
      else game_state &= ~(WHITE_KINGSIDE | WHITE_QUEENSIDE);
    }

    // Update castling state on rook move
    if (chess_piece->get_type() == Type::ROOK) {
      if (target_piece != nullptr) {
        if (*target_piece == (game_state & BLACKS_TURN) && target_piece->get_type() == Type::KING) {
          // Castling by moving rook onto own king, so remove all castling rights
          if (game_state & BLACKS_TURN) game_state &= ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);
          else game_state &= ~(WHITE_KINGSIDE | WHITE_QUEENSIDE);
        }
      } 
      else {
        int rank;
        (game_state & BLACKS_TURN) ? rank = 7 : rank = 0;
        if (start == Position(0, rank)) {
          // Btiwise removal of queenside castling rights
          if (game_state & BLACKS_TURN) game_state &= ~BLACK_QUEENSIDE;
          else game_state &= ~WHITE_QUEENSIDE;
        }
        else if (start == Position(7, rank)) {
          // Btiwise removal of kingside castling rights
          if (game_state & BLACKS_TURN) game_state &= ~BLACK_KINGSIDE;
          else game_state &= ~WHITE_KINGSIDE;
        }
      }
    }

    // Move successfully made, change current player
    if (game_state & BLACKS_TURN) game_state &= ~BLACKS_TURN;
    else game_state |= BLACKS_TURN;

    // Check if new active_player is in check
    if (is_check(board)) {
      cout << static_cast<Colour>(game_state & BLACKS_TURN) << " is in check";
      if (!can_move(board)) {
        cout << "mate";
        game_state |= GAME_OVER;
      }
      cout << endl;
    }
    else if (!can_move(board)) {
      cout << static_cast<Colour>(game_state & BLACKS_TURN) << " is in stalemate" << endl;
      game_state |= GAME_OVER;
    }
  }
}

// HELPER METHODS
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
  
  if (rank == 0 && file == 8) game_state |= LOADING_ACTIVE_PLAYER;
      
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
  if (is_check(board)) {
    if (!can_move(board)) {
      cout << static_cast<Colour>(game_state & BLACKS_TURN) << " is in checkmate";
      game_state |= GAME_OVER;
    }
    cout << endl;
  }
  else if (!can_move(board)) {
    cout << static_cast<Colour>(game_state & BLACKS_TURN) << " is in stalemate" << endl;
    game_state |= GAME_OVER;
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
  if (game_state & GAME_OVER) {
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
  if (*chess_piece != (game_state & BLACKS_TURN)) {
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
    // Castling allowed by moving rook onto king or king onto rook so ignore rooks and kings
    if (chess_piece->get_type() != Type::ROOK && chess_piece->get_type() != Type::KING) {
      output_unsuccessful_move(chess_piece, start, end);
      return false;
    }
  }
  
  // Try move
  return try_move(chess_piece, start, end, board, true);

}

void ChessGame::output_successful_move(ChessPiece* chess_piece, ChessPiece* opponent_piece, Position start, Position end) {

  cout << *chess_piece << " moves from " << start << " to " << end;
  if (opponent_piece != nullptr && opponent_piece->get_colour() != chess_piece->get_colour()) {
    cout << " taking " << *opponent_piece;
  }
  cout << endl;
}

void ChessGame::output_unsuccessful_move(ChessPiece* chess_piece, Position start, Position end) {
  cout << *chess_piece << " cannot move to " << end << "!" << endl;
}

bool ChessGame::is_check(ChessPiece* b[8][8]) const {
  ChessPiece* king = nullptr;
  Position king_position(-1, -1); 

  for (int file = 0; file < 8; file++) {
    for (int rank = 0; rank < 8; rank++) {
      if (b[file][rank] != nullptr) {
        if (b[file][rank]->get_type() == Type::KING && *b[file][rank] == (game_state & BLACKS_TURN)) {
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

  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      if (b[file][rank] != nullptr && *b[file][rank] != (game_state & BLACKS_TURN)) {
        if (b[file][rank]->try_move(Position(file, rank), king_position, b, this)) return true;
      }
    }
  }
  return false;
}

bool ChessGame::try_move(ChessPiece* chess_piece, Position start, Position end, ChessPiece* b[8][8], bool output) {
  
  if (chess_piece->try_move(start, end, b, this, &attempting_castling)) {

    // Check if trying to castle
    if (attempting_castling != NILL) {
      // Trying to castle 
      // Direction and colour of castling set by king/rook to attempting_castling
      if (!(game_state & attempting_castling)) { 
        if (output) output_unsuccessful_move(chess_piece, start, end);
        attempting_castling = NILL;
        return false;
      }
    }
    else {
      // Not castling so check if move puts self in check
      ChessPiece* tmp_board[8][8];
      for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {
          tmp_board[file][rank] = b[file][rank];
        }
      }
      // Make move on tmp_board
      tmp_board[end.get_file()][end.get_rank()] = chess_piece;
      tmp_board[start.get_file()][start.get_rank()] = nullptr;

      // Ensure move does not put self in check
      if (is_check(tmp_board)) {
        if (output) output_unsuccessful_move(chess_piece, start, end);
        return false;
      }
    }
    return true;
  }
  
  if (output) output_unsuccessful_move(chess_piece, start, end);
  return false;
}

bool ChessGame::can_move(ChessPiece* b[8][8]) {

  // Find next active piece
  for (int file = 0; file < 8; file++) {
    for (int rank = 0; rank < 8; rank++) {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (b[file][rank] != nullptr && *b[file][rank] == (game_state & BLACKS_TURN)) {
            if (try_move(b[file][rank], Position(file, rank), Position(i, j), b, false)) return true;
          }
        }
      }
    }
  }  
  return false;
}

void ChessGame::print_board() {
  for (int rank = 7; rank >= 0; rank --){
    for (int file = 0; file < 8; file ++) {
      if (board[file][rank] != nullptr) {
        cout << board[file][rank]->get_type() << ", ";
      }
      else{
        cout << "Empty square, ";
      }
    }
    cout << endl;
  }
}