#include "Events.h"
#include <vector>


  //Constructor
  Events::Events(TTree * ttree_, const std::string sampleKeyString, int verbose) : currentEntry_(-1) {

    // Data or MC ?
    DataBool=false;
    
    // Study Tau ID
    StudyTauId=true;

    //Initialize some varaibles
     RunNum=-1;
     LumiBlockNum=-1;
     EvtNum=-1;
     NVtx=-1;
     isoElectronTracks=-1;
     isoMuonTracks=-1;
     isoPionTracks=-1;
     Leptons=-1;
     NJets=-1;
     BTags=-1;
     Weight=1;
     puWeight=1.;
     HT=0.0;
     genHT=0.0;
     MHT=0.0;
     MHT_Phi=0.0; 
     METPt=0.0;
     METPhi=0.0;
     DeltaPhi1=-99.;
     DeltaPhi2=-99.;
     DeltaPhi3=-99.;
     DeltaPhi4=-99.;

     GenMu_GenMuFromTau=0;
     GenTau_GenTauHad=0;
     GenElec_GenElecFromTau=0;
     slimJet_slimJetID = 0;
     GenMus = 0;
     GenEls = 0;
     GenTauNu = 0;
     GenTaus = 0;

     genParticles = 0;
     genParticles_PDGid = 0;  
     PDFweights =0;
     ScaleWeights = 0;
     Jets = 0;
     Jets_partonFlavor = 0;
     HTJetsMask = 0;
     Jets_bDiscriminatorCSV = 0;
     Jets_chargedEmEnergyFraction = 0;
     Jets_chargedHadronEnergyFraction = 0;
     Jets_chargedHadronMultiplicity = 0;
     Jets_electronMultiplicity = 0;
     Jets_jetArea = 0;
     Jets_muonEnergyFraction = 0;
     Jets_muonMultiplicity = 0;
     Jets_neutralEmEnergyFraction = 0;
     Jets_neutralHadronMultiplicity = 0;
     Jets_photonEnergyFraction = 0;
     Jets_photonMultiplicity = 0;
     selectedIDIsoMuons_MT2Activity = 0;
     GenMu_MT2Activity = 0;

//     slimmedMuonsPtVec=new vector<double>();
     Muons = 0;
//     selectedIDIsoMuonsPtVec=new vector<double>();
     selectedIDMuons = 0;
//     slimmedElectronsPtVec=new vector<double>();
     Electrons = 0;
//     selectedIDIsoElectronsPtVec=new vector<double>();
     selectedIDElectrons = 0;
//     selectedIDIsoElectronsPtVec=new vector<double>();
     slimJetJECdown = 0;
     slimJetJECup = 0;
     slimJet = 0;
     IsolatedElectronTracksVeto = 0;
     IsolatedMuonTracksVeto = 0;
     IsolatedPionTracksVeto = 0;

     TauLorVec = 0;
     TauIdVecagainstElectronLooseMVA5 = 0;
     TauIdVecagainstElectronMediumMVA5 = 0;
     TauIdVecagainstElectronVLooseMVA5 = 0;
     TauIdVecagainstMuonLoose3 = 0;
     TauIdVecagainstMuonTight3 = 0;
     TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits = 0;
     TauIdVecbyLoosePileupWeightedIsolation3Hits = 0;
     TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits = 0;
     TauIdVecbyMediumPileupWeightedIsolation3Hits = 0;
     TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits = 0;
     TauIdVecbyTightPileupWeightedIsolation3Hits = 0;

     TriggerNames=0;
     TriggerPass=0;

     fChain = ttree_;

    /// the variables
     fChain->SetBranchAddress("CrossSection", &CrossSection);
     fChain->SetBranchAddress("RunNum", &RunNum);
     fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum);
     fChain->SetBranchAddress("EvtNum", &EvtNum);
     fChain->SetBranchAddress("NVtx", &NVtx);
     fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks);
     fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks);
     fChain->SetBranchAddress("isoPionTracks", &isoPionTracks);
     fChain->SetBranchAddress("Leptons", &Leptons);
     fChain->SetBranchAddress("NJets", &NJets);
     fChain->SetBranchAddress("BTags", &BTags);
     fChain->SetBranchAddress("Weight", &Weight);
     fChain->SetBranchAddress("puWeight", &puWeight);
     fChain->SetBranchAddress("HT", &HT);
     fChain->SetBranchAddress("MHT", &MHT);
     fChain->SetBranchAddress("MHT_Phi", &MHT_Phi);
     fChain->SetBranchAddress("METPt", &METPt);
     fChain->SetBranchAddress("METPhi", &METPhi); 
     fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1);
     fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2);
     fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3);
     fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4);
     fChain->SetBranchAddress("JetID", &JetID);
     //fChain->SetBranchAddress("JetIDloose", &JetIDloose);
     fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter);
     fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter);
     fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter);
     fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter);
     fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter);
     if(!DataBool){
       fChain->SetBranchAddress("GenMus", &GenMus);
       fChain->SetBranchAddress("GenMu_GenMuFromTau", &GenMu_GenMuFromTau);
       fChain->SetBranchAddress("GenEls", &GenEls);
       fChain->SetBranchAddress("GenElec_GenElecFromTau", &GenElec_GenElecFromTau);
       fChain->SetBranchAddress("GenTaus", &GenTaus);
       fChain->SetBranchAddress("GenTau_GenTauHad", &GenTau_GenTauHad);
       fChain->SetBranchAddress("GenTauNu", &GenTauNu);
       fChain->SetBranchAddress("genHT", &genHT);
       fChain->SetBranchAddress("GenMu_MT2Activity", &GenMu_MT2Activity);

       fChain->SetBranchAddress("genParticles", &genParticles);
       fChain->SetBranchAddress("genParticles_PDGid", &genParticles_PDGid);
     }
     fChain->SetBranchAddress("PDFweights", &PDFweights);
     fChain->SetBranchAddress("ScaleWeights", &ScaleWeights);
     fChain->SetBranchAddress("Jets", &Jets);
     fChain->SetBranchAddress("Jets_partonFlavor", &Jets_partonFlavor);
     fChain->SetBranchAddress("HTJetsMask", &HTJetsMask);

     fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV);
     fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction);
     fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction);
     fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity);
     fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity);
     fChain->SetBranchAddress("Jets_jetArea", &Jets_jetArea);
     fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction);
     fChain->SetBranchAddress("Jets_muonMultiplicity", &Jets_muonMultiplicity);
     fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction);
     fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity);
     fChain->SetBranchAddress("Jets_photonEnergyFraction", &Jets_photonEnergyFraction);
     fChain->SetBranchAddress("Jets_photonMultiplicity", &Jets_photonMultiplicity);


