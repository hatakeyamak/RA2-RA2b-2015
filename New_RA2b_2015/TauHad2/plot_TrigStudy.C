#include <map>

void plot_TrigStudy(string histName="MHT"){

  //
  // icomp=0: only show own results
  //       1: show also Koushik's results
  //
  
  //
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////Some cosmetic work for official documents. 
  gStyle->SetOptStat(0);  ///to avoid the stat. on the plots 
//  gROOT->LoadMacro("tdrstyle.C");
//  setTDRStyle();
//  gROOT->LoadMacro("CMS_lumi_v2.C");

  char tempname[200];
  char tempname2[200];
  int W = 800;
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
  
  Float_t legendX1 = .15; //.50;
  Float_t legendX2 = .50; //.70;
  Float_t legendY1 = .6; //.65;
  Float_t legendY2 = .9;
  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.042);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  TH1D * temp_tt, * temp_wj;
  
/*
  // From W+jets - predictions
  TFile file_WJet_mu("Stack/TriggerEff_WJet_stacked.root","R");  
  temp_wj_muH = (TH1D*)file_WJet_mu.Get("TrigEff")->Clone();
  TH1D * wj_muH = new TH1D("wj_muH","WJet -- Tau mistag",temp_wj_muH->GetNbinsX(),temp_wj_muH->GetXaxis()->GetXmin(),temp_wj_muH->GetXaxis()->GetXmax());
  for(int ibin=0;ibin<wj_muH->GetNbinsX()+2;ibin++){
    double con = (double)temp_wj_muH->GetBinContent(ibin);
    double err = (double)temp_wj_muH->GetBinError(ibin);
    cout << "con: " << con << " err: " << err << endl;
    wj_muH->SetBinContent(ibin,con);
    wj_muH->SetBinError(ibin,err);
  }
*/

  
    // From ttbar - predictions
    TFile file_TTbar_mu("TriggerStudy_TTbar_.root","R");
    map<string,vector<TH1D>> trigMap;
    vector<TH1D> trigVec;
    trigMap["NoTrig"]=trigVec;
    trigMap["HLT_PFHT350_PFMET100_NoiseCleaned_v1"]=trigVec;
    trigMap["HLT_Mu15_IsoVVVL_PFHT350_PFMET70_v1"]=trigVec;
    trigMap["HLT_Mu15_IsoVVVL_PFHT400_PFMET70_v1"]=trigVec;
    int i=0;
    for(map<string,vector<TH1D>>::iterator it=trigMap.begin(); it!=trigMap.end();it++){
      i++;
      sprintf(tempname,"%s/%s",it->first.c_str(),histName.c_str());
      temp_tt = (TH1D*)file_TTbar_mu.Get(tempname)->Clone();


      //  catLeg1->SetHeader("Prob. of #mu from #tau ");

      //...........................................................................//
      // TTbar ....................................................................//
      //...........................................................................//
      double XUp = 5000. , maxVal=2500.;
      if(histName=="MHT"){
        XUp = 1000. , maxVal=8000.;
      }
      else if(histName=="HT"){
        XUp = 5000. , maxVal=4000.;
      }
      else if(histName=="MET"){
        XUp = 1000. , maxVal=8000.;
      }


      temp_tt->GetXaxis()->SetRangeUser(0.,XUp);
      temp_tt->SetMaximum(maxVal);
      temp_tt->SetTitle("");
      
      temp_tt->GetXaxis()->SetLabelFont(42);
      temp_tt->GetXaxis()->SetLabelOffset(0.007);
      temp_tt->GetXaxis()->SetLabelSize(0.04);
      temp_tt->GetXaxis()->SetTitleSize(0.05);
      temp_tt->GetXaxis()->SetTitleOffset(1.0);
      temp_tt->GetXaxis()->SetTitleFont(42);
      temp_tt->GetYaxis()->SetLabelFont(42);
      temp_tt->GetYaxis()->SetLabelOffset(0.007);
      temp_tt->GetYaxis()->SetLabelSize(0.04);
      temp_tt->GetYaxis()->SetTitleSize(0.05);
      temp_tt->GetYaxis()->SetTitleOffset(1.0);
      temp_tt->GetYaxis()->SetTitleFont(42);
      sprintf(tempname,"%s",histName.c_str());
      temp_tt->GetXaxis()->SetTitle(tempname);
      temp_tt->GetYaxis()->SetTitle("#event");
      temp_tt->SetLineColor(i);
      temp_tt->Draw("same");

     
      // TLegend
      sprintf(tempname,"%s",it->first.c_str());
      catLeg1->AddEntry(temp_tt,tempname,"l");    

    }

    catLeg1->Draw();
    sprintf(tempname,"TrigStudy_%s.png",histName.c_str());
    c1->Print(tempname);
}
