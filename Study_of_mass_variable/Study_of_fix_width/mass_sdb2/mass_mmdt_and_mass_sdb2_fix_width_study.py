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
variable="mass_sdb2"
signal_we_want="ww"
print energy_array[1][0]
#---------------------------------------------setting the hisotgram in and normalize
for m in range(0,4):
    for i in range(0,3):
        if(variable=="mass_mmdt"):
            if(signal_we_want=="tt"):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_cluster_0.5GeV_tcalo_all.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_cluster_0.5GeV_tcalo_all.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_cluster_0.5GeV_tcalo_all.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_cluster_0.5GeV_tcalo_all.root", 'r')
            if(signal_we_want=="ww"):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_cluster_0.5GeV_tcalo_all.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_cluster_0.5GeV_tcalo_all.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_cluster_0.5GeV_tcalo_all.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_cluster_0.5GeV_tcalo_all.root", 'r')
        if(variable=="mass_sdb2"):
            if(signal_we_want=="tt"):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo80_for_mass_sdb2.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo80_for_mass_sdb2.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo80_for_mass_sdb2.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo80_for_mass_sdb2.root", 'r')
            if(signal_we_want=="ww"):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo80_for_mass_sdb2.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo80_for_mass_sdb2.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo80_for_mass_sdb2.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo80_for_mass_sdb2.root", 'r')
        print f1
        h1 = f1.Get("h_mass_sdb2")
        h2 = f2.Get("h_mass_sdb2")
        print h1,h2
        h1.Scale(1.0/h1.Integral())
        h2.Scale(1.0/h2.Integral())
#------------------------------------------------
#h1.Sumw2()
#h2.Sumw2()
#overlap=0

#for ib in range(50):
#    if(h1.GetBinContent(ib) < h2.GetBinContent(ib)):
#        overlap=overlap+h1.GetBinContent(ib)
#    else:
#        overlap=overlap+h2.GetBinContent(ib)

#print overlap*100
#e=round(overlap*100,0)
#d=str(e)
#print d
#U = MannWhitneyUtest.mannWU(h1, h2)
#U_print = min (1-U, U)
#U_print_2_decimal=round(U_print,2)
#a=str(U_print_2_decimal)
#-------------------------------------------setting the starting point
        if(variable=="mass_sdb2"):
            if (signal_we_want=="tt"):
                if(energy_array[1][m]==5):
                    start_point=160
                if(energy_array[1][m]==10):
                    start_point=200
                if(energy_array[1][m]==20):
                    start_point=280
                if(energy_array[1][m]==40):
                    start_point=310
        if(variable=="mass_sdb2"):
            if (signal_we_want=="ww"):
                if(energy_array[1][m]==5):
                    start_point=80
                if(energy_array[1][m]==10):
                    start_point=105
                if(energy_array[1][m]==20):
                    start_point=180
                if(energy_array[1][m]==40):
                    start_point=180
        if(variable=="mass_mmdt"):
            if (signal_we_want=="tt"):
                if(energy_array[1][m]==5):
                    start_point=150
                if(energy_array[1][m]==10):
                    start_point=150
                if(energy_array[1][m]==20):
                    start_point=150
                if(energy_array[1][m]==40):
                    start_point=150
        if(variable=="mass_mmdt"):
            if (signal_we_want=="ww"):
                if(energy_array[1][m]==5):
                    start_point=60
                if(energy_array[1][m]==10):
                    start_point=60
                if(energy_array[1][m]==20):
                    start_point=60
                if(energy_array[1][m]==40):
                    start_point=60
#-------------------------------------------fixed width setting
        if(variable=="mass_sdb2"):
            if(energy_array[1][m]==5):
                fixed_width=40
            if(energy_array[1][m]==10):
                fixed_width=40
            if(energy_array[1][m]==20):
                fixed_width=40
            if(energy_array[1][m]==40):
                fixed_width=40
        if(variable=="mass_mmdt"):
            if(energy_array[1][m]==5):
                fixed_width=40
            if(energy_array[1][m]==10):
                fixed_width=40
            if(energy_array[1][m]==20):
                fixed_width=40
            if(energy_array[1][m]==40):
                fixed_width=40
#-------------------------------------------starting analyze the ROC curve

        a=h1.Integral()
        b=h2.Integral()
        xarray=array("f",[])
        yarray=array("f",[])

        for k in range((start_point/5)-(fixed_width/10-1),(start_point/5)-(fixed_width/10-1)+9):
            xarray.append(h1.Integral(k,k+(fixed_width/5)-1)/a)
        #xarray.append(h1.Integral(0,0+i)/a)

#karray=array("f",[])
#for k in range(100):
#    karray.append(h1.Integral(0,0+k)/a)
#print karray
            yarray.append(1-h2.Integral(k,k+(fixed_width/5)-1)/b)
        #yarray.append(1-h2.Integral(0,0+j)/b)
        print xarray
        print yarray
#------------------------------------------set pictures and see the point of tex in
#energy_cut= 0.25
#energy1_cut=str(energy_cut)
        n=9
        efficiency_number=1
        efficiency_number1=str(efficiency_number)
        if(files_array[i]=="009"):
            Color=2
        if(files_array[i]=="010"):
            Color=3
        if(files_array[i]=="012"):
            Color=4
        Color1=str(Color)


        c = TCanvas("c1", "c1",0,0,500,500)
