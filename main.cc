#include "makePlots.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "TFile.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TMultiGraph.h"
#include <typeinfo>
#include "TH2Poly.h"

vector<float> SIG_eff(int energy){
    vector<float> a;
    TApplication *app = new TApplication("app",0,0);
    TChain *chain1 = new TChain("hits");
    TChain *chain2 = new TChain("impactPoints");
    TChain *chain3 = new TChain("rechit_var");
    
    chain1->Add(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/Dis_ring_energy/MC_%dGeV_Ele_scale_0.85.root",energy));
    chain2->Add(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/Dis_ring_energy/MC_%dGeV_Ele_scale_0.85.root",energy));
    chain3->Add(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/Dis_ring_energy/MC_%dGeV_Ele_scale_0.85.root",energy));
    makePlots M(chain1,chain2,chain3,Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/Dis_ring_energy/MC_%dGeV_Ele_scale_0.85.root",energy));
    a=M.Loop();
    return (a);
}

vector<float> BKG_rej(int energy){
    vector<float> b;
    vector<float> b_modify;
    TApplication *app = new TApplication("app",0,0);
    TChain *chain1 = new TChain("hits");
    TChain *chain2 = new TChain("impactPoints");
    TChain *chain3 = new TChain("rechit_var");
    
    chain1->Add(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/Dis_ring_energy/MC_%dGeV_Pi.root",energy));
    chain2->Add(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/Dis_ring_energy/MC_%dGeV_Pi.root",energy));
    chain3->Add(Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/Dis_ring_energy/MC_%dGeV_Pi.root",energy));
    makePlots M(chain1,chain2,chain3,Form("/afs/cern.ch/work/c/chyeh/CMSSW_9_3_0/src/2018TBAnalysis/Dis_ring_energy/MC_%dGeV_Pi.root",energy));
    b=M.Loop();
    for ( int i=0 ; i<3 ; i++)
    {
            b_modify.push_back(1/b[i])
    }
    return (b_modify);
}

int main()
{
    
    cout << "Start" << endl;
    vector<int> Energies_files={50,80,100,150};
    vector<float> cut_point={0.2,0.3,0.4};
    for( int i=0 ; i<1 ; i++)
    {
        vector<float> SIG_eff_Point = SIG_eff(Energies_files[i]);
        vector<float> BKG_rej_Point = BKG_rej(Energies_files[i]);
        cout << " SIG_eff: " << a << " BKG_rej: " << b <<endl;
        
        TGraph *gr;
        TCanvas *c1 = new TCanvas("c4","c4",0,0,500,500);
        gr = new TGraph(3,&BKG_rej_Point[0],&SIG_eff_Point[0]);
        //gr->Fit(Full_poly,"R");
        gr->SetMarkerStyle(20);
        gr->SetLineColor(2);
        gr->SetMarkerSize(0.8);
        gr->SetMarkerColor(1);
        gr->Draw("AP");
        gr->SetTitle("Signal efficiency vs background rejection");
        gr->GetXaxis()->SetTitle("Signal efficiency");
        gr->GetYaxis()->SetTitle("Background rejection");
        gr->GetXaxis()->SetRangeUser(0,0.5);
        c1->Print(Form("Electron_efficiency_vs_background_rejection_%dGeV.pdf",Energies_files[i]));
        cout << "end" << endl;
        delete gr;
        //===============
        TGraph *gr1;
        TCanvas *c2 = new TCanvas("c4","c4",0,0,500,500);
        gr1 = new TGraph(3,&cut_point[0],&BKG_rej_Point[0]);
        //gr->Fit(Full_poly,"R");
        gr1->SetMarkerStyle(20);
        gr1->SetLineColor(2);
        gr1->SetMarkerSize(0.8);
        gr1->SetMarkerColor(1);
        gr1->Draw("AP");
        gr1->SetTitle("Electron efficiency vs cut");
        gr1->GetXaxis()->SetTitle("Cut E10/Etotal");
        gr1->GetYaxis()->SetTitle("Background rejection");
        gr1->GetXaxis()->SetRangeUser(0,0.5);
        c2->Print(Form("Electron_efficiency_vs_cut_%dGeV",Energies_files[i]));
        cout << "end" << endl;
        delete gr1;
        c1->Clear();
        c2->Clear();
        SIG_eff_Point.clear();
        BKG_rej_Point.clear();
    }

  return(0);
}
