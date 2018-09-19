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
#include <utility>

//Constructor
makePlots::makePlots(){}
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
 
  T_DWC->SetBranchAddress("impactX_HGCal_layer_1", &impactX_HGCal_layer_1);
  T_DWC->SetBranchAddress("impactY_HGCal_layer_1", &impactY_HGCal_layer_1);
  T_DWC->SetBranchAddress("impactX_HGCal_layer_2", &impactX_HGCal_layer_2);
  T_DWC->SetBranchAddress("impactY_HGCal_layer_2", &impactY_HGCal_layer_2);
  T_DWC->SetBranchAddress("impactX_HGCal_layer_3", &impactX_HGCal_layer_3);
  T_DWC->SetBranchAddress("impactY_HGCal_layer_3", &impactY_HGCal_layer_3);
  T_DWC->SetBranchAddress("impactX_HGCal_layer_4", &impactX_HGCal_layer_4);
  T_DWC->SetBranchAddress("impactY_HGCal_layer_4", &impactY_HGCal_layer_4);
  T_DWC->SetBranchAddress("impactX_HGCal_layer_5", &impactX_HGCal_layer_5);
  T_DWC->SetBranchAddress("impactY_HGCal_layer_5", &impactY_HGCal_layer_5);
 
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
  cout << beam_str.c_str()  << " , "<< beamE << "GeV\n" << endl;
}

void makePlots::GetData(int evt){
  if(Is_Data){
    T_Rechit-> GetEntry(evt);
    T_DWC   -> GetEntry(evt);
    T_Meta  -> GetEntry(evt);}
  else{
    T_Rechit-> GetEntry(evt);
    T_DWC   -> GetEntry(evt);}
}

void makePlots::Getinfo(int ihit,int &layer,double &x, double &y,double &z,double &ene){
    float scale_factor=0.8;
    layer = rechit_layer->at(ihit);
    x     = rechit_x    ->at(ihit);
    y     = rechit_y    ->at(ihit);
    z     = rechit_z    ->at(ihit);
    ene   = rechit_energy->at(ihit)*(scale_factor);
}

