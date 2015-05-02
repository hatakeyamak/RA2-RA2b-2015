#ifdef __MAKECINT__
#pragma link C++ class vector<int>;
#pragma link C++ class vector<vector<int> >;
#pragma link C++ class vector<vector<vector<int> > >;
#pragma link C++ class vector<TLorentzVector>;
#pragma link C++ class vector<vector<TLorentzVector> >;
#endif


#ifndef EVENT_H
#define EVENT_H

#include <cmath>
#include <exception>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TLorentzVector.h"


// Access the event content. Interfaces the TTree entries in the input ntuples.
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013
// Modified by Ahmad Borzou
//         ahmad.borzou@cern.ch
//         Feb 2015




// Global variables
  static const double pt30Arr[] = { -1, -1, 30, -1 };
  static const double pt30Eta24Arr[] = { -1, 2.4, 30, -1 };
  static const double pt50Eta24Arr[] = { -1, 2.4, 50, -1 };
  static const double pt70Eta24Arr[] = { -1, 2.4, 70, -1 };
  static const double dphiArr[] = { -1, 4.7, 30, -1 };
  static const double bTagArr[] = { -1, 2.4, 30, -1 };
  static const double pt50Arr[] = { -1, -1, 50, -1 };
  static const double pt70Arr[] = { -1, -1, 70, -1 };



class Event {
public:


  // Constructor. Expects name of the ntuple file and the maximum number 
  // of processed events. If numProcessed < 1, all events are processed.
  Event(const string fileName, int numProcessed);
  ~Event();

  // Return the maximum number of analysed events
  int nTotEvents() const { return nTotEvts_; }

  // Loads the content of the next event. Returns false if
  // no next event exists.
  bool loadNext();


  // Access to the event content

  // Event weight (for luminosity and PU profile)
  double weight() const { return weight_; }

  // HT and MHT
  double ht() const { return ht_; }
  double mht() const { return mht_; }
  double mhtPhi() const { return mhtPhi_; }
  // Number of HT jets
  int nJets() const { return nJets_; }
  // DeltaPhi between leading three MHT jets and MHT
  double deltaPhi1() const { return deltaPhi1_; }
  double deltaPhi2() const { return deltaPhi2_; }
  double deltaPhi3() const { return deltaPhi3_; }

  // Transverse mass of leading isolated muon and MET
  double mt() const { return mt_; }
  // MET for mt computation
  double met() const { return met_; }
  double metPhi() const { return metPhi_; }
  
  // Well-reconstructed jets
  int jetsN() const { return jetsN_; }   
  double*   jetsPt() const { return jetsPt_; }  
  double*   jetsEta() const { return jetsEta_; } 
  double*   jetsPhi() const { return jetsPhi_; }
  double*   jetsE() const { return jetsE_; }   

  // Well-reconstructed muons
  int muonsN() const { return muonsN_; }   
  double*   muonsPt() const { return muonsPt_; }  
  double*   muonsEta() const { return muonsEta_; } 
  double*   muonsPhi() const { return muonsPhi_; }
  double*   muonsE() const { return muonsE_; }   

  // Well-reconstructed and isolated muons
  int isoMuonsN() const { return isoMuonsN_; }   
  double*   isoMuonsPt() const { return isoMuonsPt_; }  
  double*   isoMuonsEta() const { return isoMuonsEta_; } 
  double*   isoMuonsPhi() const { return isoMuonsPhi_; }
  double*   isoMuonsE() const { return isoMuonsE_; }   

  // Well-reconstructed electrons
  int electronsN() const { return electronsN_; }   
  double*   electronsPt() const { return electronsPt_; }  
  double*   electronsEta() const { return electronsEta_; } 
  double*   electronsPhi() const { return electronsPhi_; }
  double*   electronsE() const { return electronsE_; }   

  // Well-reconstructed and isolated electrons
  int isoElectronsN() const { return isoElectronsN_; }   
  double*   isoElectronsPt() const { return isoElectronsPt_; }  
  double*   isoElectronsEta() const { return isoElectronsEta_; } 
  double*   isoElectronsPhi() const { return isoElectronsPhi_; }
  double*   isoElectronsE() const { return isoElectronsE_; }   

