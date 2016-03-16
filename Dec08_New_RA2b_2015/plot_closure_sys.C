
void shift_bin(TH1* input, TH1* output){

  char tempname[200];  
  char temptitle[200];  
  output->SetName(tempname);
  output->SetTitle(temptitle);
  output->SetBins(input->GetNbinsX(),input->GetBinLowEdge(1)-0.5,input->GetBinLowEdge(input->GetNbinsX()+1)-0.5);
  //input->Print("all");
  //output = new TH1D(tempname,temptitle,input->GetNbinsX(),input->GetBinLowEdge(1)-0.5,input->GetBinLowEdge(input->GetNbinsX()+1)-0.5); 
  // 0: underflow
  // 1: first bin [Use the lowedge of this bin]
  // input->GetNbinsX(): highest bin 
  // input->GetNbinsX()+1: overflow bin [use the lowedge of this bin]
  //

  for (int ibin=1;ibin<=input->GetNbinsX();ibin++){
    output->SetBinContent(ibin,input->GetBinContent(ibin));    
    output->SetBinError(ibin,input->GetBinError(ibin));    
    //std::cout << input->GetBinContent(ibin) << std::endl;
  }

}

void plot_closure_sys(std::string elogForPlot=""){
  
  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  gROOT->LoadMacro("CMS_lumi_v2.C");
  
  char tempname[200];
  char tempname2[200];
  int W = 1200;
  int H = 600;
  int H_ref = 600;
  int W_ref = 1200;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;
  
  double ymax=1.0;
  double ymin=0.0;
  double ytext=0.4;
  
  TCanvas* c1 = new TCanvas("name","name",10,10,W,H);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );
  c1->SetRightMargin( R/W );
  c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );
  //c1->SetTickx(0);
  //c1->SetTicky(0);

  gStyle->SetOptStat(000000);
  gStyle->SetErrorX(0.5); 
  
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
  
  //TFile *file = new TFile("LostLepton2_MuonEfficienciesFromTTbar_Elog213.root","R"); 
  //sprintf(tempname,"TauHad/Stack/%sLostLepton2_MuonEfficienciesFromstacked.root",elogForPlot.c_str());
  sprintf(tempname,"HadTauEstimation_data_formatted_treeV5_v02.root",);
  TFile *file   = new TFile(tempname,"R");

  sprintf(tempname,"searchBin_closureUncertainty");
  thist = (TH1D*)file->Get(tempname)->Clone();
  thist_input = (TH1D*)file->Get(tempname)->Clone("input");
  thist_one = (TH1D*)file->Get(tempname)->Clone("one");
  for (int ibin=1;ibin<=thist_one->GetNbinsX();ibin++){
    thist_one->SetBinContent(ibin,1.);
  }
  thist_input->Add(thist_one,-1.);

  shift_bin(thist_input,thist);
  double ymax_top=1.0;
  double ymax2_top=0.85;
  double ymin_top=0.0;
  thist->Print("all");
  
  
  thist->SetLineColor(1);
  thist->SetLineWidth(3);
  thist->SetStats(kFALSE);

  thist->SetTitle("");
  
  thist->SetMaximum(ymax);
  thist->SetMinimum(ymin);
  thist->GetXaxis()->SetLabelFont(42);
  thist->GetXaxis()->SetLabelOffset(0.007);
  thist->GetXaxis()->SetLabelSize(0.04);
  thist->GetXaxis()->SetTitleSize(0.05);
  thist->GetXaxis()->SetTitleOffset(1.0);
  thist->GetXaxis()->SetTitleFont(42);
  thist->GetYaxis()->SetLabelFont(42);
  thist->GetYaxis()->SetLabelOffset(0.007);
  thist->GetYaxis()->SetLabelSize(0.04);
  thist->GetYaxis()->SetTitleSize(0.05);
  thist->GetYaxis()->SetTitleOffset(1.20);
  thist->GetYaxis()->SetTitleFont(42);

  thist->GetYaxis()->SetTitle("Fractional Uncertainty");
  thist->GetXaxis()->SetTitle("Search region bin number");
  thist->SetMarkerStyle(20);
  thist->Draw();

  // Njet separation lines
  TLine *tl_njet = new TLine();
  tl_njet->SetLineStyle(2);
  tl_njet->SetLineWidth(3);
  tl_njet->SetLineColor(2);
  tl_njet->DrawLine(25.-0.5,ymin_top,25.-0.5,ymax_top); 
  tl_njet->DrawLine(49.-0.5,ymin_top,49.-0.5,ymax_top); 

  // Njet labels
  TLatex * ttext_njet = new TLatex();
  ttext_njet->SetTextFont(42);
  ttext_njet->SetTextColor(2);
  ttext_njet->SetTextSize(0.060);
  ttext_njet->SetTextAlign(22);
  ttext_njet->DrawLatex(13.-0.5 , ymax_top-0.1 , "4 #leq N_{#scale[0.2]{ }jet} #leq 6");
  ttext_njet->DrawLatex(37.-0.5 , ymax_top-0.1 , "7 #leq N_{#scale[0.2]{ }jet} #leq 8");
  ttext_njet->DrawLatex(61.-0.5 , ymax_top-0.1 , "N_{#scale[0.2]{ }jet} #geq 9");

  // Nb separation lines
  TLine *tl_nb = new TLine();
  tl_nb->SetLineStyle(3);
  tl_nb->SetLineColor(4);
  tl_nb->DrawLine( 7.-0.5,ymin_top, 7.-0.5,ymax2_top); 
  tl_nb->DrawLine(13.-0.5,ymin_top,13.-0.5,ymax2_top); 
  tl_nb->DrawLine(19.-0.5,ymin_top,19.-0.5,ymax2_top); 
  tl_nb->DrawLine(31.-0.5,ymin_top,31.-0.5,ymax2_top); 
  tl_nb->DrawLine(37.-0.5,ymin_top,37.-0.5,ymax2_top); 
  tl_nb->DrawLine(43.-0.5,ymin_top,43.-0.5,ymax2_top); 
  tl_nb->DrawLine(55.-0.5,ymin_top,55.-0.5,ymax2_top); 
  tl_nb->DrawLine(61.-0.5,ymin_top,61.-0.5,ymax2_top); 
  tl_nb->DrawLine(67.-0.5,ymin_top,67.-0.5,ymax2_top); 

  TLine *tl_horizontal = new TLine();
  tl_horizontal->SetLineStyle(4);
  tl_horizontal->DrawLine(0.5,0.1,72.5,0.1);
  
  // Nb labels
  TLatex * ttext_nb = new TLatex();
  ttext_nb->SetTextFont(42);
  ttext_nb->SetTextColor(4);
  ttext_nb->SetTextSize(0.060);
  ttext_nb->SetTextAlign(22);
    
  ttext_nb->DrawLatex( 4.-0.5 , ymax_top-0.2  , "N_{#scale[0.2]{ }b-jet}");
  ttext_nb->DrawLatex( 4.-0.5 , ymax_top-0.26 , "0");
  ttext_nb->DrawLatex(10.-0.5 , ymax_top-0.26 , "1");
  ttext_nb->DrawLatex(16.-0.5 , ymax_top-0.26 , "2");
  ttext_nb->DrawLatex(22.-0.5 , ymax_top-0.26 , "#geq 3");

  ttext_nb->DrawLatex( 4.+24.-0.5 , ymax_top-0.2  , "N_{#scale[0.2]{ }b-jet}");
  ttext_nb->DrawLatex( 4.+24.-0.5 , ymax_top-0.26 , "0");
  ttext_nb->DrawLatex(10.+24.-0.5 , ymax_top-0.26 , "1");
  ttext_nb->DrawLatex(16.+24.-0.5 , ymax_top-0.26 , "2");
  ttext_nb->DrawLatex(22.+24.-0.5 , ymax_top-0.26 , "#geq 3");

  ttext_nb->DrawLatex( 4.+48.-0.5 , ymax_top-0.2  , "N_{#scale[0.2]{ }b-jet}");
  ttext_nb->DrawLatex( 4.+48.-0.5 , ymax_top-0.26 , "0");
  ttext_nb->DrawLatex(10.+48.-0.5 , ymax_top-0.26 , "1");
  ttext_nb->DrawLatex(16.+48.-0.5 , ymax_top-0.26 , "2");
  ttext_nb->DrawLatex(22.+48.-0.5 , ymax_top-0.26 , "#geq 3");

  
  c1->Print("plot_closure_sys.pdf");

}
