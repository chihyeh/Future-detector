#include "makePlots.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "TFile.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMultiGraph.h"


ClassImp(hit)
ClassImp(hitcollection)
//Constructor
makePlots::makePlots(TChain* inchain):fChain(inchain)
{
  HITS = new hitcollection;
  app = new TApplication("app",0,0);  
  readmap();
  cout << "Constructor of makePlot ... \n\n" << endl;
}
//Destructor
makePlots::~makePlots()
{
  cout << "\n\n";
  cout << "Destructor of makePlot ... " << endl;
}

void makePlots::Init(){
  fChain->SetBranchAddress("hits",&HITS);
}

void makePlots::Loop(){

  Init();
  //P_and_N(0,1);
  //read_P_and_N("ped_result/RUN_101117_0925");

  TCanvas *c1 = new TCanvas;
  char plot_title[50];
    int RSA=0;
  int nevents = fChain->GetEntries();
  //============== Example for filling chip 0 ch 20 SCA0 to hist ==============

  TH1F *h = new TH1F("h","",100,150,250); //("title","",slice,star,end)
for(int RSA=0 ; RSA<13 ; RSA++){
for(int ev = 0; ev < nevents ; ++ev){
    fChain -> GetEntry(ev); // Get HITcollection from root file event
    
    for(int i = 0 ; i < NSCA ; ++i)
      TS[i] = HITS->rollposition[i];
      int nhits = HITS->hit_num;
    for(int hit = 0; hit < nhits ; ++hit){
        H = HITS->Hits.at(hit);
        if(!H.CCorNC) continue; // remove unconnected channel
        if(H.chip == 0 && H.ch == 32){
            if(TS[RSA]<9){h->Fill(H.SCA_hg[RSA]); }}}}
  sprintf(plot_title,"HG_SCA%d_channel%d",RSA,H.ch);
  h->Draw();
  h->SetTitle(plot_title);
  c1->Update();
    c1->Print(Form("HG_SCA%d_channel%d.pdf",RSA,H.ch));

    TFile *f = new TFile(Form("HG_SCA%d_channel%d.root",RSA,H.ch),"recreate");
    h->Write();
    f->Close();
    }

    //=================== End of example for filling hist =======================

  
  //========== Here shows the example how to use TH2Poly to draw plot =========
/* for(int ev = 0; ev < nevents ; ++ev){
    if(ev % 100 != 0) continue;

    fChain -> GetEntry(ev); // Get HITcollection from root file event
    TH2Poly *poly = new TH2Poly;
    InitTH2Poly(*poly); 
        
    for(int i = 0 ; i < NSCA ; ++i) TS[i] = HITS->rollposition[i];
    
    int nhits = HITS->hit_num;
    for(int hit = 0; hit < nhits ; ++hit){
      H = HITS->Hits.at(hit);
      if(!H.CCorNC) continue; // remove unconnected channel
      
      for(int sca = 0; sca < NSCA; ++sca){
	if(TS[sca] == 0 ){
	  int forCH = H.chip*32+H.ch/2;
	  float X = CHmap[forCH].first;
	  float Y = CHmap[forCH].second;
	  poly->Fill(X,Y,H.SCA_hg[sca]);}}
    }
    poly->Draw("colztext");
    sprintf(plot_title,"HG_TS0_evt%d",ev);
    poly->SetTitle(plot_title);
    c1->Update();
      c1->Print(Form("HG_TS0_evt%d.pdf",ev));
    delete poly;
}
  //============== End of the example to use TH2Poly to draw plot ==============

  
   
  // An example shows how to check the ADC vs TS for certain channel(injected)
  // Remove this comment to run
  TGraph *gr;
  for(int ev = 0; ev < nevents ; ++ev){
    if(ev % 50 != 0) continue;
    if(ev < 200) continue;
    fChain -> GetEntry(ev);
    for(int i = 0 ; i < NSCA ; ++i) TS[i] = HITS->rollposition[i];    
    int nhits = HITS->hit_num;
    for(int hit = 0; hit < nhits ; ++hit){
      H = HITS->Hits.at(hit);
      if(H.ch != 30) continue;

      gr = new TGraph(13, TS,H.SCA_lg );
      gr->SetMarkerColor(H.chip+2);
      gr->SetMarkerStyle(22);
      gr->SetMarkerSize(1.2);
      gr->Draw("AP");
      sprintf(plot_title,"HG_evt %d chip %d",ev,H.chip);
      gr->SetTitle(plot_title);
      gr->GetXaxis()->SetTitle("TS");
      gr->GetYaxis()->SetTitle("ADC");

      c1->Update();
      //if(ev == 400){
	//sprintf(plot_title,"%s.png",plot_title);
	//c1->SaveAs(plot_title);} // remove the comment to save plots
        c1->Print(Form("HG_evt %d chip %d.pdf",ev,H.chip));
    }
  }
    
}

void makePlots::calib(){

  Init();

  fChain->GetEntry(0);
  vector<int > vec_inj_ch;
  vec_inj_ch.assign(HITS->inj_ch.begin(),HITS->inj_ch.begin()+HITS->inj_ch.size());
  if((int)vec_inj_ch.size() == 0){
    cout << "This run has no injection channel! skip it!" << endl;
    return;}
  
  cout << "number of injection channel: "<< vec_inj_ch.size() << endl;

  string runtitle;
  int start = input_RUN.find_last_of("/");
  int end   = input_RUN.find(".root");
  runtitle = input_RUN.substr(start+1,end-start-1);
  
  
  TCanvas *c1 = new TCanvas;
  int nevents = fChain->GetEntries();
  
  for(int inC = 0; inC < (int)vec_inj_ch.size() ; ++inC){
    cout << "CH " << vec_inj_ch.at(inC) << endl;
    int tmp_inj_ch = vec_inj_ch.at(inC);
    char plot_title[150];  
    sprintf(plot_title,"calib_result/root/%dCH_Id%d_%s.root", (int)vec_inj_ch.size(),tmp_inj_ch,runtitle.c_str());

    TFile *outr = new TFile(plot_title,"recreate");
    
    TGraph *gr;
    float dac[nevents];
    float HG[4][nevents];
    float LG[4][nevents];
    float TOT[4][nevents];
    
    for(int ev = 0; ev < nevents ; ++ev){
      fChain -> GetEntry(ev);
      for(int i = 0 ; i < NSCA ; ++i) TS[i] = HITS->rollposition[i];    
      int nhits = HITS->hit_num;
      if(HITS-> inj_dac > 10000) continue;
      dac[ev] = HITS-> inj_dac;
    
      for(int hit = 0; hit < nhits ; ++hit){
	H = HITS->Hits.at(hit);
	if(H.ch != tmp_inj_ch) continue;
	for(int sca = 0;sca < NSCA; ++sca){
	  if(TS[sca] == 5){
	    HG[H.chip][ev] = H.SCA_hg[sca];
	    LG[H.chip][ev] = H.SCA_lg[sca];
	  }
	}
	TOT[H.chip][ev] = H.TOTS;
      }
    }

  
    TMultiGraph *mgr = new TMultiGraph();
    TLegend *leg = new TLegend(0.55,0.5,0.9,0.9);
    
    char GR_save[100],leg_desc[100];
    
    for(int ski = 0; ski < 4 ; ++ski){
      gr = new TGraph(nevents, dac,HG[ski] );
      gr->SetMarkerStyle(24);
      gr->SetMarkerSize(0.4);
      gr->SetMarkerColor(ski+1);
      gr->Draw("AP");
      gr->GetXaxis()->SetTitle("dac");
      gr->GetYaxis()->SetTitle("HGTS5");
      mgr->Add(gr);
      sprintf(leg_desc,"CHIP%d",ski);
      leg->AddEntry(gr,leg_desc,"P");
      sprintf(plot_title,"%s_%dCH_Id%d_HG%d", runtitle.c_str(),(int)vec_inj_ch.size(),tmp_inj_ch,ski);
      gr->SetTitle(plot_title);
      sprintf(GR_save,"HGchip%d",ski);
      gr->Write(GR_save);
        c1->Print(Form("HGchip%d.pdf",ski));
    }

  
    for(int ski = 0; ski < 4 ; ++ski){
      gr = new TGraph(nevents, dac,LG[ski] );
      gr->SetMarkerStyle(22);
      gr->SetMarkerSize(0.4);
      gr->SetMarkerColor(ski+1);
      gr->Draw("AP");
      gr->SetTitle(plot_title);
      gr->GetXaxis()->SetTitle("dac");
      gr->GetYaxis()->SetTitle("LGTS5");
      mgr->Add(gr);
        leg->AddEntry(gr,leg_desc,"P");
      sprintf(plot_title,"%s_%dCH_Id%d_LG%d", runtitle.c_str(),(int)vec_inj_ch.size(),tmp_inj_ch,ski);
      gr->SetTitle(plot_title);

      
      sprintf(GR_save,"LGchip%d",ski);
      gr->Write(GR_save);
        c1->Print(Form("LGchip%d.pdf",ski));
    }

    for(int ski = 0; ski < 4 ; ++ski){
      gr = new TGraph(nevents, dac,TOT[ski] );
      gr->SetMarkerStyle(21);
      gr->SetMarkerSize(0.4);
      gr->SetMarkerColor(ski+1);
      gr->Draw("AP");
      gr->SetTitle(plot_title);
      gr->GetXaxis()->SetTitle("dac");
      gr->GetYaxis()->SetTitle("TOT");
      mgr->Add(gr);

      sprintf(plot_title,"%s_%dCH_Id%d_TOT%d", runtitle.c_str(),(int)vec_inj_ch.size(),tmp_inj_ch,ski);
      gr->SetTitle(plot_title);
        leg->AddEntry(gr,leg_desc,"P");
      sprintf(GR_save,"TOTchip%d",ski);
      gr->Write(GR_save);
        c1->Print(Form("TOTchip%d.pdf",ski));

    }

    mgr->Draw("ap");
    mgr->GetXaxis()->SetTitle("dac");
    mgr->GetYaxis()->SetTitle("HGLGTS5 + TOT");
    leg->SetBorderSize(0);
    leg->Draw("same");
    
    c1->Update();
    //getchar();

    sprintf(plot_title,"calib_result/Plots/%dCH_Id%d_%s.png", (int)vec_inj_ch.size(),tmp_inj_ch,runtitle.c_str());
    c1->SaveAs(plot_title);
    outr->Close();
  }*/
}


