#ifndef LEPTON_EFFICIENCY_H
#define LEPTON_EFFICIENCY_H

#include <cmath>
#include <iostream>
#include <exception>
#include <vector>

#include "TFile.h"
#include "TH2.h"
#include "TString.h"

#include "HistReader.h"


// Access the lepton reconstruction or isolation efficiencies
// and related information. The efficiencies are determined
// in bins of HT, MHT, and N(jets).
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013
class LeptonEfficiency {
public:

  // Labels for histogram names  
  static TString nameMuonRecoEff() { return "MuonRecoEff"; }
  static TString nameMuonRecoEff(unsigned int nJetBin) { return nameMuonRecoEff()+nJetBinId(nJetBin); }
  static TString nameMuonIsoEff() { return "MuonIsoEff"; }
  static TString nameMuonIsoEff(unsigned int nJetBin) { return nameMuonIsoEff()+nJetBinId(nJetBin); }
  static TString nameElecRecoEff() { return "ElecRecoEff"; }
  static TString nameElecRecoEff(unsigned int nJetBin) { return nameElecRecoEff()+nJetBinId(nJetBin); }
  static TString nameElecIsoEff() { return "ElecIsoEff"; }
  static TString nameElecIsoEff(unsigned int nJetBin) { return nameElecIsoEff()+nJetBinId(nJetBin); }
  static TString nameEffNJetsBinning() { return "EffNJetsBinning"; }
  static TString nJetBinId(unsigned int bin);


  // Constructor. 'histNameBase' is appended by the appropriate 
  // suffix for the N(jets) bins.
  LeptonEfficiency(const TString &fileName, const TString &histNameBase);
  ~LeptonEfficiency();

  // Return the efficiency
  double operator()(double ht, double mht, unsigned int nJets) const;

  // Return the number of NJets bins
  unsigned int numNJetBins() const { return hNJetsBinning_->GetNbinsX(); }


private:
  std::vector<TH2*> effs_;
  TH1* hNJetsBinning_;
  unsigned int nJetsMin_;
  double htMin_;
  double htMax_;
  double mhtMin_;
  double mhtMax_;

  unsigned int getNJetIdx(unsigned int nJets) const;
};



LeptonEfficiency::LeptonEfficiency(const TString &fileName, const TString &histNameBase) {
  // Get the NJets binning
  hNJetsBinning_ = HistReader::get(fileName,nameEffNJetsBinning());
  nJetsMin_ = std::ceil(hNJetsBinning_->GetXaxis()->GetBinLowEdge(1));
  
  for(int i = 0; i < hNJetsBinning_->GetNbinsX(); ++i) {
    const TString histName(histNameBase+nJetBinId(i));
    TH2* h = static_cast<TH2*>(HistReader::get(fileName,histName));
    effs_.push_back(h);
    if( i == 0 ) {
      htMin_ = h->GetXaxis()->GetBinLowEdge(1);
      htMax_ = h->GetXaxis()->GetBinUpEdge(h->GetNbinsX());
      mhtMin_ = h->GetYaxis()->GetBinLowEdge(1);
      mhtMax_ = h->GetYaxis()->GetBinUpEdge(h->GetNbinsY());
    }
  }
}


LeptonEfficiency::~LeptonEfficiency() {
  for(std::vector<TH2*>::iterator it = effs_.begin();
      it != effs_.end(); ++it) {
    delete *it;
  }
}


double LeptonEfficiency::operator()(double ht, double mht, unsigned int nJets) const {
  double htTmp = ht;
  if( htTmp < htMin_ ) htTmp = htMin_ + 0.01;
  if( htTmp > htMax_ ) htTmp = htMax_ - 0.01;
  double mhtTmp = mht;
  if( mhtTmp < mhtMin_ ) mhtTmp = mhtMin_ + 0.01;
  if( mhtTmp > mhtMax_ ) mhtTmp = mhtMax_ - 0.01;
  unsigned int nJetsTmp = nJets;
  if( nJetsTmp < nJetsMin_ ) nJetsTmp = nJetsMin_;

  TH2* h = effs_.at( getNJetIdx(nJetsTmp) );

  return h->GetBinContent( h->FindBin(htTmp,mhtTmp) );
}


TString LeptonEfficiency::nJetBinId(unsigned int bin) {
  TString id("NJetsBin");
  id += bin;

  return id;
}


unsigned int LeptonEfficiency::getNJetIdx(unsigned int nJets) const {
  if( nJets < nJetsMin_ ) {
    std::cerr << "\n\nERROR trying to obtain lepton efficiency for nJets < " << nJetsMin_ << "\n\n" << std::endl;
    throw std::exception();
  }

  unsigned int bin = hNJetsBinning_->FindBin(nJets);
  if( bin > static_cast<unsigned int>(hNJetsBinning_->GetNbinsX()) ) bin--;

  return bin-1;			// histogram binning starts at 1!
}

#endif
