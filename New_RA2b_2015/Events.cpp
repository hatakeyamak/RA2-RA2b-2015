#include "Events.h"
#include <vector>


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
     MHTPhi=0.0; 
     DeltaPhi1=-99.;
     DeltaPhi2=-99.;
     DeltaPhi3=-99.;
     minDeltaPhiN=-99.;

     GenMu_GenMuFromTau=new int();
     GenTau_GenTauHad=new int();
     GenElec_GenElecFromTau=new int();

     GenMuPtVec=new vector<double>();   
     GenMuEtaVec=new vector<double>();   
     GenMuPhiVec=new vector<double>();   
     GenElecPtVec=new vector<double>();
     GenElecEtaVec=new vector<double>();
     GenElecPhiVec=new vector<double>();
     GenTauPtVec=new vector<double>();
     GenTauEtaVec=new vector<double>();
     GenTauPhiVec=new vector<double>();
     JetsPtVec=new vector<double>();
     JetsEtaVec=new vector<double>();
     JetsPhiVec=new vector<double>();
     MuonsPtVec=new vector<double>();
     MuonsEtaVec=new vector<double>();
     MuonsPhiVec=new vector<double>();
     ElectronsPtVec=new vector<double>();
     ElectronsEtaVec=new vector<double>();
     ElectronsPhiVec=new vector<double>();

     selectedIDIsoMuonsPtVec=new vector<double>();
     selectedIDIsoMuonsEtaVec=new vector<double>();
     selectedIDIsoMuonsPhiVec=new vector<double>();

     selectedIDIsoElectronsPtVec=new vector<double>();
     selectedIDIsoElectronsEtaVec=new vector<double>();
     selectedIDIsoElectronsPhiVec=new vector<double>();


     testVec=new vector<double>();


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
     fChain->SetBranchAddress("MHTPhi", &MHTPhi); 
     fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1);
     fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2);
     fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3);
     fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN);
     
   fChain->SetBranchAddress("GenMuPtVec", &GenMuPtVec);
   fChain->SetBranchAddress("GenMuEtaVec", &GenMuEtaVec);
   fChain->SetBranchAddress("GenMuPhiVec", &GenMuPhiVec);
   fChain->SetBranchAddress("GenMu_GenMuFromTau", GenMu_GenMuFromTau);
   fChain->SetBranchAddress("GenElecPtVec", &GenElecPtVec);
   fChain->SetBranchAddress("GenElecEtaVec", &GenElecEtaVec);
   fChain->SetBranchAddress("GenElecPhiVec", &GenElecPhiVec);
   fChain->SetBranchAddress("GenElec_GenElecFromTau", GenElec_GenElecFromTau);
   fChain->SetBranchAddress("GenTauPtVec", &GenTauPtVec);
   fChain->SetBranchAddress("GenTauEtaVec", &GenTauEtaVec);
   fChain->SetBranchAddress("GenTauPhiVec", &GenTauPhiVec);
   fChain->SetBranchAddress("GenTau_GenTauHad", GenTau_GenTauHad);
   fChain->SetBranchAddress("JetsPtVec", &JetsPtVec);
   fChain->SetBranchAddress("JetsEtaVec", &JetsEtaVec);
   fChain->SetBranchAddress("JetsPhiVec", &JetsPhiVec);
   fChain->SetBranchAddress("MuonsPtVec", &MuonsPtVec);
   fChain->SetBranchAddress("MuonsEtaVec", &MuonsEtaVec);
   fChain->SetBranchAddress("MuonsPhiVec", &MuonsPhiVec);
   fChain->SetBranchAddress("ElectronsPtVec", &ElectronsPtVec);
   fChain->SetBranchAddress("ElectronsEtaVec", &ElectronsEtaVec);
   fChain->SetBranchAddress("ElectronsPhiVec", &ElectronsPhiVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsPtVec", &selectedIDIsoMuonsPtVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsEtaVec", &selectedIDIsoMuonsEtaVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsPhiVec", &selectedIDIsoMuonsPhiVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsPtVec", &selectedIDIsoElectronsPtVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsEtaVec", &selectedIDIsoElectronsEtaVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsPhiVec", &selectedIDIsoElectronsPhiVec);

fChain->SetBranchAddress("testVec", &testVec);
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
  double Events::mhtphi() const { return MHTPhi; }

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

  // Gen Muon 
   vector<double>  Events::GenMuPtVec_() const { return *GenMuPtVec ;}
   vector<double>  Events::GenMuEtaVec_() const { return *GenMuEtaVec ;}
   vector<double>  Events::GenMuPhiVec_() const { return *GenMuPhiVec ;}

   vector<double>  Events::GenElecPtVec_() const { return *GenElecPtVec ;}
   vector<double>  Events::GenElecEtaVec_() const { return *GenElecEtaVec ;}
   vector<double>  Events::GenElecPhiVec_() const { return *GenElecPhiVec ;}


   vector<double>  Events::GenTauPtVec_() const { return *GenTauPtVec ;}
   vector<double>  Events::GenTauEtaVec_() const { return *GenTauEtaVec ;}
   vector<double>  Events::GenTauPhiVec_() const { return *GenTauPhiVec ;}

   vector<double>  Events::JetsPtVec_() const { return *JetsPtVec ;}
   vector<double>  Events::JetsEtaVec_() const { return *JetsEtaVec ;}
   vector<double>  Events::JetsPhiVec_() const { return *JetsPhiVec ;}
  
   vector<double>  Events::MuPtVec_() const{ return  *selectedIDIsoMuonsPtVec;}
   vector<double>  Events::MuEtaVec_() const{ return *selectedIDIsoMuonsEtaVec;}
   vector<double>  Events::MuPhiVec_() const{ return *selectedIDIsoMuonsPhiVec;}

   vector<double>  Events::ElecPtVec_() const{ return *selectedIDIsoElectronsPtVec;}
   vector<double>  Events::ElecEtaVec_() const{ return *selectedIDIsoElectronsEtaVec;}
   vector<double>  Events::ElecPhiVec_() const{return *selectedIDIsoElectronsPhiVec;}


   vector<int>     Events::GenMuFromTauVec_() const {
     vector<int> tempVec;
     for(int i=0; i< GenMuPtVec->size(); i++){
        tempVec.push_back((int)*(GenMu_GenMuFromTau+i)==1);
     }
     return tempVec;
   }

   vector<int>     Events::GenElecFromTauVec_() const {
     vector<int> tempVec;
     for(int i=0; i< GenElecPtVec->size(); i++){
        tempVec.push_back((int)*(GenElec_GenElecFromTau+i)==1);
     }
     return tempVec;
  }


  vector<int>     Events::GenTauHadVec_() const { 
    vector<int> tempVec;
    for(int i=0; i< GenTauPtVec->size(); i++){
      tempVec.push_back((int) *(GenTau_GenTauHad+i) ==1);
    }
    return tempVec;
  }



  
//  std::vector<double> Events::Pt_GenMu() const { 
//    std::vector<double> tempV;
//    tempV.assign(&GenMuPt[0],&GenMuPt[0]+2);
//std::vector<double> tempV(GenMuPt,GenMuPt+sizeof(GenMuPt)/sizeof(double));
//    return tempV;
//  }

//  double Events::Eta_GenMu() const { return GenMuEta;}
//  double Events::Phi_GenMu() const { return GenMuPhi;}


