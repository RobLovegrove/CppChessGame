#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {

 private:
  int file = 0;
  int rank = 0;

 public:

  struct Result {
    double gradient;
    int delta_file;
    int delta_rank;
  };

  int get_file() { return file; }
  int get_rank() { return rank; }

  friend bool operator == (const Position& p1, const Position& p2);
  friend bool operator != (const Position& p1, const Position& p2);
  Position& operator = (const Position& p);
  friend Result operator / (const Position& p1, const Position& p2);
  friend Result operator - (const Position& p1, const Position& p2);
  friend std::ostream& operator << (std::ostream& os, Position position);

  Position(int file, int rank) : file(file), rank(rank) {}
};

#endif
