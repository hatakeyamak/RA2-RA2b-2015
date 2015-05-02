#include <cmath>
#include <iostream>
#include <vector>

#include "TH1.h"
#include "TH1D.h"
#include "TString.h"
#include "TVector2.h"

#include "../Utils/Event.h"
#include "../Utils/Sample.h"
#include "../Utils/Selection.h"


// Simulated background and data yields.
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013

// === Main Function ===================================================
void general2(unsigned int id, int nEvts = -1) {
  std::cout << "Analysing the '" << Sample::toTString(id) << "' sample" << std::endl;


  // --- Declare the Output Histograms ---------------------------------
  TH1* hNJets = new TH1D("hNJets",";N(jets);N(events)",9,3,12);
  hNJets->Sumw2();
  TH1* hHt = new TH1D("hHt",";H_{T} [GeV]",25,500,3000);
  hHt->Sumw2();
  hHt->GetXaxis()->SetNdivisions(505);
  TH1* hMht = new TH1D("hMht",";#slash{H}_{T} [GeV]",20,200,1200);
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

  // Event yields in the different RA2 search bins
  // First bin (around 0) is baseline selection
  TH1* hYields = new TH1D("hYields",";;N(events)",37,-0.5,36.5);
  hYields->Sumw2();
  hYields->GetXaxis()->SetBinLabel(1,"baseline");
  for(int bin = 2; bin <= hYields->GetNbinsX(); ++bin) {
    TString label = "Bin ";
    label += bin-1;
    hYields->GetXaxis()->SetBinLabel(bin,label);
  }


  // --- Analyse the events --------------------------------------------
  Event* evt = new Event(Sample::fileNameFullSample(id),nEvts);
  
  // Loop over the events
  while( evt->loadNext() ) {

    // Apply the lepton veto
    if( evt->isoElectronsN() != 0 ) continue;
    if( evt->isoMuonsN() != 0 ) continue;

    // Apply the NJets baseline-cut
    if( !Selection::nJets(evt->nJets()) ) continue;

    // Apply the HT and MHT baseline-cuts
    if( !Selection::ht(evt->ht()) ) continue;
    if( !Selection::mht(evt->mht()) ) continue;

    // Apply the delta-phi cuts
    if( !Selection::deltaPhi(evt->deltaPhi1(),evt->deltaPhi2(),evt->deltaPhi3()) ) continue;

    // Apply an event weight
    const float weight = evt->weight();
    
    // Fill histograms
    hNJets->Fill(evt->nJets(),weight);
    hHt->Fill(evt->ht(),weight);
    hMht->Fill(evt->mht(),weight);
    for(unsigned int i = 0; i < hJetPt.size(); ++i) {
      if( i == evt->jetsN() ) break;
      hJetPt.at(i)->Fill(evt->jetsPt()[i],weight);
      hJetPhi.at(i)->Fill(evt->jetsPhi()[i],weight);
      hJetEta.at(i)->Fill(evt->jetsEta()[i],weight);
    }
    hDeltaPhi.at(0)->Fill(evt->deltaPhi1(),weight);
    hDeltaPhi.at(1)->Fill(evt->deltaPhi2(),weight);
    hDeltaPhi.at(2)->Fill(evt->deltaPhi3(),weight);

    hYields->Fill(0.,weight);	// This is after the baseline selection

    // Apply the search-bin selection (tighter than baseline)
    const unsigned int searchBin = Selection::searchBin(evt->ht(),evt->mht(),evt->nJets());
    if( searchBin > 0 ) {
      hYields->Fill(searchBin,weight);
    }

  } // End of loop over events



  // --- Save the Histograms to File -----------------------------------
  TFile outFile("General_"+Sample::toTString(id)+"-Yields.root","RECREATE");
  hNJets->Write();
  hHt->Write();
  hMht->Write();
  for(unsigned int i = 0; i < hJetPt.size(); ++i) {
    hJetPt.at(i)->Write();
    hJetEta.at(i)->Write();
    hJetPhi.at(i)->Write();
    hDeltaPhi.at(i)->Write();
  }  
  hYields->Write();
  outFile.Close();
}