  // Generator-level decay information
  int flgW() const { return flgW_; }
  int flgTau() const { return flgTau_; }

  // Generatorl-level letpon from W decay
  double genLeptonPt() const { return genLeptonPt_; }
  double genLeptonEta() const { return genLeptonEta_; }
  double genLeptonPhi() const { return genLeptonPhi_; }
  double genLeptonE() const { return genLeptonE_; }
  Int_t genLeptonPdgId() const { return genLeptonPdgId_; }

  // Generator-level lepton from tau decay
  double genLeptonFromTauPt() const { return genLeptonFromTauPt_; }
  double genLeptonFromTauEta() const { return genLeptonFromTauEta_; }
  double genLeptonFromTauPhi() const { return genLeptonFromTauPhi_; }
  double genLeptonFromTauE() const { return genLeptonFromTauE_; }
  Int_t genLeptonFromTauPdgId() const { return genLeptonFromTauPdgId_; }

  // 
  int countJets(const vector<TLorentzVector> &inputJets, const double *jetCutsArr){
  return countJets(inputJets, jetCutsArr[0], jetCutsArr[1], jetCutsArr[2], jetCutsArr[3]);
  }
  int countJets(const vector<TLorentzVector> &inputJets, const double minAbsEta, const double maxAbsEta, const double minPt, const double maxPt){
  int cntNJets =0;
  for(unsigned int ij=0; ij<inputJets.size(); ij++){
  double perjetpt = inputJets[ij].Pt(), perjeteta = inputJets[ij].Eta();
  if( ( minAbsEta == -1 || fabs(perjeteta) >= minAbsEta )
  && ( maxAbsEta == -1 || fabs(perjeteta) < maxAbsEta )
  && ( minPt == -1 || perjetpt >= minPt )
  && ( maxPt == -1 || perjetpt < maxPt ) ){
  cntNJets ++;
  }
  }
  return cntNJets;
  }


private:
  const int maxColSize_;
  int nTotEvts_;
  int currentEntry_;

  TChain* chain_;

  double weight_;

  double ht_;
  double mht_;
  double mhtPhi_;
  int nJets_;
  double deltaPhi1_;
  double deltaPhi2_;
  double deltaPhi3_;
  double mt_;
  double met_;
  double metPhi_;

  int jetsN_;   
  double*   jetsPt_;  
  double*   jetsEta_; 
  double*   jetsPhi_;
  double*   jetsE_;   

  int muonsN_;   
  double*   muonsPt_;  
  double*   muonsEta_; 
  double*   muonsPhi_;
  double*   muonsE_;   

  int isoMuonsN_;   
  double*   isoMuonsPt_;  
  double*   isoMuonsEta_; 
  double*   isoMuonsPhi_;
  double*   isoMuonsE_;   

  int electronsN_;   
  double*   electronsPt_;  
  double*   electronsEta_; 
  double*   electronsPhi_;
  double*   electronsE_;   

  int isoElectronsN_;   
  double*   isoElectronsPt_;  
  double*   isoElectronsEta_; 
  double*   isoElectronsPhi_;
  double*   isoElectronsE_;   

  double genLeptonPt_;
  double genLeptonEta_;
  double genLeptonPhi_;
  double genLeptonE_;
  Int_t genLeptonPdgId_;

  double genLeptonFromTauPt_;
  double genLeptonFromTauEta_;
  double genLeptonFromTauPhi_;
  double genLeptonFromTauE_;
  Int_t genLeptonFromTauPdgId_;

  int flgW_;
  int flgTau_;
  
  
  vector<TLorentzVector> * template_oriJetsVec;
  int cntNJetsPt30Eta24;
};


