

#include "Utils.h"


Utils::Utils(){
  start_time = GetCurTime();
  last_time = 0;
}

Utils::~Utils(){}


double 
Utils::GetCurTime(void){

  struct timeval curr;
  gettimeofday(&curr,NULL);
  return(curr.tv_sec + curr.tv_usec / 1e6);

}


void
Utils::Stats(const vector<double>& _data, 
                double& _sum, double& _avg, double& _var){

  _sum = 0;
  for(uint i=0; i<_data.size(); i++){
    _sum += _data[i];
  }

  _avg = _sum/_data.size();

  _var = 0;
  for(uint i=0; i<_data.size(); i++){
    _var += (_data[i]-_avg)*(_data[i]-_avg); 
  }
  _var = sqrt(_var/_data.size());
  
}


void
Utils::WriteMatrix(const mat& _m, char* _fname){

  ofstream fout(_fname);
  if(!fout)
    cerr << "Cannot create output file"<<endl;
  
  for(uint i=0; i<_m.size(); i++){
    for(uint j=0; j<_m[0].size(); j++)
      fout<<_m[i][j]<<"\t";
    fout<<endl;
  }
  
  fout.close();
}


void
Utils::WriteMatrix(Assignment& _as, char* _fname){

  ofstream fout(_fname);
  if(!fout)
    cerr << "Cannot create output file"<<endl;
  
  fout<<"# seed: "<<_as.GetSeed()<<endl;
  for(uint i=0; i<_as.GetRowSize(); i++){
    for(uint j=0; j<_as.GetColSize(); j++)
      fout<<_as.GetMatrix()[i][j]<<"\t";
    fout<<endl;
  }
  
  fout.close();

}


void 
Utils::OutLog(void){
  int a = 0; //a dummy
  stringstream ss;
  ss << a;
  string log = LOG_DIR + ss.str() + ".log";
  ofstream fout(log.c_str(),ios::app);
  if(!fout)
    cerr << "Cannot open output file. No log file generated!"<<endl;

  if(this->GetCurTime()-this->last_time > 100){
    fout<<"The "<<int(this->GetCurTime()-this->start_time)<<"th second: "<<endl;
    this->last_time = this->GetCurTime();
   }

  fout.close();

}


