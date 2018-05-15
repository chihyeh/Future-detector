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
variable=("tau21","tau32","c2b1")
print variable[0],variable[1],variable[2]
print files_array[0],files_array[1],files_array[2]
l=9
p=1
#---------------------------------------------setting the hisotgram in and normalize
for k in range(0,3):
    if(variable[k]=="tau21"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_ww.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_ww.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_ww.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_ww.root", 'r')
                
                h1 = f1.Get("h_"+variable[k]+"_b1")
                h2 = f2.Get("h_"+variable[k]+"_b1")

                h1_Max_y=h1.GetBinContent(h1.GetMaximumBin())
                h2_Max_y=h2.GetBinContent(h2.GetMaximumBin())
                print h1_Max_y,h2_Max_y
                Maximum_in_histogram=max(h1_Max_y,h2_Max_y)

                h3 = TH1F("h3","Ratio histogram",100,0,1)
                h3=h1.Clone("h3")
                h3.Divide(h2)

                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                  
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                ratio_BinContent_1=0
                ratio_BinContent_2=0
                M=h3.GetMaximumBin()
                L=M
                R=M
                print M
                for Q in range(101):
                    print '==============================================='
                    print 'signal total'+str(a)
                    print 'signal:'+str(h1.Integral(L,R))
                    print 'background:'+str(h2.Integral(L,R))
                    print 'Ratio:'+str(h3.Integral(L,R))
                    print 'Ratio_total:'+str(h3.Integral())
                    print str(h3.GetBinContent(L-1))
                    print str(h3.GetBinContent(R+1))
                    print '==============================================='
                    print 'next-step'
                    #---------------------------
                    if(h1.Integral(R+2,100)!=0 and h2.Integral(R+2,100)==0):
                        ratio_BinContent_2=9999
                        print 'this bin is zero, after:no background'
                    if(h1.Integral(R+2,100)==0 and h2.Integral(R+2,100)!=0):
                        ratio_BinContent_2=0
                        print 'this bin is zero, after:no signal'
                    if(h1.Integral(R+2,100)==0 and h2.Integral(R+2,100)==0):
                        ratio_BinContent_2=-1
                        print 'this bin is zero, after:no signal and background'
                    if(h1.Integral(R+2,100)!=0 and h2.Integral(R+2,100)!=0):
                        ratio_BinContent_2=h1.Integral(R+2,100)/h2.Integral(R+2,100)
                        print 'this bin is not zero : right'
                    
                    if(h1.Integral(0,L-2)!=0 and h2.Integral(0,L-2)==0):
                        ratio_BinContent_1=9999
                        print 'this bin is zero, before:no background'
                    if(h1.Integral(0,L-2)==0 and h2.Integral(0,L-2)!=0):
                        ratio_BinContent_1=0
                        print 'this bin is zero, before:no signal'
                    if(h1.Integral(0,L-2)==0 and h2.Integral(0,L-2)==0):
                        ratio_BinContent_1=-1
                        print 'this bin is zero, before:no signal and background'
                    if(h1.Integral(0,L-2)!=0 and h2.Integral(0,L-2)!=0):
                        ratio_BinContent_1=h1.Integral(0,L-2)/h2.Integral(0,L-2)
                        print 'this bin is not zero : left'
                    #---------------------------
                    
                    #---------------------------
                    if(h3.GetBinContent(L-1)>h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(R+1)==0):
                            if(h3.GetBinContent(L-1)>ratio_BinContent_2):
                                print'YA4'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(L-1)<ratio_BinContent_2):
                                print 'YA4'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(L-1)==ratio_BinContent_2):
                                print 'YA4'
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                            if(h1.Integral(L,R)>a/2):
                                print str(h1.Integral(L,R))+'More than half'
                                print '================================================fuck=============================================================='
                                print '=========================================================================================================================='
                                break
                    #---------------------------
                    if(h3.GetBinContent(L-1)<h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(L-1)==0):
                            if(h3.GetBinContent(R+1)>ratio_BinContent_1):
                                print'YA5'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(R+1)<ratio_BinContent_1):
                                'YA5'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(R+1)==ratio_BinContent_1):
                                print 'YA5'
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break

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
                            if(h1.Integral(L,R)>a/2):
                                print str(h1.Integral(L,R))+'More than half'
                                print '================================================fuck=============================================================='
                                print '=========================================================================================================================='
                                break
        #-----------------------------------
                    if(h3.GetBinContent(L-1)==h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(L-1)==0 and h3.GetBinContent(R+1)==0):
                            if(ratio_BinContent_2>ratio_BinContent_1):
                                print 'YA6'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            elif(ratio_BinContent_2<ratio_BinContent_1):
                                print 'YA6'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break

                            elif(ratio_BinContent_2==ratio_BinContent_1):
                                print 'YA6'
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break

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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
                    
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                        #------------------------------------------
                n=R-L
                print n
                
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
                gr.SetLineWidth(3)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1/background_efficiency")
                gr.Draw()
                c.SetLogy()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_50%.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_50%.pdf")
                  
                  

    elif(variable[k]=="tau32"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_tt.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_tt.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_tt.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_tt.root", 'r')
                h1 = f1.Get("h_"+variable[k]+"_b1")
                h2 = f2.Get("h_"+variable[k]+"_b1")
                print h1,h2

                h1_Max_y=h1.GetBinContent(h1.GetMaximumBin())
                h2_Max_y=h2.GetBinContent(h2.GetMaximumBin())
                print h1_Max_y,h2_Max_y
                Maximum_in_histogram=max(h1_Max_y,h2_Max_y)
                
                h3 = TH1F("h3","Ratio histogram",100,0,1)
                h3=h1.Clone("h3")
                h3.Divide(h2)
                
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                ratio_BinContent_1=0
                ratio_BinContent_2=0
                M=h3.GetMaximumBin()
                L=M
                R=M
                print M
                for Q in range(101):
                    print '==============================================='
                    print 'signal total'+str(a)
                    print 'signal:'+str(h1.Integral(L,R))
                    print 'background:'+str(h2.Integral(L,R))
                    print 'Ratio:'+str(h3.Integral(L,R))
                    print 'Ratio_total:'+str(h3.Integral())
                    print str(h3.GetBinContent(L-1))
                    print str(h3.GetBinContent(R+1))
                    print '==============================================='
                    print 'next-step'
                    #---------------------------
                    if(h1.Integral(R+2,100)!=0 and h2.Integral(R+2,100)==0):
                        ratio_BinContent_2=9999
                        print 'this bin is zero, after:no background'
                    if(h1.Integral(R+2,100)==0 and h2.Integral(R+2,100)!=0):
                        ratio_BinContent_2=0
                        print 'this bin is zero, after:no signal'
                    if(h1.Integral(R+2,100)==0 and h2.Integral(R+2,100)==0):
                        ratio_BinContent_2=-1
                        print 'this bin is zero, after:no signal and background'
                    if(h1.Integral(R+2,100)!=0 and h2.Integral(R+2,100)!=0):
                        ratio_BinContent_2=h1.Integral(R+2,100)/h2.Integral(R+2,100)
                        print 'this bin is not zero : right'
                    
                    if(h1.Integral(0,L-2)!=0 and h2.Integral(0,L-2)==0):
                        ratio_BinContent_1=9999
                        print 'this bin is zero, before:no background'
                    if(h1.Integral(0,L-2)==0 and h2.Integral(0,L-2)!=0):
                        ratio_BinContent_1=0
                        print 'this bin is zero, before:no signal'
                    if(h1.Integral(0,L-2)==0 and h2.Integral(0,L-2)==0):
                        ratio_BinContent_1=-1
                        print 'this bin is zero, before:no signal and background'
                    if(h1.Integral(0,L-2)!=0 and h2.Integral(0,L-2)!=0):
                        ratio_BinContent_1=h1.Integral(0,L-2)/h2.Integral(0,L-2)
                        print 'this bin is not zero : left'
                    #---------------------------
                    
                    #---------------------------
                    if(h3.GetBinContent(L-1)>h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(R+1)==0):
                            if(h3.GetBinContent(L-1)>ratio_BinContent_2):
                                print'YA4'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(L-1)<ratio_BinContent_2):
                                print 'YA4'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(L-1)==ratio_BinContent_2):
                                print 'YA4'
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                            if(h1.Integral(L,R)>a/2):
                                print str(h1.Integral(L,R))+'More than half'
                                print '================================================fuck=============================================================='
                                print '=========================================================================================================================='
                                break
                    #---------------------------
                    if(h3.GetBinContent(L-1)<h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(L-1)==0):
                            if(h3.GetBinContent(R+1)>ratio_BinContent_1):
                                print'YA5'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(R+1)<ratio_BinContent_1):
                                'YA5'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(R+1)==ratio_BinContent_1):
                                print 'YA5'
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
                    
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
                            if(h1.Integral(L,R)>a/2):
                                print str(h1.Integral(L,R))+'More than half'
                                print '================================================fuck=============================================================='
                                print '=========================================================================================================================='
                                break
        #-----------------------------------
                    if(h3.GetBinContent(L-1)==h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(L-1)==0 and h3.GetBinContent(R+1)==0):
                            if(ratio_BinContent_2>ratio_BinContent_1):
                                print 'YA6'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                        elif(ratio_BinContent_2<ratio_BinContent_1):
                            print 'YA6'
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
                            if(h1.Integral(L,R)>a/2):
                                print str(h1.Integral(L,R))+'More than half'
                                print '================================================fuck=============================================================='
                                print '=========================================================================================================================='
                                break
                        
                        elif(ratio_BinContent_2==ratio_BinContent_1):
                            print 'YA6'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                        
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
        
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
#------------------------------------------
                n=R-L
                print n


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
                gr.SetLineWidth(3)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1/background_efficiency")
                gr.Draw()
                c.SetLogy()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_50%.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_50%.pdf")




    elif(variable[k]=="c2b1"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_ww.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_ww.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_ww.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_tcalo_mass_cut_for_ww.root", 'r')

                h1 = f1.Get("h_c2_b1")
                h2 = f2.Get("h_c2_b1")
                print h1,h2

                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())

                h1_Max_y=h1.GetBinContent(h1.GetMaximumBin())
                h2_Max_y=h2.GetBinContent(h2.GetMaximumBin())
                print h1_Max_y,h2_Max_y
                Maximum_in_histogram=max(h1_Max_y,h2_Max_y)
                
                h3 = TH1F("h3","Ratio histogram",100,0,1)
                h3=h1.Clone("h3")
                h3.Divide(h2)
                
                #print h1,h2
                #print variable[k]
                #print '1'
                #h1.Scale(1.0/h1.Integral())
                #h2.Scale(1.0/h2.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                ratio_BinContent_1=0
                ratio_BinContent_2=0
                M=h3.GetMaximumBin()
                L=M
                R=M
                print M
                for Q in range(101):
                    print '==============================================='
                    print 'signal total'+str(a)
                    print 'signal:'+str(h1.Integral(L,R))
                    print 'background:'+str(h2.Integral(L,R))
                    print 'Ratio:'+str(h3.Integral(L,R))
                    print 'Ratio_total:'+str(h3.Integral())
                    print str(h3.GetBinContent(L-1))
                    print str(h3.GetBinContent(R+1))
                    print '==============================================='
                    print 'next-step'
                    #---------------------------
                    if(h1.Integral(R+2,100)!=0 and h2.Integral(R+2,100)==0):
                        ratio_BinContent_2=9999
                        print 'this bin is zero, after:no background'
                    if(h1.Integral(R+2,100)==0 and h2.Integral(R+2,100)!=0):
                        ratio_BinContent_2=0
                        print 'this bin is zero, after:no signal'
                    if(h1.Integral(R+2,100)==0 and h2.Integral(R+2,100)==0):
                        ratio_BinContent_2=-1
                        print 'this bin is zero, after:no signal and background'
                    if(h1.Integral(R+2,100)!=0 and h2.Integral(R+2,100)!=0):
                        ratio_BinContent_2=h1.Integral(R+2,100)/h2.Integral(R+2,100)
                        print 'this bin is not zero : right'
                    
                    if(h1.Integral(0,L-2)!=0 and h2.Integral(0,L-2)==0):
                        ratio_BinContent_1=9999
                        print 'this bin is zero, before:no background'
                    if(h1.Integral(0,L-2)==0 and h2.Integral(0,L-2)!=0):
                        ratio_BinContent_1=0
                        print 'this bin is zero, before:no signal'
                    if(h1.Integral(0,L-2)==0 and h2.Integral(0,L-2)==0):
                        ratio_BinContent_1=-1
                        print 'this bin is zero, before:no signal and background'
                    if(h1.Integral(0,L-2)!=0 and h2.Integral(0,L-2)!=0):
                        ratio_BinContent_1=h1.Integral(0,L-2)/h2.Integral(0,L-2)
                        print 'this bin is not zero : left'
                    #---------------------------
                    
                    #---------------------------
                    if(h3.GetBinContent(L-1)>h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(R+1)==0):
                            if(h3.GetBinContent(L-1)>ratio_BinContent_2):
                                print'YA4'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(L-1)<ratio_BinContent_2):
                                print 'YA4'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(L-1)==ratio_BinContent_2):
                                print 'YA4'
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                            if(h1.Integral(L,R)>a/2):
                                print str(h1.Integral(L,R))+'More than half'
                                print '================================================fuck=============================================================='
                                print '=========================================================================================================================='
                                break
                    #---------------------------
                    if(h3.GetBinContent(L-1)<h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(L-1)==0):
                            if(h3.GetBinContent(R+1)>ratio_BinContent_1):
                                print'YA5'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(R+1)<ratio_BinContent_1):
                                'YA5'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            if(h3.GetBinContent(R+1)==ratio_BinContent_1):
                                print 'YA5'
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
                    
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
                            if(h1.Integral(L,R)>a/2):
                                print str(h1.Integral(L,R))+'More than half'
                                print '================================================fuck=============================================================='
                                print '=========================================================================================================================='
                                break
        #-----------------------------------
                    if(h3.GetBinContent(L-1)==h3.GetBinContent(R+1)):
                        if(h3.GetBinContent(L-1)==0 and h3.GetBinContent(R+1)==0):
                            if(ratio_BinContent_2>ratio_BinContent_1):
                                print 'YA6'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                            elif(ratio_BinContent_2<ratio_BinContent_1):
                                print 'YA6'
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
                                if(h1.Integral(L,R)>a/2):
                                    print str(h1.Integral(L,R))+'More than half'
                                    print '================================================fuck=============================================================='
                                    print '=========================================================================================================================='
                                    break
                    
                            elif(ratio_BinContent_2==ratio_BinContent_1):
                                print 'YA6'
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
                        
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
                                    
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
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
                                    if(h1.Integral(L,R)>a/2):
                                        print str(h1.Integral(L,R))+'More than half'
                                        print '================================================fuck=============================================================='
                                        print '=========================================================================================================================='
                                        break
                                                                                                                                                                                                #------------------------------------------
                n=R-L
                print n
                
                
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
                gr.SetLineWidth(3)
                gr.SetLineStyle(1)
                gr.SetMarkerColor(Color)
                gr.SetMarkerStyle(0)
                gr.SetMarkerSize(0)
                gr.GetXaxis().SetTitle("signal_efficiency")
                gr.GetXaxis().SetTitleColor(4)
                gr.GetYaxis().SetTitle("1/background_efficiency")
                gr.Draw()
                c.SetLogy()
                
                print files_array[i]
                print variable[k]
                print str(energy_array[1][m])
                f=TFile("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_50%.root","RECREATE")
                gr.Write()
                c.Print("cluster_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_50%.pdf")
