import ROOT
import MannWhitneyUtest
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

f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev20mumu_pythia6_zprime20tev_ttbar%rfull009_onlyhadronic/radius0.4_jetsubstructure_retcalo.root", 'r')
f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev20mumu_pythia6_zprime20tev_qq%rfull009_onlyhadronic/radius0.4_jetsubstructure_retcalo.root", 'r')

h1 = f1.Get("h_tau32_b1") #change the names of the histograms to the TH1's present in f1 and f2
h2 = f2.Get("h_tau32_b1")

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
h1.SetLineColor(1)
h1.SetLineWidth(3)
h2.SetLineColor(2)
h2.SetLineWidth(3)
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




leg.AddEntry(h1,"Z'(20TeV)#rightarrowt#bar{t}#rightarrow3 jet","l")
#leg.AddEntry(h1,"Z'(20TeV)#rightarrowW^{+}W^{-}#rightarrow2 jet","l")
leg.AddEntry(h2,"Z'(20TeV)#rightarrowq#bar{q}#rightarrow1 jet","l")

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


c.Print("r009_tau32b1_20tev_04_U.pdf")
c.Print("r009_tau32b1_20tev_04_U.eps")

#where h1 and h2 are TH1s

