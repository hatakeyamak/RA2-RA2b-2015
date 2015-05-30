
void plot_TauTemplate_SingleTemplate(int i,int icomp=3, string input=""){

  //
  // icomp=0: only show own results
  //       1: show also Koushik's results
  //
  
  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  gROOT->LoadMacro("CMS_lumi_v2.C");

  char tempname[200];
  char tempname2[200];
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
  
  Float_t legendX1 = .60; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .60; //.65;
  Float_t legendY2 = .90;
  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  //
  
//  TFile *file_08TeV         = new TFile("tauTemplatesRes_8TeV.root","R"); 
//  TFile *file_13TeV         = new TFile("HadTau_TauResponseTemplates_stacked.root","R"); 
  sprintf(tempname,"HadTau_TauResponseTemplates_TTbar_%s.root",input.c_str());
  TFile *file_13TeV         = new TFile(tempname,"R");
  TFile *file_13TeV_NoLowPtJet = new TFile("../../TauHad/HadTau_TauResponseTemplates_TTbar_.root","R"); 
  TFile *file_13TeV_TTbar   = new TFile(tempname,"R");
  TFile *file_Rishi_TauGun         = new TFile("Rishi_TauTemplate.root","R");
  TFile *file_Rishi_TTbar         = new TFile("Rishi_TTJetsResponse.root","R");

  TH1D * thist;
  catLeg1->SetHeader("p_{T}(#tau^{had}) [GeV]");

    sprintf(tempname,"hTauResp_%d",i);
    thist = (TH1D*)file_13TeV->Get(tempname)->Clone();
    sprintf(tempname2,"hTauResp_%d_AB",i);
    thist->SetName(tempname2);
    thist->SetLineColor(i+1);
    thist->SetFillColor(0);
    thist->SetLineWidth(3);

    if(i==0){
      thist->SetMaximum(1.4);
      thist->GetXaxis()->SetLabelFont(42);
      thist->GetXaxis()->SetLabelOffset(0.007);
      thist->GetXaxis()->SetLabelSize(0.04);
      thist->GetXaxis()->SetTitleSize(0.05);
      thist->GetXaxis()->SetTitleOffset(0.9);
      thist->GetXaxis()->SetTitleFont(42);
      thist->GetYaxis()->SetLabelFont(42);
      thist->GetYaxis()->SetLabelOffset(0.007);
      thist->GetYaxis()->SetLabelSize(0.04);
      thist->GetYaxis()->SetTitleSize(0.05);
      thist->GetYaxis()->SetTitleOffset(1.25);
      thist->GetYaxis()->SetTitleFont(42);
      thist->GetXaxis()->SetTitle("p_{T}(visible)/p_{T}(generated_{#tau})");
      thist->GetYaxis()->SetTitle("Probability");

    }

    thist->Draw("same,hist");
    if(i==0)sprintf(tempname,"20 - 30");
    if(i==1)sprintf(tempname,"30 - 50");
    if(i==2)sprintf(tempname,"50 - 100");
    if(i==3)sprintf(tempname,">100");
    catLeg1->AddEntry(thist,tempname,"l");
  catLeg1->Draw();

  TH1D * thist_Rishi_TauGun;
  if (icomp==3){
    sprintf(tempname,"response%d",i+2);
    thist_Rishi_TauGun = (TH1D*)file_Rishi_TauGun->Get(tempname)->Clone();
    if(thist_Rishi_TauGun->Integral("width") > 0.){
     thist_Rishi_TauGun->Scale(1./thist_Rishi_TauGun->Integral("width")); 
    }
    sprintf(tempname2,"hTauResp_%d_Rishi_TauGun",i);
    thist_Rishi_TauGun->SetName(tempname2);
    thist_Rishi_TauGun->SetLineColor(i+1);
    thist_Rishi_TauGun->SetLineWidth(3);
    thist_Rishi_TauGun->SetLineStyle(3);
    thist_Rishi_TauGun->Draw("same,hist");
    if(i==0)sprintf(tempname,"20 - 30: Rishi_TauGun");
    if(i==1)sprintf(tempname,"30 - 50: Rishi_TauGun");
    if(i==2)sprintf(tempname,"50 - 100:Rishi_TauGun");
    if(i==3)sprintf(tempname,">100: Rishi_TauGun");
    catLeg1->AddEntry(thist_Rishi_TauGun,tempname,"l");
  }

  TH1D * thist_Rishi_TTbar;
  if (icomp==3){
    sprintf(tempname,"response%d",i+2);
    thist_Rishi_TTbar = (TH1D*)file_Rishi_TTbar->Get(tempname)->Clone();
    if(thist_Rishi_TTbar->Integral("width") > 0.){
     thist_Rishi_TTbar->Scale(1./thist_Rishi_TTbar->Integral("width")); 
    }
    sprintf(tempname2,"hTauResp_%d_Rishi_TTbar",i);
    thist_Rishi_TTbar->SetName(tempname2);
    thist_Rishi_TTbar->SetLineColor(i+1);
    thist_Rishi_TTbar->SetLineWidth(3);
    thist_Rishi_TTbar->SetLineStyle(2);
    thist_Rishi_TTbar->Draw("same,hist");
    if(i==0)sprintf(tempname,"20 - 30: Rishi_TTbar");
    if(i==1)sprintf(tempname,"30 - 50: Rishi_TTbar");
    if(i==2)sprintf(tempname,"50 - 100:Rishi_TTbar");
    if(i==3)sprintf(tempname,">100: Rishi_TTbar");
    catLeg1->AddEntry(thist_Rishi_TTbar,tempname,"l");
  }

  catLeg1->Draw();  

  sprintf(tempname,"Response%d_TTbar_%s.png",i,input.c_str());
  c1->Print(tempname);

}
