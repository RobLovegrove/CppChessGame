#include "ChessPiece.h"

#include <iostream>

using namespace std;

ostream& operator << (ostream& os, Type type) {
    switch (type) {
        case Type::PAWN:
        os << "Pawn";
        break;
        case Type::ROOK:
        os << "Rook";
        break;
        case Type::KNIGHT:
        os << "Knight";
        break;
        case Type::BISHOP:
        os << "Bishop";
        break;
        case Type::QUEEN:
        os << "Queen";
        break;
        case Type::KING:
        os << "King";
        break;
        default:
        cout << "Error: Invalid Chess Type found when trying to output to console";
    }

    return os;
}