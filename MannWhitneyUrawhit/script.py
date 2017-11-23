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

f1 = ROOT.TFile.Open(sys.argv[1], 'r')
f2 = ROOT.TFile.Open(sys.argv[2], 'r')

h1 = f1.Get("h_c2_b1") #change the names of the histograms to the TH1's present in f1 and f2
h2 = f2.Get("h_c2_b1")

h1.Sumw2()
h2.Sumw2()
h1.Scale(1.0/h1.Integral())
h2.Scale(1.0/h2.Integral())

U = MannWhitneyUtest.mannWU(h1, h2)
U_print = min (1-U, U)
U_print_2_decimal=round(U_print,2)
a=str(U_print_2_decimal)

leg = TLegend(0.72,0.6,0.4,0.8)
leg.SetFillColor(0);
leg.SetFillStyle(0);
leg.SetTextSize(0.04);
leg.SetBorderSize(0);

c = TCanvas("c1", "c1",0,0,500,500)
gStyle.SetOptStat(0)
h1.SetLineColor(2)
h1.SetLineWidth(3)
h2.SetLineColor(1)
h2.SetLineWidth(3)
leg.AddEntry("","#sqrt{s}=40TeV","")
leg.AddEntry(h1,"z'->qq","l")
leg.AddEntry(h2,"z'->ww","l")

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


c.Print("raw_r012_c2b1_40tev_04_U.pdf")
#where h1 and h2 are TH1s

