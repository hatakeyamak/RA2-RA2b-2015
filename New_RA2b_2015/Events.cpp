#include "Events.h"



  //Constructor
  Events::Events(TTree * ttree_, const std::string sampleKeyString, int verbose) : currentEntry_(-1) {

    //Initialize some varaibles
     RunNum=-1;
     LumiBlockNum=-1;
     EvtNum=-1;
     NVtx=-1;
     isoTracks=-1;
     Leptons=-1;
     NJets=-1;
     BTags=-1;
     Weight=1;
     HT=0.0;
     MHT=0.0;
     DeltaPhi1=-99.;
     DeltaPhi2=-99.;
     DeltaPhi3=-99.;
     minDeltaPhiN=-99.;
     fChain = ttree_;
    
    /// the variables
     fChain->SetBranchAddress("RunNum", &RunNum);
     fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum);
     fChain->SetBranchAddress("EvtNum", &EvtNum);
     fChain->SetBranchAddress("NVtx", &NVtx);
     fChain->SetBranchAddress("isoTracks", &isoTracks);
     fChain->SetBranchAddress("Leptons", &Leptons);
     fChain->SetBranchAddress("NJets", &NJets);
     fChain->SetBranchAddress("BTags", &BTags);
     fChain->SetBranchAddress("Weight", &Weight);
     fChain->SetBranchAddress("HT", &HT);
     fChain->SetBranchAddress("MHT", &MHT);
     fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1);
     fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2);
     fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3);
     fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN);

    // Number of total entries
    template_Entries = fChain->GetEntries();
    







  }//end of class constructor Event


  // A function to make events available
  bool Events::loadNext() {

    if( currentEntry_ < 0 ) {
      std::cout << "Processing " << template_Entries << " events" << std::endl;
    }

    ++currentEntry_;

    if( currentEntry_ == template_Entries ) {

      return false;

    } else {

      if( currentEntry_ > 0 && currentEntry_%100000 == 0 ) {
        std::cout << " Processed " << currentEntry_ << " events" << std::endl;
      }

      fChain->GetEntry(currentEntry_);
      return true;

    }

  }


// Some Functions

  // Event weight (for luminosity and PU profile)
  double Events::weight() const { return Weight; }

  // HT and MHT
  double Events::ht() const { return HT; }
  double Events::mht() const { return MHT; }

  // Number of HT jets
  int Events::nJets() const { return NJets; }

  // Number of B jets
  int Events::nBtags() const { return BTags; }

  // Number of Leptons
  int Events::nLeptons() const { return Leptons; }

  // Number of IsoTrk 
  int Events::nIso() const { return isoTracks; }

  // DeltaPhi between leading three MHT jets and MHT
  double Events::deltaPhi1() const { return DeltaPhi1; }
  double Events::deltaPhi2() const { return DeltaPhi2; }
  double Events::deltaPhi3() const { return DeltaPhi3; }