void makePlots::P_and_N(int option,bool output){

  int skip_TS;
  
  int mem_of_SCA[NSCA][NCH][NSCA];
  int sumHG     [NCHIP][NCH][NSCA];
  int sumLG     [NCHIP][NCH][NSCA];
  double sumsqHG   [NCHIP][NCH][NSCA];
  double sumsqLG   [NCHIP][NCH][NSCA];  

  for(int i = 0; i < NCHIP; ++i){    
    for(int j = 0; j < NCH; ++j){
      for(int k = 0; k < NSCA; ++k){
	sumHG     [i][j][k] = 0;
	sumsqHG   [i][j][k] = 0;
	sumLG     [i][j][k] = 0;
	sumsqLG   [i][j][k] = 0;
	mem_of_SCA[i][j][k] = 0;}}}
  
  if(option == 0){
    cout << "calculate pedestal and noise based on TS 0 ~ 8" << endl;
    skip_TS = 9;  }
  
  else if(option == 1){
    cout << "calculate pedestal and noise based on TS 0 and 1"
	 << "(The test beam method)" << endl;
    skip_TS = 2;  }

  else{
    cout << "invalid option for pedestal noise calculation!" << endl;
    return;}
  
    int nevents = fChain->GetEntries();
    for(int ev = 0; ev < nevents ; ++ev){
      fChain -> GetEntry(ev);
      for(int i = 0 ; i < NSCA ; ++i)
	TS[i] = HITS->rollposition[i];

      int nhits = HITS->hit_num;
      for(int hit = 0; hit < nhits ; ++hit){
	H = HITS->Hits.at(hit);
	for(int sca = 0; sca < NSCA; ++sca){
	  if(TS[sca] >= skip_TS) continue;
	  sumHG  [H.chip][H.ch][sca] += H.SCA_hg[sca];
	  sumsqHG[H.chip][H.ch][sca] += H.SCA_hg[sca]*H.SCA_hg[sca];
	  sumLG  [H.chip][H.ch][sca] += H.SCA_lg[sca];
	  sumsqLG[H.chip][H.ch][sca] += H.SCA_lg[sca]*H.SCA_lg[sca];
	  mem_of_SCA[H.chip][H.ch][sca]++;
	}
      }
    }

    for(int i = 0; i < NCHIP; ++i){    
      for(int j = 0; j < NCH; ++j){
	for(int k = 0; k < NSCA; ++k){
	  avg_HG  [i][j][k] = (float)sumHG  [i][j][k]/mem_of_SCA[i][j][k];
	  sigma_HG[i][j][k] = (float)sumsqHG  [i][j][k]/mem_of_SCA[i][j][k];
	  sigma_HG[i][j][k] -= avg_HG  [i][j][k]*avg_HG  [i][j][k];
	  sigma_HG[i][j][k] = sqrt(sigma_HG[i][j][k]);
	  avg_LG  [i][j][k] = (float)sumLG  [i][j][k]/mem_of_SCA[i][j][k];
	  sigma_LG[i][j][k] = (float)sumsqLG  [i][j][k]/mem_of_SCA[i][j][k];
	  sigma_LG[i][j][k] -= avg_LG  [i][j][k]*avg_LG  [i][j][k];
	  sigma_LG[i][j][k] = sqrt(sigma_LG[i][j][k]); }}}
  
  if(output == true){
    string filename;
    filename = input_RUN;
    int start = filename.find_last_of("/");
    int end   = filename.find(".root");
    string outf = filename.substr(start+1,end-start-1);
    char outtitleH[100];
    char outtitleL[100];
    sprintf(outtitleH,"ped_result/%s_HG.txt",outf.c_str());
    ofstream fileHG(outtitleH);
    sprintf(outtitleL,"ped_result/%s_LG.txt",outf.c_str());
    ofstream fileLG(outtitleL);
    fileHG << "CHIP\tCH\t";
    fileLG << "CHIP\tCH\t";
    for(int i = 0; i < NSCA; ++i){
      fileHG << "SCA " << i << " ";
      fileLG << "SCA " << i << " ";}
    fileHG << "\n";
    fileLG << "\n";
    for(int i = 0; i < NCHIP; ++i){    
      for(int j = 0; j < NCH; ++j){
	fileHG << i << "\t" << j << "\t";
	fileLG << i << "\t" << j << "\t";
	for(int k = 0; k < NSCA; ++k){
	  fileHG << fixed << setprecision(2) << avg_HG[i][j][k] << " ";
	  fileLG << fixed << setprecision(2) << avg_LG[i][j][k] << " ";}
	fileHG << "\n";
	fileLG << "\n";
	fileHG << i << "\t" << j << "\t";
	fileLG << i << "\t" << j << "\t";

	for(int k = 0; k < NSCA; ++k){
	  fileHG << fixed << setprecision(2) << sigma_HG[i][j][k] << " ";
	  fileLG << fixed << setprecision(2) << sigma_LG[i][j][k] << " ";}
	fileHG << "\n";
	fileLG << "\n";      
      }
    }
    fileHG.close();
    fileLG.close();
    cout << "output mode is selected, output file will be:" << endl;
    cout << "1. " << outtitleH << "\n" << "2. " << outtitleL << endl;
  }
  
}

