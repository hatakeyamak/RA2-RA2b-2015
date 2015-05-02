// Data-based prediction. In case of W+jets MC, perform closure test
//
// For this exercise, we will need in particular the following
// event variables:
// isoMuonsN,Pt,Eta,Phi()       : (array) kinematic properties of well-reconstructed,
//                                isolated muons
// jetsN,Pt,Eta,Phi()           : (array) kinematic properties of reconstructed jets
// flgW(), flgTau()             : characterise the W and possible subsequent tau decay
//
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013

#include <algorithm>
#include <cmath>
#include <iostream>

#include "TH1.h"
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"

#include "../Utils/Event.h"
#include "../Utils/HistReader.h"
#include "../Utils/LeptonAcceptance.h"
#include "../Utils/LeptonEfficiency.h"
#include "../Utils/TauResponse.h"
#include "../Utils/Sample.h"
#include "../Utils/Selection.h"
#include "../Utils/utils.h"



// === Helper Functions ================================================
bool deltaPhi(float mhtPhi, int nJets, const float* jetPt, const float* jetEta, const float* jetPhi, int tauJetMatchIdx, float tauJetPt, float tauJetEta, float tauJetPhi);



// === Main Function ===================================================
void hadTau2(unsigned int id = 11,
	     const TString &effName = "../data/LostLepton_MuonEfficienciesFromWJetMC.root",
	     const TString &respTempl = "../data/HadTau_TauResponseTemplates.root",
	     int nEvts = -1) {

  const bool isMC = ( id >= 10 );


  // --- Declare the Output Histograms ---------------------------------
  const TString title = isMC ? "Hadronic-Tau Closure Test" : "Hadronic-Tau Prediction";

  // Control plot: muon pt in the control sample
  TH1* hMuonPt = new TH1D("hMuonPt",title+";p_{T}(#mu^{gen}) [GeV];N(events)",50,0.,500.);
  hMuonPt->Sumw2();

  // Predicted distributions
  TH1* hPredHt = new TH1D("hPredHt",title+";H_{T} [GeV];N(events)",25,500.,3000.);
  hPredHt->Sumw2();
  TH1* hPredMht = new TH1D("hPredMht",title+";#slash{H}_{T} [GeV];N(events)",20,200.,1200.);   
  hPredMht->Sumw2();
  TH1* hPredNJets = new TH1D("hPredNJets",title+";N(jets);N(events)",9,3,12);   
  hPredNJets->Sumw2();

  // In case of MC: true distributions
  TH1* hTrueHt = static_cast<TH1*>(hPredHt->Clone("hTrueHt"));
  TH1* hTrueMht = static_cast<TH1*>(hPredMht->Clone("hTrueMht"));
  TH1* hTrueNJets = static_cast<TH1*>(hPredNJets->Clone("hTrueNJets"));

  // Event yields in the different RA2 search bins
  // First bin (around 0) is baseline selection
  TH1* hPredYields = new TH1D("hPredYields",title+";;N(events)",37,-0.5,36.5);
  hPredYields->Sumw2();
  hPredYields->GetXaxis()->SetBinLabel(1,"baseline");
  for(int bin = 2; bin <= hPredYields->GetNbinsX(); ++bin) {
    TString label = "Bin ";
    label += bin-1;
    hPredYields->GetXaxis()->SetBinLabel(bin,label);
  }
  TH1* hTrueYields = static_cast<TH1*>(hPredYields->Clone("hTrueYields"));



  // --- Tau Templates and Muon Efficiencies ---------------------------

  // Interface to the tau response templates
  TauResponse tauResp(respTempl);

  // Interfaces to the muon acceptance as well as reconstruction and 
  // isolation efficiencies
  LeptonAcceptance muonAcc(effName,LeptonAcceptance::nameMuonAcc());
  LeptonEfficiency muonRecoEff(effName,LeptonEfficiency::nameMuonRecoEff());
  LeptonEfficiency muonIsoEff(effName,LeptonEfficiency::nameMuonIsoEff());



  // --- Analyse the events --------------------------------------------

  // Interface to the event content
  Event* evt = new Event(Sample::fileNameFullSample(id),nEvts);

  // Loop over the events (tree entries)
  while( evt->loadNext() ) {

    // Select the control sample: 
    // - select events with exactly one well-reconstructed, isolated muon
    // Use the muon to predict the energy deposits of the 
    // hadronically decaying tau:
    // - scale the muon pt by a random factor drawn from the
    //   tau-reponse template to simulate the tau measurement
    // - use the simulated tau-pt to predict HT, MHT, and N(jets)
    if( evt->isoMuonsN() == 1 && evt->isoElectronsN() == 0 ) {

      // The kinematic properties of the well-reconstructed, isolated muon
      const float muPt = evt->isoMuonsPt()[0];
      const float muEta = evt->isoMuonsEta()[0];
      const float muPhi = evt->isoMuonsPhi()[0];
      
      // Use only events where the muon is inside acceptance
      if( muPt < TauResponse::ptMin() ) continue;
      if( std::abs( muEta ) > TauResponse::etaMax() ) continue;

      // "Cross cleaning": find the jet that corresponds to
      // the muon. Associate the jet that is closest in
      // in eta-phi space to the lepton
      int muJetIdx = -1;
      const float deltaRMax = 0.2;
      if( !utils::findMatchedObject(muJetIdx,muEta,muPhi,evt->jetsEta(),evt->jetsPhi(),evt->jetsN(),deltaRMax) ) continue;

      // Calculate RA2 selection-variables from "cleaned" jets
      int selNJet = 0;
      float selHt   = 0.;
      float selMhtX = 0.;
      float selMhtY = 0.;
      for(int jetIdx = 0; jetIdx < evt->jetsN(); ++jetIdx) {	// Loop over reco jets
	// Skip this jet if it is the muon
	if( jetIdx == muJetIdx ) continue;
	
	// Calculate NJet and HT
	if( evt->jetsPt()[jetIdx] > Selection::htJetPtMin() && std::abs(evt->jetsEta()[jetIdx]) < Selection::htJetEtaMax() ) {
	  selNJet++;
	  selHt += evt->jetsPt()[jetIdx];
	}
	// Calculate MHT
	if( evt->jetsPt()[jetIdx] > Selection::mhtJetPtMin() && std::abs(evt->jetsEta()[jetIdx]) < Selection::mhtJetEtaMax() ) {
	  selMhtX -= evt->jetsPt()[jetIdx]*cos(evt->jetsPhi()[jetIdx]);
	  selMhtY -= evt->jetsPt()[jetIdx]*sin(evt->jetsPhi()[jetIdx]);
	}
      } // End of loop over reco jets
      
      // Select only events with at least 2 HT jets
      if( selNJet < 2 ) continue;

      // Plot the muon pt as control plot
      hMuonPt->Fill(muPt);
      
      // Get random number from tau-response template
      // The template is chosen according to the muon pt
      const float scale = tauResp.getRandom(muPt);
      // Scale muon pt with tau response --> simulate tau jet pt
      const float simTauJetPt = scale * muPt;
      const float simTauJetEta = muEta;
      const float simTauJetPhi = muPhi;

      // Taking into account the simulated tau jet, recompute
      // HT, MHT, and N(jets)
      int simNJet = selNJet;
      float simHt = selHt;
      float simMhtX = selMhtX;
      float simMhtY = selMhtY;
      
      // If simulted tau-jet meets same criteria as as HT jets,
      // recompute NJets and HT
      if( simTauJetPt > Selection::htJetPtMin() && std::abs(muEta) < Selection::htJetEtaMax() ) {
	simNJet++;
	simHt += simTauJetPt;
      }
      // If simulated tau-jet meets same criteria as MHT jets,
      // recompute MHT
      if( simTauJetPt > Selection::mhtJetPtMin() && std::abs(muEta) < Selection::mhtJetEtaMax() ) {
	simMhtX -= simTauJetPt*cos(muPhi);
	simMhtY -= simTauJetPt*sin(muPhi);
      }

      const float simMht = sqrt( simMhtX*simMhtX + simMhtY*simMhtY );
      const float simMhtPhi = std::atan2(simMhtY,simMhtX);

      // Apply baseline selection
      if( !Selection::nJets(simNJet) ) continue;
      if( !Selection::ht(simHt) ) continue;
      if( !Selection::mht(simMht) ) continue;
      if( !deltaPhi(simMhtPhi,evt->jetsN(),evt->jetsPt(),evt->jetsEta(),evt->jetsPhi(),muJetIdx,simTauJetPt,simTauJetEta,simTauJetPhi) ) continue;

      // Corrections to control sample
      const double corrBRWToTauHad = 0.65;  // Correction for the BR of hadronic tau decays
      const double corrBRTauToMu = 1./1.15; // Correction for the fact that some muons could come from leptonic decays of taus from W decays
      const double acc = muonAcc(evt->mht(),evt->nJets());
      const double recoEff = muonRecoEff(evt->ht(),evt->mht(),evt->nJets());
      const double isoEff = muonIsoEff(evt->ht(),evt->mht(),evt->nJets());
      if( !( acc > 0. && recoEff > 0. && isoEff > 0. ) ) continue;
      const double corrMuAcc = 1./acc; // Correction for muon acceptance
      const double corrMuRecoEff = 1./recoEff; // Correction for muon reconstruction efficiency
      const double corrMuIsoEff = 1./isoEff; // Correction for muon isolation efficiency

      // The overall correction factor
      const double corr = corrBRTauToMu * corrBRWToTauHad * corrMuAcc * corrMuRecoEff * corrMuIsoEff;

      // Fill the prediction
      hPredHt->Fill(simHt,corr);
      hPredMht->Fill(simMht,corr);
      hPredNJets->Fill(simNJet,corr);

      // Predicted event yields
      hPredYields->Fill(0.,corr);
      const unsigned int searchBin = Selection::searchBin(simHt,simMht,simNJet);
      if( searchBin > 0 ) {
	hPredYields->Fill(searchBin,corr);
      }

    } // End if exactly one muon


    if( isMC ) {
      // Fill the 'truth' for comparison with the prediction
      // Select only events where the W decayed into a hadronically
      // decaying tau
      if( !( evt->flgW() == 15 && evt->flgTau() == 1 ) ) continue;
      
      // Apply baseline selection
      if( !Selection::nJets(evt->nJets()) ) continue;
      if( !Selection::ht(evt->ht()) ) continue;
      if( !Selection::mht(evt->mht()) ) continue;
      if( !Selection::deltaPhi(evt->deltaPhi1(),evt->deltaPhi2(),evt->deltaPhi3()) ) continue;

      hTrueHt->Fill(evt->ht());
      hTrueMht->Fill(evt->mht());
      hTrueNJets->Fill(evt->nJets());

      // True event yields
      hTrueYields->Fill(0.);
      const unsigned int searchBin = Selection::searchBin(evt->ht(),evt->mht(),evt->nJets());
      if( searchBin > 0 ) {
	hTrueYields->Fill(searchBin);
      }

    } // End isMC

  } // End of loop over events
  

  // --- Save the Histograms to File -----------------------------------
  const TString outFileName = isMC ? "HadTau_WJetMC_Closure.root" : "HadTau_Data_Prediction.root";
  TFile outFile(outFileName,"RECREATE");
  hMuonPt->Write();
  hTrueHt->Write();
  hTrueMht->Write();
  hTrueNJets->Write();
  hTrueYields->Write();
  hPredHt->Write();
  hPredMht->Write();
  hPredNJets->Write();
  hPredYields->Write();
  outFile.Close();
}





