#include <cmath>
#include <iostream>
#include <vector>

#include "TH1.h"
#include "TH1D.h"
#include "TString.h"
#include "TVector2.h"

#include "../Utils/Event.h"
#include "../Utils/Sample.h"


// Investigation of SM background and signal event properties.
// Learning how to access the data
//
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013

// === Main Function ===================================================
void general1(unsigned int id, int nEvts = -1) {
  std::cout << "Analysing the '" << Sample::toTString(id) << "' sample" << std::endl;


  // --- Declare the Output Histograms ---------------------------------
  TH1* hNJets = new TH1D("hNJets",";N(jets);N(events)",12,0,12);
  hNJets->Sumw2();
  TH1* hHt = new TH1D("hHt",";H_{T} [GeV]",30,0,3000);
  hHt->Sumw2();
  hHt->GetXaxis()->SetNdivisions(505);
  TH1* hMht = new TH1D("hMht",";#slash{H}_{T} [GeV]",24,0,1200);
  hMht->Sumw2();
  hMht->GetXaxis()->SetNdivisions(505);
  std::vector<TH1*> hJetPt(3,NULL);
  std::vector<TH1*> hJetPhi(3,NULL);
  std::vector<TH1*> hJetEta(3,NULL);
  std::vector<TH1*> hDeltaPhi(3,NULL);
  for(unsigned int i = 0; i < hJetPt.size(); ++i) {
    TString name = "hJetPt_";
    name += i;
    TString title = ";p_{T}(jet ";
    title += i+1;
    title += ") [GeV];N(events)";
    hJetPt.at(i) = new TH1D(name,title,30,0,1500);
    hJetPt.at(i)->Sumw2();

    name = "hJetPhi_";
    name += i;
    title = ";#phi(jet ";
    title += i+1;
    title += ");N(events)";
    hJetPhi.at(i) = new TH1D(name,title,24,-4,4);
    hJetPhi.at(i)->Sumw2();

    name = "hJetEta_";
    name += i;
    title = ";#eta(jet ";
    title += i+1;
    title += ");N(events)";
    hJetEta.at(i) = new TH1D(name,title,25,-5,5);
    hJetEta.at(i)->Sumw2();

    name = "hDeltaPhi_";
    name += i;
    title = ";#Delta#phi(#slash{#vec{H}}_{T},jet ";
    title += i+1;
    title += ");N(events)";
    hDeltaPhi.at(i) = new TH1D(name,title,24,0,3.2);
    hDeltaPhi.at(i)->Sumw2();
  }



  // --- Analyse the events --------------------------------------------
  // The Event class is an interface to the TTree objects in the
  // input ROOT files. 
  // Here, we use the following event variables:
  //  - isoElectronsN() : Number of well-reconstructed, isolated electrons
  //  - isoMuonsN()     : Number of well-reconstructed, isolated muons
  //  - jetsN()         : Number of well-reconstructed jets
  //  - jetsPt()        : Array of size jetsN() lsstoring the jets pt; likewise for eta and phi
  Event* evt = new Event(Sample::fileNameFullSample(id),nEvts);
  
  // Loop over the events
  while( evt->loadNext() ) {

    // Apply the lepton veto
    if( evt->isoElectronsN() != 0 ) continue;
    if( evt->isoMuonsN() != 0 ) continue;


    // Calculate the jet-based RA2 selection variables
    float selNJet = 0;          // Number of jets with pt > 50 GeV and |eta| < 2.5 (`HT jets')
    float selHt   = 0.;		// HT, computed from jets with pt > 50 GeV and |eta| < 2.5 (`HT jets')
    float selMhtX = 0.;		// X-component of MHT,  computed from jets with pt > 30 GeV (`MHT jets')
    float selMhtY = 0.;		// Y-component of MHT,  computed from jets with pt > 30 GeV (`MHT jets')
    // Loop over reco jets in this event: they are ordered in pt
    for(int jetIdx = 0; jetIdx < evt->jetsN(); ++jetIdx) {
      // Calculate NJet and HT
      if( evt->jetsPt()[jetIdx] > 50. && std::abs(evt->jetsEta()[jetIdx]) < 2.5 ) {
	// This is an HT jet
	selNJet++;
	selHt += evt->jetsPt()[jetIdx];
      }
      // Calculate MHT components
      if( evt->jetsPt()[jetIdx] > 30 && std::abs(evt->jetsEta()[jetIdx]) < 5.0 ) {
	// This is an MHT jet
	selMhtX -= evt->jetsPt()[jetIdx]*std::cos(evt->jetsPhi()[jetIdx]);
	selMhtY -= evt->jetsPt()[jetIdx]*std::sin(evt->jetsPhi()[jetIdx]);
      }
    } // End of loop over reco jets
    // Compute MHT from components
    const float selMht = sqrt( selMhtX*selMhtX + selMhtY*selMhtY );

    // Delta phi between the MHT vector and the jet for the leading MHT jets
    std::vector<double> deltaPhis(3,9999.);
    const float phiMht = std::atan2(selMhtY,selMhtX);
    // Loop over reco jets: remember, they are ordered in pt!
    unsigned int nMhtJets = 0;
    for(int jetIdx = 0; jetIdx < evt->jetsN(); ++jetIdx) {
      
      // Select MHT jets
      if( evt->jetsPt()[jetIdx] > 30 && std::abs(evt->jetsEta()[jetIdx]) < 5.0 ) {
	
	// Compute delta phi (per convention in sector between -Pi and Pi)
	// between this jet and the MHT vector
	const float deltaPhi = TVector2::Phi_mpi_pi(evt->jetsPhi()[jetIdx]-phiMht); 
	// Store deltaPhi
	deltaPhis.at(nMhtJets) = std::abs( deltaPhi );
	
	// Increase counter for MHT jets
	++nMhtJets;
	// DeltaPhi cut only for first three jets
	// Leave jet loop if the first 3 MHT jets tested
	if( nMhtJets == 3 ) break;
	
      }	// End of MHT-jet criterion

    } // End of loop over reco jets

    // Fill histograms
    hNJets->Fill(selNJet);
    hHt->Fill(selHt);
    hMht->Fill(selMht);
    for(unsigned int i = 0; i < hJetPt.size(); ++i) {
      if( i == evt->jetsN() ) break;
      hJetPt.at(i)->Fill(evt->jetsPt()[i]);
      hJetPhi.at(i)->Fill(evt->jetsPhi()[i]);
      hJetEta.at(i)->Fill(evt->jetsEta()[i]);
      hDeltaPhi.at(i)->Fill(deltaPhis.at(i));
    }
  } // End of loop over events



  // --- Save the Histograms to File -----------------------------------
  TFile outFile("General_"+Sample::toTString(id)+".root","RECREATE");
  hNJets->Write();
  hHt->Write();
  hMht->Write();
  for(unsigned int i = 0; i < hJetPt.size(); ++i) {
    hJetPt.at(i)->Write();
    hJetEta.at(i)->Write();
    hJetPhi.at(i)->Write();
    hDeltaPhi.at(i)->Write();
  }  
  outFile.Close();
}
