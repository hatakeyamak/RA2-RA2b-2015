// Determine the acceptance and the identification and isolation efficiencies
// of the muon in simulated W+jet events
//
// For this exercise, we will need in particular the following
// event variables:
// flgW(), flgTau()             : characterise the W and possible subsequent tau decay
// genLeptonPt,Eta,Phi()        : kinematic properties of generator-level lepton from 
//                                W decay
// genLeptonFromTauPt,Eta,Phi() : kinematic properties of generator-level tau from lepton
//                                from W decay
// muonsN,Pt,Eta,Phi()          : (array) kinematic properties of well-reconstructed muons
// isoMuonsN,Pt,Eta,Phi()       : (array) kinematic properties of well-reconstructed and
//                                isolated muons
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"
#include "TH2.h"
#include "TH2D.h"
#include "TString.h"
#include "TVector2.h"
#include "TLorentzVector.h"

#include "../Utils/Event.h"
#include "../Utils/LeptonAcceptance.h"
#include "../Utils/LeptonEfficiency.h"
#include "../Utils/Sample.h"
#include "../Utils/Selection.h"
#include "../Utils/utils.h"

#ifdef __MAKECINT__
#pragma link C++ class vector<int>;
#pragma link C++ class vector<vector<int> >;
#pragma link C++ class vector<vector<vector<int> > >;
#pragma link C++ class vector<TLorentzVector>;
#pragma link C++ class vector<vector<TLorentzVector> >;
#endif



// === Global Variables ================================================

// Muon-matching related parameters
const double deltaRMax = 0.1;
const double deltaPtMax = 0.2;


// === Helper Functions ================================================

// MHT bins for acceptance parametrisation
std::vector<double> accMHTBinEdges() {
  std::vector<double> bins;
  bins.push_back(200.);
  bins.push_back(300.);
  bins.push_back(400.);
  bins.push_back(600.);
  bins.push_back(1600.);
  
  return bins;
}

// N(jets) bins for acceptance parametrisation
std::vector<double> accNJetsBinEdges() {
  std::vector<double> bins;
  bins.push_back(2.5);
  bins.push_back(3.5);
  bins.push_back(4.5);
  bins.push_back(5.5);
  bins.push_back(6.5);
  bins.push_back(13.5);
  
  return bins;
}

  // HT bins for efficiency parametrisation
std::vector<double> effHTBinEdges() {
  std::vector<double> bins;
  bins.push_back(500);
  bins.push_back(600);
  bins.push_back(800);
  bins.push_back(1000);
  bins.push_back(1250);
  bins.push_back(2500);

  return bins;
}

// MHT bins for efficiency parametrisation
std::vector<double> effMHTBinEdges() {
  std::vector<double> bins;
  bins.push_back(200);
  bins.push_back(250);
  bins.push_back(300);
  bins.push_back(350);
  bins.push_back(450);
  bins.push_back(600);
  bins.push_back(2500);

  return bins;
}

// NJets bins for efficiency parametrisation
std::vector<double> effNJetsBinEdges() {
  std::vector<double> bins;
  bins.push_back(2.5);
  bins.push_back(3.5);
  bins.push_back(5.5);
  bins.push_back(7.5);
  bins.push_back(13.5);
  
  return bins;
}

// Find bin. Fills 'bin' with index [0, h::GetNbinsX()-1] of bin that
// contains 'val'. Returns false if 'val' smaller binning, true otherwise.
bool findBin(TH1* h, const double val, unsigned int& bin) {
  const bool insideBinning = val >= h->GetXaxis()->GetBinLowEdge(1);
  if( insideBinning ) {
    bin = h->FindBin(val)-1;
    if( static_cast<int>(bin) == h->GetNbinsX() ) bin--; // in case of val larger than binning
  }

  return insideBinning;
}




