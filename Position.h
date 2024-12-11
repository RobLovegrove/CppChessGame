#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {

 private:
  int file = 0;
  int rank = 0;

 public:

  /*
    Struct with result of comparison returned to class wanting to compare two
    Positions 
  */
  struct Result {
    double gradient;
    int delta_file;
    int delta_rank;
  };
  /*
    Getter method to return Position file
  */
  int get_file() { return file; }

  /*
    Getter method to return Position rank
  */
  int get_rank() { return rank; }

  /*
    Method: Position equal to operator overloading

    Returns:
      bool: True if two positions have equal rank and file
            False if not
  */
  friend bool operator == (const Position& p1, const Position& p2);
 
  /*
    Method: Position not equal to operator overloading

    Returns:
    bool: True if two positions have equal rank and file
          False if they are
  */
  friend bool operator != (const Position& p1, const Position& p2);

  /*
    Method: Position assignment operator overloading

    Sets this Position's file and rank equal to given Position's file and rank
  */
  Position& operator = (const Position& p);

  /*
    Method: Position division operator overloading

    Determines the difference between the file and rank of this Position 
    with a given Position
    Subtracting the first position provided from the second provided
    Then calculates the gradient by dividing delta_rank by delta_file

    returns:
      Position result struct: (gradient (double), 
                               delta_file (int),
                               delta_rank (int))
  */
  friend Result operator / (const Position& p1, const Position& p2);

  /*
    Method: Position subtraction operator overloading

    Determines the difference between the file and rank of this Position 
    with a given Position
    Subtracting the first position provided from the second provided

    returns:
      Position result struct: (gradient (double) set to 0, 
                               delta_file (int),
                               delta_rank (int))
  */
  friend Result operator - (const Position& p1, const Position& p2);

  /*
    Method: Position output operator overloading
    Outputs a Position to ostream&:
        Static casts file to char from 'A' and 'H'
        outputs rank as ints
  */
  friend std::ostream& operator << (std::ostream& os, Position position);

   /*
    Position Constructor
    Sets the Position file and rank

    Param:
      file: Of type int, sets file 
      rank: Of type int, sets rank
  */
  Position(int file, int rank) : file(file), rank(rank) {}
};

#endif
