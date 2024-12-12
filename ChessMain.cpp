#include"ChessGame.h"

#include<iostream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";
	ChessGame cg;

	cg.submitMove("A2", "A4");
	
	// Testing Pawn
	cout << "\nTesting Pawn" << std::endl;
	cg.loadState("2K5/pppppppp/8/8/P1k5/1nb5/P7/8 w KQkq");

	//cg.display_board();
	cg.submitMove("A2", "C3");
	//cg.display_board();
	cg.submitMove("A4", "A3");
	//cg.display_board();
	cg.submitMove("A2", "B2");
	//cg.display_board();
	cg.submitMove("A2", "B3");
	//cg.display_board();
	cg.submitMove("A7", "A5");
	//cg.display_board();
	cg.submitMove("C4", "D5");
	//cg.display_board();
	cg.submitMove("A4", "A5");
	//cg.display_board();
	cg.submitMove("A7", "A5");
	//cg.display_board();
	cg.submitMove("H7", "H5");
	//cg.display_board();

	// Testing Rook
	cout << "\nTesting Rook" << std::endl;
	cg.loadState("7r/R7/r7/8/1K1k4/8/8/R7 w KQkq");
	//cg.display_board();
	cg.submitMove("A1", "B3");
	//cg.display_board();
	cg.submitMove("A1", "A3");
	//cg.display_board();
	cg.submitMove("H8", "A8");
	//cg.display_board();
	cg.submitMove("A3", "A8");
	//cg.display_board();
	cg.submitMove("A3", "A7");
	//cg.display_board();
	cg.submitMove("A3", "A6");

	// Testing Knight
	cout << "\nTesting Knight" << std::endl;
	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	//cg.display_board();
	cg.submitMove("B1", "B3");
	//cg.display_board();
	cg.submitMove("B1", "D3");
	//cg.display_board();
	cg.submitMove("B1", "C3");
	//cg.display_board();
	cg.submitMove("G8", "G6");
	//cg.display_board();
	cg.submitMove("G8", "F6");
	//cg.display_board();
	cg.submitMove("C3", "D5");
	//cg.display_board();
	cg.submitMove("B8", "C6");
	//cg.display_board();
	cg.submitMove("D5", "F6");
	//cg.display_board();

	// Testing Bishop
	cout << "\nTesting Bishop" << std::endl;
	cg.loadState("rnbqkbnr/ppp2ppp/8/8/8/8/P1PPPP1P/RNBQKBNR w KQkq");
	//cg.display_board();
	cg.submitMove("C1", "C5");
	//cg.display_board();
	cg.submitMove("C1", "E3");
	//cg.display_board();
	cg.submitMove("C1", "F1");
	//cg.display_board();
	cg.submitMove("C1", "A3");
	//cg.display_board();
	cg.submitMove("F8", "C5");
	//cg.display_board();
	cg.submitMove("A3", "C5");
	//cg.display_board();
	cg.submitMove("C8", "G4");
	//cg.display_board();
	cg.submitMove("F1", "H3");
	//cg.display_board();
	cg.submitMove("G4", "E2");
	//cg.display_board();
	cg.submitMove("H3", "D6");
	//cg.display_board();
	cg.submitMove("H3", "C8");
	//cg.display_board();
	cg.submitMove("E2", "E2");
	//cg.display_board();
	cg.submitMove("E2", "B5");
	//cg.display_board();
	cg.submitMove("C8", "D7");
	//cg.display_board();
	cg.submitMove("B5", "D7");
	//cg.display_board();

	// Testing Queen
	cout << "\nTesting Queen" << std::endl;
	cg.loadState("rnbqkbnr/ppp2ppp/8/8/8/8/PPP2PPP/RNBQKBNR w KQkq");
	//cg.display_board();
	cg.submitMove("D1", "C2");
	//cg.display_board();
	cg.submitMove("D1", "D4");
	//cg.display_board();
	cg.submitMove("D8", "D6");
	//cg.display_board();
	cg.submitMove("D4", "H8");
	//cg.display_board();
	cg.submitMove("D4", "F6");
	//cg.display_board();
	cg.submitMove("D6", "E6");
	//cg.display_board();
	cg.submitMove("F6", "E6");
	//cg.display_board();

	// Testing King
	cout << "\nTesting King" << std::endl;
	cg.loadState("rnbqkbnr/ppp3pp/8/8/8/8/PPP2PPP/RNBQKBNR w KQkq");
	//cg.display_board();
	cg.submitMove("E1", "C2");
	//cg.display_board();
	cg.submitMove("E1", "E2");
	//cg.display_board();
	cg.submitMove("E8", "D7");
	//cg.display_board();
	cg.submitMove("E8", "F7");
	//cg.display_board();

	// CHECKMATE EXAMPLE

	cout << "\nTesting checkmate" << std::endl;
	cg.loadState("8/8/8/5K1k/8/8/8/6R1 w KQkq");
	cout << '\n';
	//cg.display_board();
	cg.submitMove("G1", "H1");
	cg.submitMove("H5", "H6");
	cout << '\n';
	//cg.display_board();

	// STALEMATE EXAMPLE
	cout << "\nTesting stalemate" << std::endl;
	cg.loadState("5k2/5P2/4K3/8/8/8/8/8 w KQkq");
	cout << '\n';
	//cg.display_board();
	cg.submitMove("E6", "F6");
	cout << '\n';
	//cg.display_board();

	// CASTLING EXAMPLE
	// Kingside with rook
	cout << "\nTesting Castling" << std::endl;
	cg.loadState("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq");
	cout << '\n';
	cg.display_board();
	cg.submitMove("H1", "E1");
	cg.display_board();
	cg.submitMove("H8", "E8");
	cout << '\n';
	cg.display_board();

	// Queenside with King
	cg.loadState("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq");
	cout << '\n';
	cg.display_board();
	cg.submitMove("E1", "A1");
	cg.display_board();
	cg.submitMove("E8", "B8");
	cout << '\n';
	cg.display_board();

	// Queenside through check
	cg.loadState("r3k2r/8/4R3/8/8/r7/8/R3K2R w KQkq");
	cout << '\n';
	cg.display_board();
	cg.submitMove("E1", "A1");
	cg.display_board();
	cg.submitMove("E8", "B8");
	cout << '\n';
	cg.display_board();

	// Kingside through check
	cg.loadState("rnbqkbnr/pppppppp/8/8/8/5r2/8/R3K2R w KQkq");
	cout << '\n';
	cg.display_board();
	cg.submitMove("E1", "G1");
	cg.display_board();
	cg.submitMove("E1", "B1");
	cout << '\n';
	cg.display_board();

	// Queenside through check
	cg.loadState("rnbqkbnr/pppppppp/8/8/8/3r4/8/R3K2R w KQkq");
	cout << '\n';
	cg.display_board();
	cg.submitMove("E1", "A1");
	cout << '\n';
	cg.display_board();

	// Queenside not through check
	cg.loadState("rnbqkbnr/pppppppp/8/8/8/r7/8/R3K2R w KQkq");
	cout << '\n';
	cg.display_board();
	cg.submitMove("E1", "A1");
	cout << '\n';
	cg.display_board();

	// Queenside through check
	cg.loadState("r3k2r/pppppppp/8/8/8/3r4/8/R3K2R w KQkq");
	cout << '\n';
	cg.display_board();
	cg.submitMove("E1", "E2");
	cg.display_board();
	cg.submitMove("H8", "G8");
	cg.display_board();
	cg.submitMove("E2", "E1");
	cg.display_board();
	cg.submitMove("G8", "H8");
	cg.display_board();
	cg.submitMove("E1", "G1");
	cg.display_board();
	cg.submitMove("E1", "F1");
	cg.display_board();
	cg.submitMove("E8", "G8");
	cout << '\n';
	cg.display_board();

	// PRE GIVEN TESTS
	cout << "Pre-provided Tests" << std::endl;
	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';
	//cg.display_board();
	cg.submitMove("D7", "D6");
	cout << '\n';
	//cg.display_board();
	cg.submitMove("D4", "H6");
	cout << '\n';
	//cg.display_board();
	cg.submitMove("D2", "D4");
	cout << '\n';
	//cg.display_board();
	cg.submitMove("F8", "B4");
	cout << '\n';
	//cg.display_board();

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("E2", "E4");
	cg.submitMove("E7", "E6");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("D2", "D4");
	cg.submitMove("D7", "D5");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("B1", "C3");
	cg.submitMove("F8", "B4");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("F1", "D3");
	cg.submitMove("B4", "C3");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("B2", "C3");
	cg.submitMove("H7", "H6");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("C1", "A3");
	cg.submitMove("B8", "D7");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("D1", "E2");
	cg.submitMove("D5", "E4");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("D3", "E4");
	cg.submitMove("G8", "F6");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("E4", "D3");
	cg.submitMove("B7", "B6");
	cout << '\n';

	//cg.display_board();
	cg.submitMove("E2", "E6");
	cg.submitMove("F7", "E6");
	cout << '\n';
	
	//cg.display_board();
	cg.submitMove("D3", "G6");
	cout << '\n';

	//cg.display_board();

	return 0;
}
