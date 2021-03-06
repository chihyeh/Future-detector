import ROOT
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
from array import array


f1 = ROOT.TFile.Open("/Users/ms08962476/github/Study_of_rawhit_cut_plots_in_efficiency/codes/Rawhit_0.5GeV_r012_tau32_10tev_04_eff_log.root",'r')
f2 = ROOT.TFile.Open("/Users/ms08962476/github/Study_of_rawhit_cut_plots_in_efficiency/codes/Rawhit_0.25GeV_r012_tau32_10tev_04_eff_log.root",'r')
#f3 = ROOT.TFile.Open(sys.argv[3], 'r')
energy= 5
files="r012"


#f4 = ROOT.TFile.Open(sys.argv[4], 'r')

G1 = f1.Get("Graph")
#G1.SetName("G1")
G2 = f2.Get("Graph")
#G2.SetName("G2")
#G3 = f3.Get("Graph")
#G3.SetName("G3")
print G1,G2
#G1.Scale(1.0/G1.Integral())
#G2.Scale(1.0/G2.Integral())

c = TCanvas("c1", "c1",0,0,1000,1000)
gStyle.SetOptStat(0)
leg = TLegend(0.1,0.65,0.4,0.9)
leg.SetFillColor(0)
leg.SetFillStyle(0)
leg.SetTextSize(0.04)
leg.SetBorderSize(0)

#mg=TMultiGraph()
G1.SetLineColor(2)
G2.SetLineColor(1)
G1.SetLineWidth(3)
G2.SetLineWidth(3)
G2.Draw("")
G1.Draw("same")
#G3.Draw("ALPsame")
#G4.Draw("ALPsame")
variable="tau21"
energy_cut1= 0.25
energy_cut2= 0.5
energy1=str(energy)
energy1_cut=str(energy_cut1)
energy2_cut=str(energy_cut2)
mg=TMultiGraph()
mg.Add(G1)
mg.Add(G2)

#mg.Add(G1)
#mg.Add(G2)
#mg.Add(G3)
#mg.Add(G4)
#mg.SetTitle("cluster_"+variable+"_"+energy1+"_tev_eff_compare_same_central; signal efficiency; 1 - background efficiency")
#mg.SetTitle("raw_"+variable+"_"+energy1+"tev_"+energy1_cut+"_compare_to_"+energy2_cut+"GeV_eff; signal efficiency; 1 - background efficiency")
#mg.SetTitle("Try_tau21_tGEN_nonu")
#mg.Draw("ALP")
#mg.GetXaxis().SetLabelOffset(999)
#mg.GetXaxis().SetLabelize(0)
#mg.GetYaxis().SetRangeUser(0,0.8)



#t = TText()
#t.SetTextAlign(20)
#t.SetTextSize(0.030)
#t.SetTextFont(60)
#t.SetTextColor(4)
#label=["20*20","5*5","1*1"]
#for i in range(3):
#    t.DrawText(i+1,-0.03,label[i])

#leg.AddEntry("G3","1*1","l")

#leg.AddEntry("G4","#sqrt{s}=40TeV","l")
c.SetLogy()
c.Draw()
leg.Draw()


c.Print("Distribution_cluster_tau21_"+files+"_"+energy1+"tev_plot_ww_qq_try.pdf")
#c.Print("cluster_"+variable+"_"+energy1+"_tev_eff_compare_central_fixed.pdf")
#c.Print("raw_"+variable+"_"+energy1+"tev_"+energy1_cut+"_compare_to_"+energy2_cut+"GeV_eff.pdf")