// Returns result of delta-phi selection taking into account the reconstructed
// jets and the tau jet. The pt ordering of the jets and the tau jet is checked
// explicitly.
bool deltaPhi(float mhtPhi, int nJets, const float* jetPt, const float* jetEta, const float* jetPhi, int tauJetMatchIdx, float tauJetPt, float tauJetEta, float tauJetPhi) {
  // Find leading three MHT jets, i.e. with pt > 30 GeV,
  // that are not matched to the tau jet
  int nMhtJets = 0;
  float mhtJetPt[3] = { 0., 0., 0. };
  float mhtJetPhi[3] = { 0., 0., 0. };
  for(int jetIdx = 0; jetIdx < nJets; ++jetIdx) {
    // Skip this jet if it is the tau
    if( jetIdx == tauJetMatchIdx ) continue;
    
    if( jetPt[jetIdx] > Selection::mhtJetPtMin() && std::abs(jetEta[jetIdx]) < Selection::mhtJetEtaMax() ) {
      nMhtJets++;
      if( nMhtJets == 1 ) {
	mhtJetPt[0] = jetPt[jetIdx];
	mhtJetPhi[0] = jetPhi[jetIdx];
      } else if( nMhtJets == 2 ) {
	mhtJetPt[1] = jetPt[jetIdx];
	mhtJetPhi[1] = jetPhi[jetIdx];
      } else if( nMhtJets == 3 ) {
	mhtJetPt[2] = jetPt[jetIdx];
	mhtJetPhi[2] = jetPhi[jetIdx];
	break;
      }
    }
  }

  if( nMhtJets < 2 ) {		// One or no MHT jet
    return false;
  }

  // Check if tau jet counts as MHT jet
  // and in that case reorder the jets
  if( tauJetPt > Selection::mhtJetPtMin() && std::abs(tauJetEta) < Selection::mhtJetEtaMax() ) {
    if( nMhtJets == 2 ) {	// Two MHT jets
      if( tauJetPt > mhtJetPt[0] ) {
	mhtJetPhi[2] = mhtJetPhi[1];
	mhtJetPhi[1] = mhtJetPhi[0];
	mhtJetPhi[0] = tauJetPhi;
      } else if( tauJetPt > mhtJetPt[1] ) {
	mhtJetPhi[2] = mhtJetPhi[1];
	mhtJetPhi[1] = tauJetPhi;
      } else {
	mhtJetPhi[2] = tauJetPhi;
      }
      nMhtJets++;
    } else {			// Three or more MHT jets
      if( tauJetPt > mhtJetPt[0] ) {
	mhtJetPhi[2] = mhtJetPhi[1];
	mhtJetPhi[1] = mhtJetPhi[0];
	mhtJetPhi[0] = tauJetPhi;
      } else if( tauJetPt > mhtJetPt[1] ) {
	mhtJetPhi[2] = mhtJetPhi[1];
	mhtJetPhi[1] = tauJetPhi;
      } else if( tauJetPt > mhtJetPt[2] ) {
	mhtJetPhi[2] = tauJetPhi;
      }
    }
  }

  float dphi[3];
  for(int i = 0; i < nMhtJets; ++i) {
    dphi[i] = std::abs(utils::deltaPhi(mhtJetPhi[i],mhtPhi));    
  }

  // Apply DeltaPhi cuts
  return Selection::deltaPhi(dphi[0],dphi[1],dphi[2]);
}
