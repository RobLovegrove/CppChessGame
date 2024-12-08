#include"ChessGame.h"

#include<iostream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";
	ChessGame cg;
	/*
	// CHECKMATE EXAMPLE
	cg.loadState("8/8/8/5K1k/8/8/8/6R1 w KQkq");
	cout << '\n';

	cg.submitMove("G1", "H1");
	cout << '\n';

	cg.submitMove("H5", "H6");
	cout << '\n';
	// STALEMATE EXAMPLE
	cg.loadState("5k2/5P2/4K3/8/8/8/8/8 w KQkq");
	cout << '\n';

	cg.submitMove("E6", "F6");
	cout << '\n';
	*/
	
/*
	cg.loadState("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq");
	cout << '\n';
	cg.submitMove("H1", "E1");
	cout << '\n';

	cg.print_board();
	cg.submitMove("E8", "H8");
	cout << '\n';

	cg.submitMove("F1", "H1");
	cout << '\n';

	cg.submitMove("G8", "H8");
	cout << '\n';

	cg.submitMove("E1", "G1");
	cout << '\n';

	cg.print_board();
*/

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	cg.submitMove("D7", "D6");
	cout << '\n';

	cg.submitMove("D4", "H6");
	cout << '\n';

	cg.submitMove("D2", "D4");
	cout << '\n';

	cg.submitMove("F8", "B4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	cg.submitMove("E2", "E4");
	cg.submitMove("E7", "E6");
	cout << '\n';

	cg.submitMove("D2", "D4");
	cg.submitMove("D7", "D5");
	cout << '\n';

	cg.submitMove("B1", "C3");
	cg.submitMove("F8", "B4");
	cout << '\n';

	cg.submitMove("F1", "D3");
	cg.submitMove("B4", "C3");
	cout << '\n';

	cg.submitMove("B2", "C3");
	cg.submitMove("H7", "H6");
	cout << '\n';

	cg.submitMove("C1", "A3");
	cg.submitMove("B8", "D7");
	cout << '\n';

	cg.submitMove("D1", "E2");
	cg.submitMove("D5", "E4");
	cout << '\n';

	cg.submitMove("D3", "E4");
	cg.submitMove("G8", "F6");
	cout << '\n';

	cg.submitMove("E4", "D3");
	cg.submitMove("B7", "B6");
	cout << '\n';

	cg.submitMove("E2", "E6");
	cg.submitMove("F7", "E6");
	cout << '\n';

	cg.submitMove("D3", "G6");
	cout << '\n';

	return 0;
}
