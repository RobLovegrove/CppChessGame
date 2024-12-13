#include <iostream>
#include <cstring>
#include <cassert>

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

/* - - - - - - - - - CONSTRUCTOR - - - - - - - - - - - */
ChessGame::ChessGame() {
  for (int file = 0; file < 8; file++){
    for (int rank = 0; rank < 8; rank++) {
      board[file][rank] = nullptr; 
    }
  }
  game_state = NILL;
}

/* - - - - - - - - - DESCTRUCTOR - - - - - - - - - - - */
ChessGame::~ChessGame() {
  for (int file = 0; file < 8; file++){
    for (int rank = 0; rank < 8; rank++) {
      
      // Deallocate memory
      delete board[file][rank];
      board[file][rank] = nullptr;
    }
  }
}

/* - - - - - - - - - LOAD STATE FUNCTIONS - - - - - - - - - - - */

void ChessGame::loadState(const char* FEN_string) {

  game_state = NILL;
  
  int rank = 7;
  int file = 0;
  
  for (int i = 0; FEN_string[i] != '\0'; i++) {    

    if (!game_state) { //If gamestate NILL, parse piece position
      load_position(FEN_string[i], file, rank);
    }
    
    else if (game_state & LOADING_ACTIVE_PLAYER) {
      if (FEN_string[i] == 'w') {
        // Active player set to white by default
	      game_state |= LOADING_CASTLING_RIGHTS;
        game_state &= ~LOADING_ACTIVE_PLAYER;
      }
      else if (FEN_string[i] == 'b') {
        game_state |= BLACKS_TURN;
	      game_state |= LOADING_CASTLING_RIGHTS;
        game_state &= ~LOADING_ACTIVE_PLAYER;
      }
    }
    
    else if (game_state & LOADING_CASTLING_RIGHTS) {
      
      if (FEN_string[i] == '-') {
        // Castling rights set to none as default
        loading_complete();
        return;
      }

      // Add castling rights
      if (FEN_string[i] == 'K') game_state |= WHITE_KINGSIDE;
      else if (FEN_string[i] == 'Q') game_state |= WHITE_QUEENSIDE;
      else if (FEN_string[i] == 'k') game_state |= BLACK_KINGSIDE;
      else if (FEN_string[i] == 'q') game_state |= BLACK_QUEENSIDE;
    }
  }
  
  loading_complete();
}


/* - - - - - - - - - LOAD STATE HELPER FUNCTIONS - - - - - - - - - - - */

void ChessGame::load_position(const char c, int& file, int& rank) {

  if (c == '/') {
    rank--;
    file = 0;
  }
  
  if (c > '0' && c < '9') {
    int num_blank_squares = c - '0';
    for (int j = 0; j < num_blank_squares; j++) {
      // Deallocate memory
      delete board[file][rank];
      board[file][rank] = nullptr;
      file++;
    }
  }
  
  if (c >= 'B' && c <= 'R') {
    assign_piece(c, file, rank, Colour::WHITE);
  }
  
  if (c >= 'b' && c <= 'r') {
    char uppercase = toupper(c);
    assign_piece(uppercase, file, rank, Colour::BLACK);
  }
  
  if (rank == 0 && file == 8) game_state |= LOADING_ACTIVE_PLAYER;
      
}

void ChessGame::assign_piece(
  const char c, int &file, const int rank, const Colour &colour) {

  // Deallocate memory
  delete board[file][rank];
  board[file][rank] = nullptr;

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

  // Check whether the newly loaded game is already in checkmate/stalemate 
  if (is_check()) {
    cout << static_cast<Colour>(game_state & BLACKS_TURN) << " is in check";
    if (!can_move()) {
      cout << "mate";
      game_state |= GAME_OVER;
    }
    cout << endl;
  }
  else if (!can_move()) {
    cout << static_cast<Colour>(game_state & BLACKS_TURN);
    cout << " is in stalemate" << endl;
    game_state |= GAME_OVER;
  }
}


