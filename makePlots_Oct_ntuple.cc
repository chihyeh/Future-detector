#include "makePlots.h"
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

//Constructor
makePlots::makePlots(){
  TestRun = false;
  Init();}
makePlots::makePlots( TChain *c1,TChain *c2,TChain *c3,string filename ):T_Rechit(c1),T_DWC(c2),T_Meta(c3)
{
  cout << "Data: Constructor of makePlot ... \n\n" << endl;
  fname = filename;
  // Set object pointer(Data)
  rechit_detid = 0;
  rechit_module = 0;
  rechit_layer = 0;
  rechit_chip = 0;
  rechit_channel = 0;
  rechit_type = 0;
  rechit_x = 0;
  rechit_y = 0;
  rechit_z = 0;
  rechit_iu = 0;
  rechit_iv = 0;
  rechit_energy = 0;
  rechit_energy_noHG = 0;
  rechit_amplitudeHigh = 0;
  rechit_amplitudeLow = 0;
  rechit_hg_goodFit = 0;
  rechit_lg_goodFit = 0;
  rechit_hg_saturated = 0;
  rechit_lg_saturated = 0;
  rechit_fully_calibrated = 0;
  rechit_TS2High = 0;
  rechit_TS2Low = 0;
  rechit_TS3High = 0;
  rechit_TS3Low = 0;
  rechit_Tot = 0;
  rechit_time = 0;
  rechit_timeMaxHG = 0;
  rechit_timeMaxLG = 0;
  rechit_toaRise = 0;
  rechit_toaFall = 0;
  TestRun = false;
  Init();  
}
makePlots::makePlots( TChain *c1,TChain *c2,string filename ):T_Rechit(c1),T_DWC(c2){
  cout << "MC: Constructor of makePlot ... \n\n" << endl;
    fname = filename;
  // Set object pointer(Data)
  rechit_detid = 0;
  rechit_module = 0;
  rechit_layer = 0;
  rechit_chip = 0;
  rechit_channel = 0;
  rechit_type = 0;
  rechit_x = 0;
  rechit_y = 0;
  rechit_z = 0;
  rechit_iu = 0;
  rechit_iv = 0;
  rechit_energy = 0;
  rechit_energy_noHG = 0;
  rechit_amplitudeHigh = 0;
  rechit_amplitudeLow = 0;
  rechit_hg_goodFit = 0;
  rechit_lg_goodFit = 0;
  rechit_hg_saturated = 0;
  rechit_lg_saturated = 0;
  rechit_fully_calibrated = 0;
  rechit_TS2High = 0;
  rechit_TS2Low = 0;
  rechit_TS3High = 0;
  rechit_TS3Low = 0;
  rechit_Tot = 0;
  rechit_time = 0;
  rechit_timeMaxHG = 0;
  rechit_timeMaxLG = 0;
  rechit_toaRise = 0;
  rechit_toaFall = 0;
  TestRun = false;
  Init();
}
makePlots::makePlots( TChain *c1,string filename ):T_Rechit(c1){
  cout << "Test Data: Constructor of makePlot ... \n\n" << endl;
  fname = filename;
  // Set object pointer(Data)
  rechit_detid = 0;
  rechit_module = 0;
  rechit_layer = 0;
  rechit_chip = 0;
  rechit_channel = 0;
  rechit_type = 0;
  rechit_x = 0;
  rechit_y = 0;
  rechit_z = 0;
  rechit_iu = 0;
  rechit_iv = 0;
  rechit_energy = 0;
  rechit_energy_noHG = 0;
  rechit_amplitudeHigh = 0;
  rechit_amplitudeLow = 0;
  rechit_hg_goodFit = 0;
  rechit_lg_goodFit = 0;
  rechit_hg_saturated = 0;
  rechit_lg_saturated = 0;
  rechit_fully_calibrated = 0;
  rechit_TS2High = 0;
  rechit_TS2Low = 0;
  rechit_TS3High = 0;
  rechit_TS3Low = 0;
  rechit_Tot = 0;
  rechit_time = 0;
  rechit_timeMaxHG = 0;
  rechit_timeMaxLG = 0;
  rechit_toaRise = 0;
  rechit_toaFall = 0;
  TestRun = true;
  Init();
}

//Destructor
makePlots::~makePlots()
{
  cout << "\n\n";
  cout << "Destructor of makePlot ... " << endl;
}

