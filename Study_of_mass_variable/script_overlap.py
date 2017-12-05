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
from array import array

energy_array=("f",[5,10,20,40])
width_array=("f",[40,60,80,100])
signal_we_want=("ww","tt")
variable="mass_sdb2"
for j in range(0,2):
    for i in range(0,4):
        print signal_we_want[j]
        print "energy="+str(energy_array[1][i])
        print "width="+str(width_array[1][i])
        f1 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyU/cluster_r010_"+variable+"_"+str(energy_array[1][i])+"tev_eff_1_width_"+str(width_array[1][i])+"GeV_fix_"+signal_we_want[j]+".root",'r')
#f1 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyU/cluster_r010_mass_mmdt_40tev_eff_1_width_40GeV_fix_tt.root",'r')
        G1=f1.Get("Graph")
        f2 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyU/cluster_r009_"+variable+"_"+str(energy_array[1][i])+"tev_eff_1_width_"+str(width_array[1][i])+"GeV_fix_"+signal_we_want[j]+".root",'r')
#f2 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyU/cluster_r009_mass_mmdt_40tev_eff_1_width_40GeV_fix_tt.root",'r')
        G2=f2.Get("Graph")
        f3 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyU/cluster_r012_"+variable+"_"+str(energy_array[1][i])+"tev_eff_1_width_"+str(width_array[1][i])+"GeV_fix_"+signal_we_want[j]+".root",'r')
#f3 = ROOT.TFile.Open("/Users/ms08962476/MannWhitneyU/cluster_r012_mass_mmdt_40tev_eff_1_width_40GeV_fix_tt.root",'r')
        G3=f3.Get("Graph")
#f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev40mumu_pythia6_zprime40tev_qq%rfull010_onlyhadronic/radius0.4_jetsubstructure_tGEN_nonu.root",'r')
#G4=f4.Get("h_tau32_b1")
#f5 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev40mumu_pythia6_zprime40tev_qq%rfull009_onlyhadronic/radius0.4_jetsubstructure_tGEN_nonu.root", 'r')
#G5=f5.Get("h_tau32_b1")
#f6 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev40mumu_pythia6_zprime40tev_qq%rfull012_onlyhadronic/radius0.4_jetsubstructure_tGEN_nonu.root", 'r')
#G6=f6.Get("h_tau32_b1")
#f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev40mumu_pythia6_zprime40tev_qq%rfull012_onlyhadronic/radius0.4_jetsubstructure_tGEN_nonu.root", 'r')
#G2=f2.Get("h_tau32_b1")
#f3 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev40mumu_pythia6_zprime40tev_ttbar%rfull012_onlyhadronic/radius0.4_jetsubstructure_retcalo.root", 'r')
#G3=f3.Get("h_tau32_b1")
#f4 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev40mumu_pythia6_zprime40tev_qq%rfull012_onlyhadronic/radius0.4_jetsubstructure_retcalo.root", 'r')
#G4=f4.Get("h_tau32_b1")
#fixed_point=i
#f3 = ROOT.TFile.Open(sys.argv[3], 'r')
#f4 = ROOT.TFile.Open(sys.argv[4], 'r')

#G1 = f1.Get("Graph")
#G1.SetName("G1")
#G2 = f2.Get("Graph")
#G2.SetName("G2")
#G3 = f3.Get("Graph")
#G3.SetName("G3")

#G1.Sumw2()
#G2.Sumw2()
#G3.Sumw2()
#G4.Sumw2()
#G5.Sumw2()
#G6.Sumw2()


#G1.Scale(1.0/G1.Integral())
#G2.Scale(1.0/G2.Integral())
#G3.Scale(1.0/G3.Integral())
#G4.Scale(1.0/G4.Integral())
#G5.Scale(1.0/G5.Integral())
#G6.Scale(1.0/G6.Integral())



        c = TCanvas("c1", "c1",0,0,1000,1000)
        gStyle.SetOptStat(0)
#tau21-leg = TLegend(0.1,0.7,0.6,0.9)
        leg = TLegend(0.1,0.7,0.9,0.9)
        leg.SetFillColor(0)
        leg.SetFillStyle(0)
        leg.SetTextSize(0.04)
        leg.SetBorderSize(2)

        mg=TMultiGraph()

#G1.Draw("E")
#G2.Draw("E")
#G3.Draw("E")
#G4.Draw("E")
#G5.Draw("E")
#G6.Draw("E")


#G1.Draw("histsame")
#G2.Draw("histsame")
#G3.Draw("histsame")
#G4.Draw("histsameE")
#G5.Draw("histsameE")
#G6.Draw("histsameE")


#G1.SetLineWidth(2)
#G2.SetLineWidth(2)
#G3.SetLineWidth(2)
#G4.SetLineWidth(2)
#G5.SetLineWidth(2)
#G6.SetLineWidth(2)


