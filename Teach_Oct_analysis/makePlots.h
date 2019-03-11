/////////////////////////////////////////////////////////
// Arthor: Chia-hung Chien  chchien521@gmail.com       
// Just use the same class name as we used to.
// Date : 20-June-2018
/////////////////////////////////////////////////////////

#ifndef makePlots_h
#define makePlots_h

#include "TTree.h"
#include "TROOT.h"
#include "TH2Poly.h"
#include "TApplication.h"
#include "TChain.h"
#include <string>
#include <vector>

using namespace std;

const double ENEPERMIP = 86.5e-06; //(GeV) Based on 150GeV muon for 300um Si

class makePlots{
 public:
    makePlots();
    makePlots( TChain *c1,TChain *c2,TChain *c3, string filename );
    
    ~makePlots();
    
  void Loop();
  void Event_Display(); // ignoreEE when you only want to see FH part
  // hitmap == 1 is one want to see hit map or it will fill by energy(mip) normalized by total energy
  
  //member
  bool Is_Data;
  int  beamE;
  int  runN; //0 for MC
  int  PID; // 0 for electron, 1 for pion, 2 for muon
  string beam_str; // "Ele","Pi","Mu"

 private:
  // Members
  string fname;
  //TApplication *app;
  
  TFile        *Inputfile;
  TTree        *T_Rechit;
  TTree        *T_DWC;
  TTree        *T_Meta;
  TTree        *T_MC;
  TTree        *T_rechit_var;
  int          nevents;
  bool         TestRun;
  int          NLAYER_ALL;
  int          NLAYER_EE;
  int          NLAYER_FH;
  int          setup_config;
  //********************* SETUP_CONFIG *****************************
  //0 For 28EE(+4*1cm Fe)+ 12FH(7module*9layer + 1module*3layer)  **
  //1 For 28EE+ 11FH(1*2 + 7module*9layer)                        **
  //  (only air between last EE and first 7 module  FH)           **
  //2 For 0EE + 9FH (7module*9layer, not sure about the absorber) **
  //3 For 8EE(+4*1cm Fe) + 12FH(7module*12layer)                  **
  // New EE setup on http://cmsonline.cern.ch/cms-elog/1069915    **
  //****************************************************************
  
  // Mainframe functions
    void Init();
    void Init_Runinfo();
    void GetData(int evt);
    void Getinfo(int nhit, int &layer,double &x, double &y,double &z,double &ene);
    // Tool functions
    void InitTH2Poly(TH2Poly& poly); //Give frame to TH2Poly
    void InitTH2Poly_flower(TH2Poly& poly); //Give flower frame to TH2Poly
    void Event_Display(int ev); // Event Display
    void Event_Display_3D(int ev); // Event Display
    void root_logon();
    double* Set_X0(double X0_arr[]);
  ///////////////////////////////
  // Declaration of leaf types //
  ///////////////////////////////
  /*Data*/
  //For Rechit
   UInt_t          event;
   UInt_t          run;
   Int_t           pdgID;
   Float_t        beamEnergy;
   Float_t        trueBeamEnergy;
   UInt_t           NRechits;
   vector<unsigned int> *rechit_detid;
   vector<unsigned int> *rechit_module;
   vector<unsigned int> *rechit_layer;
   vector<unsigned int> *rechit_chip;
   vector<unsigned int> *rechit_channel;
   vector<unsigned int> *rechit_type;
   vector<float>   *rechit_x;
   vector<float>   *rechit_y;
   vector<float>   *rechit_z;
   vector<int>     *rechit_iu;
   vector<int>     *rechit_iv;
   vector<float>   *rechit_energy;
   vector<float>   *rechit_energy_noHG;
   vector<float>   *rechit_amplitudeHigh;
   vector<float>   *rechit_amplitudeLow;
   vector<bool>     *rechit_hg_goodFit;
   vector<bool>     *rechit_lg_goodFit;
   vector<bool>     *rechit_hg_saturated;
   vector<bool>     *rechit_lg_saturated;
   vector<bool>     *rechit_fully_calibrated;
   vector<float>   *rechit_TS2High;
   vector<float>   *rechit_TS2Low;
   vector<float>   *rechit_TS3High;
   vector<float>   *rechit_TS3Low;
   vector<unsigned short>   *rechit_Tot;
   vector<float>   *rechit_time;   
   vector<float>   *rechit_timeMaxHG;
   vector<float>   *rechit_timeMaxLG;
   vector<unsigned short>   *rechit_toaRise;
   vector<unsigned short>   *rechit_toaFall;

   // For ImpactPoints (from Delayed wire chamber)
   Int_t           ntracks;
   // ignore the layers currently
   Float_t         trackChi2_X;
   Float_t         trackChi2_Y;
   Int_t           dwcReferenceType;
   Double_t        m_x;
   Double_t        m_y;
   Double_t        b_x;
   Double_t        b_y;

   // TBD

   // For metadata
   Int_t           configuration;
   Float_t         biasCurrentCh0;
   Float_t         biasCurrentCh1;
   Float_t         biasCurrentCh2;
   Float_t         biasCurrentCh3;
   Float_t         humidity_RHDP4;
   Float_t         TCassette07;
   Float_t         tablePositionY;
   Float_t         humidity_air;
   Float_t         temperature_air;
   
    //TBD
    Float_t        impactX_HGCal_layer_1;
    Float_t        impactY_HGCal_layer_1;
    Float_t        impactX_HGCal_layer_2;
    Float_t        impactY_HGCal_layer_2;
    Float_t        impactX_HGCal_layer_3;
    Float_t        impactY_HGCal_layer_3;
    Float_t        impactX_HGCal_layer_4;
    Float_t        impactY_HGCal_layer_4;
    Float_t        impactX_HGCal_layer_5;
    Float_t        impactY_HGCal_layer_5;

    vector<vector<double> > *hit_mip;
    vector<vector<double> > *hit_x;
    vector<vector<double> > *hit_y;
    vector<vector<double> > *hit_z;
    Double_t        totalE;
    Double_t        totalE_CEE;
    Double_t        totalE_CEH;
    Int_t           NLAYER;
    Int_t           layerNhit[40];
    Double_t        layerE[40];
    Double_t        layerE1[40];
    Double_t        layerE7[40];
    Double_t        layerE19[40];
    Double_t        layerE37[40];
    Double_t        layerE61[40];


};

#endif
