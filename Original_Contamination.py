#========Data-MC comparison for Electron=====#
import ROOT
import os
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
'''
files1="009"
files2="010"
files3="012"
files_array=(files1,files2,files3)
energy_array=("f",[5,10,20,40])
variable=("tau21","tau32","c2b1")
print variable[0],variable[1],variable[2]
print files_array[0],files_array[1],files_array[2]
variables=("h_mass_mmdt")
for j in range(0,3):
    for m in range(0,4):
        if(energy_array[1][m]<20):
            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200_no_UOF.root", 'r')
            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins_no_UOF_new_75%.root", 'r')
        if(energy_array[1][m]>=20):
            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200_no_UOF.root", 'r')
            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[j]+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins_no_UOF_new_75%.root", 'r')
        
        
        h1 = f1.Get(variables[0])
        h2 = f2.Get(variables[0])

'''
'''
f1= ROOT.TFile.Open=("/Users/ms08962476/NTU_TB/root_plot_original_Contamination/Run177_50GeV_Ele_result.root",'r')
f2= ROOT.TFile.Open=("/Users/ms08962476/NTU_TB/root_plot_original_Contamination/MC_50GeV_Ele_result.root",'r')
print f1,f2
h1 = f1.Get("layer_8_9_10_E7devE19")
h2 = f2.Get("layer_8_9_10_E7devE19")
'''

Found_energy=("50","80","100","150")
variable=("layer_8_9_10_E7devE19","layer_9_10_11_E7devE19","layer_9_E7devE19","layer_10_E7devE19")
print type(variable)
for var_number in range(4):
    for found_energy in range(3):
        for Run_number in range(500):
            if(os.path.exists("/Users/ms08962476/NTU_TB/root_plot_original_Contamination/Run"+str(Run_number)+"_"+str(Found_energy[found_energy])+"GeV_Ele_result.root")==1):
                print 'input data filename:/Users/ms08962476/NTU_TB/root_plot_original_Contamination/Run'+str(Run_number)+'_'+(Found_energy[found_energy])+'GeV_Ele_result.root'
                print 'input MC   filename:/Users/ms08962476/NTU_TB/root_plot_original_Contamination/MC_'+str(Found_energy[found_energy])+'GeV_Ele_result.root'
                f1= ROOT.TFile.Open=("/Users/ms08962476/NTU_TB/root_plot_original_Contamination/Run"+str(Run_number)+"_"+str(Found_energy[found_energy])+"GeV_Ele_result.root",'r')
                f2= ROOT.TFile.Open=("/Users/ms08962476/NTU_TB/root_plot_original_Contamination/MC_"+str(Found_energy[found_energy])+"GeV_Ele_result.root",'r')
                print type(variable[var_number])
                h1 = f1.Get(variable[var_number])
                h2 = f2.Get("h_")
                Data_Entries=h1.GetEntries()
                MC_Entries  =h2.GetEntries()
                Scale_Factor=Data_Entries/MC_Entries
                h2.Scale(Scale_Factor)

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
                h1.SetLineStyle(1)
                h2.SetLineStyle(9)
                h1.SetTitle(variables[var])
                h2.SetTitle(variables[var])
                h1.SetXTitle("E7/E19")
                h2.SetXTitle("E7/E19")
                h1.SetYTitle("Event number")
                h2.SetYTitle("Event number")
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

                leg.AddEntry(h1,"Data"+str(Found_energy(found_energy))+"Ele","l")
    #leg.AddEntry(h1,"Z'(20TeV)#rightarrowW^{+}W^{-}#rightarrow2 jet","l")
                leg.AddEntry(h2,"Data"+str(Found_energy(found_energy))+"Ele","l")

                if(h1.GetBinContent(h1.GetMaximumBin())>h2.GetBinContent(h2.GetMaximumBin())):
                    h1.Draw("hist")
                    h2.Draw("histsame")
                else:
                    h2.Draw("hist")
                    h1.Draw("histsame")
                leg.Draw()
                c.Draw()
                c.Print("Run"+str(Run_number)+"_"+str(Found_energy(found_energy))+"Ele_MC_DATA_Comparison.eps")