void makePlots::Init(){

  nevents = T_Rechit->GetEntries();
  if(Is_Data)
    cout << "(Data)Nevents: "<< nevents << endl;
  else
    cout << "(MC)Nevents: "<< nevents << endl;

  T_Rechit->SetBranchAddress("event", &event);
  T_Rechit->SetBranchAddress("run", &run);
  T_Rechit->SetBranchAddress("pdgID", &pdgID);
  T_Rechit->SetBranchAddress("beamEnergy", &beamEnergy);
  T_Rechit->SetBranchAddress("trueBeamEnergy", &trueBeamEnergy);
  T_Rechit->SetBranchAddress("NRechits", &NRechits);
  T_Rechit->SetBranchAddress("rechit_detid", &rechit_detid);
  T_Rechit->SetBranchAddress("rechit_module", &rechit_module);
  T_Rechit->SetBranchAddress("rechit_layer", &rechit_layer);
  T_Rechit->SetBranchAddress("rechit_chip", &rechit_chip);
  T_Rechit->SetBranchAddress("rechit_channel", &rechit_channel);

  T_Rechit->SetBranchAddress("rechit_x", &rechit_x);
  T_Rechit->SetBranchAddress("rechit_y", &rechit_y);
  T_Rechit->SetBranchAddress("rechit_z", &rechit_z);
  T_Rechit->SetBranchAddress("rechit_iu", &rechit_iu);
  T_Rechit->SetBranchAddress("rechit_iv", &rechit_iv);
  T_Rechit->SetBranchAddress("rechit_energy", &rechit_energy);

  T_Rechit->SetBranchAddress("rechit_amplitudeHigh", &rechit_amplitudeHigh);
  T_Rechit->SetBranchAddress("rechit_amplitudeLow", &rechit_amplitudeLow);
    
  T_Rechit->SetBranchAddress("rechit_Tot", &rechit_Tot);
  T_Rechit->SetBranchAddress("rechit_time", &rechit_time);
  T_Rechit->SetBranchAddress("rechit_timeMaxHG", &rechit_timeMaxHG);
  T_Rechit->SetBranchAddress("rechit_timeMaxLG", &rechit_timeMaxLG);
  T_Rechit->SetBranchAddress("rechit_toaRise", &rechit_toaRise);
  T_Rechit->SetBranchAddress("rechit_toaFall", &rechit_toaFall);

  if(Is_Data){
    T_Rechit->SetBranchAddress("rechit_type", &rechit_type);
    T_Rechit->SetBranchAddress("rechit_energy_noHG", &rechit_energy_noHG);
    T_Rechit->SetBranchAddress("rechit_hg_goodFit", &rechit_hg_goodFit);
    T_Rechit->SetBranchAddress("rechit_lg_goodFit", &rechit_lg_goodFit);
    T_Rechit->SetBranchAddress("rechit_hg_saturated", &rechit_hg_saturated);
    T_Rechit->SetBranchAddress("rechit_lg_saturated", &rechit_lg_saturated);
    T_Rechit->SetBranchAddress("rechit_fully_calibrated", &rechit_fully_calibrated);
    T_Rechit->SetBranchAddress("rechit_TS2High", &rechit_TS2High);
    T_Rechit->SetBranchAddress("rechit_TS2Low", &rechit_TS2Low);
    T_Rechit->SetBranchAddress("rechit_TS3High", &rechit_TS3High);
    T_Rechit->SetBranchAddress("rechit_TS3Low", &rechit_TS3Low);}


  if(!TestRun){
    T_DWC ->SetBranchAddress("ntracks", &ntracks);
    T_DWC->SetBranchAddress("trackChi2_X", &trackChi2_X);
    T_DWC->SetBranchAddress("trackChi2_Y", &trackChi2_Y);
    T_DWC->SetBranchAddress("dwcReferenceType", &dwcReferenceType);
    T_DWC->SetBranchAddress("m_x", &m_x);
    T_DWC->SetBranchAddress("m_y", &m_y);
    T_DWC->SetBranchAddress("b_x", &b_x);
    T_DWC->SetBranchAddress("b_y", &b_y);


  
    if(Is_Data){
      T_Meta->SetBranchAddress("configuration", &configuration);
      T_Meta->SetBranchAddress("biasCurrentCh0", &biasCurrentCh0);
      T_Meta->SetBranchAddress("biasCurrentCh1", &biasCurrentCh1);
      T_Meta->SetBranchAddress("biasCurrentCh2", &biasCurrentCh2);
      T_Meta->SetBranchAddress("biasCurrentCh3", &biasCurrentCh3);
      T_Meta->SetBranchAddress("humidity_RHDP4", &humidity_RHDP4);
      T_Meta->SetBranchAddress("TCassette07", &TCassette07);
      T_Meta->SetBranchAddress("tablePositionY", &tablePositionY);
      T_Meta->SetBranchAddress("humidity_air", &humidity_air);
      T_Meta->SetBranchAddress("temperature_air", &temperature_air);}
  }
  Init_Runinfo();
}
void makePlots::Init_Runinfo(){
  T_Rechit->GetEntry(0);
  beamE = beamEnergy;
  if( pdgID == 11 ){
    beam_str = "Ele";
    PID = 0;}
  else if( pdgID == 13){
    beam_str = "Mu";
    PID = 2;}
  else if( pdgID == 211){
    beam_str = "Pi";
    PID = 1;}
  else{
    cout << "unknown PDGID QQ" << endl;
    beam_str = "??";
    PID = -1;}
  if(Is_Data)
    runN = run;
  else
    runN = 0;
  
  if(runN <= 722 ) {
    setup_config = 0;
    NLAYER_EE = 28;
    NLAYER_FH = 12;
    if(runN <= 257){
      cout << "TOA threshold will be changed after Run 257." << endl;}
  }
  else if(runN > 722 && runN <= 1057){
    setup_config = 1;
    NLAYER_EE = 28;
    NLAYER_FH = 11;}
  else if(runN > 1057 && runN <= 1078){
    setup_config = 2;
    NLAYER_EE = 0;
    NLAYER_FH = 9;}
  else{
    setup_config = 3;
    NLAYER_EE = 8;
    NLAYER_FH = 12;
  }
  
  NLAYER = NLAYER_EE+NLAYER_FH;
  cout << "Beam type = "<< beam_str.c_str()  << " , Energy = "<< beamE
       << "GeV" << ", setup_config = "  << setup_config << endl;
}