Event::Event(const string InRootList, int numProcessed)
  : maxColSize_(50), currentEntry_(-1) {

  std::cout << "Setting up event variables ... " << std::flush;

  jetsPt_  = new double[maxColSize_];  
  jetsEta_ = new double[maxColSize_]; 
  jetsPhi_ = new double[maxColSize_];
  jetsE_   = new double[maxColSize_];   

  muonsPt_  = new double[maxColSize_];  
  muonsEta_ = new double[maxColSize_]; 
  muonsPhi_ = new double[maxColSize_];
  muonsE_   = new double[maxColSize_];   

  isoMuonsPt_  = new double[maxColSize_];  
  isoMuonsEta_ = new double[maxColSize_]; 
  isoMuonsPhi_ = new double[maxColSize_];
  isoMuonsE_   = new double[maxColSize_];   

  electronsPt_  = new double[maxColSize_];  
  electronsEta_ = new double[maxColSize_]; 
  electronsPhi_ = new double[maxColSize_];
  electronsE_   = new double[maxColSize_];   

  isoElectronsPt_  = new double[maxColSize_];  
  isoElectronsEta_ = new double[maxColSize_]; 
  isoElectronsPhi_ = new double[maxColSize_];
  isoElectronsE_   = new double[maxColSize_];   

  template_oriJetsVec = new vector<TLorentzVector>();
  
  char filenames[500];
  vector<string> filesVec;
  ///read the file names from the .txt files and load them to a vector.
  ifstream fin(InRootList.c_str());while(fin.getline(filenames, 500) ){filesVec.push_back(filenames);}

  chain_ = new TChain("stopTreeMaker/AUX");
  for(unsigned int in=0; in<filesVec.size(); in++){ chain_->Add(filesVec.at(in).c_str()); }
  //  chain_->Add(fileName);
  nTotEvts_ = ( numProcessed < 0 ) ? chain_->GetEntries() : std::min(numProcessed,static_cast<int>(chain_->GetEntries()));

  chain_->SetBranchStatus("*",0);
  // Set the branches
  chain_->SetBranchStatus("jetsLVec", 1);chain_->SetBranchAddress("jetsLVec", &template_oriJetsVec);


  //chain_->SetBranchAddress("NJets",&nJets_);
  cntNJetsPt30Eta24 = countJets((*template_oriJetsVec), pt30Eta24Arr);
  nJets_ = (int) template_oriJetsVec->size();//cntNJetsPt30Eta24;

  chain_->SetBranchStatus("mht",1);chain_->SetBranchAddress("mht", &mht_);

/*
  chain_->SetBranchAddress("Weight",&weight_);

  chain_->SetBranchAddress("HT",&ht_);
  chain_->SetBranchAddress("MHTPhi",&mhtPhi_);
  chain_->SetBranchAddress("DeltaPhi1",&deltaPhi1_);
  chain_->SetBranchAddress("DeltaPhi2",&deltaPhi2_);
  chain_->SetBranchAddress("DeltaPhi3",&deltaPhi3_);
  chain_->SetBranchAddress("MT",&mt_);
  chain_->SetBranchAddress("MET",&met_);
  chain_->SetBranchAddress("METPhi",&metPhi_);

  chain_->SetBranchAddress("JetsNum",&jetsN_);
  chain_->SetBranchAddress("JetsPt",  jetsPt_);  
  chain_->SetBranchAddress("JetsEta", jetsEta_);
  chain_->SetBranchAddress("JetsPhi", jetsPhi_);
  chain_->SetBranchAddress("JetsE",   jetsE_);

  chain_->SetBranchAddress("MuonsNum",&muonsN_);
  chain_->SetBranchAddress("MuonsPt",  muonsPt_);  
  chain_->SetBranchAddress("MuonsEta", muonsEta_);
  chain_->SetBranchAddress("MuonsPhi", muonsPhi_);
  chain_->SetBranchAddress("MuonsE",   muonsE_);

  chain_->SetBranchAddress("IsoMuonsNum",&isoMuonsN_);
  chain_->SetBranchAddress("IsoMuonsPt",  isoMuonsPt_);  
  chain_->SetBranchAddress("IsoMuonsEta", isoMuonsEta_);
  chain_->SetBranchAddress("IsoMuonsPhi", isoMuonsPhi_);
  chain_->SetBranchAddress("IsoMuonsE",   isoMuonsE_);

  chain_->SetBranchAddress("ElecsNum",&electronsN_);
  chain_->SetBranchAddress("ElecsPt",  electronsPt_);  
  chain_->SetBranchAddress("ElecsEta", electronsEta_);
  chain_->SetBranchAddress("ElecsPhi", electronsPhi_);
  chain_->SetBranchAddress("ElecsE",   electronsE_);

  chain_->SetBranchAddress("IsoElecsNum",&isoElectronsN_);
  chain_->SetBranchAddress("IsoElecsPt",  isoElectronsPt_);  
  chain_->SetBranchAddress("IsoElecsEta", isoElectronsEta_);
  chain_->SetBranchAddress("IsoElecsPhi", isoElectronsPhi_);
  chain_->SetBranchAddress("IsoElecsE",   isoElectronsE_);

  if( chain_->GetListOfBranches()->FindObject("FlgW") ) {
    // In case of W+jets sampel
    chain_->SetBranchAddress("FlgW",&flgW_);
    chain_->SetBranchAddress("FlgTau",&flgTau_);
    
    chain_->SetBranchAddress("GenLeptonPt",  &genLeptonPt_);  
    chain_->SetBranchAddress("GenLeptonEta", &genLeptonEta_);
    chain_->SetBranchAddress("GenLeptonPhi", &genLeptonPhi_);
    chain_->SetBranchAddress("GenLeptonE",   &genLeptonE_);
    chain_->SetBranchAddress("GenLeptonPdgId",  &genLeptonPdgId_);
    
    chain_->SetBranchAddress("GenLeptonFromTauPt",  &genLeptonFromTauPt_);  
    chain_->SetBranchAddress("GenLeptonFromTauEta", &genLeptonFromTauEta_);
    chain_->SetBranchAddress("GenLeptonFromTauPhi", &genLeptonFromTauPhi_);
    chain_->SetBranchAddress("GenLeptonFromTauE",   &genLeptonFromTauE_);
    chain_->SetBranchAddress("GenLeptonFromTauPdgId",  &genLeptonFromTauPdgId_);
  }
*/
  std::cout << "ok" << std::endl;
}


