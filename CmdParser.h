
///////////////////////////////////////////////////////////////////////////////
// File Name: CmdParser.h
// This file defines a class for parsing command line
// Lantao Liu, Dec 3, 2011
///////////////////////////////////////////////////////////////////////////////


#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class CmdParser{
public:
  CmdParser(int _argc, char **_argv):seed(SEED), 
				     assignment_size(COL_SIZE),
				     //output_file(OUTPUT_FILE),
				     verbose_level(VERBOSE_LEVEL){ 
    ParseCmd(_argc, _argv); 
  }
  ~CmdParser(){}
  
  //some accessors
  string GetInputFileName(void){ return input_file; }
  uint GetSeed(void){ return seed; }
  size_t GetAssignmentSize(void){ return assignment_size; }

  void ParseCmd(int argc, char **argv);
  
  void DisplayInput(void);

  void GiveUsage(char *cmd);
  
public:
  uint seed;
  string input_file;
  size_t assignment_size;
  //string output_file;
  uint verbose_level;

};

void
CmdParser::ParseCmd(int argc, char **argv){

  int c;
  while ((c = getopt (argc, argv, "i:s:n:o:v:h")) != -1)
    switch (c)
    {
           case 'i':
             this->input_file = optarg;
             break;
           case 's':
             this->seed = atoi(optarg);
             break;
           case 'n':
             this->assignment_size = atoi(optarg);
             break;
           //case 'o':
           //  this->output_file = optarg;
           //  break;
           case 'v':
             this->verbose_level = atoi(optarg);
	     if(this->verbose_level < VERBOSE_LEVEL){ 
		cout<<"Undefine DEBUG in \"Define.h\" and re-compile."<<endl;
                exit(0);
	     }
	     break;
	   case 'h':
	     this->GiveUsage(argv[0]);
	     break;
           case '?':
           default:
	     this->GiveUsage(argv[0]);
             exit(0);
    }
}

void
CmdParser::DisplayInput(void){

  if(this->input_file != "")
    _cout("  Accept new input file: "<<input_file<<endl);
  
  if(this->seed != SEED)
    _cout("  Accept new seed: "<<seed<<endl);

  if(this->assignment_size != COL_SIZE)
    _cout("  Accept new assignment size: "<<assignment_size<<endl);

  //if(this->output_file != OUTPUT_FILE)
  //  _cout("  Accept new output file: "<<output_file<<endl);

  if(this->verbose_level != VERBOSE_LEVEL)
    _cout("  Accept new verbose level: "<<verbose_level<<endl);

}

void
CmdParser::GiveUsage(char *cmd)
{
   fprintf(stderr,"\nUsage:    %s \n",cmd);
   fprintf(stderr,"          -i   input an assignment file (string)\n");
   fprintf(stderr,"          -s   random generator with seed (unsigned int)\n");
   fprintf(stderr,"          -n   matrix size (size_t)\n");
   //fprintf(stderr,"          -o   write into output file (string)\n");
   fprintf(stderr,"          -v   verbose level (0 or 1)\n");
   fprintf(stderr,"More details can be found in README file\n\n");
   exit(0);
}


#endif


