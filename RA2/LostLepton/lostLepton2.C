// Perform closure test for muon acceptance in W+Jets MC sample
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013

#include <algorithm>
#include <cmath>
#include <iostream>

#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"
#include "TString.h"
#include "TVector2.h"

#include "../Utils/Event.h"
#include "../Utils/LeptonAcceptance.h"
#include "../Utils/Sample.h"
#include "../Utils/Selection.h"



// === Main Function ===================================================
void lostLepton2(unsigned int id = 11,
		 const TString &effName = "../data/LostLepton_MuonEfficienciesFromWJetMC.root",
		 int nEvts = -1) {

  // --- Declare the Output Histograms ---------------------------------
  const TString title = "Acceptance Closure-Test";

  TH1* hHt = new TH1D("hHt",title+";H_{T} [GeV]",25,500,3000);
  hHt->Sumw2();
  TH1* hHtPred = static_cast<TH1*>(hHt->Clone("hHtPred"));
  TH1* hMht = new TH1D("hMht",title+";#slash{H}_{T} [GeV]",20,200,1200);
  hMht->Sumw2();
  TH1* hMhtPred = static_cast<TH1*>(hMht->Clone("hMhtPred"));
  TH1* hNJets = new TH1D("hNJets",title+";N(jets)",9,3,12);
  hNJets->Sumw2();
  TH1* hNJetsPred = static_cast<TH1*>(hNJets->Clone("hNJetsPred"));

  // Event yields in the different RA2 search bins
  // First bin (around 0) is baseline selection
  TH1* hYields = new TH1D("hYields",title+";;N(events)",37,-0.5,36.5);
  hYields->Sumw2();
  hYields->GetXaxis()->SetBinLabel(1,"baseline");
  for(int bin = 2; bin <= hYields->GetNbinsX(); ++bin) {
    TString label = "Bin ";
    label += bin-1;
    hYields->GetXaxis()->SetBinLabel(bin,label);
  }
  TH1* hYieldsPred = static_cast<TH1*>(hYields->Clone("hYieldsPred"));

  // Muon in control sample
  TH1* hMuonPt = new TH1D("hMuonPt",title+";p_{T}(#mu) [GeV];N(events)",50,0,1200);
  hMuonPt->Sumw2();
  TH1* hMuonEta = new TH1D("hMuonEta",title+";#eta(#mu);N(events)",50,-5,5);
  hMuonEta->Sumw2();


  // --- Analyse the events --------------------------------------------

  // Interface to the event content
  Event* evt = new Event(Sample::fileNameFullSample(id),nEvts);

  // Interface to the muon acceptance maps
  LeptonAcceptance muonAcc(effName,LeptonAcceptance::nameMuonAcc());

  // Loop over the events (tree entries)
  while( evt->loadNext() ) {

    // Apply the NJets baseline-cut
    if( !Selection::nJets(evt->nJets()) ) continue;
    // Apply the HT and MHT baseline-cuts
    if( !Selection::ht(evt->ht()) ) continue;
    if( !Selection::mht(evt->mht()) ) continue;
    // Apply the delta-phi cuts
    if( !Selection::deltaPhi(evt->deltaPhi1(),evt->deltaPhi2(),evt->deltaPhi3()) ) continue;

    // Select only events where the W decayed either
    // - into a muon (pdgId 13)
    // - into a tau (pdgId 15) that decays into a muon
    const bool isWToMuon = evt->flgW() == 13;
    const bool isWToTauToMuon = evt->flgW() == 15 && evt->flgTau() == 13;
    if( !( isWToMuon || isWToTauToMuon ) ) continue;

    // Find the search bin (tighter than baseline selection) this event falls into
    const unsigned int searchBin = Selection::searchBin(evt->ht(),evt->mht(),evt->nJets());

    // Pick up the kinematic information from generator-level muon, i.e.
    // either the muon from W decay or the moun from tau decay
    const double genMuPt = isWToMuon ? evt->genLeptonPt() : evt->genLeptonFromTauPt();
    const double genMuEta = isWToMuon ? evt->genLeptonEta() : evt->genLeptonFromTauEta();

    if( genMuPt > LeptonAcceptance::muonPtMin() && std::abs(genMuEta) < LeptonAcceptance::muonEtaMax() ) {
      // Generator-level muon in acceptance: our control sample.
      // The event will be weighted to account for the probability that the muon
      // is out-of acceptance. In this way, we can predict the number
      // of events with muons out-of-acceptance

      // The muon acceptance depends on the MHT and N(jets) of the event
      const double muAcc = muonAcc(evt->mht(),evt->nJets());

      // The "lost-lepton weight": product of the probability for the muon
      // to be out-of acceptance (1.-muAcc) and a correction to account for the fact
      // that the control sample itself contains only events with muons
      // inside the acceptance (1./muAcc).
      const double llw = (1. - muAcc) / muAcc;

      // Predicted HT, MHT, N(jets) spectra
      hHtPred->Fill(evt->ht(),llw);
      hMhtPred->Fill(evt->mht(),llw);
      hNJetsPred->Fill(evt->nJets(),llw);

      // Predicted event yields      
      hYieldsPred->Fill(0.,llw);	// After the baseline selection
      if( searchBin > 0 ) hYieldsPred->Fill(searchBin,llw); // In the search bin

      // For the control-sample statistics
      hMuonPt->Fill(genMuPt);
      hMuonEta->Fill(genMuEta);

    } else {
      // The muon is out-of acceptance. This is the truth to which we
      // want to compare our prediction.

      // True HT, MHT, N(jets) spectra
      hHt->Fill(evt->ht());
      hMht->Fill(evt->mht());
      hNJets->Fill(evt->nJets());
      
      // True event yields      
      hYields->Fill(0.);	// After the baseline selection
      if( searchBin > 0 ) hYields->Fill(searchBin); // In the search bin
    }


  } // End of loop over events

  // --- Save the Histograms to File -----------------------------------
  TFile outFile("LostLepton_ClosureMuonAcceptance.root","RECREATE");
  hHt->Write();
  hMht->Write();
  hNJets->Write();
  hYields->Write();
  hHtPred->Write();
  hMhtPred->Write();
  hNJetsPred->Write();
  hYieldsPred->Write();
  hMuonPt->Write();
  hMuonEta->Write();
  outFile.Close();
}
