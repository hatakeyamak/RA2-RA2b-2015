#include "Events.h"
#include <vector>


  //Constructor
  Events::Events(TTree * ttree_, const std::string sampleKeyString, int verbose) : currentEntry_(-1) {

    // Data or MC ?
    DataBool=true;
  
    //Initialize some varaibles
     RunNum=-1;
     LumiBlockNum=-1;
     EvtNum=-1;
     NVtx=-1;
//     isoTracks=-1;
     isoElectronTracks=-1;
     isoMuonTracks=-1;
     isoPionTracks=-1;
     Leptons=-1;
     NJets=-1;
     BTags=-1;
     Weight=1;
     HT=0.0;
     MHT=0.0;
     MHT_Phi=0.0; 
     //MHTPhi=0.0;
     METPt=0.0;
     METPhi=0.0;
     DeltaPhi1=-99.;
     DeltaPhi2=-99.;
     DeltaPhi3=-99.;
     minDeltaPhiN_=-99.;

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
     GenTauNuPtVec=new vector<double>();
     GenTauNuEtaVec=new vector<double>();
     GenTauNuPhiVec=new vector<double>();
     JetsPtVec=new vector<double>();
     JetsEtaVec=new vector<double>();
     JetsPhiVec=new vector<double>();
//     Jets_bDiscriminator=new Float_t();
     slimmedMuonsPtVec=new vector<double>();
     slimmedMuonsEtaVec=new vector<double>();
     slimmedMuonsPhiVec=new vector<double>();
     MuonsPtVec=new vector<double>();
     MuonsEtaVec=new vector<double>();
     MuonsPhiVec=new vector<double>();
     selectedIDIsoMuonsPtVec=new vector<double>();
     selectedIDIsoMuonsEtaVec=new vector<double>();
     selectedIDIsoMuonsPhiVec=new vector<double>();
     selectedIDMuonsPtVec=new vector<double>();
     selectedIDMuonsEtaVec=new vector<double>();
     selectedIDMuonsPhiVec=new vector<double>();

     slimmedElectronsPtVec=new vector<double>();
     slimmedElectronsEtaVec=new vector<double>();
     slimmedElectronsPhiVec=new vector<double>();
     ElectronsPtVec=new vector<double>();
     ElectronsEtaVec=new vector<double>();
     ElectronsPhiVec=new vector<double>();
     selectedIDIsoElectronsPtVec=new vector<double>();
     selectedIDIsoElectronsEtaVec=new vector<double>();
     selectedIDIsoElectronsPhiVec=new vector<double>();
     selectedIDElectronsPtVec=new vector<double>();
     selectedIDElectronsEtaVec=new vector<double>();
     selectedIDElectronsPhiVec=new vector<double>();

     selectedIDIsoElectronsPtVec=new vector<double>();
     selectedIDIsoElectronsEtaVec=new vector<double>();
     selectedIDIsoElectronsPhiVec=new vector<double>();

     slimJetPtVec=new vector<double>();
     slimJetEtaVec=new vector<double>();
     slimJetPhiVec=new vector<double>();

     IsolatedElectronTracksVetoPtVec = new vector<double>();
     IsolatedElectronTracksVetoEtaVec = new vector<double>();
     IsolatedElectronTracksVetoPhiVec = new vector<double>();
     IsolatedMuonTracksVetoPtVec = new vector<double>();
     IsolatedMuonTracksVetoEtaVec = new vector<double>();
     IsolatedMuonTracksVetoPhiVec = new vector<double>();
     IsolatedPionTracksVetoPtVec = new vector<double>();
     IsolatedPionTracksVetoEtaVec = new vector<double>();
     IsolatedPionTracksVetoPhiVec = new vector<double>();

     testVec=new vector<double>();

     TriggerNames=new vector<string>();
     PassTrigger=new vector<int>();

     fChain = ttree_;
    
    /// the variables
     fChain->SetBranchAddress("RunNum", &RunNum);
     fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum);
     fChain->SetBranchAddress("EvtNum", &EvtNum);
     fChain->SetBranchAddress("NVtx", &NVtx);
