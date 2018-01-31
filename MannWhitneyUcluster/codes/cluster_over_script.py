import ROOT
import MannWhitneyUtest
import sys
from ROOT import TFile, TH1F, gDirectory, TCanvas, TPad, TProfile,TGraph, TGraphAsymmErrors,TMultiGraph,TText
from ROOT import TH1D, TH1, TH1I
from ROOT import gStyle
from ROOT import gROOT
from ROOT import TStyle
from ROOT import TLegend
from ROOT import TMath
from ROOT import TPaveText
from ROOT import TLatex
variable=("tau21","tau32","c2b1")
k=0
if(variable[k]=="tau21"):
    f1 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_tau21_5tev_04_Man.root")
    f2 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_tau21_5tev_04_Man.root")
    f3 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_tau21_5tev_04_Man.root")
    f4 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_tau21_5tev_04_Man.root")


    G1 = f1.Get("Graph") #change the names of the histograms to the TH1's present in f1 and f2
    G2 = f2.Get("Graph")
    G3 = f3.Get("Graph")
    G4 = f4.Get("Graph")

    c = TCanvas("c1", "c1",0,0,500,500)
    gStyle.SetOptStat(0)

    leg = TLegend(0.45,0.75,0.75,0.85)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.05)
    leg.SetBorderSize(0)
    leg.SetTextFont(22)
    #leg.AddEntry("","Z'#rightarrowt#bar{t}#rightarrow3 jet","")
    leg.AddEntry("","Z'#rightarrowW^{+}W^{-}#rightarrow2 jet","")
    #leg.AddEntry("","Z'#rightarrowq#bar{q}#rightarrow1 jet","")
    
    mg=TMultiGraph()
    mg.Add(G1)
    mg.Add(G2)
    mg.Add(G3)
    mg.Add(G4)
    mg.Draw("ALP")
    mg.GetXaxis().SetTitle("cm#timescm(cell_size)")
    mg.GetYaxis().SetTitle("U_value")
    mg.GetYaxis().SetRangeUser(0,0.8)
    mg.GetXaxis().SetLabelSize(0)
    mg.GetYaxis().SetLabelSize(0.04)
    mg.GetYaxis().SetLabelFont(22)
    mg.GetXaxis().SetTitleFont(22)
    mg.GetYaxis().SetTitleFont(22)


    leg1 = TLegend(0.1,0.65,0.6,0.9)
    leg1.SetFillColor(0)
    leg1.SetFillStyle(0)
    leg1.SetTextSize(0.05)
    leg1.SetBorderSize(0)
    leg1.SetTextFont(22)
    leg1.AddEntry(G1,"#sqrt{s}=5TeV","l")
    leg1.AddEntry(G2,"#sqrt{s}=10TeV","l")
    leg1.AddEntry(G3,"#sqrt{s}=20TeV","l")
    leg1.AddEntry(G4,"#sqrt{s}=40TeV","l")

    t = TText()
    t.SetTextAlign(20)
    t.SetTextSize(0.03)
    t.SetTextFont(22)
    t.SetTextColor(1)
    label=["20*20","5*5","1*1"]
    for i in range(3):
        t.DrawText(i+1,-0.03,label[i])
    c.Draw()
    mg.Draw()
    leg.Draw()
    leg1.Draw()



    c.Print("Rawhit_0.5GeV_tau21_summary_U.pdf")
    c.Print("Rawhit_0.5GeV_tau21_summary_U.eps")

