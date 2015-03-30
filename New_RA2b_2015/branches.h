//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar 28 21:43:43 2015 by ROOT version 5.34/25
// from TTree PreSelection/PreSelection
// found on file: /home/borzou/MiniAOD/CMSSW_7_2_3_patch1/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection-HT.root
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
   Int_t           NJets;
   Int_t           BTags;
   Float_t         Weight;
   Float_t         HT;
   Float_t         MHT;
   Float_t         DeltaPhi1;
   Float_t         DeltaPhi2;
   Float_t         DeltaPhi3;
   Float_t         minDeltaPhiN;
   vector<double>  *testVec;
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
   vector<double>  *JetsPtVec;
   vector<double>  *JetsEtaVec;
   vector<double>  *JetsPhiVec;
   UShort_t        JetsNum;
   Float_t         JetsE[43];   //[JetsNum]
   Float_t         JetsTLorentzVector[43];   //[JetsNum]
   Float_t         Jets_bDiscriminator[43];   //[JetsNum]
   Float_t         Jets_chargedEmEnergyFraction[43];   //[JetsNum]
   Float_t         Jets_chargedHadronEnergyFraction[43];   //[JetsNum]
   Int_t           Jets_chargedHadronMultiplicity[43];   //[JetsNum]
   Int_t           Jets_electronMultiplicity[43];   //[JetsNum]
   Float_t         Jets_jetArea[43];   //[JetsNum]
   Float_t         Jets_muonEnergyFraction[43];   //[JetsNum]
   Int_t           Jets_muonMultiplicity[43];   //[JetsNum]
   Float_t         Jets_neutralEmEnergyFraction[43];   //[JetsNum]
   Int_t           Jets_neutralHadronMultiplicity[43];   //[JetsNum]
   Float_t         Jets_photonEnergyFraction[43];   //[JetsNum]
   Int_t           Jets_photonMultiplicity[43];   //[JetsNum]

   // List of branches
   TBranch        *b_RunNum;   //!
   TBranch        *b_LumiBlockNum;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_NVtx;   //!
   TBranch        *b_isoTracks;   //!
   TBranch        *b_Leptons;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_BTags;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_DeltaPhi1;   //!
   TBranch        *b_DeltaPhi2;   //!
   TBranch        *b_DeltaPhi3;   //!
   TBranch        *b_minDeltaPhiN;   //!
   TBranch        *b_testVec;   //!
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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/borzou/MiniAOD/CMSSW_7_2_3_patch1/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection-HT.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/borzou/MiniAOD/CMSSW_7_2_3_patch1/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection-HT.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/borzou/MiniAOD/CMSSW_7_2_3_patch1/src/AllHadronicSUSY/TreeMaker/test/ReducedSelection-HT.root:/TreeMaker2");
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
   JetsPtVec = 0;
   JetsEtaVec = 0;
   JetsPhiVec = 0;
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
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
   fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN, &b_minDeltaPhiN);
   fChain->SetBranchAddress("testVec", &testVec, &b_testVec);
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
