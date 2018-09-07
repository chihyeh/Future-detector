#include "makePlots.h"
#include <fstream>
#include <iostream>
#include <string>         // std::string
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <utility>

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
    std::vector<std::string> Found_energy = {"50","80","100","150"};
    std::string found_energy="";
    int start = filename.find_last_of("/");
    int end = filename.find(".root");
    string f_substr = filename.substr(start+1,end-start-1);
    int start_1 = f_substr.find_first_of("_");
    int end_1 = f_substr.find_last_of("G");
    string f_substr_1 = f_substr.substr(start_1+1,end_1-start_1-1);
    f_substr_1=found_energy;
    TFile* Pi_histo = TFile::Open(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/root_plot_delcut/MC_%sGeV_Pi_delta_cut.root",found_energy.c_str()));
    TFile* Ele_histo = TFile::Open(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/root_plot_delcut/MC_%sGeV_Ele_delta_cut.root",found_energy.c_str()));
    TH1D *h_Pi;
    TH1D *h_Ele;
    h_Pi=(TH1D*) Pi_histo->Get("total_energy");
    h_Ele=(TH1D*) Ele_histo->Get("total_energyL3");
    int ELE_CUT=0;
    int PI_CUT=0;
    //find the second high
    for (int Pi_cut=1 ; Pi_cut < h_Pi->GetSize()-2 ; Pi_cut++)
    {
         if(h_Pi->GetBinContent(Pi_cut)<1000)
        {
            PI_CUT=(Pi_cut-1)*5;
            cout << "PI_CUT: " << PI_CUT << endl;
            break;
        }
        else
        {
            continue;
        }
    }
    cout << "OUT_OF_LOOP_PI_CUT: " << PI_CUT << endl;

    for (int Ele_cut=1 ; Ele_cut < h_Ele->GetSize()-2 ; Ele_cut++)
    {
        if(h_Ele->GetBinContent(Ele_cut)==0)
        {
            if(Ele_cut<30)
            {
                continue;
            }
            else
            {
            ELE_CUT=(Ele_cut-1)*5;
            cout << "ELE_CUT: " << ELE_CUT << endl;
            break;
            }
        }
        else
        {
            continue;
        }
    }
    cout << "OUT_OF_LOOP_ELE_CUT: " << ELE_CUT << endl;



  //M->Event_Display();
  M->my_Loop(PI_CUT,ELE_CUT);
  //M->Loop();
  return(0);
}
