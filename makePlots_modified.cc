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
#include "TGraphErrors.h"

//Constructor
makePlots::makePlots(){
    TestRun = false;
    Init();}
makePlots::makePlots( TChain *c1,TChain *c2,TChain *c3,string filename ):T_Rechit(c1),T_DWC(c2),T_rechit_var(c3)
{
    cout << "Data and MC: Constructor of makePlot ... \n\n" << endl;
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
  T_rechit_var->SetBranchAddress("layerE61", layerE61);

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
    
    NLAYER_ALL = NLAYER_EE + NLAYER_FH ;
    cout << "Beam type = "<< beam_str.c_str()  << " , Energy = "<< beamE
    << "GeV" << ", setup_config = "  << setup_config << endl;
}

void makePlots::GetData(int evt){
    if(TestRun){
        T_Rechit-> GetEntry(evt);
        T_rechit_var  -> GetEntry(evt);
    }
    if(!TestRun){
        if(Is_Data){
            T_Rechit-> GetEntry(evt);
            T_rechit_var  -> GetEntry(evt);
            T_DWC -> GetEntry(evt);}
        else{
            T_Rechit-> GetEntry(evt);
            T_rechit_var  -> GetEntry(evt);}
    }
}

void makePlots::Getinfo(int ihit,int &layer,double &x, double &y,double &z,double &ene){
    if(Is_Data)
	{
    layer = rechit_layer->at(ihit);
    x     = rechit_x    ->at(ihit);
    y     = rechit_y    ->at(ihit);
    z     = rechit_z    ->at(ihit);
    ene   = (rechit_energy->at(ihit))*(1);
	}
    else
	{
    layer = rechit_layer->at(ihit);
    x     = rechit_x    ->at(ihit);
    y     = rechit_y    ->at(ihit);
    z     = rechit_z    ->at(ihit);
    ene   = (rechit_energy->at(ihit))*(1);
	}
}
int makePlots::GetBeamE(){
     Init();
     return(beamE);
}
//========GetHistoEtotal========//
TH1F* makePlots::GetHistoEtotal(vector<int> Good_layer_number,vector<int> Bad_layer_number, vector<float> Chi2test, int resolution_number){
  Init();
  char title[100];
  double X0_arr[NLAYER_ALL];
  double *X0_layer = Set_X0(X0_arr);
  cout << "Run GetHistoEtotal function" << endl;
  TH1F *h_totalE_with_good_layer;
  int iL_number = Good_layer_number.size();
  for(int i = 0; i < 28 ; i++)
  {
	cout << "Chi2test" << Chi2test[i] << endl;
  }
  if(Is_Data)
  {
    sprintf(title,"total_energy_with_%i_good_layers_Add_1_bad_layer_Data",iL_number);
    h_totalE_with_good_layer = new TH1F(title,title,500,0,10000);
  }
  else
  {  
    sprintf(title,"total_energy_with_%i_good_layers_Add_1_bad_layer_MC",iL_number);
    h_totalE_with_good_layer = new TH1F(title,title,500,0,10000);
  }
 // float totalE=0;
  // vector<float> Bad_Layer_resolution;
  vector<int> Bad_layers_resolution_counting={0,0,0,0,0,0,0,0,0,0,0};
  vector<int> Bad_layers={1,4,7,8,10,14,16,18,19,22,24};
  vector<int> Bad_layers_for_computing={3,7,13,15,17,18,21,23};
  float shower_depth_max=9;
  float shower_depth_max_for_calculate=8;
//===========================
   vector<float> Bad_Layer_resolution;
   vector<float> Bad_layer_calculation;
   cout << "Close5" << endl;

   for(int N = 0 ; N < 28 ; N++)
        { 
        for(int i = 0 ; i < 28 - iL_number-3 ; i++)
         {
        if(abs((Bad_layers_for_computing[i]-shower_depth_max_for_calculate))==N)Bad_layer_calculation.push_back(Bad_layers_for_computing[i]);
        else continue;
	}
        if(Bad_layer_calculation.size()==2)
        { 
   	cout << "Close3" << endl;     
	cout << "Bad_layer_calculation.size()" << Bad_layer_calculation.size() << endl;
	cout << "Bad_layer_calculation[0]" << Bad_layer_calculation[0] << endl;
        cout << "Bad_layer_calculation[1]" << Bad_layer_calculation[1] << endl;
                if(Chi2test[Bad_layer_calculation[0]]>Chi2test[Bad_layer_calculation[1]])
                {       
       			 cout << "Close6" << endl;      
                        Bad_Layer_resolution.push_back(Bad_layer_calculation[1]);
                        Bad_Layer_resolution.push_back(Bad_layer_calculation[0]);
                }   
                else
                {       
                         cout << "Close9" << endl;
                        Bad_Layer_resolution.push_back(Bad_layer_calculation[0]);
                        Bad_Layer_resolution.push_back(Bad_layer_calculation[1]);
                }
        }
        else if(Bad_layer_calculation.size()==1)
	{
        cout << "Close10" << endl;
	Bad_Layer_resolution.push_back(Bad_layer_calculation[0]);
	}
	else continue;        
	Bad_layer_calculation.clear();
	}
	for(int i = 0 ; i < 28 - iL_number-3 ; i++)
	{
                         cout << "Close11" << endl;
		cout << "Bad-layers-sequence" << Bad_Layer_resolution[i] << endl;
	}
	for(int iL = 0 ; iL < resolution_number ; ++iL)
  	{
                         cout << "Close12" << endl;
		Good_layer_number.push_back(Bad_Layer_resolution[iL]);
	}
   cout << "Close4" << endl;
    for(int ev = 0; ev < nevents; ++ev)
    {
    float totalE=0;
    if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;
    GetData(ev);
    int Nhits = NRechits;
       //=========calculate the shower depth========//
   //    cout << "Close1" << endl;  
   for(int iL = 0 ; iL < iL_number+resolution_number ; ++iL) 
       {
        if(layerE[Good_layer_number[iL]]<=20)continue;
        if(Is_Data)
        {if(b_x > -2 and b_x < 1 and b_y > -1 and b_y < 2 and trackChi2_X < 5 and trackChi2_X < 5)totalE = totalE + layerE[Good_layer_number[iL]]*(1.055);}
        else
        {totalE = totalE + layerE[Good_layer_number[iL]]*(1);}
        }
    if(ev==1 or ev==2) 
    {//cout << "totalE" << totalE << endl;
     for(int iL=0 ; iL < iL_number ; ++iL)
    {cout << Good_layer_number[iL] << endl;}}	
    h_totalE_with_good_layer->Fill(totalE);
   	}
   return(h_totalE_with_good_layer);
   }
