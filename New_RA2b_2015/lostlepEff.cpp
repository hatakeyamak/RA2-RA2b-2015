
//Lost Lepton Efficiency and Acceptance maps

#include "Events.h"
#include "interface/LeptonEfficiency.h"
#include "interface/Selection.h"

#include "TTree.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "TChain.h"
#include <cmath>
#include <map>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "TLorentzVector.h"
#include <stdio.h>
#include "TColor.h"
#include "TF1.h"
#include "TLegend.h"
#include "TVector3.h"
#include "TFile.h"
#include "TH1.h"
#include "TVector2.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TROOT.h"


using namespace std;

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



int main(int argc, char *argv[]){

  /////////////////////////////////////
  if (argc != 6)
  {
    std::cout << "Please enter something like:  ./run \"filelist_WJets_PU20bx25_100_200.txt\" \"WJets_PU20bx25_100_200\" \"Results\" \"00\" \"0\" "      << std::endl;
    return EXIT_FAILURE;
  }
  
  //get the inputs from user
    const string InRootList = argv[1];
    const string subSampleKey = argv[2];
    const string OutDir = argv[3];
    const string inputNum = argv[4];
    const string verbosity = argv[5];
  //////////////////////////////////////
    int verbose = atoi(verbosity.c_str());
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





  //some varaibles
    char filenames[500];
    vector<string> filesVec;
    ifstream fin(InRootList.c_str());
    TChain *sample_AUX = new TChain("stopTreeMaker/AUX");

  ///read the file names from the .txt files and load them to a vector.
    while(fin.getline(filenames, 500) ){filesVec.push_back(filenames);}
    cout<< "\nProcessing " << subSampleKey << " ... " << endl;
    for(unsigned int in=0; in<filesVec.size(); in++){ sample_AUX->Add(filesVec.at(in).c_str()); }

  // get total number of events
  int N_Entries = sample_AUX->GetEntries();
  printf("Total Entries: %d \n ",N_Entries );

  // Interface to the event content
    Events * evt = new  Events(sample_AUX, subSampleKey);

  // Loop over the events (tree entries)
  for(int ie=0; ie < N_Entries ; ie++ ){
  if (ie >=1000)break;

//
  // --- Analyse the events --------------------------------------------


  if(verbose!=0)printf(" ########################### \n event #: %d \n ",ie);





    // Apply the NJets baseline-cut
    if(verbose!=0)printf("NJet: %d \n ",evt->vLJets(ie).size());
    if( !Selection::nJets(evt->vLJets(ie).size()) ) continue;
    // Apply the HT and MHT baseline-cuts
    if(verbose!=0)printf("ht: %g mht: %g \n ",evt->ht(ie),evt->mht(ie));
    if( !Selection::ht(evt->ht(ie)) ) continue;
    if( !Selection::mht(evt->mht(ie)) ) continue;
    // Apply the delta-phi cuts
    if(verbose!=0)printf("dphi0: %g dphi1: %g dphi2: %g \n ",evt->deltaPhiV(ie)[0],evt->deltaPhiV(ie)[1],evt->deltaPhiV(ie)[2]);
    if( !Selection::deltaPhi(evt->deltaPhiV(ie)[0],evt->deltaPhiV(ie)[1],evt->deltaPhiV(ie)[2]) ) continue;
/*
    // Select only events where the W decayed
    // - into a muon (pdgId 13)
    // - into a tau (pdgId 15) that decays into a muon
    const bool isWToMuon = (evt->W_emuVec_()->size()!=0) ? true : false;
    const bool isWToTauToMuon = (evt->W_tau_emuVec_()->size()!=0) ? true : false;
    if( !( isWToMuon || isWToTauToMuon ) ) continue;

    // Pick up the kinematic information from generator-level muon, i.e.
    // either the muon from W decay or the moun from tau decay
    double genMuPt=0.; 
    double genMuEta=-99.;
    double genMuPhi=-99.;
    int firstMuId=0;
    if(verbose!=0)printf(" List of particles: \n");
    for(int i=0; i < (int) evt->template_genDecayPdgIdVec_()->size();i++){///loop over all particles
      int pdgId = evt->template_genDecayPdgIdVec_()->at(i);
      if(verbose!=0)printf(" pdg: %d \n",pdgId);
      if(std::abs(pdgId)==13){//see if it is muon
        genMuPt = evt->template_genDecayLVec_()->at(i).Pt();
        genMuPt = evt->template_genDecayLVec_()->at(i).Eta();
        genMuPt = evt->template_genDecayLVec_()->at(i).Phi();
        firstMuId = pdgId;
      }
      if(pdgId!=firstMuId && std::abs(pdgId)==13){//check if there is another muon whith higher pt
        if(evt->template_genDecayLVec_()->at(i).Pt() > genMuPt)genMuPt=evt->template_genDecayLVec_()->at(i).Pt();
      }
    }
    if(verbose!=0)printf("MuPt: %g \n " , genMuPt);

    // Acceptance determination 1: Counter for all events
    // with muons at generator level
//    hNJetsVsMhtAll->Fill(evt->mht(),evt->nJets());

*/

 }//end of while. loop over events.  
}

