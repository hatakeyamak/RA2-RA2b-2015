#include <vector>
#include <cstdio>
#include <string> 
#include <cmath>
using namespace std;



Plot_TauId(string histname="searchH_b_", string cutname="tauId1124_iso", 
		   double lumi=10., double lumiControl=10.,
		   bool normalize=false, int rebin=0
		   ){

  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents.
  //
  // Set basic style
  //
  gStyle->SetPalette(1) ; // for better color output
  /*
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  gROOT->LoadMacro("CMS_lumi.C");

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)
  int iPos =10;
  */
  
  TString line = "";
  char tempname[200];
  sprintf(tempname,"%8.1f",lumi);
  line+=tempname;
  line+=" fb^{-1} (13 TeV)";
  TString lumi_sqrtS = line;

  ///////////////////////////////////////////////////////////////////////////////////////////

  int W = 900;
  int H = 600;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.02*H_ref;
  float B = 1.*H_ref;
  float L = 0.08*W_ref;
  float R = 0.08*W_ref;

  double xtext_top;
  double ymax_top=1000000.;
  double ymin_top=1.;
  double xmax=192.;
  double xmin=1.0;
  
  float ymax2_top = 3000.;
  float ymax3_top = 3000.;
  float ymax4_top = 3000.;
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  //
  // More specific style set, opening input files etc

  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots
  char xtitlename[200];
  char ytitlename[200];

  sprintf(tempname,"Main/results_filelist_Spring15_T1qqqq_1000_800_00-March31_00.root");
  TFile * ExpSignal1 = new TFile(tempname,"R");
  sprintf(tempname,"Main/results_filelist_Spring15_T1bbbb_1500_100_00-March31_00.root");
  TFile * ExpSignal2 = new TFile(tempname,"R");
  sprintf(tempname,"Main/results_filelist_Spring15_T1bbbb_1000_900_00-March31_00.root");
  TFile * ExpSignal3 = new TFile(tempname,"R");
  sprintf(tempname,"Main/results_filelist_Spring15_T1tttt_1200_800_00-March31_00.root");
  TFile * ExpSignal4 = new TFile(tempname,"R");
  sprintf(tempname,"Main/results_filelist_Spring15_T1tttt_1500_100_00-March31_00.root");
  TFile * ExpSignal5 = new TFile(tempname,"R");
  TFile * ExpTT = new TFile("Main/results_filelist_Spring15_TTbar_March31.root","R");
  TFile * ExpWJ = new TFile("Main/results_filelist_Spring15_WJet_March31.root","R");
  TFile * ExpT  = new TFile("Main/results_filelist_Spring15_SingleT_March31.root","R");
  TFile * ExpZJ = new TFile("Main/results_filelist_Spring15_ZJet_March31.root","R");
  TFile * ExpQCD = new TFile("Main/results_filelist_Spring15_QCD_March31.root","R");
  
  //
  // Define legend
  //
  Float_t legendX1 = .15; //.50;
  Float_t legendX2 = .45; //.70;
  Float_t legendY1 = .72; //.65;
  Float_t legendY2 = .92;

  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);

  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);
  catLeg1->SetNColumns(2);
  catLeg1->SetColumnSeparation(1.5);
  //
  // Define canvas
  //
  TCanvas *canvas = new TCanvas("canvas","canvas",10,10,W,H);
 
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L/W );
  canvas->SetRightMargin( R/W );
  canvas->SetTopMargin( T/H*3.0 );
  canvas->SetBottomMargin( B/H );
  canvas->SetTickx(0);
  canvas->SetTicky(0);
  canvas->SetLogy();
  /*
  canvas->Divide(1, 2);
  canvas_1->SetTopMargin(0.1);
  canvas_2->SetBottomMargin(1.8);

  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
 
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel
 
  // set pad size
  canvas_up->SetPad(0., 1 - up_height, 0.97, 1.);
  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.30);
  
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);
  
  // draw top figure
  canvas_up->cd();
  */
  
  TH1D * hExpTT, * hExpWJ, * hExpT, * hExpZJ, * hExpQCD;
  TH1D * hExpSignal1;
  THStack * stackTT, * stackWJ, * stackT, * stackZJ, * stackQCD, * ExpStack;
  ExpStack = new THStack("","");

  double HT_x_max=2500.;
  double HT_x_min=400.;
  double MHT_x_max=1000.;
  double NJet_x_max=15.;
  double NBtag_x_max=4.;
  double search_x_max=19.;
  double search_x_min=1.;

  //sprintf(tempname,"allEvents/%s/StatError_%s_allEvents",cutname.c_str(),cutname.c_str());
  //hPreData_StatError  =(TH1D*) ExpSignal1->Get(tempname)->Clone("hPreData_StatError");
  sprintf(tempname,"allEvents/%s/%s",cutname.c_str(),histname.c_str());
  hExpSignal1  =(TH1D*) ExpSignal1->Get(tempname)->Clone("hExpSignal1");
  hExpSignal2  =(TH1D*) ExpSignal2->Get(tempname)->Clone("hExpSignal2");
  hExpSignal3  =(TH1D*) ExpSignal3->Get(tempname)->Clone("hExpSignal3");
  hExpSignal4  =(TH1D*) ExpSignal4->Get(tempname)->Clone("hExpSignal4");
  hExpSignal5  =(TH1D*) ExpSignal5->Get(tempname)->Clone("hExpSignal5");
  //hPreTT  =(TH1D*) PreTT->Get(tempname)->Clone();
  //hPreWJ12=(TH1D*) PreWJ12->Get(tempname)->Clone();
  //hPreWJ24=(TH1D*) PreWJ24->Get(tempname)->Clone();
  //hPreWJ46=(TH1D*) PreWJ46->Get(tempname)->Clone();
  //hPreWJ6I=(TH1D*) PreWJ6I->Get(tempname)->Clone();

  sprintf(tempname,"allEvents/%s/%s",cutname.c_str(),histname.c_str());
  hExpTT=(TH1D*) ExpTT->Get(tempname)->Clone("ExpTT"); 
  hExpWJ=(TH1D*) ExpWJ->Get(tempname)->Clone("ExpWJ");   
  hExpT=(TH1D*) ExpT->Get(tempname)->Clone("ExpT");
  hExpZJ=(TH1D*) ExpZJ->Get(tempname)->Clone("ExpZJ");
  hExpQCD=(TH1D*) ExpQCD->Get(tempname)->Clone("ExpQCD");

  double scaleSig=1.;
  TH1D * hSignal1 = static_cast<TH1D*>(hExpSignal1->Clone("hSignal1"));
  hSignal1->Scale(scaleSig*lumi/lumiControl);
  TH1D * hSignal2 = static_cast<TH1D*>(hExpSignal2->Clone("hSignal2"));
  hSignal2->Scale(scaleSig*lumi/lumiControl);
  TH1D * hSignal3 = static_cast<TH1D*>(hExpSignal3->Clone("hSignal3"));
  hSignal3->Scale(scaleSig*lumi/lumiControl);
  TH1D * hSignal4 = static_cast<TH1D*>(hExpSignal4->Clone("hSignal4"));
  hSignal4->Scale(scaleSig*lumi/lumiControl);
  TH1D * hSignal5 = static_cast<TH1D*>(hExpSignal5->Clone("hSignal5"));
  hSignal5->Scale(scaleSig*lumi/lumiControl);

  TH1D * hExp_forScale = static_cast<TH1D*>(hExpTT->Clone("hExp_forScale"));
  hExp_forScale->Add(hExpZJ);
  hExp_forScale->Add(hExpWJ);
  hExp_forScale->Add(hExpQCD);
  hExp_forScale->Add(hExpT);
  
 // hSignal1->SetMarkerSize(1.2);
 // hSignal1->SetMarkerStyle(20);

  printf("Total signal: %8.2f\nTotal Background:  %8.2f\n",hSignal1->GetSumOfWeights(),hExp_forScale->GetSumOfWeights());
  //printf("Bin content: %g Stat error: %g \n ",hPreData_StatError->GetBinContent(1)/trigEff,hPreData_StatError->GetBinError(1));
  //printf("scale to match exp to pre = %10.5f, and %10.5f from lumi info\n",scale,lumi/(3.));
  
  hExpTT->SetFillColor(kBlue);
  hExpWJ->SetFillColor(kMagenta-1);
  hExpT->SetFillColor(kRed);
  hExpZJ->SetFillColor(kCyan);
  hExpQCD->SetFillColor(kGreen);
  
  TH1D * hExp = static_cast<TH1D*>(hExpTT->Clone("hExp"));
  hExp->Add(hExpZJ);
  hExp->Add(hExpWJ);
  hExp->Add(hExpQCD);
  hExp->Add(hExpT);

  ExpStack->Add(hExpT);
  ExpStack->Add(hExpQCD);
  ExpStack->Add(hExpWJ);
  ExpStack->Add(hExpTT);
  ExpStack->Add(hExpZJ);
  
  
    xtext_top = 1800.;
    //y_legend  = 2000.;
    sprintf(xtitlename,"Search region bin number");
    sprintf(ytitlename,"Events");
    


  // Actually draw plots
  int linewidth =3;
  hSignal1->GetXaxis()->SetTitleSize(0.04);
  hSignal1->GetXaxis()->SetTitleOffset(0.8);
  hSignal1->GetXaxis()->SetTitleFont(42);
  hSignal1->GetXaxis()->SetLabelSize(0.03);
  hSignal1->GetXaxis()->SetLabelOffset(0.01);
  //hSignal1->GetYaxis()->SetLabelFont(42);
  //hSignal1->GetYaxis()->SetLabelOffset(0.007);
  //hSignal1->GetYaxis()->SetLabelSize(0.04);
  hSignal1->GetYaxis()->SetTitleSize(0.04);
  hSignal1->GetYaxis()->SetTitleOffset(0.7);
  hSignal1->GetYaxis()->SetTitleFont(42);
  hSignal1->GetYaxis()->SetLabelSize(0.03);

  hSignal1->GetXaxis()->SetTitle(xtitlename);
  hSignal1->GetYaxis()->SetTitle(ytitlename);
  hSignal1->SetLineColor(1);
  hSignal1->SetMaximum(ymax_top);
  hSignal1->SetMinimum(ymin_top);
  hSignal1->GetXaxis()->SetRangeUser(xmin,xmax);
  if(cutname=="isoPion")sprintf(tempname,"Isolated pion track");
  else sprintf(tempname,"");
  hSignal1->SetTitle(tempname);
  hSignal1->SetLineColor(kBlack);
  hSignal1->SetLineWidth(linewidth);
  /*
  hSignal2->SetTitle("");
  hSignal2->SetLineColor(kRed+1);
  hSignal2->SetLineWidth(linewidth);
  hSignal3->SetTitle("");
  hSignal3->SetLineColor(kGreen);
  hSignal3->SetLineWidth(linewidth);
  hSignal4->SetTitle("");
  hSignal4->SetLineColor(kRed-6);
  hSignal4->SetLineWidth(linewidth);
  hSignal5->SetTitle("");
  hSignal5->SetLineColor(kMagenta);
  hSignal5->SetLineWidth(linewidth);
  */
  hSignal1->Draw("same");
  ExpStack->Draw("same hist");
  hSignal1->Draw("same hist");
  /*
  hSignal2->Draw("same hist");
  hSignal3->Draw("same hist");
  hSignal4->Draw("same hist");
  hSignal5->Draw("same hist");
  */

  
  sprintf(tempname,"T1qqqq_1000_800");
  catLeg1->AddEntry(hSignal1,tempname);
  /*
  sprintf(tempname,"T1bbbb_1500_100 x %g",scaleSig);
  catLeg1->AddEntry(hSignal2,tempname);
  sprintf(tempname,"T1bbbb_1000_900 x %g",scaleSig);
  catLeg1->AddEntry(hSignal3,tempname);
  sprintf(tempname,"T1tttt_1200_800 x %g",scaleSig);
  catLeg1->AddEntry(hSignal4,tempname);
  sprintf(tempname,"T1tttt_1500_100 x %g",scaleSig);
  catLeg1->AddEntry(hSignal5,tempname);
  */
  sprintf(tempname,"t#bar{t}");
  catLeg1->AddEntry(hExpTT,tempname,"f");
  sprintf(tempname,"W + jets");
  catLeg1->AddEntry(hExpWJ,tempname,"f");  
  sprintf(tempname,"single top");
  catLeg1->AddEntry(hExpT,tempname,"f");
  sprintf(tempname,"Z + jets");
  catLeg1->AddEntry(hExpZJ,tempname,"f");
  sprintf(tempname,"QCD");
  catLeg1->AddEntry(hExpQCD,tempname,"f");
  
  catLeg1->Draw();
  
  {
//    CMS_lumi( canvas_up, iPeriod, iPos );   // writing the lumi information and the CMS "logo"
  }
  canvas->Update();
  canvas->RedrawAxis();
   
