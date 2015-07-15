//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 13 09:22:06 2015 by ROOT version 5.34/22
// from TTree PreSelection/PreSelection
// found on file: /home/hatake/ana/RA2/CMSSW_7_2_3_patch1_July11_v03/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection_khmod8.root
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

// Fixed size dimensions of array or collections stored in the TTree if any.

class branches {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   UInt_t          EvtNum;
   Int_t           NVtx;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Int_t           Leptons;
   Int_t           TagLeptonHighPT;
   Int_t           NumPhotons;
   Int_t           METFilters;
   Int_t           CSCTightHaloFilter;
   Int_t           HBHENoiseFilter;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           NJets;
   Int_t           BTags;
   Float_t         Weight;
   Float_t         HT;
   Float_t         MHT;
   Float_t         MHT_Phi;
   Float_t         DeltaPhi1;
   Float_t         DeltaPhi2;
   Float_t         DeltaPhi3;
   Float_t         minDeltaPhiN;
   Float_t         DeltaPhiN1;
   Float_t         DeltaPhiN2;
   Float_t         DeltaPhiN3;
   Float_t         METPt;
   Float_t         METPhi;
   UChar_t         JetID;
   vector<double>  *testVec;
   vector<double>  *MuonsPtVec;
   vector<double>  *MuonsEtaVec;
   vector<double>  *MuonsPhiVec;
   UShort_t        MuonsNum;
   Float_t         MuonsE[2];   //[MuonsNum]
   Float_t         MuonsTLorentzVector[2];   //[MuonsNum]
   vector<double>  *ElectronsPtVec;
   vector<double>  *ElectronsEtaVec;
   vector<double>  *ElectronsPhiVec;
   UShort_t        ElectronsNum;
   Float_t         ElectronsE[3];   //[ElectronsNum]
   Float_t         ElectronsTLorentzVector[3];   //[ElectronsNum]
   vector<double>  *IsolatedElectronTracksVetoPtVec;
   vector<double>  *IsolatedElectronTracksVetoEtaVec;
   vector<double>  *IsolatedElectronTracksVetoPhiVec;
   UShort_t        IsolatedElectronTracksVetoNum;
   Float_t         IsolatedElectronTracksVetoE[3];   //[IsolatedElectronTracksVetoNum]
   Float_t         IsolatedElectronTracksVetoTLorentzVector[3];   //[IsolatedElectronTracksVetoNum]
   Float_t         IsolatedElectronTracksVeto_MT[3];   //[IsolatedElectronTracksVetoNum]
   vector<double>  *IsolatedMuonTracksVetoPtVec;
   vector<double>  *IsolatedMuonTracksVetoEtaVec;
   vector<double>  *IsolatedMuonTracksVetoPhiVec;
   UShort_t        IsolatedMuonTracksVetoNum;
   Float_t         IsolatedMuonTracksVetoE[2];   //[IsolatedMuonTracksVetoNum]
   Float_t         IsolatedMuonTracksVetoTLorentzVector[2];   //[IsolatedMuonTracksVetoNum]
   Float_t         IsolatedMuonTracksVeto_MT_1[2];   //[IsolatedMuonTracksVetoNum]
   vector<double>  *IsolatedPionTracksVetoPtVec;
   vector<double>  *IsolatedPionTracksVetoEtaVec;
   vector<double>  *IsolatedPionTracksVetoPhiVec;
   UShort_t        IsolatedPionTracksVetoNum;
   Float_t         IsolatedPionTracksVetoE[2];   //[IsolatedPionTracksVetoNum]
   Float_t         IsolatedPionTracksVetoTLorentzVector[2];   //[IsolatedPionTracksVetoNum]
   Float_t         IsolatedPionTracksVeto_MT_2[2];   //[IsolatedPionTracksVetoNum]
   vector<double>  *selectedIDIsoMuonsPtVec;
   vector<double>  *selectedIDIsoMuonsEtaVec;
   vector<double>  *selectedIDIsoMuonsPhiVec;
   UShort_t        selectedIDIsoMuonsNum;
   Float_t         selectedIDIsoMuonsE[2];   //[selectedIDIsoMuonsNum]
   Float_t         selectedIDIsoMuonsTLorentzVector[2];   //[selectedIDIsoMuonsNum]
   Float_t         selectedIDIsoMuons_MTW[2];   //[selectedIDIsoMuonsNum]
   vector<double>  *selectedIDMuonsPtVec;
   vector<double>  *selectedIDMuonsEtaVec;
   vector<double>  *selectedIDMuonsPhiVec;
   UShort_t        selectedIDMuonsNum;
   Float_t         selectedIDMuonsE[4];   //[selectedIDMuonsNum]
   Float_t         selectedIDMuonsTLorentzVector[4];   //[selectedIDMuonsNum]
   Float_t         selectedIDMuons_MTW_1[4];   //[selectedIDMuonsNum]
   vector<double>  *selectedIDIsoElectronsPtVec;
   vector<double>  *selectedIDIsoElectronsEtaVec;
   vector<double>  *selectedIDIsoElectronsPhiVec;
   UShort_t        selectedIDIsoElectronsNum;
   Float_t         selectedIDIsoElectronsE[3];   //[selectedIDIsoElectronsNum]
   Float_t         selectedIDIsoElectronsTLorentzVector[3];   //[selectedIDIsoElectronsNum]
   Float_t         selectedIDIsoElectrons_MTW_2[3];   //[selectedIDIsoElectronsNum]
   vector<double>  *selectedIDElectronsPtVec;
   vector<double>  *selectedIDElectronsEtaVec;
   vector<double>  *selectedIDElectronsPhiVec;
   UShort_t        selectedIDElectronsNum;
   Float_t         selectedIDElectronsE[3];   //[selectedIDElectronsNum]
   Float_t         selectedIDElectronsTLorentzVector[3];   //[selectedIDElectronsNum]
   Float_t         selectedIDElectrons_MTW_3[3];   //[selectedIDElectronsNum]
   vector<double>  *SelectedPFCandidatesPtVec;
   vector<double>  *SelectedPFCandidatesEtaVec;
   vector<double>  *SelectedPFCandidatesPhiVec;
   UShort_t        SelectedPFCandidatesNum;
   Float_t         SelectedPFCandidatesE[110];   //[SelectedPFCandidatesNum]
   Float_t         SelectedPFCandidatesTLorentzVector[110];   //[SelectedPFCandidatesNum]
   Int_t           SelectedPFCandidates_Charge[110];   //[SelectedPFCandidatesNum]
   Int_t           SelectedPFCandidates_Typ[110];   //[SelectedPFCandidatesNum]
   vector<double>  *GenBosonPtVec;
   vector<double>  *GenBosonEtaVec;
   vector<double>  *GenBosonPhiVec;
   UShort_t        GenBosonNum;
   Float_t         GenBosonE[1];   //[GenBosonNum]
   Float_t         GenBosonTLorentzVector[1];   //[GenBosonNum]
   Int_t           GenBoson_GenBosonPDGId[1];   //[GenBosonNum]
   vector<double>  *GenMuPtVec;
   vector<double>  *GenMuEtaVec;
   vector<double>  *GenMuPhiVec;
   UShort_t        GenMuNum;
   Float_t         GenMuE[2];   //[GenMuNum]
   Float_t         GenMuTLorentzVector[2];   //[GenMuNum]
   Int_t           GenMu_GenMuFromTau[2];   //[GenMuNum]
   vector<double>  *GenElecPtVec;
   vector<double>  *GenElecEtaVec;
   vector<double>  *GenElecPhiVec;
   UShort_t        GenElecNum;
   Float_t         GenElecE[2];   //[GenElecNum]
   Float_t         GenElecTLorentzVector[2];   //[GenElecNum]
   Int_t           GenElec_GenElecFromTau[2];   //[GenElecNum]
   vector<double>  *GenTauPtVec;
   vector<double>  *GenTauEtaVec;
   vector<double>  *GenTauPhiVec;
   UShort_t        GenTauNum;
   Float_t         GenTauE[2];   //[GenTauNum]
   Float_t         GenTauTLorentzVector[2];   //[GenTauNum]
   Int_t           GenTau_GenTauHad[2];   //[GenTauNum]
   vector<double>  *TauDecayCandsPtVec;
   vector<double>  *TauDecayCandsEtaVec;
   vector<double>  *TauDecayCandsPhiVec;
   UShort_t        TauDecayCandsNum;
   Float_t         TauDecayCandsE[6];   //[TauDecayCandsNum]
   Float_t         TauDecayCandsTLorentzVector[6];   //[TauDecayCandsNum]
   Int_t           TauDecayCands_pdgID[6];   //[TauDecayCandsNum]
   vector<double>  *selectedIDIsoMuonsNoMiniIsoPtVec;
   vector<double>  *selectedIDIsoMuonsNoMiniIsoEtaVec;
   vector<double>  *selectedIDIsoMuonsNoMiniIsoPhiVec;
   UShort_t        selectedIDIsoMuonsNoMiniIsoNum;
   Float_t         selectedIDIsoMuonsNoMiniIsoE[2];   //[selectedIDIsoMuonsNoMiniIsoNum]
   Float_t         selectedIDIsoMuonsNoMiniIsoTLorentzVector[2];   //[selectedIDIsoMuonsNoMiniIsoNum]
   vector<double>  *selectedIDIsoElectronsNoMiniIsoPtVec;
   vector<double>  *selectedIDIsoElectronsNoMiniIsoEtaVec;
   vector<double>  *selectedIDIsoElectronsNoMiniIsoPhiVec;
   UShort_t        selectedIDIsoElectronsNoMiniIsoNum;
   Float_t         selectedIDIsoElectronsNoMiniIsoE[3];   //[selectedIDIsoElectronsNoMiniIsoNum]
   Float_t         selectedIDIsoElectronsNoMiniIsoTLorentzVector[3];   //[selectedIDIsoElectronsNoMiniIsoNum]
   vector<double>  *JetsPtVec;
   vector<double>  *JetsEtaVec;
   vector<double>  *JetsPhiVec;
   UShort_t        JetsNum;
   Float_t         JetsE[10];   //[JetsNum]
   Float_t         JetsTLorentzVector[10];   //[JetsNum]
   Float_t         Jets_bDiscriminator[10];   //[JetsNum]
   Float_t         Jets_chargedEmEnergyFraction[10];   //[JetsNum]
   Float_t         Jets_chargedHadronEnergyFraction[10];   //[JetsNum]
   Int_t           Jets_chargedHadronMultiplicity[10];   //[JetsNum]
   Int_t           Jets_electronMultiplicity[10];   //[JetsNum]
   Float_t         Jets_jetArea[10];   //[JetsNum]
   Float_t         Jets_muonEnergyFraction[10];   //[JetsNum]
   Int_t           Jets_muonMultiplicity[10];   //[JetsNum]
   Float_t         Jets_neutralEmEnergyFraction[10];   //[JetsNum]
   Int_t           Jets_neutralHadronMultiplicity[10];   //[JetsNum]
   Float_t         Jets_photonEnergyFraction[10];   //[JetsNum]
   Int_t           Jets_photonMultiplicity[10];   //[JetsNum]
   vector<double>  *slimmedElectronsPtVec;
   vector<double>  *slimmedElectronsEtaVec;
   vector<double>  *slimmedElectronsPhiVec;
   UShort_t        slimmedElectronsNum;
   Float_t         slimmedElectronsE[8];   //[slimmedElectronsNum]
   Float_t         slimmedElectronsTLorentzVector[8];   //[slimmedElectronsNum]
   vector<double>  *slimmedMuonsPtVec;
   vector<double>  *slimmedMuonsEtaVec;
   vector<double>  *slimmedMuonsPhiVec;
   UShort_t        slimmedMuonsNum;
   Float_t         slimmedMuonsE[16];   //[slimmedMuonsNum]
   Float_t         slimmedMuonsTLorentzVector[16];   //[slimmedMuonsNum]
   vector<double>  *SelectedPFElecCandidatesPtVec;
   vector<double>  *SelectedPFElecCandidatesEtaVec;
   vector<double>  *SelectedPFElecCandidatesPhiVec;
   UShort_t        SelectedPFElecCandidatesNum;
   Float_t         SelectedPFElecCandidatesE[5];   //[SelectedPFElecCandidatesNum]
   Float_t         SelectedPFElecCandidatesTLorentzVector[5];   //[SelectedPFElecCandidatesNum]
   vector<double>  *SelectedPFMuCandidatesPtVec;
   vector<double>  *SelectedPFMuCandidatesEtaVec;
   vector<double>  *SelectedPFMuCandidatesPhiVec;
   UShort_t        SelectedPFMuCandidatesNum;
   Float_t         SelectedPFMuCandidatesE[4];   //[SelectedPFMuCandidatesNum]
   Float_t         SelectedPFMuCandidatesTLorentzVector[4];   //[SelectedPFMuCandidatesNum]
   vector<double>  *SelectedPFPionCandidatesPtVec;
   vector<double>  *SelectedPFPionCandidatesEtaVec;
   vector<double>  *SelectedPFPionCandidatesPhiVec;
   UShort_t        SelectedPFPionCandidatesNum;
   Float_t         SelectedPFPionCandidatesE[39];   //[SelectedPFPionCandidatesNum]
   Float_t         SelectedPFPionCandidatesTLorentzVector[39];   //[SelectedPFPionCandidatesNum]
   vector<double>  *slimJetPtVec;
   vector<double>  *slimJetEtaVec;
   vector<double>  *slimJetPhiVec;
   UShort_t        slimJetNum;
   Float_t         slimJetE[52];   //[slimJetNum]
   Float_t         slimJetTLorentzVector[52];   //[slimJetNum]
   Int_t           slimJet_slimJetID[52];   //[slimJetNum]
   vector<double>  *GenTauNuPtVec;
   vector<double>  *GenTauNuEtaVec;
   vector<double>  *GenTauNuPhiVec;
   UShort_t        GenTauNuNum;
   Float_t         GenTauNuE[4];   //[GenTauNuNum]
   Float_t         GenTauNuTLorentzVector[4];   //[GenTauNuNum]
   Float_t         GenTauNu_TauNuMomPt[4];   //[GenTauNuNum]
   vector<int>     *genParticles_PDGid;
   vector<int>     *PassTrigger;
   vector<string>  *TriggerNames;
   vector<TLorentzVector> *genParticles;
   vector<TLorentzVector> *bestPhoton;

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_isoElectronTracks;   //!
   TBranch        *b_isoMuonTracks;   //!
   TBranch        *b_isoPionTracks;   //!
   TBranch        *b_Leptons;   //!
   TBranch        *b_TagLeptonHighPT;   //!
   TBranch        *b_NumPhotons;   //!
   TBranch        *b_METFilters;   //!
   TBranch        *b_CSCTightHaloFilter;   //!
   TBranch        *b_HBHENoiseFilter;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_BTags;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_MHT_Phi;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_minDeltaPhiN;   //!
   TBranch        *b_DeltaPhiN1;   //!
   TBranch        *b_DeltaPhiN2;   //!
   TBranch        *b_DeltaPhiN3;   //!
   TBranch        *b_METPt;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_JetID;   //!
   TBranch        *b_testVec;   //!
   TBranch        *b_MuonsPtVec;   //!
   TBranch        *b_MuonsEtaVec;   //!
   TBranch        *b_MuonsPhiVec;   //!
   TBranch        *b_MuonsNum;   //!
   TBranch        *b_MuonsE;   //!
   TBranch        *b_MuonsTLorentzVector;   //!
   TBranch        *b_ElectronsPtVec;   //!
   TBranch        *b_ElectronsEtaVec;   //!
   TBranch        *b_ElectronsPhiVec;   //!
   TBranch        *b_ElectronsNum;   //!
   TBranch        *b_ElectronsE;   //!
   TBranch        *b_ElectronsTLorentzVector;   //!
   TBranch        *b_IsolatedElectronTracksVetoPtVec;   //!
   TBranch        *b_IsolatedElectronTracksVetoEtaVec;   //!
   TBranch        *b_IsolatedElectronTracksVetoPhiVec;   //!
   TBranch        *b_IsolatedElectronTracksVetoNum;   //!
   TBranch        *b_IsolatedElectronTracksVetoE;   //!
   TBranch        *b_IsolatedElectronTracksVetoTLorentzVector;   //!
   TBranch        *b_IsolatedElectronTracksVeto_MT;   //!
   TBranch        *b_IsolatedMuonTracksVetoPtVec;   //!
   TBranch        *b_IsolatedMuonTracksVetoEtaVec;   //!
   TBranch        *b_IsolatedMuonTracksVetoPhiVec;   //!
   TBranch        *b_IsolatedMuonTracksVetoNum;   //!
   TBranch        *b_IsolatedMuonTracksVetoE;   //!
   TBranch        *b_IsolatedMuonTracksVetoTLorentzVector;   //!
   TBranch        *b_IsolatedMuonTracksVeto_MT_1;   //!
   TBranch        *b_IsolatedPionTracksVetoPtVec;   //!
   TBranch        *b_IsolatedPionTracksVetoEtaVec;   //!
   TBranch        *b_IsolatedPionTracksVetoPhiVec;   //!
   TBranch        *b_IsolatedPionTracksVetoNum;   //!
   TBranch        *b_IsolatedPionTracksVetoE;   //!
   TBranch        *b_IsolatedPionTracksVetoTLorentzVector;   //!
   TBranch        *b_IsolatedPionTracksVeto_MT_2;   //!
   TBranch        *b_selectedIDIsoMuonsPtVec;   //!
   TBranch        *b_selectedIDIsoMuonsEtaVec;   //!
   TBranch        *b_selectedIDIsoMuonsPhiVec;   //!
   TBranch        *b_selectedIDIsoMuonsNum;   //!
   TBranch        *b_selectedIDIsoMuonsE;   //!
   TBranch        *b_selectedIDIsoMuonsTLorentzVector;   //!
   TBranch        *b_selectedIDIsoMuons_MTW;   //!
   TBranch        *b_selectedIDMuonsPtVec;   //!
   TBranch        *b_selectedIDMuonsEtaVec;   //!
   TBranch        *b_selectedIDMuonsPhiVec;   //!
   TBranch        *b_selectedIDMuonsNum;   //!
   TBranch        *b_selectedIDMuonsE;   //!
   TBranch        *b_selectedIDMuonsTLorentzVector;   //!
   TBranch        *b_selectedIDMuons_MTW_1;   //!
   TBranch        *b_selectedIDIsoElectronsPtVec;   //!
   TBranch        *b_selectedIDIsoElectronsEtaVec;   //!
   TBranch        *b_selectedIDIsoElectronsPhiVec;   //!
   TBranch        *b_selectedIDIsoElectronsNum;   //!
   TBranch        *b_selectedIDIsoElectronsE;   //!
   TBranch        *b_selectedIDIsoElectronsTLorentzVector;   //!
   TBranch        *b_selectedIDIsoElectrons_MTW_2;   //!
   TBranch        *b_selectedIDElectronsPtVec;   //!
   TBranch        *b_selectedIDElectronsEtaVec;   //!
   TBranch        *b_selectedIDElectronsPhiVec;   //!
   TBranch        *b_selectedIDElectronsNum;   //!
   TBranch        *b_selectedIDElectronsE;   //!
   TBranch        *b_selectedIDElectronsTLorentzVector;   //!
   TBranch        *b_selectedIDElectrons_MTW_3;   //!
   TBranch        *b_SelectedPFCandidatesPtVec;   //!
   TBranch        *b_SelectedPFCandidatesEtaVec;   //!
   TBranch        *b_SelectedPFCandidatesPhiVec;   //!
   TBranch        *b_SelectedPFCandidatesNum;   //!
   TBranch        *b_SelectedPFCandidatesE;   //!
   TBranch        *b_SelectedPFCandidatesTLorentzVector;   //!
   TBranch        *b_SelectedPFCandidates_Charge;   //!
   TBranch        *b_SelectedPFCandidates_Typ;   //!
   TBranch        *b_GenBosonPtVec;   //!
   TBranch        *b_GenBosonEtaVec;   //!
   TBranch        *b_GenBosonPhiVec;   //!
   TBranch        *b_GenBosonNum;   //!
   TBranch        *b_GenBosonE;   //!
   TBranch        *b_GenBosonTLorentzVector;   //!
   TBranch        *b_GenBoson_GenBosonPDGId;   //!
   TBranch        *b_GenMuPtVec;   //!
   TBranch        *b_GenMuEtaVec;   //!
   TBranch        *b_GenMuPhiVec;   //!
   TBranch        *b_GenMuNum;   //!
   TBranch        *b_GenMuE;   //!
   TBranch        *b_GenMuTLorentzVector;   //!
   TBranch        *b_GenMu_GenMuFromTau;   //!
   TBranch        *b_GenElecPtVec;   //!
   TBranch        *b_GenElecEtaVec;   //!
   TBranch        *b_GenElecPhiVec;   //!
   TBranch        *b_GenElecNum;   //!
   TBranch        *b_GenElecE;   //!
   TBranch        *b_GenElecTLorentzVector;   //!
   TBranch        *b_GenElec_GenElecFromTau;   //!
   TBranch        *b_GenTauPtVec;   //!
   TBranch        *b_GenTauEtaVec;   //!
   TBranch        *b_GenTauPhiVec;   //!
   TBranch        *b_GenTauNum;   //!
   TBranch        *b_GenTauE;   //!
   TBranch        *b_GenTauTLorentzVector;   //!
   TBranch        *b_GenTau_GenTauHad;   //!
   TBranch        *b_TauDecayCandsPtVec;   //!
   TBranch        *b_TauDecayCandsEtaVec;   //!
   TBranch        *b_TauDecayCandsPhiVec;   //!
   TBranch        *b_TauDecayCandsNum;   //!
   TBranch        *b_TauDecayCandsE;   //!
   TBranch        *b_TauDecayCandsTLorentzVector;   //!
   TBranch        *b_TauDecayCands_pdgID;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoPtVec;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoEtaVec;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoPhiVec;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoNum;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoE;   //!
   TBranch        *b_selectedIDIsoMuonsNoMiniIsoTLorentzVector;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoPtVec;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoEtaVec;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoPhiVec;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoNum;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoE;   //!
   TBranch        *b_selectedIDIsoElectronsNoMiniIsoTLorentzVector;   //!
   TBranch        *b_JetsPtVec;   //!
   TBranch        *b_JetsEtaVec;   //!
   TBranch        *b_JetsPhiVec;   //!
   TBranch        *b_JetsNum;   //!
   TBranch        *b_JetsE;   //!
   TBranch        *b_JetsTLorentzVector;   //!
   TBranch        *b_Jets_bDiscriminator;   //!
   TBranch        *b_Jets_chargedEmEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronEnergyFraction;   //!
   TBranch        *b_Jets_chargedHadronMultiplicity;   //!
   TBranch        *b_Jets_electronMultiplicity;   //!
   TBranch        *b_Jets_jetArea;   //!
   TBranch        *b_Jets_muonEnergyFraction;   //!
   TBranch        *b_Jets_muonMultiplicity;   //!
   TBranch        *b_Jets_neutralEmEnergyFraction;   //!
   TBranch        *b_Jets_neutralHadronMultiplicity;   //!
   TBranch        *b_Jets_photonEnergyFraction;   //!
   TBranch        *b_Jets_photonMultiplicity;   //!
   TBranch        *b_slimmedElectronsPtVec;   //!
   TBranch        *b_slimmedElectronsEtaVec;   //!
   TBranch        *b_slimmedElectronsPhiVec;   //!
   TBranch        *b_slimmedElectronsNum;   //!
   TBranch        *b_slimmedElectronsE;   //!
   TBranch        *b_slimmedElectronsTLorentzVector;   //!
   TBranch        *b_slimmedMuonsPtVec;   //!
   TBranch        *b_slimmedMuonsEtaVec;   //!
   TBranch        *b_slimmedMuonsPhiVec;   //!
   TBranch        *b_slimmedMuonsNum;   //!
   TBranch        *b_slimmedMuonsE;   //!
   TBranch        *b_slimmedMuonsTLorentzVector;   //!
   TBranch        *b_SelectedPFElecCandidatesPtVec;   //!
   TBranch        *b_SelectedPFElecCandidatesEtaVec;   //!
   TBranch        *b_SelectedPFElecCandidatesPhiVec;   //!
   TBranch        *b_SelectedPFElecCandidatesNum;   //!
   TBranch        *b_SelectedPFElecCandidatesE;   //!
   TBranch        *b_SelectedPFElecCandidatesTLorentzVector;   //!
   TBranch        *b_SelectedPFMuCandidatesPtVec;   //!
   TBranch        *b_SelectedPFMuCandidatesEtaVec;   //!
   TBranch        *b_SelectedPFMuCandidatesPhiVec;   //!
   TBranch        *b_SelectedPFMuCandidatesNum;   //!
   TBranch        *b_SelectedPFMuCandidatesE;   //!
   TBranch        *b_SelectedPFMuCandidatesTLorentzVector;   //!
   TBranch        *b_SelectedPFPionCandidatesPtVec;   //!
   TBranch        *b_SelectedPFPionCandidatesEtaVec;   //!
   TBranch        *b_SelectedPFPionCandidatesPhiVec;   //!
   TBranch        *b_SelectedPFPionCandidatesNum;   //!
   TBranch        *b_SelectedPFPionCandidatesE;   //!
   TBranch        *b_SelectedPFPionCandidatesTLorentzVector;   //!
   TBranch        *b_slimJetPtVec;   //!
   TBranch        *b_slimJetEtaVec;   //!
   TBranch        *b_slimJetPhiVec;   //!
   TBranch        *b_slimJetNum;   //!
   TBranch        *b_slimJetE;   //!
   TBranch        *b_slimJetTLorentzVector;   //!
   TBranch        *b_slimJet_slimJetID;   //!
   TBranch        *b_GenTauNuPtVec;   //!
   TBranch        *b_GenTauNuEtaVec;   //!
   TBranch        *b_GenTauNuPhiVec;   //!
   TBranch        *b_GenTauNuNum;   //!
   TBranch        *b_GenTauNuE;   //!
   TBranch        *b_GenTauNuTLorentzVector;   //!
   TBranch        *b_GenTauNu_TauNuMomPt;   //!
   TBranch        *b_genParticles_PDGid;   //!
   TBranch        *b_PassTrigger;   //!
   TBranch        *b_TriggerNames;   //!
   TBranch        *b_genParticles;   //!
   TBranch        *b_bestPhoton;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/hatake/ana/RA2/CMSSW_7_2_3_patch1_July11_v03/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection_khmod8.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/hatake/ana/RA2/CMSSW_7_2_3_patch1_July11_v03/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection_khmod8.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/hatake/ana/RA2/CMSSW_7_2_3_patch1_July11_v03/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection_khmod8.root:/TreeMaker2");
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
   testVec = 0;
   MuonsPtVec = 0;
   MuonsEtaVec = 0;
   MuonsPhiVec = 0;
   ElectronsPtVec = 0;
   ElectronsEtaVec = 0;
   ElectronsPhiVec = 0;
   IsolatedElectronTracksVetoPtVec = 0;
   IsolatedElectronTracksVetoEtaVec = 0;
   IsolatedElectronTracksVetoPhiVec = 0;
   IsolatedMuonTracksVetoPtVec = 0;
   IsolatedMuonTracksVetoEtaVec = 0;
   IsolatedMuonTracksVetoPhiVec = 0;
   IsolatedPionTracksVetoPtVec = 0;
   IsolatedPionTracksVetoEtaVec = 0;
   IsolatedPionTracksVetoPhiVec = 0;
   selectedIDIsoMuonsPtVec = 0;
   selectedIDIsoMuonsEtaVec = 0;
   selectedIDIsoMuonsPhiVec = 0;
   selectedIDMuonsPtVec = 0;
   selectedIDMuonsEtaVec = 0;
   selectedIDMuonsPhiVec = 0;
   selectedIDIsoElectronsPtVec = 0;
   selectedIDIsoElectronsEtaVec = 0;
   selectedIDIsoElectronsPhiVec = 0;
   selectedIDElectronsPtVec = 0;
   selectedIDElectronsEtaVec = 0;
   selectedIDElectronsPhiVec = 0;
   SelectedPFCandidatesPtVec = 0;
   SelectedPFCandidatesEtaVec = 0;
   SelectedPFCandidatesPhiVec = 0;
   GenBosonPtVec = 0;
   GenBosonEtaVec = 0;
   GenBosonPhiVec = 0;
   GenMuPtVec = 0;
   GenMuEtaVec = 0;
   GenMuPhiVec = 0;
   GenElecPtVec = 0;
   GenElecEtaVec = 0;
   GenElecPhiVec = 0;
   GenTauPtVec = 0;
   GenTauEtaVec = 0;
   GenTauPhiVec = 0;
   TauDecayCandsPtVec = 0;
   TauDecayCandsEtaVec = 0;
   TauDecayCandsPhiVec = 0;
   selectedIDIsoMuonsNoMiniIsoPtVec = 0;
   selectedIDIsoMuonsNoMiniIsoEtaVec = 0;
   selectedIDIsoMuonsNoMiniIsoPhiVec = 0;
   selectedIDIsoElectronsNoMiniIsoPtVec = 0;
   selectedIDIsoElectronsNoMiniIsoEtaVec = 0;
   selectedIDIsoElectronsNoMiniIsoPhiVec = 0;
   JetsPtVec = 0;
   JetsEtaVec = 0;
   JetsPhiVec = 0;
   slimmedElectronsPtVec = 0;
   slimmedElectronsEtaVec = 0;
   slimmedElectronsPhiVec = 0;
   slimmedMuonsPtVec = 0;
   slimmedMuonsEtaVec = 0;
   slimmedMuonsPhiVec = 0;
   SelectedPFElecCandidatesPtVec = 0;
   SelectedPFElecCandidatesEtaVec = 0;
   SelectedPFElecCandidatesPhiVec = 0;
   SelectedPFMuCandidatesPtVec = 0;
   SelectedPFMuCandidatesEtaVec = 0;
   SelectedPFMuCandidatesPhiVec = 0;
   SelectedPFPionCandidatesPtVec = 0;
   SelectedPFPionCandidatesEtaVec = 0;
   SelectedPFPionCandidatesPhiVec = 0;
   slimJetPtVec = 0;
   slimJetEtaVec = 0;
   slimJetPhiVec = 0;
   GenTauNuPtVec = 0;
   GenTauNuEtaVec = 0;
   GenTauNuPhiVec = 0;
   genParticles_PDGid = 0;
   PassTrigger = 0;
   TriggerNames = 0;
   genParticles = 0;
   bestPhoton = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks, &b_isoElectronTracks);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks, &b_isoMuonTracks);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks, &b_isoPionTracks);
   fChain->SetBranchAddress("Leptons", &Leptons, &b_Leptons);
   fChain->SetBranchAddress("TagLeptonHighPT", &TagLeptonHighPT, &b_TagLeptonHighPT);
   fChain->SetBranchAddress("NumPhotons", &NumPhotons, &b_NumPhotons);
   fChain->SetBranchAddress("METFilters", &METFilters, &b_METFilters);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MHT_Phi", &MHT_Phi, &b_MHT_Phi);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN, &b_minDeltaPhiN);
   fChain->SetBranchAddress("DeltaPhiN1", &DeltaPhiN1, &b_DeltaPhiN1);
   fChain->SetBranchAddress("DeltaPhiN2", &DeltaPhiN2, &b_DeltaPhiN2);
   fChain->SetBranchAddress("DeltaPhiN3", &DeltaPhiN3, &b_DeltaPhiN3);
   fChain->SetBranchAddress("METPt", &METPt, &b_METPt);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
   fChain->SetBranchAddress("testVec", &testVec, &b_testVec);
   fChain->SetBranchAddress("MuonsPtVec", &MuonsPtVec, &b_MuonsPtVec);
   fChain->SetBranchAddress("MuonsEtaVec", &MuonsEtaVec, &b_MuonsEtaVec);
   fChain->SetBranchAddress("MuonsPhiVec", &MuonsPhiVec, &b_MuonsPhiVec);
   fChain->SetBranchAddress("MuonsNum", &MuonsNum, &b_MuonsNum);
   fChain->SetBranchAddress("MuonsE", MuonsE, &b_MuonsE);
   fChain->SetBranchAddress("MuonsTLorentzVector", MuonsTLorentzVector, &b_MuonsTLorentzVector);
   fChain->SetBranchAddress("ElectronsPtVec", &ElectronsPtVec, &b_ElectronsPtVec);
   fChain->SetBranchAddress("ElectronsEtaVec", &ElectronsEtaVec, &b_ElectronsEtaVec);
   fChain->SetBranchAddress("ElectronsPhiVec", &ElectronsPhiVec, &b_ElectronsPhiVec);
   fChain->SetBranchAddress("ElectronsNum", &ElectronsNum, &b_ElectronsNum);
   fChain->SetBranchAddress("ElectronsE", ElectronsE, &b_ElectronsE);
   fChain->SetBranchAddress("ElectronsTLorentzVector", ElectronsTLorentzVector, &b_ElectronsTLorentzVector);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoPtVec", &IsolatedElectronTracksVetoPtVec, &b_IsolatedElectronTracksVetoPtVec);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoEtaVec", &IsolatedElectronTracksVetoEtaVec, &b_IsolatedElectronTracksVetoEtaVec);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoPhiVec", &IsolatedElectronTracksVetoPhiVec, &b_IsolatedElectronTracksVetoPhiVec);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoNum", &IsolatedElectronTracksVetoNum, &b_IsolatedElectronTracksVetoNum);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoE", IsolatedElectronTracksVetoE, &b_IsolatedElectronTracksVetoE);
   fChain->SetBranchAddress("IsolatedElectronTracksVetoTLorentzVector", IsolatedElectronTracksVetoTLorentzVector, &b_IsolatedElectronTracksVetoTLorentzVector);
   fChain->SetBranchAddress("IsolatedElectronTracksVeto_MT", IsolatedElectronTracksVeto_MT, &b_IsolatedElectronTracksVeto_MT);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoPtVec", &IsolatedMuonTracksVetoPtVec, &b_IsolatedMuonTracksVetoPtVec);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoEtaVec", &IsolatedMuonTracksVetoEtaVec, &b_IsolatedMuonTracksVetoEtaVec);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoPhiVec", &IsolatedMuonTracksVetoPhiVec, &b_IsolatedMuonTracksVetoPhiVec);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoNum", &IsolatedMuonTracksVetoNum, &b_IsolatedMuonTracksVetoNum);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoE", IsolatedMuonTracksVetoE, &b_IsolatedMuonTracksVetoE);
   fChain->SetBranchAddress("IsolatedMuonTracksVetoTLorentzVector", IsolatedMuonTracksVetoTLorentzVector, &b_IsolatedMuonTracksVetoTLorentzVector);
   fChain->SetBranchAddress("IsolatedMuonTracksVeto_MT_1", IsolatedMuonTracksVeto_MT_1, &b_IsolatedMuonTracksVeto_MT_1);
   fChain->SetBranchAddress("IsolatedPionTracksVetoPtVec", &IsolatedPionTracksVetoPtVec, &b_IsolatedPionTracksVetoPtVec);
   fChain->SetBranchAddress("IsolatedPionTracksVetoEtaVec", &IsolatedPionTracksVetoEtaVec, &b_IsolatedPionTracksVetoEtaVec);
   fChain->SetBranchAddress("IsolatedPionTracksVetoPhiVec", &IsolatedPionTracksVetoPhiVec, &b_IsolatedPionTracksVetoPhiVec);
   fChain->SetBranchAddress("IsolatedPionTracksVetoNum", &IsolatedPionTracksVetoNum, &b_IsolatedPionTracksVetoNum);
   fChain->SetBranchAddress("IsolatedPionTracksVetoE", IsolatedPionTracksVetoE, &b_IsolatedPionTracksVetoE);
   fChain->SetBranchAddress("IsolatedPionTracksVetoTLorentzVector", IsolatedPionTracksVetoTLorentzVector, &b_IsolatedPionTracksVetoTLorentzVector);
   fChain->SetBranchAddress("IsolatedPionTracksVeto_MT_2", IsolatedPionTracksVeto_MT_2, &b_IsolatedPionTracksVeto_MT_2);
   fChain->SetBranchAddress("selectedIDIsoMuonsPtVec", &selectedIDIsoMuonsPtVec, &b_selectedIDIsoMuonsPtVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsEtaVec", &selectedIDIsoMuonsEtaVec, &b_selectedIDIsoMuonsEtaVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsPhiVec", &selectedIDIsoMuonsPhiVec, &b_selectedIDIsoMuonsPhiVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsNum", &selectedIDIsoMuonsNum, &b_selectedIDIsoMuonsNum);
   fChain->SetBranchAddress("selectedIDIsoMuonsE", selectedIDIsoMuonsE, &b_selectedIDIsoMuonsE);
   fChain->SetBranchAddress("selectedIDIsoMuonsTLorentzVector", selectedIDIsoMuonsTLorentzVector, &b_selectedIDIsoMuonsTLorentzVector);
   fChain->SetBranchAddress("selectedIDIsoMuons_MTW", selectedIDIsoMuons_MTW, &b_selectedIDIsoMuons_MTW);
   fChain->SetBranchAddress("selectedIDMuonsPtVec", &selectedIDMuonsPtVec, &b_selectedIDMuonsPtVec);
   fChain->SetBranchAddress("selectedIDMuonsEtaVec", &selectedIDMuonsEtaVec, &b_selectedIDMuonsEtaVec);
   fChain->SetBranchAddress("selectedIDMuonsPhiVec", &selectedIDMuonsPhiVec, &b_selectedIDMuonsPhiVec);
   fChain->SetBranchAddress("selectedIDMuonsNum", &selectedIDMuonsNum, &b_selectedIDMuonsNum);
   fChain->SetBranchAddress("selectedIDMuonsE", selectedIDMuonsE, &b_selectedIDMuonsE);
   fChain->SetBranchAddress("selectedIDMuonsTLorentzVector", selectedIDMuonsTLorentzVector, &b_selectedIDMuonsTLorentzVector);
   fChain->SetBranchAddress("selectedIDMuons_MTW_1", selectedIDMuons_MTW_1, &b_selectedIDMuons_MTW_1);
   fChain->SetBranchAddress("selectedIDIsoElectronsPtVec", &selectedIDIsoElectronsPtVec, &b_selectedIDIsoElectronsPtVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsEtaVec", &selectedIDIsoElectronsEtaVec, &b_selectedIDIsoElectronsEtaVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsPhiVec", &selectedIDIsoElectronsPhiVec, &b_selectedIDIsoElectronsPhiVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsNum", &selectedIDIsoElectronsNum, &b_selectedIDIsoElectronsNum);
   fChain->SetBranchAddress("selectedIDIsoElectronsE", selectedIDIsoElectronsE, &b_selectedIDIsoElectronsE);
   fChain->SetBranchAddress("selectedIDIsoElectronsTLorentzVector", selectedIDIsoElectronsTLorentzVector, &b_selectedIDIsoElectronsTLorentzVector);
   fChain->SetBranchAddress("selectedIDIsoElectrons_MTW_2", selectedIDIsoElectrons_MTW_2, &b_selectedIDIsoElectrons_MTW_2);
   fChain->SetBranchAddress("selectedIDElectronsPtVec", &selectedIDElectronsPtVec, &b_selectedIDElectronsPtVec);
   fChain->SetBranchAddress("selectedIDElectronsEtaVec", &selectedIDElectronsEtaVec, &b_selectedIDElectronsEtaVec);
   fChain->SetBranchAddress("selectedIDElectronsPhiVec", &selectedIDElectronsPhiVec, &b_selectedIDElectronsPhiVec);
   fChain->SetBranchAddress("selectedIDElectronsNum", &selectedIDElectronsNum, &b_selectedIDElectronsNum);
   fChain->SetBranchAddress("selectedIDElectronsE", selectedIDElectronsE, &b_selectedIDElectronsE);
   fChain->SetBranchAddress("selectedIDElectronsTLorentzVector", selectedIDElectronsTLorentzVector, &b_selectedIDElectronsTLorentzVector);
   fChain->SetBranchAddress("selectedIDElectrons_MTW_3", selectedIDElectrons_MTW_3, &b_selectedIDElectrons_MTW_3);
   fChain->SetBranchAddress("SelectedPFCandidatesPtVec", &SelectedPFCandidatesPtVec, &b_SelectedPFCandidatesPtVec);
   fChain->SetBranchAddress("SelectedPFCandidatesEtaVec", &SelectedPFCandidatesEtaVec, &b_SelectedPFCandidatesEtaVec);
   fChain->SetBranchAddress("SelectedPFCandidatesPhiVec", &SelectedPFCandidatesPhiVec, &b_SelectedPFCandidatesPhiVec);
   fChain->SetBranchAddress("SelectedPFCandidatesNum", &SelectedPFCandidatesNum, &b_SelectedPFCandidatesNum);
   fChain->SetBranchAddress("SelectedPFCandidatesE", SelectedPFCandidatesE, &b_SelectedPFCandidatesE);
   fChain->SetBranchAddress("SelectedPFCandidatesTLorentzVector", SelectedPFCandidatesTLorentzVector, &b_SelectedPFCandidatesTLorentzVector);
   fChain->SetBranchAddress("SelectedPFCandidates_Charge", SelectedPFCandidates_Charge, &b_SelectedPFCandidates_Charge);
   fChain->SetBranchAddress("SelectedPFCandidates_Typ", SelectedPFCandidates_Typ, &b_SelectedPFCandidates_Typ);
   fChain->SetBranchAddress("GenBosonPtVec", &GenBosonPtVec, &b_GenBosonPtVec);
   fChain->SetBranchAddress("GenBosonEtaVec", &GenBosonEtaVec, &b_GenBosonEtaVec);
   fChain->SetBranchAddress("GenBosonPhiVec", &GenBosonPhiVec, &b_GenBosonPhiVec);
   fChain->SetBranchAddress("GenBosonNum", &GenBosonNum, &b_GenBosonNum);
   fChain->SetBranchAddress("GenBosonE", GenBosonE, &b_GenBosonE);
   fChain->SetBranchAddress("GenBosonTLorentzVector", GenBosonTLorentzVector, &b_GenBosonTLorentzVector);
   fChain->SetBranchAddress("GenBoson_GenBosonPDGId", GenBoson_GenBosonPDGId, &b_GenBoson_GenBosonPDGId);
   fChain->SetBranchAddress("GenMuPtVec", &GenMuPtVec, &b_GenMuPtVec);
   fChain->SetBranchAddress("GenMuEtaVec", &GenMuEtaVec, &b_GenMuEtaVec);
   fChain->SetBranchAddress("GenMuPhiVec", &GenMuPhiVec, &b_GenMuPhiVec);
   fChain->SetBranchAddress("GenMuNum", &GenMuNum, &b_GenMuNum);
   fChain->SetBranchAddress("GenMuE", GenMuE, &b_GenMuE);
   fChain->SetBranchAddress("GenMuTLorentzVector", GenMuTLorentzVector, &b_GenMuTLorentzVector);
   fChain->SetBranchAddress("GenMu_GenMuFromTau", GenMu_GenMuFromTau, &b_GenMu_GenMuFromTau);
   fChain->SetBranchAddress("GenElecPtVec", &GenElecPtVec, &b_GenElecPtVec);
   fChain->SetBranchAddress("GenElecEtaVec", &GenElecEtaVec, &b_GenElecEtaVec);
   fChain->SetBranchAddress("GenElecPhiVec", &GenElecPhiVec, &b_GenElecPhiVec);
   fChain->SetBranchAddress("GenElecNum", &GenElecNum, &b_GenElecNum);
   fChain->SetBranchAddress("GenElecE", GenElecE, &b_GenElecE);
   fChain->SetBranchAddress("GenElecTLorentzVector", GenElecTLorentzVector, &b_GenElecTLorentzVector);
   fChain->SetBranchAddress("GenElec_GenElecFromTau", GenElec_GenElecFromTau, &b_GenElec_GenElecFromTau);
   fChain->SetBranchAddress("GenTauPtVec", &GenTauPtVec, &b_GenTauPtVec);
   fChain->SetBranchAddress("GenTauEtaVec", &GenTauEtaVec, &b_GenTauEtaVec);
   fChain->SetBranchAddress("GenTauPhiVec", &GenTauPhiVec, &b_GenTauPhiVec);
   fChain->SetBranchAddress("GenTauNum", &GenTauNum, &b_GenTauNum);
   fChain->SetBranchAddress("GenTauE", GenTauE, &b_GenTauE);
   fChain->SetBranchAddress("GenTauTLorentzVector", GenTauTLorentzVector, &b_GenTauTLorentzVector);
   fChain->SetBranchAddress("GenTau_GenTauHad", GenTau_GenTauHad, &b_GenTau_GenTauHad);
   fChain->SetBranchAddress("TauDecayCandsPtVec", &TauDecayCandsPtVec, &b_TauDecayCandsPtVec);
   fChain->SetBranchAddress("TauDecayCandsEtaVec", &TauDecayCandsEtaVec, &b_TauDecayCandsEtaVec);
   fChain->SetBranchAddress("TauDecayCandsPhiVec", &TauDecayCandsPhiVec, &b_TauDecayCandsPhiVec);
   fChain->SetBranchAddress("TauDecayCandsNum", &TauDecayCandsNum, &b_TauDecayCandsNum);
   fChain->SetBranchAddress("TauDecayCandsE", TauDecayCandsE, &b_TauDecayCandsE);
   fChain->SetBranchAddress("TauDecayCandsTLorentzVector", TauDecayCandsTLorentzVector, &b_TauDecayCandsTLorentzVector);
   fChain->SetBranchAddress("TauDecayCands_pdgID", TauDecayCands_pdgID, &b_TauDecayCands_pdgID);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoPtVec", &selectedIDIsoMuonsNoMiniIsoPtVec, &b_selectedIDIsoMuonsNoMiniIsoPtVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoEtaVec", &selectedIDIsoMuonsNoMiniIsoEtaVec, &b_selectedIDIsoMuonsNoMiniIsoEtaVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoPhiVec", &selectedIDIsoMuonsNoMiniIsoPhiVec, &b_selectedIDIsoMuonsNoMiniIsoPhiVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoNum", &selectedIDIsoMuonsNoMiniIsoNum, &b_selectedIDIsoMuonsNoMiniIsoNum);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoE", selectedIDIsoMuonsNoMiniIsoE, &b_selectedIDIsoMuonsNoMiniIsoE);
   fChain->SetBranchAddress("selectedIDIsoMuonsNoMiniIsoTLorentzVector", selectedIDIsoMuonsNoMiniIsoTLorentzVector, &b_selectedIDIsoMuonsNoMiniIsoTLorentzVector);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoPtVec", &selectedIDIsoElectronsNoMiniIsoPtVec, &b_selectedIDIsoElectronsNoMiniIsoPtVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoEtaVec", &selectedIDIsoElectronsNoMiniIsoEtaVec, &b_selectedIDIsoElectronsNoMiniIsoEtaVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoPhiVec", &selectedIDIsoElectronsNoMiniIsoPhiVec, &b_selectedIDIsoElectronsNoMiniIsoPhiVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoNum", &selectedIDIsoElectronsNoMiniIsoNum, &b_selectedIDIsoElectronsNoMiniIsoNum);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoE", selectedIDIsoElectronsNoMiniIsoE, &b_selectedIDIsoElectronsNoMiniIsoE);
   fChain->SetBranchAddress("selectedIDIsoElectronsNoMiniIsoTLorentzVector", selectedIDIsoElectronsNoMiniIsoTLorentzVector, &b_selectedIDIsoElectronsNoMiniIsoTLorentzVector);
   fChain->SetBranchAddress("JetsPtVec", &JetsPtVec, &b_JetsPtVec);
   fChain->SetBranchAddress("JetsEtaVec", &JetsEtaVec, &b_JetsEtaVec);
   fChain->SetBranchAddress("JetsPhiVec", &JetsPhiVec, &b_JetsPhiVec);
   fChain->SetBranchAddress("JetsNum", &JetsNum, &b_JetsNum);
   fChain->SetBranchAddress("JetsE", JetsE, &b_JetsE);
   fChain->SetBranchAddress("JetsTLorentzVector", JetsTLorentzVector, &b_JetsTLorentzVector);
   fChain->SetBranchAddress("Jets_bDiscriminator", Jets_bDiscriminator, &b_Jets_bDiscriminator);
   fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
   fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
   fChain->SetBranchAddress("Jets_electronMultiplicity", Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
   fChain->SetBranchAddress("Jets_jetArea", Jets_jetArea, &b_Jets_jetArea);
   fChain->SetBranchAddress("Jets_muonEnergyFraction", Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
   fChain->SetBranchAddress("Jets_muonMultiplicity", Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
   fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
   fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
   fChain->SetBranchAddress("Jets_photonEnergyFraction", Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
   fChain->SetBranchAddress("Jets_photonMultiplicity", Jets_photonMultiplicity, &b_Jets_photonMultiplicity);
   fChain->SetBranchAddress("slimmedElectronsPtVec", &slimmedElectronsPtVec, &b_slimmedElectronsPtVec);
   fChain->SetBranchAddress("slimmedElectronsEtaVec", &slimmedElectronsEtaVec, &b_slimmedElectronsEtaVec);
   fChain->SetBranchAddress("slimmedElectronsPhiVec", &slimmedElectronsPhiVec, &b_slimmedElectronsPhiVec);
   fChain->SetBranchAddress("slimmedElectronsNum", &slimmedElectronsNum, &b_slimmedElectronsNum);
   fChain->SetBranchAddress("slimmedElectronsE", slimmedElectronsE, &b_slimmedElectronsE);
   fChain->SetBranchAddress("slimmedElectronsTLorentzVector", slimmedElectronsTLorentzVector, &b_slimmedElectronsTLorentzVector);
   fChain->SetBranchAddress("slimmedMuonsPtVec", &slimmedMuonsPtVec, &b_slimmedMuonsPtVec);
   fChain->SetBranchAddress("slimmedMuonsEtaVec", &slimmedMuonsEtaVec, &b_slimmedMuonsEtaVec);
   fChain->SetBranchAddress("slimmedMuonsPhiVec", &slimmedMuonsPhiVec, &b_slimmedMuonsPhiVec);
   fChain->SetBranchAddress("slimmedMuonsNum", &slimmedMuonsNum, &b_slimmedMuonsNum);
   fChain->SetBranchAddress("slimmedMuonsE", slimmedMuonsE, &b_slimmedMuonsE);
   fChain->SetBranchAddress("slimmedMuonsTLorentzVector", slimmedMuonsTLorentzVector, &b_slimmedMuonsTLorentzVector);
   fChain->SetBranchAddress("SelectedPFElecCandidatesPtVec", &SelectedPFElecCandidatesPtVec, &b_SelectedPFElecCandidatesPtVec);
   fChain->SetBranchAddress("SelectedPFElecCandidatesEtaVec", &SelectedPFElecCandidatesEtaVec, &b_SelectedPFElecCandidatesEtaVec);
   fChain->SetBranchAddress("SelectedPFElecCandidatesPhiVec", &SelectedPFElecCandidatesPhiVec, &b_SelectedPFElecCandidatesPhiVec);
   fChain->SetBranchAddress("SelectedPFElecCandidatesNum", &SelectedPFElecCandidatesNum, &b_SelectedPFElecCandidatesNum);
   fChain->SetBranchAddress("SelectedPFElecCandidatesE", SelectedPFElecCandidatesE, &b_SelectedPFElecCandidatesE);
   fChain->SetBranchAddress("SelectedPFElecCandidatesTLorentzVector", SelectedPFElecCandidatesTLorentzVector, &b_SelectedPFElecCandidatesTLorentzVector);
   fChain->SetBranchAddress("SelectedPFMuCandidatesPtVec", &SelectedPFMuCandidatesPtVec, &b_SelectedPFMuCandidatesPtVec);
   fChain->SetBranchAddress("SelectedPFMuCandidatesEtaVec", &SelectedPFMuCandidatesEtaVec, &b_SelectedPFMuCandidatesEtaVec);
   fChain->SetBranchAddress("SelectedPFMuCandidatesPhiVec", &SelectedPFMuCandidatesPhiVec, &b_SelectedPFMuCandidatesPhiVec);
   fChain->SetBranchAddress("SelectedPFMuCandidatesNum", &SelectedPFMuCandidatesNum, &b_SelectedPFMuCandidatesNum);
   fChain->SetBranchAddress("SelectedPFMuCandidatesE", SelectedPFMuCandidatesE, &b_SelectedPFMuCandidatesE);
   fChain->SetBranchAddress("SelectedPFMuCandidatesTLorentzVector", SelectedPFMuCandidatesTLorentzVector, &b_SelectedPFMuCandidatesTLorentzVector);
   fChain->SetBranchAddress("SelectedPFPionCandidatesPtVec", &SelectedPFPionCandidatesPtVec, &b_SelectedPFPionCandidatesPtVec);
   fChain->SetBranchAddress("SelectedPFPionCandidatesEtaVec", &SelectedPFPionCandidatesEtaVec, &b_SelectedPFPionCandidatesEtaVec);
   fChain->SetBranchAddress("SelectedPFPionCandidatesPhiVec", &SelectedPFPionCandidatesPhiVec, &b_SelectedPFPionCandidatesPhiVec);
   fChain->SetBranchAddress("SelectedPFPionCandidatesNum", &SelectedPFPionCandidatesNum, &b_SelectedPFPionCandidatesNum);
   fChain->SetBranchAddress("SelectedPFPionCandidatesE", SelectedPFPionCandidatesE, &b_SelectedPFPionCandidatesE);
   fChain->SetBranchAddress("SelectedPFPionCandidatesTLorentzVector", SelectedPFPionCandidatesTLorentzVector, &b_SelectedPFPionCandidatesTLorentzVector);
   fChain->SetBranchAddress("slimJetPtVec", &slimJetPtVec, &b_slimJetPtVec);
   fChain->SetBranchAddress("slimJetEtaVec", &slimJetEtaVec, &b_slimJetEtaVec);
   fChain->SetBranchAddress("slimJetPhiVec", &slimJetPhiVec, &b_slimJetPhiVec);
   fChain->SetBranchAddress("slimJetNum", &slimJetNum, &b_slimJetNum);
   fChain->SetBranchAddress("slimJetE", slimJetE, &b_slimJetE);
   fChain->SetBranchAddress("slimJetTLorentzVector", slimJetTLorentzVector, &b_slimJetTLorentzVector);
   fChain->SetBranchAddress("slimJet_slimJetID", slimJet_slimJetID, &b_slimJet_slimJetID);
   fChain->SetBranchAddress("GenTauNuPtVec", &GenTauNuPtVec, &b_GenTauNuPtVec);
   fChain->SetBranchAddress("GenTauNuEtaVec", &GenTauNuEtaVec, &b_GenTauNuEtaVec);
   fChain->SetBranchAddress("GenTauNuPhiVec", &GenTauNuPhiVec, &b_GenTauNuPhiVec);
   fChain->SetBranchAddress("GenTauNuNum", &GenTauNuNum, &b_GenTauNuNum);
   fChain->SetBranchAddress("GenTauNuE", GenTauNuE, &b_GenTauNuE);
   fChain->SetBranchAddress("GenTauNuTLorentzVector", GenTauNuTLorentzVector, &b_GenTauNuTLorentzVector);
   fChain->SetBranchAddress("GenTauNu_TauNuMomPt", GenTauNu_TauNuMomPt, &b_GenTauNu_TauNuMomPt);
   fChain->SetBranchAddress("genParticles_PDGid", &genParticles_PDGid, &b_genParticles_PDGid);
   fChain->SetBranchAddress("PassTrigger", &PassTrigger, &b_PassTrigger);
   fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
   fChain->SetBranchAddress("genParticles", &genParticles, &b_genParticles);
   fChain->SetBranchAddress("bestPhoton", &bestPhoton, &b_bestPhoton);
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
