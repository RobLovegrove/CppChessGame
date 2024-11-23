#ifndef POSITION_H
#define POSITION_H

class Position {

 private:
  int file = 0;
  int rank = 0;
  
 public:

 Position(int file, int rank) : file(file), rank(rank) {}

  int get_file() { return file; }
  int get_rank() { return rank; }

};

#endif