//=========GetTGraphErrors========//
TGraphErrors* makePlots::GetTGraphErrors(vector<float> X, vector<float> Y, vector<float> X_Errors, vector<float>Y_Errors)
{
  Init();
  cout << "======In Loop of GetTGraphErrors===" << endl;
  cout << "runN:" << runN << endl;
  cout << "beamE:" << beamE << endl;
  cout << "===================================" << endl;

  TGraphErrors* Plot = new TGraphErrors(18,&X[0],&Y[0],&X_Errors[0],&Y_Errors[0]);
  //Plot->Write("Run%i_%i_bx_cut_TGraphErrors",runN,beamE);
  return(Plot);
}


//========GetHistoE=======//
vector<TH1F*> makePlots::Loop_for_TH1F(vector<float> dEdXMEVperMIP, vector<float> INVSF, float Scale ,int arg_method,int energy_arrangement){
   
  char title[100];char title1[100];char title2[100]; char title3[100];char title4[100];
    cout << "Welcome to TH1F world!" << endl;
  double ENEPERMIP = 86.5e-03; // in MeV
  Init();
// arg_method=0 for no scale, arg_method=1 for dEdX, arg_method=2 for SF //
    if(arg_method==0) cout << "No scale, Raw data to see it" << endl;
    if(arg_method==1) cout << "dEdX Method - Calibration" << endl;
    if(arg_method==2) cout << "Sf   Method - Calibration" << endl;
//===============Claim the histograms with range and parameters ( Pay attention! The range will impact on the resolution of the linearity ! )===========//
  int Bin;
  if(arg_method==0)Bin=100000;
  if(arg_method==1)Bin=4000;
  if(arg_method==2)Bin=4000; 
  
  TH1F *h_layer_energy[30];
  vector<TH1F*> h_layer_energy_return;

    if(Is_Data==1)
	{
        sprintf(title,"Run%i_total_energy_Data",runN);
    h_layer_energy[0] = new TH1F(title,title,Bin,0,1000);
	}
 
    if(Is_Data==0)
        {
        sprintf(title3,"%iGeV_total_energy_MC",beamE);
    h_layer_energy[0] = new TH1F(title3,title3,Bin,0,1000);
        }
//==============Check the type and events==============//
   cout << "nevents" << nevents << endl;
   cout << "Data_type: " << Is_Data << endl;
   
//=============Ready for storing the events===========//
   cout << "Scale=" << Scale << endl;
    
    for(int ev = 0; ev < nevents; ++ev)
	{
   float totalE = 0;
   if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;
    GetData(ev);
    int Nhits = NRechits;
//=======Raw_Hits_energy=====//
/*
    vector<float> RawEne_Layer;
    for(int iL = 0; iL < NLAYER_EE ; ++iL)
	{
	float Raw_totalE = 0 ;
	float Raw_totalE_Check = 0 ;
	vector<double> x,y,z,ene;
        x   = hit_x->at(iL);
        y   = hit_y->at(iL);
        z   = hit_z->at(iL);
        ene = hit_mip->at(iL);
        for(int iH = 0; iH < layerNhit[iL] ; ++iH)
        {
	if(ene[iH]>0 and ene[iH]<200)  (Raw_totalE_Check) = (Raw_totalE_Check) + ene[iH];	
        }
	RawEne_Layer.push_back(Raw_totalE_Check);
	}*/
//=====================================//
    for(int iL = 0; iL < NLAYER_EE ; ++iL)
    {
	
    //=======Different abilities of Converting the MIPs to GeV since the 200m and 300m======//
	float Convert_par;
	if(iL < 26) Convert_par=85.5e-06;
	if(iL > 26) Convert_par=57.6e-06;
	//=============Different method======================//
    if(Is_Data==1)
        {
    if(arg_method==0){if( b_x > (-1.7) and b_x < (-0.7)and b_y > (0) and b_y < (1.5))totalE = totalE + ((layerE[iL]*(1))*(Scale)*(1)*(Convert_par));}
    if(arg_method==1){if( b_x > (-1.7) and b_x < (-0.7)and b_y > (0) and b_y < (1.5))totalE = totalE + (layerE[iL]*(dEdXMEVperMIP[iL]*(10e+06))*(Scale)*(1)/(10e+09));}
    if(arg_method==2){if( b_x > (-1.7) and b_x < (-0.7)and b_y > (0) and b_y < (1.5))totalE = totalE + ((1.054)*(layerE[iL]*(1))*(Scale)*(1)*(Convert_par)*INVSF[energy_arrangement]);}
        }

    if(Is_Data==0)
        {
    if(arg_method==0){totalE = totalE + ((layerE[iL]*(1))*(1)*(Convert_par));}
    if(arg_method==1){totalE = totalE + (layerE[iL]*(dEdXMEVperMIP[iL]*(10e+06))*(1)/(10e+09));}
    if(arg_method==2){totalE = totalE + ((1.054)*layerE[iL]*(1))*(1)*(Convert_par)*INVSF[energy_arrangement];} 
        }
	}
	if(totalE > 0) h_layer_energy[0]->Fill( (totalE) );	
	}
       h_layer_energy_return.push_back(h_layer_energy[0]);
    
return(h_layer_energy_return);
}
//=========Loop function=======//

