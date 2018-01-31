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
        for j in range(0,3):
            for m in range(0,4):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
     
                            
                h1 = f1.Get("h_"+variable[k]+"_b1")
                h2 = f2.Get("h_"+variable[k]+"_b1")

                h1.Sumw2()
                h2.Sumw2()
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())

                U = MannWhitneyUtest.mannWU(h1, h2)
                U_print = min (1-U, U)
                U_print_2_decimal=round(U_print,2)
                a=str(U_print_2_decimal)

                leg = TLegend(0.1,0.7,0.4,0.9)
                leg.SetFillColor(0)
                leg.SetFillStyle(0)
                leg.SetTextSize(0.04)
                leg.SetBorderSize(0)
                leg.SetTextFont(22)

                c = TCanvas("c1", "c1",0,0,500,500)
                gStyle.SetOptStat(0)
                h1.SetLineColor(2)
                h1.SetLineWidth(3)
                h2.SetLineColor(1)
                h2.SetLineWidth(3)
                h2.SetLineStyle(9)
                h1.SetTitle(" ")
                h2.SetTitle(" ")
                h1.SetXTitle("#tau_{21}")
                h2.SetXTitle("#tau_{21}")
                h1.SetYTitle("Number of jet per 0.04")
                h2.SetYTitle("Number of jet per 0.04")
                h1.GetYaxis().SetLabelSize(0.03)
                h2.GetYaxis().SetLabelSize(0.03)
                h1.GetXaxis().SetTitleFont(22)
                h2.GetXaxis().SetTitleFont(22)
                h1.GetYaxis().SetTitleFont(22)
                h2.GetYaxis().SetTitleFont(22)
                h1.GetXaxis().SetLabelFont(22)
                h2.GetXaxis().SetLabelFont(22)
                h1.GetYaxis().SetLabelFont(22)
                h2.GetYaxis().SetLabelFont(22)




    #leg.AddEntry(h1,"Z'(20TeV)#rightarrowt#bar{t}#rightarrow3 jet","l")
                leg.AddEntry(h1,"Z'("+str(energy_array[1][m])+"TeV)#rightarrowW^{+}W^{-}#rightarrow2 jet","l")
                leg.AddEntry(h2,"Z'("+str(energy_array[1][m])+"TeV)#rightarrowq#bar{q}#rightarrow1 jet","l")

                if(h1.GetBinContent(h1.GetMaximumBin())>h2.GetBinContent(h2.GetMaximumBin())):
                    h1.Draw("hist")
                    h2.Draw("histsame")
                else:
                    h2.Draw("hist")
                    h1.Draw("histsame")

                leg.AddEntry("","MannWhitneyUtest:","")
                leg.AddEntry("",a,"")
                leg.Draw()
                c.Draw()


    #c.Print("r009_tau32b1_20tev_04_U.pdf")
    #c.Print("r009_tau32b1_20tev_04_U.eps")
        
                f=TFile("Dis_Rawhit_0.25GeV_"+files_array[j]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root","RECREATE")
                #c.Print("Dis_Rawhit_0.25GeV_"+files_array[k]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root.pdf")
                c.Print("Dis_Rawhit_0.25GeV_"+files_array[j]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.eps")


                  

    elif(variable[k]=="tau32"):
        for j in range(0,3):
            for m in range(0,4):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
        
        
                h1 = f1.Get("h_"+variable[k]+"_b1")
                h2 = f2.Get("h_"+variable[k]+"_b1")
                
                h1.Sumw2()
                h2.Sumw2()
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                
                U = MannWhitneyUtest.mannWU(h1, h2)
                U_print = min (1-U, U)
                U_print_2_decimal=round(U_print,2)
                a=str(U_print_2_decimal)
                
                leg = TLegend(0.1,0.7,0.4,0.9)
                leg.SetFillColor(0)
                leg.SetFillStyle(0)
                leg.SetTextSize(0.04)
                leg.SetBorderSize(0)
                leg.SetTextFont(22)
                
                c = TCanvas("c1", "c1",0,0,500,500)
                gStyle.SetOptStat(0)
                h1.SetLineColor(2)
                h1.SetLineWidth(3)
                h2.SetLineColor(1)
                h2.SetLineWidth(3)
                h2.SetLineStyle(9)
                h1.SetTitle(" ")
                h2.SetTitle(" ")
                h1.SetXTitle("#tau_{32}")
                h2.SetXTitle("#tau_{32}")
                h1.SetYTitle("Number of jet per 0.04")
                h2.SetYTitle("Number of jet per 0.04")
                h1.GetYaxis().SetLabelSize(0.03)
                h2.GetYaxis().SetLabelSize(0.03)
                h1.GetXaxis().SetTitleFont(22)
                h2.GetXaxis().SetTitleFont(22)
                h1.GetYaxis().SetTitleFont(22)
                h2.GetYaxis().SetTitleFont(22)
                h1.GetXaxis().SetLabelFont(22)
                h2.GetXaxis().SetLabelFont(22)
                h1.GetYaxis().SetLabelFont(22)
                h2.GetYaxis().SetLabelFont(22)
                
                
                
                
                leg.AddEntry(h1,"Z'("+str(energy_array[1][m])+"TeV)#rightarrowt#bar{t}#rightarrow3 jet","l")
                #leg.AddEntry(h1,"Z'(20TeV)#rightarrowW^{+}W^{-}#rightarrow2 jet","l")
                leg.AddEntry(h2,"Z'("+str(energy_array[1][m])+"TeV)#rightarrowq#bar{q}#rightarrow1 jet","l")
                
                if(h1.GetBinContent(h1.GetMaximumBin())>h2.GetBinContent(h2.GetMaximumBin())):
                    h1.Draw("hist")
                    h2.Draw("histsame")
                else:
                    h2.Draw("hist")
                    h1.Draw("histsame")
            
                leg.AddEntry("","MannWhitneyUtest:","")
                leg.AddEntry("",a,"")
                leg.Draw()
                c.Draw()
                
                
                #c.Print("r009_tau32b1_20tev_04_U.pdf")
                #c.Print("r009_tau32b1_20tev_04_U.eps")
                
                f=TFile("Dis_Rawhit_0.25GeV_"+files_array[j]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root","RECREATE")
                #c.Print("Dis_Rawhit_0.25GeV_"+files_array[k]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root.pdf")
                c.Print("Dis_Rawhit_0.25GeV_"+files_array[j]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.eps")

    elif(variable[k]=="c2b1"):
        for j in range(0,3):
            for m in range(0,4):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhits_0.25GeV_25bins.root", 'r')
        
        
                h1 = f1.Get("h_c2_b1")
                h2 = f2.Get("h_c2_b1")
                
                h1.Sumw2()
                h2.Sumw2()
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                
                U = MannWhitneyUtest.mannWU(h1, h2)
                U_print = min (1-U, U)
                U_print_2_decimal=round(U_print,2)
                a=str(U_print_2_decimal)
                
                leg = TLegend(0.4,0.7,0.7,0.9)
                leg.SetFillColor(0)
                leg.SetFillStyle(0)
                leg.SetTextSize(0.04)
                leg.SetBorderSize(0)
                leg.SetTextFont(22)
                
                c = TCanvas("c1", "c1",0,0,500,500)
                gStyle.SetOptStat(0)
                h1.SetLineColor(2)
                h1.SetLineWidth(3)
                h2.SetLineColor(1)
                h2.SetLineWidth(3)
                h2.SetLineStyle(9)
                h1.SetTitle(" ")
                h2.SetTitle(" ")
                h1.SetXTitle("c_{2}^{1}")
                h2.SetXTitle("c_{2}^{1}")
                h1.SetYTitle("Number of jet per 0.04")
                h2.SetYTitle("Number of jet per 0.04")
                h1.GetYaxis().SetLabelSize(0.03)
                h2.GetYaxis().SetLabelSize(0.03)
                h1.GetXaxis().SetTitleFont(22)
                h2.GetXaxis().SetTitleFont(22)
                h1.GetYaxis().SetTitleFont(22)
                h2.GetYaxis().SetTitleFont(22)
                h1.GetXaxis().SetLabelFont(22)
                h2.GetXaxis().SetLabelFont(22)
                h1.GetYaxis().SetLabelFont(22)
                h2.GetYaxis().SetLabelFont(22)
                
                
                
                
                #leg.AddEntry(h1,"Z'("+str(energy_array[1][m])+"TeV)#rightarrowt#bar{t}#rightarrow3 jet","l")
                leg.AddEntry(h1,"Z'("+str(energy_array[1][m])+"TeV)#rightarrowW^{+}W^{-}#rightarrow2 jet","l")
                leg.AddEntry(h2,"Z'("+str(energy_array[1][m])+"TeV)#rightarrowq#bar{q}#rightarrow1 jet","l")
                
                if(h1.GetBinContent(h1.GetMaximumBin())>h2.GetBinContent(h2.GetMaximumBin())):
                    h1.Draw("hist")
                    h2.Draw("histsame")
                else:
                    h2.Draw("hist")
                    h1.Draw("histsame")
                
                leg.AddEntry("","MannWhitneyUtest:","")
                leg.AddEntry("",a,"")
                leg.Draw()
                c.Draw()
                
                
                #c.Print("r009_tau32b1_20tev_04_U.pdf")
                #c.Print("r009_tau32b1_20tev_04_U.eps")
                
                f=TFile("Dis_Rawhit_0.25GeV_"+files_array[j]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root","RECREATE")
                #c.Print("Dis_Rawhit_0.25GeV_"+files_array[k]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.root.pdf")
                c.Print("Dis_Rawhit_0.25GeV_"+files_array[j]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_Man.eps")


