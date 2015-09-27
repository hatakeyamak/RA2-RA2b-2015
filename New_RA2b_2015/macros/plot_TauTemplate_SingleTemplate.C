void plot_TauTemplate_SingleTemplate(int i){


  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
//  gROOT->LoadMacro("CMS_lumi_v2.C");

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

   
  TFile *file_TTbar        = new TFile("TauHad/Stack/HadTau_TauResponseTemplates_TTbar_stacked.root","R");
  TFile *file_WJet         = new TFile("TauHad/Stack/HadTau_TauResponseTemplates_WJet_stacked.root","R");


  TH1D * thist_TTbar;
  catLeg1->SetHeader("p_{T}(#tau^{had}) [GeV]");

    sprintf(tempname,"hTauResp_%d",i);
    thist_TTbar = (TH1D*)file_TTbar->Get(tempname)->Clone();
	
	if(thist_TTbar->Integral("width") > 0.){
     thist_TTbar->Scale(1./thist_TTbar->Integral("width")); 
    }
	
    sprintf(tempname2,"hTauResp_%d_AB",i);
    thist_TTbar->SetName(tempname2);
    thist_TTbar->SetLineColor(4);
    thist_TTbar->SetFillColor(0);
    thist_TTbar->SetLineWidth(3);


      thist_TTbar->SetMaximum(1.4);
      thist_TTbar->GetXaxis()->SetLabelFont(42);
      thist_TTbar->GetXaxis()->SetLabelOffset(0.007);
      thist_TTbar->GetXaxis()->SetLabelSize(0.04);
      thist_TTbar->GetXaxis()->SetTitleSize(0.05);
      thist_TTbar->GetXaxis()->SetTitleOffset(0.9);
      thist_TTbar->GetXaxis()->SetTitleFont(42);
      thist_TTbar->GetYaxis()->SetLabelFont(42);
      thist_TTbar->GetYaxis()->SetLabelOffset(0.007);
      thist_TTbar->GetYaxis()->SetLabelSize(0.04);
      thist_TTbar->GetYaxis()->SetTitleSize(0.05);
      thist_TTbar->GetYaxis()->SetTitleOffset(1.25);
      thist_TTbar->GetYaxis()->SetTitleFont(42);
      thist_TTbar->GetXaxis()->SetTitle("p_{T}(visible)/p_{T}(generated_{#tau})");
      thist_TTbar->GetYaxis()->SetTitle("Probability");


    thist_TTbar->Draw("same,hist");
    if(i==0)sprintf(tempname,"20 - 30 TTbar");
    if(i==1)sprintf(tempname,"30 - 50 TTbar");
    if(i==2)sprintf(tempname,"50 - 100 TTbar");
    if(i==3)sprintf(tempname,">100 TTbar");
    catLeg1->AddEntry(thist_TTbar,tempname,"l");
  catLeg1->Draw();

  TH1D * thist_WJet;

    sprintf(tempname,"hTauResp_%d",i);
    thist_WJet = (TH1D*)file_WJet->Get(tempname)->Clone();
    if(thist_WJet->Integral("width") > 0.){
     thist_WJet->Scale(1./thist_WJet->Integral("width")); 
    }
    sprintf(tempname2,"hTauResp_%d_WJet",i);
    thist_WJet->SetName(tempname2);
    thist_WJet->SetLineColor(2);
    thist_WJet->SetFillColor(0);
    thist_WJet->SetLineWidth(3);
    thist_WJet->SetLineStyle(3);
    thist_WJet->Draw("same,hist");
    if(i==0)sprintf(tempname,"20 - 30: WJet");
    if(i==1)sprintf(tempname,"30 - 50: WJet");
    if(i==2)sprintf(tempname,"50 - 100:WJet");
    if(i==3)sprintf(tempname,">100: WJet");
    catLeg1->AddEntry(thist_WJet,tempname,"l");
  





  catLeg1->Draw();  

  sprintf(tempname,"Response%d.png",i);
  c1->Print(tempname);

}
