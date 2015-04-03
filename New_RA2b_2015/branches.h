//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 31 09:51:27 2015 by ROOT version 5.34/25
// from TTree PreSelection/PreSelection
// found on file: /home/borzou/MiniAOD/CMSSW_7_2_3_patch1/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection.root
//////////////////////////////////////////////////////////

#ifndef branches_h
#define branches_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "/build/bellenot/source/root_v5.34.25/root/cint/cint/lib/prec_stl/vector"

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
   Int_t           isoTracks;
   Int_t           Leptons;
   Int_t           LeptonsNoMiniIsolation;
   Int_t           NJets;
   Int_t           BTags;
   Float_t         Weight;
   Float_t         HT;
   Float_t         MHT;
   Float_t         DeltaPhi1;
   Float_t         DeltaPhi2;
   Float_t         DeltaPhi3;
   Float_t         minDeltaPhiN;
   Float_t         DeltaPhiN1;
   Float_t         DeltaPhiN2;
   Float_t         DeltaPhiN3;
   Float_t         METPt;
   Float_t         METPhi;
   vector<double>  *testVec;
   vector<double>  *TagIsoMuonPtVec;
   vector<double>  *TagIsoMuonEtaVec;
   vector<double>  *TagIsoMuonPhiVec;
   UShort_t        TagIsoMuonNum;
   Float_t         TagIsoMuonE[1];   //[TagIsoMuonNum]
   Float_t         TagIsoMuonTLorentzVector[1];   //[TagIsoMuonNum]
   vector<double>  *ProbeIsoMuonPtVec;
   vector<double>  *ProbeIsoMuonEtaVec;
   vector<double>  *ProbeIsoMuonPhiVec;
   UShort_t        ProbeIsoMuonNum;
   Float_t         ProbeIsoMuonE[1];   //[ProbeIsoMuonNum]
   Float_t         ProbeIsoMuonTLorentzVector[1];   //[ProbeIsoMuonNum]
   Float_t         ProbeIsoMuon_InvariantMass[1];   //[ProbeIsoMuonNum]
   Int_t           ProbeIsoMuon_PassingOrFail[1];   //[ProbeIsoMuonNum]
   vector<double>  *TagIDMuonPtVec;
   vector<double>  *TagIDMuonEtaVec;
   vector<double>  *TagIDMuonPhiVec;
   UShort_t        TagIDMuonNum;
   Float_t         TagIDMuonE[1];   //[TagIDMuonNum]
   Float_t         TagIDMuonTLorentzVector[1];   //[TagIDMuonNum]
   vector<double>  *ProbeIDMuonPtVec;
   vector<double>  *ProbeIDMuonEtaVec;
   vector<double>  *ProbeIDMuonPhiVec;
   UShort_t        ProbeIDMuonNum;
   Float_t         ProbeIDMuonE[3];   //[ProbeIDMuonNum]
   Float_t         ProbeIDMuonTLorentzVector[3];   //[ProbeIDMuonNum]
   Float_t         ProbeIDMuon_InvariantMass_1[3];   //[ProbeIDMuonNum]
   Int_t           ProbeIDMuon_PassingOrFail_1[3];   //[ProbeIDMuonNum]
   vector<double>  *TagIsoElectronPtVec;
   vector<double>  *TagIsoElectronEtaVec;
   vector<double>  *TagIsoElectronPhiVec;
   UShort_t        TagIsoElectronNum;
   Float_t         TagIsoElectronE[1];   //[TagIsoElectronNum]
   Float_t         TagIsoElectronTLorentzVector[1];   //[TagIsoElectronNum]
   vector<double>  *ProbeIsoElectronPtVec;
   vector<double>  *ProbeIsoElectronEtaVec;
   vector<double>  *ProbeIsoElectronPhiVec;
   UShort_t        ProbeIsoElectronNum;
   Float_t         ProbeIsoElectronE[1];   //[ProbeIsoElectronNum]
   Float_t         ProbeIsoElectronTLorentzVector[1];   //[ProbeIsoElectronNum]
   Float_t         ProbeIsoElectron_InvariantMass_2[1];   //[ProbeIsoElectronNum]
   Int_t           ProbeIsoElectron_PassingOrFail_2[1];   //[ProbeIsoElectronNum]
   vector<double>  *TagIDElectronPtVec;
   vector<double>  *TagIDElectronEtaVec;
   vector<double>  *TagIDElectronPhiVec;
   UShort_t        TagIDElectronNum;
   Float_t         TagIDElectronE[1];   //[TagIDElectronNum]
   Float_t         TagIDElectronTLorentzVector[1];   //[TagIDElectronNum]
   vector<double>  *ProbeIDElectronPtVec;
   vector<double>  *ProbeIDElectronEtaVec;
   vector<double>  *ProbeIDElectronPhiVec;
   UShort_t        ProbeIDElectronNum;
   Float_t         ProbeIDElectronE[2];   //[ProbeIDElectronNum]
   Float_t         ProbeIDElectronTLorentzVector[2];   //[ProbeIDElectronNum]
   Float_t         ProbeIDElectron_InvariantMass_3[2];   //[ProbeIDElectronNum]
   Int_t           ProbeIDElectron_PassingOrFail_3[2];   //[ProbeIDElectronNum]
   vector<double>  *JetsPtVec;
   vector<double>  *JetsEtaVec;
   vector<double>  *JetsPhiVec;
   UShort_t        JetsNum;
   Float_t         JetsE[8];   //[JetsNum]
   Float_t         JetsTLorentzVector[8];   //[JetsNum]
   Float_t         Jets_bDiscriminator[8];   //[JetsNum]
   Float_t         Jets_chargedEmEnergyFraction[8];   //[JetsNum]
   Float_t         Jets_chargedHadronEnergyFraction[8];   //[JetsNum]
   Int_t           Jets_chargedHadronMultiplicity[8];   //[JetsNum]
   Int_t           Jets_electronMultiplicity[8];   //[JetsNum]
   Float_t         Jets_jetArea[8];   //[JetsNum]
   Float_t         Jets_muonEnergyFraction[8];   //[JetsNum]
   Int_t           Jets_muonMultiplicity[8];   //[JetsNum]
   Float_t         Jets_neutralEmEnergyFraction[8];   //[JetsNum]
   Int_t           Jets_neutralHadronMultiplicity[8];   //[JetsNum]
   Float_t         Jets_photonEnergyFraction[8];   //[JetsNum]
   Int_t           Jets_photonMultiplicity[8];   //[JetsNum]
   vector<double>  *SelectedPFCandidatesPtVec;
   vector<double>  *SelectedPFCandidatesEtaVec;
   vector<double>  *SelectedPFCandidatesPhiVec;
   UShort_t        SelectedPFCandidatesNum;
   Float_t         SelectedPFCandidatesE[81];   //[SelectedPFCandidatesNum]
   Float_t         SelectedPFCandidatesTLorentzVector[81];   //[SelectedPFCandidatesNum]
   Int_t           SelectedPFCandidates_Charge[81];   //[SelectedPFCandidatesNum]
   Int_t           SelectedPFCandidates_Typ[81];   //[SelectedPFCandidatesNum]
   vector<double>  *MuonsPtVec;
   vector<double>  *MuonsEtaVec;
   vector<double>  *MuonsPhiVec;
   UShort_t        MuonsNum;
   Float_t         MuonsE[1];   //[MuonsNum]
   Float_t         MuonsTLorentzVector[1];   //[MuonsNum]
   vector<double>  *ElectronsPtVec;
   vector<double>  *ElectronsEtaVec;
   vector<double>  *ElectronsPhiVec;
   UShort_t        ElectronsNum;
   Float_t         ElectronsE[2];   //[ElectronsNum]
   Float_t         ElectronsTLorentzVector[2];   //[ElectronsNum]
   vector<double>  *IsolatedTracksPtVec;
   vector<double>  *IsolatedTracksEtaVec;
   vector<double>  *IsolatedTracksPhiVec;
   UShort_t        IsolatedTracksNum;
   Float_t         IsolatedTracksE[3];   //[IsolatedTracksNum]
   Float_t         IsolatedTracksTLorentzVector[3];   //[IsolatedTracksNum]
   vector<double>  *selectedIDIsoMuonsPtVec;
   vector<double>  *selectedIDIsoMuonsEtaVec;
   vector<double>  *selectedIDIsoMuonsPhiVec;
   UShort_t        selectedIDIsoMuonsNum;
   Float_t         selectedIDIsoMuonsE[1];   //[selectedIDIsoMuonsNum]
   Float_t         selectedIDIsoMuonsTLorentzVector[1];   //[selectedIDIsoMuonsNum]
   vector<double>  *selectedIDMuonsPtVec;
   vector<double>  *selectedIDMuonsEtaVec;
   vector<double>  *selectedIDMuonsPhiVec;
   UShort_t        selectedIDMuonsNum;
   Float_t         selectedIDMuonsE[1];   //[selectedIDMuonsNum]
   Float_t         selectedIDMuonsTLorentzVector[1];   //[selectedIDMuonsNum]
   vector<double>  *selectedIDIsoElectronsPtVec;
   vector<double>  *selectedIDIsoElectronsEtaVec;
   vector<double>  *selectedIDIsoElectronsPhiVec;
   UShort_t        selectedIDIsoElectronsNum;
   Float_t         selectedIDIsoElectronsE[2];   //[selectedIDIsoElectronsNum]
   Float_t         selectedIDIsoElectronsTLorentzVector[2];   //[selectedIDIsoElectronsNum]
   vector<double>  *selectedIDElectronsPtVec;
   vector<double>  *selectedIDElectronsEtaVec;
   vector<double>  *selectedIDElectronsPhiVec;
   UShort_t        selectedIDElectronsNum;
   Float_t         selectedIDElectronsE[2];   //[selectedIDElectronsNum]
   Float_t         selectedIDElectronsTLorentzVector[2];   //[selectedIDElectronsNum]
   vector<double>  *SelectedPFCandidates_1PtVec;
   vector<double>  *SelectedPFCandidates_1EtaVec;
   vector<double>  *SelectedPFCandidates_1PhiVec;
   UShort_t        SelectedPFCandidates_1Num;
   Float_t         SelectedPFCandidates_1E[81];   //[SelectedPFCandidates_1Num]
   Float_t         SelectedPFCandidates_1TLorentzVector[81];   //[SelectedPFCandidates_1Num]
   Int_t           SelectedPFCandidates_1_Charge_1[81];   //[SelectedPFCandidates_1Num]
   Int_t           SelectedPFCandidates_1_Typ_1[81];   //[SelectedPFCandidates_1Num]
   vector<double>  *GenBosonPtVec;
   vector<double>  *GenBosonEtaVec;
   vector<double>  *GenBosonPhiVec;
   UShort_t        GenBosonNum;
   Float_t         GenBosonE[2];   //[GenBosonNum]
   Float_t         GenBosonTLorentzVector[2];   //[GenBosonNum]
   Int_t           GenBoson_GenBosonPDGId[2];   //[GenBosonNum]
   vector<double>  *GenMuPtVec;
   vector<double>  *GenMuEtaVec;
   vector<double>  *GenMuPhiVec;
   UShort_t        GenMuNum;
   Float_t         GenMuE[1];   //[GenMuNum]
   Float_t         GenMuTLorentzVector[1];   //[GenMuNum]
   Int_t           GenMu_GenMuFromTau[1];   //[GenMuNum]
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
   Float_t         GenTauE[1];   //[GenTauNum]
   Float_t         GenTauTLorentzVector[1];   //[GenTauNum]
   Int_t           GenTau_GenTauHad[1];   //[GenTauNum]
   vector<double>  *selectedIDIsoMuonsNoMiniIsoPtVec;
   vector<double>  *selectedIDIsoMuonsNoMiniIsoEtaVec;
   vector<double>  *selectedIDIsoMuonsNoMiniIsoPhiVec;
   UShort_t        selectedIDIsoMuonsNoMiniIsoNum;
   Float_t         selectedIDIsoMuonsNoMiniIsoE[1];   //[selectedIDIsoMuonsNoMiniIsoNum]
   Float_t         selectedIDIsoMuonsNoMiniIsoTLorentzVector[1];   //[selectedIDIsoMuonsNoMiniIsoNum]
   vector<double>  *selectedIDIsoElectronsNoMiniIsoPtVec;
   vector<double>  *selectedIDIsoElectronsNoMiniIsoEtaVec;
   vector<double>  *selectedIDIsoElectronsNoMiniIsoPhiVec;
   UShort_t        selectedIDIsoElectronsNoMiniIsoNum;
   Float_t         selectedIDIsoElectronsNoMiniIsoE[1];   //[selectedIDIsoElectronsNoMiniIsoNum]
   Float_t         selectedIDIsoElectronsNoMiniIsoTLorentzVector[1];   //[selectedIDIsoElectronsNoMiniIsoNum]
   vector<double>  *Jets_1PtVec;
   vector<double>  *Jets_1EtaVec;
   vector<double>  *Jets_1PhiVec;
   UShort_t        Jets_1Num;
   Float_t         Jets_1E[8];   //[Jets_1Num]
   Float_t         Jets_1TLorentzVector[8];   //[Jets_1Num]
   Float_t         Jets_1_bDiscriminator_1[8];   //[Jets_1Num]
   Float_t         Jets_1_chargedEmEnergyFraction_1[8];   //[Jets_1Num]
   Float_t         Jets_1_chargedHadronEnergyFraction_1[8];   //[Jets_1Num]
   Int_t           Jets_1_chargedHadronMultiplicity_1[8];   //[Jets_1Num]
   Int_t           Jets_1_electronMultiplicity_1[8];   //[Jets_1Num]
   Float_t         Jets_1_jetArea_1[8];   //[Jets_1Num]
   Float_t         Jets_1_muonEnergyFraction_1[8];   //[Jets_1Num]
   Int_t           Jets_1_muonMultiplicity_1[8];   //[Jets_1Num]
   Float_t         Jets_1_neutralEmEnergyFraction_1[8];   //[Jets_1Num]
   Int_t           Jets_1_neutralHadronMultiplicity_1[8];   //[Jets_1Num]
   Float_t         Jets_1_photonEnergyFraction_1[8];   //[Jets_1Num]
   Int_t           Jets_1_photonMultiplicity_1[8];   //[Jets_1Num]

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_isoTracks;   //!
   TBranch        *b_Leptons;   //!
   TBranch        *b_LeptonsNoMiniIsolation;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_BTags;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_minDeltaPhiN;   //!
   TBranch        *b_DeltaPhiN1;   //!
   TBranch        *b_DeltaPhiN2;   //!
   TBranch        *b_DeltaPhiN3;   //!
   TBranch        *b_METPt;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_testVec;   //!
   TBranch        *b_TagIsoMuonPtVec;   //!
   TBranch        *b_TagIsoMuonEtaVec;   //!
   TBranch        *b_TagIsoMuonPhiVec;   //!
   TBranch        *b_TagIsoMuonNum;   //!
   TBranch        *b_TagIsoMuonE;   //!
   TBranch        *b_TagIsoMuonTLorentzVector;   //!
   TBranch        *b_ProbeIsoMuonPtVec;   //!
   TBranch        *b_ProbeIsoMuonEtaVec;   //!
   TBranch        *b_ProbeIsoMuonPhiVec;   //!
   TBranch        *b_ProbeIsoMuonNum;   //!
   TBranch        *b_ProbeIsoMuonE;   //!
   TBranch        *b_ProbeIsoMuonTLorentzVector;   //!
   TBranch        *b_ProbeIsoMuon_InvariantMass;   //!
   TBranch        *b_ProbeIsoMuon_PassingOrFail;   //!
   TBranch        *b_TagIDMuonPtVec;   //!
   TBranch        *b_TagIDMuonEtaVec;   //!
   TBranch        *b_TagIDMuonPhiVec;   //!
   TBranch        *b_TagIDMuonNum;   //!
   TBranch        *b_TagIDMuonE;   //!
   TBranch        *b_TagIDMuonTLorentzVector;   //!
   TBranch        *b_ProbeIDMuonPtVec;   //!
   TBranch        *b_ProbeIDMuonEtaVec;   //!
   TBranch        *b_ProbeIDMuonPhiVec;   //!
   TBranch        *b_ProbeIDMuonNum;   //!
   TBranch        *b_ProbeIDMuonE;   //!
   TBranch        *b_ProbeIDMuonTLorentzVector;   //!
   TBranch        *b_ProbeIDMuon_InvariantMass_1;   //!
   TBranch        *b_ProbeIDMuon_PassingOrFail_1;   //!
   TBranch        *b_TagIsoElectronPtVec;   //!
   TBranch        *b_TagIsoElectronEtaVec;   //!
   TBranch        *b_TagIsoElectronPhiVec;   //!
   TBranch        *b_TagIsoElectronNum;   //!
   TBranch        *b_TagIsoElectronE;   //!
   TBranch        *b_TagIsoElectronTLorentzVector;   //!
   TBranch        *b_ProbeIsoElectronPtVec;   //!
   TBranch        *b_ProbeIsoElectronEtaVec;   //!
   TBranch        *b_ProbeIsoElectronPhiVec;   //!
   TBranch        *b_ProbeIsoElectronNum;   //!
   TBranch        *b_ProbeIsoElectronE;   //!
   TBranch        *b_ProbeIsoElectronTLorentzVector;   //!
   TBranch        *b_ProbeIsoElectron_InvariantMass_2;   //!
   TBranch        *b_ProbeIsoElectron_PassingOrFail_2;   //!
   TBranch        *b_TagIDElectronPtVec;   //!
   TBranch        *b_TagIDElectronEtaVec;   //!
   TBranch        *b_TagIDElectronPhiVec;   //!
   TBranch        *b_TagIDElectronNum;   //!
   TBranch        *b_TagIDElectronE;   //!
   TBranch        *b_TagIDElectronTLorentzVector;   //!
   TBranch        *b_ProbeIDElectronPtVec;   //!
   TBranch        *b_ProbeIDElectronEtaVec;   //!
   TBranch        *b_ProbeIDElectronPhiVec;   //!
   TBranch        *b_ProbeIDElectronNum;   //!
   TBranch        *b_ProbeIDElectronE;   //!
   TBranch        *b_ProbeIDElectronTLorentzVector;   //!
   TBranch        *b_ProbeIDElectron_InvariantMass_3;   //!
   TBranch        *b_ProbeIDElectron_PassingOrFail_3;   //!
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
   TBranch        *b_SelectedPFCandidatesPtVec;   //!
   TBranch        *b_SelectedPFCandidatesEtaVec;   //!
   TBranch        *b_SelectedPFCandidatesPhiVec;   //!
   TBranch        *b_SelectedPFCandidatesNum;   //!
   TBranch        *b_SelectedPFCandidatesE;   //!
   TBranch        *b_SelectedPFCandidatesTLorentzVector;   //!
   TBranch        *b_SelectedPFCandidates_Charge;   //!
   TBranch        *b_SelectedPFCandidates_Typ;   //!
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
   TBranch        *b_IsolatedTracksPtVec;   //!
   TBranch        *b_IsolatedTracksEtaVec;   //!
   TBranch        *b_IsolatedTracksPhiVec;   //!
   TBranch        *b_IsolatedTracksNum;   //!
   TBranch        *b_IsolatedTracksE;   //!
   TBranch        *b_IsolatedTracksTLorentzVector;   //!
   TBranch        *b_selectedIDIsoMuonsPtVec;   //!
   TBranch        *b_selectedIDIsoMuonsEtaVec;   //!
   TBranch        *b_selectedIDIsoMuonsPhiVec;   //!
   TBranch        *b_selectedIDIsoMuonsNum;   //!
   TBranch        *b_selectedIDIsoMuonsE;   //!
   TBranch        *b_selectedIDIsoMuonsTLorentzVector;   //!
   TBranch        *b_selectedIDMuonsPtVec;   //!
   TBranch        *b_selectedIDMuonsEtaVec;   //!
   TBranch        *b_selectedIDMuonsPhiVec;   //!
   TBranch        *b_selectedIDMuonsNum;   //!
   TBranch        *b_selectedIDMuonsE;   //!
   TBranch        *b_selectedIDMuonsTLorentzVector;   //!
   TBranch        *b_selectedIDIsoElectronsPtVec;   //!
   TBranch        *b_selectedIDIsoElectronsEtaVec;   //!
   TBranch        *b_selectedIDIsoElectronsPhiVec;   //!
   TBranch        *b_selectedIDIsoElectronsNum;   //!
   TBranch        *b_selectedIDIsoElectronsE;   //!
   TBranch        *b_selectedIDIsoElectronsTLorentzVector;   //!
   TBranch        *b_selectedIDElectronsPtVec;   //!
   TBranch        *b_selectedIDElectronsEtaVec;   //!
   TBranch        *b_selectedIDElectronsPhiVec;   //!
   TBranch        *b_selectedIDElectronsNum;   //!
   TBranch        *b_selectedIDElectronsE;   //!
   TBranch        *b_selectedIDElectronsTLorentzVector;   //!
   TBranch        *b_SelectedPFCandidates_1PtVec;   //!
   TBranch        *b_SelectedPFCandidates_1EtaVec;   //!
   TBranch        *b_SelectedPFCandidates_1PhiVec;   //!
   TBranch        *b_SelectedPFCandidates_1Num;   //!
   TBranch        *b_SelectedPFCandidates_1E;   //!
   TBranch        *b_SelectedPFCandidates_1TLorentzVector;   //!
   TBranch        *b_SelectedPFCandidates_1_Charge_1;   //!
   TBranch        *b_SelectedPFCandidates_1_Typ_1;   //!
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
   TBranch        *b_Jets_1PtVec;   //!
   TBranch        *b_Jets_1EtaVec;   //!
   TBranch        *b_Jets_1PhiVec;   //!
   TBranch        *b_Jets_1Num;   //!
   TBranch        *b_Jets_1E;   //!
   TBranch        *b_Jets_1TLorentzVector;   //!
   TBranch        *b_Jets_1_bDiscriminator_1;   //!
   TBranch        *b_Jets_1_chargedEmEnergyFraction_1;   //!
   TBranch        *b_Jets_1_chargedHadronEnergyFraction_1;   //!
   TBranch        *b_Jets_1_chargedHadronMultiplicity_1;   //!
   TBranch        *b_Jets_1_electronMultiplicity_1;   //!
   TBranch        *b_Jets_1_jetArea_1;   //!
   TBranch        *b_Jets_1_muonEnergyFraction_1;   //!
   TBranch        *b_Jets_1_muonMultiplicity_1;   //!
   TBranch        *b_Jets_1_neutralEmEnergyFraction_1;   //!
   TBranch        *b_Jets_1_neutralHadronMultiplicity_1;   //!
   TBranch        *b_Jets_1_photonEnergyFraction_1;   //!
   TBranch        *b_Jets_1_photonMultiplicity_1;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/borzou/MiniAOD/CMSSW_7_2_3_patch1/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/borzou/MiniAOD/CMSSW_7_2_3_patch1/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/borzou/MiniAOD/CMSSW_7_2_3_patch1/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection.root:/TreeMaker2");
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
   TagIsoMuonPtVec = 0;
   TagIsoMuonEtaVec = 0;
   TagIsoMuonPhiVec = 0;
   ProbeIsoMuonPtVec = 0;
   ProbeIsoMuonEtaVec = 0;
   ProbeIsoMuonPhiVec = 0;
   TagIDMuonPtVec = 0;
   TagIDMuonEtaVec = 0;
   TagIDMuonPhiVec = 0;
   ProbeIDMuonPtVec = 0;
   ProbeIDMuonEtaVec = 0;
   ProbeIDMuonPhiVec = 0;
   TagIsoElectronPtVec = 0;
   TagIsoElectronEtaVec = 0;
   TagIsoElectronPhiVec = 0;
   ProbeIsoElectronPtVec = 0;
   ProbeIsoElectronEtaVec = 0;
   ProbeIsoElectronPhiVec = 0;
   TagIDElectronPtVec = 0;
   TagIDElectronEtaVec = 0;
   TagIDElectronPhiVec = 0;
   ProbeIDElectronPtVec = 0;
   ProbeIDElectronEtaVec = 0;
   ProbeIDElectronPhiVec = 0;
   JetsPtVec = 0;
   JetsEtaVec = 0;
   JetsPhiVec = 0;
   SelectedPFCandidatesPtVec = 0;
   SelectedPFCandidatesEtaVec = 0;
   SelectedPFCandidatesPhiVec = 0;
   MuonsPtVec = 0;
   MuonsEtaVec = 0;
   MuonsPhiVec = 0;
   ElectronsPtVec = 0;
   ElectronsEtaVec = 0;
   ElectronsPhiVec = 0;
   IsolatedTracksPtVec = 0;
   IsolatedTracksEtaVec = 0;
   IsolatedTracksPhiVec = 0;
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
   SelectedPFCandidates_1PtVec = 0;
   SelectedPFCandidates_1EtaVec = 0;
   SelectedPFCandidates_1PhiVec = 0;
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
   selectedIDIsoMuonsNoMiniIsoPtVec = 0;
   selectedIDIsoMuonsNoMiniIsoEtaVec = 0;
   selectedIDIsoMuonsNoMiniIsoPhiVec = 0;
   selectedIDIsoElectronsNoMiniIsoPtVec = 0;
   selectedIDIsoElectronsNoMiniIsoEtaVec = 0;
   selectedIDIsoElectronsNoMiniIsoPhiVec = 0;
   Jets_1PtVec = 0;
   Jets_1EtaVec = 0;
   Jets_1PhiVec = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
   fChain->SetBranchAddress("isoTracks", &isoTracks, &b_isoTracks);
   fChain->SetBranchAddress("Leptons", &Leptons, &b_Leptons);
   fChain->SetBranchAddress("LeptonsNoMiniIsolation", &LeptonsNoMiniIsolation, &b_LeptonsNoMiniIsolation);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN, &b_minDeltaPhiN);
   fChain->SetBranchAddress("DeltaPhiN1", &DeltaPhiN1, &b_DeltaPhiN1);
   fChain->SetBranchAddress("DeltaPhiN2", &DeltaPhiN2, &b_DeltaPhiN2);
   fChain->SetBranchAddress("DeltaPhiN3", &DeltaPhiN3, &b_DeltaPhiN3);
   fChain->SetBranchAddress("METPt", &METPt, &b_METPt);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("testVec", &testVec, &b_testVec);
   fChain->SetBranchAddress("TagIsoMuonPtVec", &TagIsoMuonPtVec, &b_TagIsoMuonPtVec);
   fChain->SetBranchAddress("TagIsoMuonEtaVec", &TagIsoMuonEtaVec, &b_TagIsoMuonEtaVec);
   fChain->SetBranchAddress("TagIsoMuonPhiVec", &TagIsoMuonPhiVec, &b_TagIsoMuonPhiVec);
   fChain->SetBranchAddress("TagIsoMuonNum", &TagIsoMuonNum, &b_TagIsoMuonNum);
   fChain->SetBranchAddress("TagIsoMuonE", &TagIsoMuonE, &b_TagIsoMuonE);
   fChain->SetBranchAddress("TagIsoMuonTLorentzVector", &TagIsoMuonTLorentzVector, &b_TagIsoMuonTLorentzVector);
   fChain->SetBranchAddress("ProbeIsoMuonPtVec", &ProbeIsoMuonPtVec, &b_ProbeIsoMuonPtVec);
   fChain->SetBranchAddress("ProbeIsoMuonEtaVec", &ProbeIsoMuonEtaVec, &b_ProbeIsoMuonEtaVec);
   fChain->SetBranchAddress("ProbeIsoMuonPhiVec", &ProbeIsoMuonPhiVec, &b_ProbeIsoMuonPhiVec);
   fChain->SetBranchAddress("ProbeIsoMuonNum", &ProbeIsoMuonNum, &b_ProbeIsoMuonNum);
   fChain->SetBranchAddress("ProbeIsoMuonE", &ProbeIsoMuonE, &b_ProbeIsoMuonE);
   fChain->SetBranchAddress("ProbeIsoMuonTLorentzVector", &ProbeIsoMuonTLorentzVector, &b_ProbeIsoMuonTLorentzVector);
   fChain->SetBranchAddress("ProbeIsoMuon_InvariantMass", &ProbeIsoMuon_InvariantMass, &b_ProbeIsoMuon_InvariantMass);
   fChain->SetBranchAddress("ProbeIsoMuon_PassingOrFail", &ProbeIsoMuon_PassingOrFail, &b_ProbeIsoMuon_PassingOrFail);
   fChain->SetBranchAddress("TagIDMuonPtVec", &TagIDMuonPtVec, &b_TagIDMuonPtVec);
   fChain->SetBranchAddress("TagIDMuonEtaVec", &TagIDMuonEtaVec, &b_TagIDMuonEtaVec);
   fChain->SetBranchAddress("TagIDMuonPhiVec", &TagIDMuonPhiVec, &b_TagIDMuonPhiVec);
   fChain->SetBranchAddress("TagIDMuonNum", &TagIDMuonNum, &b_TagIDMuonNum);
   fChain->SetBranchAddress("TagIDMuonE", TagIDMuonE, &b_TagIDMuonE);
   fChain->SetBranchAddress("TagIDMuonTLorentzVector", TagIDMuonTLorentzVector, &b_TagIDMuonTLorentzVector);
   fChain->SetBranchAddress("ProbeIDMuonPtVec", &ProbeIDMuonPtVec, &b_ProbeIDMuonPtVec);
   fChain->SetBranchAddress("ProbeIDMuonEtaVec", &ProbeIDMuonEtaVec, &b_ProbeIDMuonEtaVec);
   fChain->SetBranchAddress("ProbeIDMuonPhiVec", &ProbeIDMuonPhiVec, &b_ProbeIDMuonPhiVec);
   fChain->SetBranchAddress("ProbeIDMuonNum", &ProbeIDMuonNum, &b_ProbeIDMuonNum);
   fChain->SetBranchAddress("ProbeIDMuonE", ProbeIDMuonE, &b_ProbeIDMuonE);
   fChain->SetBranchAddress("ProbeIDMuonTLorentzVector", ProbeIDMuonTLorentzVector, &b_ProbeIDMuonTLorentzVector);
   fChain->SetBranchAddress("ProbeIDMuon_InvariantMass_1", ProbeIDMuon_InvariantMass_1, &b_ProbeIDMuon_InvariantMass_1);
   fChain->SetBranchAddress("ProbeIDMuon_PassingOrFail_1", ProbeIDMuon_PassingOrFail_1, &b_ProbeIDMuon_PassingOrFail_1);
   fChain->SetBranchAddress("TagIsoElectronPtVec", &TagIsoElectronPtVec, &b_TagIsoElectronPtVec);
   fChain->SetBranchAddress("TagIsoElectronEtaVec", &TagIsoElectronEtaVec, &b_TagIsoElectronEtaVec);
   fChain->SetBranchAddress("TagIsoElectronPhiVec", &TagIsoElectronPhiVec, &b_TagIsoElectronPhiVec);
   fChain->SetBranchAddress("TagIsoElectronNum", &TagIsoElectronNum, &b_TagIsoElectronNum);
   fChain->SetBranchAddress("TagIsoElectronE", TagIsoElectronE, &b_TagIsoElectronE);
   fChain->SetBranchAddress("TagIsoElectronTLorentzVector", TagIsoElectronTLorentzVector, &b_TagIsoElectronTLorentzVector);
   fChain->SetBranchAddress("ProbeIsoElectronPtVec", &ProbeIsoElectronPtVec, &b_ProbeIsoElectronPtVec);
   fChain->SetBranchAddress("ProbeIsoElectronEtaVec", &ProbeIsoElectronEtaVec, &b_ProbeIsoElectronEtaVec);
   fChain->SetBranchAddress("ProbeIsoElectronPhiVec", &ProbeIsoElectronPhiVec, &b_ProbeIsoElectronPhiVec);
   fChain->SetBranchAddress("ProbeIsoElectronNum", &ProbeIsoElectronNum, &b_ProbeIsoElectronNum);
   fChain->SetBranchAddress("ProbeIsoElectronE", ProbeIsoElectronE, &b_ProbeIsoElectronE);
   fChain->SetBranchAddress("ProbeIsoElectronTLorentzVector", ProbeIsoElectronTLorentzVector, &b_ProbeIsoElectronTLorentzVector);
   fChain->SetBranchAddress("ProbeIsoElectron_InvariantMass_2", ProbeIsoElectron_InvariantMass_2, &b_ProbeIsoElectron_InvariantMass_2);
   fChain->SetBranchAddress("ProbeIsoElectron_PassingOrFail_2", ProbeIsoElectron_PassingOrFail_2, &b_ProbeIsoElectron_PassingOrFail_2);
   fChain->SetBranchAddress("TagIDElectronPtVec", &TagIDElectronPtVec, &b_TagIDElectronPtVec);
   fChain->SetBranchAddress("TagIDElectronEtaVec", &TagIDElectronEtaVec, &b_TagIDElectronEtaVec);
   fChain->SetBranchAddress("TagIDElectronPhiVec", &TagIDElectronPhiVec, &b_TagIDElectronPhiVec);
   fChain->SetBranchAddress("TagIDElectronNum", &TagIDElectronNum, &b_TagIDElectronNum);
   fChain->SetBranchAddress("TagIDElectronE", TagIDElectronE, &b_TagIDElectronE);
   fChain->SetBranchAddress("TagIDElectronTLorentzVector", TagIDElectronTLorentzVector, &b_TagIDElectronTLorentzVector);
   fChain->SetBranchAddress("ProbeIDElectronPtVec", &ProbeIDElectronPtVec, &b_ProbeIDElectronPtVec);
   fChain->SetBranchAddress("ProbeIDElectronEtaVec", &ProbeIDElectronEtaVec, &b_ProbeIDElectronEtaVec);
   fChain->SetBranchAddress("ProbeIDElectronPhiVec", &ProbeIDElectronPhiVec, &b_ProbeIDElectronPhiVec);
   fChain->SetBranchAddress("ProbeIDElectronNum", &ProbeIDElectronNum, &b_ProbeIDElectronNum);
   fChain->SetBranchAddress("ProbeIDElectronE", ProbeIDElectronE, &b_ProbeIDElectronE);
   fChain->SetBranchAddress("ProbeIDElectronTLorentzVector", ProbeIDElectronTLorentzVector, &b_ProbeIDElectronTLorentzVector);
   fChain->SetBranchAddress("ProbeIDElectron_InvariantMass_3", ProbeIDElectron_InvariantMass_3, &b_ProbeIDElectron_InvariantMass_3);
   fChain->SetBranchAddress("ProbeIDElectron_PassingOrFail_3", ProbeIDElectron_PassingOrFail_3, &b_ProbeIDElectron_PassingOrFail_3);
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
   fChain->SetBranchAddress("SelectedPFCandidatesPtVec", &SelectedPFCandidatesPtVec, &b_SelectedPFCandidatesPtVec);
   fChain->SetBranchAddress("SelectedPFCandidatesEtaVec", &SelectedPFCandidatesEtaVec, &b_SelectedPFCandidatesEtaVec);
   fChain->SetBranchAddress("SelectedPFCandidatesPhiVec", &SelectedPFCandidatesPhiVec, &b_SelectedPFCandidatesPhiVec);
   fChain->SetBranchAddress("SelectedPFCandidatesNum", &SelectedPFCandidatesNum, &b_SelectedPFCandidatesNum);
   fChain->SetBranchAddress("SelectedPFCandidatesE", SelectedPFCandidatesE, &b_SelectedPFCandidatesE);
   fChain->SetBranchAddress("SelectedPFCandidatesTLorentzVector", SelectedPFCandidatesTLorentzVector, &b_SelectedPFCandidatesTLorentzVector);
   fChain->SetBranchAddress("SelectedPFCandidates_Charge", SelectedPFCandidates_Charge, &b_SelectedPFCandidates_Charge);
   fChain->SetBranchAddress("SelectedPFCandidates_Typ", SelectedPFCandidates_Typ, &b_SelectedPFCandidates_Typ);
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
   fChain->SetBranchAddress("IsolatedTracksPtVec", &IsolatedTracksPtVec, &b_IsolatedTracksPtVec);
   fChain->SetBranchAddress("IsolatedTracksEtaVec", &IsolatedTracksEtaVec, &b_IsolatedTracksEtaVec);
   fChain->SetBranchAddress("IsolatedTracksPhiVec", &IsolatedTracksPhiVec, &b_IsolatedTracksPhiVec);
   fChain->SetBranchAddress("IsolatedTracksNum", &IsolatedTracksNum, &b_IsolatedTracksNum);
   fChain->SetBranchAddress("IsolatedTracksE", IsolatedTracksE, &b_IsolatedTracksE);
   fChain->SetBranchAddress("IsolatedTracksTLorentzVector", IsolatedTracksTLorentzVector, &b_IsolatedTracksTLorentzVector);
   fChain->SetBranchAddress("selectedIDIsoMuonsPtVec", &selectedIDIsoMuonsPtVec, &b_selectedIDIsoMuonsPtVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsEtaVec", &selectedIDIsoMuonsEtaVec, &b_selectedIDIsoMuonsEtaVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsPhiVec", &selectedIDIsoMuonsPhiVec, &b_selectedIDIsoMuonsPhiVec);
   fChain->SetBranchAddress("selectedIDIsoMuonsNum", &selectedIDIsoMuonsNum, &b_selectedIDIsoMuonsNum);
   fChain->SetBranchAddress("selectedIDIsoMuonsE", selectedIDIsoMuonsE, &b_selectedIDIsoMuonsE);
   fChain->SetBranchAddress("selectedIDIsoMuonsTLorentzVector", selectedIDIsoMuonsTLorentzVector, &b_selectedIDIsoMuonsTLorentzVector);
   fChain->SetBranchAddress("selectedIDMuonsPtVec", &selectedIDMuonsPtVec, &b_selectedIDMuonsPtVec);
   fChain->SetBranchAddress("selectedIDMuonsEtaVec", &selectedIDMuonsEtaVec, &b_selectedIDMuonsEtaVec);
   fChain->SetBranchAddress("selectedIDMuonsPhiVec", &selectedIDMuonsPhiVec, &b_selectedIDMuonsPhiVec);
   fChain->SetBranchAddress("selectedIDMuonsNum", &selectedIDMuonsNum, &b_selectedIDMuonsNum);
   fChain->SetBranchAddress("selectedIDMuonsE", selectedIDMuonsE, &b_selectedIDMuonsE);
   fChain->SetBranchAddress("selectedIDMuonsTLorentzVector", selectedIDMuonsTLorentzVector, &b_selectedIDMuonsTLorentzVector);
   fChain->SetBranchAddress("selectedIDIsoElectronsPtVec", &selectedIDIsoElectronsPtVec, &b_selectedIDIsoElectronsPtVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsEtaVec", &selectedIDIsoElectronsEtaVec, &b_selectedIDIsoElectronsEtaVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsPhiVec", &selectedIDIsoElectronsPhiVec, &b_selectedIDIsoElectronsPhiVec);
   fChain->SetBranchAddress("selectedIDIsoElectronsNum", &selectedIDIsoElectronsNum, &b_selectedIDIsoElectronsNum);
   fChain->SetBranchAddress("selectedIDIsoElectronsE", selectedIDIsoElectronsE, &b_selectedIDIsoElectronsE);
   fChain->SetBranchAddress("selectedIDIsoElectronsTLorentzVector", selectedIDIsoElectronsTLorentzVector, &b_selectedIDIsoElectronsTLorentzVector);
   fChain->SetBranchAddress("selectedIDElectronsPtVec", &selectedIDElectronsPtVec, &b_selectedIDElectronsPtVec);
   fChain->SetBranchAddress("selectedIDElectronsEtaVec", &selectedIDElectronsEtaVec, &b_selectedIDElectronsEtaVec);
   fChain->SetBranchAddress("selectedIDElectronsPhiVec", &selectedIDElectronsPhiVec, &b_selectedIDElectronsPhiVec);
   fChain->SetBranchAddress("selectedIDElectronsNum", &selectedIDElectronsNum, &b_selectedIDElectronsNum);
   fChain->SetBranchAddress("selectedIDElectronsE", selectedIDElectronsE, &b_selectedIDElectronsE);
   fChain->SetBranchAddress("selectedIDElectronsTLorentzVector", selectedIDElectronsTLorentzVector, &b_selectedIDElectronsTLorentzVector);
   fChain->SetBranchAddress("SelectedPFCandidates_1PtVec", &SelectedPFCandidates_1PtVec, &b_SelectedPFCandidates_1PtVec);
   fChain->SetBranchAddress("SelectedPFCandidates_1EtaVec", &SelectedPFCandidates_1EtaVec, &b_SelectedPFCandidates_1EtaVec);
   fChain->SetBranchAddress("SelectedPFCandidates_1PhiVec", &SelectedPFCandidates_1PhiVec, &b_SelectedPFCandidates_1PhiVec);
   fChain->SetBranchAddress("SelectedPFCandidates_1Num", &SelectedPFCandidates_1Num, &b_SelectedPFCandidates_1Num);
   fChain->SetBranchAddress("SelectedPFCandidates_1E", SelectedPFCandidates_1E, &b_SelectedPFCandidates_1E);
   fChain->SetBranchAddress("SelectedPFCandidates_1TLorentzVector", SelectedPFCandidates_1TLorentzVector, &b_SelectedPFCandidates_1TLorentzVector);
   fChain->SetBranchAddress("SelectedPFCandidates_1_Charge_1", SelectedPFCandidates_1_Charge_1, &b_SelectedPFCandidates_1_Charge_1);
   fChain->SetBranchAddress("SelectedPFCandidates_1_Typ_1", SelectedPFCandidates_1_Typ_1, &b_SelectedPFCandidates_1_Typ_1);
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
   fChain->SetBranchAddress("Jets_1PtVec", &Jets_1PtVec, &b_Jets_1PtVec);
   fChain->SetBranchAddress("Jets_1EtaVec", &Jets_1EtaVec, &b_Jets_1EtaVec);
   fChain->SetBranchAddress("Jets_1PhiVec", &Jets_1PhiVec, &b_Jets_1PhiVec);
   fChain->SetBranchAddress("Jets_1Num", &Jets_1Num, &b_Jets_1Num);
   fChain->SetBranchAddress("Jets_1E", Jets_1E, &b_Jets_1E);
   fChain->SetBranchAddress("Jets_1TLorentzVector", Jets_1TLorentzVector, &b_Jets_1TLorentzVector);
   fChain->SetBranchAddress("Jets_1_bDiscriminator_1", Jets_1_bDiscriminator_1, &b_Jets_1_bDiscriminator_1);
   fChain->SetBranchAddress("Jets_1_chargedEmEnergyFraction_1", Jets_1_chargedEmEnergyFraction_1, &b_Jets_1_chargedEmEnergyFraction_1);
   fChain->SetBranchAddress("Jets_1_chargedHadronEnergyFraction_1", Jets_1_chargedHadronEnergyFraction_1, &b_Jets_1_chargedHadronEnergyFraction_1);
   fChain->SetBranchAddress("Jets_1_chargedHadronMultiplicity_1", Jets_1_chargedHadronMultiplicity_1, &b_Jets_1_chargedHadronMultiplicity_1);
   fChain->SetBranchAddress("Jets_1_electronMultiplicity_1", Jets_1_electronMultiplicity_1, &b_Jets_1_electronMultiplicity_1);
   fChain->SetBranchAddress("Jets_1_jetArea_1", Jets_1_jetArea_1, &b_Jets_1_jetArea_1);
   fChain->SetBranchAddress("Jets_1_muonEnergyFraction_1", Jets_1_muonEnergyFraction_1, &b_Jets_1_muonEnergyFraction_1);
   fChain->SetBranchAddress("Jets_1_muonMultiplicity_1", Jets_1_muonMultiplicity_1, &b_Jets_1_muonMultiplicity_1);
   fChain->SetBranchAddress("Jets_1_neutralEmEnergyFraction_1", Jets_1_neutralEmEnergyFraction_1, &b_Jets_1_neutralEmEnergyFraction_1);
   fChain->SetBranchAddress("Jets_1_neutralHadronMultiplicity_1", Jets_1_neutralHadronMultiplicity_1, &b_Jets_1_neutralHadronMultiplicity_1);
   fChain->SetBranchAddress("Jets_1_photonEnergyFraction_1", Jets_1_photonEnergyFraction_1, &b_Jets_1_photonEnergyFraction_1);
   fChain->SetBranchAddress("Jets_1_photonMultiplicity_1", Jets_1_photonMultiplicity_1, &b_Jets_1_photonMultiplicity_1);
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
