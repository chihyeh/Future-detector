#include "TH1.h"
#include "TF1.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TGraph.h"

//#include "utils.h"
//======================================================================//
// Global Functions:
// SigmaE/E for calorimeter with stoch and const term only
double resolutionf1(double *x,double *par) {
  // x[0]   - Beam Energy (just 6 points for now) 
  // par[0] - Stochastic Term
  // par[1] - Constant Term
  // par[2] - Noise Term (absolute resolution)

  //cout << x[0] << "," << par[0] << ", " << par[1] << endl;
  //double func_value=sqrt(par[0]*par[0]/x[0]+par[1]*par[1]);
  double func_value=sqrt(par[0]*par[0]/x[0]+par[1]*par[1]+par[2]*par[2]/(x[0]*x[0]));
  return func_value;
}
//======================================================================//

void DoResolutionStudies(){

  gROOT->Reset();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
  char histoDraw[100];
  //gStyle->SetOptFit(0);
  gStyle->SetStatX(0.88);
  gStyle->SetStatY(0.95);
  gStyle->SetPalette(1);
  
  const int NLAYERS=28;
#define NENERGIES 9
  int BEAME[NENERGIES]={20,30,50,80,100,150,200,250,300};
  //double BEAMED[NENERGIES]={20,30,50,79.929,99.831,149.138,197.316,243.631,287.138};//fit
  double BEAMED[NENERGIES]={20,30,49.99,79.93,99.83,149.14,197.32,243.61,287.18};//Shilpi
  double BEAMEE[NENERGIES]={0.,0.,0.,0.,0.,0.,0.,0.3,0.4};// errors on BeamE from dipole, SR etc.

  double rangeGausFitSyst[NENERGIES];
  for (int i=0; i<NENERGIES; i++) rangeGausFitSyst[i]=0.05;

  //***********************************
  //* Read Files
  //***********************************
  TFile* ftest100 = new TFile("output.root");
  gDirectory->pwd();
  ftest100->ls("-d");
  //fd100->cd();
  //
  //* Definition of local histogram arrays
  //
  TH1D *shDepth[NENERGIES];
  TH1D *Erec[NENERGIES];
  TH1D *E1rec[NENERGIES];
  TH1D *E2rec[NENERGIES];
  TH1D *E3rec[NENERGIES];
  TH1D *E4rec[NENERGIES];
  TH2D *EtotVx[NENERGIES];
  TH2D *EtotVy[NENERGIES];
  TH1D *Ypos1[NENERGIES];
  TH1D *Ypos1MC[NENERGIES];
  
  TH1D *ErecMC[NENERGIES];
  TH1D *E1recMC[NENERGIES];
  TH1D *E2recMC[NENERGIES];
  TH1D *E3recMC[NENERGIES];
  TH1D *E4recMC[NENERGIES];
  TH1D *shDepthMC[NENERGIES];
  TH1D *shDepthMC0p2Al[NENERGIES];
  TH1D *G4close[NENERGIES];
  TH1D *SF[NENERGIES];
  TH2D *eloss[NENERGIES];
  TH2D *eleak[NENERGIES];
  TH1D *eReco[NENERGIES];
  TH1D *eRecoMC[NENERGIES];
  TH1D *eCalibF[NENERGIES];
  TH1D *eCalibFUp[NENERGIES];
  TH1D *etrue[NENERGIES];
  TH1D *eCalibDEDXmc[NENERGIES];
  TH1D *eCalibDEDXdata[NENERGIES];
  TH1D *eCalibMC[NENERGIES];
  TH1D *eResU[NENERGIES];

  double BinSIZE      [NENERGIES];
  for (int i=0; i<NENERGIES; i++) {
    BinSIZE     [i]=0.0;
  }

  gDirectory->GetObject("EleakVsShdepth100",eleak[0]);


  TCanvas *c1 = new TCanvas("c1","c1");


  TFile* f20data = new TFile("outputData20GeV.root");
  gDirectory->GetObject("Ereco20",Erec[0]);
  gDirectory->GetObject("E1reco20",E1rec[0]);
  gDirectory->GetObject("E2reco20",E2rec[0]);
  gDirectory->GetObject("E3reco20",E3rec[0]);
  gDirectory->GetObject("E4reco20",E4rec[0]);
  gDirectory->GetObject("shDepthAbs",shDepth[0]);
  gDirectory->GetObject("EtotVsbx20",EtotVx[0]);
  gDirectory->GetObject("EtotVsby20",EtotVy[0]);
  gDirectory->GetObject("YpositionL1",Ypos1[0]);
  gDirectory->GetObject("EcalibL20",eCalibDEDXdata[0]);
  TFile* f30data = new TFile("outputData30GeV.root");
  gDirectory->GetObject("Ereco30",Erec[1]);
  gDirectory->GetObject("E1reco30",E1rec[1]);
  gDirectory->GetObject("E2reco30",E2rec[1]);
  gDirectory->GetObject("E3reco30",E3rec[1]);
  gDirectory->GetObject("E4reco30",E4rec[1]);
  gDirectory->GetObject("EtotVsbx30",EtotVx[1]);
  gDirectory->GetObject("EtotVsby30",EtotVy[1]);
  gDirectory->GetObject("shDepthAbs",shDepth[1]);
  gDirectory->GetObject("EcalibL30",eCalibDEDXdata[1]);
  TFile* f50data = new TFile("outputData50GeV.root");
  gDirectory->GetObject("Ereco50",Erec[2]);
  gDirectory->GetObject("E1reco50",E1rec[2]);
  gDirectory->GetObject("E2reco50",E2rec[2]);
  gDirectory->GetObject("E3reco50",E3rec[2]);
  gDirectory->GetObject("E4reco50",E4rec[2]);
  gDirectory->GetObject("EtotVsbx50",EtotVx[2]);
  gDirectory->GetObject("EtotVsby50",EtotVy[2]);
  gDirectory->GetObject("shDepthAbs",shDepth[2]);
  gDirectory->GetObject("EcalibL50",eCalibDEDXdata[2]);
  TFile* f80data = new TFile("outputData80GeV.root");
  gDirectory->GetObject("Ereco80",Erec[3]);
  gDirectory->GetObject("E1reco80",E1rec[3]);
  gDirectory->GetObject("E2reco80",E2rec[3]);
  gDirectory->GetObject("E3reco80",E3rec[3]);
  gDirectory->GetObject("E4reco80",E4rec[3]);
  gDirectory->GetObject("EtotVsbx80",EtotVx[3]);
  gDirectory->GetObject("EtotVsby80",EtotVy[3]);
  gDirectory->GetObject("shDepthAbs",shDepth[3]);
  gDirectory->GetObject("EcalibL80",eCalibDEDXdata[3]);
  TFile* f100data = new TFile("outputData100GeV.root");
  gDirectory->GetObject("Ereco100",Erec[4]);
  gDirectory->GetObject("E1reco100",E1rec[4]);
  gDirectory->GetObject("E2reco100",E2rec[4]);
  gDirectory->GetObject("E3reco100",E3rec[4]);
  gDirectory->GetObject("E4reco100",E4rec[4]);
  gDirectory->GetObject("EtotVsbx100",EtotVx[4]);
  gDirectory->GetObject("EtotVsby100",EtotVy[4]);
  gDirectory->GetObject("shDepthAbs",shDepth[4]);
  gDirectory->GetObject("EcalibL100",eCalibDEDXdata[4]);
  TFile* f150data = new TFile("outputData150GeV.root");
  gDirectory->GetObject("Ereco150",Erec[5]);
  gDirectory->GetObject("E1reco150",E1rec[5]);
  gDirectory->GetObject("E2reco150",E2rec[5]);
  gDirectory->GetObject("E3reco150",E3rec[5]);
  gDirectory->GetObject("E4reco150",E4rec[5]);
  gDirectory->GetObject("EtotVsbx150",EtotVx[5]);
  gDirectory->GetObject("EtotVsby150",EtotVy[5]);
  gDirectory->GetObject("shDepthAbs",shDepth[5]);
  gDirectory->GetObject("EcalibL150",eCalibDEDXdata[5]);
  TFile* f200data = new TFile("outputData200GeV.root");
  gDirectory->GetObject("Ereco200",Erec[6]);
  gDirectory->GetObject("E1reco200",E1rec[6]);
  gDirectory->GetObject("E2reco200",E2rec[6]);
  gDirectory->GetObject("E3reco200",E3rec[6]);
  gDirectory->GetObject("E4reco200",E4rec[6]);
  gDirectory->GetObject("EtotVsbx200",EtotVx[6]);
  gDirectory->GetObject("EtotVsby200",EtotVy[6]);
  gDirectory->GetObject("shDepthAbs",shDepth[6]);
  gDirectory->GetObject("EcalibL200",eCalibDEDXdata[6]);
  TFile* f250data = new TFile("outputData250GeV.root");
  gDirectory->GetObject("Ereco250",Erec[7]);
  gDirectory->GetObject("E1reco250",E1rec[7]);
  gDirectory->GetObject("E2reco250",E2rec[7]);
  gDirectory->GetObject("E3reco250",E3rec[7]);
  gDirectory->GetObject("E4reco250",E4rec[7]);
  gDirectory->GetObject("EtotVsbx250",EtotVx[7]);
  gDirectory->GetObject("EtotVsby250",EtotVy[7]);
  gDirectory->GetObject("shDepthAbs",shDepth[7]);
  gDirectory->GetObject("EcalibL250",eCalibDEDXdata[7]);
  TFile* f300data = new TFile("outputData300GeV.root");
  gDirectory->GetObject("Ereco300",Erec[8]);
  gDirectory->GetObject("E1reco300",E1rec[8]);
  gDirectory->GetObject("E2reco300",E2rec[8]);
  gDirectory->GetObject("E3reco300",E3rec[8]);
  gDirectory->GetObject("E4reco300",E4rec[8]);
  gDirectory->GetObject("EtotVsbx300",EtotVx[8]);
  gDirectory->GetObject("EtotVsby300",EtotVy[8]);
  gDirectory->GetObject("shDepthAbs",shDepth[8]);
  gDirectory->GetObject("EcalibL300",eCalibDEDXdata[8]);



  TFile* f20mc0p2Al = new TFile("outputMC20GeV0p2Al.root");
  gDirectory->GetObject("Ereco20",ErecMC[0]);
  gDirectory->GetObject("E1reco20",E1recMC[0]);
  gDirectory->GetObject("E2reco20",E2recMC[0]);
  gDirectory->GetObject("E3reco20",E3recMC[0]);
  gDirectory->GetObject("E4reco20",E4recMC[0]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[0]);
  gDirectory->GetObject("YpositionL1",Ypos1MC[0]);
  TFile* f30mc0p2Al = new TFile("outputMC30GeV0p2Al.root");
  gDirectory->GetObject("Ereco30",ErecMC[1]);
  gDirectory->GetObject("E1reco30",E1recMC[1]);
  gDirectory->GetObject("E2reco30",E2recMC[1]);
  gDirectory->GetObject("E3reco30",E3recMC[1]);
  gDirectory->GetObject("E4reco30",E4recMC[1]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[1]);
  TFile* f50mc0p2Al = new TFile("outputMC50GeV0p2Al.root");
  gDirectory->GetObject("Ereco50",ErecMC[2]);
  gDirectory->GetObject("E1reco50",E1recMC[2]);
  gDirectory->GetObject("E2reco50",E2recMC[2]);
  gDirectory->GetObject("E3reco50",E3recMC[2]);
  gDirectory->GetObject("E4reco50",E4recMC[2]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[2]);
  TFile* f80mc0p2Al = new TFile("outputMC80GeV0p2Al.root");
  gDirectory->GetObject("Ereco80",ErecMC[3]);
  gDirectory->GetObject("E1reco80",E1recMC[3]);
  gDirectory->GetObject("E2reco80",E2recMC[3]);
  gDirectory->GetObject("E3reco80",E3recMC[3]);
  gDirectory->GetObject("E4reco80",E4recMC[3]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[3]);
  TFile* f100mc0p2Al = new TFile("outputMC100GeV0p2Al.root");
  gDirectory->GetObject("Ereco100",ErecMC[4]);
  gDirectory->GetObject("E1reco100",E1recMC[4]);
  gDirectory->GetObject("E2reco100",E2recMC[4]);
  gDirectory->GetObject("E3reco100",E3recMC[4]);
  gDirectory->GetObject("E4reco100",E4recMC[4]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[4]);
  TFile* f150mc0p2Al = new TFile("outputMC150GeV0p2Al.root");
  gDirectory->GetObject("Ereco150",ErecMC[5]);
  gDirectory->GetObject("E1reco150",E1recMC[5]);
  gDirectory->GetObject("E2reco150",E2recMC[5]);
  gDirectory->GetObject("E3reco150",E3recMC[5]);
  gDirectory->GetObject("E4reco150",E4recMC[5]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[5]);
  TFile* f200mc0p2Al = new TFile("outputMC200GeV0p2Al.root");
  gDirectory->GetObject("Ereco200",ErecMC[6]);
  gDirectory->GetObject("E1reco200",E1recMC[6]);
  gDirectory->GetObject("E2reco200",E2recMC[6]);
  gDirectory->GetObject("E3reco200",E3recMC[6]);
  gDirectory->GetObject("E4reco200",E4recMC[6]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[6]);
  TFile* f250mc0p2Al = new TFile("outputMC250GeV0p2Al.root");
  gDirectory->GetObject("Ereco250",ErecMC[7]);
  gDirectory->GetObject("E1reco250",E1recMC[7]);
  gDirectory->GetObject("E2reco250",E2recMC[7]);
  gDirectory->GetObject("E3reco250",E3recMC[7]);
  gDirectory->GetObject("E4reco250",E4recMC[7]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[7]);
  TFile* f300mc0p2Al = new TFile("outputMC300GeV0p2Al.root");
  gDirectory->GetObject("Ereco300",ErecMC[8]);
  gDirectory->GetObject("E1reco300",E1recMC[8]);
  gDirectory->GetObject("E2reco300",E2recMC[8]);
  gDirectory->GetObject("E3reco300",E3recMC[8]);
  gDirectory->GetObject("E4reco300",E4recMC[8]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p2Al[8]);



  TH1D *ErecMC0p5Al[NENERGIES];
  TH1D *E1recMC0p5Al[NENERGIES];
  TH1D *E2recMC0p5Al[NENERGIES];
  TH1D *E3recMC0p5Al[NENERGIES];
  TH1D *E4recMC0p5Al[NENERGIES];
  TH1D *shDepthMC0p5Al[NENERGIES];
  TFile* f20mc0p5Al = new TFile("outputMC20GeV0p5Al.root");
  gDirectory->GetObject("Ereco20",ErecMC0p5Al[0]);
  gDirectory->GetObject("E1reco20",E1recMC0p5Al[0]);
  gDirectory->GetObject("E2reco20",E2recMC0p5Al[0]);
  gDirectory->GetObject("E3reco20",E3recMC0p5Al[0]);
  gDirectory->GetObject("E4reco20",E4recMC0p5Al[0]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[0]);
  TFile* f30mc0p5Al = new TFile("outputMC30GeV0p5Al.root");
  gDirectory->GetObject("Ereco30",ErecMC0p5Al[1]);
  gDirectory->GetObject("E1reco30",E1recMC0p5Al[1]);
  gDirectory->GetObject("E2reco30",E2recMC0p5Al[1]);
  gDirectory->GetObject("E3reco30",E3recMC0p5Al[1]);
  gDirectory->GetObject("E4reco30",E4recMC0p5Al[1]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[1]);
  TFile* f50mc0p5Al = new TFile("outputMC50GeV0p5Al.root");
  gDirectory->GetObject("Ereco50",ErecMC0p5Al[2]);
  gDirectory->GetObject("E1reco50",E1recMC0p5Al[2]);
  gDirectory->GetObject("E2reco50",E2recMC0p5Al[2]);
  gDirectory->GetObject("E3reco50",E3recMC0p5Al[2]);
  gDirectory->GetObject("E4reco50",E4recMC0p5Al[2]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[2]);
  TFile* f80mc0p5Al = new TFile("outputMC80GeV0p5Al.root");
  gDirectory->GetObject("Ereco80",ErecMC0p5Al[3]);
  gDirectory->GetObject("E1reco80",E1recMC0p5Al[3]);
  gDirectory->GetObject("E2reco80",E2recMC0p5Al[3]);
  gDirectory->GetObject("E3reco80",E3recMC0p5Al[3]);
  gDirectory->GetObject("E4reco80",E4recMC0p5Al[3]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[3]);
  TFile* f100mc0p5Al = new TFile("outputMC100GeV0p5Al.root");
  gDirectory->GetObject("Ereco100",ErecMC0p5Al[4]);
  gDirectory->GetObject("E1reco100",E1recMC0p5Al[4]);
  gDirectory->GetObject("E2reco100",E2recMC0p5Al[4]);
  gDirectory->GetObject("E3reco100",E3recMC0p5Al[4]);
  gDirectory->GetObject("E4reco100",E4recMC0p5Al[4]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[4]);
  TFile* f150mc0p5Al = new TFile("outputMC150GeV0p5Al.root");
  gDirectory->GetObject("Ereco150",ErecMC0p5Al[5]);
  gDirectory->GetObject("E1reco150",E1recMC0p5Al[5]);
  gDirectory->GetObject("E2reco150",E2recMC0p5Al[5]);
  gDirectory->GetObject("E3reco150",E3recMC0p5Al[5]);
  gDirectory->GetObject("E4reco150",E4recMC0p5Al[5]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[5]);
  TFile* f200mc0p5Al = new TFile("outputMC200GeV0p5Al.root");
  gDirectory->GetObject("Ereco200",ErecMC0p5Al[6]);
  gDirectory->GetObject("E1reco200",E1recMC0p5Al[6]);
  gDirectory->GetObject("E2reco200",E2recMC0p5Al[6]);
  gDirectory->GetObject("E3reco200",E3recMC0p5Al[6]);
  gDirectory->GetObject("E4reco200",E4recMC0p5Al[6]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[6]);
  TFile* f250mc0p5Al = new TFile("outputMC250GeV0p5Al.root");
  gDirectory->GetObject("Ereco250",ErecMC0p5Al[7]);
  gDirectory->GetObject("E1reco250",E1recMC0p5Al[7]);
  gDirectory->GetObject("E2reco250",E2recMC0p5Al[7]);
  gDirectory->GetObject("E3reco250",E3recMC0p5Al[7]);
  gDirectory->GetObject("E4reco250",E4recMC0p5Al[7]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[7]);
  TFile* f300mc0p5Al = new TFile("outputMC300GeV0p5Al.root");
  gDirectory->GetObject("Ereco300",ErecMC0p5Al[8]);
  gDirectory->GetObject("E1reco300",E1recMC0p5Al[8]);
  gDirectory->GetObject("E2reco300",E2recMC0p5Al[8]);
  gDirectory->GetObject("E3reco300",E3recMC0p5Al[8]);
  gDirectory->GetObject("E4reco300",E4recMC0p5Al[8]);
  gDirectory->GetObject("shDepthAbs",shDepthMC0p5Al[8]);


  TFile* f20 = new TFile("outputMC20GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[0]);
  gDirectory->GetObject("G4closure",G4close[0]);
  gDirectory->GetObject("SF20",SF[0]);
  gDirectory->GetObject("EupVsEtwo100",eloss[0]);
  gDirectory->GetObject("EcalibF20",eCalibF[0]);
  gDirectory->GetObject("EcalibFUp20",eCalibFUp[0]);
  gDirectory->GetObject("Etrue20",etrue[0]);
  gDirectory->GetObject("EcalibL20",eCalibDEDXmc[0]);
  gDirectory->GetObject("EresUnsmear20",eResU[0]);
  TFile* f30 = new TFile("outputMC30GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[1]);
  gDirectory->GetObject("G4closure",G4close[1]);
  gDirectory->GetObject("SF30",SF[1]);
  gDirectory->GetObject("EupVsEtwo100",eloss[1]);
  gDirectory->GetObject("EcalibF30",eCalibF[1]);
  gDirectory->GetObject("EcalibFUp30",eCalibFUp[1]);
  gDirectory->GetObject("Etrue30",etrue[1]);
  gDirectory->GetObject("EcalibL30",eCalibDEDXmc[1]);
  gDirectory->GetObject("EresUnsmear30",eResU[1]);
  TFile* f50 = new TFile("outputMC50GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[2]);
  gDirectory->GetObject("G4closure",G4close[2]);
  gDirectory->GetObject("SF50",SF[2]);
  gDirectory->GetObject("EupVsEtwo100",eloss[2]);
  gDirectory->GetObject("EcalibF50",eCalibF[2]);
  gDirectory->GetObject("EcalibFUp50",eCalibFUp[2]);
  gDirectory->GetObject("Etrue50",etrue[2]);
  gDirectory->GetObject("EcalibL50",eCalibDEDXmc[2]);
  gDirectory->GetObject("EresUnsmear50",eResU[2]);
  TFile* f80 = new TFile("outputMC80GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[3]);
  gDirectory->GetObject("G4closure",G4close[3]);
  gDirectory->GetObject("SF80",SF[3]);
  gDirectory->GetObject("EupVsEtwo100",eloss[3]);
  gDirectory->GetObject("EcalibF80",eCalibF[3]);
  gDirectory->GetObject("EcalibFUp80",eCalibFUp[3]);
  gDirectory->GetObject("Etrue80",etrue[3]);
  gDirectory->GetObject("EcalibL80",eCalibDEDXmc[3]);
  gDirectory->GetObject("EresUnsmear80",eResU[3]);
  TFile* f100 = new TFile("outputMC100GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[4]);
  gDirectory->GetObject("G4closure",G4close[4]);
  gDirectory->GetObject("SF100",SF[4]);
  gDirectory->GetObject("EupVsEtwo100",eloss[4]);
  gDirectory->GetObject("EcalibF100",eCalibF[4]);
  gDirectory->GetObject("EcalibFUp100",eCalibFUp[4]);
  gDirectory->GetObject("Etrue100",etrue[4]);
  gDirectory->GetObject("EcalibL100",eCalibDEDXmc[4]);
  gDirectory->GetObject("EresUnsmear100",eResU[4]);
  TFile* f150 = new TFile("outputMC150GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[5]);
  gDirectory->GetObject("G4closure",G4close[5]);
  gDirectory->GetObject("SF150",SF[5]);
  gDirectory->GetObject("EupVsEtwo100",eloss[5]);
  gDirectory->GetObject("EcalibF150",eCalibF[5]);
  gDirectory->GetObject("EcalibFUp150",eCalibFUp[5]);
  gDirectory->GetObject("Etrue150",etrue[5]);
  gDirectory->GetObject("EcalibL150",eCalibDEDXmc[5]);
  gDirectory->GetObject("EresUnsmear150",eResU[5]);
  TFile* f200 = new TFile("outputMC200GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[6]);
  gDirectory->GetObject("G4closure",G4close[6]);
  gDirectory->GetObject("SF200",SF[6]);
  gDirectory->GetObject("EupVsEtwo100",eloss[6]);
  gDirectory->GetObject("EcalibF200",eCalibF[6]);
  gDirectory->GetObject("EcalibFUp200",eCalibFUp[6]);
  gDirectory->GetObject("Etrue200",etrue[6]);
  gDirectory->GetObject("EcalibL200",eCalibDEDXmc[6]);
  gDirectory->GetObject("EresUnsmear200",eResU[6]);
  TFile* f250 = new TFile("outputMC250GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[7]);
  gDirectory->GetObject("G4closure",G4close[7]);
  gDirectory->GetObject("SF250",SF[7]);
  gDirectory->GetObject("EupVsEtwo100",eloss[7]);
  gDirectory->GetObject("EcalibF250",eCalibF[7]);
  gDirectory->GetObject("EcalibFUp250",eCalibFUp[7]);
  gDirectory->GetObject("Etrue250",etrue[7]);
  gDirectory->GetObject("EcalibL250",eCalibDEDXmc[7]);
  gDirectory->GetObject("EresUnsmear250",eResU[7]);
  TFile* f300 = new TFile("outputMC300GeV.root");
  gDirectory->GetObject("shDepthAbs",shDepthMC[8]);
  gDirectory->GetObject("G4closure",G4close[8]);
  gDirectory->GetObject("SF300",SF[8]);
  gDirectory->GetObject("EupVsEtwo100",eloss[8]);
  gDirectory->GetObject("EcalibF300",eCalibF[8]);
  gDirectory->GetObject("EcalibFUp300",eCalibFUp[8]);
  gDirectory->GetObject("Etrue300",etrue[8]);
  gDirectory->GetObject("EcalibL300",eCalibDEDXmc[8]);
  gDirectory->GetObject("EresUnsmear300",eResU[8]);



  //
  //* Check the 1st Layer Y positions:
  //
  for(int i=0; i<1; i++){
    Ypos1MC[i]->Draw();
    Ypos1[i]->Draw("sameerrors");
    Ypos1[i]->SetMarkerSize(1.2);
    Ypos1MC[i]->SetXTitle("L1 Y posiction (cm)");
    Ypos1MC[i]->GetYaxis()->SetTitleOffset(1.3);
    //YL1[i]->SetMaximum(0.20);
    //YL1[i]->SetMinimum(0.0);
    c1->Update();
    c1->Print("YpositionL1.png");
  }
  //getchar();
  //exit(0);

  //
  //* Check the Etotal vs position:
  //
  TH1D* Evsx[NENERGIES];
  for(int i=0; i<NENERGIES; i++){
    Evsx[i] = EtotVx[i]->ProfileX();
    Evsx[i]->Draw();
    Evsx[i]->SetXTitle("Beam X posiction (cm)");
    Evsx[i]->SetYTitle("Total Energy");
    Evsx[i]->GetYaxis()->SetTitleOffset(1.3);
    Evsx[i]->SetMaximum(0.20);
    //Evsx[i]->SetMinimum(0.0);

  //EtotVx[0]->Draw();
    EtotVx[i]->Draw("box");
    EtotVx[i]->SetXTitle("Beam X posiction (cm)");
    EtotVx[i]->SetYTitle("Total Energy (GeV)");
    c1->Update();
    c1->Print("EnergyVsPositionEffect.png");
    //getchar();
  }
  c1->Update();
  //getchar();

  TH1D* Evsy[NENERGIES];
  for(int i=0; i<NENERGIES; i++){
    Evsy[i] = EtotVy[i]->ProfileX();
    Evsy[i]->Draw();
    Evsy[i]->SetXTitle("Beam Y posiction (cm)");
    Evsy[i]->SetYTitle("Total Energy");
    Evsy[i]->GetYaxis()->SetTitleOffset(1.3);
    Evsy[i]->SetMaximum(0.20);
    //Evsx[i]->SetMinimum(0.0);

  //EtotVx[0]->Draw();
    EtotVy[i]->Draw("box");
    EtotVy[i]->SetXTitle("Beam Y posiction (cm)");
    EtotVy[i]->SetYTitle("Total Energy (GeV)");
    c1->Update();
    c1->Print("EnergyVsPositionEffect.png");
    //getchar();
  }
  c1->Update();
  //getchar();


  //
  //* Control Plot1: Shower Depth
  //
  //gPad->SetLogy(1);//linear
  for(int i=0; i<NENERGIES; i++){
    TLegend legeSD(0.60,0.70,0.95,0.88);
    legeSD.SetFillStyle(0);  
    legeSD.SetBorderSize(0);
    legeSD.SetHeader("CMS HGCAL TB2018");
    //shDepthMC[i]->Sumw2();
    shDepth[i]->Draw("errors");
    shDepth[i]->SetMaximum(1.2*shDepth[i]->GetMaximum());
    shDepthMC[i]->Scale(shDepth[i]->Integral()/shDepthMC[i]->Integral());
    shDepthMC[i]->Draw("histosame");
    shDepthMC[i]->SetLineColor(2);
    shDepthMC0p2Al[i]->Scale(shDepth[i]->Integral()/shDepthMC0p2Al[i]->Integral());
    shDepthMC0p2Al[i]->Draw("histosame");
    shDepthMC0p5Al[i]->Scale(shDepth[i]->Integral()/shDepthMC0p5Al[i]->Integral());
    shDepthMC0p5Al[i]->Draw("histosame");
    shDepthMC0p5Al[i]->SetLineColor(4);
    //shDepth[i]->Draw("errorssame");

    shDepthMC[i]->SetXTitle("Shower Depth (X0)");
    sprintf(histoDraw,"Data %dGeV",BEAME[i]);
    legeSD.AddEntry(shDepth[i],histoDraw,"PL");
    sprintf(histoDraw,"MC MCP+0.2X0");
    legeSD.AddEntry(shDepthMC0p2Al[i],histoDraw,"L");
    sprintf(histoDraw,"MC MCP+BeamPosInZM800");
    legeSD.AddEntry(shDepthMC0p5Al[i],histoDraw,"L");
    sprintf(histoDraw,"MC No MCP");
    legeSD.AddEntry(shDepthMC[i],histoDraw,"L");
    legeSD.Draw();
    sprintf(histoDraw,"shDepthDataVsMC%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    //getchar();
  }
  cout << "Finished with Shower Depth Control plots" << endl;
  c1->Update();
  //getchar();
  //exit(0);


  //
  //* Control Plot 3: E1 data/MC
  //
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.50,0.70,0.82,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL TB2018");
    E1recMC[i]->Scale(E1rec[i]->Integral()/E1recMC[i]->Integral());
    E1recMC[i]->Draw("histo");
    E1recMC[i]->SetLineColor(kRed);
    E1recMC[i]->SetMaximum(1.1*E1recMC[i]->GetMaximum());
    E1recMC0p5Al[i]->Scale(E1rec[i]->Integral()/E1recMC0p5Al[i]->Integral());
    E1recMC0p5Al[i]->Draw("histosame");
    E1rec[i]->Draw("errorssame");
    E1recMC[i]->SetXTitle("E1_{rechit} (MeV)");
    sprintf(histoDraw,"Data %dGeV v11",BEAME[i]);
    leger.AddEntry(E1rec[i],histoDraw,"PL");
    sprintf(histoDraw,"MC   %dGeV +0.2X0",BEAME[i]);
    leger.AddEntry(E1recMC[i],histoDraw,"L");
    sprintf(histoDraw,"MC   %dGeV +BeamPosInZM800",BEAME[i]);
    leger.AddEntry(E1recMC0p5Al[i],histoDraw,"L");
    leger.Draw();
    sprintf(histoDraw,"E1recoDataVsMC%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    //getchar();
  }
  cout << "Finished with E1rec Control plots" << endl;
  //getchar();
  //exit(0);

  //
  //* Control Plots 3: E2 data/MC
  //
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.50,0.70,0.82,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL TB2018");
    E2recMC[i]->Scale(E2rec[i]->Integral()/E2recMC[i]->Integral());
    E2recMC[i]->Draw("histo");
    E2recMC[i]->SetLineColor(kRed);
    E2recMC[i]->SetMaximum(1.1*E2recMC[i]->GetMaximum());
    E2recMC0p5Al[i]->Scale(E2rec[i]->Integral()/E2recMC0p5Al[i]->Integral());
    E2recMC0p5Al[i]->Draw("histosame");
    E2rec[i]->Draw("errorssame");
    E2recMC[i]->SetXTitle("E2_{rechit} (MeV)");
    sprintf(histoDraw,"Data %dGeV v11",BEAME[i]);
    leger.AddEntry(E2rec[i],histoDraw,"PL");
    sprintf(histoDraw,"MC   %dGeV +0.2X0",BEAME[i]);
    leger.AddEntry(E2recMC[i],histoDraw,"L");
    sprintf(histoDraw,"MC   %dGeV +BeamPosInZM800",BEAME[i]);
    leger.AddEntry(E2recMC0p5Al[i],histoDraw,"L");
    leger.Draw();
    sprintf(histoDraw,"E2recoDataVsMC%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    getchar();
  }
  cout << "Finished with E2rec Control plots" << endl;
  //getchar();


  //
  //* Control Plots 3: E3 data/MC
  //
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.50,0.70,0.82,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL TB2018");
    E3recMC[i]->Scale(E3rec[i]->Integral()/E3recMC[i]->Integral());
    E3recMC[i]->Draw("histo");
    E3recMC[i]->SetLineColor(kRed);
    E3recMC[i]->SetMaximum(1.1*E3recMC[i]->GetMaximum());
    E3recMC0p5Al[i]->Scale(E3rec[i]->Integral()/E3recMC0p5Al[i]->Integral());
    E3recMC0p5Al[i]->Draw("histosame");
    E3rec[i]->Draw("errorssame");
    E3recMC[i]->SetXTitle("E3_{rechit} (MeV)");
    sprintf(histoDraw,"Data %dGeV v11",BEAME[i]);
    leger.AddEntry(E3rec[i],histoDraw,"PL");
    sprintf(histoDraw,"MC   %dGeV +0.2X0",BEAME[i]);
    leger.AddEntry(E3recMC[i],histoDraw,"L");
    sprintf(histoDraw,"MC   %dGeV +BeamPosInZM800",BEAME[i]);
    leger.AddEntry(E3recMC0p5Al[i],histoDraw,"L");
    leger.Draw();
    sprintf(histoDraw,"E3recoDataVsMC%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    getchar();
  }
  cout << "Finished with E3rec Control plots" << endl;
  //getchar();

  //
  //* Control Plots 3: E4 data/MC
  //
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.50,0.70,0.82,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL TB2018");
    E4recMC[i]->Scale(E4rec[i]->Integral()/E4recMC[i]->Integral());
    E4recMC[i]->Draw("histo");
    E4recMC[i]->SetLineColor(kRed);
    E4recMC[i]->SetMaximum(1.1*E4recMC[i]->GetMaximum());
    E4recMC0p5Al[i]->Scale(E4rec[i]->Integral()/E4recMC0p5Al[i]->Integral());
    E4recMC0p5Al[i]->Draw("histosame");
    E4rec[i]->Draw("errorssame");
    E4recMC[i]->SetXTitle("E4_{rechit} (MeV)");
    sprintf(histoDraw,"Data %dGeV v11",BEAME[i]);
    leger.AddEntry(E4rec[i],histoDraw,"PL");
    sprintf(histoDraw,"MC   %dGeV +0.2X0",BEAME[i]);
    leger.AddEntry(E4recMC[i],histoDraw,"L");
    sprintf(histoDraw,"MC   %dGeV +BeamPosInZM800",BEAME[i]);
    leger.AddEntry(E4recMC0p5Al[i],histoDraw,"L");
    leger.Draw();
    sprintf(histoDraw,"E4recoDataVsMC%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    getchar();
  }
  cout << "Finished with E4rec Control plots" << endl;
  //getchar();


  //exit(0);


  //****************************************
  //* Control Plot 2: Reco energy data/MC with Gaussian Fits
  //****************************************
  double meanEneData[NENERGIES];
  double sigmEneData[NENERGIES];
  double meanEneDataE[NENERGIES];
  double  sigmEneDataE[NENERGIES];
  double  chi2perDOFData[NENERGIES];
  double resolEneData[NENERGIES];
  double resolEneDataE[NENERGIES];
  double EscaleData[NENERGIES];
  double EscaleDataErr[NENERGIES];

  double meanEneMC[NENERGIES];
  double sigmEneMC[NENERGIES];
  double meanEneMCE[NENERGIES];
  double  sigmEneMCE[NENERGIES];
  double  chi2perDOFMC[NENERGIES];
  double resolEneMC[NENERGIES];
  double resolEneMCE[NENERGIES];
  double EscaleMC[NENERGIES];
  double EscaleMCErr[NENERGIES];

  double meanEneDEDXData[NENERGIES];
  double sigmEneDEDXData[NENERGIES];
  double meanEneDEDXDataE[NENERGIES];
  double  sigmEneDEDXDataE[NENERGIES];
  double  chi2perDOFDEDXData[NENERGIES];
  double resolEneDEDXData[NENERGIES];
  double resolEneDEDXDataE[NENERGIES];
  double EscaleDEDXData[NENERGIES];
  double EscaleDEDXDataErr[NENERGIES];

  double meanEneDEDXMC[NENERGIES];
  double sigmEneDEDXMC[NENERGIES];
  double meanEneDEDXMCE[NENERGIES];
  double  sigmEneDEDXMCE[NENERGIES];
  double  chi2perDOFDEDXMC[NENERGIES];
  double resolEneDEDXMC[NENERGIES];
  double resolEneDEDXMCE[NENERGIES];
  double EscaleDEDXMC[NENERGIES];
  double EscaleDEDXMCErr[NENERGIES];

  double dMCratio[NENERGIES];
  double dMCratioErr[NENERGIES];


  TF1 *f1 = new TF1("f1","gaus");
  TF1 *f2 = new TF1("f2","gaus");
  double Noise=0.2; double Sampl=0.30; double Linear=0.01;
  float nsigmasDown=1.0;
  float nsigmasUp  =2.5;
  double mpv,sigma;
  int   mbin;

  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.18,0.70,0.50,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL TB2018");
    ErecMC[i]->Sumw2();
    ErecMC[i]->Scale(Erec[i]->GetMaximum()/ErecMC[i]->GetMaximum());
    ErecMC[i]->Draw("histo");

    if(i==8) nsigmasDown=0.5;

    //* Fit the MC:
    mbin=ErecMC[i]->GetMaximumBin();
    mpv =ErecMC[i]->GetBinCenter(mbin);
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    ErecMC[i]->Fit("f1","","histo",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f1->GetParameter(1);
    sigma = f1->GetParameter(2);
    ErecMC[i]->Fit("f1","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    ErecMC[i]->Draw("histo");
    ErecMC[i]->SetLineColor(kRed);
    f1->SetLineColor(kRed);
    f1->SetRange(mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    f1->Draw("sames");
    gStyle->SetOptFit(0);
    meanEneMC[i]= f1->GetParameter(1);
    sigmEneMC[i]= f1->GetParameter(2);
    meanEneMCE[i]=f1->GetParError(1);
    sigmEneMCE[i]=f1->GetParError(2);
    chi2perDOFMC[i]=f1->GetChisquare()/f1->GetNDF();
    resolEneMC[i]=sigmEneMC[i]/meanEneMC[i];
    //double relErrorInSEoverEMC = 
    //  sqrt (
    //        (sigmEneMCE[i]/sigmEneMC[i])*(sigmEneMCE[i]/sigmEneMC[i])+
    //        (meanEneMCE[i]/meanEneMC[i])*(meanEneMCE[i]/meanEneMC[i])
    //        );
    double relErrorInSEoverEMC = sigmEneMCE[i]/sigmEneMC[i];
    resolEneMCE[i] = relErrorInSEoverEMC*resolEneMC[i];


    //* Fit the Data:
    mbin=Erec[i]->GetMaximumBin();
    mpv =Erec[i]->GetBinCenter(mbin);
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    //Erec[i]->Fit("f2","","N",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    Erec[i]->Fit("f2","","sames",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f2->GetParameter(1);
    sigma = f2->GetParameter(2);
    Erec[i]->Fit("f2","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    f2->SetLineColor(kBlack);
    f2->SetRange(mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    meanEneData[i]= f2->GetParameter(1);
    sigmEneData[i]= f2->GetParameter(2);
    meanEneDataE[i]=f2->GetParError(1);
    sigmEneDataE[i]=f2->GetParError(2);
    chi2perDOFData[i]=f2->GetChisquare()/f2->GetNDF();
    resolEneData[i]=sigmEneData[i]/meanEneData[i];
      
    double relErrorInSEoverE = 
      sqrt (
            (sigmEneDataE[i]/sigmEneData[i])*(sigmEneDataE[i]/sigmEneData[i])+
            (meanEneDataE[i]/meanEneData[i])*(meanEneDataE[i]/meanEneData[i])+
            rangeGausFitSyst[i]*rangeGausFitSyst[i]
            );
    //double relErrorInSEoverE = sigmEneDataE[i]/sigmEneData[i];
    resolEneDataE[i] = relErrorInSEoverE*resolEneData[i];


    //* Draw plots:
    ErecMC0p5Al[i]->Scale(Erec[i]->GetMaximum()/ErecMC0p5Al[i]->GetMaximum());
    ErecMC0p5Al[i]->Draw("histosame");
    ErecMC0p5Al[i]->SetLineColor(kBlue);
    ErecMC[i]->SetMaximum(1.1*ErecMC[i]->GetMaximum());
    ErecMC[i]->Draw("histosame");
    f2->Draw("sames");
    f1->Draw("sames");
    Erec[i]->Draw("errorssame");
    ErecMC[i]->SetXTitle("E_{visible} (GeV)");
    sprintf(histoDraw,"Data %dGeV v11",BEAME[i]);
    leger.AddEntry(Erec[i],histoDraw,"PL");
    sprintf(histoDraw,"MC   %dGeV +0.2X0",BEAME[i]);
    leger.AddEntry(ErecMC[i],histoDraw,"L");
    sprintf(histoDraw,"MC   %dGeV +BeamPosInZM800",BEAME[i]);
    leger.AddEntry(ErecMC0p5Al[i],histoDraw,"L");
    leger.Draw();
    sprintf(histoDraw,"ErecoDataVsMC%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    //getchar();
  }
  cout << "Finished with Erec Control plots" << endl;
  getchar();
  //exit(0);



  //*******************************************
  //* Resolution: Data/MC Raw Energies (rechit)
  //*******************************************
  float maxGraph= 0.015;
  float minGraph=-0.015;
  gStyle->SetLabelFont(62);
  c1->SetGrid();
  TLegend legresRAW(0.50,0.70,0.95,0.90);
  legresRAW.SetFillStyle(0);  
  legresRAW.SetBorderSize(0);
  legresRAW.SetHeader("HGCAL TB2018 Resolution");
  TGraphErrors* resolGraph_errorData = new TGraphErrors(NENERGIES,BEAMED,resolEneData,BinSIZE,resolEneDataE);
  resolGraph_errorData->SetTitle(0);
  resolGraph_errorData->SetMarkerSize(1.5);
  resolGraph_errorData->SetMarkerStyle(22);
  resolGraph_errorData->SetMaximum(0.06);
  resolGraph_errorData->SetMinimum(0.00);
  //* Fit sigma_E/E
  double frpar[3];
  TF1 resFitRaw("resFitRaw",resolutionf1,7.0,260,3);
  frpar[0] = 0.30;           // stoch term
  frpar[1] = 0.015;         // Constant term
  frpar[2] = 0.00;         // Noise term ~100MeV
  resFitRaw.SetParameters(frpar);
  resFitRaw.SetParName(0,"Stoch. Term");
  resFitRaw.SetParName(1,"Const. Term");
  resFitRaw.SetParName(2,"Noise  Term");
  //resFitRaw.FixParameter(1,0.01);
  resFitRaw.FixParameter(2,0.100);
  resFitRaw.SetRange(5.0,260.);
  resFitRaw.SetLineColor(1);
  resFitRaw.SetLineWidth(0.5);
  gStyle->SetStatX(0.85);
  gStyle->SetStatY(0.95);
  resolGraph_errorData->Fit("resFitRaw","RIM"); 
  double stochTerm=resFitRaw.GetParameter(0);
  double constTerm=resFitRaw.GetParameter(1);
  double stochTermE=resFitRaw.GetParError(0);
  double constTermE=resFitRaw.GetParError(1);
  double chi2=resFitRaw.GetChisquare();
  double ndof=resFitRaw.GetNDF();
  cout << "DT Fit result: stochTerm=" << stochTerm*100 << "+/-" << stochTermE*100 << "% constTerm:" 
       << constTerm*100  << "+/-" << constTermE*100 <<"%  chi2/ndof="<< chi2/ndof << endl;
  resolGraph_errorData->GetYaxis()->SetTitleOffset(1.3);
  resolGraph_errorData->GetXaxis()->SetTitle("Beam Energy (GeV)");
  resolGraph_errorData->GetYaxis()->SetTitle("Gaussian #sigma_{E}/<E>");
  resolGraph_errorData->Draw("AP");
  c1->Update();

  TGraphErrors* resolGraph_errorMC = new TGraphErrors(NENERGIES,BEAMED,resolEneMC,BinSIZE,resolEneMCE);
  resolGraph_errorMC->SetMarkerSize(1.5);
  resolGraph_errorMC->SetMarkerStyle(24);
  resolGraph_errorMC->SetMarkerColor(2);
  resolGraph_errorMC->SetLineColor(2);
  resolGraph_errorMC->Draw("Psame");
  legresRAW.AddEntry(resolGraph_errorData,"Data (v11 Rechit)","PL");
  legresRAW.AddEntry(resolGraph_errorMC,"MC v1, 0.2X0","PL");
  legresRAW.Draw();
  c1->Update();
  c1->Print("ResolutionMCDataRAWv11.png");
  getchar();

  //******************************
  //* Escales: RAW data vs Raw MC
  //******************************
  maxGraph= 3.0;
  minGraph=-0.1;
  gStyle->SetLabelFont(62);
  TLegend legdm(0.15,0.75,0.55,0.92);
  legdm.SetFillStyle(0);  
  legdm.SetBorderSize(0);
  legdm.SetHeader("HGCAL TB2018");
  TGraphErrors* dataRawEne_error = new TGraphErrors(NENERGIES,BEAMED,meanEneData,BinSIZE,meanEneDataE);
  dataRawEne_error->SetTitle(0);
  dataRawEne_error->SetMarkerSize(1.5);
  dataRawEne_error->SetMarkerStyle(22);
  dataRawEne_error->SetMarkerColor(1);
  dataRawEne_error->SetMaximum(maxGraph);
  dataRawEne_error->SetMinimum(minGraph);
  dataRawEne_error->Draw("AP");
  dataRawEne_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  dataRawEne_error->GetYaxis()->SetTitle("Raw <Erechit> (GeV)");
  dataRawEne_error->GetYaxis()->SetTitleOffset(1.4);
  dataRawEne_error->Draw("P");
  c1->Update();

  TGraphErrors* mcRawEne_error = new TGraphErrors(NENERGIES,BEAMED,meanEneMC,BinSIZE,meanEneMCE);
  mcRawEne_error->SetTitle(0);
  mcRawEne_error->SetMarkerSize(1.5);
  mcRawEne_error->SetMarkerStyle(24);
  mcRawEne_error->SetMarkerColor(2);
  mcRawEne_error->SetLineColor(2);
  mcRawEne_error->SetMaximum(maxGraph);
  mcRawEne_error->SetMinimum(minGraph);
  //mcRawEne_error->Draw("AP");
  mcRawEne_error->Draw("Psame");

  legdm.AddEntry(dataRawEne_error,"Data: v11","PL");
  legdm.AddEntry(mcRawEne_error,"MC: 0.2X0","PL");
  legdm.Draw();


  c1->Update();
  c1->Print("meanEDatavMCRAWv11.png");
  getchar();


  //******************************
  //* Escales: RAW data/MC ratio only
  //******************************

  for (int i=0; i<NENERGIES; i++) {

    dMCratio[i] = (meanEneData[i] - meanEneMC[i])/meanEneMC[i]; 
    double numerator =(meanEneData[i] - meanEneMC[i]);
    double numerError =sqrt(meanEneDataE[i]*meanEneDataE[i]+
                            meanEneMCE[i]*meanEneMCE[i]);
    double relErrNumer=numerError/numerator;
    double relErrDenom=meanEneMCE[i]/meanEneMC[i];
    dMCratioErr[i] =fabs(dMCratio[i])*sqrt(relErrNumer*relErrNumer+relErrDenom*relErrDenom);


  }


  maxGraph= 0.08;
  minGraph=-0.08;
  gStyle->SetLabelFont(62);
  TLegend legdmc(0.55,0.72,0.90,0.92);
  legdmc.SetFillStyle(0);  
  legdmc.SetBorderSize(0);
  legdmc.SetHeader("HGCAL TB2018");
  TGraphErrors* dMCratio_error = new TGraphErrors(NENERGIES,BEAMED,dMCratio,BinSIZE,dMCratioErr);
  dMCratio_error->SetTitle(0);
  dMCratio_error->SetMarkerSize(1.5);
  dMCratio_error->SetMarkerStyle(20);
  dMCratio_error->SetMarkerColor(1);
  dMCratio_error->SetMaximum(maxGraph);
  dMCratio_error->SetMinimum(minGraph);
  dMCratio_error->Draw("AP");
  dMCratio_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  dMCratio_error->GetYaxis()->SetTitle("(E_{data}-E_{MC})/E_{MC}");
  dMCratio_error->GetYaxis()->SetTitleOffset(1.4);
  dMCratio_error->Draw("P");
  legdmc.AddEntry(dMCratio_error,"datav11/MC","PL");
  legdmc.Draw();

  c1->Update();
  c1->Print("meanEDataByMCRAWv11.png");

  getchar();
  //exit(0);

  //***********************************************************************
  //* dEdX calibration data/MC   eCalibDEDXdata and eCalibDEDXmc          *
  //***********************************************************************
  nsigmasDown=1.0;
  nsigmasUp  =2.5;
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.15,0.70,0.55,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL TB2018");
    eCalibDEDXmc[i]->Sumw2();
    eCalibDEDXmc[i]->Scale(eCalibDEDXdata[i]->GetMaximum()/eCalibDEDXmc[i]->GetMaximum());
    eCalibDEDXmc[i]->Draw("histo");

    //if(i==8) nsigmasDown=0.5;

    //* Fit the MC:
    mbin=eCalibDEDXmc[i]->GetMaximumBin();
    mpv =eCalibDEDXmc[i]->GetBinCenter(mbin);
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    eCalibDEDXmc[i]->Fit("f1","","histo",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f1->GetParameter(1);
    sigma = f1->GetParameter(2);
    eCalibDEDXmc[i]->Fit("f1","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    eCalibDEDXmc[i]->Draw("histo");
    eCalibDEDXmc[i]->SetLineColor(kRed);
    f1->SetLineColor(kRed);
    f1->SetRange(mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    f1->Draw("sames");
    gStyle->SetOptFit(0);
    meanEneDEDXMC[i]= f1->GetParameter(1);
    sigmEneDEDXMC[i]= f1->GetParameter(2);
    meanEneDEDXMCE[i]=f1->GetParError(1);
    sigmEneDEDXMCE[i]=f1->GetParError(2);
    chi2perDOFDEDXMC[i]=f1->GetChisquare()/f1->GetNDF();
    resolEneDEDXMC[i]=sigmEneDEDXMC[i]/meanEneDEDXMC[i];
    double relErrorInSEoverEDEDXMC = 
      sqrt (
            (sigmEneDEDXMCE[i]/sigmEneDEDXMC[i])*(sigmEneDEDXMCE[i]/sigmEneDEDXMC[i])+
            (meanEneDEDXMCE[i]/meanEneDEDXMC[i])*(meanEneDEDXMCE[i]/meanEneDEDXMC[i])
            );
    //double relErrorInSEoverEDEDXMC = sigmEneDEDXMCE[i]/sigmEneDEDXMC[i];
    resolEneDEDXMCE[i] = relErrorInSEoverEDEDXMC*resolEneDEDXMC[i];

    //* Fit the Data:
    mbin=eCalibDEDXdata[i]->GetMaximumBin();
    mpv =eCalibDEDXdata[i]->GetBinCenter(mbin);
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    //eCalibDEDXdata[i]->Fit("f2","","N",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    eCalibDEDXdata[i]->Fit("f2","","sames",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f2->GetParameter(1);
    sigma = f2->GetParameter(2);
    eCalibDEDXdata[i]->Fit("f2","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    f2->SetLineColor(kBlack);
    f2->SetRange(mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);

    meanEneDEDXData[i]= f2->GetParameter(1);
    sigmEneDEDXData[i]= f2->GetParameter(2);
    meanEneDEDXDataE[i]=f2->GetParError(1);
    sigmEneDEDXDataE[i]=f2->GetParError(2);
    chi2perDOFDEDXData[i]=f2->GetChisquare()/f2->GetNDF();
    resolEneDEDXData[i]=sigmEneDEDXData[i]/meanEneDEDXData[i];
    double relErrorInSEoverE = 
      sqrt (
            (sigmEneDEDXDataE[i]/sigmEneDEDXData[i])*(sigmEneDEDXDataE[i]/sigmEneDEDXData[i])+
            (meanEneDEDXDataE[i]/meanEneDEDXData[i])*(meanEneDEDXDataE[i]/meanEneDEDXData[i])+
            rangeGausFitSyst[i]*rangeGausFitSyst[i]
            );
    //double relErrorInSEoverE = sigmEneDEDXDataE[i]/sigmEneDEDXData[i];
    resolEneDEDXDataE[i] = relErrorInSEoverE*resolEneDEDXData[i];


    //* Draw plots:
    eCalibDEDXmc[i]->SetMaximum(1.1*eCalibDEDXmc[i]->GetMaximum());
    eCalibDEDXmc[i]->Draw("histosame");
    f2->Draw("sames");
    f1->Draw("sames");
    eCalibDEDXdata[i]->Draw("errorssame");
    eCalibDEDXmc[i]->SetXTitle("E_{visible} (GeV)");
    sprintf(histoDraw,"DEDXData %dGeV v11",BEAME[i]);
    leger.AddEntry(eCalibDEDXdata[i],histoDraw,"PL");
    sprintf(histoDraw,"DEDXMC   %dGeV +0.2X0",BEAME[i]);
    leger.AddEntry(eCalibDEDXmc[i],histoDraw,"L");
    leger.Draw();
    sprintf(histoDraw,"ErecoDataVsMCdEdxCalibrated%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    //getchar();
  }
  cout << "Finished with dEdX resolution fits" << endl;
  getchar();

  //
  //* Do the Escales with dEdx:
  //
  for (int i=0; i<NENERGIES; i++) {

    EscaleDEDXData[i] = (meanEneDEDXData[i] - BEAMED[i])/BEAMED[i]; 
    EscaleDEDXMC  [i] = (meanEneDEDXMC  [i] - BEAMED[i])/BEAMED[i]; 
    
    //* Stat Errors:
    //* MC
    double numerator =(meanEneDEDXMC[i] - BEAMED[i]);
    double numerError =sqrt(meanEneDEDXMCE[i]*meanEneDEDXMCE[i]);
    double relErrNumer=numerError/numerator;
    double relErrDenom=0.0;
    EscaleDEDXMCErr[i] =fabs(EscaleDEDXMC[i])*sqrt(relErrNumer*relErrNumer+relErrDenom*relErrDenom);
    
    //* Data
    numerator =(meanEneDEDXData[i] - BEAMED[i]);
    numerError =sqrt(meanEneDEDXDataE[i]*meanEneDEDXDataE[i]+
                            BEAMEE[i]*BEAMEE[i]
                            );
    relErrNumer=numerError/numerator;
    relErrDenom=BEAMEE[i]/BEAMED[i];
    EscaleDEDXDataErr[i] =fabs(EscaleDEDXData[i])*sqrt(relErrNumer*relErrNumer+relErrDenom*relErrDenom);

    cout << "EscaleDEDX : Data= " << EscaleDEDXData[i] << " MC= " << EscaleDEDXMC[i] << endl;
  }

  //*******************************************
  //* Draw Resolution: Data/MC dEdx Energies  *
  //*******************************************
  maxGraph= 0.015;
  minGraph=-0.015;
  gStyle->SetLabelFont(62);
  c1->SetGrid();
  TLegend legresDEDX(0.50,0.70,0.95,0.90);
  legresDEDX.SetFillStyle(0);  
  legresDEDX.SetBorderSize(0);
  legresDEDX.SetHeader("HGCAL TB2018 Resolution");
  TGraphErrors* resolGraph_errorDEDXData = new TGraphErrors(NENERGIES,BEAMED,resolEneDEDXData,BinSIZE,resolEneDEDXDataE);
  resolGraph_errorDEDXData->SetTitle(0);
  resolGraph_errorDEDXData->SetMarkerSize(1.5);
  resolGraph_errorDEDXData->SetMarkerStyle(22);
  resolGraph_errorDEDXData->SetMaximum(0.06);
  resolGraph_errorDEDXData->SetMinimum(0.00);
  //* Fit sigma_E/E
  TF1 resFitdEdX("resFitdEdX",resolutionf1,7.0,260,3);
  frpar[0] = 0.30;           // stoch term
  frpar[1] = 0.04;         // Constant term
  frpar[2] = 0.100;         // Noise term ~100MeV
  resFitdEdX.SetParameters(frpar);
  resFitdEdX.SetParName(0,"Stoch. Term");
  resFitdEdX.SetParName(1,"Const. Term");
  resFitdEdX.SetParName(2,"Noise  Term");
  //resFitdEdX.FixParameter(1,0.01);
  resFitdEdX.FixParameter(2,0.100);
  resFitdEdX.SetRange(5.0,260.);
  resFitdEdX.SetLineColor(1);
  resFitdEdX.SetLineWidth(0.5);
  gStyle->SetStatX(0.85);
  gStyle->SetStatY(0.95);
  resolGraph_errorDEDXData->Fit("resFitdEdX","RIM"); 
  stochTerm=resFitdEdX.GetParameter(0);
  constTerm=resFitdEdX.GetParameter(1);
  stochTermE=resFitdEdX.GetParError(0);
  constTermE=resFitdEdX.GetParError(1);
  chi2=resFitdEdX.GetChisquare();
  ndof=resFitdEdX.GetNDF();
  cout << "DT Fit result: stochTerm=" << stochTerm*100 << "+/-" << stochTermE*100 << "% constTerm:" 
       << constTerm*100  << "+/-" << constTermE*100 <<"%  chi2/ndof="<< chi2/ndof << endl;
  resolGraph_errorDEDXData->GetYaxis()->SetTitleOffset(1.3);
  resolGraph_errorDEDXData->GetXaxis()->SetTitle("Beam Energy (GeV)");
  resolGraph_errorDEDXData->GetYaxis()->SetTitle("Gaussian #sigma_{E}/<E>");
  resolGraph_errorDEDXData->Draw("AP");
  c1->Update();

  TGraphErrors* resolGraph_errorDEDXMC = new TGraphErrors(NENERGIES,BEAMED,resolEneDEDXMC,BinSIZE,resolEneDEDXMCE);
  resolGraph_errorDEDXMC->SetMarkerSize(1.5);
  resolGraph_errorDEDXMC->SetMarkerStyle(24);
  resolGraph_errorDEDXMC->SetMarkerColor(2);
  resolGraph_errorDEDXMC->SetLineColor(2);
  resolGraph_errorDEDXMC->Draw("Psame");
  legresDEDX.AddEntry(resolGraph_errorDEDXData,"dEdx Data (v11 Rechit)","PL");
  legresDEDX.AddEntry(resolGraph_errorDEDXMC,"dEdx MC v1, 0.2X0","PL");
  legresDEDX.Draw();
  c1->Update();
  c1->Print("ResolutionDEDXMCDataRAWv11.png");
  cout << "Finished with ResolutionDEDX ... " << endl;
  getchar();


  //*******************************************
  //* Draw Linearity: Data/MC dEdx Energies   *
  //*******************************************
  maxGraph= 0.1;
  minGraph=-0.1;

  TLegend leglinDEDX(0.50,0.72,0.90,0.90);
  leglinDEDX.SetFillStyle(0);  
  leglinDEDX.SetBorderSize(0);
  leglinDEDX.SetHeader("HGCAL TB2018 Linearity");
 
 

  TGraphErrors* linearityDEDXGraph_error = new TGraphErrors(NENERGIES,BEAMED,EscaleDEDXMC,BinSIZE,EscaleDEDXMCErr);

  linearityDEDXGraph_error->SetTitle(0);
  linearityDEDXGraph_error->SetMarkerSize(1.5);
  linearityDEDXGraph_error->SetMarkerStyle(24);
  linearityDEDXGraph_error->SetMarkerColor(2);
  linearityDEDXGraph_error->SetMaximum(maxGraph);
  linearityDEDXGraph_error->SetMinimum(minGraph);
  linearityDEDXGraph_error->Draw("AP");
  linearityDEDXGraph_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  linearityDEDXGraph_error->GetYaxis()->SetTitle("<(E-E_{beam})/E_{beam}>");
  linearityDEDXGraph_error->GetYaxis()->SetTitleOffset(1.2);
  linearityDEDXGraph_error->Draw("P");
  c1->SetGrid();
  c1->Update();


  TGraphErrors* linearDataDEDXGraph_error = new TGraphErrors(NENERGIES,BEAMED,EscaleDEDXData,BinSIZE,EscaleDEDXDataErr);
  linearDataDEDXGraph_error->SetTitle(0);
  linearDataDEDXGraph_error->SetMarkerSize(1.5);
  linearDataDEDXGraph_error->SetMarkerStyle(22);
  linearDataDEDXGraph_error->SetMarkerColor(1);
  linearDataDEDXGraph_error->GetYaxis()->SetTitleOffset(1.2);
  linearDataDEDXGraph_error->Draw("P");
  leglinDEDX.AddEntry(linearDataDEDXGraph_error,"Data: dEdx calibration","PL");
  leglinDEDX.AddEntry(linearityDEDXGraph_error,"MC : dEdx calibration","PL");
  leglinDEDX.Draw();
  c1->SetGrid();
  c1->Update();
  c1->Print("LinearitydEdxData.png");
  cout << "Finished with LinearityDEDX ... " << endl;
  getchar();
  //exit(0);



  //************************************
  //* Eloss Plot using truth (G4 hits)
  //************************************
  TH1D *px[NENERGIES];
  for (int i=0; i<2; i++) {
    auto legeEloss= new TLegend(0.20,0.70,0.60,0.88);
    px[i] = eloss[i]->ProfileX();
    px[i]->Draw();
    px[i]->SetXTitle("E_{1}+E_{2} (MeV)");
    px[i]->SetYTitle("E_{loss}/E_{tot} (%)");
    px[i]->GetYaxis()->SetTitleOffset(1.3);
    px[i]->SetMinimum(0.02);

    legeEloss->SetFillStyle(0);  
    legeEloss->SetBorderSize(0);
    legeEloss->SetHeader("CMS HGCAL TB2018");
    sprintf(histoDraw,"MC %dGeV",BEAME[i]);
    legeEloss->AddEntry(px[i],histoDraw,"LM");
    legeEloss->Draw();
    
    //c1->Modified();
    c1->Update();
    sprintf(histoDraw,"elossMC%dGeV.png",BEAME[i]);
    c1->Print(histoDraw);
    //getchar();
  }
  cout <<"Finished with the Eloss Upstream" << endl;
  //getchar();

  //*******************************
  //* Resolutions (Calibrated + MC)
  //*******************************

  double meanEneF[NENERGIES];
  double sigmEneF[NENERGIES];
  double meanEneFE[NENERGIES];
  double  sigmEneFE[NENERGIES];
  double  chi2perDOF[NENERGIES];
  double resolEneF[NENERGIES];
  double resolEneFE[NENERGIES];
  double relErrorInSEoverEF;
  double EscaleF[NENERGIES];
  double EscaleFErr[NENERGIES];

  double meanEneFUp[NENERGIES];
  double sigmEneFUp[NENERGIES];
  double meanEneFUpE[NENERGIES];
  double sigmEneFUpE[NENERGIES];
  double chi2perDOFFUp[NENERGIES];
  double resolEneFUp[NENERGIES];
  double resolEneFUpE[NENERGIES];
  double relErrorInSEoverEFUp;
  double EscaleFUp[NENERGIES];
  double EscaleFUpErr[NENERGIES];

  //* the following is the dEdx (bad name to use L)
  double meanEneL[NENERGIES];
  double sigmEneL[NENERGIES];
  double meanEneLE[NENERGIES];
  double sigmEneLE[NENERGIES];
  double resolEneL[NENERGIES];
  double resolEneLE[NENERGIES];
  double relErrorInSEoverEL;
  double EscaleL[NENERGIES];
  double EscaleLErr[NENERGIES];

  double meanEneU[NENERGIES];
  double sigmEneU[NENERGIES];
  double meanEneUE[NENERGIES];
  double sigmEneUE[NENERGIES];
  double resolEneU[NENERGIES];
  double resolEneUE[NENERGIES];
  double relErrorInSEoverEU;
  double EscaleU[NENERGIES];
  double EscaleUE[NENERGIES];

  double meanSF[NENERGIES];
  double sigmSF[NENERGIES];
  double meanSFE[NENERGIES];
  double sigmSFE[NENERGIES];
  double hmeanSF[NENERGIES];
  double hmeanSFE[NENERGIES];
  double medianSF[NENERGIES];

  double meanG4[NENERGIES];
  double meanG4E[NENERGIES];
  double medianG4[NENERGIES];


  //
  //* G4closure: Closure test first
  //
  for(int i=0; i<NENERGIES; i++){
    G4close[i]->Draw();
    Double_t median;
    Double_t q=0.5;
    G4close[i]->GetQuantiles(1,&median,&q);
    cout << "Median: "<< median << endl;
    medianG4[i]= median;
    meanG4[i]= G4close[i]->GetMean();
    meanG4E[i]= G4close[i]->GetMeanError();
    c1->Update();
    //getchar();
  }  
  double maxG4= 0.;
  double minG4= -0.01;
  //TLegend legSF(0.18,0.70,0.66,0.90);
  //legSF.SetFillStyle(0);  
  //legSF.SetBorderSize(0);
  //legSF.SetHeader("HGCAL TB2018 Sampling Fractions");
  TGraphErrors* G4Graph_error = new TGraphErrors(NENERGIES,BEAMED,meanG4,BinSIZE,meanG4E);
  G4Graph_error->SetTitle(0);
  G4Graph_error->SetMarkerSize(1.2);
  G4Graph_error->SetMarkerStyle(22);
  G4Graph_error->SetMarkerColor(2);
  G4Graph_error->SetMaximum(maxG4);
  G4Graph_error->SetMinimum(minG4);
  G4Graph_error->Draw("AP");
  G4Graph_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  G4Graph_error->GetYaxis()->SetTitle("<(Egeant-Etrue)/Etrue>");
  G4Graph_error->GetYaxis()->SetTitleOffset(1.3);
  G4Graph_error->Draw("P");
  sprintf(histoDraw,"G4closureGeV.png");
  c1->Update();
  c1->Print(histoDraw);
  for(int i=0; i<NENERGIES; i++){
    if(i<NENERGIES-1)
      cout << medianG4[i] <<" , " ;
    else
      cout << medianG4[i];
  }
  cout << endl;
  cout << "finished with the G4 graph" << endl;
  getchar();
  

  //
  //* SF: Sampling Fractions
  //
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.18,0.70,0.50,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL MC");
    mbin=SF[i]->GetMaximumBin();
    mpv =SF[i]->GetBinCenter(mbin);
    SF[i]->Fit("f2","","histo",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f2->GetParameter(1);
    sigma = f2->GetParameter(2);
    SF[i]->Fit("f1","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    SF[i]->SetMaximum(1.05*SF[i]->GetMaximum());
    SF[i]->Draw("histo");
    meanSF[i]= f1->GetParameter(1);
    cout << meanSF[i] << endl;
    sigmSF[i]= f1->GetParameter(2);
    meanSFE[i]=f1->GetParError(1);
    sigmSFE[i]=f1->GetParError(2);
    hmeanSF[i]= SF[i]->GetMean();
    hmeanSFE[i]= SF[i]->GetMeanError();
    Double_t median;
    Double_t q=0.5;
    SF[i]->GetQuantiles(1,&median,&q);
    cout << "Median: "<< median << endl;
    medianSF[i]= median;


    f1->SetLineColor(kRed);
    f1->SetRange(mpv-4*sigma,mpv+4*sigma);
    f1->Draw("sames");
    SF[i]->Draw("histosame");

    sprintf(histoDraw,"MC %dGeV",BEAME[i]);
    leger.AddEntry(eCalibF[i],histoDraw,"PL");
    leger.Draw();

    gStyle->SetOptStat(1);
    sprintf(histoDraw,"InverseSF%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    //getchar();
  }

  double maxSF= 110.2;
  double minSF= 108.6;
  gStyle->SetLabelFont(62);
  TLegend legSF(0.18,0.70,0.66,0.90);
  legSF.SetFillStyle(0);  
  legSF.SetBorderSize(0);
  legSF.SetHeader("HGCAL TB2018 Sampling Fractions");
  TGraphErrors* SFGraph_error = new TGraphErrors(NENERGIES,BEAMED,meanSF,BinSIZE,meanSFE);
  SFGraph_error->SetTitle(0);
  SFGraph_error->SetMarkerSize(1.2);
  SFGraph_error->SetMarkerStyle(22);
  SFGraph_error->SetMarkerColor(2);
  SFGraph_error->SetMaximum(maxSF);
  SFGraph_error->SetMinimum(minSF);
  SFGraph_error->Draw("AP");
  SFGraph_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  SFGraph_error->GetYaxis()->SetTitle("<(Esi+Epassive)/Esi>");
  SFGraph_error->GetYaxis()->SetTitleOffset(1.3);
  SFGraph_error->Draw("P");

  TGraphErrors* SFhGraph_error = new TGraphErrors(NENERGIES,BEAMED,hmeanSF,BinSIZE,hmeanSFE);
  SFhGraph_error->SetMarkerSize(1.2);
  SFhGraph_error->SetMarkerStyle(24);
  SFhGraph_error->SetMarkerColor(1);
  SFhGraph_error->Draw("Psame");
  legSF.AddEntry(SFhGraph_error,"Histogram <SF^{-1}>","PL");
  legSF.AddEntry(SFGraph_error,"Gaussian <SF^{-1}>","PL");
  legSF.Draw();

  cout << "Histogram Mean" << endl;
  for(int i=0; i<NENERGIES; i++){
    if(i<NENERGIES-1)
      cout << hmeanSF[i] <<" , " ;
    else
      cout << hmeanSF[i];
  }
  cout << endl;
  cout << "Median" << endl;
  for(int i=0; i<NENERGIES; i++){
    if(i<NENERGIES-1)
      //cout << meanSF[i] <<" , " ;
      cout << medianSF[i] <<" , " ;
    else
      //cout << meanSF[i];
      cout << medianSF[i];
  }
  cout << endl;
  cout << "Finished with the SF plots" << endl;
  c1->Update();
  c1->Print("SFhistoGaussian.png");
  getchar();
  //exit(0);




  //* True Energies first (they are smeared)
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.18,0.70,0.50,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL MC");
    mbin=etrue[i]->GetMaximumBin();
    mpv =etrue[i]->GetBinCenter(mbin);
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    etrue[i]->Fit("f1","","histo",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f1->GetParameter(1);
    sigma = f1->GetParameter(2);
    etrue[i]->Fit("f1","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    etrue[i]->SetMaximum(1.05*etrue[i]->GetMaximum());
    etrue[i]->Draw("histo");
    f1->SetLineColor(kRed);
    f1->SetRange(mpv-4*sigma,mpv+4*sigma);
    f1->Draw("sames");
    etrue[i]->Draw("histosame");
    gStyle->SetOptFit(0);
    //getchar();
  }


  //
  //* eCalibF: just a factor applied
  //
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.18,0.70,0.50,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL MC");
    mbin=eCalibF[i]->GetMaximumBin();
    mpv =eCalibF[i]->GetBinCenter(mbin);
    //* Fit the MC:
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    eCalibF[i]->Fit("f1","","histo",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f1->GetParameter(1);
    sigma = f1->GetParameter(2);
    eCalibF[i]->Fit("f1","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    eCalibF[i]->SetMaximum(1.05*eCalibF[i]->GetMaximum());
    eCalibF[i]->Draw("histo");
    f1->SetLineColor(kRed);
    f1->SetRange(mpv-4*sigma,mpv+4*sigma);
    f1->Draw("sames");
    eCalibF[i]->Draw("histosame");
    gStyle->SetOptFit(0);
    meanEneF[i]= f1->GetParameter(1);
    sigmEneF[i]= f1->GetParameter(2);
    meanEneFE[i]=f1->GetParError(1);
    sigmEneFE[i]=f1->GetParError(2);
    chi2perDOF  [i]=f1->GetChisquare()/f1->GetNDF();
    eCalibF[i]->SetMaximum(1.05*eCalibF[i]->GetMaximum());
    resolEneF[i]=sigmEneF[i]/meanEneF[i];
    double relErrorInSEoverEF = sigmEneFE[i]/sigmEneF[i];
    resolEneFE[i] = relErrorInSEoverEF*resolEneF[i];

    eCalibF[i]->SetXTitle("(E_{rec}-E_{beam})/E_{beam} (GeV)");
    sprintf(histoDraw,"MC %dGeV",BEAME[i]);
    leger.AddEntry(eCalibF[i],histoDraw,"PL");
    sprintf(histoDraw,"F   %dGeV",BEAME[i]);
    leger.Draw();
    sprintf(histoDraw,"EcalibF%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    //getchar();
  }

  //
  //* eCalibF: just a factor + Ebeam loss
  //
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.18,0.70,0.50,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL MC");
    mbin=eCalibFUp[i]->GetMaximumBin();
    mpv =eCalibFUp[i]->GetBinCenter(mbin);
    //* Fit the MC:
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    eCalibFUp[i]->Fit("f1","","histo",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f1->GetParameter(1);
    sigma = f1->GetParameter(2);
    eCalibFUp[i]->Fit("f1","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    eCalibFUp[i]->SetMaximum(1.05*eCalibFUp[i]->GetMaximum());
    eCalibFUp[i]->Draw("histo");
    f1->SetLineColor(kRed);
    f1->SetRange(mpv-4*sigma,mpv+4*sigma);
    f1->Draw("sames");
    eCalibF[i]->Draw("histosame");
    gStyle->SetOptFit(0);
    meanEneFUp[i]= f1->GetParameter(1);
    sigmEneFUp[i]= f1->GetParameter(2);
    meanEneFUpE[i]=f1->GetParError(1);
    sigmEneFUpE[i]=f1->GetParError(2);
    chi2perDOF  [i]=f1->GetChisquare()/f1->GetNDF();
    eCalibFUp[i]->SetMaximum(1.05*eCalibFUp[i]->GetMaximum());
    resolEneFUp[i]=sigmEneFUp[i]/meanEneFUp[i];
    double relErrorInSEoverEF = sigmEneFUpE[i]/sigmEneFUp[i];
    resolEneFUpE[i] = relErrorInSEoverEF*resolEneFUp[i];
    
    eCalibF[i]->SetXTitle("(E_{rec}-E_{beam})/E_{beam} (GeV)");
    sprintf(histoDraw,"Data %dGeV",BEAME[i]);
    leger.AddEntry(eCalibFUp[i],histoDraw,"PL");
    sprintf(histoDraw,"F   %dGeV",BEAME[i]);
    leger.Draw();
    sprintf(histoDraw,"EcalibFUp%dGeV.png",BEAME[i]);
    c1->Update();
    //c1->Print(histoDraw);
    //getchar();
  }

  //*eCalibDEDXmc: This is the dEdx Calibration!
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.18,0.70,0.50,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL MC");
    mbin=eCalibDEDXmc[i]->GetMaximumBin();
    mpv =eCalibDEDXmc[i]->GetBinCenter(mbin);
    //* Fit the MC:
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    eCalibDEDXmc[i]->Fit("f1","","histo",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f1->GetParameter(1);
    sigma = f1->GetParameter(2);
    eCalibDEDXmc[i]->Fit("f1","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    eCalibDEDXmc[i]->SetMaximum(1.05*eCalibF[i]->GetMaximum());
    eCalibDEDXmc[i]->Draw("histo");
    f1->SetLineColor(kRed);
    f1->SetRange(mpv-4*sigma,mpv+4*sigma);
    f1->Draw("sames");
    eCalibDEDXmc[i]->Draw("histosame");
    gStyle->SetOptFit(0);
    meanEneL[i]= f1->GetParameter(1);
    sigmEneL[i]= f1->GetParameter(2);
    meanEneLE[i]=f1->GetParError(1);
    sigmEneLE[i]=f1->GetParError(2);
    chi2perDOF  [i]=f1->GetChisquare()/f1->GetNDF();
    eCalibDEDXmc[i]->SetMaximum(1.05*eCalibDEDXmc[i]->GetMaximum());
    resolEneL[i]=sigmEneL[i]/meanEneL[i];
    double relErrorInSEoverEL = sigmEneLE[i]/sigmEneL[i];
    resolEneLE[i] = relErrorInSEoverEL*resolEneL[i];

    eCalibDEDXmc[i]->SetXTitle("(E_{rec}-E_{beam})/E_{beam} Leak(GeV)");
    sprintf(histoDraw,"Data %dGeV",BEAME[i]);
    leger.AddEntry(eCalibDEDXmc[i],histoDraw,"PL");
    sprintf(histoDraw,"L   %dGeV",BEAME[i]);
    leger.Draw();
    sprintf(histoDraw,"EcalibL%dGeV.png",BEAME[i]);
    c1->Update();
    //c1->Print(histoDraw);
    //cout << "Leakage Corrected Plots" << endl;
    cout << ">>>>>>>>> dEdX Calibration Plots" << endl;
    //getchar();
  }

  //*****************************
  //* Unsmear the beam spreads
  //*****************************
  for(int i=0; i<NENERGIES; i++){
    TLegend leger(0.18,0.70,0.50,0.88);
    leger.SetFillStyle(0);  
    leger.SetBorderSize(0);
    leger.SetHeader("CMS HGCAL MC");
    mbin=eResU[i]->GetMaximumBin();
    mpv =eResU[i]->GetBinCenter(mbin);
    //* Fit the MC:
    sigma = sqrt(Noise*Noise + Sampl*Sampl*BEAME[i] + Linear*Linear*BEAME[i]*BEAME[i]);
    eResU[i]->Fit("f1","","histo",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    mpv   = f1->GetParameter(1);
    sigma = f1->GetParameter(2);
    eResU[i]->Fit("f1","","samesL",mpv-nsigmasDown*sigma,mpv+nsigmasUp*sigma);
    eResU[i]->SetMaximum(1.05*eResU[i]->GetMaximum());
    eResU[i]->Draw("histo");
    f1->SetLineColor(kRed);
    f1->SetRange(mpv-4*sigma,mpv+4*sigma);
    f1->Draw("sames");
    eResU[i]->Draw("histosame");
    gStyle->SetOptFit(0);
    meanEneU[i]= f1->GetParameter(1);
    sigmEneU[i]= f1->GetParameter(2);
    meanEneUE[i]=f1->GetParError(1);
    sigmEneUE[i]=f1->GetParError(2);
    chi2perDOF  [i]=f1->GetChisquare()/f1->GetNDF();
    eResU[i]->SetMaximum(1.05*eResU[i]->GetMaximum());
    resolEneU[i]=sigmEneU[i];
    resolEneUE[i] = sigmEneUE[i];

    eResU[i]->SetXTitle("(E_{rec}-E_{beam})/E_{beam} (GeV)");
    sprintf(histoDraw,"Data %dGeV",BEAME[i]);
    leger.AddEntry(eResU[i],histoDraw,"PL");
    sprintf(histoDraw,"L   %dGeV",BEAME[i]);
    leger.Draw();
    sprintf(histoDraw,"EcalibU%dGeV.png",BEAME[i]);
    c1->Update();
    c1->Print(histoDraw);
    cout << "Unsmeared Plots" << endl;
    //getchar();
  }
  
  for(int i=0; i<NENERGIES; i++){
    cout << "ResolError:"<< sigmEneFE[i] << " sigma/E error: " << resolEneFE[i]<< endl;
  }


  //* Data vs MC resolutions


  //******************************
  //* Calculate Escales:
  //******************************
  for (int i=0; i<NENERGIES; i++) {

    EscaleF[i] = (meanEneF[i] - BEAMED[i])/BEAMED[i]; 
    EscaleFUp[i] = (meanEneFUp[i] - BEAMED[i])/BEAMED[i]; 
    EscaleL[i] = (meanEneL[i] - BEAMED[i])/BEAMED[i]; 
    EscaleU[i] = meanEneU[i]; 
    EscaleUE[i] =meanEneUE[i];
    //* F: Factor1
    double numerator =(meanEneF[i] - BEAMED[i]);
    double numerError =sqrt(meanEneFE[i]*meanEneFE[i]);
    double relErrNumer=numerError/numerator;
    double relErrDenom=0.0;
    EscaleFErr[i] =fabs(EscaleF[i])*sqrt(relErrNumer*relErrNumer+relErrDenom*relErrDenom);
    
    //* FUp: Factor1+Eup
    numerator =(meanEneFUp[i] - BEAMED[i]);
    numerError =sqrt(meanEneFUpE[i]*meanEneFUpE[i]);
    relErrNumer=numerError/numerator;
    relErrDenom=0.0;
    EscaleFUpErr[i] =fabs(EscaleFUp[i])*sqrt(relErrNumer*relErrNumer+relErrDenom*relErrDenom);
    
    //* L: Leakage Added
    numerator =(meanEneL[i] - BEAMED[i]);
    numerError =sqrt(meanEneLE[i]*meanEneLE[i]);
    relErrNumer=numerError/numerator;
    relErrDenom=BEAMEE[i]/BEAMED[i];
    EscaleLErr[i] =fabs(EscaleL[i])*sqrt(relErrNumer*relErrNumer+relErrDenom*relErrDenom);

    cout << "Escale : L= " << EscaleL[i] << " F= " << EscaleF[i] << endl;
  }

  //**************************************
  //* Resolution Graphs: G4 First
  //**************************************
  maxGraph= 0.015;
  minGraph=-0.015;

  gStyle->SetLabelFont(62);
  c1->SetGrid();
  
  //gStyle->SetOptFit(1);
  
  TLegend legres(0.30,0.70,0.95,0.90);
  legres.SetFillStyle(0);  
  legres.SetBorderSize(0);
  legres.SetHeader("HGCAL TB2018 Resolution");
  
  //* resolEneF: factor
  
  TGraphErrors* resolGraph_error = new TGraphErrors(NENERGIES,BEAMED,resolEneF,BinSIZE,resolEneFE);
  resolGraph_error->SetTitle(0);
  
  resolGraph_error->SetMarkerSize(1.2);
  resolGraph_error->SetMarkerStyle(22);
  //resolGraph_error->SetMaximum(0.06);
  resolGraph_error->SetMaximum(0.06);
  resolGraph_error->SetMinimum(0.00);
  
  //* Fit the SigmaE/E:
  //double frpar[2];
  //TF1 resFit("resFit",resolutionf1,7.0,260,2);
  //double frpar[3];
  TF1 resFit("resFit",resolutionf1,7.0,260,3);
  frpar[0] = 0.30;           // stoch term
  frpar[1] = 0.04;         // Constant term
  frpar[2] = 0.100;         // Noise term ~100MeV
  resFit.SetParameters(frpar);
  resFit.SetParName(0,"Stoch. Term");
  resFit.SetParName(1,"Const. Term");
  resFit.SetParName(2,"Noise  Term");
  //resFit.FixParameter(1,0.01);
  resFit.FixParameter(2,0.100);
  resFit.SetRange(5.0,260.);
  resFit.SetLineColor(1);
  resFit.SetLineWidth(0.5);
  gStyle->SetStatX(0.85);
  gStyle->SetStatY(0.95);
  resolGraph_error->Fit("resFit","RIM"); 
  stochTerm=resFit.GetParameter(0);
  constTerm=resFit.GetParameter(1);
  stochTermE=resFit.GetParError(0);
  constTermE=resFit.GetParError(1);
  chi2=resFit.GetChisquare();
  ndof=resFit.GetNDF();
  cout << "DT Fit result: stochTerm=" << stochTerm*100 << "+/-" << stochTermE*100 << "% constTerm:" 
       << constTerm*100  << "+/-" << constTermE*100 <<"%  chi2/ndof="<< chi2/ndof << endl;
  
  resolGraph_error->GetYaxis()->SetTitleOffset(1.3);
  resolGraph_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  resolGraph_error->GetYaxis()->SetTitle("Gaussian #sigma_{E}/<E>");
  resolGraph_error->Draw("AP");
  c1->Update();
  //cd_resol.Update();
  getchar();


  TGraphErrors* resolGraphL_error = new TGraphErrors(NENERGIES,BEAMED,resolEneL,BinSIZE,resolEneLE);
  resolGraphL_error->SetMarkerSize(1.2);
  resolGraphL_error->SetMarkerStyle(24);
  resolGraphL_error->SetMarkerColor(2);
  resolGraphL_error->Draw("Psame");

  TGraphErrors* resolGraphU_error = new TGraphErrors(NENERGIES,BEAMED,resolEneU,BinSIZE,resolEneUE);
  resolGraphU_error->SetMarkerSize(1.2);
  resolGraphU_error->SetMarkerStyle(25);
  resolGraphU_error->SetMarkerColor(4);
  resolGraphU_error->Draw("Psame");

  TGraphErrors* resolGraphFUp_error = new TGraphErrors(NENERGIES,BEAMED,resolEneFUp,BinSIZE,resolEneFUpE);
  resolGraphFUp_error->SetMarkerSize(1.2);
  resolGraphFUp_error->SetMarkerStyle(28);
  resolGraphFUp_error->SetMarkerColor(4);
  resolGraphFUp_error->Draw("Psame");


  //resolGraph_error->Draw("P");
  //legres.AddEntry(resolGraph_error,"MC: Visible Energy","PL");
  //legres.AddEntry(resolGraphFUp_error,"MC: Upstream corr","PL");
  //legres.AddEntry(resolGraphL_error,"MC: Leakage added","PL");
  //legres.AddEntry(resolGraphU_error,"MC: No smearing","PL");

  legres.AddEntry(resolGraph_error,"MC: SF corrected #times1.054","PL");
  legres.AddEntry(resolGraphFUp_error,"MC: SF + Beamline corrected #times1.054","PL");
  legres.AddEntry(resolGraphL_error,"MC: dEdX Calibration #times1.0","PL");
  legres.AddEntry(resolGraphU_error,"MC: SF + Beamline + Leakage #times1.0","PL");


  legres.Draw();
  c1->Update();
  c1->Print("ResolutionMC.png");
  getchar();
  

  //**************************************
  //* Linearity Graphs
  //**************************************
  maxGraph= 0.02;
  minGraph=-0.02;
  gStyle->SetLabelFont(62);
  TLegend leglin(0.15,0.68,0.70,0.92);
  leglin.SetFillStyle(0);  
  leglin.SetBorderSize(0);
  leglin.SetHeader("HGCAL TB2018 Linearity");
  TGraphErrors* linearityGraph_error = new TGraphErrors(NENERGIES,BEAMED,EscaleF,BinSIZE,EscaleFErr);
  linearityGraph_error->SetTitle(0);
  linearityGraph_error->SetMarkerSize(1.2);
  linearityGraph_error->SetMarkerStyle(22);
  linearityGraph_error->SetMarkerColor(2);
  linearityGraph_error->SetMaximum(maxGraph);
  linearityGraph_error->SetMinimum(minGraph);
  linearityGraph_error->Draw("AP");
  linearityGraph_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  linearityGraph_error->GetYaxis()->SetTitle("<(E-E_{beam})/E_{beam}>");
  linearityGraph_error->GetYaxis()->SetTitleOffset(1.4);
  linearityGraph_error->Draw("P");
  c1->Update();


  TGraphErrors* linearLGraph_error = new TGraphErrors(NENERGIES,BEAMED,EscaleL,BinSIZE,EscaleLErr);
  linearLGraph_error->SetTitle(0);
  linearLGraph_error->SetMarkerSize(1.2);
  linearLGraph_error->SetMarkerStyle(24);
  linearLGraph_error->SetMarkerColor(1);
  linearLGraph_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  linearLGraph_error->GetYaxis()->SetTitle("<(E-E_{beam})/E_{beam}>");
  linearLGraph_error->GetYaxis()->SetTitleOffset(1.3);
  linearLGraph_error->Draw("Psame");


  TGraphErrors* linearUGraph_error = new TGraphErrors(NENERGIES,BEAMED,EscaleU,BinSIZE,EscaleUE);
  linearUGraph_error->SetTitle(0);
  linearUGraph_error->SetMarkerSize(1.2);
  linearUGraph_error->SetMarkerStyle(25);
  linearUGraph_error->SetMarkerColor(4);
  linearUGraph_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  linearUGraph_error->GetYaxis()->SetTitle("<(E-E_{beam})/E_{beam}>");
  linearUGraph_error->GetYaxis()->SetTitleOffset(1.3);
  linearUGraph_error->Draw("Psame");

  TGraphErrors* linearFUpGraph_error = new TGraphErrors(NENERGIES,BEAMED,EscaleFUp,BinSIZE,EscaleFUpErr);
  linearFUpGraph_error->SetTitle(0);
  linearFUpGraph_error->SetMarkerSize(1.2);
  linearFUpGraph_error->SetMarkerStyle(28);
  linearFUpGraph_error->SetMarkerColor(4);
  linearFUpGraph_error->GetXaxis()->SetTitle("Beam Energy (GeV)");
  linearFUpGraph_error->GetYaxis()->SetTitle("<(E-E_{beam})/E_{beam}>");
  linearFUpGraph_error->GetYaxis()->SetTitleOffset(1.3);
  linearFUpGraph_error->Draw("Psame");


  //leglin.AddEntry(linearityGraph_error,"MC: Factor corrected","PL");
  //leglin.AddEntry(linearFUpGraph_error,"MC: Upstream corr","PL");
  //leglin.AddEntry(linearLGraph_error,"MC: Leakage added","PL");
  //leglin.AddEntry(linearUGraph_error,"MC: No smearing","PL");

  leglin.AddEntry(linearityGraph_error,"MC: SF corrected #times1.054","PL");
  leglin.AddEntry(linearFUpGraph_error,"MC: SF + Beamline corrected #times1.054","PL");
  leglin.AddEntry(linearLGraph_error,"MC: dEdX Calibration #times1.0","PL");
  leglin.AddEntry(linearUGraph_error,"MC: SF + Beamline + Leakage #times1.0","PL");



  leglin.Draw();
  c1->Update();
  c1->Print("LinearitySFmc.png");
  getchar();





}
