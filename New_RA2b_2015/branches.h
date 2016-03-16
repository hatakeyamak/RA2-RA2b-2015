//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan  6 12:32:16 2016 by ROOT version 5.34/22
// from TTree PreSelection/PreSelection
// found on file: run_RA2AnalysisTree.root
//////////////////////////////////////////////////////////

#ifndef branches_h
#define branches_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class branches {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   ULong64_t       EvtNum;
   vector<TLorentzVector> *bestPhoton;
   Int_t           BTags;
   Int_t           BTagsJECdown;
   Int_t           BTagsJECup;
   Double_t        CaloMETPhi;
   Double_t        CaloMETPt;
   Double_t        CrossSection;
   Bool_t          CSCTightHaloFilter;
   Double_t        DeltaPhi1;
   Double_t        DeltaPhi1JECdown;
   Double_t        DeltaPhi1JECup;
   Double_t        DeltaPhi2;
   Double_t        DeltaPhi2JECdown;
   Double_t        DeltaPhi2JECup;
   Double_t        DeltaPhi3;
   Double_t        DeltaPhi3JECdown;
   Double_t        DeltaPhi3JECup;
   Double_t        DeltaPhi4;
   Double_t        DeltaPhi4JECdown;
   Double_t        DeltaPhi4JECup;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          eeBadSc4Filter;
   Int_t           eeBadScFilter;
   vector<int>     *ElectronCharge;
   vector<TLorentzVector> *Electrons;
   vector<int>     *GenElec_GenElecFromTau;
   vector<double>  *GenElec_MT2Activity;
   vector<double>  *GenElec_RecoTrkAct;
   vector<double>  *GenElec_RecoTrkd3;
   vector<double>  *GenElec_RecoTrkIso;
   vector<TLorentzVector> *GenEls;
   Double_t        genHT;
   Double_t        GenMETPhi;
   Double_t        GenMETPt;
   vector<int>     *GenMu_GenMuFromTau;
   vector<double>  *GenMu_MT2Activity;
   vector<double>  *GenMu_RecoTrkAct;
   vector<double>  *GenMu_RecoTrkd3;
   vector<double>  *GenMu_RecoTrkIso;
   vector<TLorentzVector> *GenMus;
   vector<TLorentzVector> *genParticles;
   vector<int>     *genParticles_PDGid;
   vector<int>     *GenTau_GenTauHad;
   vector<double>  *GenTau_MT2Activity;
   vector<double>  *GenTauLeadRecoTrkAct;
   vector<double>  *GenTauLeadRecoTrkd3;
   vector<double>  *GenTauLeadRecoTrkIso;
   vector<TLorentzVector> *GenTauLeadTrk;
   vector<TLorentzVector> *GenTauNu;
   vector<TLorentzVector> *GenTaus;
   Bool_t          HBHEIsoNoiseFilter;
   Bool_t          HBHENoiseFilter;
   Double_t        HT;
   Double_t        HTJECdown;
   Double_t        HTJECup;
   vector<bool>    *HTJetsMask;
   vector<bool>    *HTJetsMaskJECdown;
   vector<bool>    *HTJetsMaskJECup;
   Int_t           isoElectronTracks;
   vector<TLorentzVector> *IsolatedElectronTracksVeto;
   vector<TLorentzVector> *IsolatedMuonTracksVeto;
   vector<TLorentzVector> *IsolatedPionTracksVeto;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Bool_t          JetID;
   Bool_t          JetIDJECdown;
   Bool_t          JetIDJECup;
   vector<TLorentzVector> *Jets;
   vector<double>  *Jets_bDiscriminatorCSV;
   vector<double>  *Jets_bDiscriminatorMVA;
   vector<double>  *Jets_chargedEmEnergyFraction;
   vector<double>  *Jets_chargedHadronEnergyFraction;
   vector<int>     *Jets_chargedHadronMultiplicity;
   vector<int>     *Jets_chargedMultiplicity;
   vector<int>     *Jets_electronMultiplicity;
   vector<int>     *Jets_hadronFlavor;
   vector<double>  *Jets_jecFactor;
   vector<double>  *Jets_jecUnc;
   vector<double>  *Jets_jetArea;
   vector<double>  *Jets_muonEnergyFraction;
   vector<int>     *Jets_muonMultiplicity;
   vector<double>  *Jets_neutralEmEnergyFraction;
   vector<double>  *Jets_neutralHadronEnergyFraction;
   vector<int>     *Jets_neutralHadronMultiplicity;
   vector<int>     *Jets_neutralMultiplicity;
   vector<int>     *Jets_partonFlavor;
   vector<double>  *Jets_photonEnergyFraction;
   vector<int>     *Jets_photonMultiplicity;
   vector<TLorentzVector> *JetsJECdown;
   vector<double>  *JetsJECdown_bDiscriminatorCSV;
   vector<int>     *JetsJECdown_hadronFlavor;
   vector<int>     *JetsJECdown_partonFlavor;
   vector<TLorentzVector> *JetsJECup;
   vector<double>  *JetsJECup_bDiscriminatorCSV;
   vector<int>     *JetsJECup_hadronFlavor;
   vector<int>     *JetsJECup_partonFlavor;
   Int_t           Leptons;
   Int_t           METFilters;
   Double_t        METPhi;
   vector<double>  *METPhiDown;
   vector<double>  *METPhiUp;
   Double_t        METPt;
   vector<double>  *METPtDown;
   vector<double>  *METPtUp;
   Double_t        MHT;
   Double_t        MHT_Phi;
   Double_t        MHT_PhiJECdown;
   Double_t        MHT_PhiJECup;
   Double_t        MHTJECdown;
   Double_t        MHTJECup;
   vector<bool>    *MHTJetsMask;
   vector<bool>    *MHTJetsMaskJECdown;
   vector<bool>    *MHTJetsMaskJECup;
   vector<int>     *MuonCharge;
   vector<TLorentzVector> *Muons;
   Int_t           nAllVertices;
   Int_t           NJets;
   Int_t           NJetsJECdown;
   Int_t           NJetsJECup;
   Int_t           nTAPElectronTracks;
   Int_t           nTAPMuonTracks;
   Int_t           nTAPPionTracks;
   Double_t        NumEvents;
   Int_t           NumInteractions;
   Int_t           NumPhotons;
   Int_t           NVtx;
   vector<int>     *PDFids;
   vector<double>  *PDFweights;
   Double_t        puSysDown;
   Double_t        puSysUp;
   Double_t        puWeight;
   vector<double>  *ScaleWeights;
   vector<TLorentzVector> *selectedIDElectrons;
   vector<bool>    *selectedIDElectrons_mediumID;
   vector<double>  *selectedIDElectrons_MiniIso;
   vector<double>  *selectedIDElectrons_MT2Activity;
   vector<double>  *selectedIDElectrons_MTW;
   vector<bool>    *selectedIDIsoElectrons_mediumID;
   vector<double>  *selectedIDIsoElectrons_MT2Activity;
   vector<double>  *selectedIDIsoElectrons_MTW;
   vector<double>  *selectedIDIsoElectrons_PTW;
   vector<double>  *selectedIDIsoMuons_MT2Activity;
   vector<double>  *selectedIDIsoMuons_MTW;
   vector<double>  *selectedIDIsoMuons_PTW;
   vector<TLorentzVector> *selectedIDMuons;
   vector<double>  *selectedIDMuons_MiniIso;
   vector<double>  *selectedIDMuons_MT2Activity;
   vector<double>  *selectedIDMuons_MTW;
   vector<TLorentzVector> *slimJet;
   vector<double>  *slimJet_jecFactor;
   vector<double>  *slimJet_jecUnc;
   vector<bool>    *slimJet_slimJetID;
   vector<TLorentzVector> *slimJetJECdown;
   vector<bool>    *slimJetJECdown_slimJetID;
   vector<TLorentzVector> *slimJetJECup;
   vector<bool>    *slimJetJECup_slimJetID;
   Double_t        SusyLSPMass;
   Double_t        SusyMotherMass;
   Int_t           TagLeptonHighPT;
   vector<TLorentzVector> *TAPElectronTracks;
   vector<double>  *TAPElectronTracks_activity;
   vector<int>     *TAPElectronTracks_chg;
   vector<double>  *TAPElectronTracks_mT;
   vector<double>  *TAPElectronTracks_trkiso;
   vector<TLorentzVector> *TAPMuonTracks;
   vector<double>  *TAPMuonTracks_activity;
   vector<int>     *TAPMuonTracks_chg;
   vector<double>  *TAPMuonTracks_mT;
   vector<double>  *TAPMuonTracks_trkiso;
   vector<TLorentzVector> *TAPPionTracks;
   vector<double>  *TAPPionTracks_activity;
   vector<int>     *TAPPionTracks_chg;
   vector<double>  *TAPPionTracks_mT;
   vector<double>  *TAPPionTracks_trkiso;
   vector<TLorentzVector> *TauDecayCands;
   vector<int>     *TauDecayCands_momInd;
   vector<int>     *TauDecayCands_pdgID;
   vector<double>  *TauIdVecagainstElectronLooseMVA5;
   vector<double>  *TauIdVecagainstElectronMediumMVA5;
   vector<double>  *TauIdVecagainstElectronVLooseMVA5;
   vector<double>  *TauIdVecagainstMuonLoose3;
   vector<double>  *TauIdVecagainstMuonTight3;
   vector<double>  *TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits;
   vector<double>  *TauIdVecbyLoosePileupWeightedIsolation3Hits;
   vector<double>  *TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits;
   vector<double>  *TauIdVecbyMediumPileupWeightedIsolation3Hits;
   vector<double>  *TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits;
   vector<double>  *TauIdVecbyTightPileupWeightedIsolation3Hits;
   vector<TLorentzVector> *TauLorVec;
   vector<string>  *TriggerNames;
   vector<int>     *TriggerPass;
   vector<int>     *TriggerPrescales;
   Double_t        TrueNumInteractions;
   Double_t        Weight;

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_bestPhoton;   //!
   TBranch        *b_BTags;   //!
   TBranch        *b_BTagsJECdown;   //!
   TBranch        *b_BTagsJECup;   //!
   TBranch        *b_CaloMETPhi;   //!
   TBranch        *b_CaloMETPt;   //!
   TBranch        *b_CrossSection;   //!
   TBranch        *b_CSCTightHaloFilter;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi1JECdown;   //!
   TBranch        *b_DeltaPhi1JECup;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi2JECdown;   //!
   TBranch        *b_DeltaPhi2JECup;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_DeltaPhi3JECdown;   //!
   TBranch        *b_DeltaPhi3JECup;   //!
   TBranch        *b_DeltaPhi4;   //!
   TBranch        *b_DeltaPhi4JECdown;   //!
   TBranch        *b_DeltaPhi4JECup;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_eeBadSc4Filter;   //!
   TBranch        *b_eeBadScFilter;   //!
   TBranch        *b_ElectronCharge;   //!
   TBranch        *b_Electrons;   //!
   TBranch        *b_GenElec_GenElecFromTau;   //!
   TBranch        *b_GenElec_MT2Activity;   //!
   TBranch        *b_GenElec_RecoTrkAct;   //!
   TBranch        *b_GenElec_RecoTrkd3;   //!
   TBranch        *b_GenElec_RecoTrkIso;   //!
   TBranch        *b_GenEls;   //!
   TBranch        *b_genHT;   //!
   TBranch        *b_GenMETPhi;   //!
   TBranch        *b_GenMETPt;   //!
   TBranch        *b_GenMu_GenMuFromTau;   //!
   TBranch        *b_GenMu_MT2Activity;   //!
   TBranch        *b_GenMu_RecoTrkAct;   //!
   TBranch        *b_GenMu_RecoTrkd3;   //!
   TBranch        *b_GenMu_RecoTrkIso;   //!
   TBranch        *b_GenMus;   //!
   TBranch        *b_genParticles;   //!
   TBranch        *b_genParticles_PDGid;   //!
   TBranch        *b_GenTau_GenTauHad;   //!
   TBranch        *b_GenTau_MT2Activity;   //!
   TBranch        *b_GenTauLeadRecoTrkAct;   //!
   TBranch        *b_GenTauLeadRecoTrkd3;   //!
   TBranch        *b_GenTauLeadRecoTrkIso;   //!
   TBranch        *b_GenTauLeadTrk;   //!
   TBranch        *b_GenTauNu;   //!
   TBranch        *b_GenTaus;   //!
   TBranch        *b_HBHEIsoNoiseFilter;   //!
   TBranch        *b_HBHENoiseFilter;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_HTJECdown;   //!
   TBranch        *b_HTJECup;   //!
   TBranch        *b_HTJetsMask;   //!
   TBranch        *b_HTJetsMaskJECdown;   //!
   TBranch        *b_HTJetsMaskJECup;   //!
   TBranch        *b_isoElectronTracks;   //!
   TBranch        *b_IsolatedElectronTracksVeto;   //!
   TBranch        *b_IsolatedMuonTracksVeto;   //!
   TBranch        *b_IsolatedPionTracksVeto;   //!
   TBranch        *b_isoMuonTracks;   //!
   TBranch        *b_isoPionTracks;   //!
   TBranch        *b_JetID;   //!
   TBranch        *b_JetIDJECdown;   //!
   TBranch        *b_JetIDJECup;   //!
   TBranch        *b_Jets;   //!
   TBranch        *b_Jets_bDiscriminatorCSV;   //!
   TBranch        *b_Jets_bDiscriminatorMVA;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity;   //!
   TBranch        *b_Jets_chargedMultiplicity;   //!
   TBranch        *b_Jets_electronMultiplicity;   //!
   TBranch        *b_Jets_hadronFlavor;   //!
   TBranch        *b_Jets_jecFactor;   //!
   TBranch        *b_Jets_jecUnc;   //!
   TBranch        *b_Jets_jetArea;   //!
   TBranch        *b_Jets_muonEnergyFraction;   //!
   TBranch        *b_Jets_muonMultiplicity;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity;   //!
   TBranch        *b_Jets_neutralMultiplicity;   //!
   TBranch        *b_Jets_partonFlavor;   //!
   TBranch        *b_Jets_photonEnergyFraction;   //!
   TBranch        *b_Jets_photonMultiplicity;   //!
   TBranch        *b_JetsJECdown;   //!
   TBranch        *b_JetsJECdown_bDiscriminatorCSV;   //!
   TBranch        *b_JetsJECdown_hadronFlavor;   //!
   TBranch        *b_JetsJECdown_partonFlavor;   //!
   TBranch        *b_JetsJECup;   //!
   TBranch        *b_JetsJECup_bDiscriminatorCSV;   //!
   TBranch        *b_JetsJECup_hadronFlavor;   //!
   TBranch        *b_JetsJECup_partonFlavor;   //!
   TBranch        *b_Leptons;   //!
   TBranch        *b_METFilters;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_METPhiDown;   //!
   TBranch        *b_METPhiUp;   //!
   TBranch        *b_METPt;   //!
   TBranch        *b_METPtDown;   //!
   TBranch        *b_METPtUp;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_MHT_Phi;   //!
   TBranch        *b_MHT_PhiJECdown;   //!
   TBranch        *b_MHT_PhiJECup;   //!
   TBranch        *b_MHTJECdown;   //!
   TBranch        *b_MHTJECup;   //!
   TBranch        *b_MHTJetsMask;   //!
   TBranch        *b_MHTJetsMaskJECdown;   //!
   TBranch        *b_MHTJetsMaskJECup;   //!
   TBranch        *b_MuonCharge;   //!
   TBranch        *b_Muons;   //!
   TBranch        *b_nAllVertices;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_NJetsJECdown;   //!
   TBranch        *b_NJetsJECup;   //!
   TBranch        *b_nTAPElectronTracks;   //!
   TBranch        *b_nTAPMuonTracks;   //!
   TBranch        *b_nTAPPionTracks;   //!
   TBranch        *b_NumEvents;   //!
   TBranch        *b_NumInteractions;   //!
   TBranch        *b_NumPhotons;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_PDFids;   //!
   TBranch        *b_PDFweights;   //!
   TBranch        *b_puSysDown;   //!
   TBranch        *b_puSysUp;   //!
   TBranch        *b_puWeight;   //!
   TBranch        *b_ScaleWeights;   //!
   TBranch        *b_selectedIDElectrons;   //!
   TBranch        *b_selectedIDElectrons_mediumID;   //!
   TBranch        *b_selectedIDElectrons_MiniIso;   //!
   TBranch        *b_selectedIDElectrons_MT2Activity;   //!
   TBranch        *b_selectedIDElectrons_MTW;   //!
   TBranch        *b_selectedIDIsoElectrons_mediumID;   //!
   TBranch        *b_selectedIDIsoElectrons_MT2Activity;   //!
   TBranch        *b_selectedIDIsoElectrons_MTW;   //!
   TBranch        *b_selectedIDIsoElectrons_PTW;   //!
   TBranch        *b_selectedIDIsoMuons_MT2Activity;   //!
   TBranch        *b_selectedIDIsoMuons_MTW;   //!
   TBranch        *b_selectedIDIsoMuons_PTW;   //!
   TBranch        *b_selectedIDMuons;   //!
   TBranch        *b_selectedIDMuons_MiniIso;   //!
   TBranch        *b_selectedIDMuons_MT2Activity;   //!
   TBranch        *b_selectedIDMuons_MTW;   //!
   TBranch        *b_slimJet;   //!
   TBranch        *b_slimJet_jecFactor;   //!
   TBranch        *b_slimJet_jecUnc;   //!
   TBranch        *b_slimJet_slimJetID;   //!
   TBranch        *b_slimJetJECdown;   //!
   TBranch        *b_slimJetJECdown_slimJetID;   //!
   TBranch        *b_slimJetJECup;   //!
   TBranch        *b_slimJetJECup_slimJetID;   //!
   TBranch        *b_SusyLSPMass;   //!
   TBranch        *b_SusyMotherMass;   //!
   TBranch        *b_TagLeptonHighPT;   //!
   TBranch        *b_TAPElectronTracks;   //!
   TBranch        *b_TAPElectronTracks_activity;   //!
   TBranch        *b_TAPElectronTracks_chg;   //!
   TBranch        *b_TAPElectronTracks_mT;   //!
   TBranch        *b_TAPElectronTracks_trkiso;   //!
   TBranch        *b_TAPMuonTracks;   //!
   TBranch        *b_TAPMuonTracks_activity;   //!
   TBranch        *b_TAPMuonTracks_chg;   //!
   TBranch        *b_TAPMuonTracks_mT;   //!
   TBranch        *b_TAPMuonTracks_trkiso;   //!
   TBranch        *b_TAPPionTracks;   //!
   TBranch        *b_TAPPionTracks_activity;   //!
   TBranch        *b_TAPPionTracks_chg;   //!
   TBranch        *b_TAPPionTracks_mT;   //!
   TBranch        *b_TAPPionTracks_trkiso;   //!
   TBranch        *b_TauDecayCands;   //!
   TBranch        *b_TauDecayCands_momInd;   //!
   TBranch        *b_TauDecayCands_pdgID;   //!
   TBranch        *b_TauIdVecagainstElectronLooseMVA5;   //!
   TBranch        *b_TauIdVecagainstElectronMediumMVA5;   //!
   TBranch        *b_TauIdVecagainstElectronVLooseMVA5;   //!
   TBranch        *b_TauIdVecagainstMuonLoose3;   //!
   TBranch        *b_TauIdVecagainstMuonTight3;   //!
   TBranch        *b_TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_TauIdVecbyLoosePileupWeightedIsolation3Hits;   //!
   TBranch        *b_TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_TauIdVecbyMediumPileupWeightedIsolation3Hits;   //!
   TBranch        *b_TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_TauIdVecbyTightPileupWeightedIsolation3Hits;   //!
   TBranch        *b_TauLorVec;   //!
   TBranch        *b_TriggerNames;   //!
   TBranch        *b_TriggerPass;   //!
   TBranch        *b_TriggerPrescales;   //!
   TBranch        *b_TrueNumInteractions;   //!
   TBranch        *b_Weight;   //!

   branches(TTree *tree=0);
   virtual ~branches();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef branches_cxx