#gStyle.SetOptStat(0)
#leg = TLegend(0.1,0.6,0.35,0.9)
#leg = TLegend(0.1,0.6,0.4,0.9)
#leg.SetFillColor(0)
#eg.SetFillStyle(0)
#leg.SetTextSize(0.04)
#leg.SetBorderSize(2)
#h1.SetLineColor(2)
#h1.SetLineWidth(3)
#h2.SetLineColor(1)
#h2.SetLineWidth(3)
#leg.AddEntry("","#sqrt{s}="+energy1+"TeV","")
#leg.AddEntry(h1,"z'->ww","l")
#leg.AddEntry(h2,"z'->qq","l")
#leg.AddEntry("","overlapped=","")
#leg.AddEntry("",d+"%","")

#if(h1.GetBinContent(h1.GetMaximumBin())>h2.GetBinContent(h2.GetMaximumBin())):
#        h1.Draw("hist")
#        h2.Draw("histsame")
#else:
#        h2.Draw("hist")
#        h1.Draw("histsame")


#if (files="r009"):
#d=2,e=2,f=2
#if (files="r010"):
#    d=3,e=6,f=3
#if (files="r012"):
#    d=4,e=7,f=4


        gr = TGraph(n,xarray,yarray)
        gr.SetLineColor(Color)
        gr.SetLineWidth(2)
        gr.SetLineStyle(1)
        gr.SetMarkerColor(4)
        gr.SetMarkerStyle(3)
        gr.SetTitle("cluster_r"+str(files_array[i])+"_"+variable+"_"+str(energy_array[1][m])+"tev_eff_fix_width_to_"+str(fixed_width)+"GeV_"+signal_we_want)
#gr.SetTitle("raw_"+files+"_"+variable+"_"+energy1+"tev_"+energy1_cut+"GeV_eff")
        gr.GetXaxis().SetTitle("signal_efficiency")
        gr.GetXaxis().SetTitleColor(4)
        gr.GetYaxis().SetTitle("1-background_efficiency")
        gr.Draw()


        d=start_point
        latex= TLatex(gr.GetX()[0],gr.GetY()[0],str(d+0*5)+"(GeV)")
        latex1=TLatex(gr.GetX()[1],gr.GetY()[1],str(d+1*5))
        latex2=TLatex(gr.GetX()[2],gr.GetY()[2],str(d+2*5))
        latex3=TLatex(gr.GetX()[3],gr.GetY()[3],str(d+3*5))
        latex4=TLatex(gr.GetX()[4],gr.GetY()[4],str(d+4*5))
        latex5=TLatex(gr.GetX()[5],gr.GetY()[5],str(d+5*5))
        latex6=TLatex(gr.GetX()[6],gr.GetY()[6],str(d+6*5))
        latex7=TLatex(gr.GetX()[7],gr.GetY()[7],str(d+7*5))
        latex8=TLatex(gr.GetX()[8],gr.GetY()[8],str(d+8*5))


        latex.SetTextSize(0.02)
        latex1.SetTextSize(0.02)
        latex2.SetTextSize(0.02)
        latex3.SetTextSize(0.02)
        latex4.SetTextSize(0.02)
        latex5.SetTextSize(0.02)
        latex6.SetTextSize(0.02)
        latex7.SetTextSize(0.02)
        latex8.SetTextSize(0.02)

        gr.GetListOfFunctions().Add(latex)
        gr.GetListOfFunctions().Add(latex1)
        gr.GetListOfFunctions().Add(latex2)
        gr.GetListOfFunctions().Add(latex3)
        gr.GetListOfFunctions().Add(latex4)
        gr.GetListOfFunctions().Add(latex5)
        gr.GetListOfFunctions().Add(latex6)
        gr.GetListOfFunctions().Add(latex7)
        gr.GetListOfFunctions().Add(latex8)


        latex.Draw()
        latex1.Draw()
        latex2.Draw()
        latex3.Draw()
        latex4.Draw()
        latex5.Draw()
        latex6.Draw()
        latex7.Draw()
        latex8.Draw()
#-----------------------------------------out of the rootfiles and pdf files


#leg.AddEntry("","MannWhitneyUtest:","")
#leg.AddEntry("",a,"")
#leg.Draw()
#c.Draw()

        f=TFile("cluster_r"+str(files_array[i])+"_"+variable+"_"+str(energy_array[1][m])+"tev_eff_"+efficiency_number1+"_width_"+str(fixed_width)+"GeV_fix_"+signal_we_want+".root","RECREATE")
#f=TFile("raw_"+files+"_"+variable+"_"+energy1+"tev_"+energy1_cut+"GeV_eff.root","RECREATE");
        gr.Write()


#leg.Draw()
        c.Print("cluster_r"+str(files_array[i])+"_"+variable+"_"+str(energy_array[1][m])+"tev_eff_"+efficiency_number1+"_width_"+str(fixed_width)+"GeV_fix_"+signal_we_want+".pdf")
#c.Print("raw_"+files+"_"+variable+"_"+energy1+"tev_"+energy1_cut+"GeV_eff.pdf")

#where h1 and h2 are TH1s

