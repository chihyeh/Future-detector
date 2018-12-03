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
makePlots::makePlots( TChain *c1,TChain *c2,TChain *c3,string filename ):T_Rechit(c1),T_DWC(c2),T_rechit_var(c3)
{
  cout << "Constructor of makePlot ... \n\n" << endl;
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
  //Rechit_var
  hit_mip = 0;
  hit_x = 0;
  hit_y = 0;
  hit_z = 0;

}
makePlots::makePlots( TChain *c1,TChain *c2,string filename ):T_Rechit(c1),T_rechit_var(c2)
{
    cout << "Constructor of makePlot ... \n\n" << endl;
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
    TestRun = true;    //Rechit_var
    
    hit_mip = 0;
    hit_x = 0;
    hit_y = 0;
    hit_z = 0;
    
}

//Destructor
makePlots::~makePlots()
{
  cout << "\n\n";
  cout << "Destructor of makePlot ... " << endl;
}

void makePlots::Init(){

  nevents = T_Rechit->GetEntries();

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
  T_Rechit->SetBranchAddress("rechit_type", &rechit_type);

  T_Rechit->SetBranchAddress("rechit_x", &rechit_x);
  T_Rechit->SetBranchAddress("rechit_y", &rechit_y);
  T_Rechit->SetBranchAddress("rechit_z", &rechit_z);
  T_Rechit->SetBranchAddress("rechit_iu", &rechit_iu);
  T_Rechit->SetBranchAddress("rechit_iv", &rechit_iv);
  T_Rechit->SetBranchAddress("rechit_energy", &rechit_energy);
  T_Rechit->SetBranchAddress("rechit_energy_noHG", &rechit_energy_noHG);

  T_Rechit->SetBranchAddress("rechit_amplitudeHigh", &rechit_amplitudeHigh);
  T_Rechit->SetBranchAddress("rechit_amplitudeLow", &rechit_amplitudeLow);
  T_Rechit->SetBranchAddress("rechit_hg_goodFit", &rechit_hg_goodFit);
  T_Rechit->SetBranchAddress("rechit_lg_goodFit", &rechit_lg_goodFit);
  T_Rechit->SetBranchAddress("rechit_hg_saturated", &rechit_hg_saturated);
  T_Rechit->SetBranchAddress("rechit_lg_saturated", &rechit_lg_saturated);
  T_Rechit->SetBranchAddress("rechit_fully_calibrated", &rechit_fully_calibrated);
  T_Rechit->SetBranchAddress("rechit_TS2High", &rechit_TS2High);
  T_Rechit->SetBranchAddress("rechit_TS2Low", &rechit_TS2Low);
  T_Rechit->SetBranchAddress("rechit_TS3High", &rechit_TS3High);
  T_Rechit->SetBranchAddress("rechit_TS3Low", &rechit_TS3Low);
    
  T_Rechit->SetBranchAddress("rechit_Tot", &rechit_Tot);
  T_Rechit->SetBranchAddress("rechit_time", &rechit_time);
  T_Rechit->SetBranchAddress("rechit_timeMaxHG", &rechit_timeMaxHG);
  T_Rechit->SetBranchAddress("rechit_timeMaxLG", &rechit_timeMaxLG);
  T_Rechit->SetBranchAddress("rechit_toaRise", &rechit_toaRise);
  T_Rechit->SetBranchAddress("rechit_toaFall", &rechit_toaFall);
  
  T_DWC ->SetBranchAddress("ntracks", &ntracks);
  T_DWC->SetBranchAddress("trackChi2_X", &trackChi2_X);
  T_DWC->SetBranchAddress("trackChi2_Y", &trackChi2_Y);
  T_DWC->SetBranchAddress("dwcReferenceType", &dwcReferenceType);
  T_DWC->SetBranchAddress("m_x", &m_x);
  T_DWC->SetBranchAddress("m_y", &m_y);
  T_DWC->SetBranchAddress("b_x", &b_x);
  T_DWC->SetBranchAddress("b_y", &b_y);

  T_rechit_var->SetBranchAddress("totalE_CEE", &totalE_CEE);
  T_rechit_var->SetBranchAddress("totalE_CEH", &totalE_CEH);
  T_rechit_var->SetBranchAddress("NLAYER", &NLAYER);
  T_rechit_var->SetBranchAddress("hit_mip", &hit_mip);
  T_rechit_var->SetBranchAddress("hit_x", &hit_x);
  T_rechit_var->SetBranchAddress("hit_y", &hit_y);
  T_rechit_var->SetBranchAddress("hit_z", &hit_z);
  T_rechit_var->SetBranchAddress("layerNhit", layerNhit);
  T_rechit_var->SetBranchAddress("totalE", &totalE);
  T_rechit_var->SetBranchAddress("layerE", layerE);
  T_rechit_var->SetBranchAddress("layerE1", layerE1);
  T_rechit_var->SetBranchAddress("layerE7", layerE7);
  T_rechit_var->SetBranchAddress("layerE19", layerE19);
  T_rechit_var->SetBranchAddress("layerE37", layerE37);
  
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

void makePlots::Loop(){
  
  double ENEPERMIP = 86.5e-03; // in MeV
  
  double X0_arr[NLAYER];
  double *X0_layer = Set_X0(X0_arr);

  Init();
  
  char title[100];
  int start = fname.find_last_of("/");
  int end = fname.find(".root");
  string f_substr = fname.substr(start+1,end-start-1);
  sprintf(title,"root_plot/%s_result.root",f_substr.c_str());
  cout << "output name : " << title << endl;

  TFile outf(title,"recreate");
  TH1D *h_E1devE7[NLAYER]; 
  TH1D *h_E7devE19[NLAYER];
  TH1F *h_Erec_CEE;
  TH1F *h_Erec_CEH;

  sprintf(title,"h_Erec_CEE",)
  h_Erec_CEE = new TH1F(title,title,400,0,16000);
  sprintf(title,"h_Erec_CEH",)
  h_Erec_CEH = new TH1F(title,title,400,0,16000);
    
  for(int iL = 0; iL < NLAYER ; ++iL){
    sprintf(title,"layer%i_E1devE7",iL);
    h_E1devE7[iL] = new TH1D(title,title,101,0,1.01);
    sprintf(title,"layer%i_E7devE19",iL);
    h_E7devE19[iL] = new TH1D(title,title,101,0,1.01);
  }

  for(int ev = 0; ev < nevents; ++ev){
    if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;
    
    GetData(ev);
    int Nhits = NRechits;

    // Event Selection
    //if ( Nhits < 200 ) continue;
    //if ( dwcReferenceType != 15) continue;

      h_Erec_CEE->Fill(totalE_CEE);
      h_Erec_CEH->Fill(totalE_CEH);

    for(int iL = 0; iL < NLAYER ; ++iL){
      //Fill shower shape histogram
      if( layerE1[iL] != 0){
	double E1devE7  = layerE1[iL]/layerE7[iL];
	double E7devE19 = layerE7[iL]/layerE19[iL];
	h_E1devE7 [iL]->Fill(E1devE7);
	h_E7devE19[iL]->Fill(E7devE19);}

      //If one wants to do sth with hits
      vector<double> x,y,z,ene;
      x   = hit_x->at(iL);
      y   = hit_y->at(iL);
      z   = hit_z->at(iL);
      ene = hit_mip->at(iL);
      for(int iH = 0; iH < layerNhit[iL] ; ++iH){
	//cout << ene[iH] << endl;
      }}

    // Calculate the shower depth
    double SHD_Elayer = 0;
    
    for(int iL = 0 ; iL < NLAYER ; ++iL){
      SHD_Elayer += X0_layer[iL]*layerE[iL];}
    SHD_Elayer /= totalE;
    // shower depth = SHD_Elayer (calculation done!)
  }
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
    if(totalE >= 140000 && ev < 10000){
      counts++;
      for(int h = 0; h < Nhits ; ++h){
	Getinfo(h,layer,posx,posy,posz,energy);
	//cout << "layer = " << layer << " , x = " << posx << ", y = " << posy << ", nmip = " << energy/ENEPERMIP <<endl;
	evtdis[layer-1]->Fill(posx,posy,energy/ENEPERMIP);
	if(layer == 1)
	  firstL->Fill(posx,posy,energy/ENEPERMIP);

      }
    }
  }
  for(int iL = 0; iL < Nlayer ; ++iL){
    c1->cd(iL+1);
    evtdis[iL]->Draw("colz");
  }
  //c1->Update();
  sprintf(title,"plots/evt_dis/evt_display_%ievts_avg.png",counts);
  //getchar();
  //c1->Update();

  c1->SaveAs(title);
  
  TCanvas *c2 = new TCanvas();
  firstL->Draw("samecolz");
  c2->Update();
  sprintf(title,"plots/evt_dis/evt_display_1st.png");
  c2->SaveAs(title);

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