//     fChain->SetBranchAddress("isoTracks", &isoTracks);
     fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks);
     fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks);
     fChain->SetBranchAddress("isoPionTracks", &isoPionTracks);
     fChain->SetBranchAddress("Leptons", &Leptons);
     fChain->SetBranchAddress("NJets", &NJets);
     fChain->SetBranchAddress("BTags", &BTags);
     fChain->SetBranchAddress("Weight", &Weight);
     fChain->SetBranchAddress("HT", &HT);
     fChain->SetBranchAddress("MHT", &MHT);
     fChain->SetBranchAddress("MHT_Phi", &MHT_Phi);
     //fChain->SetBranchAddress("MHTPhi", &MHTPhi);
     fChain->SetBranchAddress("METPt", &METPt);
     fChain->SetBranchAddress("METPhi", &METPhi); 
     fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1);
     fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2);
     fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3);
     fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN_);
     fChain->SetBranchAddress("JetID", &JetID);
     
     if(!DataBool){
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
       fChain->SetBranchAddress("GenTauNuPtVec", &GenTauNuPtVec);
       fChain->SetBranchAddress("GenTauNuEtaVec", &GenTauNuEtaVec);
       fChain->SetBranchAddress("GenTauNuPhiVec", &GenTauNuPhiVec);
     }

     fChain->SetBranchAddress("JetsPtVec", &JetsPtVec);
     fChain->SetBranchAddress("JetsEtaVec", &JetsEtaVec);
     fChain->SetBranchAddress("JetsPhiVec", &JetsPhiVec);
     fChain->SetBranchAddress("Jets_bDiscriminator", Jets_bDiscriminator);
     fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", Jets_chargedEmEnergyFraction);
     fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", Jets_chargedHadronEnergyFraction);
     fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", Jets_chargedHadronMultiplicity);
     fChain->SetBranchAddress("Jets_electronMultiplicity", Jets_electronMultiplicity);
     fChain->SetBranchAddress("Jets_jetArea", Jets_jetArea);
     fChain->SetBranchAddress("Jets_muonEnergyFraction", Jets_muonEnergyFraction);
     fChain->SetBranchAddress("Jets_muonMultiplicity", Jets_muonMultiplicity);
     fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", Jets_neutralEmEnergyFraction);
     fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", Jets_neutralHadronMultiplicity);
     fChain->SetBranchAddress("Jets_photonEnergyFraction", Jets_photonEnergyFraction);
     fChain->SetBranchAddress("Jets_photonMultiplicity", Jets_photonMultiplicity);


     fChain->SetBranchAddress("slimmedMuonsPtVec", &slimmedMuonsPtVec);
     fChain->SetBranchAddress("slimmedMuonsEtaVec", &slimmedMuonsEtaVec);
     fChain->SetBranchAddress("slimmedMuonsPhiVec", &slimmedMuonsPhiVec);
     fChain->SetBranchAddress("MuonsPtVec", &MuonsPtVec);
     fChain->SetBranchAddress("MuonsEtaVec", &MuonsEtaVec);
     fChain->SetBranchAddress("MuonsPhiVec", &MuonsPhiVec);
     fChain->SetBranchAddress("selectedIDIsoMuonsPtVec", &selectedIDIsoMuonsPtVec);
     fChain->SetBranchAddress("selectedIDIsoMuonsEtaVec", &selectedIDIsoMuonsEtaVec);
     fChain->SetBranchAddress("selectedIDIsoMuonsPhiVec", &selectedIDIsoMuonsPhiVec);
     fChain->SetBranchAddress("selectedIDMuonsPtVec", &selectedIDMuonsPtVec);
     fChain->SetBranchAddress("selectedIDMuonsEtaVec", &selectedIDMuonsEtaVec);
     fChain->SetBranchAddress("selectedIDMuonsPhiVec", &selectedIDMuonsPhiVec);

     fChain->SetBranchAddress("slimmedElectronsPtVec", &slimmedElectronsPtVec);
     fChain->SetBranchAddress("slimmedElectronsEtaVec", &slimmedElectronsEtaVec);
     fChain->SetBranchAddress("slimmedElectronsPhiVec", &slimmedElectronsPhiVec);
     fChain->SetBranchAddress("ElectronsPtVec", &ElectronsPtVec);
     fChain->SetBranchAddress("ElectronsEtaVec", &ElectronsEtaVec);
     fChain->SetBranchAddress("ElectronsPhiVec", &ElectronsPhiVec);
     fChain->SetBranchAddress("selectedIDIsoElectronsPtVec", &selectedIDIsoElectronsPtVec);
     fChain->SetBranchAddress("selectedIDIsoElectronsEtaVec", &selectedIDIsoElectronsEtaVec);
     fChain->SetBranchAddress("selectedIDIsoElectronsPhiVec", &selectedIDIsoElectronsPhiVec);
     fChain->SetBranchAddress("selectedIDElectronsPtVec", &selectedIDElectronsPtVec);
     fChain->SetBranchAddress("selectedIDElectronsEtaVec", &selectedIDElectronsEtaVec);
     fChain->SetBranchAddress("selectedIDElectronsPhiVec", &selectedIDElectronsPhiVec);

     fChain->SetBranchAddress("slimJetPtVec", &slimJetPtVec);
     fChain->SetBranchAddress("slimJetEtaVec", &slimJetEtaVec);
     fChain->SetBranchAddress("slimJetPhiVec", &slimJetPhiVec);
     fChain->SetBranchAddress("slimJet_slimJetID", slimJet_slimJetID);
     
     fChain->SetBranchAddress("IsolatedElectronTracksVetoPtVec", &IsolatedElectronTracksVetoPtVec);
     fChain->SetBranchAddress("IsolatedElectronTracksVetoEtaVec", &IsolatedElectronTracksVetoEtaVec);
     fChain->SetBranchAddress("IsolatedElectronTracksVetoPhiVec", &IsolatedElectronTracksVetoPhiVec);

     fChain->SetBranchAddress("IsolatedMuonTracksVetoPtVec", &IsolatedMuonTracksVetoPtVec);
     fChain->SetBranchAddress("IsolatedMuonTracksVetoEtaVec", &IsolatedMuonTracksVetoEtaVec);
     fChain->SetBranchAddress("IsolatedMuonTracksVetoPhiVec", &IsolatedMuonTracksVetoPhiVec);

     fChain->SetBranchAddress("IsolatedPionTracksVetoPtVec", &IsolatedPionTracksVetoPtVec);
     fChain->SetBranchAddress("IsolatedPionTracksVetoEtaVec", &IsolatedPionTracksVetoEtaVec);
     fChain->SetBranchAddress("IsolatedPionTracksVetoPhiVec", &IsolatedPionTracksVetoPhiVec);

     //
     fChain->SetBranchAddress("TriggerNames", &TriggerNames);
     fChain->SetBranchAddress("PassTrigger", &PassTrigger);
 
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

  // Run number & event number
  int Events::Runnum() const { return RunNum; }
  int Events::Evtnum() const { return EvtNum; }

  // Event weight (for luminosity and PU profile)
  double Events::weight() const { return Weight; }

  // HT and MHT
  double Events::ht() const { return HT; }
  double Events::mht() const { return MHT; }
  double Events::mhtphi() const { return /*MHTPhi;*/ MHT_Phi; }

  // MET 
  double Events::met() const { return METPt; }
  double Events::metphi() const { return METPhi; }


  // Number of HT jets
  int Events::nJets() const { return NJets; }

  // Number of B jets
  int Events::nBtags() const { return BTags; }

  // Number of Leptons
  int Events::nLeptons() const {
    int tempN;
    tempN= ( (int)selectedIDIsoMuonsPtVec->size() + (int)selectedIDIsoElectronsPtVec->size() );
    return tempN; 
//    return Leptons;
  }

  // Number of IsoTrk 
