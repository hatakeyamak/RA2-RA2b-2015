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
   TTree *         fChain;
   int             currentEntry_;
   int             template_Entries; 

public:
//constructor
Events(TTree * ttree_, const std::string sampleKeyString="ttbar", int verbose=0);

//Functions
  bool loadNext();
  int nJets() const;
  int nBtags() const;
  int nLeptons() const;
  int nIso() const;
  double weight() const ;
  double ht() const ;
  double mht() const ;
  double deltaPhi1() const ;
  double deltaPhi2() const ;
  double deltaPhi3() const ;

};//end of class Events
#endif
