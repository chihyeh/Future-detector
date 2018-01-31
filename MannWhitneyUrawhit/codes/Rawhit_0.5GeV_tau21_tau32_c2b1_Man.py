import ROOT
import sys
import math
import MannWhitneyUtest
from ROOT import TFile, TH1F, gDirectory, TCanvas, TPad, TProfile,TGraph, TGraphAsymmErrors,TGraphErrors
from ROOT import TH1D, TH1, TH1I
from ROOT import gStyle
from ROOT import gROOT
from ROOT import TStyle
from ROOT import TLegend
from ROOT import TMath
from ROOT import TPaveText
from ROOT import TLatex
from array import array
#---------------------------------------------Setting the parameters in
files1="009"
files2="010"
files3="012"
files_array=(files1,files2,files3)
energy_array=("f",[5,10,20,40])
variable=("tau21","tau32","c2b1")
print variable[0],variable[1],variable[2]
print files_array[0],files_array[1],files_array[2]
l=9
p=1
#---------------------------------------------setting the hisotgram in and normalize
for k in range(0,3):
    if(variable[k]=="tau21"):
        for m in range(0,4):
            if(energy_array[1][m]<20):
                f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f3 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f5 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f6 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
            if(energy_array[1][m]>=20):
                f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f3 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f5 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f6 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
 
                        
            h1 = f1.Get("h_"+variable[k]+"_b1")
            h2 = f2.Get("h_"+variable[k]+"_b1")
            h3 = f3.Get("h_"+variable[k]+"_b1")
            h4 = f4.Get("h_"+variable[k]+"_b1")
            h5 = f5.Get("h_"+variable[k]+"_b1")
            h6 = f6.Get("h_"+variable[k]+"_b1")


            h1.Scale(1.0/h1.Integral())
            h2.Scale(1.0/h2.Integral())
            h3.Scale(1.0/h2.Integral())
            h4.Scale(1.0/h2.Integral())
            h5.Scale(1.0/h2.Integral())
            h6.Scale(1.0/h2.Integral())

            U  = MannWhitneyUtest.mannWU(h1, h2)
            U_print  = min (1-U, U)
            U_print_2_decimal=round(U_print,2)
            U1 = MannWhitneyUtest.mannWU(h3, h4)
            U1_print = min (1-U1, U1)
            U1_print_2_decimal=round(U1_print,2)
            U2 = MannWhitneyUtest.mannWU(h5, h6)
            U2_print = min (1-U2, U2)
            U2_print_2_decimal=round(U2_print,2)
            xarray=array("f",[1,2,3])
            yarray=array("f",[U_print_2_decimal,U1_print_2_decimal,U2_print_2_decimal])

            n=3
                  
            if(str(energy_array[1][m])=="5"):
                Color=2
                l=1
            if(str(energy_array[1][m])=="10"):
                Color=3
                l=4
            if(str(energy_array[1][m])=="20"):
                Color=4
                l=7
            if(str(energy_array[1][m])=="40"):
                Color=5
                l=9

            Color1=str(Color)
                
                  
            c = TCanvas("c1", "c1",0,0,500,500)
                  
                  
            gr = TGraph(n,xarray,yarray)
            gr.SetTitle(" ")
            gr.SetLineColor(Color)
            gr.SetLineWidth(5)
            gr.SetLineStyle(l)
            gr.SetMarkerColor(Color)
            gr.SetMarkerStyle(0)
            gr.SetMarkerSize(0)
            gr.GetXaxis().SetTitle("cm#timescm(cell_size)")
            gr.GetYaxis().SetTitle("U_value")
            gr.GetXaxis().SetLabelSize(0)
            gr.GetYaxis().SetLabelFont(22)
            gr.GetXaxis().SetTitleFont(22)
            gr.GetYaxis().SetTitleFont(22)
            gr.Draw()
            
            f=TFile("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root","RECREATE")
            gr.Write()
            c.Print("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.pdf")
            c.Print("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.eps")


                  

    elif(variable[k]=="tau32"):
        for m in range(0,4):
            if(energy_array[1][m]<20):
                f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f3 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f5 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f6 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
            if(energy_array[1][m]>=20):
                f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f3 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f5 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f6 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
        
        
            h1 = f1.Get("h_"+variable[k]+"_b1")
            h2 = f2.Get("h_"+variable[k]+"_b1")
            h3 = f3.Get("h_"+variable[k]+"_b1")
            h4 = f4.Get("h_"+variable[k]+"_b1")
            h5 = f5.Get("h_"+variable[k]+"_b1")
            h6 = f6.Get("h_"+variable[k]+"_b1")
            
            
            h1.Scale(1.0/h1.Integral())
            h2.Scale(1.0/h2.Integral())
            h3.Scale(1.0/h2.Integral())
            h4.Scale(1.0/h2.Integral())
            h5.Scale(1.0/h2.Integral())
            h6.Scale(1.0/h2.Integral())
            
            U  = MannWhitneyUtest.mannWU(h1, h2)
            U_print  = min (1-U, U)
            U_print_2_decimal=round(U_print,2)
            U1 = MannWhitneyUtest.mannWU(h3, h4)
            U1_print = min (1-U1, U1)
            U1_print_2_decimal=round(U1_print,2)
            U2 = MannWhitneyUtest.mannWU(h5, h6)
            U2_print = min (1-U2, U2)
            U2_print_2_decimal=round(U2_print,2)

            xarray=array("f",[1,2,3])
            yarray=array("f",[U_print_2_decimal,U1_print_2_decimal,U2_print_2_decimal])
            
            n=3
            
            if(str(energy_array[1][m])=="5"):
                Color=2
                l=1
            if(str(energy_array[1][m])=="10"):
                Color=3
                l=4
            if(str(energy_array[1][m])=="20"):
                Color=4
                l=7
            if(str(energy_array[1][m])=="40"):
                Color=5
                l=9
            Color1=str(Color)


            c = TCanvas("c1", "c1",0,0,500,500)
    
    
            gr = TGraph(n,xarray,yarray)
            gr.SetTitle(" ")
            gr.SetLineColor(Color)
            gr.SetLineWidth(5)
            gr.SetLineStyle(l)
            gr.SetMarkerColor(Color)
            gr.SetMarkerStyle(0)
            gr.SetMarkerSize(0)
            gr.GetXaxis().SetTitle("cm#timescm(cell_size)")
            gr.GetYaxis().SetTitle("U_value")
            gr.GetXaxis().SetLabelSize(0)
            gr.GetYaxis().SetLabelFont(22)
            gr.GetXaxis().SetTitleFont(22)
            gr.GetYaxis().SetTitleFont(22)
            gr.Draw()
            
            f=TFile("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root","RECREATE")
            gr.Write()
            c.Print("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.pdf")
            c.Print("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.eps")

    elif(variable[k]=="c2b1"):
        for m in range(0,4):
            if(energy_array[1][m]<20):
                f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f3 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f5 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f6 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
            if(energy_array[1][m]>=20):
                f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull010_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f3 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull009_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f5 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
                f6 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull012_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_.0.5GeV_25bins.root", 'r')
        
        
            h1 = f1.Get("h_c2_b1")
            h2 = f2.Get("h_c2_b1")
            h3 = f3.Get("h_c2_b1")
            h4 = f4.Get("h_c2_b1")
            h5 = f5.Get("h_c2_b1")
            h6 = f6.Get("h_c2_b1")
            
            
            h1.Scale(1.0/h1.Integral())
            h2.Scale(1.0/h2.Integral())
            h3.Scale(1.0/h2.Integral())
            h4.Scale(1.0/h2.Integral())
            h5.Scale(1.0/h2.Integral())
            h6.Scale(1.0/h2.Integral())
            
            U  = MannWhitneyUtest.mannWU(h1, h2)
            U_print  = min (1-U, U)
            U_print_2_decimal=round(U_print,2)
            U1 = MannWhitneyUtest.mannWU(h3, h4)
            U1_print = min (1-U1, U1)
            U1_print_2_decimal=round(U1_print,2)
            U2 = MannWhitneyUtest.mannWU(h5, h6)
            U2_print = min (1-U2, U2)
            U2_print_2_decimal=round(U2_print,2)
            xarray=array("f",[1,2,3])
            yarray=array("f",[U_print_2_decimal,U1_print_2_decimal,U2_print_2_decimal])
            
            n=3
            
            if(str(energy_array[1][m])=="5"):
                Color=2
                l=1
            if(str(energy_array[1][m])=="10"):
                Color=3
                l=4
            if(str(energy_array[1][m])=="20"):
                Color=4
                l=7
            if(str(energy_array[1][m])=="40"):
                Color=5
                l=9

            Color1=str(Color)


            c = TCanvas("c1", "c1",0,0,500,500)
    
    
            gr = TGraph(n,xarray,yarray)
            gr.SetTitle(" ")
            gr.SetLineColor(Color)
            gr.SetLineWidth(5)
            gr.SetLineStyle(l)
            gr.SetMarkerColor(Color)
            gr.SetMarkerStyle(0)
            gr.SetMarkerSize(0)
            gr.GetXaxis().SetTitle("cm#timescm(cell_size)")
            gr.GetYaxis().SetTitle("U_value")
            gr.GetXaxis().SetLabelSize(0)
            gr.GetYaxis().SetLabelFont(22)
            gr.GetXaxis().SetTitleFont(22)
            gr.GetYaxis().SetTitleFont(22)
            gr.Draw()
            
            f=TFile("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root","RECREATE")
            gr.Write()
            c.Print("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.pdf")
            c.Print("Rawhit_0.5GeV_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.eps")


