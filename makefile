chess: ChessMain.o ChessGame.o ChessPiece.o Colour.o Position.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o
	g++ -Wall -g ChessMain.o ChessGame.o ChessPiece.o Colour.o Position.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o -o chess

ChessMain.o: ChessMain.cpp ChessGame.h
	g++ -Wall -g -c ChessMain.cpp

ChessGame.o: ChessGame.cpp ChessGame.h Pawn.h Rook.h Knight.h Bishop.h Queen.h King.h Colour.h Position.h
	g++ -Wall -g -c ChessGame.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h Colour.h Position.h
	g++ -Wall -g -c ChessPiece.cpp

Colour.o: Colour.cpp Colour.h
	g++ -Wall -g -c Colour.cpp

Position.o: Position.cpp Position.h
	g++ -Wall -g -c Position.cpp

Pawn.o: Pawn.cpp ChessPiece.h Pawn.h Colour.h Position.h
	g++ -Wall -g -c Pawn.cpp

Rook.o: Rook.cpp ChessPiece.h Rook.h Colour.h Position.h
	g++ -Wall -g -c Rook.cpp

Knight.o: Knight.cpp ChessPiece.h Knight.h Colour.h Position.h
	g++ -Wall -g -c Knight.cpp

Bishop.o: Bishop.cpp ChessPiece.h Bishop.h Colour.h Position.h
	g++ -Wall -g -c Bishop.cpp

Queen.o: Queen.cpp ChessPiece.h Queen.h Bishop.h Rook.h Colour.h Position.h
	g++ -Wall -g -c Queen.cpp

King.o: King.cpp ChessPiece.h King.h Colour.h Position.h
	g++ -Wall -g -c King.cpp

clean:
	rm -rf *.o chess