if(variable[k+1]=="tau32"):
    f1 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_c2b1_5tev_04_Man.root")
    f2 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_c2b1_5tev_04_Man.root")
    f3 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_c2b1_5tev_04_Man.root")
    f4 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_c2b1_5tev_04_Man.root")
    
    
    G1 = f1.Get("Graph") #change the names of the histograms to the TH1's present in f1 and f2
    G2 = f2.Get("Graph")
    G3 = f3.Get("Graph")
    G4 = f4.Get("Graph")
    
    c = TCanvas("c1", "c1",0,0,500,500)
    gStyle.SetOptStat(0)
    
    leg = TLegend(0.45,0.75,0.75,0.85)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.05)
    leg.SetBorderSize(0)
    leg.SetTextFont(22)
    leg.AddEntry("","Z'#rightarrowt#bar{t}#rightarrow3 jet","")
    #leg.AddEntry("","Z'#rightarrowW^{+}W^{-}#rightarrow2 jet","")
    #leg.AddEntry("","Z'#rightarrowq#bar{q}#rightarrow1 jet","")
    
    mg=TMultiGraph()
    mg.Add(G1)
    mg.Add(G2)
    mg.Add(G3)
    mg.Add(G4)
    mg.Draw("ALP")
    mg.GetXaxis().SetTitle("cm#timescm(cell_size)")
    mg.GetYaxis().SetTitle("U_value")
    mg.GetYaxis().SetRangeUser(0,0.8)
    mg.GetXaxis().SetLabelSize(0)
    mg.GetYaxis().SetLabelFont(22)
    mg.GetXaxis().SetTitleFont(22)
    mg.GetYaxis().SetTitleFont(22)
    
    
    leg1 = TLegend(0.1,0.65,0.6,0.9)
    leg1.SetFillColor(0)
    leg1.SetFillStyle(0)
    leg1.SetTextSize(0.05)
    leg1.SetBorderSize(0)
    leg1.SetTextFont(22)
    leg1.AddEntry(G1,"#sqrt{s}=5TeV","l")
    leg1.AddEntry(G2,"#sqrt{s}=10TeV","l")
    leg1.AddEntry(G3,"#sqrt{s}=20TeV","l")
    leg1.AddEntry(G4,"#sqrt{s}=40TeV","l")
    
    t = TText()
    t.SetTextAlign(20)
    t.SetTextSize(0.03)
    t.SetTextFont(22)
    t.SetTextColor(1)
    label=["20*20","5*5","1*1"]
    for i in range(3):
        t.DrawText(i+1,-0.03,label[i])
    c.Draw()
    mg.Draw()
    leg.Draw()
    leg1.Draw()



    c.Print("Rawhit_0.5GeV_tau32_summary_U.pdf")
    c.Print("Rawhit_0.5GeV_tau32_summary_U.eps")

if(variable[k+2]=="c2b1"):
    f1 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_c2b1_5tev_04_Man.root")
    f2 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_c2b1_10tev_04_Man.root")
    f3 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_c2b1_20tev_04_Man.root")
    f4 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyUcluster/Rawhit_0.5GeV_c2b1_40tev_04_Man.root")
    
    
    G1 = f1.Get("Graph") #change the names of the histograms to the TH1's present in f1 and f2
    G2 = f2.Get("Graph")
    G3 = f3.Get("Graph")
    G4 = f4.Get("Graph")
    
    c = TCanvas("c1", "c1",0,0,500,500)
    gStyle.SetOptStat(0)
    
    leg = TLegend(0.45,0.75,0.75,0.85)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.05)
    leg.SetBorderSize(0)
    leg.SetTextFont(22)
    #leg.AddEntry("","Z'#rightarrowt#bar{t}#rightarrow3 jet","")
    leg.AddEntry("","Z'#rightarrowW^{+}W^{-}#rightarrow2 jet","")
    #leg.AddEntry("","Z'#rightarrowq#bar{q}#rightarrow1 jet","")
    
    mg=TMultiGraph()
    mg.Add(G1)
    mg.Add(G2)
    mg.Add(G3)
    mg.Add(G4)
    mg.Draw("ALP")
    mg.GetXaxis().SetTitle("cm#timescm(cell_size)")
    mg.GetYaxis().SetTitle("U_value")
    mg.GetYaxis().SetRangeUser(0,0.8)
    mg.GetXaxis().SetLabelSize(0)
    mg.GetYaxis().SetLabelFont(22)
    mg.GetXaxis().SetTitleFont(22)
    mg.GetYaxis().SetTitleFont(22)
    
    
    leg1 = TLegend(0.1,0.65,0.6,0.9)
    leg1.SetFillColor(0)
    leg1.SetFillStyle(0)
    leg1.SetTextSize(0.05)
    leg1.SetBorderSize(0)
    leg1.SetTextFont(22)
    leg1.AddEntry(G1,"#sqrt{s}=5TeV","l")
    leg1.AddEntry(G2,"#sqrt{s}=10TeV","l")
    leg1.AddEntry(G3,"#sqrt{s}=20TeV","l")
    leg1.AddEntry(G4,"#sqrt{s}=40TeV","l")
    
    t = TText()
    t.SetTextAlign(20)
    t.SetTextSize(0.03)
    t.SetTextFont(22)
    t.SetTextColor(1)
    label=["20*20","5*5","1*1"]
    for i in range(3):
        t.DrawText(i+1,-0.03,label[i])
    c.Draw()
    mg.Draw()
    leg.Draw()
    leg1.Draw()



    c.Print("Rawhit_0.5GeV_c2b1_summary_U.pdf")
    c.Print("Rawhit_0.5GeV_c2b1_summary_U.eps")


