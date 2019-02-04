import ROOT
import sys
import math
import numpy as np
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
for k in range(0,1):
    if(variable[k]=="tau21"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins_no_UOF_new_75%.root",'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_tt_Dis_25bins_no_UOF_new_75%.root",'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins_no_UOF_new_75%.root",'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_tt_Dis_25bins_no_UOF_new_75%.root",'r')
                
                h1 = f1.Get("h_"+variable[k]+"_b1")
                h2 = f2.Get("h_"+variable[k]+"_b1")

                h3 = TH1F("h3","Ratio histogram",100,0,1)
                h3=h1.Clone("h3")
                h3.Sumw2()
                h3.Divide(h2)

                #print h1,h2
                #print variable[k]
                #print '1'
                h1.Sumw2()
                h2.Sumw2()
                h3.Sumw2()
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                h3.Scale(1.0/h3.Integral())

                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarray_bin=array("f",[])
                yarray_bin=array("f",[])
                xarray_bin_left=array("f",[])
                yarray_bin_right=array("f",[])
                ratio_bin_left=array("f",[])
                ratio_bin_right=array("f",[])
                #==========Signal Bin Content, Background Bin Content and Ratio Bin Content===========#
                SIG_bin_individual=array("f",[])
                BKG_bin_individual=array("f",[])
                RAT_bin_individual=array("f",[])
                analysis_highest_array=array("f",[])
                #=====================================================================================#
                ratio_BinContent_1=0
                ratio_BinContent_2=0
                N_max_ratio_bin=0
                #=====================================================================================#
                for K in range(1,26):
                    SIG_bin_individual.append(h1.GetBinContent(K))
                    BKG_bin_individual.append(h2.GetBinContent(K))
                    if(h1.GetBinContent(K)!=0 and h2.GetBinContent(K)==0):
                        RAT_bin_individual.append(9999)
                    else:
                        RAT_bin_individual.append(h3.GetBinContent(K))
                print RAT_bin_individual
                
                for analysis_highest in range(25):
                    if(RAT_bin_individual[analysis_highest]==9999):
                        print RAT_bin_individual[analysis_highest]
                        print 'no print'
                        analysis_highest_array.append(0)
                    else:
                        print RAT_bin_individual[analysis_highest]
                        print 'print'
                        analysis_highest_array.append(RAT_bin_individual[analysis_highest])
                print analysis_highest_array
                #======================================================================================#
                M=max(analysis_highest_array)
                for j in range(25):
                    if ((RAT_bin_individual[j])!= M):
                        continue
                    else:
                        N_max_ratio_bin=j
                        break
                L=N_max_ratio_bin+1
                R=N_max_ratio_bin+1
                print N_max_ratio_bin+1 #Transfer to getbincontent plane
                                        #======================================================================================#
                xarray.append(h1.Integral(L,R)/a)
                yarray.append(1/(h2.Integral(L,R)/b))
                xarray_bin.append(h1.Integral(L,R))
                yarray_bin.append(h2.Integral(L,R))
                xarray_bin_left.append(L)
                yarray_bin_right.append(R)
                Latest_Window=np.array([[L,R]])
                
                #=====================================================================================#
                for Q in range(1,26):
                    print '==============================================='
                    print 'signal total'+str(a)
                    print 'signal:'+str(h1.Integral(L,R))
                    print 'background:'+str(h2.Integral(L,R))
                    print '==============================================='
                    print 'next-step'
                    #---------------------------
                    if(R<=23):
                        if(h1.Integral(R+2,25)!=0 and h2.Integral(R+2,25)==0):
                            ratio_BinContent_2=9999
                            print 'this bin is zero, after:no background'
                        elif(h1.Integral(R+2,25)==0 and h2.Integral(R+2,25)!=0):
                            ratio_BinContent_2=0
                            print 'this bin is zero, after:no signal'
                        elif(h1.Integral(R+2,25)==0 and h2.Integral(R+2,25)==0):
                            ratio_BinContent_2=-1
                            print 'this bin is zero, after:no signal and background'
                        elif(h1.Integral(R+2,25)!=0 and h2.Integral(R+2,25)!=0):
                            ratio_BinContent_2=h1.Integral(R+2,25)/h2.Integral(R+2,25)
                            print 'this bin is not zero : right'
                    if(R==24):
                        ratio_BinContent_2=-1
                    if(L>=3):
                        if(h1.Integral(1,L-2)!=0 and h2.Integral(1,L-2)==0):
                            ratio_BinContent_1=9999
                            print 'this bin is zero, before:no background'
                        elif(h1.Integral(1,L-2)==0 and h2.Integral(1,L-2)!=0):
                            ratio_BinContent_1=0
                            print 'this bin is zero, before:no signal'
                        elif(h1.Integral(1,L-2)==0 and h2.Integral(1,L-2)==0):
                            ratio_BinContent_1=-1
                            print 'this bin is zero, before:no signal and background'
                        elif(h1.Integral(1,L-2)!=0 and h2.Integral(1,L-2)!=0):
                            ratio_BinContent_1=h1.Integral(1,L-2)/h2.Integral(1,L-2)
                            print 'this bin is not zero : left'
                    if(L==2):
                        ratio_BinContent_1=-1
                    #---------------------------
                    
                    #---------------------------
                    if(L==1 and R==25):
                        break
                    elif(L==1 and R!=25):
                        print 'YA4'
                        xarray.append(h1.Integral(L,R+1)/a)
                        yarray.append(1/((h2.Integral(L,R+1))/b))
                        xarray_bin.append(h1.Integral(L,R+1))
                        yarray_bin.append(h2.Integral(L,R+1))
                        print h1.Integral(L,R+1), a
                        L=L
                        R=R+1
                        xarray_bin_left.append(L)
                        yarray_bin_right.append(R)
                        Window=np.array([[L,R]])
                        Latest_Window=np.concatenate((Latest_Window, Window))
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----2'
                    elif(R==25 and L!=1):
                        print 'YA4'
                        xarray.append(h1.Integral(L-1,R)/a)
                        yarray.append(1/((h2.Integral(L-1,R))/b))
                        xarray_bin.append(h1.Integral(L-1,R))
                        yarray_bin.append(h2.Integral(L-1,R))
                        print h1.Integral(L-1,R), a
                        L=L-1
                        R=R
                        xarray_bin_left.append(L)
                        yarray_bin_right.append(R)
                        Window=np.array([[L,R]])
                        Latest_Window=np.concatenate((Latest_Window, Window))
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----2'

                    elif(RAT_bin_individual[L-2]>RAT_bin_individual[R]):
                        if(RAT_bin_individual[R]==0):
                            if(RAT_bin_individual[L-2]>ratio_BinContent_2):
                                print'YA4'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----1'
                            elif(RAT_bin_individual[L-2]<ratio_BinContent_2):
                                print 'YA4'
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/((h2.Integral(L,R+1))/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----2'
                            elif(RAT_bin_individual[L-2]==ratio_BinContent_2):
                                print 'YA4'
                                Random=randint(1,2)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----3'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----4'
                        else:
                            xarray.append(h1.Integral(L-1,R)/a)
                            yarray.append(1/(h2.Integral(L-1,R)/b))
                            xarray_bin.append(h1.Integral(L-1,R))
                            yarray_bin.append(h2.Integral(L-1,R))
                            print h1.Integral(L-1,R), a
                            C=h2.Integral(L-1,R)
                            L=L-1
                            R=R
                            xarray_bin_left.append(L)
                            yarray_bin_right.append(R)
                            Window=np.array([[L,R]])
                            Latest_Window=np.concatenate((Latest_Window, Window))
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----5'
                    #---------------------------
                    elif(RAT_bin_individual[L-2]<RAT_bin_individual[R]):
                        if(RAT_bin_individual[L-2]==0):
                            if(RAT_bin_individual[R]>ratio_BinContent_1):
                                print 'L-2:'+str(L-2)
                                print'signal from 0 to L-2'+str(h1.Integral(0,L-2))
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print 'ratio_bin_left:'+str(ratio_BinContent_1)
                                print '----6'
                            if(RAT_bin_individual[R]<ratio_BinContent_1):
                                'YA5'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----7'
                            if(RAT_bin_individual[R]==ratio_BinContent_1):
                                print 'YA5'
                                Random=randint(1,2)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----8'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----9'
                        #---------------------------
                        else:
                            xarray.append(h1.Integral(L,R+1)/a)
                            yarray.append(1/(h2.Integral(L,R+1)/b))
                            xarray_bin.append(h1.Integral(L,R+1))
                            yarray_bin.append(h2.Integral(L,R+1))
                            print h1.Integral(L,R+1), a
                            C=h2.Integral(L,R+1)
                            L=L
                            R=R+1
                            xarray_bin_left.append(L)
                            yarray_bin_right.append(R)
                            Window=np.array([[L,R]])
                            Latest_Window=np.concatenate((Latest_Window, Window))
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----10'
        #-----------------------------------
                    elif(RAT_bin_individual[L-2]==RAT_bin_individual[R]):
                        if(RAT_bin_individual[L-2]==0 and RAT_bin_individual[R]==0):
                            if(ratio_BinContent_2>ratio_BinContent_1):
                                print 'YA6'
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----11'
                            elif(ratio_BinContent_2<ratio_BinContent_1):
                                print 'YA6'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----12'

                            elif(ratio_BinContent_2==ratio_BinContent_1):
                                print 'YA6'
                                Random=randint(1,2)
                                print Random
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----13'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----14'
                    
                        else:
                            Random=randint(1,2)
                            print Random
                            if(Random==1):
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                C=h2.Integral(L-1,R)
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----14'
                            if(Random==2):
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----15'
#------------------------------------------
                n=R-L
                print n
                print 'ratio CONTENT 10'
                print RAT_bin_individual[9]
                print '============================================================='
                print 'ratio CONTENT 1'
                print RAT_bin_individual[0]
                print '============================================================='
                print 'Signal bin content from the first bin to the lastest bin:'
                print SIG_bin_individual
                print '============================================================='
                print 'Background bin content from the first bin to the lastest bin:'
                print BKG_bin_individual
                print '============================================================='
                print 'Ratio bin content from the first bin to the lastest bin:'
                print RAT_bin_individual
                print '============================================================='
                print 'Window:'
                print Latest_Window


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
                  
                  
                gr = TGraph(n+1,xarray,yarray)
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
                f=TFile("Rawhit_0.5GeV_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_after_cut_25bins_no_UOF_new_75%_tt.root","RECREATE")
                gr.Write()
#c.Print("Rawhit_0.5GeV_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_after_cut_25bins_no_UOF.pdf")
                  
                  

    elif(variable[k]=="tau32"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins_no_UOF_new_75%.root",'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_tt_Dis_25bins_no_UOF_new_75%.root",'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_ttbarrfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ttbar_Dis_25bins_no_UOF_new_75%.root",'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_tt_Dis_25bins_no_UOF_new_75%.root",'r')
                h1 = f1.Get("h_"+variable[k]+"_b1")
                h2 = f2.Get("h_"+variable[k]+"_b1")
                print h1,h2
                
                h1.Sumw2()
                h2.Sumw2()
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())

                h3 = TH1F("h3","Ratio histogram",100,0,1)
                h3=h1.Clone("h3")
                h3.Sumw2()
                h3.Divide(h2)
                
                #print h1,h2
                #print variable[k]
                #print '1'
                
                h1.Sumw2()
                h2.Sumw2()
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                h3.Scale(1.0/h3.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarray_bin=array("f",[])
                yarray_bin=array("f",[])
                xarray_bin_left=array("f",[])
                yarray_bin_right=array("f",[])
                ratio_bin_left=array("f",[])
                ratio_bin_right=array("f",[])
                #==========Signal Bin Content, Background Bin Content and Ratio Bin Content===========#
                SIG_bin_individual=array("f",[])
                BKG_bin_individual=array("f",[])
                RAT_bin_individual=array("f",[])
                analysis_highest_array=array("f",[])
                #=====================================================================================#
                ratio_BinContent_1=0
                ratio_BinContent_2=0
                N_max_ratio_bin=0
                #=====================================================================================#
                for K in range(1,26):
                    SIG_bin_individual.append(h1.GetBinContent(K))
                    BKG_bin_individual.append(h2.GetBinContent(K))
                    if(h1.GetBinContent(K)!=0 and h2.GetBinContent(K)==0):
                        RAT_bin_individual.append(9999)
                    else:
                        RAT_bin_individual.append(h3.GetBinContent(K))
                print RAT_bin_individual
                
                for analysis_highest in range(25):
                    if(RAT_bin_individual[analysis_highest]==9999):
                        print RAT_bin_individual[analysis_highest]
                        print 'no print'
                        analysis_highest_array.append(0)
                    else:
                        print RAT_bin_individual[analysis_highest]
                        print 'print'
                        analysis_highest_array.append(RAT_bin_individual[analysis_highest])
                print analysis_highest_array
                #======================================================================================#
                M=max(analysis_highest_array)
                for j in range(25):
                    if ((RAT_bin_individual[j])!= M):
                        continue
                    else:
                        N_max_ratio_bin=j
                        break
                L=N_max_ratio_bin+1
                R=N_max_ratio_bin+1
                print N_max_ratio_bin+1 #Transfer to getbincontent plane
                #======================================================================================#
                xarray.append(h1.Integral(L,R)/a)
                yarray.append(1/(h2.Integral(L,R)/b))
                xarray_bin.append(h1.Integral(L,R))
                yarray_bin.append(h2.Integral(L,R))
                xarray_bin_left.append(L)
                yarray_bin_right.append(R)
                Latest_Window=np.array([[L,R]])
                
                #=====================================================================================#
                for Q in range(1,26):
                    print '==============================================='
                    print 'signal total'+str(a)
                    print 'signal:'+str(h1.Integral(L,R))
                    print 'background:'+str(h2.Integral(L,R))
                    print '==============================================='
                    print 'next-step'
                    #---------------------------
                    if(R<=23):
                        if(h1.Integral(R+2,25)!=0 and h2.Integral(R+2,25)==0):
                            ratio_BinContent_2=9999
                            print 'this bin is zero, after:no background'
                        elif(h1.Integral(R+2,25)==0 and h2.Integral(R+2,25)!=0):
                            ratio_BinContent_2=0
                            print 'this bin is zero, after:no signal'
                        elif(h1.Integral(R+2,25)==0 and h2.Integral(R+2,25)==0):
                            ratio_BinContent_2=-1
                            print 'this bin is zero, after:no signal and background'
                        elif(h1.Integral(R+2,25)!=0 and h2.Integral(R+2,25)!=0):
                            ratio_BinContent_2=h1.Integral(R+2,25)/h2.Integral(R+2,25)
                            print 'this bin is not zero : right'
                    if(R==24):
                        ratio_BinContent_2=-1
                    if(L>=3):
                        if(h1.Integral(1,L-2)!=0 and h2.Integral(1,L-2)==0):
                            ratio_BinContent_1=9999
                            print 'this bin is zero, before:no background'
                        elif(h1.Integral(1,L-2)==0 and h2.Integral(1,L-2)!=0):
                            ratio_BinContent_1=0
                            print 'this bin is zero, before:no signal'
                        elif(h1.Integral(1,L-2)==0 and h2.Integral(1,L-2)==0):
                            ratio_BinContent_1=-1
                            print 'this bin is zero, before:no signal and background'
                        elif(h1.Integral(1,L-2)!=0 and h2.Integral(1,L-2)!=0):
                            ratio_BinContent_1=h1.Integral(1,L-2)/h2.Integral(1,L-2)
                            print 'this bin is not zero : left'
                    if(L==2):
                        ratio_BinContent_1=-1
                    #---------------------------
                    
                    #---------------------------
                    if(L==1 and R==25):
                        break
                    elif(L==1 and R!=25):
                        print 'YA4'
                        xarray.append(h1.Integral(L,R+1)/a)
                        yarray.append(1/((h2.Integral(L,R+1))/b))
                        xarray_bin.append(h1.Integral(L,R+1))
                        yarray_bin.append(h2.Integral(L,R+1))
                        print h1.Integral(L,R+1), a
                        L=L
                        R=R+1
                        xarray_bin_left.append(L)
                        yarray_bin_right.append(R)
                        Window=np.array([[L,R]])
                        Latest_Window=np.concatenate((Latest_Window, Window))
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----2'
                    elif(R==25 and L!=1):
                        print 'YA4'
                        xarray.append(h1.Integral(L-1,R)/a)
                        yarray.append(1/((h2.Integral(L-1,R))/b))
                        xarray_bin.append(h1.Integral(L-1,R))
                        yarray_bin.append(h2.Integral(L-1,R))
                        print h1.Integral(L-1,R), a
                        L=L-1
                        R=R
                        xarray_bin_left.append(L)
                        yarray_bin_right.append(R)
                        Window=np.array([[L,R]])
                        Latest_Window=np.concatenate((Latest_Window, Window))
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----2'
                    
                    
                    elif(RAT_bin_individual[L-2]>RAT_bin_individual[R]):
                        if(RAT_bin_individual[R]==0):
                            if(RAT_bin_individual[L-2]>ratio_BinContent_2):
                                print'YA4'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----1'
                            elif(RAT_bin_individual[L-2]<ratio_BinContent_2):
                                print 'YA4'
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/((h2.Integral(L,R+1))/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----2'
                            elif(RAT_bin_individual[L-2]==ratio_BinContent_2):
                                print 'YA4'
                                Random=randint(1,2)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----3'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----4'
                        else:
                            xarray.append(h1.Integral(L-1,R)/a)
                            yarray.append(1/(h2.Integral(L-1,R)/b))
                            xarray_bin.append(h1.Integral(L-1,R))
                            yarray_bin.append(h2.Integral(L-1,R))
                            print h1.Integral(L-1,R), a
                            C=h2.Integral(L-1,R)
                            L=L-1
                            R=R
                            xarray_bin_left.append(L)
                            yarray_bin_right.append(R)
                            Window=np.array([[L,R]])
                            Latest_Window=np.concatenate((Latest_Window, Window))
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----5'
                    #---------------------------
                    elif(RAT_bin_individual[L-2]<RAT_bin_individual[R]):
                        if(RAT_bin_individual[L-2]==0):
                            print 'R:'+str(R)
                            if(RAT_bin_individual[R]>ratio_BinContent_1):
                                print 'L-2:'+str(L-2)
                                print'signal from 0 to L-2'+str(h1.Integral(0,L-2))
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print 'ratio_bin_left:'+str(ratio_BinContent_1)
                                print '----6'
                                print 'Next'
                            elif(RAT_bin_individual[R]<ratio_BinContent_1):
                                'YA5'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----7'
                            elif(RAT_bin_individual[R]==ratio_BinContent_1):
                                print 'YA5'
                                Random=randint(1,2)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----8'
                                elif(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----9'
                        #---------------------------
                        else:
                            xarray.append(h1.Integral(L,R+1)/a)
                            yarray.append(1/(h2.Integral(L,R+1)/b))
                            xarray_bin.append(h1.Integral(L,R+1))
                            yarray_bin.append(h2.Integral(L,R+1))
                            print h1.Integral(L,R+1), a
                            C=h2.Integral(L,R+1)
                            L=L
                            R=R+1
                            xarray_bin_left.append(L)
                            yarray_bin_right.append(R)
                            Window=np.array([[L,R]])
                            Latest_Window=np.concatenate((Latest_Window, Window))
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----10'
                    #-----------------------------------
                    elif(RAT_bin_individual[L-2]==RAT_bin_individual[R]):
                        if(RAT_bin_individual[L-2]==0 and RAT_bin_individual[R]==0):
                            if(ratio_BinContent_2>ratio_BinContent_1):
                                print 'YA6'
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----11'
                            elif(ratio_BinContent_2<ratio_BinContent_1):
                                print 'YA6'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----12'
                            
                            elif(ratio_BinContent_2==ratio_BinContent_1):
                                print 'YA6'
                                Random=randint(1,2)
                                print Random
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----13'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----14'
                    
                        else:
                            Random=randint(1,2)
                            print Random
                            if(Random==1):
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                C=h2.Integral(L-1,R)
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----14'
                            elif(Random==2):
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----15'
#------------------------------------------
                n=R-L
                print n
                print 'ratio CONTENT 10'
                print RAT_bin_individual[9]
                print '============================================================='
                print 'ratio CONTENT 1'
                print RAT_bin_individual[0]
                print '============================================================='
                print 'Signal bin content from the first bin to the lastest bin:'
                print SIG_bin_individual
                print '============================================================='
                print 'Background bin content from the first bin to the lastest bin:'
                print BKG_bin_individual
                print '============================================================='
                print 'Ratio bin content from the first bin to the lastest bin:'
                print RAT_bin_individual
                print '============================================================='
                print 'Window:'
                print Latest_Window


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
                
                
                gr = TGraph(n+1,xarray,yarray)
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
                f=TFile("Rawhit_0.5GeV_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_after_cut_25bins_no_UOF_new_75%.root","RECREATE")
                gr.Write()
#c.Print("Rawhit_0.5GeV_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_after_cut_25bins_no_UOF.pdf")




    elif(variable[k]=="c2b1"):
        for m in range(0,4):
            for i in range(0,3):
                if(energy_array[1][m]<20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ww_Dis_25bins_no_UOF_new_75%.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ww_Dis_25bins_no_UOF_new_75%.root", 'r')
                if(energy_array[1][m]>=20):
                    f1 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_wwrfull"+files_array[i]+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ww_Dis_25bins_no_UOF_new_75%.root", 'r')
                    f2 = ROOT.TFile.Open("/Users/ms08962476/FD/VHEPP/analyze/onlyhadron/tev"+str(energy_array[1][m])+"mumu_pythia6_zprime"+str(energy_array[1][m])+"tev_qqrfull"+str(files_array[i])+"_onlyhadronic/radius0.4_jetsubstructure_trawhits_mass_cut_0.5GeV_for_ww_Dis_25bins_no_UOF_new_75%.root", 'r')

                h1 = f1.Get("h_c2_b1")
                h2 = f2.Get("h_c2_b1")
                print h1,h2
                h1.Sumw2()
                h2.Sumw2()
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())

                h3 = TH1F("h3","Ratio histogram",100,0,0.3)
                h3=h1.Clone("h3")
                h3.Sumw2()
                h3.Divide(h2)
                
                #print h1,h2
                #print variable[k]
                #print '1'
                
                h1.Sumw2()
                h2.Sumw2()
                h1.Scale(1.0/h1.Integral())
                h2.Scale(1.0/h2.Integral())
                h3.Scale(1.0/h3.Integral())
                
                a=h1.Integral()
                b=h2.Integral()
                xarray=array("f",[])
                yarray=array("f",[])
                xarray_bin=array("f",[])
                yarray_bin=array("f",[])
                xarray_bin_left=array("f",[])
                yarray_bin_right=array("f",[])
                ratio_bin_left=array("f",[])
                ratio_bin_right=array("f",[])
                #==========Signal Bin Content, Background Bin Content and Ratio Bin Content===========#
                SIG_bin_individual=array("f",[])
                BKG_bin_individual=array("f",[])
                RAT_bin_individual=array("f",[])
                analysis_highest_array=array("f",[])
                #=====================================================================================#
                ratio_BinContent_1=0
                ratio_BinContent_2=0
                N_max_ratio_bin=0
                #=====================================================================================#
                for K in range(1,26):
                    SIG_bin_individual.append(h1.GetBinContent(K))
                    BKG_bin_individual.append(h2.GetBinContent(K))
                    if(h1.GetBinContent(K)!=0 and h2.GetBinContent(K)==0):
                        RAT_bin_individual.append(9999)
                    else:
                        RAT_bin_individual.append(h3.GetBinContent(K))
                print RAT_bin_individual
                
                for analysis_highest in range(25):
                    if(RAT_bin_individual[analysis_highest]==9999):
                        print RAT_bin_individual[analysis_highest]
                        print 'no print'
                        analysis_highest_array.append(0)
                    else:
                        print RAT_bin_individual[analysis_highest]
                        print 'print'
                        analysis_highest_array.append(RAT_bin_individual[analysis_highest])
                print analysis_highest_array
                #======================================================================================#
                M=max(analysis_highest_array)
                for j in range(25):
                    if ((RAT_bin_individual[j])!= M):
                        continue
                    else:
                        N_max_ratio_bin=j
                        break
                L=N_max_ratio_bin+1
                R=N_max_ratio_bin+1
                print N_max_ratio_bin+1 #Transfer to getbincontent plane
                #======================================================================================#
                xarray.append(h1.Integral(L,R)/a)
                yarray.append(1/(h2.Integral(L,R)/b))
                xarray_bin.append(h1.Integral(L,R))
                yarray_bin.append(h2.Integral(L,R))
                xarray_bin_left.append(L)
                yarray_bin_right.append(R)
                Latest_Window=np.array([[L,R]])
                
                #=====================================================================================#
                for Q in range(1,26):
                    print '==============================================='
                    print 'signal total'+str(a)
                    print 'signal:'+str(h1.Integral(L,R))
                    print 'background:'+str(h2.Integral(L,R))
                    print '==============================================='
                    print 'next-step'
                    #---------------------------
                    if(R<=23):
                        if(h1.Integral(R+2,25)!=0 and h2.Integral(R+2,25)==0):
                            ratio_BinContent_2=9999
                            print 'this bin is zero, after:no background'
                        elif(h1.Integral(R+2,25)==0 and h2.Integral(R+2,25)!=0):
                            ratio_BinContent_2=0
                            print 'this bin is zero, after:no signal'
                        elif(h1.Integral(R+2,25)==0 and h2.Integral(R+2,25)==0):
                            ratio_BinContent_2=-1
                            print 'this bin is zero, after:no signal and background'
                        elif(h1.Integral(R+2,25)!=0 and h2.Integral(R+2,25)!=0):
                            ratio_BinContent_2=h1.Integral(R+2,50)/h2.Integral(R+2,50)
                            print 'this bin is not zero : right'
                    if(R==24):
                        ratio_BinContent_2=-1
                    if(L>=3):
                        if(h1.Integral(1,L-2)!=0 and h2.Integral(1,L-2)==0):
                            ratio_BinContent_1=9999
                            print 'this bin is zero, before:no background'
                        elif(h1.Integral(1,L-2)==0 and h2.Integral(1,L-2)!=0):
                            ratio_BinContent_1=0
                            print 'this bin is zero, before:no signal'
                        elif(h1.Integral(1,L-2)==0 and h2.Integral(1,L-2)==0):
                            ratio_BinContent_1=-1
                            print 'this bin is zero, before:no signal and background'
                        elif(h1.Integral(1,L-2)!=0 and h2.Integral(1,L-2)!=0):
                            ratio_BinContent_1=h1.Integral(1,L-2)/h2.Integral(1,L-2)
                            print 'this bin is not zero : left'
                    if(L==2):
                        ratio_BinContent_1=-1
                    #---------------------------
                    
                    #---------------------------
                    if(L==1 and R==25):
                        break
                    elif(L==1 and R!=25):
                        print 'YA4'
                        xarray.append(h1.Integral(L,R+1)/a)
                        yarray.append(1/((h2.Integral(L,R+1))/b))
                        xarray_bin.append(h1.Integral(L,R+1))
                        yarray_bin.append(h2.Integral(L,R+1))
                        print h1.Integral(L,R+1), a
                        L=L
                        R=R+1
                        xarray_bin_left.append(L)
                        yarray_bin_right.append(R)
                        Window=np.array([[L,R]])
                        Latest_Window=np.concatenate((Latest_Window, Window))
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----2'
                    elif(R==25 and L!=1):
                        print 'YA4'
                        xarray.append(h1.Integral(L-1,R)/a)
                        yarray.append(1/((h2.Integral(L-1,R))/b))
                        xarray_bin.append(h1.Integral(L-1,R))
                        yarray_bin.append(h2.Integral(L-1,R))
                        print h1.Integral(L-1,R), a
                        L=L-1
                        R=R
                        xarray_bin_left.append(L)
                        yarray_bin_right.append(R)
                        Window=np.array([[L,R]])
                        Latest_Window=np.concatenate((Latest_Window, Window))
                        print str(L)
                        print str(R)
                        print str(h1.GetBinContent(L))
                        print str(h1.GetBinContent(R))
                        print '----2'
                    
                    elif(RAT_bin_individual[L-2]>RAT_bin_individual[R]):
                        if(RAT_bin_individual[R]==0):
                            if(RAT_bin_individual[L-2]>ratio_BinContent_2):
                                print'YA4'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----1'
                            elif(RAT_bin_individual[L-2]<ratio_BinContent_2):
                                print 'YA4'
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/((h2.Integral(L,R+1))/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----2'
                            elif(RAT_bin_individual[L-2]==ratio_BinContent_2):
                                print 'YA4'
                                Random=randint(1,2)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----3'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----4'
                        else:
                            xarray.append(h1.Integral(L-1,R)/a)
                            yarray.append(1/(h2.Integral(L-1,R)/b))
                            xarray_bin.append(h1.Integral(L-1,R))
                            yarray_bin.append(h2.Integral(L-1,R))
                            print h1.Integral(L-1,R), a
                            C=h2.Integral(L-1,R)
                            L=L-1
                            R=R
                            xarray_bin_left.append(L)
                            yarray_bin_right.append(R)
                            Window=np.array([[L,R]])
                            Latest_Window=np.concatenate((Latest_Window, Window))
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----5'
                    #---------------------------
                    elif(RAT_bin_individual[L-2]<RAT_bin_individual[R]):
                        if(RAT_bin_individual[L-2]==0):
                            if(RAT_bin_individual[R]>ratio_BinContent_1):
                                print 'L-2:'+str(L-2)
                                print'signal from 0 to L-2'+str(h1.Integral(0,L-2))
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print 'ratio_bin_left:'+str(ratio_BinContent_1)
                                print '----6'
                            elif(RAT_bin_individual[R]<ratio_BinContent_1):
                                'YA5'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----7'
                            elif(RAT_bin_individual[R]==ratio_BinContent_1):
                                print 'YA5'
                                Random=randint(1,2)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----8'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----9'
                        #---------------------------
                        else:
                            xarray.append(h1.Integral(L,R+1)/a)
                            yarray.append(1/(h2.Integral(L,R+1)/b))
                            xarray_bin.append(h1.Integral(L,R+1))
                            yarray_bin.append(h2.Integral(L,R+1))
                            print h1.Integral(L,R+1), a
                            C=h2.Integral(L,R+1)
                            L=L
                            R=R+1
                            xarray_bin_left.append(L)
                            yarray_bin_right.append(R)
                            Window=np.array([[L,R]])
                            Latest_Window=np.concatenate((Latest_Window, Window))
                            print str(L)
                            print str(R)
                            print str(h1.GetBinContent(L))
                            print str(h1.GetBinContent(R))
                            print '----10'
                    #-----------------------------------
                    elif(RAT_bin_individual[L-2]==RAT_bin_individual[R]):
                        if(RAT_bin_individual[L-2]==0 and RAT_bin_individual[R]==0):
                            if(ratio_BinContent_2>ratio_BinContent_1):
                                print 'YA6'
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----11'
                            elif(ratio_BinContent_2<ratio_BinContent_1):
                                print 'YA6'
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----12'
                            
                            elif(ratio_BinContent_2==ratio_BinContent_1):
                                print 'YA6'
                                Random=randint(1,2)
                                if(Random==1):
                                    xarray.append(h1.Integral(L-1,R)/a)
                                    yarray.append(1/(h2.Integral(L-1,R)/b))
                                    xarray_bin.append(h1.Integral(L-1,R))
                                    yarray_bin.append(h2.Integral(L-1,R))
                                    print h1.Integral(L-1,R), a
                                    C=h2.Integral(L-1,R)
                                    L=L-1
                                    R=R
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----13'
                                if(Random==2):
                                    xarray.append(h1.Integral(L,R+1)/a)
                                    yarray.append(1/(h2.Integral(L,R+1)/b))
                                    xarray_bin.append(h1.Integral(L,R+1))
                                    yarray_bin.append(h2.Integral(L,R+1))
                                    print h1.Integral(L,R+1), a
                                    C=h2.Integral(L,R+1)
                                    L=L
                                    R=R+1
                                    xarray_bin_left.append(L)
                                    yarray_bin_right.append(R)
                                    Window=np.array([[L,R]])
                                    Latest_Window=np.concatenate((Latest_Window, Window))
                                    print str(L)
                                    print str(R)
                                    print str(h1.GetBinContent(L))
                                    print str(h1.GetBinContent(R))
                                    print '----14'
                    
                        else:
                            Random=randint(1,2)
                            print Random
                            if(Random==1):
                                xarray.append(h1.Integral(L-1,R)/a)
                                yarray.append(1/(h2.Integral(L-1,R)/b))
                                xarray_bin.append(h1.Integral(L-1,R))
                                yarray_bin.append(h2.Integral(L-1,R))
                                print h1.Integral(L-1,R), a
                                C=h2.Integral(L-1,R)
                                L=L-1
                                R=R
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----14'
                            if(Random==2):
                                xarray.append(h1.Integral(L,R+1)/a)
                                yarray.append(1/(h2.Integral(L,R+1)/b))
                                xarray_bin.append(h1.Integral(L,R+1))
                                yarray_bin.append(h2.Integral(L,R+1))
                                print h1.Integral(L,R+1), a
                                C=h2.Integral(L,R+1)
                                L=L
                                R=R+1
                                xarray_bin_left.append(L)
                                yarray_bin_right.append(R)
                                Window=np.array([[L,R]])
                                Latest_Window=np.concatenate((Latest_Window, Window))
                                print str(L)
                                print str(R)
                                print str(h1.GetBinContent(L))
                                print str(h1.GetBinContent(R))
                                print '----15'
#------------------------------------------
                n=R-L
                print n
                print 'ratio CONTENT 10'
                print RAT_bin_individual[9]
                print '============================================================='
                print 'ratio CONTENT 1'
                print RAT_bin_individual[0]
                print '============================================================='
                print 'Signal bin content from the first bin to the lastest bin:'
                print SIG_bin_individual
                print '============================================================='
                print 'Background bin content from the first bin to the lastest bin:'
                print BKG_bin_individual
                print '============================================================='
                print 'Ratio bin content from the first bin to the lastest bin:'
                print RAT_bin_individual
                print '============================================================='
                print 'Window:'
                print Latest_Window
                
                
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
                
                
                gr = TGraph(n+1,xarray,yarray)
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
                f=TFile("Rawhit_0.5GeV_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_after_cut_25bins_no_UOF_new_75%.root","RECREATE")
                gr.Write()
#c.Print("Rawhit_0.5GeV_r"+files_array[i]+"_"+variable[k]+"_"+str(energy_array[1][m])+"tev_04_eff_log_New2_after_cut_25bins_no_UOF.pdf")
