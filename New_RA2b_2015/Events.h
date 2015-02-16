/////
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
#include "TBranch.h"

using namespace std;

//global variables.
  const double cutCSVS = 0.814;

  static const double pt30Arr[] = { -1, -1, 30, -1 };
  static const double pt30Eta24Arr[] = { -1, 2.4, 30, -1 };
  static const double pt50Eta24Arr[] = { -1, 2.4, 50, -1 };
  static const double pt70Eta24Arr[] = { -1, 2.4, 70, -1 };
  static const double dphiArr[] = { -1, 4.7, 30, -1 };
  static const double bTagArr[] = { -1, 2.4, 30, -1 };
  static const double pt50Arr[] = { -1, -1, 50, -1 };
  static const double pt70Arr[] = { -1, -1, 70, -1 };

////Functions and Classses
  int countJets(const vector<TLorentzVector> &inputJets, const double *jetCutsArr);

  int countJets(const vector<TLorentzVector> &inputJets, const double minAbsEta = -1.0, const double maxAbsEta = -1.0, const double minPt = 30.0,      const double maxPt = -1.0);

  int countCSVS(const vector<TLorentzVector> &inputJets, const vector<double> &inputCSVS, const double CSVS, const double *jetCutsArr);

  int countCSVS(const vector<TLorentzVector> &inputJets, const vector<double> &inputCSVS, const double CSVS = 0.679, const double minAbsEta = -1.0,    const double maxAbsEta = -1.0, const double minPt = 30.0, const double maxPt = -1.0);
  vector<double> calcDPhi(const vector<TLorentzVector> &inputJets, const double metphi, const int nDPhi, const double *jetCutsArr);

  vector<double> calcDPhi(const vector<TLorentzVector> &inputJets, const double metphi, const int nDPhi = 3, const double minAbsEta = -1,              const double maxAbsEta = 4.7, const double minPt = 30, const double maxPt = -1);

  int initPUinput(const std::string &puDatafileName, const std::string &puDatahistName);


  double deltaPhi(double phi1, double phi2);

  double deltaR(double eta1, double eta2, double phi1, double phi2);

class Events {

  ///Some variables
    UInt_t template_run, template_event, template_lumi;
    int  template_nm1, template_n0, template_np1, template_vtxSize;
    double template_avg_npv, template_tru_npv;
    int template_nJets , nbtag ;
    double template_evtWeight;
    double template_met, template_metphi;
    double template_mht, template_ht, template_mhtphi;
    int template_nMuons, template_nElectrons, template_nIsoTrks_CUT,nIsoTrk_,nLeptons;
    double dPhi0, dPhi1, dPhi2; /// delta phi of first three jet with respect to MHT?????????
    //double delphi12;
    char tempname[200];
    char histname[200];
    vector<TH1D > vec;
    int n_elec_mu,n_elec_mu_tot,n_tau_had,n_tau_had_tot,nLostLepton, n_tau_had_tot_fromData;
    int currentEntry_ , template_Entries;
    int loose_nIsoTrks; // number of isolated tracks with Pt>5 GeV and relIso < 0.5
    vector<double> *loose_isoTrks_charge; // charge of the loose isolated tracks (see loose_nIsoTrks)
    vector<double> *loose_isoTrks_iso; // isolation values (divided by Pt to get relIso) for the loose isolated tracks
    vector<int> *loose_isoTrks_pdgId; // pdg id of the loose isolated tracks
    vector<TLorentzVector> * template_loose_isoTrksLVec; // TLorentzVector of the loose isolated tracks (see loose_nIsoTrks)
    //
    int nIsoTrks_CUT; // number of isolated tracks with Pt>10 GeV, dR<0.3, dz<0.05 and relIso<0.1
    vector<int> *forVetoIsoTrksidx; // indices of the isolated tracks (see nIsoTrks_CUT) (pointing to pfCandidate collection)
    //
    vector<double> *trksForIsoVeto_charge; // charges of the charged tracks for isolated veto studies
    vector<int> *trksForIsoVeto_pdgId; // pdg id of the charged tracks for isolated veto studies
    vector<int> *trksForIsoVeto_idx; // indices of the charged tracks for isolated veto studies (pointing to pfCandidate collection)
    //
    vector<double> *trksForIsoVeto_dz; // dz of the charged tracks for isolated veto studies
    vector<double> *loose_isoTrks_dz; // dz of the loose isolated tracks
    vector<double> *loose_isoTrks_mtw; // MT of the loose isolated tracks and MET
    vector<int> *loose_isoTrks_idx; // indices of the loose isolated tracks (pointing to pfCandidate collection)
    vector<TLorentzVector> *trksForIsoVetoLVec; // TLorentzVector of the charged tracks for isolated veto studies
    bool isData;
    string keyString;
    vector<TLorentzVector> *template_oriJetsVec;
    vector<TLorentzVector> *muonsLVec;
    vector<double>  *muonsMtw;
    vector<double>  *muonsRelIso;
    vector<TLorentzVector> *elesLVec;
    vector<double>  *elesMtw;
    vector<double>  *elesRelIso;
    vector<double> *template_recoJetsBtagCSVS;
    vector<TLorentzVector> *template_genDecayLVec;
    vector<int> *template_genDecayPdgIdVec, *template_genDecayIdxVec, *template_genDecayMomIdxVec;
    vector<string>*template_genDecayStrVec,*template_smsModelFileNameStrVec,*template_smsModelStrVec;
    double template_smsModelMotherMass, template_smsModelDaughterMass;
    vector<TLorentzVector> *template_genJetsLVec_myak5GenJetsNoNu, *template_genJetsLVec_myak5GenJetsNoNuNoStopDecays,                                                          *template_genJetsLVec_myak5GenJetsNoNuOnlyStopDecays;
    TTree * template_AUX;
    ofstream evtlistFile;
    double puWeight, totWeight, delphi12, HT;
    int cntCSVS, cntNJetsPt30, cntNJetsPt30Eta24, cntNJetsPt50Eta24, cntNJetsPt70Eta24, cntgenTop, cntleptons;
    TLorentzVector metLVec;
    vector<double> dPhiVec;

    vector<TLorentzVector> vec_Jet_30_24_Lvec;
    TLorentzVector tempLvec;
    vector<TLorentzVector> vec_recoMuonLvec;
    vector<TLorentzVector> vec_recoElecLvec;
    vector<double> vec_recoMuMTW;
    vector<int>  *W_emuVec; /// gen info. electron and muon from W.
    vector<int>  *W_tau_emuVec; /// gen info. tau from W.
    vector<int>  *W_tau_prongsVec; // gen info.


   TBranch        *b_elesLVec;    
  
public:
//constructor
  Events(TChain * ttree_, const std::string sampleKeyString="ttbar");

//Functions
  double weight(int iee) const ;
  double ht(int iee) ;
  double mht(int iee) const ;
  double mhtPhi(int iee) const ;
  vector<double> deltaPhiV(int iee) ;
  vector<int>  *W_emuVec_(int iee) const; 
  vector<int>  *W_tau_emuVec_(int iee) const;
  vector<int>  *W_tau_prongsVec_(int iee) const;
  vector<double>  *muonsMtw_(int iee) const;
  vector<TLorentzVector> *muonsLVec_(int iee) const;
  vector<TLorentzVector> *template_genDecayLVec_(int iee) const;
  vector<TLorentzVector>  vLJets(int iee) ; 
  vector<int> *template_genDecayPdgIdVec_(int iee) const, *template_genDecayIdxVec_(int iee) const, *template_genDecayMomIdxVec_(int iee) const;


};//end of class Events



#endif
