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
variable=("mass_mmdt","mass_sdb2")
signal_we_want=("ww","tt")
#---------------------------------------------setting the hisotgram in and normalize
for k in range(0,2):
    for l in range(0,2):
        for m in range(0,4):
            for i in range(0,3):
                if(variable[k]=="mass_mmdt"):
                    if(signal_we_want[l]=="tt"):
                        if(energy_array[1][m]<20):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_mmdt")
                            h2 = f2.Get("h_mass_mmdt")

                        if(energy_array[1][m]>=20):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_1200_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_mmdt")
                            h2 = f2.Get("h_mass_mmdt")

                    if(signal_we_want[l]=="ww"):
                        if(energy_array[1][m]<20):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_800_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_800_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_mmdt")
                            h2 = f2.Get("h_mass_mmdt")

                        if(energy_array[1][m]>=20):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_800_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_mmdt_800_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_mmdt")
                            h2 = f2.Get("h_mass_mmdt")

                if(variable[k]=="mass_sdb2"):
                    if(signal_we_want[l]=="tt"):
                        if(energy_array[1][m]==5):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_1200_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_1200_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_sdb2")
                            h2 = f2.Get("h_mass_sdb2")
                        if(energy_array[1][m]==10):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_1200_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_1200_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_sdb2")
                            h2 = f2.Get("h_mass_sdb2")
                        if(energy_array[1][m]==20):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_2400_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_2400_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_sdb2")
                            h2 = f2.Get("h_mass_sdb2")
                        if(energy_array[1][m]==40):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_2400_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_2400_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_sdb2")
                            h2 = f2.Get("h_mass_sdb2")
                    if(signal_we_want[l]=="ww"):
                        if(energy_array[1][m]==5):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_800_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_800_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_sdb2")
                            h2 = f2.Get("h_mass_sdb2")
                        if(energy_array[1][m]==10):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_800_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_800_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_sdb2")
                            h2 = f2.Get("h_mass_sdb2")
                        if(energy_array[1][m]==20):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_1600_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_1600_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_sdb2")
                            h2 = f2.Get("h_mass_sdb2")
                        if(energy_array[1][m]==40):
                            f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_1600_no_UOF.root", 'r')
                            f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_for_sdb2_1600_no_UOF.root", 'r')
                            h1 = f1.Get("h_mass_sdb2")
                            h2 = f2.Get("h_mass_sdb2")
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
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
        #-------------------------------------------fixed width setting
                #if(variable=="mass_sdb2"):
                #   if(energy_array[1][m]==5):
                #       fixed_width=40
                #    if(energy_array[1][m]==10):
                #        fixed_width=40
                #    if(energy_array[1][m]==20):
                #        fixed_width=40
                #    if(energy_array[1][m]==40):
                #        fixed_width=40
                #if(variable=="mass_mmdt"):
                #    if(energy_array[1][m]==5):
                #        fixed_width=40
                #    if(energy_array[1][m]==10):
                #        fixed_width=40
                #   if(energy_array[1][m]==20):
                #         fixed_width=40
                #    if(energy_array[1][m]==40):
                #        fixed_width=40
        #-------------------------------------------starting analyze the ROC curve

                a=h1.Integral()
                b=h2.Integral()

                numbin=h1.GetXaxis().GetNbins()
                print str(numbin)
                for p in range(1,numbin):
                    if (h1.Integral(1,p)<(h1.Integral(1,numbin)/2)<h1.Integral(1,p+1)):
                        break
                print str((p+1)*5)

                if(variable[k]=="mass_sdb2"):
                    if (signal_we_want[l]=="tt"):
                        if(energy_array[1][m]==5):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==10):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==20):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==40):
                            central_energy=(p+1)*5-20
                if(variable[k]=="mass_sdb2"):
                    if (signal_we_want[l]=="ww"):
                        if(energy_array[1][m]==5):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==10):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==20):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==40):
                            central_energy=(p+1)*5-20
                if(variable[k]=="mass_mmdt"):
                    if (signal_we_want[l]=="tt"):
                        if(energy_array[1][m]==5):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==10):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==20):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==40):
                            central_energy=(p+1)*5-20
                if(variable[k]=="mass_mmdt"):
                    if (signal_we_want[l]=="ww"):
                        if(energy_array[1][m]==5):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==10):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==20):
                            central_energy=(p+1)*5-20
                        if(energy_array[1][m]==40):
                            central_energy=(p+1)*5-20

                for j in range(0,9):
                    xarray=array("f",[])
                    yarray=array("f",[])
                    for d in range(central_energy/5+j-7,central_energy/5+j+1):
                        
                        xarray.append(h1.Integral(d,(central_energy/5+central_energy/5+1+2*j)-d)/a)
                #xarray.append(h1.Integral(0,0+i)/a)
                        yarray.append(1/(h2.Integral(d,(central_energy/5+central_energy/5+1+2*j)-d)/b))
                        print d , (central_energy/5+central_energy/5+1+2*j)-d

                    print 'From very central'+str(central_energy)
                    print 'central_energy'+str(central_energy+5*j)
        #karray=array("f",[])
        #for k in range(100):
        #    karray.append(h1.Integral(0,0+k)/a)
        #print karray
                #yarray.append(1-h2.Integral(0,0+j)/b)
        #------------------------------------------set pictures and see the point of tex in
        #energy_cut= 0.25
        #energy1_cut=str(energy_cut)
                    n=8
                    central_energy1=str(central_energy+5*j)
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
                    gr.SetMarkerSize(0)
                    gr.SetTitle("cluster_r"+str(files_array[i])+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_eff_fix_central_to_"+str(central_energy+5*j)+"GeV_"+signal_we_want[l]+"_qq")
            #gr.SetTitle("raw_"+files+"_"+variable+"_"+energy1+"tev_"+energy1_cut+"GeV_eff")
                    gr.GetXaxis().SetTitle("signal_efficiency")
                    gr.GetXaxis().SetTitleColor(1)
                    gr.GetYaxis().SetTitle("background_efficiency LOG scale")
                    gr.Draw()
                    c.SetLogy()
            #-----------------------------------------out of the rootfiles and pdf files


            #leg.AddEntry("","MannWhitneyUtest:","")
            #leg.AddEntry("",a,"")
            #leg.Draw()
            #c.Draw()

                    f=TFile("A_Cluster_"+str(files_array[i])+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_eff_"+str(efficiency_number1)+"_central_fix_at_"+central_energy1+"GeV_"+str(signal_we_want[l])+"_qq_log_no_UOF.root","RECREATE")
            #f=TFile("raw_"+files+"_"+variable+"_"+energy1+"tev_"+energy1_cut+"GeV_eff_no_UOF.root","RECREATE");
                    gr.Write()
#c.Print("A_Cluster_"+str(files_array[i])+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_eff_"+str(efficiency_number1)+"_central_fix_at_"+central_energy1+"GeV_"+str(signal_we_want[l])+"_qq_log.pdf")

            #leg.Draw()
#c.Print("A_Cluster_"+str(files_array[i])+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_eff_"+str(efficiency_number1)+"_central_fix_at_"+central_energy1+"GeV_"+str(signal_we_want[l])+"_qq.pdf")
            #c.Print("raw_"+files+"_"+variable+"_"+energy1+"tev_"+energy1_cut+"GeV_eff.pdf")

            #where h1 and h2 are TH1s