/*
  sprintf(tempname,"CMS Preliminary, %.0f fb^{-1}, #sqrt{s} = 13 TeV",lumi);
  TLatex * ttext = new TLatex(xmin, ymax_top*1.3,tempname);
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.050);
  ttext->SetTextAlign(11);
  //  ttext->Draw();
*/
  gPad->RedrawAxis(); 
  if(histname=="searchH_b_"){
     TLine *tl_njet = new TLine();
    tl_njet->SetLineStyle(2);
    tl_njet->DrawLine(25.-0.5,ymin_top,25.-0.5,ymax_top); 
    tl_njet->DrawLine(49.-0.5,ymin_top,49.-0.5,ymax_top); 

    // Njet labels
    TLatex * ttext_njet = new TLatex();
    ttext_njet->SetTextFont(42);
    //ttext_njet->SetTextSize(0.060);
    ttext_njet->SetTextSize(0.040);
    ttext_njet->SetTextAlign(22);
    ttext_njet->DrawLatex(13.-0.5 , ymax_top/100. , "4 #leq N_{#scale[0.2]{ }jet} #leq 6");
    ttext_njet->DrawLatex(37.-0.5 , ymax_top/100. , "7 #leq N_{#scale[0.2]{ }jet} #leq 8");
    ttext_njet->DrawLatex(61.-0.5 , ymax_top/100. , "N_{#scale[0.2]{ }jet} #geq 9");

    // Nb separation lines
    TLine *tl_nb = new TLine();
    tl_nb->SetLineStyle(3);
    tl_nb->DrawLine( 7.-0.5,ymin_top, 7.-0.5,ymax2_top); 
    tl_nb->DrawLine(13.-0.5,ymin_top,13.-0.5,ymax2_top); 
    tl_nb->DrawLine(19.-0.5,ymin_top,19.-0.5,ymax2_top); 
    tl_nb->DrawLine(31.-0.5,ymin_top,31.-0.5,ymax3_top); 
    tl_nb->DrawLine(37.-0.5,ymin_top,37.-0.5,ymax3_top); 
    tl_nb->DrawLine(43.-0.5,ymin_top,43.-0.5,ymax3_top); 
    tl_nb->DrawLine(55.-0.5,ymin_top,55.-0.5,ymax4_top); 
    tl_nb->DrawLine(61.-0.5,ymin_top,61.-0.5,ymax4_top); 
    tl_nb->DrawLine(67.-0.5,ymin_top,67.-0.5,ymax4_top); 
    
    // Nb labels
    TLatex * ttext_nb = new TLatex();
    ttext_nb->SetTextFont(42);
    //ttext_nb->SetTextSize(0.060);
    ttext_nb->SetTextSize(0.040);
    ttext_nb->SetTextAlign(22);
    
    ttext_nb->DrawLatex( 4.-0.5 , ymax_top/80. , "N_{#scale[0.2]{ }b-jet}");
    ttext_nb->DrawLatex( 4.-0.5 , ymax_top/170. , "0");
    ttext_nb->DrawLatex(10.-0.5 , ymax_top/170. , "1");
    ttext_nb->DrawLatex(16.-0.5 , ymax_top/170. , "2");
    ttext_nb->DrawLatex(22.-0.5 , ymax_top/170. , "#geq 3");
  }
  else if(histname=="searchH_"){
    TLine *tl_njet = new TLine();
    tl_njet->SetLineStyle(2);
    tl_njet->DrawLine(7.,ymin_top,7.,ymax_top/10.); 
    tl_njet->DrawLine(13.,ymin_top,13.,ymax_top/10.); 

    // Njet labels
    TLatex * ttext_njet = new TLatex();
    ttext_njet->SetTextFont(42);
    //ttext_njet->SetTextSize(0.060);
    ttext_njet->SetTextSize(0.040);
    ttext_njet->SetTextAlign(22);
    ttext_njet->DrawLatex(4. , ymax_top/100. , "4 #leq N_{#scale[0.2]{ }jet} #leq 6");
    ttext_njet->DrawLatex(10. , ymax_top/100. , "7 #leq N_{#scale[0.2]{ }jet} #leq 8");
    ttext_njet->DrawLatex(17. , ymax_top/100. , "N_{#scale[0.2]{ }jet} #geq 9");
  }
  
  
  
 /* 
  //
  // Bottom ratio plot
  //
  // ----------

  //KH -- flip the numerator and denominator
  TH1D * hPreOverExp = (TH1D*) hSignal1->Clone();

  for (int ibin=0;ibin<hPreOverExp->GetNbinsX();ibin++){
    if (hPreOverExp->GetBinContent(ibin+1)<lowPredictionCutOff){
      hPreOverExp->SetBinContent(ibin+1,0.);
      hPreOverExp->SetBinError(ibin+1,0.);
    }
  }
  
  hPreOverExp->Divide(hExp);

  hPreOverExp->Print("all");

  // draw bottom figure
  canvas_dw->cd();
  // font size
  hPreOverExp->GetXaxis()->SetLabelSize(font_size_dw);
  hPreOverExp->GetXaxis()->SetTitleSize(font_size_dw);
  hPreOverExp->GetYaxis()->SetLabelSize(font_size_dw);
  hPreOverExp->GetYaxis()->SetTitleSize(font_size_dw);
  
  //
  // Common to all bottom plots
  //
  sprintf(ytitlename,"Data / MC");
  hPreOverExp->GetYaxis()->SetTitle(ytitlename);
  hPreOverExp->SetMaximum(2.65);
  hPreOverExp->SetMinimum(0.0);

  //
  // Specific to each bottom plot
  //
  //sprintf(xtitlename,"search bin");
  hPreOverExp->GetXaxis()->SetRangeUser(xmin,xmax);
  TLine *tline = new TLine(xmin,1.,xmax,1.);
  
  // Setting style
  //hPreOverExp->SetMaximum(1.4);
  //hPreOverExp->GetXaxis()->SetLabelFont(42);
  hPreOverExp->GetXaxis()->SetLabelOffset(0.007);
  hPreOverExp->GetXaxis()->SetLabelSize(0.12);
  hPreOverExp->GetXaxis()->SetTitleSize(0.16);
  hPreOverExp->GetXaxis()->SetTitleOffset(0.80);
  hPreOverExp->GetXaxis()->SetTitleFont(42);
  //hPreOverExp->GetYaxis()->SetLabelFont(42);
  hPreOverExp->GetYaxis()->SetLabelOffset(0.007);
  hPreOverExp->GetYaxis()->SetLabelSize(0.12);
  hPreOverExp->GetYaxis()->SetTitleSize(0.16);
  hPreOverExp->GetYaxis()->SetTitleOffset(0.3);
  hPreOverExp->GetYaxis()->SetTitleFont(42);
  hPreOverExp->GetXaxis()->SetTickSize(0.08);

  hPreOverExp->SetTitle("");
  hPreOverExp->Draw();
  tline->SetLineStyle(2);
  tline->Draw();

  hPreOverExp->Print("all");
  */
  sprintf(tempname,"tauId_SignalVsBG_%s_%s_Plot.pdf",cutname.c_str(),histname.c_str());
  canvas->Print(tempname);
 
   printf(" ####### \n bin  background  signal1 Q1 signal2 Q2 signal3 Q3 signla4 Q4 signal5 Q5 \n ");
   for(int i=1;i<hSignal1->GetXaxis()->GetNbins()+1;i++){
	   double s1 = hSignal1->GetBinContent(i);
           double s2 = hSignal2->GetBinContent(i);
           double s3 = hSignal3->GetBinContent(i);
           double s4 = hSignal4->GetBinContent(i);
           double s5 = hSignal5->GetBinContent(i);
	   double b = hExp->GetBinContent(i);
	   double q1 = 2*(sqrt(s1+b)-sqrt(b));
           double q2 = 2*(sqrt(s2+b)-sqrt(b));
           double q3 = 2*(sqrt(s3+b)-sqrt(b));
           double q4 = 2*(sqrt(s4+b)-sqrt(b));
           double q5 = 2*(sqrt(s5+b)-sqrt(b));

	   //printf("  %d, %5.2f,  %5.2f,  %5.2f,  %5.2f,  %5.2f,  %5.2f,  %5.2f,  %5.2f,  %5.2f,  %5.2f,  %5.2f, \n ",i,b,s1,q1,s2,q2,s3,q3,s4,q4,s5,q5);
          printf("  %d, %5.2f,  %5.2f,  %5.2f, \n ",i,b,s1,q1);
	  
   }
  




}