void makePlots::GetData(int evt){
  if(TestRun){
    T_Rechit-> GetEntry(evt);
  }
  if(!TestRun){
    if(Is_Data){
      T_Rechit-> GetEntry(evt);
      T_DWC   -> GetEntry(evt);
      T_Meta  -> GetEntry(evt);}
    else{
      T_Rechit-> GetEntry(evt);}
  }
}

void makePlots::Getinfo(int ihit,int &layer,double &x, double &y,double &z,double &ene){
    layer = rechit_layer->at(ihit);
    x     = rechit_x    ->at(ihit);
    y     = rechit_y    ->at(ihit);
    z     = rechit_z    ->at(ihit);
    ene   = rechit_energy->at(ihit);
}

void makePlots::NtupleMaker(){
  
  Init();
  //  for(int i = 0 ; i < 10 ; ++i){
  //  Event_Display_3D(i);}
  
  char title[50];
  if(Is_Data)
    sprintf(title,"output_root/Run%i_%iGeV_%s.root",runN,beamE,beam_str.c_str());
  else
    sprintf(title,"output_root/MC_%iGeV_%s.root",beamE,beam_str.c_str());

  cout << "output file: " << title << endl;
  TFile outf(title,"recreate");
  TTree *outT1,*outT2;
  if(!TestRun && Is_Data){
    outT1 = T_Rechit->CopyTree("");
    outT2 = T_DWC->CopyTree("");}
  else{
    outT1 = T_Rechit->CopyTree("");
  }
  TTree *outT3 = new TTree("rechit_var","rechit_var");
  
  vector<vector<double> > hit_tmp(NLAYER);
  vector<vector<double> > hit_x(NLAYER);
  vector<vector<double> > hit_y(NLAYER);
  vector<vector<double> > hit_z(NLAYER);
  int Nhits;
  int layerNhit[NLAYER];
  double totalE,totalE_CEE,totalE_CEH;
  double layerE[NLAYER];
  double E_1[NLAYER];
  double E_7[NLAYER];
  double E_19[NLAYER];
  double E_37[NLAYER];


  outT3->Branch("totalE",&totalE,"totalE/D");
  outT3->Branch("totalE_CEE",&totalE_CEE,"totalE_CEE/D");
  outT3->Branch("totalE_CEH",&totalE_CEH,"totalE_CEH/D");
  outT3->Branch("hit_mip","std::vector< std::vector<double> >",&hit_tmp);
  outT3->Branch("hit_x","std::vector< std::vector<double> >",&hit_x);
  outT3->Branch("hit_y","std::vector< std::vector<double> >",&hit_y);
  outT3->Branch("hit_z","std::vector< std::vector<double> >",&hit_z);

  outT3->Branch("NLAYER",&NLAYER,"NLAYER/I");
  outT3->Branch("layerNhit",layerNhit,"layerNhit[NLAYER]/I");
  outT3->Branch("layerE",layerE,"layerE[NLAYER]/D");
  outT3->Branch("layerE1",E_1,"layerE1[NLAYER]/D");
  outT3->Branch("layerE7",E_7,"layerE7[NLAYER]/D");
  outT3->Branch("layerE19",E_19,"layerE19[NLAYER]/D");
  outT3->Branch("layerE37",E_37,"layerE37[NLAYER]/D");

  
  
  for(int ev = 0; ev < nevents; ++ev){
    if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;
    GetData(ev);
    Nhits = NRechits;
    
    for(int iL = 0; iL < NLAYER ; ++iL){
      hit_tmp[iL].clear();
      hit_x[iL].clear();
      hit_y[iL].clear();
      hit_z[iL].clear();
      layerE[iL] = 0;
      layerNhit[iL] = 0;
      E_1[iL] = 0;
      E_7[iL] = 0;
      E_19[iL] = 0;
      E_37[iL] = 0;}
    
    int layer;
    double posx,posy,posz,energy;
    totalE = 0;
    totalE_CEE = 0;
    totalE_CEH = 0;
    for(int h = 0; h < Nhits ; ++h){
      
      Getinfo(h,layer,posx,posy,posz,energy);
      //Be careful here layerID start from 1
      totalE += energy;
      if(layer <= NLAYER_EE)
	totalE_CEE += energy;      
      else
	totalE_CEH += energy;
      
      layerNhit[layer-1]++;
      hit_tmp[layer-1].push_back(energy);
      hit_x[layer-1].push_back(posx);
      hit_y[layer-1].push_back(posy);
      hit_z[layer-1].push_back(posz);}
 
    for(int iL = 0; iL < NLAYER ; ++iL){
      
      //Find seed
      int maxID = -1;
      double Emax = -1;
      for(int iH = 0 ; iH < (int)hit_tmp[iL].size(); ++iH){
	if( hit_tmp[iL].at(iH) > Emax ){
	  Emax  = hit_tmp[iL].at(iH);
	  maxID = iH;
	  E_1[iL] = hit_tmp[iL].at(iH);}}
      
      //Dist from seed
      double dx,dy,dR;
      for(int iH = 0 ; iH < (int)hit_tmp[iL].size(); ++iH){
	dx = hit_x[iL].at(iH) - hit_x[iL].at(maxID);
	dy = hit_y[iL].at(iH) - hit_y[iL].at(maxID);
	dR = sqrt(dx*dx + dy*dy);
	if( dR < 1.12455*1.2) E_7[iL] += hit_tmp[iL].at(iH);
	if( dR < 1.12455*2*1.2) E_19[iL] += hit_tmp[iL].at(iH);
	if( dR < 1.12455*3*1.2) E_37[iL] += hit_tmp[iL].at(iH);
	layerE[iL] += hit_tmp[iL].at(iH);}      
    }
    outT3->Fill();
  }
  outT1->Write();
  //outT2->Write();
  outT3->Write();
  outf.Close();
}

