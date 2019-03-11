#include "TH1.h"
#include "TH2.h"

void makeClass(){
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  TApplication *a = new TApplication("a", 0, 0);
  bool data = 1;
  if(data){
    TFile f("./root_data/ntuplev9_313.root");
    TTree *tt = (TTree *) f.Get("rechitntupler/hits");
    TTree *tt2 = (TTree *) f.Get("trackimpactntupler/impactPoints");
    TTree *tt3 = (TTree *) f.Get("metadatantupler/meta");
    
    tt->MakeClass("rechit");
    tt2->MakeClass("trackimpact");
    tt3->MakeClass("metadata");    
  }
  else{
    TFile f("root_data/ntuple_sim_pdgID11_beamMomentum100.0_listFTFP_BERT_EMM.root");
    TTree *tt = (TTree *) f.Get("rechitntupler/hits");
    tt->MakeClass("MC");
  }
}
