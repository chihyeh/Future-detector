#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <TString.h>
#include <TH1D.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TProfile.h>
#include <stdlib.h>


using namespace std;
const float removal=0.1;

float myDeltaR(float eta1, float eta2, float phi1, float phi2)
{
  float deta = eta1-eta2;
  float dphi = phi1-phi2;
  if(dphi >= TMath::Pi())
    dphi = dphi-TMath::Pi()*2;
  if(dphi < -TMath::Pi())
    dphi = dphi+TMath::Pi()*2;
  float dr = sqrt(deta*deta+dphi*dphi);
  return dr;
}

int *cut_ww(int files, int energy)
{
    //This one is the 160 bins histogram, range is 800. ==>Although it doesn't matter at the boundary condition, because we don't use that.
    TFile* f1 = TFile::Open(Form("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev%dmumu_pythia6_zprime%dtev_wwrfull%03d_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_800_no_UOF.root",energy,energy,files));
    TH1F *h1;
    h1=(TH1F*) f1->Get("h_mass_mmdt");
    float a=h1->Integral();
    int M=h1->GetMaximumBin();
    int L=M;
    int R=M;
    float ratio_BinContent_1=0;
    float ratio_BinContent_2=0;
    for(int Q=0 ; Q<161 ; Q++)
    {
        cout <<  "Run number: " << Q << endl;
        cout <<  "===============================================" <<endl;
        cout <<  "signal total: " << a << endl;
        cout <<  "signal: " << h1->Integral(L,R) << endl;
        cout <<  "Next left: " << h1->GetBinContent(L-1) << endl;
        cout <<  "Next right " << h1->GetBinContent(R+1) << endl;
        cout <<  "===============================================" << endl;
        cout <<  "next-step" << endl;
    //================================================================================Define the zero bin first
        if(R<=158)
        {
            if(h1->Integral(R+2,160)!=0)
            {
                h1->GetXaxis()->SetRange(R+2,160);
                ratio_BinContent_2=h1->GetMean();
                h1->GetXaxis()->SetRange(L,R);
                cout <<  "Right: this bin is zero, average it" << endl;
            }
            if(h1->Integral(R+2,160)==0)
            {
                ratio_BinContent_2=0;
                cout <<  "Right: this bin is zero, after:no signal" << endl;
            }
        }
        if(R==159)
        {
            ratio_BinContent_2=0;
        }
        //================================================================================Define the zero bin first
        if(L>=3)
        {
            if(h1->Integral(1,L-2)!=0)
            {
                h1->GetXaxis()->SetRange(1,L-2);
                ratio_BinContent_1=h1->GetMean();
                h1->GetXaxis()->SetRange(L,R);
                cout <<  "Left: this bin is zero, before:avergae it" << endl;
            }
            if(h1->Integral(1,L-2)==0)
            {
                ratio_BinContent_1=0;
                cout <<  "Left: this bin is zero, before:no signal" << endl;
            }
        }
        if(L==2)
        {
            ratio_BinContent_1=0;
        }
        //---------------------------
        
        //---------------------------
        if(L==1)
        {
            cout << "YA14" << endl;
            cout << "Now we have "<< h1->Integral(L,R+1) << "Total" << a << endl;
            L=L;
            R=R+1;
            cout <<  "Left bin:" << L << endl;
            cout <<  "Right bin:" << R << endl;
            cout <<  "----1" << endl;
            if(h1->Integral(L,R)>a/2)
            {
                cout <<  "More than half :" << h1->Integral(L,R) << endl;
                cout <<  "==========" << endl;
                break;
            }
        }
        else if(R==160)
        {
            cout << "YA15" << endl;
            cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
            L=L-1;
            R=R;
            cout <<  "Left bin:" << L << endl;
            cout <<  "Right bin:" << R << endl;
            cout <<  "----1" << endl;
            if(h1->Integral(L,R)>a/2)
            {
                cout <<  "More than half :" << h1->Integral(L,R) << endl;
                cout <<  "==========" << endl;
                break;
            }
        }
//--------------------------Use the Method 2--------------------------------//
        //The first condition-->Left>right
        else if(h1->GetBinContent(L-1)>h1->GetBinContent(R+1))
        {
            if(h1->GetBinContent(R+1)==0)
            {
                if(h1->GetBinContent(L-1)>ratio_BinContent_2)
                {
                    cout << "YA1" << endl;
                    cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                    L=L-1;
                    R=R;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----1" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                else if(h1->GetBinContent(L-1)<ratio_BinContent_2)
                {
                    cout <<  "YA2" << endl;
                    cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                    L=L;
                    R=R+1;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----2" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                else if(h1->GetBinContent(L-1)==ratio_BinContent_2)
                {
                    cout <<  "YA3" << endl;
                    int Random=rand()%2;
                    if(Random==0)
                    {
                        cout <<  "YA3_1" << endl;
                        cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                        L=L-1;
                        R=R;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----3" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                    
                    else if(Random==1)
                    {
                        cout <<  "YA3_2" << endl;
                        cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                        L=L;
                        R=R+1;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----3" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                }
            }
            else
            {
                cout << "YA4" << endl;
                cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                L=L-1;
                R=R;
                cout <<  "Left bin:" << L << endl;
                cout <<  "Right bin:" << R << endl;
                cout <<  "----4" << endl;
                if(h1->Integral(L,R)>a/2)
                {
                    cout <<  "More than half :" << h1->Integral(L,R) << endl;
                    cout <<  "==========" << endl;
                    break;
                }
            }
        }
        
        //The second condition-->Left<right
        else if(h1->GetBinContent(L-1)<h1->GetBinContent(R+1))
        {
            if(h1->GetBinContent(L-1)==0)
            {
                if(h1->GetBinContent(R+1)>ratio_BinContent_1)
                {
                    cout << "YA5" << endl;
                    cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                    L=L;
                    R=R+1;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----5" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
        
                else if(h1->GetBinContent(R+1)<ratio_BinContent_1)
                {
                    cout << "YA6" << endl;
                    cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                    L=L-1;
                    R=R;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----6" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                else if(h1->GetBinContent(R+1)==ratio_BinContent_1)
                {
                    cout <<  "YA7" << endl;
                    int Random=rand()%2;
                    if(Random==0)
                    {
                        cout <<  "YA7_1" << endl;
                        cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                        L=L-1;
                        R=R;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----7" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                    
                    else if(Random==1)
                    {
                        cout <<  "YA7_2" << endl;
                        cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                        L=L;
                        R=R+1;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----7" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                }
            }
//---------------------------
            else
            {
                cout <<  "YA8" << endl;
                cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                L=L;
                R=R+1;
                cout <<  "Left bin:" << L << endl;
                cout <<  "Right bin:" << R << endl;
                cout <<  "----8" << endl;
                if(h1->Integral(L,R)>a/2)
                {
                    cout <<  "More than half :" << h1->Integral(L,R) << endl;
                    cout <<  "==========" << endl;
                    break;
                }
            }
        }
        //The Third condition-->Left==right
        else if(h1->GetBinContent(L-1)==h1->GetBinContent(R+1))
        {
            if(h1->GetBinContent(L-1)==0 && h1->GetBinContent(R+1)==0)
            {
                if(ratio_BinContent_2>ratio_BinContent_1)
                {
                    cout <<  "YA9" << endl;
                    cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                    L=L;
                    R=R+1;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----9" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                else if(ratio_BinContent_2<ratio_BinContent_1)
                {
                    cout <<  "YA10" << endl;
                    cout <<  "Now we have" << h1->Integral(L-1,R) << "Total" << a << endl;
                    L=L-1;
                    R=R;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----10" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
        
                else if(ratio_BinContent_2==ratio_BinContent_1)
                {
                    cout <<  "YA11" << endl;
                    int Random=rand()%2;
                    if(Random==0)
                    {
                        cout <<  "YA11_1" << endl;
                        cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                        L=L-1;
                        R=R;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----11" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                    
                    else if(Random==1)
                    {
                        cout <<  "YA11_2" << endl;
                        cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                        L=L;
                        R=R+1;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----11" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                }
            }
            
            else
            {
                
                cout <<  "YA12_1" << endl;
                int Random=rand()%2;
                if(Random==0)
                {
                    cout <<  "YA12_1" << endl;
                    cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                    L=L-1;
                    R=R;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----12" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                
                else if(Random==1)
                {
                    cout <<  "YA12_2" << endl;
                    cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                    L=L;
                    R=R+1;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----12" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
            }
        }
    }
    int static cut[2]={L,R};
    int *cut_use=cut;
    delete h1;
    delete f1;
    cout << "L: " << L << "R: " << R << endl;
    return(cut_use);
}
    //------------------------------------------


//This one function is same as before, just the ttbar cut (files name are different//
int *cut_tt(int files, int energy)
{
    TFile* f1 = TFile::Open(Form("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev%dmumu_pythia6_zprime%dtev_ttbarrfull%03d_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200_no_UOF.root",energy,energy,files));
    TH1F *h1;
    h1=(TH1F*) f1->Get("h_mass_mmdt");
    float a=h1->Integral();
    int M=h1->GetMaximumBin();
    int L=M;
    int R=M;
    float ratio_BinContent_1=0;
    float ratio_BinContent_2=0;
    for( int Q=0 ; Q<241 ; Q++)
    {
        cout <<  "Run number: " << Q << endl;
        cout <<  "===============================================" <<endl;
        cout <<  "signal total: " << a << endl;
        cout <<  "signal: " << h1->Integral(L,R) << endl;
        cout <<  "Next left: " << h1->GetBinContent(L-1) << endl;
        cout <<  "Next right " << h1->GetBinContent(R+1) << endl;
        cout <<  "===============================================" << endl;
        cout <<  "next-step" << endl;
        //================================================================================Define the zero bin first
        if(R<=238)
        {
            if(h1->Integral(R+2,240)!=0)
            {
                h1->GetXaxis()->SetRange(R+2,240);
                ratio_BinContent_2=h1->GetMean();
                h1->GetXaxis()->SetRange(L,R);
                cout <<  "Right: this bin is zero, average it" << endl;
            }
            if(h1->Integral(R+2,240)==0)
            {
                ratio_BinContent_2=0;
                cout <<  "Right: this bin is zero, after:no signal" << endl;
            }
        }
        if(R==239)
        {
            ratio_BinContent_2=0;
        }
        //================================================================================Define the zero bin first
        if(L>=3)
        {
            if(h1->Integral(1,L-2)!=0)
            {
                h1->GetXaxis()->SetRange(1,L-2);
                ratio_BinContent_1=h1->GetMean();
                h1->GetXaxis()->SetRange(L,R);
                cout <<  "Left: this bin is zero, before:avergae it" << endl;
            }
            if(h1->Integral(1,L-2)==0)
            {
                ratio_BinContent_1=0;
                cout <<  "Left: this bin is zero, before:no signal" << endl;
            }
        }
        if(L==2)
        {
            ratio_BinContent_1=0;
        }
        //---------------------------
        
        //---------------------------
        if(L==1)
        {
            cout << "YA14" << endl;
            cout << "Now we have "<< h1->Integral(L,R+1) << "Total" << a << endl;
            L=L;
            R=R+1;
            cout <<  "Left bin:" << L << endl;
            cout <<  "Right bin:" << R << endl;
            cout <<  "----1" << endl;
            if(h1->Integral(L,R)>a/2)
            {
                cout <<  "More than half :" << h1->Integral(L,R) << endl;
                cout <<  "==========" << endl;
                break;
            }
        }
        else if(R==240)
        {
            cout << "YA15" << endl;
            cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
            L=L-1;
            R=R;
            cout <<  "Left bin:" << L << endl;
            cout <<  "Right bin:" << R << endl;
            cout <<  "----1" << endl;
            if(h1->Integral(L,R)>a/2)
            {
                cout <<  "More than half :" << h1->Integral(L,R) << endl;
                cout <<  "==========" << endl;
                break;
            }
        }
        else if(h1->GetBinContent(L-1)>h1->GetBinContent(R+1))
        {
            if(h1->GetBinContent(R+1)==0)
            {
                if(h1->GetBinContent(L-1)>ratio_BinContent_2)
                {
                    cout << "YA1" << endl;
                    cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                    L=L-1;
                    R=R;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----1" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                else if(h1->GetBinContent(L-1)<ratio_BinContent_2)
                {
                    cout <<  "YA2" << endl;
                    cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                    L=L;
                    R=R+1;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----2" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                else if(h1->GetBinContent(L-1)==ratio_BinContent_2)
                {
                    cout <<  "YA3" << endl;
                    int Random=rand()%2;
                    if(Random==0)
                    {
                        cout <<  "YA3_1" << endl;
                        cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                        L=L-1;
                        R=R;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----3" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                    
                    else if(Random==1)
                    {
                        cout <<  "YA3_2" << endl;
                        cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                        L=L;
                        R=R+1;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----3" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                }
            }
            //--------------------------------
            else
            {
                cout << "YA4" << endl;
                cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                L=L-1;
                R=R;
                cout <<  "Left bin:" << L << endl;
                cout <<  "Right bin:" << R << endl;
                cout <<  "----4" << endl;
                if(h1->Integral(L,R)>a/2)
                {
                    cout <<  "More than half :" << h1->Integral(L,R) << endl;
                    cout <<  "==========" << endl;
                    break;
                }
            }
        }
        
        //---------------------------
        else if(h1->GetBinContent(L-1)<h1->GetBinContent(R+1))
        {
            if(h1->GetBinContent(L-1)==0)
            {
                if(h1->GetBinContent(R+1)>ratio_BinContent_1)
                {
                    cout << "YA5" << endl;
                    cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                    L=L;
                    R=R+1;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----5" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                
                else if(h1->GetBinContent(R+1)<ratio_BinContent_1)
                {
                    cout << "YA6" << endl;
                    cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                    L=L-1;
                    R=R;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----6" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                else if(h1->GetBinContent(R+1)==ratio_BinContent_1)
                {
                    cout <<  "YA7" << endl;
                    int Random=rand()%2;
                    if(Random==0)
                    {
                        cout <<  "YA7_1" << endl;
                        cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                        L=L-1;
                        R=R;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----7" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                    
                    else if(Random==1)
                    {
                        cout <<  "YA7_2" << endl;
                        cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                        L=L;
                        R=R+1;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----7" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                }
            }
            //---------------------------
            else
            {
                cout <<  "YA8" << endl;
                cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                L=L;
                R=R+1;
                cout <<  "Left bin:" << L << endl;
                cout <<  "Right bin:" << R << endl;
                cout <<  "----8" << endl;
                if(h1->Integral(L,R)>a/2)
                {
                    cout <<  "More than half :" << h1->Integral(L,R) << endl;
                    cout <<  "==========" << endl;
                    break;
                }
            }
        }
        //-----------------------------------
        else if(h1->GetBinContent(L-1)==h1->GetBinContent(R+1))
        {
            if(h1->GetBinContent(L-1)==0 && h1->GetBinContent(R+1)==0)
            {
                if(ratio_BinContent_2>ratio_BinContent_1)
                {
                    cout <<  "YA9" << endl;
                    cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                    L=L;
                    R=R+1;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----9" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                else if(ratio_BinContent_2<ratio_BinContent_1)
                {
                    cout <<  "YA10" << endl;
                    cout <<  "Now we have" << h1->Integral(L-1,R) << "Total" << a << endl;
                    L=L-1;
                    R=R;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----10" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                
                else if(ratio_BinContent_2==ratio_BinContent_1)
                {
                    cout <<  "YA11" << endl;
                    int Random=rand()%2;
                    if(Random==0)
                    {
                        cout <<  "YA11_1" << endl;
                        cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                        L=L-1;
                        R=R;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----11" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                    
                    else if(Random==1)
                    {
                        cout <<  "YA11_2" << endl;
                        cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                        L=L;
                        R=R+1;
                        cout <<  "Left bin:" << L << endl;
                        cout <<  "Right bin:" << R << endl;
                        cout <<  "----11" << endl;
                        if(h1->Integral(L,R)>a/2)
                        {
                            cout <<  "More than half :" << h1->Integral(L,R) << endl;
                            cout <<  "==========" << endl;
                            break;
                        }
                    }
                }
            }
            
            else
            {
                
                cout <<  "YA12_1" << endl;
                int Random=rand()%2;
                if(Random==0)
                {
                    cout <<  "YA12_1" << endl;
                    cout << "Now we have "<< h1->Integral(L-1,R) << "Total" << a << endl;
                    L=L-1;
                    R=R;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----12" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
                
                else if(Random==1)
                {
                    cout <<  "YA12_2" << endl;
                    cout <<  "Now we have" << h1->Integral(L,R+1) << "Total" << a << endl;
                    L=L;
                    R=R+1;
                    cout <<  "Left bin:" << L << endl;
                    cout <<  "Right bin:" << R << endl;
                    cout <<  "----12" << endl;
                    if(h1->Integral(L,R)>a/2)
                    {
                        cout <<  "More than half :" << h1->Integral(L,R) << endl;
                        cout <<  "==========" << endl;
                        break;
                    }
                }
            }
        }
    }
    int static cut[2]={L,R};
    int *cut_use=cut;
    delete h1;
    delete f1;
    cout << "L: " << L<< "R: "<<R << endl;
    return(cut_use);
}

/*float cluster_mass_cut(int subjet , int energy, int signal, int Dir, float radius=0.4, int mode=0)
{
    int Dirvec[3]={9,10,12};
    int *Dirvec_use=Dirvec;
    int Enevec[4]={5,10,20,40};
    int *Enevec_use=Enevec;
    char const *Signal_use[] = {"ww", "ttbar","qq"};
    
    cout << "Go into the loop" << endl;
    string inputDir= Form("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev%dmumu_pythia6_zprime%dtev_%srfull%03d_onlyhadronic",Enevec_use[energy],Enevec_use[energy],Signal_use[signal],Dirvec_use[Dir]);
    string decversion;
    if(inputDir.find("rfull009")!=std::string::npos)decversion="rfull009";
    else if(inputDir.find("rfull012")!=std::string::npos)decversion="rfull012";
    else if(inputDir.find("rfull010")!=std::string::npos)decversion="rfull010";
    
    std::string treeName = "tcalo";
    std::string title = mode==0? Form("Anti-kt jet //Delta R = %.1f",radius):
    Form("Simple jet //Delta R = %.1f",radius);
    
    
    
    const std::string histonames[]=
    {
        //"mass_trim",
        "mass_mmdt",
        //"mass_prun",
        //"mass_sdb2",
        //"mass_sdm1",
        //"tau21_b1",
        //"c2_b1",
        //"d2_b1",
        //"n2_b1",
        //"tau21_b1_mmdt",
        //"c2_b1_mmdt",
        //"d2_b1_mmdt",
        //"tau32_b1"
    };
    
    
    
    //  int ntemp_histos=sizeof(histonames)/sizeof(histonames[0]);
    const int nhistos=1;//ntemp_histos;
    
    std::cout << "Total number of histograms is " << nhistos << std::endl;
    const float xmax[nhistos]={1200};
    
    TH1F* h_sub[nhistos];
    const float xmin=0;
    const int nbins=100;
    for(int ih=0; ih < nhistos; ih++)
    {
    // [(xmax[ih]-xmin)/nbins]*L or R to find the mass_cut value
    h_sub[ih] = new TH1F(Form("h_%s",histonames[ih].data()), histonames[ih].data(), nbins,xmin,xmax[ih]);
    float binwidth = (xmax[ih]-xmin)/(float)nbins;
    h_sub[ih]->SetXTitle(histonames[ih].data());
    h_sub[ih]->SetYTitle(Form("Number of jets per %.2f",binwidth));
    }
    string inputFile = inputDir + "/radius" + Form("%0.1f",radius)+ "_response_e2.root";
    cout << "opening " << inputFile.data() << endl;
    TreeReader genTree(inputFile.data(),"tGEN_nonu");
    TreeReader caloTree(inputFile.data(),treeName.data());
    
    
    for(Long64_t jEntry=0; jEntry< genTree.GetEntriesFast() ;jEntry++){
        
        genTree.GetEntry(jEntry);
        caloTree.GetEntry(jEntry);
        
        Float_t*  gen_je = genTree.GetPtrFloat("je");
        Float_t*  gen_jeta = genTree.GetPtrFloat("jeta");
        Float_t*  gen_jphi = genTree.GetPtrFloat("jphi");
        Int_t     gen_njets = genTree.GetInt("njets");
        
        Float_t*  calo_je = caloTree.GetPtrFloat("je");
        Float_t*  calo_jeta = caloTree.GetPtrFloat("jeta");
        Float_t*  calo_jphi = caloTree.GetPtrFloat("jphi");
        Int_t     calo_njets    = caloTree.GetInt("njets");
        
        Float_t*  sub[nhistos];
        
        for(int ih=0; ih < nhistos; ih++)
        {
            sub[ih] = caloTree.GetPtrFloat(Form("j_%s",histonames[ih].data()));
        }
        
        if(fabs(calo_jeta[subjet])>1.1)continue;
            
            int findGenMatch=-1;
            for(int k=0; k< gen_njets; k++){
                
                
                float dr = myDeltaR(gen_jeta[k], calo_jeta[subjet],
                                    gen_jphi[k], calo_jphi[subjet]);
                
                if(dr<0.1)
                {
                    findGenMatch=k;
                    break;
                }
            }
        if(findGenMatch<0)continue;
        cout << " genloop" << endl;
        cout << sub[0][subjet] << endl;
        return(sub[0][subjet]);

    }

}*/

void jetSubstructure(float radius=0.4, int mode=0)
{
    int Dirvec[3]={9,10,12};
    int *Dirvec_use=Dirvec;
    int Enevec[4]={5,10,20,40};
    int *Enevec_use=Enevec;
    char const *Signal_use[] = {"ww", "ttbar","qq",};
    const int nhistos=3;//ntemp_histos;
    const int nhistos_cut=1;

for ( int signal=0 ; signal <3 ; signal++)
{
    for ( int Dir=0 ; Dir <3 ; Dir++)
    {
        for(int energy=0 ; energy < 4 ; energy++)
        {
            int *Cut_ww=0;
            int *Cut_tt=0;
            cout << "===========================================" << endl;
            cout << "signal:" << Signal_use[signal] << endl;
            cout << "files:" << Dirvec_use[Dir] << endl;
            cout << "energy:" << Enevec_use[energy] << endl;
            cout << "===========================================" << endl;
          string inputDir= Form("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev%dmumu_pythia6_zprime%dtev_%srfull%03d_onlyhadronic",Enevec_use[energy],Enevec_use[energy],Signal_use[signal],Dirvec_use[Dir]);
          string decversion;
          if(inputDir.find("rfull009")!=std::string::npos)decversion="rfull009";
          else if(inputDir.find("rfull012")!=std::string::npos)decversion="rfull012";
          else if(inputDir.find("rfull010")!=std::string::npos)decversion="rfull010";

          std::string treeName = "trawhits";
          std::string treeName_cut = "tcalo";
          std::string title = mode==0? Form("Anti-kt jet //Delta R = %.1f",radius):
            Form("Simple jet //Delta R = %.1f",radius);


        
          const std::string histonames[]=
          {
            //"mass_trim",
            //"mass_mmdt",
            //"mass_prun",
            //"mass_sdb2",
            //"mass_sdm1",
            "tau21_b1",
            "c2_b1",
            //"d2_b1",
            //"n2_b1",
            //"tau21_b1_mmdt",
            //"c2_b1_mmdt",
            //"d2_b1_mmdt",
            "tau32_b1"
          };
          const std::string histonames_cut[]=
          {
            //"mass_trim",
            "mass_mmdt"
            //"mass_prun",
            //"mass_sdb2",
            //"mass_sdm1",
            //"tau21_b1",
            //"c2_b1",
            //"d2_b1",
            //"n2_b1",
            //"tau21_b1_mmdt",
            //"c2_b1_mmdt",
            //"d2_b1_mmdt",
            //"tau32_b1"
          };

        

          //  int ntemp_histos=sizeof(histonames)/sizeof(histonames[0]);
            
          std::cout << "Total number of histograms is " << nhistos << std::endl;
          const float xmax[nhistos]={1,0.3,1};
            int nbins_cut=0;
            float xmax_cut[nhistos_cut]={0};
        //======================This range is from the previous study================//
            //=====it just set range, actually, it doesn't influence the results, because we won't approach to the boundary condition.
            if(Signal_use[signal]=="ww")
            {
                xmax_cut[0]={800};
                nbins_cut=160;
            }
            if(Signal_use[signal]=="ttbar")
            {
                xmax_cut[0]={1200};
                nbins_cut=240;
            }
            if(Signal_use[signal]=="qq")//Need to chanage when cut is different!!
            {
                xmax_cut[0]={1200};
                nbins_cut=240;
            }

          TH1F* h_sub[nhistos];
          TH1F* h_sub_cut[nhistos_cut];
          const float xmin=0;
          const float xmin_cut=0;

          const int nbins=25;
          for(int ih=0; ih < nhistos; ih++)
            {
            // [(xmax[ih]-xmin)/nbins]*L or R to find the mass_cut value
              h_sub[ih] = new TH1F(Form("h_%s",histonames[ih].data()), histonames[ih].data(), nbins,xmin,xmax[ih]);
              float binwidth = (xmax[ih]-xmin)/(float)nbins;
              h_sub[ih]->SetXTitle(histonames[ih].data());
              h_sub[ih]->SetYTitle(Form("Number of jets per %.2f",binwidth));
            }
          for(int ih=0; ih < nhistos_cut; ih++)
          {
            // [(xmax[ih]-xmin)/nbins]*L or R to find the mass_cut value
             h_sub_cut[ih] = new TH1F(Form("h_%s",histonames_cut[ih].data()), histonames_cut[ih].data(), nbins_cut,xmin_cut,xmax_cut[ih]);
             float binwidth = (xmax_cut[ih]-xmin_cut)/(float)nbins_cut;
             h_sub_cut[ih]->SetXTitle(histonames_cut[ih].data());
             h_sub_cut[ih]->SetYTitle(Form("Number of jets per %.2f",binwidth));
          }
          string inputFile = inputDir + "/radius" + Form("%0.1f",radius)+ "_rawhit_fastjet_mode0_0.5GeV.root";
          string inputFile_cut = inputDir + "/radius" + Form("%0.1f",radius)+ "_response_e2.root";//we only use cluster to do the mass_variable
          cout << "opening " << inputFile.data() << endl;
          cout << "opening " << inputFile_cut.data() << endl;
          TreeReader genTree(inputFile.data(),"tGEN_nonu");
          TreeReader caloTree(inputFile.data(),treeName.data());
          TreeReader genTree_cut(inputFile_cut.data(),"tGEN_nonu");
          TreeReader caloTree_cut(inputFile_cut.data(),treeName_cut.data());
           //============ Cut function============//
            Cut_ww=cut_ww(Dirvec_use[Dir],Enevec_use[energy]);
            Cut_tt=cut_tt(Dirvec_use[Dir],Enevec_use[energy]);
            cout << Dirvec_use[Dir] << Enevec_use[energy] << endl;
            cout << "Cut_tt[0] " << Cut_tt[0] << "Cut_tt[1]"<< Cut_tt[1] << endl;
            cout << "Cut_ww[0] " << Cut_ww[0] << "Cut_ww[1]"<< Cut_ww[1] << endl;

           //=====================================//
            //=====Cut part=======//
          for(Long64_t jEntry=0; jEntry< genTree.GetEntriesFast() ;jEntry++){
            genTree.GetEntry(jEntry);
            caloTree.GetEntry(jEntry);
            genTree_cut.GetEntry(jEntry);
            caloTree_cut.GetEntry(jEntry);

            Float_t*  gen_je = genTree.GetPtrFloat("je");
            Float_t*  gen_jeta = genTree.GetPtrFloat("jeta");
            Float_t*  gen_jphi = genTree.GetPtrFloat("jphi");
            Int_t     gen_njets = genTree.GetInt("njets");

            Float_t*  calo_je = caloTree.GetPtrFloat("je");
            Float_t*  calo_jeta = caloTree.GetPtrFloat("jeta");
            Float_t*  calo_jphi = caloTree.GetPtrFloat("jphi");
            Int_t     calo_njets = caloTree.GetInt("njets");
    
            Float_t*  calo_cut_je = caloTree_cut.GetPtrFloat("je");
            Float_t*  calo_cut_jeta = caloTree_cut.GetPtrFloat("jeta");
            Float_t*  calo_cut_jphi = caloTree_cut.GetPtrFloat("jphi");
            Int_t     calo_cut_njets = caloTree_cut.GetInt("njets");

            Float_t*  sub[nhistos];
            Float_t*  sub_cut[nhistos];

            for(int ih=0; ih < nhistos; ih++)
            {
              sub[ih] = caloTree.GetPtrFloat(Form("j_%s",histonames[ih].data()));
            }
            for(int ih=0; ih< nhistos_cut ; ih++)
            {
              sub_cut[ih] = caloTree_cut.GetPtrFloat(Form("j_%s",histonames_cut[ih].data()));
            }

            //=====matching the gen tree with rawhit and cluster=======// 
            for(int i=0; i< calo_njets; i++){

              
              if(fabs(calo_jeta[i])>1.1)continue;
            //================================find match between Gentree and trawhit=======================//
              int findGenMatch=-1;
              for(int k=0; k< gen_njets; k++)
              {
            
            
            float dr = myDeltaR(gen_jeta[k], calo_jeta[i],
                                gen_jphi[k], calo_jphi[i]);
              
            if(dr<0.1)
              {
                findGenMatch=k;
                break;
              }
              }
            
              if(findGenMatch<0)continue;
            //================================find match between cluster cut and Gentree=======================//
              int findGenMatch_2=-1;
              for(int k=0; k< calo_cut_njets; k++)
              {
                    
                    
                    float dr = myDeltaR(gen_jeta[findGenMatch], calo_cut_jeta[k],
                                        gen_jphi[findGenMatch], calo_cut_jphi[k]);
                    
                    if(dr<0.1)
                    {
                        findGenMatch_2=k;
                        break;
                    }
                }
                
              if(findGenMatch_2<0)continue;
            
            //===========Pre-selection -> Find the cut in the function ( You can see the function before=========//
            // The concept is find the signal from the highest bincentent and in the 50% region use method 2
            // Look the left and the right bin and see which one is bigger, add that side bin to be the mass window
            //If bump into the zero bin, we use the mean value after that bin ( or before that if the side bin is at the left )
              
              if(Signal_use[signal]=="ww")
              {
                  //int *Cut_ww=cut_ww(1,Enevec_use[energy]);
                 if((sub_cut[0][i]<((Cut_ww[0])*5))||(sub_cut[0][i]>((Cut_ww[1])*5)))continue;
                 for(int ih=0; ih < nhistos; ih++)
                  {
                  if(sub[ih][i]<0)
                  {
                  }
                  else if(sub[ih][i]<=-1)
                  {
                      break;
                  }
                  else if(sub[ih][i]>xmax[ih])
                  {
                      h_sub[ih]->Fill(xmax[ih]-xmax[ih]/nbins/2);
                  }
                  else
                  {
                      h_sub[ih]->Fill(sub[ih][i]);
                  }
                  }
                 for(int ih=0; ih < nhistos_cut; ih++)
                  {
                  if(sub_cut[ih][i]<0)
                  {
                      h_sub_cut[ih]->Fill(sub_cut[ih][i]+0.001);
                  }
                  else if(sub_cut[ih][i]<=-1)
                  {
                      break;
                  }
                  else if(sub_cut[ih][i]>xmax_cut[ih])
                  {
                      h_sub_cut[ih]->Fill(xmax_cut[ih]-xmax_cut[ih]/nbins_cut/2);
                  }
                  else
                  {
                      h_sub_cut[ih]->Fill(sub_cut[ih][i]);
                  }
                  }
              }
              if(Signal_use[signal]=="ttbar")
              {
                //int *Cut_tt=cut_tt(1,Enevec_use[energy]);
                if((sub_cut[0][i]<((Cut_tt[0])*5))||(sub_cut[0][i]>((Cut_tt[1])*5)))continue;
                for(int ih=0; ih < nhistos; ih++)
                  {
                      if(sub[ih][i]<0)
                      {
                          h_sub[ih]->Fill(sub[ih][i]+0.001);
                      }
                      else if(sub[ih][i]<=-1)
                      {
                          cout << "=============================================================================" << endl;
                          break;
                      }
                      else if(sub[ih][i]>xmax[ih])
                      {
                          h_sub[ih]->Fill(xmax[ih]-xmax[ih]/nbins/2);
                      }
                      else
                      {
                          h_sub[ih]->Fill(sub[ih][i]);
                      }
                  }
                  for(int ih=0; ih < nhistos_cut; ih++)
                  {
                      if(sub_cut[ih][i]<0)
                      {
                          h_sub_cut[ih]->Fill(sub_cut[ih][i]+0.001);
                      }
                      else if(sub_cut[ih][i]<=-1)
                      {
                          cout << "=============================================================================" << endl;
                          break;
                      }
                      else if(sub_cut[ih][i]>xmax_cut[ih])
                      {
                          h_sub_cut[ih]->Fill(xmax_cut[ih]-xmax_cut[ih]/nbins_cut/2);
                      }
                      else
                      {
                          h_sub_cut[ih]->Fill(sub_cut[ih][i]);
                      }
                  }
              }
             if(Signal_use[signal]=="qq")
             {
                 //int *Cut_tt=cut_tt(1,Enevec_use[energy]);
                 if((sub_cut[0][i]<((Cut_tt[0])*5))||(sub_cut[0][i]>((Cut_tt[1])*5)))continue;//Change there for different bins
                 for(int ih=0; ih < nhistos; ih++)
                 {
                     if(sub[ih][i]<0)
                     {
                         h_sub[ih]->Fill(sub[ih][i]+0.001);
                     }
                     else if(sub[ih][i]<=-1)
                     {
                         cout << "=============================================================================" << endl;
                         break;
                     }
                     else if(sub[ih][i]>xmax[ih])
                     {
                         h_sub[ih]->Fill(xmax[ih]-xmax[ih]/nbins/2);
                     }
                     else
                     {
                         h_sub[ih]->Fill(sub[ih][i]);
                     }
                 }
                 for(int ih=0; ih < nhistos_cut; ih++)
                 {
                     if(sub_cut[ih][i]<0)
                     {
                         h_sub_cut[ih]->Fill(sub_cut[ih][i]+0.001);
                     }
                     else if(sub_cut[ih][i]<=-1)
                     {
                         cout << "=============================================================================" << endl;
                         break;
                     }
                     else if(sub_cut[ih][i]>xmax_cut[ih])
                     {
                         h_sub_cut[ih]->Fill(xmax_cut[ih]-xmax_cut[ih]/nbins_cut/2);
                     }
                     else
                     {
                         h_sub_cut[ih]->Fill(sub_cut[ih][i]);
                     }
                 }
             }
            }// end of loop over calo jets
          }// end loop of entries
            
           //===========================================================//
          if((Signal_use[signal]=="ttbar")||(Signal_use[signal]=="ww"))
          {
          string outputFile = inputDir + "/radius" + Form("%0.1f",radius)+ "_jetsubstructure_" + treeName + "_mass_cut_0.5GeV_for_"+Form("%s",Signal_use[signal])+"_Dis_25bin_no_UOF.root";
          cout << "writing output to " << outputFile.data() << endl;
          cout << "====================================================================================================" << endl;
          TFile* outFile = new TFile(outputFile.data(),"recreate");
          for(int ih=0;ih<nhistos;ih++)
          {
          h_sub[ih]->Write();
          }
          for(int ih=0;ih<nhistos_cut;ih++)
          {
          h_sub_cut[ih]->Write();
          }
          outFile->Close();
          }
            //===========================================================//

          if(Signal_use[signal]=="qq")
          {
          string outputFile = inputDir + "/radius" + Form("%0.1f",radius)+ "_jetsubstructure_"+ treeName + "_mass_cut_0.5GeV_for_tt_Dis_25bins_no_UOF.root";
          cout << "writing output to " << outputFile.data() << endl;
          cout << "====================================================================================================" << endl;
          TFile* outFile = new TFile(outputFile.data(),"recreate");
          for(int ih=0;ih<nhistos;ih++)
          {
          h_sub[ih]->Write();
          }
          for(int ih=0;ih<nhistos_cut;ih++)
          {
          h_sub_cut[ih]->Write();
          }
          outFile->Close();
          }
            //===========================================================//
          
        }
    }
}
}


  
		 

