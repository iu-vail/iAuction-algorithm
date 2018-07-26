
///////////////////////////////////////////////////////////////////////////////
// File name: Assignment.h
// This file defines the class of Assignment. 
// The assignment matrix can be obtained either by randomly generated, or by 
// reading from a specified input file. For the input file, user is required to 
// specify a nXn matrix. Parser has some intelligence, so no strict format is 
// required. E.g. put a file named 'example' in current directory.
// Lantao Liu, Nov 1, 2009
// Last modified: Dec 3, 2011
///////////////////////////////////////////////////////////////////////////////

#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H


#include <string>
#include <string.h>
#include <set>
#include "Define.h"

using namespace std;


///////////////////////////////////////////////////////////////////////////////
//
// Assignment class: defined methods for obtaining an assignment matrix
//
///////////////////////////////////////////////////////////////////////////////

class Assignment{
public:
  Assignment(uint _seed = SEED):seed(_seed){}
  ~Assignment(){}
  
  //Set the seed for random generator
  void SetSeed(uint _seed){ seed = _seed; }
  uint GetSeed(void){ return seed; }
  uint GetRowSize(void){ return row_size; }
  uint GetColSize(void){ return col_size; }
  mat& GetMatrix(void){ return matrix; }
  vector<uint>& GetAsgnVec(void){ return asgn_vec; }

  //Randomly generate an assignment-matrix, the default arguments are pre-set
  //Currently can generate only integer numbers
  void RandomGenerate(mat&, uint nrows = ROW_SIZE, uint ncols = COL_SIZE, 
		int Max = 100, uint _seed = SEED);
  void RandomGenerate(uint nrows = ROW_SIZE, uint ncols = COL_SIZE, 
		int Max = 100, uint _seed = SEED);
 
  //Import a utility/cost matrix from external file
  void ImportMatrix(ifstream&, mat&);
  void ImportMatrix(ifstream&);

  //Import an assignment vector
  void ImportVec(ifstream&, vector<uint>&);
  void ImportVec(ifstream&);

  // Negate a matrix via flipping the signs
  void NegateMatrix(mat&);
  void NegateMatrix(void);

  //Display matrix onto screen
  void DisplayMatrix(mat&) const;

private:
  //basic data members
  uint seed;
  uint row_size;
  uint col_size;

  mat matrix;
  vector<uint> asgn_vec;
  
};

#endif