/* - - - - - - - - - SUBMIT MOVE FUNCTIONS - - - - - - - - - - - */

void ChessGame::submitMove(const char* start_square, const char* end_square) {

  // Ensure a game has been loaded
  if (!(game_state & LOADING_CASTLING_RIGHTS)) {
    cout << "No game has been loaded in!" << endl;
    return;
  }
  
  // Check move string format is correct and within board limits
  if (!is_valid_square(start_square) || !is_valid_square(end_square)) {
    cout << "Invalid square" << endl;
    return;
  }

  // Convert sqaure to Position class
  Position start(start_square[0] - 'A', start_square[1] - '1');
  Position end(end_square[0] - 'A', end_square[1] - '1');

  // Check if move is a legal chess move
  if (is_legal_move(start, end, true)) {
     
    update_castling_rights(start, end);

    if (attempting_castling != NILL) {
      castle();
    }
    else {
      make_move(start, end);
    }

    // Change active player
    if (game_state & BLACKS_TURN) game_state &= ~BLACKS_TURN; 
    else game_state |= BLACKS_TURN;

    // Check if new active player is in check/checkmate/stalemate
    if (is_check()) {
      cout << static_cast<Colour>(game_state & BLACKS_TURN) << " is in check";
      if (!can_move()) {
        cout << "mate";
        game_state |= GAME_OVER;
      }
      cout << endl;
    }
    else if (!can_move()) {
      cout << static_cast<Colour>(game_state & BLACKS_TURN);
      cout << " is in stalemate" << endl;
      game_state |= GAME_OVER;
    }
  }
}

/* - - - - - - - - - SUBMIT MOVE HELPER FUNCTIONS - - - - - - - - - - - */

bool ChessGame::is_valid_square(const char* sqaure) const {

  if (strlen(sqaure) != 2) return false;
  if (sqaure[0] < 'A' || sqaure[0] > 'H') return false;
  if (sqaure[1] < '1' || sqaure[1] > '8') return false;

  return true;
}

bool ChessGame::is_legal_move(Position start, Position end, bool output) {

  ChessPiece* player = board[start.get_file()][start.get_rank()];

  if (!check_basic_rules(start, end, output)) return false;

  // Ensure piece is active player
  if (*player != (game_state & BLACKS_TURN)) {
    cout << "It is not " << player->get_colour() << "'s turn to move!" << endl;
    return false;
  }
  
  // Validate ChessPiece can path from start to end
  if (!player->try_move(start, end, board, &attempting_castling)) {
    // ChessPiece cannot path form start to end
    if (output) output_unsuccessful_move(start, end);
    return false;
  }

  if (attempting_castling != NILL) {
    // Ensure castling does not pass through check
    return is_castling_legal(start, end, output);
  }

  else {
    
    // Not castling so check if move puts self in check
    ChessPiece* target = board[end.get_file()][end.get_rank()];

    // Make move first - will undo this move after 
    board[end.get_file()][end.get_rank()] = player;
    board[start.get_file()][start.get_rank()] = nullptr;

    // Ensure move does not put self in check
    if (is_check()) {

      // Undo move
      board[end.get_file()][end.get_rank()] = target;
      board[start.get_file()][start.get_rank()] = player;

      if (output) output_unsuccessful_move(start, end);
      return false;
    }

    // Undo move
    board[end.get_file()][end.get_rank()] = target;
    board[start.get_file()][start.get_rank()] = player;
  }
  return true;

}