void makePlots::read_P_and_N(string ped_file){
  

  char HG_name[100],LG_name[100];
  sprintf(HG_name,"%s_HG.txt",ped_file.c_str());
  sprintf(LG_name,"%s_LG.txt",ped_file.c_str());
  ifstream inHG(HG_name);
  ifstream inLG(LG_name);
  if( !inHG.is_open() || !inLG.is_open()){
    cout << "File not found! Either" << HG_name << " or " << LG_name
	 << "doesn't exist!" << endl;
    return;}
  else{
    cout << "Input ped file is :" << endl;
    cout << "1. " << HG_name << "\n" << "2. "<< LG_name << endl;
    string line;
    getline(inHG,line); // remove header
    int chip,ch;
    int testeof;
    while(true){
      inHG >> testeof;
      if( inHG.eof() ) break;
      else{
	chip = testeof;
	inHG >> ch;
	for(int sca = 0; sca < NSCA ; ++sca)
	  inHG >> avg_HG[chip][ch][sca];
	inHG >> chip >> ch;
	for(int sca = 0; sca < NSCA ; ++sca)
	  inHG >> sigma_HG[chip][ch][sca];
      }      
    }
    getline(inLG,line); // remove header
    while(true){
      inLG >> testeof;
      if( inLG.eof() ) break;
      else{
	chip = testeof;
	inLG >> ch;
	for(int sca = 0; sca < NSCA ; ++sca)
	  inLG >> avg_LG[chip][ch][sca];
	inLG >> chip >> ch;
	for(int sca = 0; sca < NSCA ; ++sca)
	  inLG >> sigma_LG[chip][ch][sca];
      }      
    }
    
    cout << "Reading pedestal file done!" << endl;
    inHG.close();
    inLG.close();
  }  
}
void makePlots::readmap(){
  ifstream file("./src_txtfile/CH_map.txt");
  string line;
  int chip,ch,type,formatCH;
  double posx,posy;
  while(true){
    getline(file,line);
    if( file.eof() ) break;
    file >> chip >> ch >> posx >> posy >> type;
    formatCH = chip*32+ch/2;
    CHmap[formatCH] = make_pair(posx,posy);}
  file.close();
  //Since there is no such pad, assign a unreasonable value
  CHmap[2*32+60/2] = make_pair(1000.,1000.);

}

void makePlots::InitTH2Poly(TH2Poly& poly)
{
  int MAXVERTICES = 6;
  double HexX[MAXVERTICES];
  double HexY[MAXVERTICES];
  int iu,iv,CellXYsize;
  ifstream file("src_txtfile/poly_frame.txt");
  string line;

  
  for(int header = 0; header < 4; ++header )     getline(file,line);
  
  while(true){
    getline(file,line);
    if( file.eof() ) break;
    file >> iu >> iv >> CellXYsize;    
    for(int i = 0; i < CellXYsize ; ++i){
      getline(file,line);
      file >> HexX[i] >> HexY[i];
    }
    
    /*if(CellXYsize == 4){
      CellXYsize++;
      HexX[4] = HexX[0];
      HexY[4] = HexY[0];}*/
    poly.AddBin(CellXYsize, HexX, HexY);
  }
  file.close();

}
