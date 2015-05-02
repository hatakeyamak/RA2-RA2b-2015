// Plot the hadronic-tau closure test
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013
void plotClosureTest(const TString &fileName = "HadTau_WJetMC_Closure.root",
		     const TString &graphicsFormat = "png") {
  gROOT->ProcessLine(".L ../Utils/StyleMatters.h++");
  gROOT->ProcessLine(".L ../Utils/HistReader.h++");
  StyleMatters::init();
  const int canSize = 500;

  
  // Get histograms from file
  const unsigned int kNDists = 3;
  TH1* hTrue[kNDists];
  TH1* hPred[kNDists];
  for(unsigned int i = 0; i < kNDists; ++i) {
    TString name = "";
    if(      i == 0 ) name = "Ht";
    else if( i == 1 ) name = "Mht";
    else if( i == 2 ) name = "NJets";
    hPred[i] = HistReader::get(fileName,"hPred"+name);
    hTrue[i] = HistReader::get(fileName,"hTrue"+name);
  }
  TH1* hMuonPt = HistReader::get(fileName,"hMuonPt");
  
  // Set style
  for(unsigned int i = 0; i < kNDists; ++i) {
    hPred[i]->SetMarkerStyle(20);
    hPred[i]->SetMarkerColor(kRed);
    hPred[i]->SetLineColor(hPred[i]->GetMarkerColor());
    hTrue[i]->SetLineColor(kBlue);
  }
  hMuonPt->GetXaxis()->SetTitle("p_{T}(#mu) [GeV]");
  hMuonPt->SetMarkerStyle(20);
  hMuonPt->SetMarkerColor(kBlack);
  hMuonPt->SetLineColor(hMuonPt->GetMarkerColor());

  // Ratio plots
  TH1* hRatioFrame[kNDists];
  TH1* hRatio[kNDists];
  for(unsigned int i = 0; i < kNDists; ++i) {
    TString name = hTrue[i]->GetName();
    name += "Ratio";
    hRatio[i] = static_cast<TH1*>(hPred[i]->Clone(name));
    hRatio[i]->Divide(hTrue[i]);
    hRatio[i]->GetYaxis()->SetTitle("N(predicted) / N(expected)");
    hRatio[i]->GetYaxis()->SetRangeUser(0,2);

    hRatioFrame[i] = static_cast<TH1*>(hRatio[i]->Clone(name+"Frame"));
    for(int bin = 1; bin <= hRatioFrame[i]->GetNbinsX(); ++bin) {
      hRatioFrame[i]->SetBinContent(bin,1.);
    }
    hRatioFrame[i]->SetLineStyle(2);
    hRatioFrame[i]->SetLineWidth(2);
    hRatioFrame[i]->SetLineColor(hTrue[i]->GetLineColor());
  }

  // Create legend
  TLegend* leg = new TLegend(0.4,0.75,0.9,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->AddEntry(hTrue[0],"MC Expectation","L");
  leg->AddEntry(hPred[0],"Data-Based Pred.","P");


  // Draw
  for(unsigned int i = 0; i < kNDists; ++i) {
    TString name = "";
    if(      i == 0 ) name = "HT";
    else if( i == 1 ) name = "MHT";
    else if( i == 2 ) name = "NJets";

    TCanvas* can = new TCanvas(name,name,canSize,canSize);
    can->cd();
    hTrue[i]->Draw("HISTE");
    hPred[i]->Draw("PE1same");
    leg->Draw("same");
    name = "hClosure"+name;
    gPad->SetLogy();
    can->SaveAs(name+"."+graphicsFormat);

    TCanvas* canR = new TCanvas(name+"Ratio","Ratio "+name,canSize,canSize);
    canR->cd();
    hRatioFrame[i]->Draw("HIST");
    hRatio[i]->Draw("PE1same");
  }

  TCanvas* can = new TCanvas("can","muon pt",canSize,canSize);
  can->cd();
  hMuonPt->Draw("PE1");
  gPad->SetLogy();
  TString name = "MuonPt";
  name = "hClosure"+name;
  can->SaveAs(name+"."+graphicsFormat);
}