branches::branches(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run_RA2AnalysisTree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("run_RA2AnalysisTree.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("run_RA2AnalysisTree.root:/TreeMaker2");
      dir->GetObject("PreSelection",tree);

   }
   Init(tree);
}

branches::~branches()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t branches::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t branches::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void branches::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   bestPhoton = 0;
   ElectronCharge = 0;
   Electrons = 0;
   GenElec_GenElecFromTau = 0;
   GenElec_MT2Activity = 0;
   GenElec_RecoTrkAct = 0;
   GenElec_RecoTrkd3 = 0;
   GenElec_RecoTrkIso = 0;
   GenEls = 0;
   GenMu_GenMuFromTau = 0;
   GenMu_MT2Activity = 0;
   GenMu_RecoTrkAct = 0;
   GenMu_RecoTrkd3 = 0;
   GenMu_RecoTrkIso = 0;
   GenMus = 0;
   genParticles = 0;
   genParticles_PDGid = 0;
   GenTau_GenTauHad = 0;
   GenTau_MT2Activity = 0;
   GenTauLeadRecoTrkAct = 0;
   GenTauLeadRecoTrkd3 = 0;
   GenTauLeadRecoTrkIso = 0;
   GenTauLeadTrk = 0;
   GenTauNu = 0;
   GenTaus = 0;
   HTJetsMask = 0;
   HTJetsMaskJECdown = 0;
   HTJetsMaskJECup = 0;
   IsolatedElectronTracksVeto = 0;
   IsolatedMuonTracksVeto = 0;
   IsolatedPionTracksVeto = 0;
   Jets = 0;
   Jets_bDiscriminatorCSV = 0;
   Jets_bDiscriminatorMVA = 0;
   Jets_chargedEmEnergyFraction = 0;
   Jets_chargedHadronEnergyFraction = 0;
   Jets_chargedHadronMultiplicity = 0;
   Jets_chargedMultiplicity = 0;
   Jets_electronMultiplicity = 0;
   Jets_hadronFlavor = 0;
   Jets_jecFactor = 0;
   Jets_jecUnc = 0;
   Jets_jetArea = 0;
   Jets_muonEnergyFraction = 0;
   Jets_muonMultiplicity = 0;
   Jets_neutralEmEnergyFraction = 0;
   Jets_neutralHadronEnergyFraction = 0;
   Jets_neutralHadronMultiplicity = 0;
   Jets_neutralMultiplicity = 0;
   Jets_partonFlavor = 0;
   Jets_photonEnergyFraction = 0;
   Jets_photonMultiplicity = 0;
   JetsJECdown = 0;
   JetsJECdown_bDiscriminatorCSV = 0;
   JetsJECdown_hadronFlavor = 0;
   JetsJECdown_partonFlavor = 0;
   JetsJECup = 0;
   JetsJECup_bDiscriminatorCSV = 0;
   JetsJECup_hadronFlavor = 0;
   JetsJECup_partonFlavor = 0;
   METPhiDown = 0;
   METPhiUp = 0;
   METPtDown = 0;
   METPtUp = 0;
   MHTJetsMask = 0;
   MHTJetsMaskJECdown = 0;
   MHTJetsMaskJECup = 0;
   MuonCharge = 0;
   Muons = 0;
   PDFids = 0;
   PDFweights = 0;
   ScaleWeights = 0;
   selectedIDElectrons = 0;
   selectedIDElectrons_mediumID = 0;
   selectedIDElectrons_MiniIso = 0;
   selectedIDElectrons_MT2Activity = 0;
   selectedIDElectrons_MTW = 0;
   selectedIDIsoElectrons_mediumID = 0;
   selectedIDIsoElectrons_MT2Activity = 0;
   selectedIDIsoElectrons_MTW = 0;
   selectedIDIsoElectrons_PTW = 0;
   selectedIDIsoMuons_MT2Activity = 0;
   selectedIDIsoMuons_MTW = 0;
   selectedIDIsoMuons_PTW = 0;
   selectedIDMuons = 0;
   selectedIDMuons_MiniIso = 0;
   selectedIDMuons_MT2Activity = 0;
   selectedIDMuons_MTW = 0;
   slimJet = 0;
   slimJet_jecFactor = 0;
   slimJet_jecUnc = 0;
   slimJet_slimJetID = 0;
   slimJetJECdown = 0;
   slimJetJECdown_slimJetID = 0;
   slimJetJECup = 0;
   slimJetJECup_slimJetID = 0;
   TAPElectronTracks = 0;
   TAPElectronTracks_activity = 0;
   TAPElectronTracks_chg = 0;
   TAPElectronTracks_mT = 0;
   TAPElectronTracks_trkiso = 0;
   TAPMuonTracks = 0;
   TAPMuonTracks_activity = 0;
   TAPMuonTracks_chg = 0;
   TAPMuonTracks_mT = 0;
   TAPMuonTracks_trkiso = 0;
   TAPPionTracks = 0;
   TAPPionTracks_activity = 0;
   TAPPionTracks_chg = 0;
   TAPPionTracks_mT = 0;
   TAPPionTracks_trkiso = 0;
   TauDecayCands = 0;
   TauDecayCands_momInd = 0;
   TauDecayCands_pdgID = 0;
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
   TauLorVec = 0;
   TriggerNames = 0;
   TriggerPass = 0;
   TriggerPrescales = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("bestPhoton", &bestPhoton, &b_bestPhoton);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("BTagsJECdown", &BTagsJECdown, &b_BTagsJECdown);
   fChain->SetBranchAddress("BTagsJECup", &BTagsJECup, &b_BTagsJECup);
   fChain->SetBranchAddress("CaloMETPhi", &CaloMETPhi, &b_CaloMETPhi);
   fChain->SetBranchAddress("CaloMETPt", &CaloMETPt, &b_CaloMETPt);
   fChain->SetBranchAddress("CrossSection", &CrossSection, &b_CrossSection);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi1JECdown", &DeltaPhi1JECdown, &b_DeltaPhi1JECdown);
   fChain->SetBranchAddress("DeltaPhi1JECup", &DeltaPhi1JECup, &b_DeltaPhi1JECup);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi2JECdown", &DeltaPhi2JECdown, &b_DeltaPhi2JECdown);
   fChain->SetBranchAddress("DeltaPhi2JECup", &DeltaPhi2JECup, &b_DeltaPhi2JECup);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("DeltaPhi3JECdown", &DeltaPhi3JECdown, &b_DeltaPhi3JECdown);
   fChain->SetBranchAddress("DeltaPhi3JECup", &DeltaPhi3JECup, &b_DeltaPhi3JECup);
   fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
   fChain->SetBranchAddress("DeltaPhi4JECdown", &DeltaPhi4JECdown, &b_DeltaPhi4JECdown);
   fChain->SetBranchAddress("DeltaPhi4JECup", &DeltaPhi4JECup, &b_DeltaPhi4JECup);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("eeBadSc4Filter", &eeBadSc4Filter, &b_eeBadSc4Filter);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("ElectronCharge", &ElectronCharge, &b_ElectronCharge);
   fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
   fChain->SetBranchAddress("GenElec_GenElecFromTau", &GenElec_GenElecFromTau, &b_GenElec_GenElecFromTau);
   fChain->SetBranchAddress("GenElec_MT2Activity", &GenElec_MT2Activity, &b_GenElec_MT2Activity);
   fChain->SetBranchAddress("GenElec_RecoTrkAct", &GenElec_RecoTrkAct, &b_GenElec_RecoTrkAct);
   fChain->SetBranchAddress("GenElec_RecoTrkd3", &GenElec_RecoTrkd3, &b_GenElec_RecoTrkd3);
   fChain->SetBranchAddress("GenElec_RecoTrkIso", &GenElec_RecoTrkIso, &b_GenElec_RecoTrkIso);
   fChain->SetBranchAddress("GenEls", &GenEls, &b_GenEls);
   fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
   fChain->SetBranchAddress("GenMETPhi", &GenMETPhi, &b_GenMETPhi);
   fChain->SetBranchAddress("GenMETPt", &GenMETPt, &b_GenMETPt);
   fChain->SetBranchAddress("GenMu_GenMuFromTau", &GenMu_GenMuFromTau, &b_GenMu_GenMuFromTau);
   fChain->SetBranchAddress("GenMu_MT2Activity", &GenMu_MT2Activity, &b_GenMu_MT2Activity);
   fChain->SetBranchAddress("GenMu_RecoTrkAct", &GenMu_RecoTrkAct, &b_GenMu_RecoTrkAct);
   fChain->SetBranchAddress("GenMu_RecoTrkd3", &GenMu_RecoTrkd3, &b_GenMu_RecoTrkd3);
   fChain->SetBranchAddress("GenMu_RecoTrkIso", &GenMu_RecoTrkIso, &b_GenMu_RecoTrkIso);
   fChain->SetBranchAddress("GenMus", &GenMus, &b_GenMus);
   fChain->SetBranchAddress("genParticles", &genParticles, &b_genParticles);
   fChain->SetBranchAddress("genParticles_PDGid", &genParticles_PDGid, &b_genParticles_PDGid);
   fChain->SetBranchAddress("GenTau_GenTauHad", &GenTau_GenTauHad, &b_GenTau_GenTauHad);
   fChain->SetBranchAddress("GenTau_MT2Activity", &GenTau_MT2Activity, &b_GenTau_MT2Activity);
   fChain->SetBranchAddress("GenTauLeadRecoTrkAct", &GenTauLeadRecoTrkAct, &b_GenTauLeadRecoTrkAct);
   fChain->SetBranchAddress("GenTauLeadRecoTrkd3", &GenTauLeadRecoTrkd3, &b_GenTauLeadRecoTrkd3);
   fChain->SetBranchAddress("GenTauLeadRecoTrkIso", &GenTauLeadRecoTrkIso, &b_GenTauLeadRecoTrkIso);
   fChain->SetBranchAddress("GenTauLeadTrk", &GenTauLeadTrk, &b_GenTauLeadTrk);
   fChain->SetBranchAddress("GenTauNu", &GenTauNu, &b_GenTauNu);
   fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
   fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("HTJECdown", &HTJECdown, &b_HTJECdown);
   fChain->SetBranchAddress("HTJECup", &HTJECup, &b_HTJECup);
   fChain->SetBranchAddress("HTJetsMask", &HTJetsMask, &b_HTJetsMask);
   fChain->SetBranchAddress("HTJetsMaskJECdown", &HTJetsMaskJECdown, &b_HTJetsMaskJECdown);
   fChain->SetBranchAddress("HTJetsMaskJECup", &HTJetsMaskJECup, &b_HTJetsMaskJECup);
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
   fChain->SetBranchAddress("IsolatedElectronTracksVeto", &IsolatedElectronTracksVeto, &b_IsolatedElectronTracksVeto);
   fChain->SetBranchAddress("IsolatedMuonTracksVeto", &IsolatedMuonTracksVeto, &b_IsolatedMuonTracksVeto);
   fChain->SetBranchAddress("IsolatedPionTracksVeto", &IsolatedPionTracksVeto, &b_IsolatedPionTracksVeto);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
   fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
   fChain->SetBranchAddress("JetIDJECdown", &JetIDJECdown, &b_JetIDJECdown);
   fChain->SetBranchAddress("JetIDJECup", &JetIDJECup, &b_JetIDJECup);
   fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
   fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
   fChain->SetBranchAddress("Jets_bDiscriminatorMVA", &Jets_bDiscriminatorMVA, &b_Jets_bDiscriminatorMVA);
   fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
   fChain->SetBranchAddress("Jets_chargedMultiplicity", &Jets_chargedMultiplicity, &b_Jets_chargedMultiplicity);
   fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
   fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
   fChain->SetBranchAddress("Jets_jecFactor", &Jets_jecFactor, &b_Jets_jecFactor);
   fChain->SetBranchAddress("Jets_jecUnc", &Jets_jecUnc, &b_Jets_jecUnc);
   fChain->SetBranchAddress("Jets_jetArea", &Jets_jetArea, &b_Jets_jetArea);
   fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
   fChain->SetBranchAddress("Jets_muonMultiplicity", &Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
   fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronEnergyFraction", &Jets_neutralHadronEnergyFraction, &b_Jets_neutralHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
   fChain->SetBranchAddress("Jets_neutralMultiplicity", &Jets_neutralMultiplicity, &b_Jets_neutralMultiplicity);
   fChain->SetBranchAddress("Jets_partonFlavor", &Jets_partonFlavor, &b_Jets_partonFlavor);
   fChain->SetBranchAddress("Jets_photonEnergyFraction", &Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
   fChain->SetBranchAddress("Jets_photonMultiplicity", &Jets_photonMultiplicity, &b_Jets_photonMultiplicity);
   fChain->SetBranchAddress("JetsJECdown", &JetsJECdown, &b_JetsJECdown);
   fChain->SetBranchAddress("JetsJECdown_bDiscriminatorCSV", &JetsJECdown_bDiscriminatorCSV, &b_JetsJECdown_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJECdown_hadronFlavor", &JetsJECdown_hadronFlavor, &b_JetsJECdown_hadronFlavor);
   fChain->SetBranchAddress("JetsJECdown_partonFlavor", &JetsJECdown_partonFlavor, &b_JetsJECdown_partonFlavor);
   fChain->SetBranchAddress("JetsJECup", &JetsJECup, &b_JetsJECup);
   fChain->SetBranchAddress("JetsJECup_bDiscriminatorCSV", &JetsJECup_bDiscriminatorCSV, &b_JetsJECup_bDiscriminatorCSV);
   fChain->SetBranchAddress("JetsJECup_hadronFlavor", &JetsJECup_hadronFlavor, &b_JetsJECup_hadronFlavor);
   fChain->SetBranchAddress("JetsJECup_partonFlavor", &JetsJECup_partonFlavor, &b_JetsJECup_partonFlavor);
   fChain->SetBranchAddress("Leptons", &Leptons, &b_Leptons);
   fChain->SetBranchAddress("METFilters", &METFilters, &b_METFilters);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("METPhiDown", &METPhiDown, &b_METPhiDown);
   fChain->SetBranchAddress("METPhiUp", &METPhiUp, &b_METPhiUp);
   fChain->SetBranchAddress("METPt", &METPt, &b_METPt);
   fChain->SetBranchAddress("METPtDown", &METPtDown, &b_METPtDown);
   fChain->SetBranchAddress("METPtUp", &METPtUp, &b_METPtUp);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MHT_Phi", &MHT_Phi, &b_MHT_Phi);
   fChain->SetBranchAddress("MHT_PhiJECdown", &MHT_PhiJECdown, &b_MHT_PhiJECdown);
   fChain->SetBranchAddress("MHT_PhiJECup", &MHT_PhiJECup, &b_MHT_PhiJECup);
   fChain->SetBranchAddress("MHTJECdown", &MHTJECdown, &b_MHTJECdown);
   fChain->SetBranchAddress("MHTJECup", &MHTJECup, &b_MHTJECup);
   fChain->SetBranchAddress("MHTJetsMask", &MHTJetsMask, &b_MHTJetsMask);
   fChain->SetBranchAddress("MHTJetsMaskJECdown", &MHTJetsMaskJECdown, &b_MHTJetsMaskJECdown);
   fChain->SetBranchAddress("MHTJetsMaskJECup", &MHTJetsMaskJECup, &b_MHTJetsMaskJECup);
   fChain->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
   fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
   fChain->SetBranchAddress("nAllVertices", &nAllVertices, &b_nAllVertices);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("NJetsJECdown", &NJetsJECdown, &b_NJetsJECdown);
   fChain->SetBranchAddress("NJetsJECup", &NJetsJECup, &b_NJetsJECup);
   fChain->SetBranchAddress("nTAPElectronTracks", &nTAPElectronTracks, &b_nTAPElectronTracks);
   fChain->SetBranchAddress("nTAPMuonTracks", &nTAPMuonTracks, &b_nTAPMuonTracks);
   fChain->SetBranchAddress("nTAPPionTracks", &nTAPPionTracks, &b_nTAPPionTracks);
   fChain->SetBranchAddress("NumEvents", &NumEvents, &b_NumEvents);
   fChain->SetBranchAddress("NumInteractions", &NumInteractions, &b_NumInteractions);
   fChain->SetBranchAddress("NumPhotons", &NumPhotons, &b_NumPhotons);
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   fChain->SetBranchAddress("PDFids", &PDFids, &b_PDFids);
   fChain->SetBranchAddress("PDFweights", &PDFweights, &b_PDFweights);
   fChain->SetBranchAddress("puSysDown", &puSysDown, &b_puSysDown);
   fChain->SetBranchAddress("puSysUp", &puSysUp, &b_puSysUp);
   fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
   fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
   fChain->SetBranchAddress("selectedIDElectrons", &selectedIDElectrons, &b_selectedIDElectrons);
   fChain->SetBranchAddress("selectedIDElectrons_mediumID", &selectedIDElectrons_mediumID, &b_selectedIDElectrons_mediumID);
   fChain->SetBranchAddress("selectedIDElectrons_MiniIso", &selectedIDElectrons_MiniIso, &b_selectedIDElectrons_MiniIso);
   fChain->SetBranchAddress("selectedIDElectrons_MT2Activity", &selectedIDElectrons_MT2Activity, &b_selectedIDElectrons_MT2Activity);
   fChain->SetBranchAddress("selectedIDElectrons_MTW", &selectedIDElectrons_MTW, &b_selectedIDElectrons_MTW);
   fChain->SetBranchAddress("selectedIDIsoElectrons_mediumID", &selectedIDIsoElectrons_mediumID, &b_selectedIDIsoElectrons_mediumID);
   fChain->SetBranchAddress("selectedIDIsoElectrons_MT2Activity", &selectedIDIsoElectrons_MT2Activity, &b_selectedIDIsoElectrons_MT2Activity);
   fChain->SetBranchAddress("selectedIDIsoElectrons_MTW", &selectedIDIsoElectrons_MTW, &b_selectedIDIsoElectrons_MTW);
   fChain->SetBranchAddress("selectedIDIsoElectrons_PTW", &selectedIDIsoElectrons_PTW, &b_selectedIDIsoElectrons_PTW);
   fChain->SetBranchAddress("selectedIDIsoMuons_MT2Activity", &selectedIDIsoMuons_MT2Activity, &b_selectedIDIsoMuons_MT2Activity);
   fChain->SetBranchAddress("selectedIDIsoMuons_MTW", &selectedIDIsoMuons_MTW, &b_selectedIDIsoMuons_MTW);
   fChain->SetBranchAddress("selectedIDIsoMuons_PTW", &selectedIDIsoMuons_PTW, &b_selectedIDIsoMuons_PTW);
   fChain->SetBranchAddress("selectedIDMuons", &selectedIDMuons, &b_selectedIDMuons);
   fChain->SetBranchAddress("selectedIDMuons_MiniIso", &selectedIDMuons_MiniIso, &b_selectedIDMuons_MiniIso);
   fChain->SetBranchAddress("selectedIDMuons_MT2Activity", &selectedIDMuons_MT2Activity, &b_selectedIDMuons_MT2Activity);
   fChain->SetBranchAddress("selectedIDMuons_MTW", &selectedIDMuons_MTW, &b_selectedIDMuons_MTW);
   fChain->SetBranchAddress("slimJet", &slimJet, &b_slimJet);
   fChain->SetBranchAddress("slimJet_jecFactor", &slimJet_jecFactor, &b_slimJet_jecFactor);
   fChain->SetBranchAddress("slimJet_jecUnc", &slimJet_jecUnc, &b_slimJet_jecUnc);
   fChain->SetBranchAddress("slimJet_slimJetID", &slimJet_slimJetID, &b_slimJet_slimJetID);
   fChain->SetBranchAddress("slimJetJECdown", &slimJetJECdown, &b_slimJetJECdown);
   fChain->SetBranchAddress("slimJetJECdown_slimJetID", &slimJetJECdown_slimJetID, &b_slimJetJECdown_slimJetID);
   fChain->SetBranchAddress("slimJetJECup", &slimJetJECup, &b_slimJetJECup);
   fChain->SetBranchAddress("slimJetJECup_slimJetID", &slimJetJECup_slimJetID, &b_slimJetJECup_slimJetID);
   fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
   fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
   fChain->SetBranchAddress("TagLeptonHighPT", &TagLeptonHighPT, &b_TagLeptonHighPT);
   fChain->SetBranchAddress("TAPElectronTracks", &TAPElectronTracks, &b_TAPElectronTracks);
   fChain->SetBranchAddress("TAPElectronTracks_activity", &TAPElectronTracks_activity, &b_TAPElectronTracks_activity);
   fChain->SetBranchAddress("TAPElectronTracks_chg", &TAPElectronTracks_chg, &b_TAPElectronTracks_chg);
   fChain->SetBranchAddress("TAPElectronTracks_mT", &TAPElectronTracks_mT, &b_TAPElectronTracks_mT);
   fChain->SetBranchAddress("TAPElectronTracks_trkiso", &TAPElectronTracks_trkiso, &b_TAPElectronTracks_trkiso);
   fChain->SetBranchAddress("TAPMuonTracks", &TAPMuonTracks, &b_TAPMuonTracks);
   fChain->SetBranchAddress("TAPMuonTracks_activity", &TAPMuonTracks_activity, &b_TAPMuonTracks_activity);
   fChain->SetBranchAddress("TAPMuonTracks_chg", &TAPMuonTracks_chg, &b_TAPMuonTracks_chg);
   fChain->SetBranchAddress("TAPMuonTracks_mT", &TAPMuonTracks_mT, &b_TAPMuonTracks_mT);
   fChain->SetBranchAddress("TAPMuonTracks_trkiso", &TAPMuonTracks_trkiso, &b_TAPMuonTracks_trkiso);
   fChain->SetBranchAddress("TAPPionTracks", &TAPPionTracks, &b_TAPPionTracks);
   fChain->SetBranchAddress("TAPPionTracks_activity", &TAPPionTracks_activity, &b_TAPPionTracks_activity);
   fChain->SetBranchAddress("TAPPionTracks_chg", &TAPPionTracks_chg, &b_TAPPionTracks_chg);
   fChain->SetBranchAddress("TAPPionTracks_mT", &TAPPionTracks_mT, &b_TAPPionTracks_mT);
   fChain->SetBranchAddress("TAPPionTracks_trkiso", &TAPPionTracks_trkiso, &b_TAPPionTracks_trkiso);
   fChain->SetBranchAddress("TauDecayCands", &TauDecayCands, &b_TauDecayCands);
   fChain->SetBranchAddress("TauDecayCands_momInd", &TauDecayCands_momInd, &b_TauDecayCands_momInd);
   fChain->SetBranchAddress("TauDecayCands_pdgID", &TauDecayCands_pdgID, &b_TauDecayCands_pdgID);
   fChain->SetBranchAddress("TauIdVecagainstElectronLooseMVA5", &TauIdVecagainstElectronLooseMVA5, &b_TauIdVecagainstElectronLooseMVA5);
   fChain->SetBranchAddress("TauIdVecagainstElectronMediumMVA5", &TauIdVecagainstElectronMediumMVA5, &b_TauIdVecagainstElectronMediumMVA5);
   fChain->SetBranchAddress("TauIdVecagainstElectronVLooseMVA5", &TauIdVecagainstElectronVLooseMVA5, &b_TauIdVecagainstElectronVLooseMVA5);
   fChain->SetBranchAddress("TauIdVecagainstMuonLoose3", &TauIdVecagainstMuonLoose3, &b_TauIdVecagainstMuonLoose3);
   fChain->SetBranchAddress("TauIdVecagainstMuonTight3", &TauIdVecagainstMuonTight3, &b_TauIdVecagainstMuonTight3);
   fChain->SetBranchAddress("TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits", &TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits, &b_TauIdVecbyLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("TauIdVecbyLoosePileupWeightedIsolation3Hits", &TauIdVecbyLoosePileupWeightedIsolation3Hits, &b_TauIdVecbyLoosePileupWeightedIsolation3Hits);
   fChain->SetBranchAddress("TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits", &TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits, &b_TauIdVecbyMediumCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("TauIdVecbyMediumPileupWeightedIsolation3Hits", &TauIdVecbyMediumPileupWeightedIsolation3Hits, &b_TauIdVecbyMediumPileupWeightedIsolation3Hits);
   fChain->SetBranchAddress("TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits", &TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits, &b_TauIdVecbyTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("TauIdVecbyTightPileupWeightedIsolation3Hits", &TauIdVecbyTightPileupWeightedIsolation3Hits, &b_TauIdVecbyTightPileupWeightedIsolation3Hits);
   fChain->SetBranchAddress("TauLorVec", &TauLorVec, &b_TauLorVec);
   fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
   fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
   fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
   fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   Notify();
}

Bool_t branches::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void branches::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t branches::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef branches_cxx
