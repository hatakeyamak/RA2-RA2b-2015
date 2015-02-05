#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>

using namespace std;


Plot2(string cutname="nocut", string histname="MHT"){

gStyle->SetOptStat(0);  ///to avoid the stat. on the plots 
char tempname[200];

vector<TFile *> filevec;

sprintf(tempname,"TauHad/GenInfo_HadTauEstimation_TTbar_.root");
filevec.push_back(TFile::Open(tempname,"R"));
sprintf(tempname,"TauHad2/HadTauEstimation_TTbar_.root");
filevec.push_back(TFile::Open(tempname,"R"));

Float_t legendX1 = .75; //.50;
Float_t legendX2 = .99; //.70;
Float_t legendY1 = .60; //.65;
Float_t legendY2 = .75;
TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
catLeg1->SetTextSize(0.032);
catLeg1->SetTextFont(42);

TCanvas canvas("canvas");
  canvas.Divide(1, 2);
  
  TPad* canvas_up = (TPad*) canvas.GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas.GetListOfPrimitives()->FindObject("canvas_2");
 
  // define the size
  double up_height     = 0.8; // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.40; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1; // please tune the font size parameter for bottom figure
  
  double dw_height    = (1. - up_height) * dw_correction;
 
  // set pad size
  canvas_up->SetPad(0., 1 - up_height, 1., 1.);
  canvas_dw->SetPad(0., 0., 1., dw_height);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);
  
  // draw top figure
  canvas_up->cd();

TH1D * GenHist, * EstHist;

for(int i=0; i<filevec.size(); i++){
if(i==0){
sprintf(tempname,"EventsWith_0RecoMuon_0RecoElectron_1tauJet/%s/%s_%s_EventsWith_0RecoMuon_0RecoElectron_1tauJet",cutname.c_str(),histname.c_str(),cutname.c_str());
GenHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
}
if(i==1){
sprintf(tempname,"EventsWith_1RecoMuon_0RecoElectron/%s/%s_%s_EventsWith_1RecoMuon_0RecoElectron",cutname.c_str(),histname.c_str(),cutname.c_str());
EstHist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
}
thist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
thist->SetLineColor(i+3);
if(histname=="HT"){
thist->SetMaximum(7500);
}

thist->Draw("same");
if(i==0)sprintf(tempname,"FromGenInfo");
if(i==1)sprintf(tempname,"DataDriven");
catLeg1->AddEntry(thist,tempname,"l");
}
catLeg1->Draw();

GenHist->Divide(EstHist);
// draw bottom figure
  canvas_dw->cd();
  // font size
  GenHist->GetXaxis()->SetLabelSize(font_size_dw);
  GenHist->GetXaxis()->SetTitleSize(font_size_dw);
  GenHist->GetYaxis()->SetLabelSize(font_size_dw);
  GenHist->GetYaxis()->SetTitleSize(font_size_dw);

GenHist->Draw();

sprintf(tempname,"%s_%s_Plot.pdf",cutname.c_str(),histname.c_str());
canvas.Print(tempname);





}