void makePlots::Energy_Distribution_Display(bool ignore_EE,bool hitmap){

  Init();
  gStyle->SetPalette(53);
  gStyle->SetOptStat(0);
  gROOT->SetBatch(kTRUE);

  TCanvas *c1 = new TCanvas("c1","c1",6400,3600);
  if(ignore_EE){
    c1->Divide(4,3);}
  else{
    if(setup_config < 2){
      c1->Divide(8,5);}
    else if(setup_config == 2){
      c1->Divide(4,3);}
    else{
      c1->Divide(5,4);}}
  
  char title[50];


  TH2Poly *evtdis[NLAYER];

  for(int iL = 0; iL < NLAYER ; ++iL){
    evtdis[iL] = new TH2Poly();
    if(setup_config == 0){
      if(iL < NLAYER_EE){
	InitTH2Poly(*evtdis[iL]);}
      else{
	InitTH2Poly_flower(*evtdis[iL]);}
    }
    else if(setup_config == 1){
      if(iL < NLAYER_EE + 2){ // +2 For 2 single layer FH
	InitTH2Poly(*evtdis[iL]);}
      else{
	InitTH2Poly_flower(*evtdis[iL]);}
    }
    else if(setup_config == 2){
      InitTH2Poly_flower(*evtdis[iL]);}
    else if(setup_config == 3){
      if(iL < NLAYER_EE){
	InitTH2Poly(*evtdis[iL]);}
    }
    else{
      InitTH2Poly_flower(*evtdis[iL]);
    }
  
    sprintf(title,"Layer_%i",iL+1);
    evtdis[iL]->SetTitle(title);
  }
  
  int counts = 0;

  for(int ev = 0; ev < nevents; ++ev){
    if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;    
    GetData(ev);
    int Nhits;
    Nhits = NRechits;
    //cout << Nhits << endl;
    int layer;
    double posx,posy,posz,energy;
   
    
    double totalE = 0;
    for(int h = 0; h < Nhits ; ++h){
      Getinfo(h,layer,posx,posy,posz,energy);
      totalE += energy;
    }
    counts++;
    for(int h = 0; h < Nhits ; ++h){
      Getinfo(h,layer,posx,posy,posz,energy);
      //cout << "layer = " << layer << " , x = " << posx << ", y = " << posy << ", nmip = " << energy <<endl;
      if(hitmap)
	evtdis[layer-1]->Fill(posx,posy,1);
      else
	evtdis[layer-1]->Fill(posx,posy,energy/totalE);	
      //cout << "hello~" << endl;
      
    }
  }
  for(int iL = 0; iL < NLAYER ; ++iL){
    if(!ignore_EE){
      c1->cd(iL+1);
      evtdis[iL]->Draw("colz");}
    else{
      int tmpL = iL+1 - NLAYER_EE ;
      if(tmpL > 0){
	c1->cd(tmpL);
	evtdis[iL]->Draw("colz");}
    }
  }
  c1->Update();
  sprintf(title,"plots/evt_dis/energy_display_Run%i.png",runN);
  c1->SaveAs(title);
  delete c1;

}

