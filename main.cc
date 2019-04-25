#include "makePlots.h"
#include <fstream>
#include <iostream>
#include "TGraph.h"
#include "TH1.h"
#include "makePlots.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include <utility>

vector<float> E_minus_Ebeam_dev_Ebeam( vector<float> Parameters, float True_Beam_energy )
{
vector<float> E_minus_Ebeam_dev_Ebeam;
cout << "===================Plot the (E-E_beam)/(E_beam)===================" << endl;
E_minus_Ebeam_dev_Ebeam.push_back( ( (Parameters[0])-(True_Beam_energy) )/(True_Beam_energy)   );
cout << "( (Parameters[0])-(True_Beam_energy) )/(True_Beam_energy) :" << ( (Parameters[0])-(True_Beam_energy) )/(True_Beam_energy)  << endl;

return(E_minus_Ebeam_dev_Ebeam);
}
//=================================================//

vector<float> Energy_ratio_Data_MC(vector<float> Data_Parameters, vector<float> MC_Parameters)
{
vector<float> Ratio_parameters;
Ratio_parameters.push_back((Data_Parameters[0])/(MC_Parameters[0]));
cout << "(f2->GetParameter(1))/(f1->GetParameter(1))" << ((Data_Parameters[0])/(MC_Parameters[0]) << endl;
Ratio_parameters.push_back( ((Data_Parameters[0])/(MC_Parameters[0]))*sqrt( ((Data_Parameters[2])/(Data_Parameters[0]))*((Data_Parameters[2])/(Data_Parameters[0]))+ ((MC_Parameters[2])/(MC_Parameters[0]))*((MC_Parameters[2])/(MC_Parameters[0]))));
cout << "((Data_Parameters[0])/(MC_Parameters[0]))*sqrt( ((Data_Parameters[2])/(Data_Parameters[0]))*((Data_Parameters[2])/(Data_Parameters[0]))+ ((MC_Parameters[2])/(MC_Parameters[0]))*((MC_Parameters[2])/(MC_Parameters[0]))):" << ((Data_Parameters[0])/(MC_Parameters[0]))*sqrt( ((Data_Parameters[2])/(Data_Parameters[0]))*((Data_Parameters[2])/(Data_Parameters[0]))+ ((MC_Parameters[2])/(MC_Parameters[0]))*((MC_Parameters[2])/(MC_Parameters[0]))) << endl;
return(Ratio_parameters);
}

vector<float> Two_fits(vector<TH1F*> Fit_His, int Data_type)
{
//======Confirm the data type=====//
float Extra;
if(Data_type==1)
{cout << "Two_fit_for_data_is_coming" << endl;
    Extra=0.05;
}
if(Data_type==0)
{cout << "Two_fit_for_MC_is_coming" << endl;
    Extra=0;
}
//===============================//
int maxBin=0; double maxpv=0; double sigma=0;
float SigmaDown=1; float SigmaUp=2.5;
double Noise=0.2; //Pad noise, sqrt(N:Number of pads in cluster)xsigma_pad
double Sampl=0.30;//Stochastic, depend on the sampling and structure
double Linear=0.01;// Constant term, all others unknown can contribute in this one.
//============In this study, we try to get the smaller Linear(Dominant) in the high energy particle===========//
vector<float> Store_numbers;
//=================================================//
TF1 *f1 = new TF1("f1","gaus");
maxBin=Fit_His[0]->GetMaximumBin();
//-----First fit max point and sigma------------//
maxpv = Fit_His[0]->GetBinCenter(maxBin);
sigma=sqrt(Noise*Noise+Sampl*Sampl*beam_energy_number_float[i]+Linear*Linear*beam_energy_number_float[i]*beam_energy_number_float[i]);//Theory
Fit_His[0]->Draw("histo");
Fit_His[0]->Fit("f1","","histo",maxpv-SigmaDown*sigma,maxpv+SigmaUp*sigma);
//----After first fit, get the max point and sigma----//
maxpv = f1->GetParameter(1);
sigma = f1->GetParameter(2);
Fit_His[0]->Fit("f1","","samesL",maxpv-SigmaDown*sigma,maxpv+SigmaUp*sigma);
f1->SetRange(maxpv-SigmaDown*sigma,maxpv+SigmaUp*sigma);
f1->Draw("Sames");
cout << "Down=>" <<maxpv-SigmaDown*sigma << "Upper=>"<<maxpv+SigmaUp*sigma << endl;
//-------Get the parameters that will be used to study-----//
Store_numbers.push_back(f1->GetParameter(1));
Store_numbers.push_back(f1->GetParameter(2));
Store_numbers.push_back(f1->GetParError(1));
Store_numbers.push_back(f1->GetParError(2));
Store_numbers.push_back(f1->GetChisquare()/f1->GetNDF());
Store_numbers.push_back((f1->GetParameter(2)/f1->GetParameter(1)));
Store_numbers.push_back(((f1->GetParameter(2))/(f1->GetParameter(1)))*sqrt(((f1->GetParError(1))/(f1->GetParameter(1)))*((f1->GetParError(1))/(f1->GetParameter(1)))+((f1->GetParError(2))/(f1->GetParameter(2)))*((f1->GetParError(2))/(f1->GetParameter(2)))));
cout << "f1->GetParameter(1):"<< f1->GetParameter(1) << endl;
cout << "f1->GetParameter(2):"<< f1->GetParameter(2) << endl;
cout << "f1->GetParError(1):" << f1->GetParError(1) << endl;
cout << "f1->GetParError(2):" << f1->GetParError(2) << endl;
cout << "f1->GetChisquare()/f1->GetNDF()" << f1->GetChisquare()/f1->GetNDF() << endl;
cout << "Width_Div_Mean:" << f1->GetParameter(2)/f1->GetParameter(1) << endl;
cout << "Width_Div_Mean_Error:" << ((f1->GetParameter(2))/(f1->GetParameter(1)))*sqrt(((f1->GetParError(1))/(f1->GetParameter(1)))*((f1->GetParError(1))/(f1->GetParameter(1)))+((f1->GetParError(2))/(f1->GetParameter(2)))*((f1->GetParError(2))/(f1->GetParameter(2)))+(Extra)*(Extra)) << endl;
//===================================================//
return(Store_numbers);
}
                                                          
int main(){
TApplication *app = new TApplication("app",0,0);
bool Is_Data;
//===========
vector<float> beam_energy_number_float={20.0,30.0,49.99,79.93,99.83,149.14,197.32,243.61,287.18};
vector<int> beam_energy_number={20,30,50,80,100,150,200,250,300};
//vector<int> Recommened_run_old={1015,1008,961,972,990,932,996,653,435};
vector<int> Recommened_run_new={1015,1008,961,972,990,932,664,653,435};
//==========Mean========//
vector<float> DataE_Mean;
vector<float> McE_Mean;
vector<float> DataE_MeanError;
vector<float> McE_MeanError;
//==========Mean Width========//
vector<float> DataE_width;
vector<float> McE_width;
vector<float> DataE_widthError;
vector<float> McE_widthError;
//==========MeanError==========//
vector<float> Data_MeanDivError;
vector<float> MC_MeanDivError;
vector<float> Data_MeanDivError_Error;
vector<float> MC_MeanDivError_Error;
//==========Chi2test_store========//
vector<float> Chi2test_data;
vector<float> Chi2test_MC; 
vector<float> Data_X_no_error={0,0,0,0,0,0,0,0,0};
vector<float> MC_X_no_error={0,0,0,0,0,0,0,0,0};;
vector<float> Ratio_Energy;
vector<float> Ratio_Energy_Error;
//===============================//
vector<float> dEdXMEVperMIP={
  10.058,//Layer 1
  9.6,9.6,9.6,9.6,9.6,9.6,9.6,9.6,9.6,9.6,9.6,9.6,9.6,//Layers 2-14
  11.109,11.109,//L 15-16
  9.6,9.6,//
  11.109,11.109,//L 19-20
  9.6,9.6,//L 21-22
  10.354,10.354,//L 23-24
  9.6,9.6,9.6,//L 25-27
  6.595
};
vector<float> E_minus_Ebeam_dev_Ebeam_Data;
vector<float> E_minus_Ebeam_dev_Ebeam_Data_Error;
vector<float> E_minus_Ebeam_dev_Ebeam_MC;
vector<float> E_minus_Ebeam_dev_Ebeam_MC_Error;

vector<float> b_x_middle;
vector<float> b_x_error;
vector<float> Mean_divide_beamE;
vector<float> Mean_Errors_divide_beamE;
// cout << "======Start to run Data part=======" << endl;
 //==================
//=========root file created======//
char title[100];
sprintf(title,"Resolution_fit/dEdX_resolution_study_add_cut_bx_by_optimized_Final_finner_bin_v13.root");
TFile outf(title,"recreate");       

for(int i = 0 ; i < 9 ; i++)
{
    vector<float> Data_Fit_Par;
    vector<float> MC_Fit_Par;
  int config;
  if(beam_energy_number[i]< 200)config=2;
  if(beam_energy_number[i]>=200)config=1;
  cout << "beam_energy_number[i]" << beam_energy_number[i] << endl;
  cout << "config" << config << endl;
  cout << Form("/eos/user/c/chyeh/Data_v13_config%i/Run%i_%iGeV_Ele_v13.root",config,Recommened_run_new[i],beam_energy_number[i]) << endl;
  makePlots *Data;
  TChain *chain = new TChain("hits");
  TChain *chain2 = new TChain("impactPoints");
  TChain *chain3 = new TChain("rechit_var");
  string filename=(Form("/eos/user/c/chyeh/Data_v13_config%i/Run%i_%iGeV_Ele_v13.root",config,Recommened_run_new[i],beam_energy_number[i]));
  chain->Add(filename.c_str());
  chain2->Add(filename.c_str());
  chain3->Add(filename.c_str());
  Data = new makePlots(chain,chain2,chain3,filename);
  Data->Is_Data = 1 ;
  vector<TH1F*> h_Data_Histo;
  h_Data_Histo = Data->GetHistoE(1,1,i);
  Data_Fit_Par = Two_fits(h_Data_Histo,1);
//==========Get MC totalE Histo=======//
  makePlots *MC;
  TChain *chain4 = new TChain("hits");
  TChain *chain5 = new TChain("impactPoints");
  TChain *chain6 = new TChain("rechit_var");
  string filename1=(Form("/eos/user/c/chyeh/MC_v1_ntuple/MC_%iGeV_Ele_ZM800.root",beam_energy_number[i]));
  chain4->Add(filename1.c_str());
  chain5->Add(filename1.c_str());
  chain6->Add(filename1.c_str());
  MC = new makePlots(chain4,chain5,chain6,filename1);
  MC->Is_Data = 0 ;
  vector<TH1F*> h_MC_Histo;
  h_MC_Histo = MC->GetHistoE(1,1,i);
  MC_Fit_Par = Two_fits(h_MC_Histo,0);
    
  cout << "Data_Fit_Par[0]/MC_Fit_Par[0]:" << Data_Fit_Par[0]/MC_Fit_Par[0] << endl;
/*
  //=================================//
  DataE_Mean.push_back();
  McE_Mean.push_back();
  DataE_MeanError.push_back();
  McE_MeanError.push_back();
    //==========Mean Width========//
  DataE_width.push_back();
  McE_width.push_back();
  DataE_widthError.push_back();
  McE_widthError.push_back();
    //==========MeanError==========//
  Data_MeanDivError.push_back();
  MC_MeanDivError.push_back();
  Data_MeanDivError_Error.push_back();
  MC_MeanDivError_Error.push_back();
  //===============================//
  E_minus_Ebeam_dev_Ebeam_Data.push_back();
  E_minus_Ebeam_dev_Ebeam_Data_Error.push_back();
  E_minus_Ebeam_dev_Ebeam_MC.push_back();
  E_minus_Ebeam_dev_Ebeam_MC_Error.push_back();
 */
  //===============================//
  f1->Clear();
  f2->Clear();
  chain ->Clear();
  chain2->Clear();
  chain3->Clear();
  chain4->Clear();
  chain5->Clear();  
  chain6->Clear();
filename.clear();
filename1.clear();
}
    /*
    TGraphErrors *h_resolution_fit_Data  = new TGraphErrors(9,&beam_energy_number_float[0],&Data_MeanDivError[0],&Data_X_no_error[0],&Data_MeanDivError_Error[0]);
    TGraphErrors *h_resolution_fit_MC= new TGraphErrors(9,&beam_energy_number_float[0],&MC_MeanDivError[0]  ,&MC_X_no_error[0]  ,&MC_MeanDivError_Error[0]);
    TGraphErrors *h_energy_ratio_Data_MC = new TGraphErrors(9,&beam_energy_number_float[0],&Ratio_Energy[0], &MC_X_no_error[0], &Ratio_Energy_Error[0]);

    TGraphErrors *h_energy_E_minus_Ebeam_dev_Ebeam_Data = new TGraphErrors(9,&beam_energy_number_float[0],&E_minus_Ebeam_dev_Ebeam_Data[0], &MC_X_no_error[0], &E_minus_Ebeam_dev_Ebeam_Data_Error[0]);
       
    TGraphErrors *h_energy_E_minus_Ebeam_dev_Ebeam_MC =   new TGraphErrors(9,&beam_energy_number_float[0],&E_minus_Ebeam_dev_Ebeam_MC[0], &MC_X_no_error[0], &E_minus_Ebeam_dev_Ebeam_MC_Error[0]);

    h_resolution_fit_MC   ->Write("SigmaE_dev_E_MC");
    h_resolution_fit_Data ->Write("SigmaE_dev_E_data");
    h_energy_ratio_Data_MC->Write("h_energy_ratio_Data_MC");
    h_energy_E_minus_Ebeam_dev_Ebeam_Data->Write("E_minus_Ebeam_dev_Ebeam_Data");
    h_energy_E_minus_Ebeam_dev_Ebeam_MC->Write("E_minus_Ebeam_dev_Ebeam_MC");
     */
  
    outf.Write();
    outf.Close();
  	
  return(0);

}
