#ifndef EVENT_H
#define EVENT_H
#include "TTree.h"
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include "TLorentzVector.h"
#include <stdio.h>
#include "TColor.h"
#include "TF1.h"
#include "TLegend.h"
#include "TVector3.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TVector2.h"
#include "TCanvas.h"
using namespace std;

  class Events{
   
   // See if working with Data or MC
   bool DataBool;

   // Declaration of leaf types
   UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   UInt_t          EvtNum;
   Int_t           NVtx;
//   Int_t           isoTracks;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Int_t           Leptons;
   Int_t           NJets;
   Int_t           BTags;
   Float_t         Weight;
   Float_t         HT;
   Float_t         MHT;
   Float_t         MHT_Phi; 
//Float_t         MHTPhi;
   Float_t         METPt;
   Float_t         METPhi;
   Float_t         DeltaPhi1;
   Float_t         DeltaPhi2;
   Float_t         DeltaPhi3;
   Float_t         minDeltaPhiN_;
   TTree *         fChain;
   int             currentEntry_;
   int             template_Entries; 


   vector<double>  *testVec;

   vector<double>  *GenMuPtVec;
   vector<double>  *GenMuEtaVec;
   vector<double>  *GenMuPhiVec;

   vector<double>  *GenElecPtVec;
   vector<double>  *GenElecEtaVec;
   vector<double>  *GenElecPhiVec;


   vector<double>  *GenTauPtVec;
   vector<double>  *GenTauEtaVec;
   vector<double>  *GenTauPhiVec;

   vector<double>  *GenTauNuPtVec;
   vector<double>  *GenTauNuEtaVec;
   vector<double>  *GenTauNuPhiVec;

   vector<double>  *JetsPtVec;
   vector<double>  *JetsEtaVec;
   vector<double>  *JetsPhiVec;
   Float_t        Jets_bDiscriminator[50];  
   Float_t         Jets_chargedEmEnergyFraction[50];   //[JetsNum]        
   Float_t         Jets_chargedHadronEnergyFraction[50];   //[JetsNum]    
   Int_t           Jets_chargedHadronMultiplicity[50];   //[JetsNum]      
   Int_t           Jets_electronMultiplicity[50];   //[JetsNum]           
   Float_t         Jets_jetArea[50];   //[JetsNum]                        
   Float_t         Jets_muonEnergyFraction[50];   //[JetsNum]             
   Int_t           Jets_muonMultiplicity[50];   //[JetsNum]               
   Float_t         Jets_neutralEmEnergyFraction[50];   //[JetsNum]        
   Int_t           Jets_neutralHadronMultiplicity[50];   //[JetsNum]      
   Float_t         Jets_photonEnergyFraction[50];   //[JetsNum]          
   Int_t           Jets_photonMultiplicity[50];   //[JetsNum]            

   vector<double>  *slimJetPtVec;
   vector<double>  *slimJetEtaVec;
   vector<double>  *slimJetPhiVec;

   vector<double>  *slimmedMuonsPtVec;
   vector<double>  *slimmedMuonsEtaVec;
   vector<double>  *slimmedMuonsPhiVec;
   vector<double>  *MuonsPtVec;
   vector<double>  *MuonsEtaVec;
   vector<double>  *MuonsPhiVec;
   vector<double>  *selectedIDMuonsPtVec;
   vector<double>  *selectedIDMuonsEtaVec;
   vector<double>  *selectedIDMuonsPhiVec;
   vector<double>  *selectedIDIsoMuonsPtVec;
   vector<double>  *selectedIDIsoMuonsEtaVec;
   vector<double>  *selectedIDIsoMuonsPhiVec;

   vector<double>  *slimmedElectronsPtVec;
   vector<double>  *slimmedElectronsEtaVec;
   vector<double>  *slimmedElectronsPhiVec;
   vector<double>  *ElectronsPtVec;
   vector<double>  *ElectronsEtaVec;
   vector<double>  *ElectronsPhiVec;
   vector<double>  *selectedIDElectronsPtVec;
   vector<double>  *selectedIDElectronsEtaVec;
   vector<double>  *selectedIDElectronsPhiVec;
   vector<double>  *selectedIDIsoElectronsPtVec;
   vector<double>  *selectedIDIsoElectronsEtaVec;
   vector<double>  *selectedIDIsoElectronsPhiVec;

   vector<double>  *IsolatedElectronTracksVetoPtVec;
   vector<double>  *IsolatedElectronTracksVetoEtaVec;
   vector<double>  *IsolatedElectronTracksVetoPhiVec;

   vector<double>  *IsolatedMuonTracksVetoPtVec;
   vector<double>  *IsolatedMuonTracksVetoEtaVec;
   vector<double>  *IsolatedMuonTracksVetoPhiVec;

   vector<double>  *IsolatedPionTracksVetoPtVec;
   vector<double>  *IsolatedPionTracksVetoEtaVec;
   vector<double>  *IsolatedPionTracksVetoPhiVec;


   Int_t    *     GenMu_GenMuFromTau;   //[GenMuNum]
   Int_t    *      GenElec_GenElecFromTau;   //[GenElecNum]
   Int_t    *      GenTau_GenTauHad;   //[GenTauNum]
   Int_t           slimJet_slimJetID[100];
   UChar_t         JetID; 

public:
//constructor
Events(TTree * ttree_, const std::string sampleKeyString="ttbar", int verbose=0);

//Functions
  bool loadNext();
  int Runnum() const;
  int Evtnum() const;
  int nJets() const;
  int nBtags() const;
  int nLeptons() const;
//  int nIso() const;
  int nIsoElec() const ;
  int nIsoMu() const ;
  int nIsoPion() const;
  double weight() const ;
  double ht() const ;
  double mht() const ;
  double mhtphi() const ;
  double met() const ;
  double metphi() const ;
  double deltaPhi1() const ;
  double deltaPhi2() const ;
  double deltaPhi3() const ;
  double minDeltaPhiN() const ;
  int nGenMu() const ;
  int JetId() const ; 

  bool DataBool_() const;

   vector<double>  GenMuPtVec_() const;
   vector<double>  GenMuEtaVec_() const;
   vector<double>  GenMuPhiVec_() const;

   vector<double>  GenElecPtVec_() const;
   vector<double>  GenElecEtaVec_() const;
   vector<double>  GenElecPhiVec_() const;


   vector<double>  GenTauPtVec_() const;
   vector<double>  GenTauEtaVec_() const;
   vector<double>  GenTauPhiVec_() const;

   vector<double>  GenTauNuPtVec_() const;
   vector<double>  GenTauNuEtaVec_() const;
   vector<double>  GenTauNuPhiVec_() const;

   vector<double>  JetsPtVec_() const;
   vector<double>  JetsEtaVec_() const;
   vector<double>  JetsPhiVec_() const;
   vector<double>  csvVec() const;
   vector<double>  Jets_chargedEmEnergyFraction_() const;
   vector<double>  Jets_chargedHadronEnergyFraction_() const;
   vector<int>     Jets_chargedHadronMultiplicity_() const;
   vector<int>     Jets_electronMultiplicity_() const;
   vector<double>  Jets_jetArea_() const;
   vector<double>  Jets_muonEnergyFraction_() const;
   vector<int>     Jets_muonMultiplicity_() const;
   vector<double>  Jets_neutralEmEnergyFraction_() const;
   vector<int>     Jets_neutralHadronMultiplicity_() const;
   vector<double>  Jets_photonEnergyFraction_() const; 
   vector<int>     Jets_photonMultiplicity_() const;


   vector<double>  slimJetPtVec_() const;
   vector<double>  slimJetEtaVec_() const;
   vector<double>  slimJetPhiVec_() const;

   vector<int>     slimJetID_() const;

   vector<double>  slimmedMuPtVec_() const;
   vector<double>  slimmedMuEtaVec_() const;
   vector<double>  slimmedMuPhiVec_() const;
   vector<double>  MuNoIsoPtVec_() const;
   vector<double>  MuNoIsoEtaVec_() const;
   vector<double>  MuNoIsoPhiVec_() const;
   vector<double>  MuPtVec_() const;
   vector<double>  MuEtaVec_() const;
   vector<double>  MuPhiVec_() const;

   vector<double>  slimmedElecPtVec_() const;
   vector<double>  slimmedElecEtaVec_() const;
   vector<double>  slimmedElecPhiVec_() const;
   vector<double>  ElecNoIsoPtVec_() const;
   vector<double>  ElecNoIsoEtaVec_() const;
   vector<double>  ElecNoIsoPhiVec_() const;
   vector<double>  ElecPtVec_() const;
   vector<double>  ElecEtaVec_() const;
   vector<double>  ElecPhiVec_() const;

   vector<int>     GenMuFromTauVec_() const;   
   vector<int>     GenElecFromTauVec_() const;   
   vector<int>     GenTauHadVec_() const;   

   vector<double>  IsoElecPtVec_() const;
   vector<double>  IsoElecEtaVec_() const;
   vector<double>  IsoElecPhiVec_() const;
   vector<double>  IsoMuPtVec_() const;
   vector<double>  IsoMuEtaVec_() const;
   vector<double>  IsoMuPhiVec_() const;
   vector<double>  IsoPionPtVec_() const;
   vector<double>  IsoPionEtaVec_() const;
   vector<double>  IsoPionPhiVec_() const;


};//end of class Events
#endif
