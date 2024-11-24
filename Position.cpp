#include "Position.h"

bool operator == (const Position& p1, const Position& p2) {
    if (p1.file == p2.file && p1.rank == p2.rank) return true;
    return false;
}

Position& Position::operator = (const Position& p) {
    if (this == &p) {
        return *this;
    }
    this->file = p.file;
    this->rank = p.rank;
    return *this;
}

Position::Result operator / (const Position& p1, const Position& p2) {
    int df= p2.file - p1.file;
    int dr = p2.rank - p1.rank;

    if (df == 0) return {0,0,0};
    double gradient = dr / static_cast<double>(df);

    return {gradient, df, dr}; // Return the structure with all values
}

Position::Result operator - (const Position& p1, const Position& p2) {
    int df= p2.file - p1.file;
    int dr = p2.rank - p1.rank;

    return {0, df, dr}; // Return the structure with all values
}