//  int Events::nIso() const { return isoTracks; }
  int Events::nIsoElec() const { return isoElectronTracks; }
  int Events::nIsoMu() const { return isoMuonTracks; }
  int Events::nIsoPion() const { return isoPionTracks; }

  // DeltaPhi between leading three MHT jets and MHT
  double Events::deltaPhi1() const { return DeltaPhi1; }
  double Events::deltaPhi2() const { return DeltaPhi2; }
  double Events::deltaPhi3() const { return DeltaPhi3; }
  double Events::minDeltaPhiN() const { return minDeltaPhiN_; }

  // To see if an event passes the jetId requirement or not.  
  int Events::JetId() const {
/*
    int jetid=1;
    // We only consider HTJets 
    for(int i=0; i< slimJetPtVec->size(); i++){
      if(slimJetPtVec->at(i) > 30. && fabs(slimJetEtaVec->at(i)) < 2.4 ){
        if( (int)*(slimJet_slimJetID+i) == 0 )jetid=0;
      }
    }
    return jetid;
*/
    return JetID;
  }

  bool Events::DataBool_() const { return DataBool; }

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

   vector<double>  Events::GenTauNuPtVec_() const { return *GenTauNuPtVec ;}
   vector<double>  Events::GenTauNuEtaVec_() const { return *GenTauNuEtaVec ;}
   vector<double>  Events::GenTauNuPhiVec_() const { return *GenTauNuPhiVec ;}

   vector<double>  Events::JetsPtVec_() const { return *JetsPtVec ;}
   vector<double>  Events::JetsEtaVec_() const { return *JetsEtaVec ;}
   vector<double>  Events::JetsPhiVec_() const { return *JetsPhiVec ;}
   vector<double>  Events::csvVec() const {
    vector<double> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((double)*(Jets_bDiscriminator+i));
    }
    return tempvec;
   }

   vector<double>  Events::Jets_chargedEmEnergyFraction_() const {
    vector<double> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((double)*(Jets_chargedEmEnergyFraction+i));
    }
    return tempvec;
   }

   vector<double>  Events::Jets_chargedHadronEnergyFraction_() const {
    vector<double> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((double)*(Jets_chargedHadronEnergyFraction+i));
    }
    return tempvec;
   }

   vector<int>  Events::Jets_chargedHadronMultiplicity_() const {
    vector<int> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((int)*(Jets_chargedHadronMultiplicity+i));
    }
    return tempvec;
   }

   vector<int>  Events::Jets_electronMultiplicity_() const {
    vector<int> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((int)*(Jets_electronMultiplicity+i));
    }
    return tempvec;
   }

   vector<double>  Events::Jets_jetArea_() const {
    vector<double> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((double)*(Jets_jetArea+i));
    }
    return tempvec;
   }

   vector<double>  Events::Jets_muonEnergyFraction_() const {
    vector<double> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((double)*(Jets_muonEnergyFraction+i));
    }
    return tempvec;
   }

   vector<int>  Events::Jets_muonMultiplicity_() const {
    vector<int> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((int)*(Jets_muonMultiplicity+i));
    }
    return tempvec;
   }

   vector<double>  Events::Jets_neutralEmEnergyFraction_() const {
    vector<double> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((double)*(Jets_neutralEmEnergyFraction+i));
    }
    return tempvec;
   }

   vector<int>  Events::Jets_neutralHadronMultiplicity_() const {
    vector<int> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((int)*(Jets_neutralHadronMultiplicity+i));
    }
    return tempvec;
   }

   vector<double>  Events::Jets_photonEnergyFraction_() const {
    vector<double> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((double)*(Jets_photonEnergyFraction+i));
    }
    return tempvec;
   }

   vector<int>  Events::Jets_photonMultiplicity_() const {
    vector<int> tempvec;
    tempvec.clear();
    for(int i=0; i< JetsPtVec->size();i++){
      tempvec.push_back((int)*(Jets_photonMultiplicity+i));
    }
    return tempvec;
   }


   vector<double>  Events::slimJetPtVec_() const { return *slimJetPtVec ;}
   vector<double>  Events::slimJetEtaVec_() const { return *slimJetEtaVec ;}
   vector<double>  Events::slimJetPhiVec_() const { return *slimJetPhiVec ;}

   vector<int>     Events::slimJetID_() const { 
     vector<int> tempVec;
     for(int i=0; i< slimJetPtVec->size(); i++){
        tempVec.push_back((int)*(slimJet_slimJetID+i));
     }
     return tempVec;
   }  


   vector<double>  Events::slimmedMuPtVec_() const{ return  *slimmedMuonsPtVec;}
   vector<double>  Events::slimmedMuEtaVec_() const{ return *slimmedMuonsEtaVec;}
   vector<double>  Events::slimmedMuPhiVec_() const{ return *slimmedMuonsPhiVec;}
   vector<double>  Events::MuNoIsoPtVec_() const{ return  *selectedIDMuonsPtVec;}
   vector<double>  Events::MuNoIsoEtaVec_() const{ return *selectedIDMuonsEtaVec;}
   vector<double>  Events::MuNoIsoPhiVec_() const{ return *selectedIDMuonsPhiVec;}
   vector<double>  Events::MuPtVec_() const{ return  *selectedIDIsoMuonsPtVec;}
   vector<double>  Events::MuEtaVec_() const{ return *selectedIDIsoMuonsEtaVec;}
   vector<double>  Events::MuPhiVec_() const{ return *selectedIDIsoMuonsPhiVec;}

   vector<double>  Events::slimmedElecPtVec_() const{ return  *slimmedElectronsPtVec;}
   vector<double>  Events::slimmedElecEtaVec_() const{ return *slimmedElectronsEtaVec;}
   vector<double>  Events::slimmedElecPhiVec_() const{ return *slimmedElectronsPhiVec;}
   vector<double>  Events::ElecNoIsoPtVec_() const{ return  *selectedIDElectronsPtVec;}
   vector<double>  Events::ElecNoIsoEtaVec_() const{ return *selectedIDElectronsEtaVec;}
   vector<double>  Events::ElecNoIsoPhiVec_() const{ return *selectedIDElectronsPhiVec;}
   vector<double>  Events::ElecPtVec_() const{ return *selectedIDIsoElectronsPtVec;}
   vector<double>  Events::ElecEtaVec_() const{ return *selectedIDIsoElectronsEtaVec;}
   vector<double>  Events::ElecPhiVec_() const{return *selectedIDIsoElectronsPhiVec;}

   vector<double>  Events::IsoElecPtVec_() const{ return *IsolatedElectronTracksVetoPtVec;}
   vector<double>  Events::IsoElecEtaVec_() const{ return *IsolatedElectronTracksVetoEtaVec;}
   vector<double>  Events::IsoElecPhiVec_() const{ return *IsolatedElectronTracksVetoPhiVec;}
   vector<double>  Events::IsoMuPtVec_() const{ return *IsolatedMuonTracksVetoPtVec;}
   vector<double>  Events::IsoMuEtaVec_() const{ return *IsolatedMuonTracksVetoEtaVec;}
   vector<double>  Events::IsoMuPhiVec_() const{ return *IsolatedMuonTracksVetoPhiVec;}
   vector<double>  Events::IsoPionPtVec_() const{ return *IsolatedPionTracksVetoPtVec;}
   vector<double>  Events::IsoPionEtaVec_() const{ return *IsolatedPionTracksVetoEtaVec;}
   vector<double>  Events::IsoPionPhiVec_() const{ return *IsolatedPionTracksVetoPhiVec;}

   vector<string>  Events::TriggerNames_() const{ return *TriggerNames;}
   vector<int>     Events::PassTrigger_() const{ return *PassTrigger;}

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


