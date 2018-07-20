import ROOT
import sys
import math
from random import randint
from ROOT import TFile, TH1F, gDirectory, TCanvas, TPad, TProfile,TGraph, TGraphAsymmErrors,TGraphErrors
from ROOT import TH1D, TH1, TH1I
from ROOT import gStyle
from ROOT import gROOT
from ROOT import TStyle
from ROOT import TLegend
from ROOT import TMath
from ROOT import TPaveText
from ROOT import TLatex
from ROOT import TLine
from array import array
#-------------------------------
f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_ttbarrfull010_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200.root", 'r')
f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_ttbarrfull009_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200.root", 'r')
f3 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_ttbarrfull012_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200.root", 'r')
#--------------------------------
f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_qqrfull010_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200.root", 'r')
f5 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_qqrfull009_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200.root", 'r')
f6 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_qqrfull012_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200.root", 'r')
#--------------------------------
f7 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_ttbarrfull010_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins.root", 'r')
f8 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_ttbarrfull009_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins.root", 'r')
f9 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev5mumu_pythia6_zprime5tev_ttbarrfull012_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins.root", 'r')
#----------------------------
#=====================================
h1_signal_no_cut=f1.Get("h_mass_mmdt")
h2_signal_no_cut=f2.Get("h_mass_mmdt")
h3_signal_no_cut=f3.Get("h_mass_mmdt")
h4_BKG_no_cut=f4.Get("h_mass_mmdt")
h5_BKG_no_cut=f5.Get("h_mass_mmdt")
h6_BKG_no_cut=f6.Get("h_mass_mmdt")
#=====================================
h7_signal_after_cut=f7.Get("h_mass_mmdt")
h8_signal_after_cut=f8.Get("h_mass_mmdt")
h9_signal_after_cut=f9.Get("h_mass_mmdt")
#=====================================
h1_signal_no_cut.Sumw2()
h2_signal_no_cut.Sumw2()
h3_signal_no_cut.Sumw2()
h4_BKG_no_cut.Sumw2()
h5_BKG_no_cut.Sumw2()
h6_BKG_no_cut.Sumw2()
h7_signal_after_cut.Sumw2()
h8_signal_after_cut.Sumw2()
h9_signal_after_cut.Sumw2()
h1_signal_no_cut.Scale(1.0/h1_signal_no_cut.Integral())
h2_signal_no_cut.Scale(1.0/h2_signal_no_cut.Integral())
h3_signal_no_cut.Scale(1.0/h3_signal_no_cut.Integral())
h4_BKG_no_cut.Scale(1.0/h4_BKG_no_cut.Integral())
h5_BKG_no_cut.Scale(1.0/h5_BKG_no_cut.Integral())
h6_BKG_no_cut.Scale(1.0/h6_BKG_no_cut.Integral())
h7_signal_after_cut.Scale(1.0/h7_signal_after_cut.Integral())
h8_signal_after_cut.Scale(1.0/h8_signal_after_cut.Integral())
h9_signal_after_cut.Scale(1.0/h9_signal_after_cut.Integral())
#======================================
h7_Left=h7_signal_after_cut.FindFirstBinAbove()
h7_right=h7_signal_after_cut.FindLastBinAbove()
h7_Max=h7_signal_after_cut.GetMaximum()
Range_h7_Left=h7_Left*5
Range_h7_right=h7_right*5
h8_Left=h8_signal_after_cut.FindFirstBinAbove()
h8_right=h8_signal_after_cut.FindLastBinAbove()
h8_Max=h8_signal_after_cut.GetMaximum()
Range_h8_Left=h8_Left*5
Range_h8_right=h8_right*5
h9_Left=h9_signal_after_cut.FindFirstBinAbove()
h9_right=h9_signal_after_cut.FindLastBinAbove()
h9_Max=h9_signal_after_cut.GetMaximum()
Range_h9_Left=h9_Left*5
Range_h9_right=h9_right*5
#=====================================
h7_max=h1_signal_no_cut.GetMaximum()
T7_1= TLine(Range_h7_Left,0,Range_h7_Left,h7_max)
T7_1.SetLineColor(3)
T7_2= TLine(Range_h7_right,0,Range_h7_right,h7_max)
T7_2.SetLineColor(3)
#-----------------------
h8_max=h2_signal_no_cut.GetMaximum()
T8_1= TLine(Range_h8_Left,0,Range_h8_Left,h8_max)
T8_1.SetLineColor(3)
T8_2= TLine(Range_h8_right,0,Range_h8_right,h8_max)
T8_2.SetLineColor(3)
#-----------------------
h9_max=h3_signal_no_cut.GetMaximum()
T9_1= TLine(Range_h9_Left,0,Range_h9_Left,h9_max)
T9_1.SetLineColor(3)
T9_2= TLine(Range_h9_right,0,Range_h9_right,h9_max)
T9_2.SetLineColor(3)
#=====================================
leg = TLegend(0.5,0.7,0.8,0.9)
leg.SetFillColor(0)
leg.SetFillStyle(0)
leg.SetTextSize(0.04)
leg.SetBorderSize(0)
leg.SetTextFont(22)
#===================================
c = TCanvas("c1", "c1",0,0,500,500)
gStyle.SetOptStat(0)
h3_signal_no_cut.SetLineColor(2)
h3_signal_no_cut.SetLineWidth(3)
h6_BKG_no_cut.SetLineColor(1)
h6_BKG_no_cut.SetLineWidth(3)
h3_signal_no_cut.SetLineStyle(1)
h6_BKG_no_cut.SetLineStyle(9)
h3_signal_no_cut.SetTitle(" ")
h6_BKG_no_cut.SetTitle(" ")
h3_signal_no_cut.SetXTitle("Mass_mmdt")
h6_BKG_no_cut.SetXTitle("Mass_mmdt")
h3_signal_no_cut.SetYTitle("Number of jet per 0.04")
h6_BKG_no_cut.SetYTitle("Number of jet per 0.04")
h3_signal_no_cut.GetYaxis().SetLabelSize(0.03)
h6_BKG_no_cut.GetYaxis().SetLabelSize(0.03)
h3_signal_no_cut.GetXaxis().SetTitleFont(22)
h6_BKG_no_cut.GetXaxis().SetTitleFont(22)
h3_signal_no_cut.GetYaxis().SetTitleFont(22)
h6_BKG_no_cut.GetYaxis().SetTitleFont(22)
h3_signal_no_cut.GetXaxis().SetLabelFont(22)
h6_BKG_no_cut.GetXaxis().SetLabelFont(22)
h3_signal_no_cut.GetYaxis().SetLabelFont(22)
h6_BKG_no_cut.GetYaxis().SetLabelFont(22)
h3_signal_no_cut.GetXaxis().SetRangeUser(0,400)
h6_BKG_no_cut.GetXaxis().SetRangeUser(0,400)
#=================================
leg.AddEntry(h1_signal_no_cut,"Z'(5TeV)#rightarrowt#bar{t}#rightarrow3 jet","l")
leg.AddEntry(h4_BKG_no_cut,"Z'(5TeV)#rightarrowq#bar{q}#rightarrow1 jet","l")
#================================
h6_BKG_no_cut.Draw("hist")
h3_signal_no_cut.Draw("histsame")
T9_1.Draw()
T9_2.Draw()
leg.Draw()
c.Draw()

c.Print("Mass_cut_1x1.pdf")