//     fChain->SetBranchAddress("slimmedMuonsPtVec", &slimmedMuonsPtVec);
      fChain->SetBranchAddress("Muons", &Muons);
//     fChain->SetBranchAddress("selectedIDIsoMuonsPtVec", &selectedIDIsoMuonsPtVec);
     fChain->SetBranchAddress("selectedIDMuons", &selectedIDMuons);

//     fChain->SetBranchAddress("slimmedElectronsPtVec", &slimmedElectronsPtVec);
     fChain->SetBranchAddress("Electrons", &Electrons);
//     fChain->SetBranchAddress("selectedIDIsoElectronsPtVec", &selectedIDIsoElectronsPtVec);
     fChain->SetBranchAddress("selectedIDElectrons", &selectedIDElectrons);
     fChain->SetBranchAddress("slimJetJECdown", &slimJetJECdown);  
     fChain->SetBranchAddress("slimJetJECup", &slimJetJECup);
     fChain->SetBranchAddress("slimJet", &slimJet);
     fChain->SetBranchAddress("slimJet_slimJetID", &slimJet_slimJetID);
     fChain->SetBranchAddress("IsolatedElectronTracksVeto", &IsolatedElectronTracksVeto);
     fChain->SetBranchAddress("IsolatedMuonTracksVeto", &IsolatedMuonTracksVeto);
     fChain->SetBranchAddress("IsolatedPionTracksVeto", &IsolatedPionTracksVeto);

     fChain->SetBranchAddress("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity);

     if(StudyTauId){
       fChain->SetBranchAddress("TauLorVec", &TauLorVec);
       fChain->SetBranchAddress("TauIdVecagainstElectronLooseMVA5", &TauIdVecagainstElectronLooseMVA5);
       fChain->SetBranchAddress("TauIdVecagainstElectronMediumMVA5", &TauIdVecagainstElectronMediumMVA5);
       fChain->SetBranchAddress("TauIdVecagainstElectronVLooseMVA5", &TauIdVecagainstElectronVLooseMVA5);
       fChain->SetBranchAddress("TauIdVecagainstMuonLoose3", &TauIdVecagainstMuonLoose3);
       fChain->SetBranchAddress("TauIdVecagainstMuonTight3", &TauIdVecagainstMuonTight3);
       fChain->SetBranchAddress("TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits", &TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits);
       fChain->SetBranchAddress("TauIdVecbyLoosePileupWeightedIsolation3Hits", &TauIdVecbyLoosePileupWeightedIsolation3Hits);
       fChain->SetBranchAddress("TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits", &TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits);
       fChain->SetBranchAddress("TauIdVecbyMediumPileupWeightedIsolation3Hits", &TauIdVecbyMediumPileupWeightedIsolation3Hits);
       fChain->SetBranchAddress("TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits", &TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits);
       fChain->SetBranchAddress("TauIdVecbyTightPileupWeightedIsolation3Hits", &TauIdVecbyTightPileupWeightedIsolation3Hits);
     }
     
     fChain->SetBranchAddress("TriggerNames", &TriggerNames);
     fChain->SetBranchAddress("TriggerPass", &TriggerPass);

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

      if( currentEntry_ > 0 && currentEntry_%10000 == 0 ) {
        std::cout << " Processed " << currentEntry_ << " events" << std::endl;
      }

      fChain->GetEntry(currentEntry_);
      return true;

    }

  }


