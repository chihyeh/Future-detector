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

int makePlots(){
#include <iostream>       // std::cout
#include <string>         // std::string
#include <fstream>
    std::vector<std::string> Found_energy = {"50","80","100","150"};
    std::string filename="/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/root_plot_delcuut/MC_50GeV_Ele.root";
    std::string found_energy="";
    int start = filename.find_last_of("/");
    int end = filename.find(".root");
    string f_substr = filename.substr(start+1,end-start-1);
    int start_1 = f_substr.find_first_of("_");
    int end_1 = f_substr.find_last_of("G");
    string f_substr_1 = f_substr.substr(start_1+1,end_1-start_1-1);

cout <<f_substr_1<< endl;
return(0);
}
