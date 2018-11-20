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
  T_rechit_var->SetBranchAddress("layerE63",layerE63);
  T_rechit_var->SetBranchAddress("layerE19out",layerE19out);
  T_rechit_var->SetBranchAddress("layerE37out",layerE37out);
  T_rechit_var->SetBranchAddress("layerE63out",layerE63out);

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

  cout << beam_str.c_str()  << " , "<< beamE << "GeV\n" << endl;
}

void makePlots::GetData(int evt){

    T_Rechit      -> GetEntry(evt);
    T_DWC         -> GetEntry(evt);
    T_rechit_var  -> GetEntry(evt);
}

void makePlots::Getinfo(int ihit,int &layer,double &x, double &y,double &z,double &ene){
    layer = rechit_layer->at(ihit);
    x     = rechit_x    ->at(ihit);
    y     = rechit_y    ->at(ihit);
    z     = rechit_z    ->at(ihit);
    ene   = rechit_energy->at(ihit);
}

vector<float> makePlots::Loop(){
  
  int NLAYER = 28;
  double ENEPERMIP = 86.5e-03;
  double X0_arr[NLAYER];
  double *X0_layer = Set_X0(X0_arr);


  Init();
  TCanvas *c1 = new TCanvas();
 
  char title[100];
  int start = fname.find_last_of("/");
  int end = fname.find(".root");
  string f_substr = fname.substr(start+1,end-start-1);
  sprintf(title,"Delta_ray_candidate_search/%s_ring_result.root",f_substr.c_str());
  cout << "output name : " << title << endl;
  TFile outf(title,"recreate");
  //TH1D *h_E1devE7[NLAYER]; 
  //TH1D *h_E7devE37[NLAYER];
  //TH1D *h_E7devE37_09_1_layer;
  TH1D *h_DWCf3_Dis_X;
  TH1D *h_DWCf3_Dis_Y;
  TH1D *h_DWCf5_Dis_X;
  TH1D *h_DWCf5_Dis_Y;
  TH1D *h_how_many_layers_less_than_3_MIPs_seed;
  TH1D *h_how_many_layers_less_than_3_MIPs_total;
  TH1D *h_E28_Seed;
  //TH1D *h_totalE_last_detector_delta_ray_Candidate;
  //TH1D *h_shower_depth_ring_total_cut;
  TH1D *h_shower_depth_ring_cut_have_last_detector_cut; 
  //TH1D *h_shower_depth_ring_3MIP_no_last_detector_cut_seed;
  TH1D *h_shower_depth_ring_less_3MIP_have_last_detector_cut_seed;
  TH1D *h_shower_depth_ring_more_3MIP_have_last_detector_cut_seed;
  //TH1D *h_shower_depth_ring_3MIP_cut_total;
  
  TH2D *h_totalE_E28_Seed;
  TH2D *h_shower_depth_vs_totalE_ring_cut_have_last_detector_cut;
  TH2D *h_shower_depth_vs_totalE_Per_Ele_Candidate_have_last_detector_cut;
  TH2D *h_shower_depth_vs_totalE_delta_ray_Candidate_have_last_detector_cut;
  
  TH1D *h_energy_to_10_Ele;
  TH1D *h_energy_to_10_Per_Ele;
  TH1D *h_energy_to_10_Delta_ray;
  TH1D *h_energy_to_5_Ele;
  TH1D *h_energy_to_5_Per_Ele;
  TH1D *h_energy_to_5_Delta_ray;

  TH1D *h_energy_to_10_Delta_ray_no_cut;
  TH1D *h_energy_to_10_Delta_ray_after_5_ring_cut;
  TH1D *h_energy_to_10_Delta_ray_after_5_ring_cut_plus_three_MIPs_cut;
  TH1D *h_energy_to_10_Delta_ray_after_5_ring_cut_plus_three_MIPs_075_cut;
  TH1D *h_energy_to_10_Delta_ray_after_all_cut;

  /*TH1D *h_shower_depth_5_to_10_totalE;
  TH1D *h_totalE;
  TH1D *h_leak_back_three_layers_energy_seed;
  TH1D *h_leak_back_three_layers_energy_total;
  */
  //TH1D *h_back_three_layer_totalE;
 // TH1D *h_forward_5_layer_totalE
  //TH1D *h_smaller_than_point_9_shower_depth;
  //TH1D *h_bigger_than_point_9_shower_depth;
  /*TH1D *h_layerE19;
  TH1D *h_layerE37;
  TH1D *h_layerE63;
  TH1D *h_layerEout19;
  TH1D *h_layerEout37;
  TH1D *h_layerEout63;
  */
  //TH1D *h_layer_8_to_15_E1devE7;
  //TH1D *h_layer_8_to_15_E7devE37;
  /*TH1D *h_Ratio_in_total_layerE19;
  TH1D *h_Ratio_in_total_layerE37;
  TH1D *h_Ratio_in_total_layerE63;
  TH1D *h_Ratio_out_total_layerE19;
  TH1D *h_Ratio_out_total_layerE37;
  */
  //TH1D *h_Ratio_out_total_layerE63;
 
  //TH1D *h_shower_depth;
  //TH2D *h_Correlation_totalE_shower_depth;
  
  /*TH1D *h_how_many_layers_less_than_3_MIPs_seed;
  TH1D *h_how_many_layers_less_than_3_MIPs_total; 
  TH1D *h_5layers_more_less_than_3MIP_seed_totalE;
  TH1D *h_5layers_more_less_than_3MIP_total_totalE;
  TH1D *h_5layers_more_less_than_3MIP_seed_shower_depth;
  TH1D *h_5layers_more_less_than_3MIP_total_shower_depth;
  TH1D *h_5layers_more_less_than_3MIP_seed_last_three_layer_energy;
  TH1D *h_5layers_more_less_than_3MIP_total_last_three_layer_energy;
  */
  /*
  TH1D *total_energy;
  TH1D *total_energy_last_three_layer;
  TH1D *h_layer_8_9_10_E1devE7;
  TH1D *h_layer_8_9_10_E7devE37;
  TH1D *h_layer_9_10_11_E1devE7;
  TH1D *h_layer_9_10_11_E7devE37;
  TH1D *h_layer_8_E1devE7;
  TH1D *h_layer_8_E7devE37;
  TH1D *h_layer_9_E1devE7;
  TH1D *h_layer_9_E7devE37;
  TH1D *h_layer_10_E1devE7;
  TH1D *h_layer_10_E7devE37;
  TH1D *h_layer_11_E1devE7;
  TH1D *h_layer_11_E7devE37;
  TH1D *h_layer_total_E1devE7;
  TH1D *h_layer_total_E7devE37;*/
  //TH1D *h_layer_E1energy[NLAYER]; 
  //TH1D *h_first_5layers_E1energy;
  //TH1D *h_last_5layers_E1energy;
  /*for(int iL = 0; iL < NLAYER ; ++iL){
    sprintf(title,"layer%i_E1energy",iL);
    h_layer_E1energy[iL] = new TH1D(title,title,500,0,1000);
  }*/
   // sprintf(title,"first_5layers_E1energy");
   // h_first_5layers_E1energy = new TH1D(title,title,10,0,20);
   // sprintf(title,"last_3layers_E1energy");
   // h_first_5layers_E1energy = new TH1D(title,title,20,0,20);
  /*for(int iL = 0; iL < NLAYER ; ++iL){
    sprintf(title,"layer%i_E1devE7",iL);
    h_E1devE7[iL] = new TH1D(title,title,101,0,1.01);
    sprintf(title,"layer%i_E7devE37",iL);
    h_E7devE37[iL] = new TH1D(title,title,101,0,1.01);
  }*/
   /*TH1D *h_layer8_E7devE37_Perfect_electron_candidate;
   TH1D *h_layer9_E7devE37_Perfect_electron_candidate;
   TH1D *h_layer10_E7devE37_Perfect_electron_candidate;
  */ 
  //TH1D *h_layerall_E7devE37_no_last_detector_Perfect_electron_candidate;
  //TH1D *h_layerall_E7devE19_no_last_detector_Perfect_electron_candidate;
  TH1D *h_layerall_E7devE37_have_last_detector_Perfect_electron_candidate;
  TH1D *h_layerall_E7devE19_have_last_detector_Perfect_electron_candidate;  
  TH1D *h_layerall_E7devE37_have_last_detector_Perfect_electron_candidate_before_contamination_cut;
  TH1D *h_layerall_E7devE19_have_last_detector_Perfect_electron_candidate_before_contamination_cut;
  

/* sprintf(title,"layer8_E7devE37_Perfect_electron_candidate");
   h_layer8_E7devE37_Perfect_electron_candidate = new TH1D(title,title,25,0,1);
   sprintf(title,"layer9_E7devE37_Perfect_electron_candidate");
   h_layer9_E7devE37_Perfect_electron_candidate = new TH1D(title,title,25,0,1);
   sprintf(title,"layer10_E7devE37_Perfect_electron_candidate");
   h_layer10_E7devE37_Perfect_electron_candidate = new TH1D(title,title,25,0,1);
  */
   sprintf(title,"layerall_E7devE37_have_last_detector_Perfect_electron_candidate");
   h_layerall_E7devE37_have_last_detector_Perfect_electron_candidate = new TH1D(title,title,70,0.3,1);
   sprintf(title,"layerall_E7devE19_have_last_detector_Perfect_electron_candidate");
   h_layerall_E7devE19_have_last_detector_Perfect_electron_candidate = new TH1D(title,title,70,0.3,1);
   sprintf(title,"layerall_E7devE37_have_last_detector_Perfect_electron_candidate_before_contamination_cut");
   h_layerall_E7devE37_have_last_detector_Perfect_electron_candidate_before_contamination_cut = new TH1D(title,title,70,0.3,1);
   sprintf(title,"layerall_E7devE19_have_last_detector_Perfect_electron_candidate_before_contamination_cut");
   h_layerall_E7devE19_have_last_detector_Perfect_electron_candidate_before_contamination_cut = new TH1D(title,title,70,0.3,1);


   /*sprintf(title,"layerall_E7devE37_no_last_detector_Perfect_electron_candidate");
   h_layerall_E7devE37_no_last_detector_Perfect_electron_candidate = new TH1D(title,title,20,0.8,1);
   sprintf(title,"layerall_E7devE19_no_last_detector_Perfect_electron_candidate");
   h_layerall_E7devE19_no_last_detector_Perfect_electron_candidate = new TH1D(title,title,20,0.8,1);
   */
  /* TH1D *h_layer20_E7devE37_delta_ray_candidate;
   TH1D *h_layer21_E7devE37_delta_ray_candidate;
   TH1D *h_layer22_E7devE37_delta_ray_candidate;
   TH1D *h_layer23_E7devE37_delta_ray_candidate;
   TH1D *h_layer24_E7devE37_delta_ray_candidate;
   TH1D *h_layer25_E7devE37_delta_ray_candidate;
  */ 
  TH1D *h_layerall_E7devE37_have_last_detector_delta_ray_candidate;
  TH1D *h_layerall_E7devE19_have_last_detector_delta_ray_candidate;
  TH1D *h_layerall_E7devE37_have_last_detector_delta_ray_candidate_before_contamination_cut;
  TH1D *h_layerall_E7devE19_have_last_detector_delta_ray_candidate_before_contamination_cut;

   /*sprintf(title,"layer20_E7devE37_delta_ray_candidate");
   h_layer20_E7devE37_delta_ray_candidate = new TH1D(title,title,25,0,1);
   sprintf(title,"layer21_E7devE37_delta_ray_candidate");
   h_layer21_E7devE37_delta_ray_candidate = new TH1D(title,title,25,0,1);
   sprintf(title,"layer22_E7devE37_delta_ray_candidate");
   h_layer22_E7devE37_delta_ray_candidate = new TH1D(title,title,25,0,1);
   sprintf(title,"layer23_E7devE37_delta_ray_candidate");
   h_layer23_E7devE37_delta_ray_candidate = new TH1D(title,title,25,0,1);
   sprintf(title,"layer24_E7devE37_delta_ray_candidate");
   h_layer24_E7devE37_delta_ray_candidate = new TH1D(title,title,25,0,1);
   sprintf(title,"layer25_E7devE37_delta_ray_candidate");
   h_layer25_E7devE37_delta_ray_candidate = new TH1D(title,title,25,0,1);
*/
/*	sprintf(title,"layerall_E7devE37_no_last_detector_delta_ray_candidate");
   h_layerall_E7devE37_no_last_detector_delta_ray_candidate = new TH1D(title,title,20,0.8,1);
        sprintf(title,"layerall_E7devE19_no_last_detector_delta_ray_candidate");
   h_layerall_E7devE19_no_last_detector_delta_ray_candidate = new TH1D(title,title,20,0.8,1);
*/  
      sprintf(title,"layerall_E7devE37_have_last_detector_delta_ray_candidate");
   h_layerall_E7devE37_have_last_detector_delta_ray_candidate = new TH1D(title,title,70,0.3,1);
        sprintf(title,"layerall_E7devE19_have_last_detector_delta_ray_candidate");
   h_layerall_E7devE19_have_last_detector_delta_ray_candidate = new TH1D(title,title,70,0.3,1);
      sprintf(title,"layerall_E7devE37_have_last_detector_delta_ray_candidate_before_contamination_cut");
   h_layerall_E7devE37_have_last_detector_delta_ray_candidate_before_contamination_cut = new TH1D(title,title,70,0.3,1);
        sprintf(title,"layerall_E7devE19_have_last_detector_delta_ray_candidate_before_contamination_cut");
   h_layerall_E7devE19_have_last_detector_delta_ray_candidate_before_contamination_cut = new TH1D(title,title,70,0.3,1);

  /* TH1D *h_layer8_E7devE37_MC_electron;
   TH1D *h_layer9_E7devE37_MC_electron;
   TH1D *h_layer10_E7devE37_MC_electron;
   */
	TH1D *h_layerall_E7devE37_have_last_detector_MC_electron;
        TH1D *h_layerall_E7devE19_have_last_detector_MC_electron;
  //      TH1D *h_layerall_E7devE37_no_last_detector_MC_electron;
    //    TH1D *h_layerall_E7devE19_no_last_detector_MC_electron;

   /*sprintf(title,"layer8_E7devE37_MC_electron");
   h_layer8_E7devE37_MC_electron = new TH1D(title,title,25,0,1);
   sprintf(title,"layer9_E7devE37_MC_electron");
   h_layer9_E7devE37_MC_electron = new TH1D(title,title,25,0,1);
   sprintf(title,"layer10_E7devE37_MC_electron");
   h_layer10_E7devE37_MC_electron = new TH1D(title,title,25,0,1);
   */
  sprintf(title,"layerall_E7devE37_have_last_detector_MC_electron");
   h_layerall_E7devE37_have_last_detector_MC_electron = new TH1D(title,title,70,0.3,1);
  //sprintf(title,"layerall_E7devE37_no_last_detector_MC_electron");
  // h_layerall_E7devE37_no_last_detector_MC_electron = new TH1D(title,title,20,0.8,1);
  sprintf(title,"layerall_E7devE19_have_last_detector_MC_electron");
   h_layerall_E7devE19_have_last_detector_MC_electron = new TH1D(title,title,70,0.3,1);
  //sprintf(title,"layerall_E7devE19_no_last_detector_MC_electron");
  // h_layerall_E7devE19_no_last_detector_MC_electron = new TH1D(title,title,20,0.8,1);

       TH1D *h_layerall_E7devE37_have_last_detector_before_contamination_cut;
       TH1D *h_layerall_E7devE19_have_last_detector_before_contamination_cut;
       sprintf(title,"layerall_E7devE37_have_last_detector_before_contamination_cut");
        h_layerall_E7devE37_have_last_detector_before_contamination_cut = new TH1D(title,title,70,0.3,1);
       sprintf(title,"layerall_E7devE19_have_last_detector_before_contamination_cut");
       h_layerall_E7devE19_have_last_detector_before_contamination_cut = new TH1D(title,title,70,0.3,1);








    vector<float> XLayer_Ele;
    vector<float> YMIPs_Ele;
    vector<float> XLayer_Delta;
    vector<float> YMIPs_Delta;
    char GR_save[50], GR_save_1[50];
    TGraph *h_event_delta_ray_candidate[50];
    TGraph *h_event_Perfect_electron_candidate[50];
  
  //for(int iL = 0; iL < 50 ; ++iL){
     //sprintf(title,"h_event%i_delta_ray_candidate",iL);
    // h_event_delta_ray_candidate[iL] = new TGraph(28,);
     //}


  h_DWCf3_Dis_X = new TH1D ("h_DWCf3_Dis_X","h_DWCf3_Dis_X",20,-10,10);
  h_DWCf3_Dis_Y = new TH1D ("h_DWCf3_Dis_Y","h_DWCf3_Dis_Y",20,-10,10);
  h_DWCf5_Dis_X = new TH1D ("h_DWCf5_Dis_X","h_DWCf5_Dis_X",20,-10,10);
  h_DWCf5_Dis_Y = new TH1D ("h_DWCf5_Dis_Y","h_DWCf5_Dis_Y",20,-10,10);
  
   // sprintf(title,"totalE");
    //h_totalE = new TH1D (title,title,400,0,16000);
   /*
    sprintf(title,"shower_depth");
    h_shower_depth = new TH1D (title,title,112,0,28);
    sprintf(title,"Correlation_totalE_shower_depth");
    h_Correlation_totalE_shower_depth = new TH2D (title,title,112,0,28,400,0,16000);
   */
    /*sprintf(title,"how_many_layers_less_than_3_MIPs_seed");
    h_how_many_layers_less_than_3_MIPs_seed = new TH1D (title,title,15,0,15);
    sprintf(title,"how_many_layers_less_than_3_MIPs_total");
    h_how_many_layers_less_than_3_MIPs_total = new TH1D (title,title,15,0,15);
    sprintf(title,"5layers_more_less_than_3MIP_seed_totalE");
    h_5layers_more_less_than_3MIP_seed_totalE = new TH1D (title,title,1000,0,20000);
    sprintf(title,"5layers_more_less_than_3MIP_total_totalE");
    h_5layers_more_less_than_3MIP_total_totalE = new TH1D (title,title,1000,0,20000);
    sprintf(title,"5layers_more_less_than_3MIP_seed_shower_depth");
    h_5layers_more_less_than_3MIP_seed_shower_depth = new TH1D (title,title,112,0,28);
    sprintf(title,"5layers_more_less_than_3MIP_total_shower_depth");
    h_5layers_more_less_than_3MIP_total_shower_depth = new TH1D (title,title,112,0,28);
    sprintf(title,"5layers_more_less_than_3MIP_seed_last_three_layer_energy");
    h_5layers_more_less_than_3MIP_seed_last_three_layer_energy = new TH1D (title,title,800,0,16000);
    sprintf(title,"5layers_more_less_than_3MIP_total_last_three_layer_energy");
    h_5layers_more_less_than_3MIP_total_last_three_layer_energy = new TH1D (title,title,800,0,16000);
   */

 /*sprintf(title,"layerE19");
    h_layerE19 = new TH1D (title,title,1000,0,20000);
    sprintf(title,"layerE37");
    h_layerE37 = new TH1D (title,title,1000,0,20000);
    sprintf(title,"layerE63");
    h_layerE63 = new TH1D (title,title,1000,0,20000);
    sprintf(title,"layerEout19");
    h_layerEout19 = new TH1D (title,title,1000,0,20000);
    sprintf(title,"layerEout37");
    h_layerEout37 = new TH1D (title,title,1000,0,20000);
    sprintf(title,"layerEout63");
    h_layerEout63 = new TH1D (title,title,1000,0,20000);
    sprintf(title,"Ratio_in_total_layerE19");
    h_Ratio_in_total_layerE19 = new TH1D (title,title,100,0.9,1);
    sprintf(title,"Ratio_in_total_layerE37");
    h_Ratio_in_total_layerE37 = new TH1D (title,title,100,0.9,1);
    sprintf(title,"Ratio_in_total_layerE63");
    h_Ratio_in_total_layerE63 = new TH1D (title,title,100,0.9,1);
    sprintf(title,"Ratio_out_total_layerE19");
    h_Ratio_out_total_layerE19 = new TH1D (title,title,100,0,0.1);
    sprintf(title,"Ratio_out_total_layerE37");
    h_Ratio_out_total_layerE37 = new TH1D (title,title,100,0,0.1);
    */
    //sprintf(title,"Ratio_out_total_layerE63");
    //h_Ratio_out_total_layerE63 = new TH1D (title,title,100,0,0.1);


    //sprintf(title,"E7devE37");
    //h_E7devE37 = new TH1D(title,title,100,0.9,1);
    //sprintf(title,"E7devE37_09_1_layer");
    //h_E7devE37_09_1_layer = new TH1D(title,title,29,0,29);
  
    //sprintf(title,"shower_depth_ring_cut");
    //h_shower_depth_ring_cut = new TH1D (title,title,112,0,28);
    sprintf(title,"how_many_layers_less_than_3_MIPs_seed");
    h_how_many_layers_less_than_3_MIPs_seed = new TH1D (title,title,15,0,15);
    sprintf(title,"how_many_layers_less_than_3_MIPs_total");
    h_how_many_layers_less_than_3_MIPs_total = new TH1D (title,title,15,0,15);
    sprintf(title,"shower_depth_ring_cut_have_last_detector_cut");
    h_shower_depth_ring_cut_have_last_detector_cut = new TH1D (title,title,112,0,28);
    /*sprintf(title,"shower_depth_ring_cut_no_last_detector_cut");
    h_shower_depth_ring_cut_no_last_detector_cut = new TH1D (title,title,112,0,28);
    sprintf(title,"shower_depth_ring_3MIP_no_last_detector_cut_seed");
    h_shower_depth_ring_3MIP_no_last_detector_cut_seed = new TH1D (title,title,112,0,28);
    */
    sprintf(title,"E28_Seed");
    h_E28_Seed = new TH1D (title,title,1000,0,1000);
    sprintf(title,"totalE_E28_Seed");
    h_totalE_E28_Seed = new TH2D (title,title,20,0,20,4000,0,16000);

    sprintf(title,"shower_depth_ring_more_3MIP_have_last_detector_cut_seed");
    h_shower_depth_ring_more_3MIP_have_last_detector_cut_seed = new TH1D (title,title,112,0,28);
    sprintf(title,"shower_depth_ring_less_3MIP_have_last_detector_cut_seed");
    h_shower_depth_ring_less_3MIP_have_last_detector_cut_seed = new TH1D (title,title,112,0,28);
    //sprintf(title,"shower_depth_ring_3MIP_cut_total");
    //h_shower_depth_ring_3MIP_cut_total = new TH1D (title,title,112,0,28);
    sprintf(title,"shower_depth_vs_totalE_Per_Ele_Candidate_have_last_detector_cut");
    h_shower_depth_vs_totalE_Per_Ele_Candidate_have_last_detector_cut = new TH2D (title,title,112,0,28,400,0,16000);
    //sprintf(title,"shower_depth_vs_totalE_Per_Ele_Candidate_no_last_detector_cut");
    //h_shower_depth_vs_totalE_Per_Ele_Candidate_no_last_detector_cut = new TH2D (title,title,112,0,28,400,0,16000);
    sprintf(title,"shower_depth_vs_totalE_delta_ray_Candidate_have_last_detector_cut");
    h_shower_depth_vs_totalE_delta_ray_Candidate_have_last_detector_cut = new TH2D (title,title,112,0,28,400,0,16000);
    //sprintf(title,"shower_depth_vs_totalE_delta_ray_Candidate_no_last_detector_cut");
   // h_shower_depth_vs_totalE_delta_ray_Candidate_no_last_detector_cut = new TH2D (title,title,112,0,28,400,0,16000);
    sprintf(title,"shower_depth_vs_totalE_ring_cut_have_last_detector_cut");
    h_shower_depth_vs_totalE_ring_cut_have_last_detector_cut = new TH2D (title,title,112,0,28,400,0,16000);
    sprintf(title,"energy_to_5_Ele");
    h_energy_to_5_Ele = new TH1D (title,title,50,0,1);
    sprintf(title,"energy_to_5_Per_Ele");
    h_energy_to_5_Per_Ele = new TH1D (title,title,50,0,1);
    sprintf(title,"energy_to_5_Delta_ray");
    h_energy_to_5_Delta_ray = new TH1D (title,title,50,0,1);
    sprintf(title,"energy_to_10_Ele");
    h_energy_to_10_Ele = new TH1D (title,title,50,0,1);
    sprintf(title,"energy_to_10_Per_Ele");
    h_energy_to_10_Per_Ele = new TH1D (title,title,50,0,1);
    sprintf(title,"energy_to_10_Delta_ray");
    h_energy_to_10_Delta_ray = new TH1D (title,title,50,0,1);

    sprintf(title,"h_energy_to_10_Delta_ray_no_cut");
    h_energy_to_10_Delta_ray_no_cut = new TH1D (title,title,50,0,1);
    sprintf(title,"h_energy_to_10_Delta_ray_after_5_ring_cut");
    h_energy_to_10_Delta_ray_after_5_ring_cut = new TH1D (title,title,50,0,1);
    sprintf(title,"h_energy_to_10_Delta_ray_after_5_ring_cut_plus_three_MIPs_cut");
    h_energy_to_10_Delta_ray_after_5_ring_cut_plus_three_MIPs_cut = new TH1D (title,title,50,0,1);
    sprintf(title,"h_energy_to_10_Delta_ray_after_5_ring_cut_plus_three_MIPs_075_cut");
    h_energy_to_10_Delta_ray_after_5_ring_cut_plus_three_MIPs_075_cut = new TH1D (title,title,50,0,1);
    sprintf(title,"h_energy_to_10_Delta_ray_after_all_cut");
    h_energy_to_10_Delta_ray_after_all_cut = new TH1D (title,title,50,0,1);



 //sprintf(title,"shower_depth_vs_totalE_ring_cut_no_last_detector_cut");
    //h_shower_depth_vs_totalE_ring_cut_no_last_detector_cut = new TH2D (title,title,112,0,28,400,0,16000);

 //   sprintf(title,"totalE_last_detector_delta_ray_Candidate");
   //	 h_totalE_last_detector_delta_ray_Candidate = new TH1D (title,title,400,0,2000);
/*sprintf(title,"shower_depth_5_to_10_totalE");
    h_shower_depth_5_to_10_totalE = new TH1D (title,title,800,0,16000);
    sprintf(title,"leak_back_three_layers_energy_seed");
    h_leak_back_three_layers_energy_seed = new TH1D (title,title,800,0,16000);
    sprintf(title,"leak_back_three_layers_energy_total");
    h_leak_back_three_layers_energy_total = new TH1D (title,title,800,0,16000);
*/

   /* sprintf(title,"shower_depth");
    shower_depth = new TH1D (title,title,112,0,28);
    sprintf(title,"total_energy");
    total_energy = new TH1D (title,title,1000,0,20000);
    sprintf(title,"total_energy_last_three_layer");
    total_energy_last_three_layer = new TH1D (title,title,60,0,300);

    sprintf(title,"layer_8_9_10_E1devE7");
    h_layer_8_9_10_E1devE7 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_8_9_10_E7devE37");
    h_layer_8_9_10_E7devE37 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_9_10_11_E1devE7");
    h_layer_9_10_11_E1devE7 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_9_10_11_E7devE37");
    h_layer_9_10_11_E7devE37 = new TH1D(title,title,100,0,1);

    sprintf(title,"layer_8_E1devE7");
    h_layer_8_E1devE7 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_8_E7devE37");
    h_layer_8_E7devE37 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_9_E1devE7");
    h_layer_9_E1devE7 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_9_E7devE37");
    h_layer_9_E7devE37 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_10_E1devE7");
    h_layer_10_E1devE7 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_10_E7devE37");
    h_layer_10_E7devE37 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_11_E1devE7");
    h_layer_11_E1devE7 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_11_E7devE37");
    h_layer_11_E7devE37 = new TH1D(title,title,100,0,1);
    sprintf(title,"layer_total_E1devE7");
    h_layer_total_E1devE7= new TH1D(title,title,100,0,1);
    sprintf(title,"layer_total_E7devE37");
    h_layer_total_E7devE37= new TH1D(title,title,100,0,1);*/
  int delta_event=0;
  int electron_event=0;
    float event_pass_2=0;
    float event_pass_3=0;
    float event_pass_4=0;
  float event_total=0;
  vector<float> cut;
  //int check_point8=0;
  //int check_point8_1=0;
  //int check_point8_2=0;
  //int check_point8_3=0;
  //int check_point8_4=0;


  for(int ev = 0; ev < nevents; ++ev){
    if(ev %10000 == 0) cout << "Processing event: "<< ev << endl;
    //cout << "nevents: " << nevents << endl;
    //cout <<"ev: " << ev << endl;
    GetData(ev);
    int Nhits = NRechits;
    /*h_DWCf3_Dis_X->Fill(impactX_HGCal_layer_1);
    h_DWCf3_Dis_X->Fill(impactX_HGCal_layer_2);
    h_DWCf3_Dis_X->Fill(impactX_HGCal_layer_3);
    h_DWCf3_Dis_Y->Fill(impactY_HGCal_layer_1);
    h_DWCf3_Dis_Y->Fill(impactY_HGCal_layer_2);
    h_DWCf3_Dis_Y->Fill(impactY_HGCal_layer_3);

    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_1);
    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_2);
    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_3);
    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_4);
    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_5);

    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_1);
    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_2);
    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_3);
    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_4);
    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_5);
*/
    // Event Selection
    if ( Nhits < 200 ) continue;
    if ( dwcReferenceType != 15) continue;
    /*if ( impactX_HGCal_layer_1>1 || impactX_HGCal_layer_1<-1) continue; 
    if ( impactY_HGCal_layer_1>1 || impactY_HGCal_layer_1<-1) continue;
    if ( impactX_HGCal_layer_2>1 || impactX_HGCal_layer_2<-1) continue;
    if ( impactY_HGCal_layer_2>1 || impactY_HGCal_layer_2<-1) continue;
    if ( impactX_HGCal_layer_3>1 || impactX_HGCal_layer_3<-1) continue;
    if ( impactY_HGCal_layer_3>1 || impactY_HGCal_layer_3<-1) continue;
    if ( impactX_HGCal_layer_4>1 || impactX_HGCal_layer_4<-1) continue;
    if ( impactY_HGCal_layer_4>1 || impactY_HGCal_layer_4<-1) continue;
    if ( impactX_HGCal_layer_5>1 || impactX_HGCal_layer_5<-1) continue;
    if ( impactY_HGCal_layer_5>1 || impactY_HGCal_layer_5<-1) continue;
    */
    double SHD_Elayer = 0;
    int SHD_Elayer_for_contamination=0;
   // cout << "impactX_HGCAL_layer_1" << impactX_HGCal_layer_1 << endl;
    
    h_DWCf3_Dis_X->Fill(impactX_HGCal_layer_1);
    h_DWCf3_Dis_X->Fill(impactX_HGCal_layer_2);
    h_DWCf3_Dis_X->Fill(impactX_HGCal_layer_3);
    h_DWCf3_Dis_Y->Fill(impactY_HGCal_layer_1);
    h_DWCf3_Dis_Y->Fill(impactY_HGCal_layer_2);
    h_DWCf3_Dis_Y->Fill(impactY_HGCal_layer_3);

    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_1);
    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_2);
    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_3);
    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_4);
    h_DWCf5_Dis_X->Fill(impactX_HGCal_layer_5);

    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_1);
    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_2);
    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_3);
    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_4);
    h_DWCf5_Dis_Y->Fill(impactY_HGCal_layer_5);
    
    // h_totalE->Fill(totalE);
    double InitlayerE19=0;
    double InitlayerE37=0;
    double InitlayerE63=0;
    double InitlayerE19out=0;
    double InitlayerE37out=0;
    double InitlayerE63out=0;
    double Initlayer_number_seed=0;
    double Initlayer_number_total=0;
    double Initenergy_seed=0;
    double Initenergy_total=0;
    for(int iL = 0; iL < NLAYER ; ++iL){
	SHD_Elayer += X0_layer[iL]*layerE[iL];
        if( layerE1[iL] != 0){
         double E1devE7  = layerE1[iL]/layerE7[iL];
         double E7devE1g = layerE7[iL]/layerE19[iL];
         InitlayerE19=InitlayerE19+layerE19[iL];
         InitlayerE37=InitlayerE37+layerE37[iL];
         InitlayerE63=InitlayerE63+layerE63[iL];
         InitlayerE19out=InitlayerE19out+layerE19out[iL];
         InitlayerE37out=InitlayerE37out+layerE37out[iL];
         InitlayerE63out=InitlayerE63out+layerE63out[iL];
         		 
         //h_layer_total_E1devE7->Fill(E1devE7);
 /*       
        h_layerE19->Fill(layerE19[iL]);
        h_layerE37->Fill(layerE37[iL]);
        h_layerE63->Fill(layerE63[iL]);
        h_layerEout19->Fill(layerE19out[iL]);
        h_layerEout37->Fill(layerE37out[iL]);
        h_layerEout63->Fill(layerE63out[iL]);*/
        /*if(iL>=8 && iL <=15)
        }
            h_layer_8_to_15_E1devE7->Fill(E1devE7);
        }
        if(iL>=8 && iL <=15)
        {
            h_layer_8_to_15_E7devE37->Fill(E7devE37);
        }*/
        /*if( iL >= 7 && iL <= 9 )
	{
	h_layer_8_9_10_E1devE7->Fill(E1devE7);
	h_layer_8_9_10_E7devE37->Fill(E7devE37);
	}
        if( iL >= 8 && iL <= 10 )
        {
        h_layer_9_10_11_E1devE7->Fill(E1devE7);
        h_layer_9_10_11_E7devE37->Fill(E7devE37);
        }

	if( iL == 7 )
	{
	h_layer_8_E1devE7->Fill(E1devE7);
	h_layer_8_E7devE37->Fill(E7devE37);
	}
	if( iL == 8 )
	{
	h_layer_9_E1devE7->Fill(E1devE7);
	h_layer_9_E7devE37->Fill(E7devE37);
	}
	if( iL == 9)
	{
	h_layer_10_E1devE7->Fill(E1devE7);
	h_layer_10_E7devE37->Fill(E7devE37);
	}
	if( iL == 10 )
	{
	h_layer_11_E1devE7->Fill(E1devE7);
	h_layer_11_E7devE37->Fill(E7devE37);
	}
        */
}
      /*if( layerE1[iL] != 0){
	double E1devE7  = layerE1[iL]/layerE7[iL];
	double E7devE37 = layerE7[iL]/layerE19[iL];
	h_E1devE7 [iL]->Fill(E1devE7);
 	h_E7devE37[iL]->Fill(E7devE37);}*/
       

        //If one wants to do sth with hits
     }
        /*h_layerE19->Fill(InitlayerE19);
        h_layerE37->Fill(InitlayerE37);
        h_layerE63->Fill(InitlayerE63);
        h_layerEout19->Fill(InitlayerE19out);
        h_layerEout37->Fill(InitlayerE37out);
        h_layerEout63->Fill(InitlayerE63out);
        h_Ratio_in_total_layerE19->Fill(InitlayerE19/totalE);
        h_Ratio_in_total_layerE37->Fill(InitlayerE37/totalE);
        h_Ratio_in_total_layerE63->Fill(InitlayerE63/totalE);
        h_Ratio_out_total_layerE19->Fill(InitlayerE19out/totalE);
        h_Ratio_out_total_layerE37->Fill(InitlayerE37out/totalE);
        */
       // h_Ratio_out_total_layerE63->Fill(InitlayerE63out/totalE);
      float energy_first_10layers_5=0;
    for(int iL = 0 ; iL < 10 ; iL++)
    {
            if(iL<10)
            {
            energy_first_10layers_5=energy_first_10layers_5+layerE[iL];
            }


    }
    
       event_total=event_total+1;
    
      if(energy_first_10layers_5/totalE > 0.2)
      {
          event_pass_2=event_pass_2+1;
      }
      if(energy_first_10layers_5/totalE > 0.3)
      {
          event_pass_3=event_pass_3+1;
      }
      if(energy_first_10layers_5/totalE > 0.4)
      {
          event_pass_4=event_pass_4+1;
      }

    h_energy_to_10_Delta_ray_no_cut->Fill(energy_first_10layers_5/totalE);
    SHD_Elayer /= totalE;
	//h_shower_depth_vs_totalE_ring_cut->Fill(SHD_Elayer);
	//For_electron_MC
	        int SHD_Elayer_float=SHD_Elayer*10;
	/*if(ev%20000==0)
                {      
			//cout << "SHD_Elayer_float: " << endl; 
                        cout << "SHD_Elayer: " << SHD_Elayer << endl;
		        cout << "SHD_Elayer_float: " << SHD_Elayer_float << endl;
		}*/
	//int SHD_Elayer_float=SHD_Elayer*10;
	if(SHD_Elayer_float%10>=5)
	{
                SHD_Elayer_for_contamination=SHD_Elayer+1;
		if(ev%20000==0)
		{
			//cout << "SHD_Elayer: " << SHD_Elayer << endl;
        //cout << "SHD_Elayer_for_contamination: " << SHD_Elayer_for_contamination << endl;
		}
		//SHD_Elayer_for_contamination=SHD_Elayer+1;
	//cout << "SHD_Elayer_for_contamination: " << SHD_Elayer_for_contamination << endl;
	}
	if(SHD_Elayer_float%10<5)
	{
                SHD_Elayer_for_contamination=SHD_Elayer;
		 if(ev%20000==0)
                {
                        //cout << "SHD_Elayer: " << SHD_Elayer << endl;
                  //cout << "SHD_Elayer_for_contamination: " << SHD_Elayer_for_contamination << endl;
		}
                //SHD_Elayer_for_contamination=SHD_Elayer;
        //cout << "SHD_Elayer_for_contamination: " << SHD_Elayer_for_contamination << endl;
	}
	if(InitlayerE63out/totalE<=0.01)
	{
	if(layerE1[27]<20)
	{
        for(int iL = 0; iL < NLAYER ; ++iL)
                {
                        double E7devE19  = layerE7[iL]/layerE19[iL];
                        double E7devE37 = layerE7[iL]/layerE37[iL];
			 h_layerall_E7devE19_have_last_detector_before_contamination_cut->Fill(E7devE19);
                         h_layerall_E7devE37_have_last_detector_before_contamination_cut->Fill(E7devE37);
		}	
	}	
	//	h_shower_depth_ring_cut->Fill(SHD_Elayer);
               /* h_shower_depth_vs_totalE_ring_cut_no_last_detector_cut->Fill(SHD_Elayer,totalE);
		if(layerE1[27]<20)
		{
                h_shower_depth_vs_totalE_ring_cut_have_last_detector_cut->Fill(SHD_Elayer,totalE);
		}*/
		float energy_first_10layers_1=0;
		float energy_first_5layers_1=0;
		int check_point8=0;
		for(int iL = 0; iL < NLAYER ; ++iL)
                {       
                        double E7devE19  = layerE7[iL]/layerE19[iL];
                        double E7devE37 = layerE7[iL]/layerE37[iL];
			if(iL==SHD_Elayer_for_contamination and E7devE19>0.75)
			{
			//cout << "check_point: "<< check_point8 << endl;
			check_point8=check_point8+1;
			}
		}
                if(check_point8!=0)
		{
		h_E28_Seed->Fill(layerE1[27]);
		}
		if(check_point8!=0 and layerE1[27]<20)
		{
	//		cout <<"Electron_pass_Contamination: "<< ev << endl;
                	//h_shower_depth_vs_totalE_ring_cut_no_last_detector_cut->Fill(SHD_Elayer,totalE);
 			for(int iL = 0; iL < 10 ; iL++)
			{
				if(iL<10)
				{
				energy_first_10layers_1=energy_first_10layers_1+layerE[iL];		
				}
				if(iL<5)
				{                                
				energy_first_5layers_1=energy_first_5layers_1+layerE[iL];
				}
			}               
			h_energy_to_5_Ele->Fill(energy_first_5layers_1/totalE);
            h_energy_to_10_Ele->Fill(energy_first_10layers_1/totalE);
			h_totalE_E28_Seed->Fill(layerE1[27],totalE);
                	h_shower_depth_vs_totalE_ring_cut_have_last_detector_cut->Fill(SHD_Elayer,totalE);
                	h_shower_depth_ring_cut_have_last_detector_cut->Fill(SHD_Elayer);
			
			//h_shower_depth_ring_cut_no_last_detector_cut->Fill(SHD_Elayer);
			for(int iL = 0; iL < NLAYER ; ++iL)
			{
                        double E7devE19  = layerE7[iL]/layerE19[iL];
                        double E7devE37 = layerE7[iL]/layerE37[iL];
			//h_layerall_E7devE19_no_last_detector_MC_electron->Fill(E7devE19);
                        //h_layerall_E7devE37_no_last_detector_MC_electron->Fill(E7devE37);
		
			
                        h_layerall_E7devE19_have_last_detector_MC_electron->Fill(E7devE19);
                        h_layerall_E7devE37_have_last_detector_MC_electron->Fill(E7devE37);
			
			}
                }
			/*if(iL==7)
                        {
                                h_layer8_E7devE37_MC_electron->Fill(E7devE37);
                        }
                        if(iL==8)
                        {
                                h_layer9_E7devE37_MC_electron->Fill(E7devE37);
                        }
                        if(iL==9)
                        {
                                h_layer10_E7devE37_MC_electron->Fill(E7devE37);
                        }*/
                }

	
	//For Pion MC
	if(InitlayerE63out/totalE<=0.01)
       {
        for(int iL = 0; iL < NLAYER ; ++iL)
        {
        //Initenergy_seed = Initenergy_seed + layerE1[iL];
        //        //Initenergy_total = Initenergy_total + layerE[iL];     
        //                //cout << "Initenergy_seed: " << Initenergy_seed << endl;
        //                        //cout << "Initenergy_total: " << Initenergy_total << endl;
        //
        //
        //
        if( layerE1[iL] > 3 and layerE1[iL+1] > 3 and layerE1[iL+2] > 3)
        {
	if(iL<=4)
        {
	//cout << "iL: " << iL << endl;
        }
	//                                                                                                 cout << "layerE1[iL-1]: " << layerE1[iL-1] << endl;
        //                                                                                                                         cout << "layerE1[iL]: " << layerE1[iL] << endl;
        //                                                                                                                                                 cout << "layerE1[iL+1]: " << layerE1[iL+1] << endl;
        //                                                                                                                                                                         cout << "layerE1[iL+2]: " << layerE1[iL+2] << endl;
                                                                                                                                                                   Initlayer_number_seed=iL;                                                                                                                                  break;
        }
        else
	{
	continue;
	}
	}
        //
        //                                                                                                                                                                                                                                                                          else
        //                                                                                                                                                                                                                                                                                   {
        //                                                                                                                                                                                                                                                                                                   continue;
        //                                                                                                                                                                                                                                                                                                            }
        //
        //h_shower_depth_ring_total_cut->Fill(SHD_Elayer);
        //Perfect electorn selection;
        if(Initlayer_number_seed<=4)
        //if(SHD_Elayer >= 5 and SHD_Elayer <= 10)
	{
		//h_shower_depth_vs_totalE_Per_Ele_Candidate->Fill(SHD_Elayer,totalE);
		//h_shower_depth_5_to_10_totalE->Fill(totalE);
		float energy_first_10layers_2=0 ;
	        float energy_first_5layers_2=0 ;
		int check_point8_1=0;
		if(layerE1[27]<20)
		{
                for(int iL = 0; iL < NLAYER ; ++iL)
                {
                        double E7devE19  = layerE7[iL]/layerE19[iL];
                        double E7devE37 = layerE7[iL]/layerE37[iL];
                        h_layerall_E7devE19_have_last_detector_Perfect_electron_candidate_before_contamination_cut->Fill(E7devE19);
                        h_layerall_E7devE37_have_last_detector_Perfect_electron_candidate_before_contamination_cut->Fill(E7devE37);
		}
		}
		for(int iL = 0; iL < NLAYER ; ++iL)	
		{	
			double E7devE19  = layerE7[iL]/layerE19[iL];
                	double E7devE37 = layerE7[iL]/layerE37[iL];
			if(iL==SHD_Elayer_for_contamination and E7devE19>0.75)
			{
//				cout << "check_point_1: "<< check_point8_1 << endl;
				check_point8_1=check_point8_1+1;
			}		
		}
		if(check_point8_1!=0 and layerE1[27]<20)
		{
                      //  cout <<"Per_Electron_pass_Contamination: "<< ev << endl;
                        for(int iL = 0 ; iL < 10 ; iL++)
                        {
				if(iL<10)
				{
                                energy_first_10layers_2=energy_first_10layers_2+layerE[iL];
                        	}
				if(iL<5)
				{
				energy_first_5layers_2=energy_first_5layers_2+layerE[iL];
				}
			}
                        h_energy_to_5_Per_Ele->Fill(energy_first_5layers_2/totalE);
			h_energy_to_10_Per_Ele->Fill(energy_first_10layers_2/totalE);
		h_shower_depth_vs_totalE_Per_Ele_Candidate_have_last_detector_cut->Fill(SHD_Elayer,totalE);
		h_shower_depth_ring_less_3MIP_have_last_detector_cut_seed->Fill(SHD_Elayer);
		//
		electron_event=electron_event+1;
		for(int iL = 0; iL < NLAYER ; ++iL)
		{
		        XLayer_Ele.push_back(iL);
                        YMIPs_Ele.push_back(layerE1[iL]);
                        double E7devE19  = layerE7[iL]/layerE19[iL];
                        double E7devE37 = layerE7[iL]/layerE37[iL];
			h_layerall_E7devE19_have_last_detector_Perfect_electron_candidate->Fill(E7devE19);
			h_layerall_E7devE37_have_last_detector_Perfect_electron_candidate->Fill(E7devE37);
		}
			if(electron_event<=49)
			{
                        	h_event_Perfect_electron_candidate[electron_event] = new TGraph(28,&XLayer_Ele[0],&YMIPs_Ele[0]);
                        	h_event_Perfect_electron_candidate[electron_event]->SetTitle(Form("h_event%i_electron_candidate",electron_event));
                        	sprintf(GR_save_1,"h_event%i_electron_candidate",electron_event);
                        	h_event_Perfect_electron_candidate[electron_event]->Write(GR_save_1);                   
				XLayer_Ele.clear();
                        	YMIPs_Ele.clear();
			}
			else
			{
                        	XLayer_Ele.clear();
                        	YMIPs_Ele.clear();
			}

			/*if(iL==7)
			{
				h_layer8_E7devE37_Perfect_electron_candidate->Fill(E7devE37);
			}
                	if(iL==8)
                	{
                		h_layer9_E7devE37_Perfect_electron_candidate->Fill(E7devE37);
                	}
                	if(iL==9)
                	{
                		h_layer10_E7devE37_Perfect_electron_candidate->Fill(E7devE37);
                	}*/
		
		}
		/*electron_event=electron_event+1;
		if(electron_event<=49)
		{
			h_shower_depth_5_to_10_totalE->Fill(totalE);
                        for(int iL = 0; iL < NLAYER ; ++iL)
                        {
                                XLayer_Ele.push_back(iL);
                                YMIPs_Ele.push_back(layerE1[iL]);
                        }
			h_event_Perfect_electron_candidate[electron_event] = new TGraph(28,&XLayer_Ele[0],&YMIPs_Ele[0]);
			h_event_Perfect_electron_candidate[electron_event]->SetTitle(Form("h_event%i_electron_candidate",electron_event));
			sprintf(GR_save_1,"h_event%i_electron_candidate",electron_event);
                        h_event_Perfect_electron_candidate[electron_event]->Write(GR_save_1);			
			XLayer_Ele.clear();
			YMIPs_Ele.clear();
		}	
		else
		{
			continue;
		}*/
	}
		/*float energy_first_10layers_5=0;
	                for(int iL = 0 ; iL < 10 ; iL++)
                        {
                                if(iL<10)
                                {
                                energy_first_10layers_5=energy_first_10layers_5+layerE[iL];
                                }
                                
                
                        }
                        
                        h_energy_to_10_Delta_ray_no_cut->Fill(energy_first_10layers_5/totalE);
*/
       if(InitlayerE63out/totalE<=0.01)
	{
                float energy_first_10layers_6=0;
                        for(int iL = 0 ; iL < 10 ; iL++)
                        {
                                if(iL<10)
                                {
                                energy_first_10layers_6=energy_first_10layers_6+layerE[iL];
                                }


                        }

                        h_energy_to_10_Delta_ray_after_5_ring_cut->Fill(energy_first_10layers_6/totalE);


 //h_first_5layers_E1energy->Fill(layerE1[0]+layerE1[1]+layerE1[2]+layerE1[3]+layerE1[4]);            
	for(int iL = 0; iL < NLAYER ; ++iL)
	{
	//Initenergy_seed = Initenergy_seed + layerE1[iL];
	//Initenergy_total = Initenergy_total + layerE[iL];	
	//cout << "Initenergy_seed: " << Initenergy_seed << endl;
        //cout << "Initenergy_total: " << Initenergy_total << endl;
	 
        
             
         if( layerE1[iL] > 3 and layerE1[iL+1] > 3 and layerE1[iL+2] > 3)
                {
			/*cout << "iL: " << iL << endl;
                        cout << "layerE1[iL-1]: " << layerE1[iL-1] << endl;
			cout << "layerE1[iL]: " << layerE1[iL] << endl;
			cout << "layerE1[iL+1]: " << layerE1[iL+1] << endl;
                        cout << "layerE1[iL+2]: " << layerE1[iL+2] << endl;
			*/
			Initlayer_number_seed=iL;
			break;
		}
           
         
	 else
	 {
		continue;
	 }
	 }
 	 for(int iL = 0; iL < NLAYER ; ++iL)
         {
	 
          
            if( layerE[iL] > 3 and layerE[iL+1] > 3 and layerE[iL+2] > 3)
                {	
			 /*cout << "iL: " << iL << endl;
                        cout << "layerE[iL-1]: " << layerE[iL-1] << endl;
                        cout << "layerE[iL]: " << layerE[iL] << endl;
                         cout << "layerE[iL+1]: " << layerE[iL+1] << endl;
                         cout << "layerE[iL+2]: " << layerE[iL+2] << endl;
			*/
			    Initlayer_number_total=iL;
                        break;
                }
            
         
         else
         {
                continue;
         }               
	}
	 
         //cout << "Hello3"<<endl;
         // cout << "Initlayer_number_seed: " << Initlayer_number_seed << endl;
	 // cout << "Initlayer_number_total: " << Initlayer_number_total << endl;
	 h_how_many_layers_less_than_3_MIPs_seed->Fill(Initlayer_number_seed);
         h_how_many_layers_less_than_3_MIPs_total->Fill(Initlayer_number_total);
        //cout <<"Initlayer_number_seed" << Initlayer_number_seed << endl;
        //cout <<"Initlayer_number_total" << Initlayer_number_total << endl;
	if(Initlayer_number_seed >= 5 and Initlayer_number_seed <= 14)
	{
	//		h_totalE_last_detector_delta_ray_Candidate->Fill(layerE1[27]);
			float energy_first_10layers_3=0;
			float energy_first_5layers_3=0;
			int check_point8_2=0;
	               float energy_first_10layers_7=0;
                        for(int iL = 0 ; iL < 10 ; iL++)
                        {
                                if(iL<10)
                                {
                                energy_first_10layers_7=energy_first_10layers_7+layerE[iL];
                                }


                        }

                        h_energy_to_10_Delta_ray_after_5_ring_cut_plus_three_MIPs_cut->Fill(energy_first_10layers_7/totalE);

                                               
/* h_shower_depth_ring_3MIP_no_last_detector_cut_seed->Fill(SHD_Elayer);
			if(layerE1[27]<20)
			{
			  h_shower_depth_ring_3MIP_have_last_detector_cut_seed->Fill(SHD_Elayer);
			}*/
                       // h_leak_back_three_layers_energy_seed->Fill(layerE1[25]+layerE1[26]+layerE1[27]);
                       if(layerE1[27]<20)
			{
                        for(int iL = 0; iL < NLAYER ; ++iL)
                        {
                                double E7devE19  = layerE7[iL]/layerE19[iL];
                                double E7devE37 = layerE7[iL]/layerE37[iL];
                                h_layerall_E7devE19_have_last_detector_delta_ray_candidate_before_contamination_cut->Fill(E7devE19);
                                h_layerall_E7devE37_have_last_detector_delta_ray_candidate_before_contamination_cut->Fill(E7devE37);
			}
			}

			for(int iL = 0; iL < NLAYER ; ++iL)
                	{       
                        double E7devE19  = layerE7[iL]/layerE19[iL];
                        double E7devE37 = layerE7[iL]/layerE37[iL];
			if(iL==SHD_Elayer_for_contamination and E7devE19>0.75)
			{
	                 //      cout << "check_point_2: "<< check_point8_2 << endl;
                                check_point8_2=check_point8_2+1;		
			}
			}
			if(check_point8_2!=0)
			{
	                float energy_first_10layers_7=0;
                        for(int iL = 0 ; iL < 10 ; iL++)
                        {
                                if(iL<10)
                                {
                                energy_first_10layers_7=energy_first_10layers_7+layerE[iL];
                                }


                        }

                        h_energy_to_10_Delta_ray_after_5_ring_cut_plus_three_MIPs_075_cut->Fill(energy_first_10layers_7/totalE);
			}
			
			if(check_point8_2!=0 and layerE1[27]<20)
			{
        //                cout <<"Delta_Electron_pass_Contamination: "<< ev << endl;
			h_shower_depth_ring_more_3MIP_have_last_detector_cut_seed->Fill(SHD_Elayer);
                        h_shower_depth_vs_totalE_delta_ray_Candidate_have_last_detector_cut->Fill(SHD_Elayer,totalE);
			delta_event=delta_event+1;
                       
			
                        for(int iL = 0; iL < 10 ; iL++)
                        {
				if(iL<10)
				{
                                energy_first_10layers_3=energy_first_10layers_3+layerE[iL];
                        	}
				if(iL<5)
				{
				energy_first_5layers_3=energy_first_5layers_3+layerE[iL];
				}
			}
			h_energy_to_10_Delta_ray_after_all_cut->Fill(energy_first_10layers_3/totalE);
                        h_energy_to_5_Delta_ray->Fill(energy_first_5layers_3/totalE);
			h_energy_to_10_Delta_ray->Fill(energy_first_10layers_3/totalE);
                        for(int iL = 0 ; iL < NLAYER  ; iL++)
			{
			        XLayer_Delta.push_back(iL);
                        	YMIPs_Delta.push_back(layerE1[iL]);
                        	double E7devE19  = layerE7[iL]/layerE19[iL];
                       		double E7devE37 = layerE7[iL]/layerE37[iL];
                        	h_layerall_E7devE19_have_last_detector_delta_ray_candidate->Fill(E7devE19);
                        	h_layerall_E7devE37_have_last_detector_delta_ray_candidate->Fill(E7devE37);
				
			}
			if(delta_event<=49)
			{
                        h_event_delta_ray_candidate[delta_event] = new TGraph (28,&XLayer_Delta[0],&YMIPs_Delta[0]);
                        h_event_delta_ray_candidate[delta_event]->SetTitle(Form("h_event%i_delta_event_candidate",delta_event));
                        sprintf(GR_save,"h_event%i_delta_event_candidate",delta_event);
                        h_event_delta_ray_candidate[delta_event]->Write(GR_save);
                        XLayer_Delta.clear();
                        YMIPs_Delta.clear();
			}
			else
			{
                        XLayer_Delta.clear();
                        YMIPs_Delta.clear();
			}
			/*if(iL==19)
                        {
                                h_layer20_E7devE37_delta_ray_candidate->Fill(E7devE37);
                        }
                        if(iL==20)
                        {
                                h_layer21_E7devE37_delta_ray_candidate->Fill(E7devE37);
                        }
                        if(iL==21)
                        {
                                h_layer22_E7devE37_delta_ray_candidate->Fill(E7devE37);
                        }
                        if(iL==22)
                        {
                                h_layer23_E7devE37_delta_ray_candidate->Fill(E7devE37);
                        }
                        if(iL==23)
                        {
                                h_layer24_E7devE37_delta_ray_candidate->Fill(E7devE37);
                        }
                        if(iL==24)
                        {
                                h_layer25_E7devE37_delta_ray_candidate->Fill(E7devE37);
                        }*/

        	        }
	
                        
                        

		/*delta_event=delta_event+1;
		if(delta_event<=49)
		{
			h_shower_depth_ring_total_3MIP_cut_seed->Fill(SHD_Elayer);
			h_leak_back_three_layers_energy_seed->Fill(layerE1[25]+layerE1[26]+layerE1[27]);
			for(int iL = 0; iL < NLAYER ; ++iL)
			{
			        double E1devE7  = layerE1[iL]/layerE7[iL];
         			double E7devE37 = layerE7[iL]/layerE19[iL];
				XLayer_Delta.push_back(iL);
				YMIPs_Delta.push_back(layerE1[iL]);
				if( E7devE37 >= 0.9 and E7devE37 < 1)
				}
				h_E1devE7 [iL]->Fill(E1devE7);
        			h_E7devE37[iL]->Fill(E7devE37);
				h_E7devE37_0.9_1_layer->Fill(iL);
				}
			}
		   	h_event_delta_ray_candidate[delta_event] = new TGraph (28,&XLayer_Delta[0],&YMIPs_Delta[0]);
			h_event_delta_ray_candidate[delta_event]->SetTitle(Form("h_event%i_delta_event_candidate",delta_event));
			sprintf(GR_save,"h_event%i_delta_event_candidate",delta_event);
			h_event_delta_ray_candidate[delta_event]->Write(GR_save);
			XLayer_Delta.clear();
			YMIPs_Delta.clear();
		}
		else
		{
			continue;
		}*/
		
	}
	if(Initlayer_number_total > 5 and Initlayer_number_total <= 15)
        {
		//h_totalE->Fill(totalE);
 //               h_shower_depth_ring_3MIP_cut_total->Fill(SHD_Elayer);
		//h_leak_back_three_layers_energy_total->Fill(layerE[25]+layerE[26]+layerE[27]);
        }
}
         }
        //cout <<"Event_loop_terminal" << endl;

	 
         // h_layer_E1energy[iL]->Fill(layerE1[iL]);
           //cout << "Event number: " << ev << endl;
           //cout << "Fucking love it! The event."<< endl;
           /*SHD_Elayer /= totalE;
           h_totalE->Fill(totalE);
           h_shower_depth->Fill(SHD_Elayer);
           h_Correlation_totalE_shower_depth->Fill(SHD_Elayer,totalE);
      */
       
      
 
  }
  /*
  h_event_delta_ray_candidate->Draw("BOX2");
  h_event_delta_ray_candidate->SetMarkerStyle(20);
  h_event_delta_ray_candidate->SetMarkerSize(0.6);
  gStyle->SetPalette(kBird);
  */
	/*
  h_Correlation_totalE_shower_depth->Draw("BOX2");
  h_Correlation_totalE_shower_depth->SetMarkerStyle(20);
  h_Correlation_totalE_shower_depth->SetMarkerSize(0.6);
  gStyle->SetPalette(kBird);
  */
  outf.Write();
  outf.Close();
  cut.push_back(event_pass_2/event_total);
cut.push_back(event_pass_3/event_total);
cut.push_back(event_pass_4/event_total);

  return(cut);
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
         1 0.933   2 0.976   3 0.909   4 0.976   5 0.909
         6 0.976   7 0.909   8 0.976   9 0.909   10 0.976
         11 0.909  12 0.976  13 0.909  14 0.976  15 0.909
         16 1.143  17 0.909  18 0.976  19 0.909  20 1.43
         21 0.909  22 0.976  23 0.909  24 0.976  25 0.909
         26 0.976  27 0.909  28 0.976
         */
        double single_layer_X0[28];
        for( int i = 0 ; i < 28 ; ++i){
            if ( i % 2 == 0) single_layer_X0[i] = 0.909;
            else single_layer_X0[i] = 0.976;
        }
        single_layer_X0[0]  = 0.933;
        single_layer_X0[15] = 1.143;
        single_layer_X0[19] = 1.43;
        
        double X0_sum = 0.;
        for(int iL = 0 ; iL < 28 ; ++iL){
            X0_sum += single_layer_X0[iL];
            X0_arr[iL] = X0_sum;
        }
        
        return X0_arr;
    }
  