Event::~Event() {

  for(int i = 0; i < maxColSize_; ++i) {
    delete [] jetsPt_;  
    delete [] jetsEta_; 
    delete [] jetsPhi_;
    delete [] jetsPhi_;   
    delete [] muonsPt_;  
    delete [] muonsEta_; 
    delete [] muonsPhi_;
    delete [] muonsPhi_;   
    delete [] isoMuonsPt_;  
    delete [] isoMuonsEta_; 
    delete [] isoMuonsPhi_;
    delete [] isoMuonsPhi_;   
    delete [] electronsPt_;  
    delete [] electronsEta_; 
    delete [] electronsPhi_;
    delete [] electronsPhi_;   
    delete [] isoElectronsPt_;  
    delete [] isoElectronsEta_; 
    delete [] isoElectronsPhi_;
    delete [] isoElectronsPhi_;   
  }

  delete chain_;
}


bool Event::loadNext() {
  if( currentEntry_ < 0 ) {
    std::cout << "Processing " << nTotEvents() << " events" << std::endl;
  }
  ++currentEntry_;

  if( currentEntry_ == nTotEvts_ ) {

    return false;

  } else {

    if( currentEntry_ > 0 && currentEntry_%100000 == 0 ) {
      std::cout << "  Processed " << currentEntry_ << " events" << std::endl;
    }
  
    chain_->GetEntry(currentEntry_);
    if( jetsN_ > maxColSize_ ) {
      std::cerr << "\n\nERROR: number of read jets in entry " << currentEntry_ << " larger than array size" << std::endl;
//      throw std::exception();
    }
    if( muonsN_ > maxColSize_ ) {
      std::cerr << "\n\nERROR: number of read muons in entry " << currentEntry_ << " larger than array size" << std::endl;
//      throw std::exception();
    }
    if( isoMuonsN_ > maxColSize_ ) {
      std::cerr << "\n\nERROR: number of read iso-muons in entry " << currentEntry_ << " larger than array size" << std::endl;
//      throw std::exception();
    }
    if( electronsN_ > maxColSize_ ) {
      std::cerr << "\n\nERROR: number of read electrons in entry " << currentEntry_ << " larger than array size: " << std::endl;
//      throw std::exception();
    }
    if( isoElectronsN_ > maxColSize_ ) {
      std::cerr << "\n\nERROR: number of read iso-electrons in entry " << currentEntry_ << " larger than array size" << std::endl;
//      throw std::exception();
    }

    return true;
  }
}

#endif
