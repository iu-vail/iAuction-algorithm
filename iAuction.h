///////////////////////////////////////////////////////////////////////////////
// File name: iAuction.h
// This file defines class of the iAuction method, which has a time 
// complexity of O(n^3 lg n). The practical running time is extremely fast.
// Lantao Liu, Apr 15, 2013
///////////////////////////////////////////////////////////////////////////////

#ifndef IAUCTION_H
#define IAUCTION_H

#include "Define.h"
#include "Assignment.h"
#include <set>

template<typename T> class less_comp; //defined later

class iAuction {

public:
  iAuction(){ cerr<<"Not allowed."<<endl; exit(0); }  
  iAuction(mat& m){
        row_size = m.size();
        col_size = m[0].size();
        assert(row_size <= col_size);  
        orig_matrix = m;
  }
  ~iAuction(){}

  inline uint GetAssignedCol(uint _row_id){ return assignment[_row_id]; }
  inline uint GetNumAsgnRows(uint _col_id){ return record_allocations[_col_id];}
  uint GetLUsize(void){ return LU.size(); }
  uint GetSVsize(void){ return SV.size(); }
  void UpdateRecordAllocations(void);

  uint UpdateLabeledRows(uint _col_id);

  void InitAlgo();
  void InitStage();

  // pre-process the heaps
  void Preprocess(void);	//create all at begining of a stage
  void MakeHeap(uint _row_id);  //on-demand creatation, better

  // a stage of the algorithm that reduces the 'deficiency'/distance  by 1
  uint MainStage(uint s);
  // main algorithm
  void MainAlgo();

  // get current sum of costs based on current assignemnt solution 
  double ComputeCostSum(const mat& _m, const vector<uint>& _as) const;
  // double check if each col got assigned with an unique row 
  void DoubleCheck(void);

  // some display functions
  void DisplayMatrix(const mat&) const;
  void DisplayMatrix(const mat&, const vector<uint>&, bool must_display=false) const;
  void DisplayMatrix(const mat&, const vector<uint>&, const vector<double>& _deltas) const;
  void DisplayAssignment(void) const;
  void DisplaySet(const set<uint>&) const;
  template<typename T>
  void DisplayVec(const vector<T>& _vec);


//basic data members
private:
  mat orig_matrix;              // a copy of original matrix

  uint row_size;
  uint col_size;

  set<uint> LU;
  set<uint> SV;

  vector<double> Deltas;

  vector<uint> assignment;      // from agent perspecitve,a1->t3, a2->t5, a3-..
  vector<uint> allocation;	// from task perspective, t1->a4, t2->a3, t3-..
  vector<uint> record_allocations;
				// num of agts assigned to a single task
  vector<set<uint> > allocation_rows;
				// the row ids assigned to each col
  set<uint> allocated_cols;	// the cols (tasks) that have rows assigned to

  //vector<double> q;
  vector<int> pred_j;
  vector<vector<uint> > pred;

  vector<
        priority_queue<
                pair<uint, double>,
                vector<pair<uint,double> >,
                less_comp<uint> >
        > heaps;            // heaps to maintain searching status


public:
  //data for expt, not useful for algo
  vector<uint> lu_seq;
  uint size_sum;
  uint price_cnt;


};

// for priority queue elements' comparison
template<typename T>
class less_comp{
public:
#ifdef MINIMIZATION
    less_comp(bool __switch = false){ _switch = __switch; };
#else
  less_comp(bool __switch = true){ _switch = __switch; };
#endif
  bool operator() (const pair<T, double>& a,
                const pair<T, double>& b) const {
  if(!_switch) // output in increasing order
    return a.second > b.second ? true : false ;
  else       // output in decreasing order
    return a.second < b.second ? true : false ;
  }

private:
  bool _switch;

};


#endif