vector<TH2F*> makePlots::Loop_for_TH2F(vector<float> dEdXMEVperMIP, vector<float> INVSF, float Scale ,int arg_method,int energy_arrangement,float True_energy)
{
    vector<TH2F*> Return_TH2F;
    cout << "Welcome to TH2F world!" << endl;
    if(arg_method==0) cout << "No scale, Raw data to see it" << endl;
    if(arg_method==1) cout << "dEdX Method - Calibration" << endl;
    if(arg_method==2) cout << "Sf   Method - Calibration" << endl;

  double ENEPERMIP = 86.5e-03; // in MeV
  Init();
  double X0_arr[NLAYER_ALL];
  double *X0_layer = Set_X0(X0_arr);
  cout << "nevents" << nevents << endl;
  char title[100]; char title1[100];
//=======================Claim_variables====================//
    float xmax;
    if(arg_method==0)xmax=200;
    if(arg_method==1)xmax=1;
  sprintf(title1,"TH2F_Run%i_SF-1_SD_Data",runN);
  TH2F *TH2F_SFvsSD  = new TH2F(title1,title1,112,0,28,xmax/1000,0,xmax);

  cout << "Is_Data: " << Is_Data << endl;
  //===============parameters for calculate E10 related number========//

  for(int ev = 0; ev < nevents; ++ev){
    if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;
      float totalE=0;
    GetData(ev);
    int Nhits = NRechits;
//=======================================
    double Shower_depth_CEE = 0;
    double Shower_depth_total = 0;
    
    for(int iL = 0 ; iL < NLAYER_ALL ; ++iL)
    {
		if(iL < NLAYER_EE)
		{
			Shower_depth_CEE   += X0_layer[iL]*layerE[iL];
		}
        if(iL < NLAYER_ALL)
        {
            Shower_depth_total += X0_layer[iL]*layerE[iL];
        }
    }
         Shower_depth_CEE /= totalE_CEE;
	     Shower_depth_total /= ( totalE_CEE + totalE_CEH );
//=======================================
      for(int iL = 0; iL < NLAYER_EE ; ++iL)
      {
          
          //=======Different abilities of Converting the MIPs to GeV since the 200m and 300m======//
          float Convert_par;
          if(iL < 26) Convert_par=85.5e-06;
          if(iL > 26) Convert_par=57.6e-06;
          //=============Different method======================//
          if(Is_Data==1)
          {
              if(arg_method==0){if( b_x > (-1.7) and b_x < (-0.7)and b_y > (0) and b_y < (1.5))totalE = totalE + ((layerE[iL]*(1))*(Scale)*(1)*(Convert_par));}
              if(arg_method==1){if( b_x > (-1.7) and b_x < (-0.7)and b_y > (0) and b_y < (1.5))totalE = totalE + (layerE[iL]*(dEdXMEVperMIP[iL]*(10e+06))*(Scale)*(1)/(10e+09));}
              if(arg_method==2){if( b_x > (-1.7) and b_x < (-0.7)and b_y > (0) and b_y < (1.5))totalE = totalE + ((1.054)*(layerE[iL]*(1))*(Scale)*(1)*(Convert_par)*INVSF[energy_arrangement]);}
          }
          
          if(Is_Data==0)
          {
              if(arg_method==0){totalE = totalE + ((layerE[iL]*(1))*(1)*(Convert_par));}
              if(arg_method==1){totalE = totalE + (layerE[iL]*(dEdXMEVperMIP[iL]*(10e+06))*(1)/(10e+09));}
              if(arg_method==2){totalE = totalE + ((1.054)*layerE[iL]*(1))*(1)*(Convert_par)*INVSF[energy_arrangement];}
          }
      }


  if(Is_Data)
    {
	
      if(b_x > -1.7 and b_x < -0.7 and b_y > 0 and b_y < 1.5)
      {
          SFvsSD->Fill( (Shower_depth_CEE), (True_energy/totalE) );
      }
	}
   else//for MC
    {
          SFvsSD->Fill( (Shower_depth_CEE), (True_energy/totalE) );
    }
  }
    Return_TH2F.push_back(TH2F_SFvsSD);
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
    double single_layer_X0[NLAYER_ALL];
    //Temporarily assign 4.5X0 to all the absorber layer in FH
    if(setup_config < 2){
        cout << "setup_config" << setup_config << endl;
        for( int i = 0 ; i < NLAYER_EE ; ++i){
            if ( i % 2 == 0) single_layer_X0[i] = 0.909;
            else single_layer_X0[i] = 0.976;
        }
        single_layer_X0[0]  = 0.933;
        single_layer_X0[15] = 1.143;
        single_layer_X0[19] = 1.143;
        single_layer_X0[23] = 1.06;
        if(setup_config == 0){
            cout << "NLAYER_EE" << NLAYER_EE << endl;
            cout << "NLAYER_ALL" << NLAYER_ALL << endl;
            for(int i = NLAYER_EE ; i < NLAYER_ALL ; ++i){
                single_layer_X0[i]  = 4.5;}
        }
        else{
            single_layer_X0[NLAYER_EE]    = 0;
            single_layer_X0[NLAYER_EE+1]  = 0;
            for(int i = NLAYER_EE+2 ; i < NLAYER_ALL ; ++i){
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
        for(int i = NLAYER_EE ; i < NLAYER_ALL ; ++i){
            single_layer_X0[i]  = 4.5;}
    }
    double X0_sum = 0.;
    for(int iL = 0 ; iL < NLAYER_ALL ; ++iL){
        X0_sum += single_layer_X0[iL];
        X0_arr[iL] = X0_sum;
        //cout << "X0_sum" << X0_sum << endl;
    }
    
    return X0_arr;
}
