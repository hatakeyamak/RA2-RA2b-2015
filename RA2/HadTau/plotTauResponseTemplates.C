// Plot the tau-reponse templates
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013
void plotTauResponseTemplates(const TString &fileName = "../data/HadTau_TauResponseTemplates.root",
			      const TString &graphicsFormat = "png") {
  gROOT->ProcessLine(".L ../Utils/StyleMatters.h++");
  gROOT->ProcessLine(".L ../Utils/HistReader.h++");
  gROOT->ProcessLine(".L ../Utils/TauResponse.h++");
  StyleMatters::init();
  const int canSize = 500;

  
  // Get histograms from file
  TH1* hResp[TauResponse::nBins()];
  for(unsigned int i = 0; i < TauResponse::nBins(); ++i) {
    hResp[i] = HistReader::get(fileName,TauResponse::name(i));
  }
  
  // Set style
  for(unsigned int i = 0; i < TauResponse::nBins(); ++i) {
    hResp[i]->SetLineWidth(2);
    hResp[i]->SetLineColor(1+i);
    hResp[i]->GetYaxis()->SetRangeUser(0.,2.05);
  }

  // Create legend
  TLegend* leg = new TLegend(0.63,0.55,0.9,0.89);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->SetHeader("p_{T}(#tau^{gen}) [GeV]");
  for(unsigned int i = 0; i < TauResponse::nBins(); ++i) {
    TString entry("");
    if( i < TauResponse::nBins()-1 ) {
      entry += TauResponse::ptMin(i);
      entry += " - ";
      entry += TauResponse::ptMax(i);
    } else {
      entry += "> ";
      entry += TauResponse::ptMin(i);
    }
    leg->AddEntry(hResp[i],entry,"L");
  }

  // Draw
  TCanvas* can = new TCanvas("can","Response",canSize,canSize);
  can->cd();
  hResp[0]->Draw("HIST");
  for(unsigned int i = 1; i < TauResponse::nBins(); ++i) {
    hResp[i]->Draw("HISTsame");
  }
  leg->Draw("same");
  can->SaveAs("TauResponseTemplates."+graphicsFormat);
}
