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
        cout << "Error: Invalid Type found when trying to output to console";
    }
    return os;
}

std::ostream& operator << (ostream& os, const ChessPiece& piece) {
    os << piece.colour << "'s " << piece.get_type();
    return os;
}

bool ChessPiece::operator==(uint8_t value) const {
    // Compare the piece's colour with the active player bit
    // Casting colour to int will be 0 for WHITE and 1 for BLACK
    // Active player flag will be 0b00000000 for WHITE and 0b00000001 for BLACK
    return static_cast<int>(colour) == value;
}

bool ChessPiece::operator!=(uint8_t value) const {
    // Compare the piece's colour with the active player bit
    // Casting colour to int will be 0 for WHITE and 1 for BLACK
    // Active player flag will be 0b00000000 for WHITE and 0b00000001 for BLACK
    return static_cast<int>(colour) != value;
}