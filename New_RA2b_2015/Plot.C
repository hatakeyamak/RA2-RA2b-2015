#include <vector>
#include <cstdio>
using namespace std;


Plot(string cutname="nocut", string histname="MHT"){

char tempname[200];
 int W = 600;
int H = 600;
int H_ref = 600;
int W_ref = 800;
float T = 0.08*H_ref;
float B = 0.12*H_ref;
float L = 0.12*W_ref;
float R = 0.04*W_ref;

TCanvas* c1 = new TCanvas("name","name",10,10,W,H);
c1->SetFillColor(0);
c1->SetBorderMode(0);
c1->SetFrameFillStyle(0);
c1->SetFrameBorderMode(0);
c1->SetLeftMargin( L/W );
c1->SetRightMargin( R/W );
c1->SetTopMargin( T/H );
c1->SetBottomMargin( B/H );
c1->SetTickx(0);
c1->SetTicky(0);



Float_t legendX1 = .75; //.50;
Float_t legendX2 = .99; //.70;
Float_t legendY1 = .60; //.65;
Float_t legendY2 = .75;
TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
catLeg1->SetTextSize(0.032);
catLeg1->SetTextFont(42);

vector<TFile *> filevec;

sprintf(tempname,"TauHad/GenInfo_HadTauEstimation_TTbar_.root");
filevec.push_back(TFile::Open(tempname,"R"));
sprintf(tempname,"TauHad2/HadTauEstimation_TTbar_.root");
filevec.push_back(TFile::Open(tempname,"R"));

/*
TH1D * thist;
TFile * file = new TFile("TauHad/GenInfo_HadTauEstimation_TTbar_.root","R");
sprintf(tempname,"EventsWith_0RecoMuon_0RecoElectron_1tauJet/%s/%s_%s_EventsWith_0RecoMuon_0RecoElectron_1tauJet",cutname.c_str(),histname.c_str(),cutname.c_str());
thist=(TH1D*) file->Get(tempname)->Clone();
*/


for(int i=0; i<filevec.size(); i++){
if(i==0){continue;sprintf(tempname,"EventsWith_0RecoMuon_0RecoElectron_1tauJet/%s/%s_%s_EventsWith_0RecoMuon_0RecoElectron_1tauJet",cutname.c_str(),histname.c_str(),cutname.c_str());}
if(i==1)sprintf(tempname,"EventsWith_1RecoMuon_0RecoElectron/%s/%s_%s_EventsWith_1RecoMuon_0RecoElectron",cutname.c_str(),histname.c_str(),cutname.c_str());
thist=(TH1D*) filevec.at(i)->Get(tempname)->Clone();
thist->SetLineColor(i+3);
thist->Draw("same");
if(i==0)sprintf(tempname,"FromGenInfo");
if(i==1)sprintf(tempname,"DataDriven");
catLeg1->AddEntry(thist,tempname,"l");
}
catLeg1->Draw();
sprintf(tempname,"%s_%s_Plot.pdf",cutname.c_str(),histname.c_str());
c1->Print(tempname);




}
