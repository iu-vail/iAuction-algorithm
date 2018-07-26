
#include "Assignment.h"

void
Assignment::RandomGenerate(mat& matrix, uint nrows, uint ncols, int Max, uint _seed){
 
  //accept new seed for random generator
#ifdef INTEGER
  if(_seed != SEED)
    srand(_seed);
  else 
    srand(seed);
#else
  if(_seed != SEED)
    srand48(_seed);
  else 
    srand48(seed);
#endif
  
  matrix.clear();
  matrix.resize(nrows);
  for(uint i=0; i<nrows; i++)
    matrix[i].resize(ncols);

  //randomly generate
  for(uint i=0; i<nrows; i++)
    for(uint j=0; j<ncols; j++){
#ifdef INTEGER
      int rdm=rand()%Max-1; 
      if(rdm<0) rdm = 0;
#else
      double rdm=drand48()*Max;
#endif
      matrix[i][j] = rdm;
  }      

}

void
Assignment::RandomGenerate(uint nrows, uint ncols, int Max, uint _seed){

  RandomGenerate(matrix, nrows, ncols, Max, _seed);
  //update data members
  row_size = nrows;
  col_size = ncols;

}


void
Assignment::ImportMatrix(ifstream& input_file, mat& matrix){

  string line;
  vector<double> numstream;

  uint num_rows = 0;
  uint num_cols = 0;

  if (input_file.is_open())
  {
    while (!input_file.eof() )
    {
      getline (input_file,line);

      uint local_num_cols=0;
      vector<double> local_numstream;
      string word;

      stringstream parse(line);
      while(parse >> word){
	//if comment line, ignore it
	if(word[0] == '#')
	  break;
	//numstream.push_back(atoi(word.c_str()));  //if not number, then convert to zero
	numstream.push_back(atof(word.c_str()));  //if not number, then convert to zero
	//local_numstream.push_back(atoi(word.c_str()));
	local_numstream.push_back(atof(word.c_str()));

	//matrix(num_rows, num_cols)= atoi(word.c_str()); 	
	local_num_cols++;
      } //end inner while

      //double check if the matrix format is correct or not
      if(num_cols && local_num_cols && num_cols!=local_num_cols){
	cerr<<endl<<"Please input a correct matrix format!"<<endl<<endl;
	exit(0);
      }
      //update column number if everything looks normal
      if(local_num_cols)
	num_cols = local_num_cols;
      //update row number if everything looks normal
      if(line.length()&&local_numstream.size())
        num_rows++;

    } //end out layer while

    input_file.close();

    matrix.clear();
    //put elements into matrix
    //matrix.resize(num_rows, num_cols);
    matrix.resize(num_rows);
    for(uint i=0; i<num_rows; i++)
      matrix[i].resize(num_cols);

    vector<double>::iterator itr = numstream.begin();
    for(uint i=0; i<num_rows; i++)
      for(uint j=0; j<num_cols; j++)
	matrix[i][j] = *itr++;
  } //end outmost if
  else{ 
    cerr <<endl<<"Error: Unable to open file! Stopped."<<endl<<endl; 
    exit(0);
  }

}

void
Assignment::ImportMatrix(ifstream& input_file){

  ImportMatrix(input_file, matrix);
  //update class data members
  row_size = matrix.size();
  col_size = matrix[0].size();

}


void
Assignment::ImportVec(ifstream& input_file, vector<uint>& vec){

  string line;

  if (input_file.is_open())
  {
    while (!input_file.eof() )
    {
      uint num_cols = 0;
      vec.clear();
      getline (input_file,line);
      string word;

      stringstream parse(line);
      while(parse >> word){
	//if comment line, ignore it
	if(word[0] == '#')
	  break;
	vec.push_back(atoi(word.c_str()));  //if not number, convert to zero
	num_cols++;
      } //end inner while

      if(num_cols > 0)
        break;

    } //end out layer while

    input_file.close();

  } //end outmost if
  else{ 
    cerr <<endl<<"Error: Unable to open file! Stopped."<<endl<<endl; 
    exit(0);
  }

}


void
Assignment::ImportVec(ifstream& input_file){

  ImportVec(input_file, asgn_vec);

}



void
Assignment::NegateMatrix(mat& m){

  for(uint i=0; i<m.size(); i++)
    for(uint j=0; j<m[0].size(); j++)
      m[i][j] = -m[i][j];

}

void
Assignment::NegateMatrix(void){

  NegateMatrix(matrix);

}



void
Assignment::DisplayMatrix(mat& m) const{

  if(m[0].size() > DISPLAY_WIDTH*3){
    _cout("Matrix is big, not displaying."<<endl);
    return;
  }

  _cout(endl<<"The assignment problem (matrix) you queried is:"<<endl<<endl);
  for(uint i=0; i<m.size(); i++){
    for(uint j=0; j<m[0].size(); j++)
      _cout("  "<<m[i][j]<<"\t");
    _cout(endl);
  }
  _cout(endl);

}