void makePlots::Event_Display(int ev){

  TCanvas *c1 = new TCanvas("c1","c1",6400,3600);
  if(setup_config < 2){
    c1->Divide(8,5);}
  else if(setup_config == 2){
    c1->Divide(4,3);}
  else{
    c1->Divide(5,4);}
  char title[50];


  TH2Poly *evtdis[NLAYER];

  for(int iL = 0; iL < NLAYER ; ++iL){
    evtdis[iL] = new TH2Poly();
    if(setup_config == 0){
      if(iL < NLAYER_EE){
	InitTH2Poly(*evtdis[iL]);}
      else{
	InitTH2Poly_flower(*evtdis[iL]);}
    }
    else if(setup_config == 1){
      if(iL < NLAYER_EE + 2){ // +2 For 2 single layer FH
	InitTH2Poly(*evtdis[iL]);}
      else{
	InitTH2Poly_flower(*evtdis[iL]);}
    }
    else if(setup_config == 2){
      InitTH2Poly_flower(*evtdis[iL]);}
    else if(setup_config == 3){
      if(iL < NLAYER_EE){
	InitTH2Poly(*evtdis[iL]);}
    }
    else{
      InitTH2Poly_flower(*evtdis[iL]);
    }
    
    sprintf(title,"Layer_%i",iL+1);
    evtdis[iL]->SetTitle(title);
  }

  GetData(ev);
  int Nhits;
  Nhits = NRechits;
  //cout << Nhits << endl;
  int layer;
  double posx,posy,posz,energy;

  
  double totalE = 0;
  for(int h = 0; h < Nhits ; ++h){
    Getinfo(h,layer,posx,posy,posz,energy);
      totalE += energy;
  }

  for(int h = 0; h < Nhits ; ++h){
    Getinfo(h,layer,posx,posy,posz,energy);
    //cout << "layer = " << layer << " , x = " << posx << ", y = " << posy << ", nmip = " << energy/ENEPERMIP <<endl;
    evtdis[layer-1]->Fill(posx,posy,energy/totalE);
    //cout << "hello~" << endl;
  }
  
  for(int iL = 0; iL < NLAYER ; ++iL){
    c1->cd(iL+1);
    evtdis[iL]->Draw("colz");
  }

  c1->Update();
  sprintf(title,"plots/evt_dis/event_display_%ievt.png",ev);
  c1->SaveAs(title);
  
  delete c1;

}