void makePlots::NtupleMaker(){
  int NLAYER = 28;
  double ENEPERMIP = 86.5e-06; //(GeV) Based on 150GeV muon for 300um Si
  
  Init();
  char title[50];
  if(Is_Data)
    sprintf(title,"output_root_wrong/Run%i_%iGeV_%s.root",runN,beamE,beam_str.c_str());
  else
    sprintf(title,"output_root_Dis/MC_%iGeV_%s_scale.root",beamE,beam_str.c_str());
  cout << "output file: " << title << endl;
  TFile outf(title,"recreate");
  TTree *outT1 = T_Rechit->CopyTree("");
  TTree *outT2 = T_DWC->CopyTree("");
  TTree *outT3 = new TTree("rechit_var","rechit_var");
  
  vector<vector<double> > hit_tmp(NLAYER);
  vector<vector<double> > hit_x(NLAYER);
  vector<vector<double> > hit_y(NLAYER);
  vector<vector<double> > hit_z(NLAYER);
  int Nhits;
  int layerNhit[NLAYER];
  double totalE;
  double layerE[NLAYER];
  double E_1[NLAYER];
  double E_7[NLAYER];
  double E_19[NLAYER];
  double E_37[NLAYER];


  outT3->Branch("hit_mip","std::vector< std::vector<double> >",&hit_tmp);
  outT3->Branch("hit_x","std::vector< std::vector<double> >",&hit_x);
  outT3->Branch("hit_y","std::vector< std::vector<double> >",&hit_y);
  outT3->Branch("hit_z","std::vector< std::vector<double> >",&hit_z);
  outT3->Branch("layerNhit",layerNhit,"layerNhit[28]/I");
  outT3->Branch("totalE",&totalE,"totalE/D");
  outT3->Branch("layerE",layerE,"layerE[28]/D");
  outT3->Branch("layerE1",E_1,"layerE1[28]/D");
  outT3->Branch("layerE7",E_7,"layerE7[28]/D");
  outT3->Branch("layerE19",E_19,"layerE19[28]/D");
  outT3->Branch("layerE37",E_37,"layerE37[28]/D");

  
  
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
    
    for(int h = 0; h < Nhits ; ++h){
      
      Getinfo(h,layer,posx,posy,posz,energy);
      totalE += energy;
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
  outT2->Write();
  outT3->Write();
  outf.Close();
}

void makePlots::Loop(){
  int NLAYER = 28;
  double GEVTOMEV = 1000;

  Init();
  
  char title[50],pngtitle[50];
  if(Is_Data)
    sprintf(title,"root_plot/%iGeV_%s.root",beamE,beam_str.c_str());    
  else
    sprintf(title,"root_plot/%iGeV_%s_MC.root",beamE,beam_str.c_str());

  TFile outf(title,"recreate");

  TCanvas *c1 = new TCanvas();
  TH1D *hEsum = new TH1D("ETotalinMIP","ETotalinMIP",100,0,120000);
  TH1D *hNhit = new TH1D("Nofhit","Nofhit",200,0,1000);
  TH1D *hNhit_f5 = new TH1D("Nofhit_first5","Nofhit_f5",40,0,200);
  TH1D *hNhit_l5 = new TH1D("Nofhit_last5","Nofhit_l5",40,0,200);
  TH1D *hEratio_f5 = new TH1D("Eratio_first5","Eratio_first5",25,0,100);
  TH1D *hEratio_l5 = new TH1D("Eratio_last5","Eratio_last5",25,0,50);
  TH1D *hSHD = new TH1D("SHD","SHD",56,0,28);


  vector<vector<double> > hit_tmp(NLAYER);
  
  for(int ev = 0; ev < nevents; ++ev){
    if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;
    GetData(ev);
    int Nhits;
    Nhits = NRechits;

    // Event Selection
    if (Nhits < 200) continue;
    
    for(int iL = 0; iL < NLAYER ; ++iL)
      hit_tmp[iL].clear();
    
    int layer;
    double posx,posy,posz,energy;
    double ENEPERMIP = 86.5e-03;
    int Nhit_f5 = 0;
    int Nhit_l5 = 0;
    double totalE = 0;

    
    for(int h = 0; h < Nhits ; ++h){
      Getinfo(h,layer,posx,posy,posz,energy);
      if(!Is_Data)
	energy*=GEVTOMEV;
      //Hit selection
      if( energy < 2*ENEPERMIP) continue;
      //cout << energy/ENEPERMIP << endl;
      totalE += energy/ENEPERMIP;
      hit_tmp[layer-1].push_back(energy/ENEPERMIP);    }
    //getchar();
    double SHD = 0.;
    double E_f5 = 0.;
    double E_l5 = 0.;
    for(int iL = 0; iL < NLAYER ; ++iL){
      double layerE = 0.;
      
      for(int iH = 0 ; iH < (int)hit_tmp[iL].size(); ++iH){
	if(iL < 5)  Nhit_f5++;
	if(iL > 22) Nhit_l5++;
	layerE += hit_tmp[iL].at(iH);
      }
      if(iL < 5)  E_f5 += layerE;
      if(iL > 22) E_l5 += layerE;
    }
    hEsum     -> Fill(totalE);
    hNhit     -> Fill(Nhits);
    hNhit_f5  -> Fill(Nhit_f5);
    hNhit_l5  -> Fill(Nhit_l5);
    hEratio_f5-> Fill(E_f5/totalE*100.);
    hEratio_l5-> Fill(E_l5/totalE*100.);
    hSHD      -> Fill(SHD);
  }

  //Drawing
  gStyle->SetPalette(54);
  gStyle->SetOptStat(0);
  if(Is_Data)
    hEsum->Draw("error");
  else
    hEsum->Draw();
  c1->Update();

  if(Is_Data)
    sprintf(pngtitle,"%iGeV_%s_Esum.png",beamE,beam_str.c_str());
  else
    sprintf(pngtitle,"%iGeV_%s_Esum_MC.png",beamE,beam_str.c_str());
  c1->SaveAs(pngtitle);
  
  outf.Write();
  outf.Close();
}

void makePlots::Event_Display(){

  Init();
  gStyle->SetPalette(54);
  gStyle->SetOptStat(0);
  gROOT->SetBatch(kTRUE);
  //TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  TCanvas *c1 = new TCanvas("c1","c1",6400,3600);
  c1->Divide(7,4);
  char title[50];

  int Nlayer = 28;
  TH2Poly *evtdis[Nlayer];

  for(int iL = 0; iL < Nlayer ; ++iL){
    evtdis[iL] = new TH2Poly();
    InitTH2Poly(*evtdis[iL]);
    sprintf(title,"Layer_%i",iL+1);
    evtdis[iL]->SetTitle(title);
  }

  TH2Poly *firstL = new TH2Poly();
  InitTH2Poly(*firstL);
  int counts = 0;
  for(int ev = 0; ev < nevents; ++ev){
    if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;
    
    GetData(ev);
    int Nhits;
    Nhits = NRechits;
    //cout << Nhits << endl;
    int layer;
    double posx,posy,posz,energy;
    double ENEPERMIP = 52.8e-03;
    
    double totalE = 0;
    for(int h = 0; h < Nhits ; ++h){
      Getinfo(h,layer,posx,posy,posz,energy);
      totalE += energy/ENEPERMIP;
    }
    if(totalE >= 140000 && totalE <= 150000 && ev < 10000){
      for(int h = 0; h < Nhits ; ++h){
	Getinfo(h,layer,posx,posy,posz,energy);
	//cout << "layer = " << layer << " , x = " << posx << ", y = " << posy << ", nmip = " << energy/ENEPERMIP <<endl;
	evtdis[layer-1]->Fill(posx,posy,energy/ENEPERMIP);
	if(layer == 1)
	  firstL->Fill(posx,posy,energy/ENEPERMIP);
	//cout << "hello~" << endl;
      }
    }
  }
  for(int iL = 0; iL < Nlayer ; ++iL){
    c1->cd(iL+1);
    evtdis[iL]->Draw("colz");
  }
  //c1->Update();
  sprintf(title,"plots/evt_dis/evt_display_%iavg.png",counts);
  //getchar();
  //c1->Update();

  c1->SaveAs(title);
  
  TCanvas *c2 = new TCanvas();
  firstL->Draw("samecolz");
  c2->Update();
  sprintf(title,"plots/evt_dis/evt_display_1st.png");
  c2->SaveAs(title);
  cout << "End?!" << endl;
  //getchar();
  
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

