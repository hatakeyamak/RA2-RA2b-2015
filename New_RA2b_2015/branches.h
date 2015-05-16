//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat May 16 10:28:08 2015 by ROOT version 5.34/25
// from TTree PreSelection/PreSelection
// found on file: /data3/store/user/borzou/ntuples/Apr02/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/Spring14miniaod-141029_PU40bx50_PLS170_V6AN2-v1/150515_175928/0000/ReducedSelection_1.root
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
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Int_t           Leptons;
   Int_t           LeptonsNoMiniIsolation;
   Int_t           NJets;
   Int_t           BTags;
   Float_t         Weight;
   Float_t         HT;
   Float_t         MHTPhi;
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
   UChar_t         JetID;
   vector<double>  *testVec;
   vector<double>  *MuonsPtVec;
   vector<double>  *MuonsEtaVec;
   vector<double>  *MuonsPhiVec;
   UShort_t        MuonsNum;
   Float_t         MuonsE[4];   //[MuonsNum]
   Float_t         MuonsTLorentzVector[4];   //[MuonsNum]
   vector<double>  *ElectronsPtVec;
   vector<double>  *ElectronsEtaVec;
   vector<double>  *ElectronsPhiVec;
   UShort_t        ElectronsNum;
   Float_t         ElectronsE[4];   //[ElectronsNum]
   Float_t         ElectronsTLorentzVector[4];   //[ElectronsNum]
   vector<double>  *IsolatedTracksPtVec;
   vector<double>  *IsolatedTracksEtaVec;
   vector<double>  *IsolatedTracksPhiVec;
   UShort_t        IsolatedTracksNum;
   Float_t         IsolatedTracksE[1];   //[IsolatedTracksNum]
   Float_t         IsolatedTracksTLorentzVector[1];   //[IsolatedTracksNum]
   vector<double>  *selectedIDIsoMuonsPtVec;
   vector<double>  *selectedIDIsoMuonsEtaVec;
   vector<double>  *selectedIDIsoMuonsPhiVec;
   UShort_t        selectedIDIsoMuonsNum;
   Float_t         selectedIDIsoMuonsE[4];   //[selectedIDIsoMuonsNum]
   Float_t         selectedIDIsoMuonsTLorentzVector[4];   //[selectedIDIsoMuonsNum]
   vector<double>  *selectedIDMuonsPtVec;
   vector<double>  *selectedIDMuonsEtaVec;
   vector<double>  *selectedIDMuonsPhiVec;
   UShort_t        selectedIDMuonsNum;
   Float_t         selectedIDMuonsE[5];   //[selectedIDMuonsNum]
   Float_t         selectedIDMuonsTLorentzVector[5];   //[selectedIDMuonsNum]
   vector<double>  *selectedIDIsoElectronsPtVec;
   vector<double>  *selectedIDIsoElectronsEtaVec;
   vector<double>  *selectedIDIsoElectronsPhiVec;
   UShort_t        selectedIDIsoElectronsNum;
   Float_t         selectedIDIsoElectronsE[4];   //[selectedIDIsoElectronsNum]
   Float_t         selectedIDIsoElectronsTLorentzVector[4];   //[selectedIDIsoElectronsNum]
   vector<double>  *selectedIDElectronsPtVec;
   vector<double>  *selectedIDElectronsEtaVec;
   vector<double>  *selectedIDElectronsPhiVec;
   UShort_t        selectedIDElectronsNum;
   Float_t         selectedIDElectronsE[4];   //[selectedIDElectronsNum]
   Float_t         selectedIDElectronsTLorentzVector[4];   //[selectedIDElectronsNum]
   vector<double>  *SelectedPFCandidatesPtVec;
   vector<double>  *SelectedPFCandidatesEtaVec;
   vector<double>  *SelectedPFCandidatesPhiVec;
   UShort_t        SelectedPFCandidatesNum;
   Float_t         SelectedPFCandidatesE[192];   //[SelectedPFCandidatesNum]
   Float_t         SelectedPFCandidatesTLorentzVector[192];   //[SelectedPFCandidatesNum]
   Int_t           SelectedPFCandidates_Charge[192];   //[SelectedPFCandidatesNum]
   Int_t           SelectedPFCandidates_Typ[192];   //[SelectedPFCandidatesNum]
   vector<double>  *GenBosonPtVec;
   vector<double>  *GenBosonEtaVec;
   vector<double>  *GenBosonPhiVec;
   UShort_t        GenBosonNum;
   Float_t         GenBosonE[4];   //[GenBosonNum]
   Float_t         GenBosonTLorentzVector[4];   //[GenBosonNum]
   Int_t           GenBoson_GenBosonPDGId[4];   //[GenBosonNum]
   vector<double>  *GenMuPtVec;
   vector<double>  *GenMuEtaVec;
   vector<double>  *GenMuPhiVec;
   UShort_t        GenMuNum;
   Float_t         GenMuE[4];   //[GenMuNum]
   Float_t         GenMuTLorentzVector[4];   //[GenMuNum]
   Int_t           GenMu_GenMuFromTau[4];   //[GenMuNum]
   vector<double>  *GenElecPtVec;
   vector<double>  *GenElecEtaVec;
   vector<double>  *GenElecPhiVec;
   UShort_t        GenElecNum;
   Float_t         GenElecE[4];   //[GenElecNum]
   Float_t         GenElecTLorentzVector[4];   //[GenElecNum]
   Int_t           GenElec_GenElecFromTau[4];   //[GenElecNum]
   vector<double>  *GenTauPtVec;
   vector<double>  *GenTauEtaVec;
   vector<double>  *GenTauPhiVec;
   UShort_t        GenTauNum;
   Float_t         GenTauE[4];   //[GenTauNum]
   Float_t         GenTauTLorentzVector[4];   //[GenTauNum]
   Int_t           GenTau_GenTauHad[4];   //[GenTauNum]
   vector<double>  *selectedIDIsoMuonsNoMiniIsoPtVec;
   vector<double>  *selectedIDIsoMuonsNoMiniIsoEtaVec;
   vector<double>  *selectedIDIsoMuonsNoMiniIsoPhiVec;
   UShort_t        selectedIDIsoMuonsNoMiniIsoNum;
   Float_t         selectedIDIsoMuonsNoMiniIsoE[4];   //[selectedIDIsoMuonsNoMiniIsoNum]
   Float_t         selectedIDIsoMuonsNoMiniIsoTLorentzVector[4];   //[selectedIDIsoMuonsNoMiniIsoNum]
   vector<double>  *selectedIDIsoElectronsNoMiniIsoPtVec;
   vector<double>  *selectedIDIsoElectronsNoMiniIsoEtaVec;
   vector<double>  *selectedIDIsoElectronsNoMiniIsoPhiVec;
   UShort_t        selectedIDIsoElectronsNoMiniIsoNum;
   Float_t         selectedIDIsoElectronsNoMiniIsoE[4];   //[selectedIDIsoElectronsNoMiniIsoNum]
   Float_t         selectedIDIsoElectronsNoMiniIsoTLorentzVector[4];   //[selectedIDIsoElectronsNoMiniIsoNum]
   vector<double>  *JetsPtVec;
   vector<double>  *JetsEtaVec;
   vector<double>  *JetsPhiVec;
   UShort_t        JetsNum;
   Float_t         JetsE[19];   //[JetsNum]
   Float_t         JetsTLorentzVector[19];   //[JetsNum]
   Float_t         Jets_bDiscriminator[19];   //[JetsNum]
   Float_t         Jets_chargedEmEnergyFraction[19];   //[JetsNum]
   Float_t         Jets_chargedHadronEnergyFraction[19];   //[JetsNum]
   Int_t           Jets_chargedHadronMultiplicity[19];   //[JetsNum]
   Int_t           Jets_electronMultiplicity[19];   //[JetsNum]
   Float_t         Jets_jetArea[19];   //[JetsNum]
   Float_t         Jets_muonEnergyFraction[19];   //[JetsNum]
   Int_t           Jets_muonMultiplicity[19];   //[JetsNum]
   Float_t         Jets_neutralEmEnergyFraction[19];   //[JetsNum]
   Int_t           Jets_neutralHadronMultiplicity[19];   //[JetsNum]
   Float_t         Jets_photonEnergyFraction[19];   //[JetsNum]
   Int_t           Jets_photonMultiplicity[19];   //[JetsNum]
   vector<double>  *slimmedElectronsPtVec;
   vector<double>  *slimmedElectronsEtaVec;
   vector<double>  *slimmedElectronsPhiVec;
   UShort_t        slimmedElectronsNum;
   Float_t         slimmedElectronsE[11];   //[slimmedElectronsNum]
   Float_t         slimmedElectronsTLorentzVector[11];   //[slimmedElectronsNum]
   vector<double>  *slimmedMuonsPtVec;
   vector<double>  *slimmedMuonsEtaVec;
   vector<double>  *slimmedMuonsPhiVec;
   UShort_t        slimmedMuonsNum;
   Float_t         slimmedMuonsE[33];   //[slimmedMuonsNum]
   Float_t         slimmedMuonsTLorentzVector[33];   //[slimmedMuonsNum]
   vector<double>  *slimJetPtVec;
   vector<double>  *slimJetEtaVec;
   vector<double>  *slimJetPhiVec;
   UShort_t        slimJetNum;
   Float_t         slimJetE[66];   //[slimJetNum]
   Float_t         slimJetTLorentzVector[66];   //[slimJetNum]
   Int_t           slimJet_slimJetID[66];   //[slimJetNum]
   vector<double>  *GenTauNuPtVec;
   vector<double>  *GenTauNuEtaVec;
   vector<double>  *GenTauNuPhiVec;
   UShort_t        GenTauNuNum;
   Float_t         GenTauNuE[6];   //[GenTauNuNum]
   Float_t         GenTauNuTLorentzVector[6];   //[GenTauNuNum]
   Float_t         GenTauNu_TauNuMomPt[6];   //[GenTauNuNum]

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_isoElectronTracks;   //!
   TBranch        *b_isoMuonTracks;   //!
   TBranch        *b_isoPionTracks;   //!
   TBranch        *b_Leptons;   //!
   TBranch        *b_LeptonsNoMiniIsolation;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_BTags;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_MHTPhi;   //!
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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data3/store/user/borzou/ntuples/Apr02/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/Spring14miniaod-141029_PU40bx50_PLS170_V6AN2-v1/150515_175928/0000/ReducedSelection_1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/data3/store/user/borzou/ntuples/Apr02/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/Spring14miniaod-141029_PU40bx50_PLS170_V6AN2-v1/150515_175928/0000/ReducedSelection_1.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/data3/store/user/borzou/ntuples/Apr02/SMS-T1tttt_2J_mGl-1500_mLSP-100_Tune4C_13TeV-madgraph-tauola/Spring14miniaod-141029_PU40bx50_PLS170_V6AN2-v1/150515_175928/0000/ReducedSelection_1.root:/TreeMaker2");
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
   slimJetPtVec = 0;
   slimJetEtaVec = 0;
   slimJetPhiVec = 0;
   GenTauNuPtVec = 0;
   GenTauNuEtaVec = 0;
   GenTauNuPhiVec = 0;
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
   fChain->SetBranchAddress("LeptonsNoMiniIsolation", &LeptonsNoMiniIsolation, &b_LeptonsNoMiniIsolation);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
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
//   fChain->SetBranchAddress("IsolatedTracksPtVec", &IsolatedTracksPtVec, &b_IsolatedTracksPtVec);
//   fChain->SetBranchAddress("IsolatedTracksEtaVec", &IsolatedTracksEtaVec, &b_IsolatedTracksEtaVec);
//   fChain->SetBranchAddress("IsolatedTracksPhiVec", &IsolatedTracksPhiVec, &b_IsolatedTracksPhiVec);
//   fChain->SetBranchAddress("IsolatedTracksNum", &IsolatedTracksNum, &b_IsolatedTracksNum);
//   fChain->SetBranchAddress("IsolatedTracksE", &IsolatedTracksE, &b_IsolatedTracksE);
//   fChain->SetBranchAddress("IsolatedTracksTLorentzVector", &IsolatedTracksTLorentzVector, &b_IsolatedTracksTLorentzVector);
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
