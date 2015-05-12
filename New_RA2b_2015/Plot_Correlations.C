#include <cstdio>
using namespace std;

Plot_Correlations(){
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

TFile * file = new TFile("TauHad2/HadTauEstimation_TTbar_.root","R");

TH1D * searchH, * searchH_b, * htH, *mhtH, *njetH, *nbH;

searchH = (TH1D*) file->Get("hCorSearch_noW")->Clone();
searchH_b = (TH1D*) file->Get("hCorSearch_noW_b")->Clone();
htH = (TH1D*) file->Get("hCorHT_noW")->Clone();
mhtH = (TH1D*) file->Get("hCorMHT_noW")->Clone();
njetH = (TH1D*) file->Get("hCorNJet_noW")->Clone();
nbH = (TH1D*) file->Get("hCorNBtag_noW")->Clone();

searchH->Draw();
c1->Print("Plots/SearchBinCorrelation_noW.png");
searchH_b->Draw();
c1->Print("Plots/SearchBinCorrelation_noW_b.png");
htH->Draw();
c1->Print("Plots/htCorrelation_noW.png");
mhtH->Draw();
c1->Print("Plots/mhtCorrelation_noW.png");
njetH->Draw();
c1->Print("Plots/njetCorrelation_noW.png");
nbH->Draw();
c1->Print("Plots/nbCorrelation_noW.png");


}
