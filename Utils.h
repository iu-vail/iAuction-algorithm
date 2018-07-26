
///////////////////////////////////////////////////////////////////////////////
// File name: Utils.h
// This file defines the class of Utils. 
// It constains some auxillary functions.
// Lantao Liu, Dec 8, 2011
///////////////////////////////////////////////////////////////////////////////

#ifndef UTILS_H
#define UTILS_H

#include "Define.h"
#include "Assignment.h"
#include <sys/time.h>
#include <time.h>
#include <unistd.h>  // for usleep() 
#include <math.h>    // for pow, sin, cos
#include <cfloat>    // DBL_MIN, DBL_MAX


#define QUIET

#define LOG_DIR "outlog/"


class Utils{
public:
  Utils();
  ~Utils();

public:
  double GetStartTime(void){ return start_time; }
  double GetLastTime(void){ return last_time; }

  double GetCurTime(void);   
  void Stats(const vector<double>& _data, 
		double& _sum, double& _avg, double& _var);
  void WriteMatrix(const mat& _m, char* _fname);
  void WriteMatrix(Assignment& _as, char* _fname=(char*)DEBUG_FILE);
  template<typename T>
  void WriteVec(const vector<T>&, char* _fname);
  template<typename T>
  void WriteVecAppend(const vector<T>&, char* _fname);
  void OutLog(void);

  template<typename T>
  void DisplayVec(const vector<T>&);

public:
  double start_time;
  double last_time;

};


template<typename T>
void
Utils::WriteVec(const vector<T>& _vec, char* _fname){

  ofstream fout(_fname);
  if(!fout)
    cerr << "Cannot create output file"<<endl;

  for(uint i=0; i<_vec.size(); i++)
    fout<<_vec[i]<<" ";
  fout<<endl;

}

template<typename T>
void
Utils::WriteVecAppend(const vector<T>& _vec, char* _fname){

  ofstream fout;
  fout.open(_fname, ios::app);    // open file for appending
  assert(!fout.fail()); 
  for(uint i=0; i<_vec.size(); i++)
    fout<<_vec[i]<<" ";
  fout<<endl;
  fout.close();

}


template<typename T>
void
Utils::DisplayVec(const vector<T>& _vec){

  for(uint i=0; i<_vec.size(); i++)
    cout<<_vec[i]<<" ";
  cout<<endl;

}

#endif


