#include <vector>
#include <cstdio>
using namespace std;


CalcMtEff(){
gStyle->SetOptStat(0);  ///to avoid the stat. on the plots
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

TFile * before = new TFile("HadTauEstimation_TTbar_Elog227AfterMT.root","R");
TFile * after = new TFile("HadTauEstimation_TTbar_Elog227BeforeMT.root","R");

TH1D * thist;
TH1D * thist2;
thist = (TH1D *) before->Get("searchH")->Clone("after");
thist2 = (TH1D *) after->Get("searchH")->Clone("before");

TH1D * MtCutEff = static_cast<TH1D*>(thist->Clone("MtCutEff"));
MtCutEff->Divide(thist,thist2,1,1,"B");

MtCutEff->Draw();
sprintf(tempname,"MtEff.png");
c1->Print(tempname);

TFile * outFile = new TFile("MtEff_TTbar.root","RECREATE");
MtCutEff->Write();
outFile->Close();


}
