# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++2a -Wall -g

# Output executable
TARGET = chess

# Source files and corresponding object files
SRCS = ChessMain.cpp ChessGame.cpp ChessPiece.cpp Colour.cpp Position.cpp Pawn.cpp Rook.cpp Knight.cpp Bishop.cpp Queen.cpp King.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Pattern rule for generating object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule
clean:
	rm -rf $(OBJS) $(TARGET)