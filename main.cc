#include "makePlots.h"
#include <fstream>
#include <iostream>
#include <string>         // std::string

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
  for (int i=0;i<filename.size();i++)
  {
        cout << filename << endl;
        cout << filename.find(Found_energy[i]) << endl;
        int found = filename.find(Found_energy[i]);
        if(found!=1)
        {
            continue;
            
        }
        if(std::string::npos!=1)
        {
            found_energy=Found_energy[i];
            break;
            
        }
    }
    TFile* Pi_histo = TFile::Open(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/root_plot_delcut/MC_%sGeV_Pi_delta_cut.root",found_energy));
    TFile* Ele_histo = TFile::Open(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/root_plot_delcut/MC_%sGeV_Ele_delta_cut.root",found_energy));
    TH1D *h_Pi;
    TH1D *h_Ele;
    h_Pi=(TH1D*) Pi_histo->Get("total_energy");
    h_Ele=(TH1D*) Ele_histo->Get("total_energyL3");
    //find the second high
    for (int Pi_cut=1 ; Pi_cut < h_Pi->GetSize()-2 ; Pi_cut++)
    {
         if(h_Pi->GetBinContent(Pi_cut)<1000)
        {
            int PI_CUT=(Pi_cut-1)*5
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
                continue
            }
            else
            {
            int ELE_CUT=(Ele_cut-1)*5
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
