#include <vector>
#include <cstdio>

using namespace std;

/*

.L Plot_searchBin_full.C
Plot_searchBin_full("stacked","searchH_b","Elog365_");
Plot_searchBin_full("stacked","QCD_Low","Elog365_");
Plot_searchBin_full("stacked","QCD_Up","Elog365_");

root.exe -b -q 'Plot_searchBin_full.C("stacked","searchH_b","Elog365_")'
root.exe -b -q 'Plot_searchBin_full.C("stacked","QCD_Low","Elog365_")'
root.exe -b -q 'Plot_searchBin_full.C("stacked","QCD_Up","Elog365_")'

*/

Plot_searchBin_full(string sample="stacked",string histname="searchH_b",string elog="",int pull=0,int choice=1){

  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents.
  //
  // Set basic style
  //
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();
  gStyle->SetPalette(1) ; // for better color output
  gROOT->LoadMacro("CMS_lumi_v2.C");

  //
  // Canvas size
  int W = 1200;
  int H = 600;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.08*W_ref;

  //
  // Various vertical line coordinates
  float ymax_top = 40000.;
  float ymin_top = 0.015;

  float ymax2_top = 1000.;
  float ymax3_top = 200.;
  float ymax4_top = 30.;

  float ymax_bottom = 1.65;
  float ymin_bottom = 0.5;
  //float ymax_bottom = 1.50;
  //float ymin_bottom = 0.5;

  float ymax2_bottom = 2.15;
  float ymax3_bottom = 2.15;
  float ymax4_bottom = 2.15;

  //
  // Luminosity information for scaling
  double lumi = 10.; // normaliza to 10 (fb-1)

  double xsec_ttbar   = 806.1; // (pb) https://twiki.cern.ch/twiki/bin/viewauth/CMS/RA2b13TeV
  int    nevent_ttbar = 25348009;
  double lumi_ttbar   = 31.445; // (fb-1)
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  //
  // More specific style set, opening input files etc

  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots
  char tempname[200];
  char xtitlename[200];
  char ytitlename[200];

  if(sample.find("stack")==string::npos)sprintf(tempname,"TauHad/%sGenInfo_HadTauEstimation_%s.root",elog.c_str(),sample.c_str());
  else sprintf(tempname,"TauHad/Stack/%sGenInfo_HadTauEstimation_%s.root",elog.c_str(),sample.c_str());
  //cout << "warning:\n Warning \n \n  using elog195 for pre and  exp \n \n ";
  TFile * GenFile = new TFile(tempname,"R");
  printf("Opened %s\n",tempname);
  if(sample.find("stack")==string::npos)sprintf(tempname,"TauHad2/%sHadTauEstimation_%s.root",elog.c_str(),sample.c_str());
  else sprintf(tempname,"TauHad2/Stack/%sHadTauEstimation_%s.root",elog.c_str(),sample.c_str());
  TFile * EstFile = new TFile(tempname,"R");
  printf("Opened %s\n",tempname);

  //
  // Define legend
  //
  Float_t legendX1 = .66; //.50;
  Float_t legendX2 = .85; //.70;
  Float_t legendY1 = .80; //.65;
  Float_t legendY2 = .92;

  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);

  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

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
  canvas->SetRightMargin( 0.1 );
  canvas->SetTopMargin( T/H );
  canvas->SetBottomMargin( B/H );
  canvas->SetTickx(0);
  canvas->SetTicky(0);

  canvas->Divide(1, 2);
  
  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");

  //
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel

  //
  // set pad size
  canvas_up->SetPad(0., 1 - up_height, 0.97, 1.);
  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.25);
  
  //
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);
  
  //
  // draw top figure
  canvas_up->cd();

  TH1D * GenHist, * EstHist,* thist;
  TH1D * histTemplate;
  THStack *tempstack;

  double HT_x_max=2500.;
  double HT_x_min=400.;
  double MHT_x_max=1000.;
  double NJet_x_max=15.;
  double NBtag_x_max=4.;
  double search_x_max=73.;
  if(histname.find("QCD")!=string::npos)search_x_max=224.;
  double search_x_min=1.;

  sprintf(tempname,"%s",histname.c_str());
  if(sample.find("stacked")!=string::npos){
    tempstack=(THStack*)EstFile->Get(tempname)->Clone();
    EstHist=(TH1D*) tempstack->GetStack()->Last();
    tempstack=(THStack*)GenFile->Get(tempname)->Clone();   
    GenHist=(TH1D*) tempstack->GetStack()->Last();
    tempstack=(THStack*)EstFile->Get(tempname)->Clone();
    EstHistD=(TH1D*) tempstack->GetStack()->Last();
    tempstack=(THStack*)GenFile->Get(tempname)->Clone();
    GenHistD=(TH1D*) tempstack->GetStack()->Last();    
  }
  else{
    EstHist=(TH1D*) EstFile->Get(tempname)->Clone();
    GenHist=(TH1D*) GenFile->Get(tempname)->Clone();
    EstHistD=(TH1D*) EstFile->Get(tempname)->Clone();
    GenHistD=(TH1D*) GenFile->Get(tempname)->Clone();
  }
  GenHist->SetLineColor(2);
  EstHist->SetLineColor(4);
  //GenHist->GetXaxis()->SetLabelFont(42);
  //GenHist->GetXaxis()->SetLabelOffset(0.007);
  //GenHist->GetXaxis()->SetLabelSize(0.04);
  GenHist->GetXaxis()->SetTitleSize(0.05);
  GenHist->GetXaxis()->SetTitleOffset(0.9);
  GenHist->GetXaxis()->SetTitleFont(42);
  //GenHist->GetYaxis()->SetLabelFont(42);
  //GenHist->GetYaxis()->SetLabelOffset(0.007);
  //GenHist->GetYaxis()->SetLabelSize(0.04);
  GenHist->GetYaxis()->SetTitleSize(0.05);
  GenHist->GetYaxis()->SetTitleOffset(1.25);
  GenHist->GetYaxis()->SetTitleFont(42);

  //EstHist->GetXaxis()->SetLabelFont(42);
  //EstHist->GetXaxis()->SetLabelOffset(0.007);
  //EstHist->GetXaxis()->SetLabelSize(0.04);
  EstHist->GetXaxis()->SetTitleSize(0.05);
  EstHist->GetXaxis()->SetTitleOffset(0.9);
  EstHist->GetXaxis()->SetTitleFont(42);
  //EstHist->GetYaxis()->SetLabelFont(42);
  //EstHist->GetYaxis()->SetLabelOffset(0.007);
  //EstHist->GetYaxis()->SetLabelSize(0.04);
  EstHist->GetYaxis()->SetTitleSize(0.05);
  EstHist->GetYaxis()->SetTitleOffset(1.25);
  EstHist->GetYaxis()->SetTitleFont(42);
  sprintf(xtitlename,"search bins");
  sprintf(ytitlename,"Events");
  gPad->SetLogy();
  GenHist->SetMaximum(ymax_top);
  GenHist->SetMinimum(ymin_top);
  GenHist->GetXaxis()->SetRangeUser(search_x_min,search_x_max);

  //gPad->SetGridx(1);
  GenHist->SetTitle("");
  GenHist->SetMarkerStyle(20);
  GenHist->SetLineColor(1);
  GenHist->GetXaxis()->SetTitle(xtitlename);
  GenHist->GetYaxis()->SetTitle(ytitlename);
  TH1D * GenHist_Normalize = static_cast<TH1D*>(GenHist->Clone("GenHist_Normalize"));
  //KH  GenHist_Normalize->Scale(lumi/lumi_ttbar);
  GenHist_Normalize->SetMaximum(ymax_top);
  GenHist_Normalize->SetMinimum(ymin_top);
  //GenHist->Draw("e");
  //KH GenHist->Draw("same");
  GenHist_Normalize->DrawCopy("e");

  //EstHist->SetFillStyle(3004);
  EstHist->SetFillStyle(3144);
  EstHist->SetFillColor(kGreen-3);
  EstHist->SetMarkerStyle(20);
  EstHist->SetMarkerSize(0.0001);
  //EstHist->Draw("e2same");
  //EstHist->Draw("esame");
  TH1D * EstHist_Normalize = static_cast<TH1D*>(EstHist->Clone("EstHist_Normalize"));
  //  EstHist_Normalize->Scale(lumi/lumi_ttbar);
  EstHist_Normalize->DrawCopy("e2same");
  EstHist_Normalize->DrawCopy("esame");

  GenHist->Print("all");
  EstHist->Print("all");
  
  //
  // Re-draw to have "expectation" on top of "prediction"
  GenHist_Normalize->DrawCopy("esame");
  //
    // Legend & texts
    sprintf(tempname,"#tau_{hadronic} BG expectation (MC truth)");
    catLeg1->AddEntry(GenHist,tempname,"p");
    sprintf(tempname,"Prediction from MC");
    catLeg1->AddEntry(EstHist,tempname);
    catLeg1->Draw();

  //
  if(histname.find("QCD")==string::npos ){
    
    //-----------------------------------------------------------
    // Putting lines and labels explaining search region definitions
    //-----------------------------------------------------------

    // Njet separation lines
    TLine *tl_njet = new TLine();
    tl_njet->SetLineStyle(2);
    tl_njet->DrawLine(25.,ymin_top,25.,ymax_top); 
    tl_njet->DrawLine(49.,ymin_top,49.,ymax_top); 

    // Njet labels
    TLatex * ttext_njet = new TLatex();
    ttext_njet->SetTextFont(42);
    ttext_njet->SetTextSize(0.04);
    ttext_njet->SetTextAlign(22);
    ttext_njet->DrawLatex(13. , ymax_top/4. , "4 #leq N_{jets} #leq 6");
    ttext_njet->DrawLatex(37. , ymax_top/4. , "7 #leq N_{jets} #leq 8");
    ttext_njet->DrawLatex(61. , ymax_top/400. , "N_{jets} #geq 9");

    // Nb separation lines
    TLine *tl_nb = new TLine();
    tl_nb->SetLineStyle(3);
    tl_nb->DrawLine( 7.,ymin_top, 7.,ymax2_top); 
    tl_nb->DrawLine(13.,ymin_top,13.,ymax2_top); 
    tl_nb->DrawLine(19.,ymin_top,19.,ymax2_top); 
    tl_nb->DrawLine(31.,ymin_top,31.,ymax3_top); 
    tl_nb->DrawLine(37.,ymin_top,37.,ymax3_top); 
    tl_nb->DrawLine(43.,ymin_top,43.,ymax3_top); 
    tl_nb->DrawLine(55.,ymin_top,55.,ymax4_top); 
    tl_nb->DrawLine(61.,ymin_top,61.,ymax4_top); 
    tl_nb->DrawLine(67.,ymin_top,67.,ymax4_top); 
    
    // Nb labels
    TLatex * ttext_nb = new TLatex();
    ttext_nb->SetTextFont(42);
    ttext_nb->SetTextSize(0.04);
    ttext_nb->SetTextAlign(22);

    ttext_nb->DrawLatex( 4. , ymax_top/20. , "N_{b} = 0");
    ttext_nb->DrawLatex(10. , ymax_top/20. , "N_{b} = 1");
    ttext_nb->DrawLatex(16. , ymax_top/20. , "N_{b} = 2");
    ttext_nb->DrawLatex(22. , ymax_top/20. , "N_{b} #geq 3");
    
    TText * ttext = new TLatex(60. , ymax_top/50. , "Normalized to 3 fb^{-1}");
    ttext->SetTextFont(42);
    ttext->SetTextSize(0.045);
    ttext->SetTextAlign(22);
    ttext->Draw();

    //
  } else {
    
    //-----------------------------------------------------------
    // Putting lines and labels explaining search region definitions
    //-----------------------------------------------------------

    // Njet separation lines
    TLine *tl_njet = new TLine();
    tl_njet->SetLineStyle(2);
    tl_njet->DrawLine( 45.,ymin_top, 45.,ymax_top); 
    tl_njet->DrawLine( 89.,ymin_top, 89.,ymax_top); 
    tl_njet->DrawLine(133.,ymin_top,133.,ymax_top); 
    tl_njet->DrawLine(177.,ymin_top,177.,ymax_top/100.); 

    // Njet labels
    TLatex * ttext_njet = new TLatex();
    ttext_njet->SetTextFont(42);
    ttext_njet->SetTextSize(0.04);
    ttext_njet->SetTextAlign(22);
    ttext_njet->DrawLatex(23. , ymax_top/4. , "N_{jets} = 4");
    ttext_njet->DrawLatex(67. , ymax_top/4. , "N_{jets} = 5");
    ttext_njet->DrawLatex(111., ymax_top/4. , "N_{jets} = 6");
    ttext_njet->DrawLatex(155., ymax_top/400. , "7 #leq N_{jets} #leq 8");
    ttext_njet->DrawLatex(199., ymax_top/400. , "N_{jets} #geq 9");

    // Nb separation lines
    TLine *tl_nb = new TLine();
    tl_nb->SetLineStyle(3);
    tl_nb->DrawLine(12.,ymin_top,12.,ymax2_top); 
    tl_nb->DrawLine(23.,ymin_top,23.,ymax2_top); 
    tl_nb->DrawLine(34.,ymin_top,34.,ymax2_top); 

    tl_nb->DrawLine(56.,ymin_top,56.,ymax2_top); 
    tl_nb->DrawLine(67.,ymin_top,67.,ymax2_top); 
    tl_nb->DrawLine(78.,ymin_top,78.,ymax2_top); 

    tl_nb->DrawLine(100.,ymin_top,100.,ymax2_top); 
    tl_nb->DrawLine(111.,ymin_top,111.,ymax2_top); 
    tl_nb->DrawLine(122.,ymin_top,122.,ymax2_top); 

    tl_nb->DrawLine(144.,ymin_top,144.,ymax3_top); 
    tl_nb->DrawLine(155.,ymin_top,155.,ymax3_top); 
    tl_nb->DrawLine(166.,ymin_top,166.,ymax3_top); 

    tl_nb->DrawLine(188.,ymin_top,188.,ymax4_top); 
    tl_nb->DrawLine(199.,ymin_top,199.,ymax4_top); 
    tl_nb->DrawLine(210.,ymin_top,210.,ymax4_top); 

    // Nb labels
    TLatex * ttext_nb = new TLatex();
    ttext_nb->SetTextFont(42);
    ttext_nb->SetTextSize(0.04);
    ttext_nb->SetTextAlign(22);
    ttext_nb->SetTextAngle(90);

    ttext_nb->DrawLatex( 6. , ymax_top/50. , "N_{b} = 0");
    ttext_nb->DrawLatex(17. , ymax_top/50. , "N_{b} = 1");
    ttext_nb->DrawLatex(28. , ymax_top/50. , "N_{b} = 2");
    ttext_nb->DrawLatex(39. , ymax_top/50. , "N_{b} #geq 3");
    
    TText * ttext = new TLatex(160. , ymax_top/50. , "Normalized to 10 fb^{-1}");
    ttext->SetTextFont(42);
    ttext->SetTextSize(0.045);
    ttext->SetTextAlign(22);
    ttext->Draw();

  }


  //
  // Bottom ratio plot
  //
  // ----------

  if(choice==0){
      //KH -- flip the numerator and denominator
      EstHistD->Divide(GenHistD);

      // draw bottom figure
      canvas_dw->cd();
      // font size
      EstHistD->GetXaxis()->SetLabelSize(font_size_dw);
      EstHistD->GetXaxis()->SetTitleSize(font_size_dw);
      EstHistD->GetYaxis()->SetLabelSize(font_size_dw);
      EstHistD->GetYaxis()->SetTitleSize(font_size_dw);
      
      //
      // Common to all bottom plots
      //
      sprintf(ytitlename,"Estimate / #tau_{had} BG");
      EstHistD->SetMaximum(2.65);
      EstHistD->SetMinimum(0.0);

      //
      // Specific to each bottom plot
      //
      sprintf(xtitlename,"search bin");
      EstHistD->GetXaxis()->SetRangeUser(search_x_min,search_x_max);
      TLine *tline = new TLine(search_x_min,1.,search_x_max,1.);

      // Setting style
      //EstHistD->SetMaximum(1.4);
      //EstHistD->GetXaxis()->SetLabelFont(42);
      //EstHistD->GetXaxis()->SetLabelOffset(0.007);
      //EstHistD->GetXaxis()->SetLabelSize(0.04);
      EstHistD->GetXaxis()->SetTitleSize(0.12);
      EstHistD->GetXaxis()->SetTitleOffset(0.9);
      EstHistD->GetXaxis()->SetTitleFont(42);
      //EstHistD->GetYaxis()->SetLabelFont(42);
      //EstHistD->GetYaxis()->SetLabelOffset(0.007);
      //EstHistD->GetYaxis()->SetLabelSize(0.04);
      EstHistD->GetYaxis()->SetTitleSize(0.13);
      EstHistD->GetYaxis()->SetTitleOffset(0.5);
      EstHistD->GetYaxis()->SetTitleFont(42);

      EstHistD->GetXaxis()->SetTitle(xtitlename);
      EstHistD->GetYaxis()->SetTitle(ytitlename);

      //gPad->SetGridx(1);
      EstHistD->SetTitle("");
      EstHistD->Draw();
      tline->SetLineStyle(2);
      tline->Draw();
  }

  if(choice==1){

    //
    // Preparing ratio histograms
      TH1D * numerator   = static_cast<TH1D*>(GenHist->Clone("numerator"));
      TH1D * numerator_fullstaterr   = static_cast<TH1D*>(GenHist->Clone("numerator_fullstaterr"));
      TH1D * denominator = static_cast<TH1D*>(EstHist->Clone("denominator"));

      TH1D * GenHist_Clone = static_cast<TH1D*>(GenHist->Clone("GenHist_Clone"));
      TH1D * EstHist_Clone = static_cast<TH1D*>(EstHist->Clone("EstHist_Clone"));
      TH1D * EstHist_NoError = static_cast<TH1D*>(EstHist->Clone("EstHist_NoError"));
      TH1D * One_NoError = static_cast<TH1D*>(EstHist->Clone("EstHist_NoError"));
      for (int ibin=0; ibin<EstHist_NoError->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
	EstHist_NoError->SetBinError(ibin,0.);
	One_NoError->SetBinContent(ibin,1.);
	One_NoError->SetBinError(ibin,0.);
      }

      //EstHistD->Add(GenHistD,-1);
      numerator->Divide(GenHist_Clone,EstHist_NoError,1,1,"");
      denominator->Divide(EstHist_Clone,EstHist_NoError,1,1,"");

      numerator_fullstaterr->Divide(GenHist_Clone,EstHist_Clone,1,1,"");  // Expectation/Prediction
      numerator_fullstaterr->Add(One_NoError,-1.);                        // Expectation/Prediction-1

      // draw bottom figure
      canvas_dw->cd();
      // font size
      numerator->GetXaxis()->SetLabelSize(font_size_dw);
      numerator->GetXaxis()->SetTitleSize(font_size_dw);
      numerator->GetYaxis()->SetLabelSize(font_size_dw);
      numerator->GetYaxis()->SetTitleSize(font_size_dw);

      //
      // Horizontal Lines
      TLine *tline  = new TLine(search_x_min,1.,search_x_max,1.);
      TLine *tline0 = new TLine(search_x_min,0.,search_x_max,0.);

      //
      // Common to all bottom plots
      //
      //sprintf(ytitlename,"#frac{Estimate - #tau_{had} BG}{#tau_{had} BG} ");
      sprintf(ytitlename,"#frac{Expectation}{Prediction} ");
      numerator->SetMaximum(ymax_bottom);
      numerator->SetMinimum(ymin_bottom);

      //
      // Specific to each bottom plot
      //
      // Setting style
      //numerator->SetMaximum(1.4);
      //numerator->GetXaxis()->SetLabelFont(42);
      //numerator->GetXaxis()->SetLabelOffset(0.007);
      //numerator->GetXaxis()->SetLabelSize(0.04);
      numerator->GetXaxis()->SetTitleSize(0.12);
      numerator->GetXaxis()->SetTitleOffset(0.9);
      numerator->GetXaxis()->SetTitleFont(42);
      //numerator->GetYaxis()->SetLabelFont(42);
      //numerator->GetYaxis()->SetLabelOffset(0.007);
      //numerator->GetYaxis()->SetLabelSize(0.04);
      numerator->GetYaxis()->SetTitleSize(0.13);
      numerator->GetYaxis()->SetTitleOffset(0.5);
      numerator->GetYaxis()->SetTitleFont(42);

      numerator->GetXaxis()->SetTitle(xtitlename);
      numerator->GetYaxis()->SetTitle(ytitlename);

      //gPad->SetGridx(1);


      if (pull==1){

	sprintf(ytitlename,"#frac{Exp - Pre}{Stat Error} ");
	numerator->SetMaximum(8.);
	numerator->SetMinimum(-8.);
	
	//
	// Specific to each bottom plot
	//
	// Setting style

	for (int ibin=0; ibin<numerator_fullstaterr->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
	  numerator_fullstaterr->SetBinContent(ibin,numerator_fullstaterr->GetBinContent(ibin)/numerator_fullstaterr->GetBinError(ibin));
	  numerator_fullstaterr->SetBinError(ibin,0.);
	}

	numerator_fullstaterr->GetXaxis()->SetLabelSize(font_size_dw);
	numerator_fullstaterr->GetXaxis()->SetTitleSize(font_size_dw);
	numerator_fullstaterr->GetYaxis()->SetLabelSize(font_size_dw);
	numerator_fullstaterr->GetYaxis()->SetTitleSize(font_size_dw);

	numerator_fullstaterr->GetXaxis()->SetTitleSize(0.12);
	numerator_fullstaterr->GetXaxis()->SetTitleOffset(0.9);
	numerator_fullstaterr->GetXaxis()->SetTitleFont(42);
	numerator_fullstaterr->GetYaxis()->SetTitleSize(0.13);
	numerator_fullstaterr->GetYaxis()->SetTitleOffset(0.5);
	numerator_fullstaterr->GetYaxis()->SetTitleFont(42);
	
	numerator_fullstaterr->GetXaxis()->SetTitle(xtitlename);
	numerator_fullstaterr->GetYaxis()->SetTitle(ytitlename);
	numerator_fullstaterr->SetFillColor(kGreen-3);
	numerator_fullstaterr->DrawCopy();

	//
	// Drawing lines
	tline0->SetLineStyle(2);
	tline0->Draw();

      }
      else {

      //
      // Plotting
      numerator->SetTitle("");
      numerator->DrawCopy();

      denominator->DrawCopy("e2same");
      denominator->DrawCopy("same");

      numerator->DrawCopy("same");

      numerator->Print("all");
      denominator->Print("all");
      numerator_fullstaterr->Print("all");

      //
      // Drawing lines
      tline->SetLineStyle(2);
      tline->Draw();

      }
      

      //
      if(histname.find("QCD")==string::npos ){
	
      // Njet separation lines
      TLine *tl_njet = new TLine();
      tl_njet->SetLineStyle(2);
      tl_njet->DrawLine( 25.,ymin_bottom, 25.,ymax_bottom); 
      tl_njet->DrawLine( 49.,ymin_bottom, 49.,ymax_bottom); 

      // Nb separation lines
      TLine *tl_nb = new TLine();
      tl_nb->SetLineStyle(3);
      tl_nb->DrawLine( 7.,ymin_bottom, 7.,ymax2_bottom); 
      tl_nb->DrawLine(13.,ymin_bottom,13.,ymax2_bottom); 
      tl_nb->DrawLine(19.,ymin_bottom,19.,ymax2_bottom); 
      
      tl_nb->DrawLine(31.,ymin_bottom,31.,ymax2_bottom); 
      tl_nb->DrawLine(37.,ymin_bottom,37.,ymax2_bottom); 
      tl_nb->DrawLine(43.,ymin_bottom,43.,ymax2_bottom); 
      
      tl_nb->DrawLine(55.,ymin_bottom,55.,ymax2_bottom); 
      tl_nb->DrawLine(61.,ymin_bottom,61.,ymax2_bottom); 
      tl_nb->DrawLine(67.,ymin_bottom,67.,ymax2_bottom); 

      } else {
	
      // Njet separation lines
      TLine *tl_njet = new TLine();
      tl_njet->SetLineStyle(2);
      tl_njet->DrawLine( 45.,ymin_bottom, 45.,ymax_bottom); 
      tl_njet->DrawLine( 89.,ymin_bottom, 89.,ymax_bottom); 
      tl_njet->DrawLine(133.,ymin_bottom,133.,ymax_bottom); 
      tl_njet->DrawLine(177.,ymin_bottom,177.,ymax_bottom); 


      // Nb separation lines
      TLine *tl_nb = new TLine();
      tl_nb->SetLineStyle(3);
      tl_nb->DrawLine(12.,ymin_bottom,12.,ymax2_bottom); 
      tl_nb->DrawLine(23.,ymin_bottom,23.,ymax2_bottom); 
      tl_nb->DrawLine(34.,ymin_bottom,34.,ymax2_bottom); 
      
      tl_nb->DrawLine(56.,ymin_bottom,56.,ymax2_bottom); 
      tl_nb->DrawLine(67.,ymin_bottom,67.,ymax2_bottom); 
      tl_nb->DrawLine(78.,ymin_bottom,78.,ymax2_bottom); 
      
      tl_nb->DrawLine(100.,ymin_bottom,100.,ymax2_bottom); 
      tl_nb->DrawLine(111.,ymin_bottom,111.,ymax2_bottom); 
      tl_nb->DrawLine(122.,ymin_bottom,122.,ymax2_bottom); 

      tl_nb->DrawLine(144.,ymin_bottom,144.,ymax2_bottom); 
      tl_nb->DrawLine(155.,ymin_bottom,155.,ymax2_bottom); 
      tl_nb->DrawLine(166.,ymin_bottom,166.,ymax2_bottom); 
      
      tl_nb->DrawLine(188.,ymin_bottom,188.,ymax2_bottom); 
      tl_nb->DrawLine(199.,ymin_bottom,199.,ymax2_bottom); 
      tl_nb->DrawLine(210.,ymin_bottom,210.,ymax2_bottom); 
    
  }

  }

  sprintf(tempname,"Closure_%s_%s_Full_%sPlot.png",histname.c_str(),sample.c_str(),elog.c_str());
  if (pull==1) 
    sprintf(tempname,"ClosurePull_%s_%s_Full_%sPlot.png",histname.c_str(),sample.c_str(),elog.c_str());
  canvas->Print(tempname);

  sprintf(tempname,"Closure_%s_%s_Full_%sPlot.pdf",histname.c_str(),sample.c_str(),elog.c_str());
  if (pull==1)
    sprintf(tempname,"ClosurePull_%s_%s_Full_%sPlot.pdf",histname.c_str(),sample.c_str(),elog.c_str());
  canvas->Print(tempname);

  }
