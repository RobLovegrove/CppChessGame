#include <iostream>
#include <cstring>
#include <cassert>

// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq

#include "ChessGame.h"
#include "Colour.h"
#include "Position.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

using namespace std;

// DESTRUCTORS

ChessGame::~ChessGame() {
  for (int file = 0; file < 8; file++){
    for (int rank = 0; rank < 8; rank++) {
      if (board[file][rank] != NULL) {
	delete board[file][rank];
      }
    }
  }
}

// METHODS

void ChessGame::loadState(const char* current_position) {

  enum {POSITION, ACTIVE_PLAYER, CASTLING, FINISHED} state = POSITION;
  
  int rank = 7;
  int file = 0;
  
  for (int i = 0; current_position[i] != '\0'; i++) {

    if (state == POSITION) {
      
      if (current_position[i] == '/') {
	rank--;
	file = 0;
      }
      
      if (current_position[i] > '0' && current_position[i] < '9') {
	int num_blank_squares = current_position[i] - '0';
	for (int j = 0; j < num_blank_squares; j++) {
	  board[file][rank] = NULL;
	  cout << "empty " << file << rank << endl;
	  file++;
	}
      }
      
      if (current_position[i] >= 'B' && current_position[i] <= 'R') {
	assign_piece(current_position[i], file, rank, Colour::WHITE);
      }
      
      if (current_position[i] >= 'b' && current_position[i] <= 'r') {
	char uppercase = current_position[i] - 32;
	assign_piece(uppercase, file, rank, Colour::BLACK);
      }
      
      if (rank == 0 && file == 8) state = ACTIVE_PLAYER;
      
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
      // CONSIDER Implementing this at a later date
      state = FINISHED;
    }

    else if (state == FINISHED) {
      cout << "A new board state is loaded!" << endl;
      return;
    }
  }
}

void ChessGame::submitMove(const char* start_square, const char* end_square) {

  // Check move string format is correct and within board limits
  if (!is_valid_square(start_square) || !is_valid_square(end_square)) {
    cout << "Invalid square" << endl;
  }

  // Convert sqaure to Position class
  Position start(start_square[0] - 'A', start_square[1] - '1');
  Position end(end_square[0] - 'A', end_square[1] - '1');

  // Check if move is a legal chess move
  is_legal_move(start, end);

  
}

// HELPER MEHODS

void ChessGame::assign_piece(char c, int &file, int rank, Colour colour) {

  switch (c) {
  case 'P':
    {
      Pawn* pawn = new Pawn(colour);
      board[file][rank] = pawn;
      cout << "pawn " << file << rank << endl;
      file++;
      break;
    }
  case 'R':
    {
      Rook* rook =  new Rook(colour);
      board[file][rank] = rook;
      cout << "rook " << file << rank << endl;
      file++;
      break;
    }
  case 'N':
    {
      Knight* knight =  new Knight(colour);
      board[file][rank] = knight;
      cout << "knight " << file << rank << endl;
      file++;
      break;
    }
  case 'B':
    {
      Bishop* bishop = new Bishop(colour);
      board[file][rank] = bishop;
      cout << "bishop " << file << rank << endl;
      file++;
      break;
    }
  case 'Q':
    {
      Queen* queen = new Queen(colour);
      board[file][rank] = queen;
      cout << "queen " << file << rank << endl;
      file++;
      break;
    }
  case 'K':
    {
      King* king = new King(colour);
      board[file][rank] = king;
      cout << "king " << file << rank << endl;
      file++;
      break;
    }
  default:
    cout << "Char found in string that does not equal a chess piece" << endl;
    assert(false);
  }
}


// ??COMPLETE THIS

bool ChessGame::is_valid_square(const char* sqaure) {

  if (strlen(sqaure) != 2) return false;

  return true;
  
}

void ChessGame::is_legal_move(Position start, Position end) {
  
  // No piece at location
  if (board[start.get_file()][start.get_rank()] == NULL) {
    cout << "There is no piece at position " << static_cast<char>(start.get_file() + 'A');
    cout << start.get_rank() + 1 << "!\n" << endl;
    return;
  }
  
  // Piece is not active colour
  if (board[start.get_file()][start.get_rank()]->get_colour() != active_player) {
    cout << "It is not " << board[start.get_file()][start.get_rank()]->get_colour();
    cout << "'s turn to move!" << endl;
    return;
  }
  
  // Try move
  if (board[start.get_file()][start.get_rank()]->try_move(start, end, board)) {
    cout << board[start.get_file()][start.get_rank()]->get_colour() << "'s ";
    cout << "Pawn" << " moves from " << static_cast<char>(start.get_file() + 'A');
    cout << start.get_rank() + 1 << " to " << static_cast<char>(end.get_file() + 'A');
    cout << end.get_rank() + 1 << endl;
							  
  }
}

