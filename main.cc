#include "makePlots.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv){

  TApplication *app = new TApplication("app",0,0);

  TChain *chain = new TChain("hits");
  TChain *chain2 = new TChain("impactPoints");
  TChain *chain3 = new TChain("rechit_var");
  
  string filename;
  string inputfile="input.txt";
  ifstream infile(inputfile.c_str());
  while(true){
    
    infile >> filename;
    if(infile.eof()) break;
    if( filename.length() > 2){
      cout << "input file: " << filename << endl;
      chain->Add(filename.c_str());
      chain2->Add(filename.c_str());
      chain3->Add(filename.c_str());
    }
    else{
      cout << filename << " is not available, please check "
	   << inputfile << endl;}
  }
  infile.close();


  makePlots *M;
  M = new makePlots(chain,chain2,chain3,filename);

  //M->Event_Display();
  M->Loop();
  
  return(0);
}
