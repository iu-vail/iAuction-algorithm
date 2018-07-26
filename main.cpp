
///////////////////////////////////////////////////////////////////////////////
// File name: main.cpp
// First obtain assignment, then call the algorithm.
// Lantao Liu, Apr 15, 2013
/////////////////////////////////////////////////////////////////////////////// 

#include "Define.h"
#include "CmdParser.h"
#include "Assignment.h"
#include "iAuction.h"
#include "Utils.h"


int main(int argc, char** argv)
{

  //parse command line and generate an assignment
  CmdParser parser(argc, argv);
  parser.DisplayInput();

  Assignment as;
  if(parser.GetInputFileName().empty()){
    if(parser.GetSeed())
      as.SetSeed(parser.GetSeed());
    else
      as.SetSeed(time(NULL));

    _cout(endl<<"  *Seed for random generator: "<<as.GetSeed()<<endl);
    _cout("  RAND_MAX: "<<RAND_MAX<<endl);
    as.RandomGenerate( parser.GetAssignmentSize(), 
			 parser.GetAssignmentSize(), 
			 MAX_RANDOM, 
			 parser.GetSeed() );
  }
  else{
    ifstream myfile(parser.GetInputFileName().c_str());
    as.ImportMatrix(myfile);
  }
  // negate matrix: uncomment below to convert from Maxmization to Maximization
  //as.NegateMatrix();

  as.DisplayMatrix(as.GetMatrix());

  if(as.GetRowSize() != as.GetColSize()){
     cerr<<endl<<"  The input problem must be a SQUARE matrix. You can add dummy rows/columns of 0s to convert a rectangular matrix to a square matrix."<<endl<<endl;
     exit(0);
  }


  Utils utils;

  try{

    iAuction auction(as.GetMatrix());

    double time_start = utils.GetCurTime();
    double time = 0;
  
    auction.MainAlgo();

    time += utils.GetCurTime() - time_start;
    cout<<"Time used: "<<time<<endl;
  }
  catch(int e){

    if(e==EXCEPTION_BROKEN){
      cerr<<"I suspect there is something wrong..."<<endl;
      cerr<<"Current seed: "<<as.GetSeed()<<endl;
      cerr<<"The problem has been written in to \"debug.txt\". Send this file to code maintainer? "<<endl;
      utils.WriteMatrix(as);
    }
    else if(e==EXCEPTION_WRONG){
      cerr<<"!!Wrong solution, double check it. "<<endl;
      cerr<<"Current seed: "<<as.GetSeed()<<endl;
      cerr<<"The problem has been written in to \"debug.txt\"."<<endl;
      utils.WriteMatrix(as);
    }
    else
      cerr<<"Unknown exception caught. "<<endl;
  }

  return 0;

}


