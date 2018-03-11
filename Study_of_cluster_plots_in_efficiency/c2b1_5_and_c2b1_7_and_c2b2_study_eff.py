import ROOT
import sys
from ROOT import TFile, TH1F, gDirectory, TCanvas, TPad, TProfile,TGraph, TGraphAsymmErrors
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
#variable=("tau21","tau32","c2b1")
variable=("c2b1_5","c2b1","c2b1_7","c2b2")
print variable[0],variable[1],variable[2],variable[3]
print files_array[0],files_array[1],files_array[2]
l=9
p=1
#---------------------------------------------setting the hisotgram in and normalize
for k in range(0,4):
    if(variable[k]=="c2b1_5"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                        
                h1 = f1.Get("h_c2_b1_5")
                h2 = f2.Get("h_c2_b1_5")
                print h1,h2
                print variable[k]
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                  
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                print xarray
                print yarray
                n=51
                  
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                    p=1
                if(files_array[i]=="010"):
                    Color=2
                    l=21
                    p=2
                if(files_array[i]=="012"):
                    Color=2
                    l=22
                    p=10
                Color1=str(Color)

                
                  
                c = TCanvas("c1", "c1",0,0,500,500)
                  
                  
                gr = TGraph(n,xarray,yarray)
                gr.SetLineColor(Color)
                gr.SetLineWidth(3)
                gr.SetLineStyle(p)
                #gr.SetMarkerColor(Color)
                #gr.SetMarkerStyle(l)
                #gr.SetMarkerSize(1)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff.pdf")
    if(variable[k]=="c2b1"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
        
                h1 = f1.Get("h_c2_b1")
                h2 = f2.Get("h_c2_b1")
                print h1,h2
                print variable[k]
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                print xarray
                print yarray
                n=51
                
                if(files_array[i]=="009"):
                    Color=5
                    l=4
                    p=1
                if(files_array[i]=="010"):
                    Color=5
                    l=21
                    p=2
                if(files_array[i]=="012"):
                    Color=5
                    l=22
                    p=10
                Color1=str(Color)
                
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraph(n,xarray,yarray)
                gr.SetLineColor(Color)
                gr.SetLineWidth(3)
                gr.SetLineStyle(p)
                #gr.SetMarkerColor(Color)
                #gr.SetMarkerStyle(l)
                #gr.SetMarkerSize(1)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff.pdf")



    elif(variable[k]=="c2b1_7"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                h1 = f1.Get("h_c2_b1_7")
                h2 = f2.Get("h_c2_b1_7")
                print h1,h2
                         
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                                           
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                                           
                for o in range(51):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                print xarray
                print yarray
                n=51
                                           
                if(files_array[i]=="009"):
                    Color=3
                    l=4
                    p=1
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                    p=2
                if(files_array[i]=="012"):
                    Color=3
                    l=22
                    p=10
                Color1=str(Color)
                                           
                                           
                c = TCanvas("c1", "c1",0,0,500,500)
                                           
                                           
                gr = TGraph(n,xarray,yarray)
                gr.SetLineColor(Color)
                gr.SetLineWidth(3)
                gr.SetLineStyle(p)
                #gr.SetMarkerColor(Color)
                #gr.SetMarkerStyle(l)
                #gr.SetMarkerSize(1)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()
                                           
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff.pdf")
                                           
                                           


    elif(variable[k]=="c2b2"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_c2_variable.root", 'r')

                h1 = f1.Get("h_c2_b2")
                h2 = f2.Get("h_c2_b2")
                print h1,h2

                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())

                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])

                for o in range(100):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1-h2.Integral(0,0+o)/b)
                print xarray
                print yarray
                n=51

                if(files_array[i]=="009"):
                    Color=4
                    l=4
                    p=1
                if(files_array[i]=="010"):
                    Color=4
                    l=21
                    p=2
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                    p=10
                Color1=str(Color)



                c = TCanvas("c1", "c1",0,0,500,500)


                gr = TGraph(n,xarray,yarray)
                gr.SetLineColor(Color)
                gr.SetLineWidth(3)
                gr.SetLineStyle(p)
                #gr.SetMarkerColor(Color)
                #gr.SetMarkerStyle(l)
                #gr.SetMarkerSize(1)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1-background_efficiency")
                gr.Draw()

                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff.pdf")


