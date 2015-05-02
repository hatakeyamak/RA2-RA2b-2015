// Determine the tau response templates in simulated W+jet events
//
// For this exercise, we will need in particular the following
// event variables:
// flgW(), flgTau()             : characterise the W and possible subsequent tau decay
// genLeptonPt,Eta,Phi()        : kinematic properties of generator-level lepton from 
//                                W decay
// jetsN,Pt,Eta,Phi()           : (array) kinematic properties of reconstructed jets
//
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "TH1.h"
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include "TVector2.h"

#include "../Utils/Event.h"
#include "../Utils/TauResponse.h"
#include "../Utils/Sample.h"
#include "../Utils/Selection.h"
#include "../Utils/utils.h"




// === Main Function ===================================================
void hadTau1(unsigned int id = 11, int nEvts = -1) {

  // --- Declare the Output Histograms ---------------------------------

  // The tau response templates
  // They are filled for different bins in generated tau-lepton pt.
  // The binning is encapsulated in ../Utils/TauResponse.h
  std::vector<TH1*> hTauResp(TauResponse::nBins());
  for(unsigned int i = 0; i < TauResponse::nBins(); ++i) {
    hTauResp.at(i) = new TH1D(TauResponse::name(i),";p_{T}(visible) / p_{T}(generated);Probability",50,0.,2.5);
    hTauResp.at(i)->Sumw2();
  }

  // Control histograms for the jet-tau matching efficiency
  TH1* hNJetAll = new TH1D("hNJetAll",";N(jets)",10,0,10);
  hNJetAll->Sumw2();
  TH1* hNJetPass = static_cast<TH1*>(hNJetAll->Clone("hNJetPass"));

  TH1* hHtAll = new TH1D("hHtAll",";H_{T} [GeV]",30,0,3000);
  hHtAll->Sumw2();
  TH1* hHtPass = static_cast<TH1*>(hHtAll->Clone("hHtPass"));

  TH1* hMhtAll = new TH1D("hMhtAll",";#slash{H}_{T} [GeV]",20,0,2000);
  hMhtAll->Sumw2();
  TH1* hMhtPass = static_cast<TH1*>(hMhtAll->Clone("hMhtPass"));



  // --- Analyse the events --------------------------------------------

  // Interface to the event content
  Event* evt = new Event(Sample::fileNameFullSample(id),nEvts);

  // Loop over the events (tree entries)
  while( evt->loadNext() ) {

    // Select only events where the W decayed into a hadronically
    // decaying tau
    if( !(evt->flgW() == 15 && evt->flgTau() == 1) ) continue;

    // Kinematic variables of generator-level tau
    const float genTauPt = evt->genLeptonPt();
    const float genTauEta = evt->genLeptonEta();
    const float genTauPhi = evt->genLeptonPhi();

    // Use only events where the tau is inside the muon acceptance
    // because lateron we will apply the response to muon+jet events
    if( genTauPt < TauResponse::ptMin() ) continue;
    if( std::abs(genTauEta) > TauResponse::etaMax() ) continue;


    // "Cross cleaning": find the jet that originates in the
    // hadronic tau-decay. Associate the jet that is closest in
    // deltaR to the tau. The distance has to be smaller than deltaRMax.

    // First, fill counters before jet-tau matching
    hNJetAll->Fill(evt->nJets());
    hHtAll->Fill(evt->ht());
    hMhtAll->Fill(evt->mht());

    // Do the matching
    int tauJetIdx = -1;		// Will store the index of the jet matched to the tau
    const float deltaRMax = genTauPt < 50. ? 0.2 : 0.1; // Increase deltaRMax at low pt to maintain high-enought matching efficiency
    if( !utils::findMatchedObject(tauJetIdx,genTauEta,genTauPhi,evt->jetsEta(),evt->jetsPhi(),evt->jetsN(),deltaRMax) ) continue;

    // Then, fill counters after matching
    hNJetPass->Fill(evt->nJets());
    hHtPass->Fill(evt->ht());
    hMhtPass->Fill(evt->mht());


    // Calculate RA2 selection-variables from "cleaned" jets,
    // i.e. jets withouth the tau-jet
    int selNJet = 0; // Number of HT jets (jets pt > 50 GeV and |eta| < 2.5)

    for(int jetIdx = 0; jetIdx < evt->jetsN(); ++jetIdx) {	// Loop over reco jets
      // Skip this jet if it is the tau
      if( jetIdx == tauJetIdx ) continue;

      // Calculate NJet 
      if( evt->jetsPt()[jetIdx] > Selection::htJetPtMin() && std::abs(evt->jetsEta()[jetIdx]) < Selection::htJetEtaMax() ) selNJet++;
    } // End of loop over reco jets
    
    
    // Select only events with at least 2 HT jets
    if( selNJet < 2 ) continue;
    

    // Fill histogram with relative visible energy of the tau
    // ("tau response template") for hadronically decaying taus
    for(int jetIdx = 0; jetIdx < evt->jetsN(); ++jetIdx) {	// Loop over reco jets
      // Select tau jet
      if( jetIdx == tauJetIdx ) {
	// Get the response pt bin for the tau
	const unsigned int ptBin = TauResponse::ptBin(genTauPt);
	// Fill the corresponding response template
	const double tauJetPt = evt->jetsPt()[jetIdx];
	hTauResp.at(ptBin)->Fill( tauJetPt / genTauPt );
	break;		// End the jet loop once the tau jet has been found
      }
    }	// End of loop over reco jets
  } // End of loop over tree entries


  // Normalize the response distributions to get the probability density
  for(unsigned int i = 0; i < hTauResp.size(); ++i) {
    if( hTauResp.at(i)->Integral("width") > 0. ) {
      hTauResp.at(i)->Scale(1./hTauResp.at(i)->Integral("width"));
    }
  }

  // Get the jet-tau matching efficiency
  TH1* hMatchEffNJet = static_cast<TH1*>(hNJetPass->Clone("hMatchEffNJet"));
  hMatchEffNJet->Divide(hNJetAll);
  TH1* hMatchEffHt = static_cast<TH1*>(hHtPass->Clone("hMatchEffHt"));
  hMatchEffHt->Divide(hHtAll);
  TH1* hMatchEffMht = static_cast<TH1*>(hMhtPass->Clone("hMatchEffMht"));
  hMatchEffMht->Divide(hMhtAll);


  // --- Save the Histograms to File -----------------------------------
  TFile outFile("../data/HadTau_TauResponseTemplates.root","RECREATE");
  for(unsigned int i = 0; i < hTauResp.size(); ++i) {
    hTauResp.at(i)->Write();
  }
  hMatchEffNJet->Write();
  hMatchEffHt->Write();
  hMatchEffMht->Write();
  outFile.Close();
}