bool ChessGame::check_basic_rules(
  Position start, Position end, bool output) const {

  ChessPiece* player = board[start.get_file()][start.get_rank()];
  ChessPiece* opponent = board[end.get_file()][end.get_rank()];

  // Game is already over
  if (game_state & GAME_OVER) {
    if (output) cout << "The game is already over!" << endl;
    return false;
  }

  // No piece at starting location
  if (player == nullptr) {
    if (output)
    cout << "There is no piece at position " << start << "!" << endl;
    return false;
  }

  // Start and end location are the same
  if (start == end) {
    if (output) output_unsuccessful_move(start, end);
    return false;
  }
  
  // Opponent piece is the same colour as piece being moved
  if (opponent != nullptr && player->get_colour() == opponent->get_colour()) {
    // Castling allowed by moving rook onto king or king onto rook
    // Therefore ignore rooks and kings
    if (!dynamic_cast<Rook*>(player) && !dynamic_cast<King*>(player)) {

      if (output) output_unsuccessful_move(start, end);
      return false;
    }
  }

  return true;
}

bool ChessGame::is_castling_legal(Position start, Position end, bool output) {

  // Check if king has appropriate castling rights
  // Attempting_castling flag changed by King/Rook if castling path possible 
  if (!(game_state & attempting_castling)) { 
    if (output) output_unsuccessful_move(start, end);
    // Reset attempting_castling and return false
    attempting_castling = NILL;
    return false;
  }

  int rank = 0, increment = -1;
  if (game_state & BLACKS_TURN) rank = 7;
  if (attempting_castling & WHITE_KINGSIDE || 
      attempting_castling & BLACK_KINGSIDE) {
    increment = 1;
  }

  // Check if king starts in check
  if (is_check()) {
    if (output) output_unsuccessful_move(start, end);
    attempting_castling = NILL;
    return false;
  }
  for (int i = 1; i < 3; i++) {
    Position target(4 + (i*increment), rank);

    // Check whether square king passes through/finishes on is attacked
    if (is_square_attacked(target)) {
      if (output) output_unsuccessful_move(start, end);
      attempting_castling = NILL;
      return false;
    }
  }
  return true;
}

bool ChessGame::is_check() {

  ChessPiece* king = nullptr;
  Position king_position(-1, -1); 

  // Find king's position
  for (int file = 0; file < 8; file++) {
    for (int rank = 0; rank < 8; rank++) {
      if (board[file][rank] != nullptr) {
        if (dynamic_cast<King*>(board[file][rank]) && 
          *board[file][rank] == (game_state & BLACKS_TURN)) {
          king_position = Position(file, rank);
          king = board[file][rank];
          break;
        }
      }
    }
  }

  if (king == nullptr || king_position == Position(-1,-1)) {
    cout << "Error: Unable to find king";
    return false;
  }

  return is_square_attacked(king_position);
}

bool ChessGame::is_square_attacked(Position target) {
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      if (board[file][rank] != nullptr && 
      *board[file][rank] != (game_state & BLACKS_TURN)) {

        if (check_basic_rules(Position(file, rank), target, false)) {
          if (board[file][rank]->try_move(Position(file, rank), target, board))
            return true;
        }
      }
    }
  }
  return false;
}

bool ChessGame::can_move() {

  // Find next active piece
  for (int file = 0; file < 8; file++) {
    for (int rank = 0; rank < 8; rank++) {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          // ChessPiece == operator overloaded 
          // Compares piece colour with active_player flag
          if (board[file][rank] != nullptr && 
            *board[file][rank] == (game_state & BLACKS_TURN)) {
            if (is_legal_move(Position(file, rank), Position(i, j), false)) 
              return true;
          }
        }
      }
    }
  }  
  return false;
}

