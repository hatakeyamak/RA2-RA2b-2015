// Plot the hadronic-tau prediction and print the event yields
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013
void plotPrediction(const TString &fileName = "HadTau_Data_Prediction.root",
		    const TString &graphicsFormat = "png") {
  gROOT->ProcessLine(".L ../Utils/StyleMatters.h++");
  gROOT->ProcessLine(".L ../Utils/HistReader.h++");
  StyleMatters::init();
  const int canSize = 500;
  
  // Get histograms from file
  const unsigned int kNDists = 3;
  TH1* hPred[kNDists];
  for(unsigned int i = 0; i < kNDists; ++i) {
    TString name = "";
    if(      i == 0 ) name = "Ht";
    else if( i == 1 ) name = "Mht";
    else if( i == 2 ) name = "NJets";
    hPred[i] = HistReader::get(fileName,"hPred"+name);
  }
  TH1* hMuonPt = HistReader::get(fileName,"hMuonPt");
  

  // Set style
  for(unsigned int i = 0; i < kNDists; ++i) {
    hPred[i]->SetMarkerStyle(20);
    hPred[i]->SetMarkerColor(kRed);
    hPred[i]->SetLineColor(hPred[i]->GetMarkerColor());
  }
  hMuonPt->SetMarkerStyle(20);
  hMuonPt->SetMarkerColor(kBlack);
  hMuonPt->SetLineColor(hMuonPt->GetMarkerColor());


  // Draw
  for(unsigned int i = 0; i < kNDists; ++i) {
    TString name = "";
    if(      i == 0 ) name = "HT";
    else if( i == 1 ) name = "MHT";
    else if( i == 2 ) name = "NJets";

    TCanvas* can = new TCanvas(name,name,canSize,canSize);
    can->cd();
    hPred[i]->Draw("PE1");
    name = "hPred"+name;
    gPad->SetLogy();
    can->SaveAs(name+"."+graphicsFormat);
  }

  TCanvas* can = new TCanvas("can","muon pt",canSize,canSize);
  can->cd();
  hMuonPt->Draw("PE1");
  gPad->SetLogy();
  can->SaveAs("hMuonPt."+graphicsFormat);


  // Print event yields
  std::cout << "Number of control-sample events:" << hMuonPt->Integral(1,100000) << std::endl;;

  TH1* hYieldsPred = HistReader::get(fileName,"hPredYields");
  std::cout << "Event yields" << std::endl;
  std::cout << "Selection : \tPredicted Yields\t\t" << std::endl;
  for(int bin = 1; bin <= hYieldsPred->GetNbinsX(); ++bin) {
    std::cout << hYieldsPred->GetXaxis()->GetBinLabel(bin) << " : \t" << std::flush;
    std::cout << hYieldsPred->GetBinContent(bin) << " +/- " << hYieldsPred->GetBinError(bin) << "  \t" << std::flush;
    std::cout << std::endl;
  }
}

