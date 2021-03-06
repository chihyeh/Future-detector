import ROOT
import sys
import math
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
variable=("tau21b0b0_ww","tau32b0b0_tt","tau21b2b0_ww","tau32b2b0_tt","tau21b2b2_ww","tau32b2b2_tt","c2b1_b0_ww","c2b1_b2_ww")
print variable[0],variable[1],variable[2]
print files_array[0],files_array[1],files_array[2]
l=9
p=1
#---------------------------------------------setting the hisotgram in and normalize
for k in range(0,8):
    if(variable[k]=="tau21b0b0_ww"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
        
                h1 = f1.Get("h_tau21_b1_mmdt_mmdt")
                h2 = f2.Get("h_tau21_b1_mmdt_mmdt")
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                #print b
                print str(a)
                print str(b)
                print h1.Integral(0,15)/a
                print 1-h2.Integral(0,15)/b
                print math.sqrt((1-h1.Integral(0,15)/a)*(h1.Integral(0,15)/a)/a)
                print math.sqrt((1-h2.Integral(0,15)/b)*(h2.Integral(0,15)/b)/b)
                #print h2.Integral(0,26)
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                    xarrayErrors.append(math.sqrt((1-h1.Integral(0,0+o)/a)*(h1.Integral(0,0+o)/a)/a))
                    yarrayErrors.append(math.sqrt((1-h2.Integral(0,0+o)/b)*(h2.Integral(0,0+o)/b)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=51
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")
    elif(variable[k]=="tau32b0b0_tt"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                
                h1 = f1.Get("h_tau21_b1_mmdt_mmdt")
                h2 = f2.Get("h_tau21_b1_mmdt_mmdt")
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                #print b
                print str(a)
                print str(b)
                print h1.Integral(0,15)/a
                print 1-h2.Integral(0,15)/b
                print math.sqrt((1-h1.Integral(0,15)/a)*(h1.Integral(0,15)/a)/a)
                print math.sqrt((1-h2.Integral(0,15)/b)*(h2.Integral(0,15)/b)/b)
                #print h2.Integral(0,26)
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                    xarrayErrors.append(math.sqrt((1-h1.Integral(0,0+o)/a)*(h1.Integral(0,0+o)/a)/a))
                    yarrayErrors.append(math.sqrt((1-h2.Integral(0,0+o)/b)*(h2.Integral(0,0+o)/b)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=51
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")

    elif(variable[k]=="tau21b2b0_ww"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
        
                h1 = f1.Get("h_tau21_b1_sdb2_mmdt")
                h2 = f2.Get("h_tau21_b1_sdb2_mmdt")
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                #print b
                print str(a)
                print str(b)
                print h1.Integral(0,15)/a
                print 1-h2.Integral(0,15)/b
                print math.sqrt((1-h1.Integral(0,15)/a)*(h1.Integral(0,15)/a)/a)
                print math.sqrt((1-h2.Integral(0,15)/b)*(h2.Integral(0,15)/b)/b)
                #print h2.Integral(0,26)
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                    xarrayErrors.append(math.sqrt((1-h1.Integral(0,0+o)/a)*(h1.Integral(0,0+o)/a)/a))
                    yarrayErrors.append(math.sqrt((1-h2.Integral(0,0+o)/b)*(h2.Integral(0,0+o)/b)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=51
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")

    elif(variable[k]=="tau32b2b0_tt"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
        
                h1 = f1.Get("h_tau21_b1_sdb2_mmdt")
                h2 = f2.Get("h_tau21_b1_sdb2_mmdt")
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                #print b
                print str(a)
                print str(b)
                print h1.Integral(0,15)/a
                print 1-h2.Integral(0,15)/b
                print math.sqrt((1-h1.Integral(0,15)/a)*(h1.Integral(0,15)/a)/a)
                print math.sqrt((1-h2.Integral(0,15)/b)*(h2.Integral(0,15)/b)/b)
                #print h2.Integral(0,26)
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                    xarrayErrors.append(math.sqrt((1-h1.Integral(0,0+o)/a)*(h1.Integral(0,0+o)/a)/a))
                    yarrayErrors.append(math.sqrt((1-h2.Integral(0,0+o)/b)*(h2.Integral(0,0+o)/b)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=51
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")

    elif(variable[k]=="tau21b2b2_ww"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                
                h1 = f1.Get("h_tau21_b1_sdb2_sdb2")
                h2 = f2.Get("h_tau21_b1_sdb2_sdb2")
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                #print b
                print str(a)
                print str(b)
                print h1.Integral(0,15)/a
                print 1-h2.Integral(0,15)/b
                print math.sqrt((1-h1.Integral(0,15)/a)*(h1.Integral(0,15)/a)/a)
                print math.sqrt((1-h2.Integral(0,15)/b)*(h2.Integral(0,15)/b)/b)
                #print h2.Integral(0,26)
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                    xarrayErrors.append(math.sqrt((1-h1.Integral(0,0+o)/a)*(h1.Integral(0,0+o)/a)/a))
                    yarrayErrors.append(math.sqrt((1-h2.Integral(0,0+o)/b)*(h2.Integral(0,0+o)/b)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=51
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")

    elif(variable[k]=="tau32b2b2_tt"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
        
                h1 = f1.Get("h_tau21_b1_sdb2_sdb2")
                h2 = f2.Get("h_tau21_b1_sdb2_sdb2")
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                #print b
                print str(a)
                print str(b)
                print h1.Integral(0,15)/a
                print 1-h2.Integral(0,15)/b
                print math.sqrt((1-h1.Integral(0,15)/a)*(h1.Integral(0,15)/a)/a)
                print math.sqrt((1-h2.Integral(0,15)/b)*(h2.Integral(0,15)/b)/b)
                #print h2.Integral(0,26)
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                    xarrayErrors.append(math.sqrt((1-h1.Integral(0,0+o)/a)*(h1.Integral(0,0+o)/a)/a))
                    yarrayErrors.append(math.sqrt((1-h2.Integral(0,0+o)/b)*(h2.Integral(0,0+o)/b)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=51
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")

    elif(variable[k]=="c2b1_b0_ww"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                
                h1 = f1.Get("h_c2_b1_mmdt")
                h2 = f2.Get("h_c2_b1_mmdt")
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                #print b
                print str(a)
                print str(b)
                print h1.Integral(0,15)/a
                print 1-h2.Integral(0,15)/b
                print math.sqrt((1-h1.Integral(0,15)/a)*(h1.Integral(0,15)/a)/a)
                print math.sqrt((1-h2.Integral(0,15)/b)*(h2.Integral(0,15)/b)/b)
                #print h2.Integral(0,26)
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                    xarrayErrors.append(math.sqrt((1-h1.Integral(0,0+o)/a)*(h1.Integral(0,0+o)/a)/a))
                    yarrayErrors.append(math.sqrt((1-h2.Integral(0,0+o)/b)*(h2.Integral(0,0+o)/b)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=51
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")

    elif(variable[k]=="c2b1_b2_ww"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_Dichroic.root", 'r')
        
                h1 = f1.Get("h_c2_b1_sdb2")
                h2 = f2.Get("h_c2_b1_sdb2")
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                #print b
                print str(a)
                print str(b)
                print h1.Integral(0,15)/a
                print 1-h2.Integral(0,15)/b
                print math.sqrt((1-h1.Integral(0,15)/a)*(h1.Integral(0,15)/a)/a)
                print math.sqrt((1-h2.Integral(0,15)/b)*(h2.Integral(0,15)/b)/b)
                #print h2.Integral(0,26)
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                    xarrayErrors.append(math.sqrt((1-h1.Integral(0,0+o)/a)*(h1.Integral(0,0+o)/a)/a))
                    yarrayErrors.append(math.sqrt((1-h2.Integral(0,0+o)/b)*(h2.Integral(0,0+o)/b)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=51
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")