#G1.SetLineStyle(1)
#G2.SetLineStyle(1)
#G3.SetLineStyle(1)
#G4.SetLineStyle(4)
#G5.SetLineStyle(4)
#G6.SetLineStyle(4)

#G3.Draw("ALPsame")
#G4.Draw("ALPsame")
#energy_cut1= 0.25
#energy_cut2= 0.5
#fixed_point1=str(fixed_point)
#energy1_cut=str(energy_cut1)
#energy2_cut=str(energy_cut2)

        mg.Add(G1)
        mg.Add(G2)
        mg.Add(G3)
#mg.Add(G4)
#G1.SetLineColor(1)
#G2.SetLineColor(2)
#G3.SetLineColor(3)
#G4.SetLineColor(2)
#G5.SetLineColor(1)
#G6.SetLineColor(3)

#G1.SetXTitle(variable);
#tau32,tau21 -> 0.04  c2b1 ->0.01
#if (variable=="c2b1"):
#    d=0.01
#else :
#    d=0.04
#d1=str(d)
#G1.SetYTitle("number of jet per "+d1);
#G1.SetTitle("Study_of_difference_in_"+variable+"_truth_level_"+energy1+"tev")
#G1.SetTitle("cluster_"+files+"_"+variable+"_"+energy1+"tev_distribution_tGEN_nonu_vs_detector_level")
#mg.SetTitle("raw_"+variable+"_"+energy1+"tev_"+energy1_cut+"_compare_to_"+energy2_cut+"GeV_eff; signal efficiency; 1 - background efficiency")
#mg.SetTitle("cluster_"+variable+"_"+energy1+"tev_eff_fixed_width_to_"+fixed_width1+"GeV_tt_qq ; signal efficiency; 1 - background efficiency")
        mg.SetTitle("cluster_"+variable+"_"+str(energy_array[1][i])+"tev_eff_fixed_width_to_"+str(width_array[1][i])+"GeV_"+signal_we_want[j]+"_qq; signal efficiency; 1 - background efficiency")
        mg.Draw("ALP")
#mg.GetXaxis().SetLabelOffset(999)
#mg.GetXaxis().SetLabelize(0)
        h=min(G1.GetHistogram().GetMinimum(),G2.GetHistogram().GetMinimum(),G3.GetHistogram().GetMinimum())
        l=max(G1.GetHistogram().GetMaximum(),G2.GetHistogram().GetMaximum(),G3.GetHistogram().GetMaximum())
        mg.GetYaxis().SetRangeUser(h-0.01,l+0.06)
#G1.GetXaxis().SetRangeUser(0,1)
#G1.GetYaxis().SetRangeUser(0.73,1.5)
#G1.GetYaxis().SetRangeUser(0,1.5)


#t = TText()
#t.SetTextAlign(20)
#t.SetTextSize(0.030)
#t.SetTextFont(60)
#t.SetTextColor(4)
#label=["20*20","5*5","1*1"]
#for i in range(3):
#    t.DrawText(i+1,-0.03,label[i])

        leg.AddEntry("","signal:z'->"+signal_we_want[j],"")
        leg.AddEntry("","background:z'->qq","")

#leg.AddEntry(G1,"z'->tt(truth-level)","l")
#leg.AddEntry(G2,"z'->qq(truth-level)","l")
#leg.AddEntry(G3,"z'->tt(detector-level)","l")
#leg.AddEntry(G4,"z'->qq(detector-level)","l")
#leg.AddEntry(G1,"z'->tt(truth-level-20*20)","l")
#leg.AddEntry(G2,"z'->tt(truth-level-5*5)","l")
#leg.AddEntry(G3,"z'->tt(truth-level-1*1)","l")
#leg.AddEntry(G4,"z'->qq(truth-level-20*20)","l")
#leg.AddEntry(G5,"z'->qq(truth-level-5*5)","l")
#leg.AddEntry(G6,"z'->qq(truth-level-1*1)","l")

        leg.AddEntry(G1,"20*20","l")
        leg.AddEntry(G2,"5*5","l")
        leg.AddEntry(G3,"1*1","l")

#leg.AddEntry("G4","#sqrt{s}=40TeV","l")

        c.Draw()
        leg.Draw()
        c.Print("cluster_"+variable+"_"+str(energy_array[1][i])+"tev_eff_fixed_width_to_"+str(width_array[1][i])+"GeV_"+signal_we_want[j]+"_qq.pdf")
#c.Print("cluster_"+variable+"_"+energy1+"tev_eff_fixed_width_to_"+fixed_width1+"GeV_tt_qq.pdf")
#c.Print("Study_of_difference_in_"+variable+"_truth_level_"+energy1+"tev.pdf")
#c.Print("cluster_"+files+"_"+variable+"_"+energy1+"tev_distribution_tGEN_nonu_vs_detector_level.pdf")
#c.Print("raw_"+variable+"_"+energy1+"tev_"+energy1_cut+"_compare_to_"+energy2_cut+"GeV_eff.pdf")