void makePlots::Event_Display_3D(int ev){
  gStyle->SetPalette(53);

  TCanvas *c1 = new TCanvas("c1","c1",6400,3600);
  char title[50];

  TH3D *evtdis = new TH3D("","",60,-10,50,50,-20,20,50,-20,20);

  GetData(ev);
  int Nhits;
  Nhits = NRechits;
  //cout << Nhits << endl;
  int layer;
  double posx,posy,posz,energy;

  
  double totalE = 0;
  for(int h = 0; h < Nhits ; ++h){
    Getinfo(h,layer,posx,posy,posz,energy);
      totalE += energy;
  }

  for(int h = 0; h < Nhits ; ++h){
    Getinfo(h,layer,posx,posy,posz,energy);
    //cout << "layer = " << layer << " , x = " << posx << ", y = " << posy << ", nmip = " << energy/ENEPERMIP <<endl;
    evtdis->Fill(layer-1,posy,posx,energy/totalE);
    //cout << "hello~" << endl;
  }
  evtdis->Draw("BOX2");
  c1->Update();
  //sprintf(title,"plots/evt_dis/event_display_%ievt.png",ev);
  //c1->SaveAs(title);
  c1->WaitPrimitive();
  
  delete c1;

}


void makePlots::InitTH2Poly(TH2Poly& poly)
{
  int MAXVERTICES = 6;
  double HexX[MAXVERTICES];
  double HexY[MAXVERTICES];
  int iu,iv,CellXYsize;
  ifstream file("src_txtfile/poly_frame.txt");
  string line;

  
  for(int header = 0; header < 4; ++header )     getline(file,line);
  
  while(true){
    getline(file,line);
    if( file.eof() ) break;
    file >> iu >> iv >> CellXYsize;    
    for(int i = 0; i < CellXYsize ; ++i){
      getline(file,line);
      file >> HexX[i] >> HexY[i];
    }
    
    poly.AddBin(CellXYsize, HexX, HexY);
  }
  file.close();

}

void makePlots::InitTH2Poly_flower(TH2Poly& poly)
{
  //For module Geometry
  double a = 0.6496345; // HGCAL_TB_CELL::FULL_CELL_SIDE,  Size in terms of 1 unit of x/y co-ordinates of a cell side which is 0.064 cm
  double A = 11*a; // One side of a full sensor(neglecting the cut at the MB)
  double x_a = sqrt(3) / 2; // cosine pi/6
  //double y_a = 1 / 2.; // sine pi/6
  double vy_a = 3. / 2;
  double  X0 = 2 * x_a * A; //Translation in Cartesian x for 1 unit of Sensor_iu
  double VX0 = x_a * A; // Cartesian x component of translation for 1 unit of Sensor_iv
  double VY0 = vy_a * A; // Cartesian y component of translation for 1 unit of Sensor_iv
  vector< pair<int,int> > sensor_iu_iv;
  sensor_iu_iv.push_back( make_pair(0,0) );
  sensor_iu_iv.push_back( make_pair(-1,0) );
  sensor_iu_iv.push_back( make_pair(1,0) );
  sensor_iu_iv.push_back( make_pair(0,-1) );
  sensor_iu_iv.push_back( make_pair(0,1) );
  sensor_iu_iv.push_back( make_pair(1,-1) );
  sensor_iu_iv.push_back( make_pair(-1,1) );

  
  double PI = 3.14159265;
  double TB_rotate = -PI/2;

    
  //For channel Geometry
  int MAXVERTICES = 6;
  double HexX[MAXVERTICES];
  double HexY[MAXVERTICES];
  int iu,iv,CellXYsize;
  string line;

  double module_centerx = 0;
  double module_centery = 0;
  double rotate_module_centerx = 0;
  double rotate_module_centery = 0;

  for(int moduleID = 0; moduleID < (int)sensor_iu_iv.size(); ++moduleID){
    ifstream file("src_txtfile/poly_frame.txt");
  
    for(int header = 0; header < 4; ++header )     getline(file,line);
    module_centerx = sensor_iu_iv[moduleID].first*X0 + sensor_iu_iv[moduleID].second*VX0;
    module_centery = sensor_iu_iv[moduleID].second*VY0;

    rotate_module_centerx =
      module_centerx * cos(TB_rotate) - module_centery * sin(TB_rotate);
    
    rotate_module_centery =
      module_centerx * sin(TB_rotate) + module_centery * cos(TB_rotate);


    while(true){
      getline(file,line);

      if( file.eof() ) break;
      bool goodbin = true;
      file >> iu >> iv >> CellXYsize;
      for(int i = 0; i < CellXYsize ; ++i){
	HexX[i] = 0;
	HexY[i] = 0;      }      
      for(int i = 0; i < CellXYsize ; ++i){
	getline(file,line);
	file >> HexX[i] >> HexY[i];
	
	HexX[i] += rotate_module_centerx;
	HexY[i] += rotate_module_centery;
      }
      poly.AddBin(CellXYsize, HexX, HexY);
    }
    file.close();
  }
}