// === Main Function ===================================================
void lostLepton1(const string InRootList="../../filelist_TTJets_PU20bx25.txt" ,int verbose=0 ,int nEvts = -1) {
  // --- Declare the Output Histograms ---------------------------------
  // We want to determine efficiencies, so we always have
  // two histograms: the distribution before and after the
  // respective selection cut

  // For muon-acceptance determination. The acceptance is determined
  // in bins of MHT and N(jets)
  std::vector<double> accMhtBins   = accMHTBinEdges();
  std::vector<double> accNJetsBins = accNJetsBinEdges();
  TH2* hNJetsVsMhtAll = new TH2D("hNJetsVsMhtAll",";#slash{H}_{T} [GeV];N(jets)",
				 accMhtBins.size()-1,&(accMhtBins.front()),
				 accNJetsBins.size()-1,&(accNJetsBins.front()));
  hNJetsVsMhtAll->Sumw2();
  TH2* hNJetsVsMhtInAcc = static_cast<TH2*>(hNJetsVsMhtAll->Clone("hNJetsVsMhtInAcc"));


  // For muon reconstruction and isolation efficiencies. The efficiencies are
  // determined in bins of HT, MHT, and N(jets)
  std::vector<double> effNJetsBins = effNJetsBinEdges();
  TH1* hEffNJetsBinning = new TH1D(LeptonEfficiency::nameEffNJetsBinning(),
				   "Define the NJets binning;N(Jets)",
				   effNJetsBins.size()-1,&(effNJetsBins.front()));
  std::vector<double> effHTBins  = effHTBinEdges(); 
  std::vector<double> effMHTBins = effMHTBinEdges(); 
  std::vector<TH2*> hRecoAll;
  std::vector<TH2*> hRecoPass;
  std::vector<TH2*> hIsoAll;
  std::vector<TH2*> hIsoPass;

  for(unsigned int i = 0; i < effNJetsBins.size()-1; ++i) {
    
    hRecoAll.push_back( new TH2D( "hReco"+LeptonEfficiency::nJetBinId(i)+"All",";H_{T} [GeV];#slash{H}_{T} [GeV]",
				  effHTBins.size()-1,&(effHTBins.front()),
				  effMHTBins.size()-1,&(effMHTBins.front()) ) );
    hRecoAll.back()->Sumw2(); 
    hRecoAll.back()->GetXaxis()->SetNdivisions(505); //505=05+100*5. So we have 05 primary div and 5 secondary div. 
    hRecoPass.push_back( static_cast<TH2*>(hRecoAll.back()->Clone("hReco"+LeptonEfficiency::nJetBinId(i)+"Pass")) );

    hIsoAll.push_back( new TH2D( "hIso"+LeptonEfficiency::nJetBinId(i)+"All",";H_{T} [GeV];#slash{H}_{T} [GeV]",
				 effHTBins.size()-1,&(effHTBins.front()),
				 effMHTBins.size()-1,&(effMHTBins.front()) ) );
    hIsoAll.back()->Sumw2(); 
    hIsoAll.back()->GetXaxis()->SetNdivisions(505);
    hIsoPass.push_back( static_cast<TH2*>(hIsoAll.back()->Clone("hIso"+LeptonEfficiency::nJetBinId(i)+"Pass")) );

  }
if(verbose!=0)printf("Jets # of bins: %d \n" ,hRecoAll.size());



  // --- Analyse the events --------------------------------------------

  // Interface to the event content
  Event* evt = new Event(InRootList,nEvts);

  // Loop over the events (tree entries)
  int eventN=0;
  while( evt->loadNext() ) {
  if(verbose!=0)printf(" ########################### \n event #: %d \n",eventN);
  eventN+=1;


    // Apply the NJets baseline-cut
    if( !Selection::nJets(evt->nJets()) ) continue;
    // Apply the HT and MHT baseline-cuts
    if( !Selection::ht(evt->ht()) ) continue;
    if( !Selection::mht(evt->mht()) ) continue;
    // Apply the delta-phi cuts
    if( !Selection::deltaPhi(evt->deltaPhi1(),evt->deltaPhi2(),evt->deltaPhi3()) ) continue;

    // Select only events where the W decayed
    // - into a muon (pdgId 13)
    // - into a tau (pdgId 15) that decays into a muon
    const bool isWToMuon = evt->flgW() == 13;
    const bool isWToTauToMuon = evt->flgW() == 15 && evt->flgTau() == 13;
    if( !( isWToMuon || isWToTauToMuon ) ) continue;

    // Pick up the kinematic information from generator-level muon, i.e.
    // either the muon from W decay or the moun from tau decay
    const double genMuPt = isWToMuon ? evt->genLeptonPt() : evt->genLeptonFromTauPt();
    const double genMuEta = isWToMuon ? evt->genLeptonEta() : evt->genLeptonFromTauEta();
    const double genMuPhi = isWToMuon ? evt->genLeptonPhi() : evt->genLeptonFromTauPhi();

    // Acceptance determination 1: Counter for all events
    // with muons at generator level
    hNJetsVsMhtAll->Fill(evt->mht(),evt->nJets());

    // Check if generator-level muon is in acceptance
    if( genMuPt > LeptonAcceptance::muonPtMin()	&& std::abs(genMuEta) < LeptonAcceptance::muonEtaMax() ) {

      // Acceptance determination 2: Counter for only those events
      // with generator-level muons inside acceptance
      hNJetsVsMhtInAcc->Fill(evt->mht(),evt->nJets());

      // Reconstruction-efficiency determination 1: Counter for all events 
      // with generator-level muons inside acceptance, regardless of whether
      // the muon has also been reconstructed or not.
      unsigned int nJetIdx = 0;
      if( !findBin(hEffNJetsBinning,evt->nJets(),nJetIdx) ) {
	std::cerr << "ERROR: jet multiplicity nJets = " << evt->nJets() << " out of lepton-efficiency binning" << std::endl;
	throw std::exception();
      }
      hRecoAll.at(nJetIdx)->Fill(evt->ht(),evt->mht());
      
      // Check if the muon has been reconstructed: check if a reconstructed 
      // muon is present in the event that matches the generator-level muon
      // in R and in pt
      int matchedMuonIdx = -1;
      if( utils::findMatchedObject(matchedMuonIdx,genMuEta,genMuPhi,evt->muonsEta(),evt->muonsPhi(),evt->muonsN(),deltaRMax) ) {
	// Muon is reconstructed
	const double relDeltaPtMu = std::abs(genMuPt - evt->muonsPt()[matchedMuonIdx]) / evt->muonsPt()[matchedMuonIdx];
	if( relDeltaPtMu < deltaPtMax ) {
	  // and matches generated pt

	  // Reconstruction-efficiency determination 2: Counter for those events 
	  // with generator-level muons inside acceptance where the muon has also
	  // been reconstructed.
	  hRecoPass.at(nJetIdx)->Fill(evt->ht(),evt->mht());

	  // Isolation-efficiency determination 1: Counter for all events with a
	  // reconstructed muon that has a generator-level muon match inside the
	  // the acceptance, regardless of whether the reconstructed muon is also
	  // isolated or not.
	  hIsoAll.at(nJetIdx)->Fill(evt->ht(),evt->mht());
	  
	  // Check if the muon is also isolated: check if an isolated muon is present
	  // in the event that matches the reconstructed muon in R
	  int matchedIsoMuonIdx = -1;
	  if( utils::findMatchedObject(matchedIsoMuonIdx,evt->muonsEta()[matchedMuonIdx],evt->muonsPhi()[matchedMuonIdx],evt->isoMuonsEta(),evt->isoMuonsPhi(),evt->isoMuonsN(),deltaRMax) ) {
	    // Muon is isolated
	    
	    // Isolation-efficiency determination 2: Counter for those events where
	    // the muon is also isolated.
	    hIsoPass.at(nJetIdx)->Fill(evt->ht(),evt->mht());

	  } // End of muon is isolated

	} // End of pt matching
      }	// End of reconstructed muon

    } // End of muon in acceptance


  // print out some informations
  if(verbose!=0)printf(" mht: %g \n ",evt->mht() );

  } // End of loop over events
  std::cout << "ok" << std::endl;

  // Compute acceptance
  TH2* hAcc = static_cast<TH2*>(hNJetsVsMhtInAcc->Clone(LeptonAcceptance::nameMuonAcc()));
  hAcc->Divide(hNJetsVsMhtAll);

  // Compute efficiencies
  std::vector<TH2*> hRecoEff;
  std::vector<TH2*> hIsoEff;
  for(unsigned int i = 0; i < hRecoAll.size(); ++i) {
    TH2* h = static_cast<TH2*>(hRecoPass.at(i)->Clone(LeptonEfficiency::nameMuonRecoEff(i)));
    h->Divide(hRecoAll.at(i));
    hRecoEff.push_back(h);
    
    h = static_cast<TH2*>(hIsoPass.at(i)->Clone(LeptonEfficiency::nameMuonIsoEff(i)));
    h->Divide(hIsoAll.at(i));
    hIsoEff.push_back(h);
  }  
  

  // --- Save the Histograms to File -----------------------------------
  TFile outFile("../data/LostLepton_MuonEfficienciesFromWJetMC.root","RECREATE");
  hAcc->Write();
  for(unsigned int i = 0; i < hRecoEff.size(); ++i) {
    hRecoEff.at(i)->Write();
    hIsoEff.at(i)->Write();
  }
  hEffNJetsBinning->Write();
  for(unsigned int i = 0; i < hRecoAll.size(); ++i) {
    hRecoAll.at(i)->Write();
    hRecoPass.at(i)->Write();
    hIsoAll.at(i)->Write();
    hIsoPass.at(i)->Write();
  }
  outFile.Close();

}
