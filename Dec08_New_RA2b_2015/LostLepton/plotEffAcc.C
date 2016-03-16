{
#include "../utils2.h"

// Open the file
  TFile * file = new TFile("LostLepton2_MuonEfficienciesFromTTbar_.root","R");
//  TFile * file2 = new TFile("LostLepton2_MuonEfficiencies_stacked.root","R");

  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots
  char tempname[200];
  // Define legend
  //
  Float_t legendX1 = .60; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .60; //.65;
  Float_t legendY2 = .80;

  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);

  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  //
  // Define c1
  //
  int W = 1000;
  int H = 500;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.08*W_ref;

  TCanvas *c1 = new TCanvas("c1","c1",10,10,W,H);

  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );
  c1->SetRightMargin( R/W );
  c1->SetRightMargin( 0.2 );
  c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );
  c1->SetTickx(0);
  c1->SetTicky(0);


//...........................................................................//
// TTbar ....................................................................//
//...........................................................................//


// Declare the histogram here
  TH1D * thist;
  thist = (TH1D*) file->Get("hAcc")->Clone("Acceptance");
  thist->SetTitle("Acceptance");
//  thist->Draw();

thist->DrawCopy();
//////////////
int binN=0;
for(int bNjet=1; bNjet<=3;  bNjet++){
    for(int bHtMht=1; bHtMht<=6; bHtMht++){
        binN++;
        if(thist->GetBinContent(binN)==1)continue;
        thist->GetXaxis()->SetRange(binN,binN);
        thist->SetMarkerColor(bHtMht);
        thist->SetMarkerStyle(bNjet+19);
        thist->DrawCopy("same");
    }
}
/////////////


//...........................................................................//
// TTbar + WJet .............................................................//
//...........................................................................//
/*
// Declare the histogram here
  TH1D * thist2;
  thist2 = (TH1D*) file2->Get("hAcc")->Clone("Acceptance");
  thist2->SetTitle("Acceptance");
//  thist2->Draw();

thist2->DrawCopy();
//////////////
int binN=0;
for(int bNjet=1; bNjet<=3;  bNjet++){
    for(int bHtMht=1; bHtMht<=6; bHtMht++){
        binN++;
        if(thist2->GetBinContent(binN)==1)continue;
        thist2->GetXaxis()->SetRange(binN,binN);
        thist2->SetMarkerColor(bHtMht);
        thist2->SetMarkerStyle(bNjet+19);
        thist2->DrawCopy("same");
    }
}
*/
/////////////

  c1->Print("Acceptance.png");



//...........................................................................//
// TTbar ....................................................................//
//...........................................................................//


  thist = (TH1D*) file->Get("hEff")->Clone("Efficiency");
  thist->SetTitle("Efficiency");
//  thist->Draw();


thist->DrawCopy();
//////////////
int binN=0;
for(int bNjet=1; bNjet<=3;  bNjet++){
    for(int bHtMht=1; bHtMht<=6; bHtMht++){
        binN++;
        if(thist->GetBinContent(binN)==1)continue;
        thist->GetXaxis()->SetRange(binN,binN);
        thist->SetMarkerColor(bHtMht);
        thist->SetMarkerStyle(bNjet+19);
        thist->DrawCopy("same");
    }
}
/////////////


//...........................................................................//
// TTbar + WJet .............................................................//
//...........................................................................//
/*
  thist2 = (TH1D*) file2->Get("hEff")->Clone("Efficiency");
  thist2->SetTitle("Efficiency");
//  thist2->Draw();


thist2->DrawCopy();
//////////////
int binN=0;
for(int bNjet=1; bNjet<=3;  bNjet++){
    for(int bHtMht=1; bHtMht<=6; bHtMht++){
        binN++;
        if(thist2->GetBinContent(binN)==1)continue;
        thist2->GetXaxis()->SetRange(binN,binN);
        thist2->SetMarkerColor(bHtMht);
        thist2->SetMarkerStyle(bNjet+19);
        thist2->DrawCopy("same");
    }
}
*/
/////////////

  c1->Print("Efficiency.png");












}