double* makePlots::Set_X0(double X0_arr[]){

  // len["Cu"] = 1.436; //cm                                  
  // len["W"] = 0.35; //cm                                  
  // len["Lead"] = 0.56; //cm                               
  // len["Pb"] = 0.56; //cm                                 
  // len["CuW"] = 0.43; //cm                                
  // len["Al"] = 8.897; //cm

  // 4-July-2018
  // In all the checks done, Pb is 4.9 mm (~0.875 X0) and 
  // Cu is 6 mm (~0.42 X0)  

  // 10-July-2018
  // Odd layers have this config: 
  // Fe(0.3)-Pb(4.9)-Fe(0.3)-Air (4.6) - PCB - Si
  // Even layers have this config: 
  // Kapton(0.01)-CuW(1.2)-Cu(6)-CuW-Kapton-Si

  // 17-July-2018
  // Fe-Pb-Fe-Air-PCB-Si 
  // Kap-CuW-Cu-CuW-Si

  /*
  // 17-July-2018
  1:0.933   2:0.976   3:0.909   4:0.976   5:0.909
  6:0.976   7:0.909   8:0.976   9:0.909   10:0.976
  11:0.909  12:0.976  13:0.909  14:0.976  15:0.909
  16:1.143  17:0.909  18:0.976  19:0.909  20:1.143
  21:0.909  22:0.976  23:0.909  24:1.06  25:0.909
  26:0.976  27:0.909  28:0.976
  */
  double single_layer_X0[NLAYER];
  //Temporarily assign 4.5X0 to all the absorber layer in FH
  if(setup_config < 2){
    for( int i = 0 ; i < NLAYER_EE ; ++i){
      if ( i % 2 == 0) single_layer_X0[i] = 0.909;
      else single_layer_X0[i] = 0.976;
    }
    single_layer_X0[0]  = 0.933;
    single_layer_X0[15] = 1.143;
    single_layer_X0[19] = 1.143;
    single_layer_X0[23] = 1.06;
    if(setup_config == 0){
      for(int i = NLAYER_EE ; i < NLAYER ; ++i){
	single_layer_X0[i]  = 4.5;}
    }
    else{
      single_layer_X0[NLAYER_EE]    = 0;
      single_layer_X0[NLAYER_EE+1]  = 0;
      for(int i = NLAYER_EE+2 ; i < NLAYER ; ++i){
	single_layer_X0[i]  = 4.5;}
    }
  }
  else if(setup_config == 2){
    cout << "This is muon run and I am not going to deal with the X0!" << endl;
    cout << "input anything to continue..." << endl;
    getchar();}
  else{
    single_layer_X0[0] = 1.82;
    single_layer_X0[1] = 1.96;
    single_layer_X0[2] = 1.96;
    single_layer_X0[3] = 2.26;
    single_layer_X0[4] = 2.26;
    single_layer_X0[5] = 2.26;
    single_layer_X0[6] = 4.48;
    single_layer_X0[7] = 5.59;
    for(int i = NLAYER_EE ; i < NLAYER ; ++i){
      single_layer_X0[i]  = 4.5;}
  }
  double X0_sum = 0.;
  for(int iL = 0 ; iL < NLAYER ; ++iL){
    X0_sum += single_layer_X0[iL];
    X0_arr[iL] = X0_sum;
  }
  
  return X0_arr;
}


