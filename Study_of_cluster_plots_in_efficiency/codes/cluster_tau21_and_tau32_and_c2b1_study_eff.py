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
from array import array
#---------------------------------------------Setting the parameters in
files1="009"
files2="010"
files3="012"
files_array=(files1,files2,files3)
energy_array=("f",[5,10,20,40])
xarray=array("f",[])
variable=("mass_mmdt","tau21","tau32","c2b1")
print variable[0],variable[1],variable[2]
print files_array[0],files_array[1],files_array[2]
l=9
p=1
#---------------------------------------------setting the hisotgram in and normalize
for k in range(2,3):
    if(variable[k]=="mass_mmdt"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
            
                h1 = f1.Get("h_mass_mmdt")
                h2 = f2.Get("h_mass_mmdt")
                print h1,h2
                print variable[k]
                print '1'
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                
                for o in range(101):
                    xarray.append(h1.Integral(0,0+o)/a)
                    yarray.append(1/(h2.Integral(0,0+o)/b))
                print xarray
                print yarray
                print xarrayErrors
                print yarrayErrors
                
                n=101
                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraphErrors(n,xarray,yarray,xarrayErrors,yarrayErrors)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(l)
                gr.SetMarkerSize(1)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("background rejection")
                gr.Draw()
                c.SetLogy()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_error.pdf")

    if(variable[k]=="tau21"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                print f1,f2
                h1 = f1.Get("h_"+variable[k]+"_b1")
                h2 = f2.Get("h_"+variable[k]+"_b1")
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                for q in range(101):
                    if (h2.Integral(0,q)==0):
                        continue
                    else:
                        break
                d=q
                print str(d)
                
                for o in range(101):
                    print h2.Integral(d,d+o)
                    xarray.append(h1.Integral(d,d+o)/a)
                    yarray.append(1/(h2.Integral(d,d+o)/b))
                
                n=101-d

                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraph(n,xarray,yarray)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(l)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("background rejection")
                gr.Draw()
                c.SetLogy()

                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_Tra.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_Tra.pdf")

                  

    elif(variable[k]=="tau32"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhit_0.5GeV_3.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhit_0.5GeV_3.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbar%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhit_0.5GeV_3.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_mode0_trawhit_0.5GeV_3.root", 'r')
                h1 = f1.Get("h_"+variable[k]+"_b1")
                h2 = f2.Get("h_"+variable[k]+"_b1")
                print h1,h2
                         
                         
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                M=h1.GetMaximumBin()
                L=M
                R=M
                for Q in range(101):

                    print 'next-step'
                    print Q
                    
                    print str(h1.GetBinContent(L-1))
                    print str(h1.GetBinContent(R+1))
                        #---------------------------
                    if(h1.Integral(R+2,100)!=0 and h2.Integral(R+2,100)==0):
                        ratio_BinContent_2=9999
                        print 'this bin is zero, after:no background'
                    elif(h1.Integral(R+2,100)==0 and h2.Integral(R+2,100)==0):
                        ratio_BinContent_2=-1
                        print 'this bin is zero, after:no signal and background'
                    elif(h1.Integral(R+2,100)!=0 and h2.Integral(R+2,100)!=0):
                        ratio_BinContent_2=h1.Integral(R+2,100)/h2.Integral(R+2,100)
                        print 'this bin is zero'
                    elif(h1.Integral(0,L-2)!=0 and h2.Integral(0,L-2)==0):
                        ratio_BinContent_1=9999
                        print 'this bin is zero, before:no background'
                    elif(h1.Integral(0,L-2)==0 and h2.Integral(0,L-2)==0):
                        ratio_BinContent_1=-1
                        print 'this bin is zero, before:no signal and background'
                    elif(h1.Integral(0,L-2)!=0 and h2.Integral(0,L-2)!=0):
                        ratio_BinContent_1=h1.Integral(0,L-2)/h2.Integral(0,L-2)
                        print 'this bin is zero'
                                                                        #---------------------------

                        #---------------------------
                        if(h1.GetBinContent(L-1)>h1.GetBinContent(R+1)):
                            if(h1.GetBinContent(R+1)==0):
                                if(h1.GetBinContent(L-1)>ratio_BinContent_2):
                                    print'YA1'
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    print h1.Integral(L-1,R), a
                                    print yarray
                                    L=L-1
                                    R=R
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----1'
                                if(h1.GetBinContent(L-1)<ratio_BinContent_2):
                                    print 'YA1'
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/((h2.Integral(L,R+1))/b))
                                    print h1.Integral(L,R+1), a
                                    print yarray
                                    L=L
                                    R=R+1
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----2'
                                if(h1.GetBinContent(L-1)==ratio_BinContent_2):
                                    print 'YA1'
                                    Random=randint(1,3)
                                    if(Random==1):
                                        xarray.append(h1.Integral(L-1,R)/a)
                                        yarray.append(1/(h2.Integral(L-1,R)/b))
                                        print h1.Integral(L-1,R), a
                                        print yarray
                                        C=h2.Integral(L-1,R)
                                        L=L-1
                                        R=R
                                        print str(L)
                                        print str(R)
                                        print str(h1.GetBinContent(L))
                                        print str(h1.GetBinContent(R))
                                        print '----3'
                                    if(Random==2):
                                        xarray.append(h1.Integral(L,R+1)/a)
                                        yarray.append(1/(h2.Integral(L,R+1)/b))
                                        print h1.Integral(L,R+1), a
                                        print yarray
                                        C=h2.Integral(L,R+1)
                                        L=L
                                        R=R+1
                                        print str(L)
                                        print str(R)
                                        print str(h1.GetBinContent(L))
                                        print str(h1.GetBinContent(R))
                                        print '----4'
                        #--------------------------------
                        else:
                            xarray.append(h1.Integral(L-1,R)/a)
                            yarray.append(1/(h2.Integral(L-1,R)/b))
                            print h1.Integral(L-1,R), a
                            print yarray
                            C=h2.Integral(L-1,R)
                            L=L-1
                            R=R
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----5'

                    elif(h1.GetBinContent(L-1)<h1.GetBinContent(R+1)):
                        #---------------------------
                        if(h1.GetBinContent(L-1)==0):
                            if(h1.GetBinContent(R+1)>ratio_BinContent_1):
                                'YA'
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                print h1.Integral(L,R+1), a
                                print yarray
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----6'
                            if(h1.GetBinContent(R+1)<ratio_BinContent_1):
                                'YA'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                print h1.Integral(L-1,R), a
                                print yarray
                                L=L-1
                                R=R
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----7'
                            if(h1.GetBinContent(R+1)==ratio_BinContent_1):
                                print 'YAA'
                                Random=randint(1,3)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    print h1.Integral(L-1,R), a
                                    print yarray
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----8'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    print h1.Integral(L,R+1), a
                                    print yarray
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----9'
                        #---------------------------
                        else:
                            xarray.append(h1.Integral(L,R+1)/a)
                            yarray.append(1/(h2.Integral(L,R+1)/b))
                            print h1.Integral(L,R+1), a
                            print yarray
                            C=h2.Integral(L,R+1)
                            L=L
                            R=R+1
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----10'
                    #-----------------------------------
                    elif(h1.GetBinContent(L-1)==h1.GetBinContent(R+1)):
                        if(h1.GetBinContent(L-1)==0 and h1.GetBinContent(R+1)==0):
                            if(ratio_BinContent_2>ratio_BinContent_1):
                                print 'YA3'
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                print h1.Integral(L,R+1), a
                                print yarray
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----11'
                            elif(ratio_BinContent_2<ratio_BinContent_1):
                                print 'YA3'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                print h1.Integral(L-1,R), a
                                print yarray
                                L=L-1
                                R=R
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----12'
                            elif(ratio_BinContent_2==ratio_BinContent_1):
                                print 'YA3'
                                Random=randint(1,3)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    print h1.Integral(L-1,R), a
                                    print yarray
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----13'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    print h1.Integral(L,R+1), a
                                    print yarray
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----14'

                        else:
                            Random=randint(1,3)
                            print Random
                            if(Random==1):
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                print h1.Integral(L-1,R), a
                                print yarray
                                C=h2.Integral(L-1,R)
                                L=L-1
                                R=R
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----14'
                            if(Random==2):
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                print h1.Integral(L,R+1), a
                                print yarray
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----15'
                    #------------------------------------------
                n=R-L
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraph(n,xarray,yarray)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(l)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("background rejection")
                gr.Draw()
                c.SetLogy()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("Try_raw_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New.root","RECREATE")
                gr.Write()
                c.Print("Try_raw_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New.pdf")

                                           


    elif(variable[k]=="c2b1"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqbar%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ww%rfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qq%rfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo.root", 'r')

                h1 = f1.Get("h_c2_b1")
                h2 = f2.Get("h_c2_b1")
                print h1,h2
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarrayErrors=array("f",[])
                yarrayErrors=array("f",[])
                for q in range(101):
                    if (h2.Integral(0,q)==0):
                        continue
                    else:
                        break
                d=q
                print str(d)
                
                for o in range(101):
                    print h2.Integral(d,d+o)
                    xarray.append(h1.Integral(d,d+o)/a)
                    yarray.append(1/(h2.Integral(d,d+o)/b))
                        
                n=101-d

                
                if(files_array[i]=="009"):
                    Color=2
                    l=4
                if(files_array[i]=="010"):
                    Color=3
                    l=21
                if(files_array[i]=="012"):
                    Color=4
                    l=22
                Color1=str(Color)
                
                
                c = TCanvas("c1", "c1",0,0,500,500)
                
                
                gr = TGraph(n,xarray,yarray)
                gr.SetLineColor(Color)
                gr.SetLineWidth(1)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(l)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("background rejection")
                gr.Draw()
                c.SetLogy()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_Tra.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_Tra.pdf")

'''M=h1.GetMaximumBin()
    L=M
        R=M
            for Q in range(101):
                if(h1.GetBinContent(L-1)<h1.GetBinContent(R+1)):
                    xarray.append(h1.Integral(L,R+1)/a)
                        yarray.append(1/(h2.Integral(L,R+1)/b))
                        print h2.Integral(L,R+1), b
                        print yarray
                        L=L
                        R=R+1
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----1'
                    if(h1.GetBinContent(L-1)>h1.GetBinContent(R+1)):
                        xarray.append(h1.Integral(L-1,R)/a)
                        yarray.append(1/(h2.Integral(L-1,R)/b))
                        print h2.Integral(L-1,R), b
                        print yarray
                        L=L-1
                        R=R
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----2'
                if(h1.GetBinContent(L-1)==h1.GetBinContent(R+1)):
                    Random=randint(1,3)
                        if (Random==1):
                            xarray.append(h1.Integral(L-1,R)/a)
                            yarray.append(1/(h2.Integral(L-1,R)/b))
                            print h2.Integral(L-1,R), b
                            print yarray
                            L=L-1
                            R=R
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----3'
                    if(Random==2):
                        if(h1.GetBinContent(L-1)<h1.GetBinContent(R+1)):
                            xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                print h2.Integral(L,R+1), b
                                print yarray
                                L=L
                                R=R+1
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----4'
                    if(h1.GetBinContent(R+1)==0):
                        xarray.append(h1.Integral(L-1,R)/a)
                        yarray.append(1/(h2.Integral(L-1,R)/b))
                        print h2.Integral(L-1,R), b
                        print yarray
                        L=L-1
                        R=R
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----5'
                        continue
                    if(h1.GetBinContent(L-1)==0):
                        xarray.append(h1.Integral(L,R+1)/a)
                        yarray.append(1/(h2.Integral(L,R+1)/b))
                        print h2.Integral(L,R+1), b
                        print yarray
                        L=L
                        R=R+1
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----6'
                        continue
                            print str(h1.GetBinContent(L-1))
                                print str(h1.GetBinContent(R+1))
                                    n=101    '''