void ChessGame::update_castling_rights(Position start, Position end) {

  ChessPiece* player = board[start.get_file()][start.get_rank()];
  ChessPiece* opponent = board[end.get_file()][end.get_rank()];

  // Bitwise removal of castling rights on king move
  if (dynamic_cast<King*>(player)) {
    if (game_state & BLACKS_TURN) 
      game_state &= ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);

    else game_state &= ~(WHITE_KINGSIDE | WHITE_QUEENSIDE);
  }

  // Update castling state on rook move
  if (dynamic_cast<Rook*>(player)) {
    if (opponent != nullptr) {
      if (*opponent == (game_state & BLACKS_TURN) && 
          dynamic_cast<King*>(opponent)) {

        // Castling by moving rook onto own king, so remove all castling rights
        if (game_state & BLACKS_TURN) 
          game_state &= ~(BLACK_KINGSIDE | BLACK_QUEENSIDE);

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

  if (dynamic_cast<Rook*>(opponent)) {
    // Capturing opponent rook, if rook in corner remove castling right
    int rank;
    (game_state & BLACKS_TURN) ? rank = 0 : rank = 7;
    if (Position(0, rank) == end) {
      // Remove queenside castling rights of non active player
      if (game_state & BLACKS_TURN) game_state &= ~WHITE_QUEENSIDE;
      else game_state &= ~BLACK_QUEENSIDE;
    }
    else if (Position(7, rank) == end) {
      // Remove kingside castling rights of non active player
      if (game_state & BLACKS_TURN) game_state &= ~WHITE_KINGSIDE;
      else game_state &= ~BLACK_QUEENSIDE;
    }
  }
}

void ChessGame::castle() {

  // Determine castling direction
  int rank = 0, king_end = 2, rook_start = 0, rook_end = 3;
  char side[10] = "queenside";
  if (game_state & BLACKS_TURN) rank = 7;
  if (attempting_castling & WHITE_KINGSIDE || 
      attempting_castling & BLACK_KINGSIDE) {

    king_end = 6;
    rook_start = 7;
    rook_end = 5;
    strcpy (side, "kingside");
  }

  // Move king
  board[king_end][rank] = board[4][rank];
  board[4][rank] = nullptr;

  // Move rook
  board[rook_end][rank] = board[rook_start][rank];
  board[rook_start][rank] = nullptr;

  // Output player castling
  cout << static_cast<Colour>(game_state & BLACKS_TURN) << " castles ";
  cout << side << endl;

  // Reset attempting_castling
  attempting_castling = NILL;
}

void ChessGame::make_move(Position start, Position end) {
  
  ChessPiece* player = board[start.get_file()][start.get_rank()];
  ChessPiece* opponent = board[end.get_file()][end.get_rank()];

  output_successful_move(start, end);

  // Remove captured piece from board
  if (opponent != nullptr) {




    delete opponent;
    opponent = nullptr;
  }

  // Make move
  board[end.get_file()][end.get_rank()] = player;
  board[start.get_file()][start.get_rank()] = nullptr;
}

void ChessGame::output_successful_move(Position start, Position end) const {

  ChessPiece* player = board[start.get_file()][start.get_rank()];
  ChessPiece* opponent = board[end.get_file()][end.get_rank()];

  cout << *player << " moves from " << start << " to " << end;
  if (opponent != nullptr && opponent->get_colour() != player->get_colour()) {
    cout << " taking " << *opponent;
  }
  cout << endl;
}

void ChessGame::output_unsuccessful_move(Position start, Position end) const {

  ChessPiece* player = board[start.get_file()][start.get_rank()];
  cout << *player << " cannot move to " << end << "!" << endl;
}

void ChessGame::display_board() {
  const char* horizontal_border = "  +---+---+---+---+---+---+---+---+"; 
  
  for (int rank = 7; rank >= 0; rank--) { 
    cout << horizontal_border << endl;
    cout << rank+1 << " |";
    for (int file = 0; file < 8; file++) { 
      ChessPiece* piece = board[file][rank];
      
      if (piece == nullptr) {
	      cout << "   |"; 
      }
      else {
	      const char* name = piece->get_type();
	      char ch = (name[0] == 'K' && name[1] == 'n') ? 'N' : name[0];
	      Colour colour = piece->get_colour();
	      char p = (colour == Colour::WHITE
		      ? static_cast<char>(toupper(ch)) : static_cast<char>(tolower(ch)));    
	      cout << " " << p << " |"; 
      }
    }
    cout << endl;
  }
  
  cout << horizontal_border << endl; 
  cout << "    A   B   C   D   E   F   G   H " << endl << endl;
}