// Some Functions
  double Events::XS() const { return CrossSection; }

  // Total number of events
  int Events::TotNEve() const { return template_Entries; }   

  // Run number & event number
  int Events::Runnum() const { return RunNum; }
  int Events::Evtnum() const { return EvtNum; }
  int Events::LumiBlocknum() const { return LumiBlockNum; }

  // Event weight (for luminosity and PU profile)
  double Events::weight() const { return Weight; }
  double Events::puweight() const { return puWeight; }

  // HT and MHT
  double Events::ht() const { return HT; }
  double Events::gen_ht() const { return genHT; }
  double Events::mht() const { return MHT; }
  double Events::mhtphi() const { return  MHT_Phi; }

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
    tempN= ( (int)Muons->size() + (int)Electrons->size() );
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
  double Events::deltaPhi4() const { return DeltaPhi4; }

  // To see if an event passes the jetId requirement or not.  
  int Events::JetId() const {
    return JetID;
  }

  bool Events::DataBool_() const { return DataBool; }

  // Gen Muon 
   vector<double>  Events::GenMuPtVec_() const {
     vector<double> vec;
     for(int i=0;i < GenMus->size();i++){
       vec.push_back(GenMus->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::GenMuEtaVec_() const {
     vector<double> vec;
     for(int i=0;i < GenMus->size();i++){
       vec.push_back(GenMus->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::GenMuPhiVec_() const {
     vector<double> vec;
     for(int i=0;i < GenMus->size();i++){
       vec.push_back(GenMus->at(i).Phi());
     }
     return vec;
   }
   vector<double>  Events::GenMuEVec_() const {
     vector<double> vec;
     for(int i=0;i < GenMus->size();i++){
       vec.push_back(GenMus->at(i).E());
     }
     return vec;
   }

   vector<double>  Events::GenElecPtVec_() const { 
     vector<double> vec;
     for(int i=0;i < GenEls->size();i++){
       vec.push_back(GenEls->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::GenElecEtaVec_() const {
     vector<double> vec;
     for(int i=0;i < GenEls->size();i++){
       vec.push_back(GenEls->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::GenElecPhiVec_() const { 
     vector<double> vec;
     for(int i=0;i < GenEls->size();i++){
       vec.push_back(GenEls->at(i).Phi());
     }
     return vec;
   }
  
   vector<TLorentzVector>* Events::GenTauLorVec() const { return GenTaus;} 
   vector<double>  Events::GenTauPtVec_() const {
     vector<double> vec;
     for(int i=0;i < GenTaus->size();i++){
       vec.push_back(GenTaus->at(i).Pt());
     }
     return vec;
   } 
   vector<double>  Events::GenTauEtaVec_() const { 
     vector<double> vec;
     for(int i=0;i < GenTaus->size();i++){
       vec.push_back(GenTaus->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::GenTauPhiVec_() const { 
     vector<double> vec;
     for(int i=0;i < GenTaus->size();i++){
       vec.push_back(GenTaus->at(i).Phi());
     }
     return vec;
   }
   vector<TLorentzVector>*  Events::GenTauNuLorVec() const { return GenTauNu;}
   vector<double>  Events::GenTauNuPtVec_() const { 
     vector<double> vec;
     for(int i=0;i < GenTauNu->size();i++){
       vec.push_back(GenTauNu->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::GenTauNuEtaVec_() const { 
     vector<double> vec;
     for(int i=0;i < GenTauNu->size();i++){
       vec.push_back(GenTauNu->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::GenTauNuPhiVec_() const { 
     vector<double> vec;
     for(int i=0;i < GenTauNu->size();i++){
       vec.push_back(GenTauNu->at(i).Phi());
     }
     return vec;
   }

   vector<TLorentzVector>     *Events::genParticles_() const {return genParticles;}
   vector<int>                *Events::genParticles_PDGid_() const {return genParticles_PDGid;}

   vector<double> * Events::PDFweights_() const {return PDFweights;}
   vector<double> * Events::ScaleWeights_() const {return ScaleWeights;}
   vector<double>  Events::JetsPtVec_() const { 
     vector<double> vec;
     for(int i=0;i < Jets->size();i++){
       vec.push_back(Jets->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::JetsEtaVec_() const { 
     vector<double> vec;
     for(int i=0;i < Jets->size();i++){
       vec.push_back(Jets->at(i).Eta());
     }
     return vec;   
   }
   vector<double>  Events::JetsPhiVec_() const { 
     vector<double> vec;
     for(int i=0;i < Jets->size();i++){
       vec.push_back(Jets->at(i).Phi());
     }
     return vec;
   }
   vector<double>  Events::JetsEVec_() const {
     vector<double> vec;
     for(int i=0;i < Jets->size();i++){
       vec.push_back(Jets->at(i).E());
     }
     return vec;
   }
   vector<TLorentzVector>  *Events::JetsLorVec_() const{return Jets;}
   vector<int> *Events::Jets_partonFlavor_() const { return Jets_partonFlavor;}
   vector<bool> *Events::HTJetsMask_() const { return HTJetsMask;}


   vector<double>  Events::csvVec() const { return *Jets_bDiscriminatorCSV;}
   vector<double>  Events::Jets_chargedEmEnergyFraction_() const { return *Jets_chargedEmEnergyFraction;}
   vector<double>  Events::Jets_chargedHadronEnergyFraction_() const { return *Jets_chargedHadronEnergyFraction;}
   vector<int>  Events::Jets_chargedHadronMultiplicity_() const { return *Jets_chargedHadronMultiplicity;}
   vector<int>  Events::Jets_electronMultiplicity_() const { return *Jets_electronMultiplicity;}

   vector<double>  Events::Jets_jetArea_() const { return *Jets_jetArea;}
   vector<double>  Events::Jets_muonEnergyFraction_() const {return *Jets_muonEnergyFraction;}
   vector<int>  Events::Jets_muonMultiplicity_() const {return *Jets_muonMultiplicity;}
   vector<double>  Events::Jets_neutralEmEnergyFraction_() const {return *Jets_neutralEmEnergyFraction;}
   vector<int>  Events::Jets_neutralHadronMultiplicity_() const {return *Jets_neutralHadronMultiplicity;}
   vector<double>  Events::Jets_photonEnergyFraction_() const {return *Jets_photonEnergyFraction;}
   vector<int>  Events::Jets_photonMultiplicity_() const {return *Jets_photonMultiplicity;}

   vector<TLorentzVector> * Events::slimJetJECdown_() const {return slimJetJECdown;}
   vector<TLorentzVector> * Events::slimJetJECup_() const {return slimJetJECup;}
   vector<double>  Events::slimJetPtVec_() const { 
     vector<double> vec;
     for(int i=0;i < slimJet->size();i++){
       vec.push_back(slimJet->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::slimJetEtaVec_() const { 
     vector<double> vec;
     for(int i=0;i < slimJet->size();i++){
       vec.push_back(slimJet->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::slimJetPhiVec_() const { 
     vector<double> vec;
     for(int i=0;i < slimJet->size();i++){
       vec.push_back(slimJet->at(i).Phi());
     }
     return vec;
   }

   vector<int>     Events::slimJetID_() const { return *slimJet_slimJetID;} 

//   vector<double>  Events::slimmedMuPtVec_() const{ return  *slimmedMuonsPtVec;}
   vector<double>  Events::MuNoIsoPtVec_() const{
     vector<double> vec;
     for(int i=0;i < selectedIDMuons->size();i++){
       vec.push_back(selectedIDMuons->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::MuNoIsoEtaVec_() const{ 
     vector<double> vec;
     for(int i=0;i < selectedIDMuons->size();i++){
       vec.push_back(selectedIDMuons->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::MuNoIsoPhiVec_() const{ 
     vector<double> vec;
     for(int i=0;i < selectedIDMuons->size();i++){
       vec.push_back(selectedIDMuons->at(i).Phi());
     }
     return vec;
   }

   vector<double>  Events::MuPtVec_() const{ 
     vector<double> vec;
     for(int i=0;i < Muons->size();i++){
       vec.push_back(Muons->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::MuEtaVec_() const{ 
     vector<double> vec;
     for(int i=0;i < Muons->size();i++){
       vec.push_back(Muons->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::MuPhiVec_() const{ 
     vector<double> vec;
     for(int i=0;i < Muons->size();i++){
       vec.push_back(Muons->at(i).Phi());
     }
     return vec;
   }
   vector<double>  Events::MuEVec_() const{
     vector<double> vec;
     for(int i=0;i < Muons->size();i++){
       vec.push_back(Muons->at(i).E());
     }
     return vec;
   }


//   vector<double>  Events::slimmedElecPtVec_() const{ return  *slimmedElectronsPtVec;}


   vector<double>  Events::ElecNoIsoPtVec_() const{ 
     vector<double> vec;
     for(int i=0;i < selectedIDElectrons->size();i++){
       vec.push_back(selectedIDElectrons->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::ElecNoIsoEtaVec_() const{ 
     vector<double> vec;
     for(int i=0;i < selectedIDElectrons->size();i++){
       vec.push_back(selectedIDElectrons->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::ElecNoIsoPhiVec_() const{ 
     vector<double> vec;
     for(int i=0;i < selectedIDElectrons->size();i++){
       vec.push_back(selectedIDElectrons->at(i).Phi());
     }
     return vec;
   }

   vector<double>  Events::ElecPtVec_() const{ 
     vector<double> vec;
     for(int i=0;i < Electrons->size();i++){
       vec.push_back(Electrons->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::ElecEtaVec_() const{ 
     vector<double> vec;
     for(int i=0;i < Electrons->size();i++){
       vec.push_back(Electrons->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::ElecPhiVec_() const{ 
     vector<double> vec;
     for(int i=0;i < Electrons->size();i++){
       vec.push_back(Electrons->at(i).Phi());
     }
     return vec;
   }

   vector<double>  Events::IsoElecPtVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedElectronTracksVeto->size();i++){
       vec.push_back(IsolatedElectronTracksVeto->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::IsoElecEtaVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedElectronTracksVeto->size();i++){
       vec.push_back(IsolatedElectronTracksVeto->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::IsoElecPhiVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedElectronTracksVeto->size();i++){
       vec.push_back(IsolatedElectronTracksVeto->at(i).Phi());
     }
     return vec;
   }

   vector<double>  Events::IsoMuPtVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedMuonTracksVeto->size();i++){
       vec.push_back(IsolatedMuonTracksVeto->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::IsoMuEtaVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedMuonTracksVeto->size();i++){
       vec.push_back(IsolatedMuonTracksVeto->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::IsoMuPhiVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedMuonTracksVeto->size();i++){
       vec.push_back(IsolatedMuonTracksVeto->at(i).Phi());
     }
     return vec;
   }

   vector<double>  Events::IsoPionPtVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedPionTracksVeto->size();i++){
       vec.push_back(IsolatedPionTracksVeto->at(i).Pt());
     }
     return vec;
   }
   vector<double>  Events::IsoPionEtaVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedPionTracksVeto->size();i++){
       vec.push_back(IsolatedPionTracksVeto->at(i).Eta());
     }
     return vec;
   }
   vector<double>  Events::IsoPionPhiVec_() const{ 
     vector<double> vec;
     for(int i=0;i < IsolatedPionTracksVeto->size();i++){
       vec.push_back(IsolatedPionTracksVeto->at(i).Phi());
     }
     return vec;
   }

   vector<double>  Events::MTActivityVec_() const{ return *selectedIDIsoMuons_MT2Activity; }
   vector<double>  Events::GenMTActivityVec_() const{ return *GenMu_MT2Activity; }

   vector<TLorentzVector>* Events::TauLorVec_() const { return TauLorVec;}
   vector<double>* Events::tauId1() const { return TauIdVecagainstElectronLooseMVA5;}
   vector<double>* Events::tauId2() const { return TauIdVecagainstElectronMediumMVA5;}
   vector<double>* Events::tauId3() const { return TauIdVecagainstElectronVLooseMVA5;}
   vector<double>* Events::tauId4() const { return TauIdVecagainstMuonLoose3;}
   vector<double>* Events::tauId5() const { return TauIdVecagainstMuonTight3;}
   vector<double>* Events::tauId6() const { return TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits;}
   vector<double>* Events::tauId7() const { return TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits;}
   vector<double>* Events::tauId8() const { return TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits;}
   vector<double>* Events::tauId9() const { return TauIdVecbyLoosePileupWeightedIsolation3Hits;}
   vector<double>* Events::tauId10() const { return TauIdVecbyMediumPileupWeightedIsolation3Hits;}
   vector<double>* Events::tauId11() const { return TauIdVecbyTightPileupWeightedIsolation3Hits;}

   map<int,int> Events::nTauMap() const{
     map<int,int> map_;
     for(int i=0; i< TauLorVec->size();i++){
       if(TauIdVecagainstElectronLooseMVA5->at(i)==1&&
          TauIdVecagainstMuonLoose3->at(i)==1&&
          TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits->at(i)==1&&
          TauIdVecbyMediumPileupWeightedIsolation3Hits->at(i)==1)map_[2233]++;

       if(TauIdVecagainstElectronLooseMVA5->at(i)==1&&
          TauIdVecagainstMuonLoose3->at(i)==1&&
          TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits->at(i)==1&&
          TauIdVecbyMediumPileupWeightedIsolation3Hits->at(i)==1)map_[2243]++;

       if(TauIdVecagainstElectronLooseMVA5->at(i)==1&&
          TauIdVecagainstMuonTight3->at(i)==1&&
          TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits->at(i)==1&&
          TauIdVecbyMediumPileupWeightedIsolation3Hits->at(i)==1)map_[2333]++;

       if(TauIdVecagainstElectronVLooseMVA5->at(i)==1&&
          TauIdVecagainstMuonTight3->at(i)==1&&
          TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits->at(i)==1&&
          TauIdVecbyMediumPileupWeightedIsolation3Hits->at(i)==1)map_[4333]++;

       if(TauIdVecagainstMuonTight3->at(i)==1&&
          TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits->at(i)==1&&
          TauIdVecbyMediumPileupWeightedIsolation3Hits->at(i)==1)map_[1333]++;
     }
     return map_;
   }

   vector<string>  Events::TriggerNames_() const{ return *TriggerNames;}
   vector<int>     Events::PassTrigger_() const{ return *TriggerPass;}

   vector<int>     Events::GenMuFromTauVec_() const { return *GenMu_GenMuFromTau;}

   vector<int>     Events::GenElecFromTauVec_() const { return *GenElec_GenElecFromTau;}

  vector<int>     Events::GenTauHadVec_() const { return *GenTau_GenTauHad;}

  double Events::csv_() const {return 0.890;} 

//  int Events::GoodVtx_() const {return GoodVtx;}
  int Events::CSCTightHaloFilter_() const {return CSCTightHaloFilter;}
  int Events::eeBadScFilter_() const {return eeBadScFilter;}
  int Events::HBHENoiseFilter_() const {return HBHENoiseFilter;}
  int Events::HBHEIsoNoiseFilter_() const {return HBHEIsoNoiseFilter;}
  int Events::EcalDeadCellTriggerPrimitiveFilter_() const {return EcalDeadCellTriggerPrimitiveFilter;}
  int Events::NVtx_() const {return NVtx;}

  
//  std::vector<double> Events::Pt_GenMu() const { 
//    std::vector<double> tempV;
//    tempV.assign(&GenMuPt[0],&GenMuPt[0]+2);
//std::vector<double> tempV(GenMuPt,GenMuPt+sizeof(GenMuPt)/sizeof(double));
//    return tempV;
//  }

//  double Events::Eta_GenMu() const { return GenMuEta;}
//  double Events::Phi_GenMu() const { return GenMuPhi;}

