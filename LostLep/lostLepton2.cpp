
  // Here all acc and iso&reco are given in Njet-Nbtag-ht-mht
  //........................................................//

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
#include "TH2.h"

#include "interface/LeptonEfficiency.h"
#include "interface/Selection.h"
#include "interface/LeptonAcceptance.h"
#include "interface/utils.h"
#include "interface/utils2.h"


using namespace std;

///Lost lepton specific variables
// === Global Variables ================================================

// Muon-matching related parameters
const double deltaRMax = 0.1;
const double deltaPtMax = 0.2;


// === Helper Functions ================================================

// MHT bins for acceptance parametrisation
std::vector<double> accMHTBinEdges() {
  std::vector<double> bins;
  bins.push_back(200.);
  bins.push_back(300.);
  bins.push_back(400.);
  bins.push_back(600.);
  bins.push_back(1600.);

  return bins;
}

// N(jets) bins for acceptance parametrisation
std::vector<double> accNJetsBinEdges() {
  std::vector<double> bins;
  bins.push_back(2.5);
  bins.push_back(3.5);
  bins.push_back(4.5);
  bins.push_back(5.5);
  bins.push_back(6.5);
  bins.push_back(13.5);

  return bins;
}

  // HT bins for efficiency parametrisation
std::vector<double> effHTBinEdges() {
  std::vector<double> bins;
  bins.push_back(500);
  bins.push_back(600);
  bins.push_back(800);
  bins.push_back(1000);
  bins.push_back(1250);
  bins.push_back(2500);

  return bins;
}

// MHT bins for efficiency parametrisation
std::vector<double> effMHTBinEdges() {
  std::vector<double> bins;
  bins.push_back(200);
  bins.push_back(250);
  bins.push_back(300);
  bins.push_back(350);
  bins.push_back(450);
  bins.push_back(600);
  bins.push_back(2500);

  return bins;
}

// NJets bins for efficiency parametrisation
std::vector<double> effNJetsBinEdges() {
  std::vector<double> bins;
  bins.push_back(2.5);
  bins.push_back(3.5);
  bins.push_back(5.5);
  bins.push_back(7.5);
  bins.push_back(13.5);

  return bins;
}


//global variables.
vector<double> puWeights_;
const double cutCSVS = 0.679;

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
int countJets(const vector<TLorentzVector> &inputJets, const double minAbsEta = -1.0, const double maxAbsEta = -1.0, const double minPt = 30.0, const double maxPt = -1.0);
int countCSVS(const vector<TLorentzVector> &inputJets, const vector<double> &inputCSVS, const double CSVS, const double *jetCutsArr);
int countCSVS(const vector<TLorentzVector> &inputJets, const vector<double> &inputCSVS, const double CSVS = 0.679, const double minAbsEta = -1.0, const double maxAbsEta = -1.0, const double minPt = 30.0, const double maxPt = -1.0);
vector<double> calcDPhi(const vector<TLorentzVector> &inputJets, const double metphi, const int nDPhi, const double *jetCutsArr);
vector<double> calcDPhi(const vector<TLorentzVector> &inputJets, const double metphi, const int nDPhi = 3, const double minAbsEta = -1, const double maxAbsEta = 4.7, const double minPt = 30, const double maxPt = -1);


int initPUinput(const std::string &puDatafileName, const std::string &puDatahistName);

class histClass{
double * a;
TH1D * b_hist;
public:
void fill(int Nhists, double * eveinfarr_, TH1D * hist_){
a = eveinfarr_;
b_hist=hist_;
(*b_hist).Fill(*a);
for(int i=1; i<=Nhists ; i++){
(*(b_hist+i)).Fill(*(a+i),*a);
}
}
};

double deltaPhi(double phi1, double phi2) {
return TVector2::Phi_mpi_pi(phi1-phi2);
}

double deltaR(double eta1, double eta2, double phi1, double phi2) {
double dphi = deltaPhi(phi1,phi2);
double deta = eta1 - eta2;
return sqrt( deta*deta + dphi*dphi );
}

bool bg_type(string bg_ ,vector<TLorentzVector> * pvec){
if(bg_=="allEvents"){return 1;}
} //end of function bg_type


  bool findMatchedObject(int &matchedObjIdx,double genEta, double genPhi,vector<TLorentzVector> vecLvec, double deltaRMax, int ver){
    matchedObjIdx = -1;
    double deltaRMin = 100000.;
    for(int objIdx = 0; objIdx < (int) vecLvec.size(); ++objIdx){
      const double dr = deltaR(genEta,vecLvec[objIdx].Eta(),genPhi,vecLvec[objIdx].Phi());
      if( dr < deltaRMin ){
      deltaRMin = dr;
      matchedObjIdx = objIdx;
      }
    }//end of loop over vec_Jet_30_24_Lvec

    bool match = false;
    if( deltaRMin < deltaRMax ) {
      match = true;

      if(ver!=0)printf("\n Mathed recoJet info: deltaRMin: %g matchedIdx: %d Pt: %g eta: %g phi: %g \n ",deltaRMin,matchedObjIdx,vecLvec[matchedObjIdx].Pt(),vecLvec[matchedObjIdx].Eta(),vecLvec[matchedObjIdx].Phi());

    } else {
      matchedObjIdx = -1;
    }

    return match;
  }




class templatePlotsFunc{///this is the main class

///Some variables
int template_run, template_event, template_lumi, template_nm1, template_n0, template_np1, template_vtxSize;
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
map<int, string> cutname;
map<int, string> eventType;
map<string , vector<TH1D> > cut_histvec_map;
map<string, map<string , vector<TH1D> > > map_map;
map<string, histClass> histobjmap;
histClass histObj;
int Nhists,n_elec_mu,n_elec_mu_tot,n_tau_had,n_tau_had_tot,nLostLepton, n_tau_had_tot_fromData;

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
vector<TLorentzVector> *template_genJetsLVec_myak5GenJetsNoNu, *template_genJetsLVec_myak5GenJetsNoNuNoStopDecays, *template_genJetsLVec_myak5GenJetsNoNuOnlyStopDecays;
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
double muPt;
double muEta;
double muPhi;
double muMtW;
vector<double> vec_recoMuMTW;
vector<TH1*> vec_resp;
vector<int>  *W_emuVec; /// gen info. electron and muon from W.
vector<int>  *W_tau_emuVec; /// gen info. tau from W.
vector<int>  *W_tau_prongsVec; // gen info.


//define different cuts here
bool ht_500(){if(HT>=500) return true; return false;}
bool ht_500_800(){if(HT>=500 && HT<800) return true; return false;}
bool ht_500_1200(){if(HT>=500 && HT<1200)return true; return false;}
bool ht_800_1200(){if(HT>=800 && HT<1200)return true; return false;}
bool ht_800(){if(HT>=800)return true; return false;}
bool ht_1200(){if(HT>=1200)return true; return false;}
bool mht_200(){if(template_mht>=200)return true; return false;}
bool mht_200_500(){if(template_mht>=200 && template_mht<500)return true; return false;}
bool mht_500_750(){if(template_mht>=500 && template_mht<750)return true; return false;}
bool mht_750(){if(template_mht>=750)return true; return false;}
bool dphi(){if(dPhi0>0.5 && dPhi1>0.3 && dPhi2>0.3)return true; return false;}
bool Njet_4(){if(cntNJetsPt30Eta24 >= 4)return true; return false;}
bool Njet_4_6(){if(cntNJetsPt30Eta24 >= 4 && cntNJetsPt30Eta24 <= 6)return true; return false;}
bool Njet_7_8(){if(cntNJetsPt30Eta24 >= 7 && cntNJetsPt30Eta24 <= 8)return true; return false;}
bool Njet_9(){if(cntNJetsPt30Eta24 >= 9)return true; return false;}
bool btag_0(){if(nbtag == 0)return true; return false;}
bool btag_1(){if(nbtag == 1)return true; return false;}
bool btag_2(){if(nbtag == 2)return true; return false;}
bool btag_3(){if(nbtag >= 3)return true; return false;}
bool isoTrk(){if(nIsoTrk_ ==0)return true; return false;}


public:
//constructor
templatePlotsFunc(TTree * ttree_, const std::string sampleKeyString="ttbar", int verbose=0, string Outdir="Results", string inputnumber="00"){

/////////////////////////////////////////////////////////////////////////////////////
// Determine the acceptance and the identification and isolation efficiencies
  // We want to determine efficiencies, so we always have
  // two histograms: the distribution before and after the
  // respective selection cut

  // For muon-acceptance determination. The acceptance is determined
  // in bins of Njet, Nbtag, ht, and mht.
  // There are 3 Njet bins, 4 Nbtag bins, 6 HtMht bins. = 3X4X6 = 72 bins.
  // For muon reconstruction and isolation efficiencies. The efficiencies are
  // determined in bins of Njet, Nbtag, ht, and mht.

//  map<string,int> binMap = utils2::BinMap();
    map<string,int> binMap = utils2::BinMap_NoB();

  int totNbins=binMap.size();

  TH1* hAccAll = new TH1D("hAccAll","Acceptance -- All",totNbins,1,totNbins);
  TH1* hIsoRecoAll = new TH1D("hIsoRecoAll","Efficiency -- All",totNbins,1,totNbins);
  TH1* hAccPass = new TH1D("hAccPass","Acceptance -- Pass",totNbins,1,totNbins);
  TH1* hIsoRecoPass = new TH1D("hIsoRecoPass","Efficiency -- Pass",totNbins,1,totNbins);

  hAccAll->Sumw2();
  hIsoRecoAll->Sumw2();
  hAccPass->Sumw2();
  hIsoRecoPass->Sumw2();

/////////////////////////////////////////////////////////////////////////////////////

//build a vector of histograms
TH1D weight_hist = TH1D("weight", "Weight Distribution", 5,0,5);
vec.push_back(weight_hist);
TH1D RA2HT_hist = TH1D("HT","HT Distribution",50,0,5000);
vec.push_back(RA2HT_hist);
TH1D RA2MHT_hist = TH1D("MHT","MHT Distribution",100,0,5000);
vec.push_back(RA2MHT_hist);
TH1D RA2NJet_hist = TH1D("NJet","Number of Jets Distribution",20,0,20);
vec.push_back(RA2NJet_hist);
TH1D RA2NBtag_hist = TH1D("NBtag","Number of Btag Distribution",20,0,20);
vec.push_back(RA2NBtag_hist);
TH1D RA2MuonPt_hist = TH1D("MuonPt","Pt of muon Distribution",80,0,400);
vec.push_back(RA2MuonPt_hist);
TH1D RA2MtW_hist = TH1D("MtW","Mt of W Distribution",10,0,120);
vec.push_back(RA2MtW_hist);


Nhists=((int)(vec.size())-1);//-1 is because weight shouldn't be counted.

////////////////////////////////////////////////////////////////////////////////////////
eventType[0]="allEvents";


/////////////////////////////////////////////
isData = false;
keyString = sampleKeyString;
TString keyStringT(keyString);
template_loose_isoTrksLVec = new vector<TLorentzVector>();
muonsLVec  = new vector<TLorentzVector>();
muonsMtw = 0;
muonsRelIso = 0;
elesLVec  = new vector<TLorentzVector>();
elesMtw = 0;
elesRelIso = 0;
loose_isoTrks_iso = new vector<double>();
loose_isoTrks_mtw = new vector<double>();
W_emuVec=0; W_tau_emuVec=0; W_tau_prongsVec=0;
template_oriJetsVec = new vector<TLorentzVector>();template_recoJetsBtagCSVS = new vector<double>();
template_genDecayLVec =0;
template_genDecayPdgIdVec =0;template_genDecayIdxVec =0;template_genDecayMomIdxVec =0;
vector<string> *template_genDecayStrVec =0, *template_smsModelFileNameStrVec =0, *template_smsModelStrVec =0;
template_genJetsLVec_myak5GenJetsNoNu =0; template_genJetsLVec_myak5GenJetsNoNuNoStopDecays =0; template_genJetsLVec_myak5GenJetsNoNuOnlyStopDecays =0;
template_AUX = ttree_;
template_AUX->SetBranchStatus("*", 0);

///the variables

template_AUX->SetBranchStatus("run", 1); template_AUX->SetBranchAddress("run", &template_run);
template_AUX->SetBranchStatus("event", 1); template_AUX->SetBranchAddress("event", &template_event);
template_AUX->SetBranchStatus("lumi", 1); template_AUX->SetBranchAddress("lumi", &template_lumi);
template_AUX->SetBranchStatus("avg_npv", 1); template_AUX->SetBranchAddress("avg_npv", &template_avg_npv);
template_AUX->SetBranchStatus("nm1", 1); template_AUX->SetBranchAddress("nm1", &template_nm1);
template_AUX->SetBranchStatus("n0", 1); template_AUX->SetBranchAddress("n0", &template_n0);
template_AUX->SetBranchStatus("np1", 1); template_AUX->SetBranchAddress("np1", &template_np1);
template_AUX->SetBranchStatus("tru_npv", 1); template_AUX->SetBranchAddress("tru_npv", &template_tru_npv);
template_AUX->SetBranchStatus("vtxSize", 1); template_AUX->SetBranchAddress("vtxSize", &template_vtxSize);
template_AUX->SetBranchStatus("nJets", 1); template_AUX->SetBranchAddress("nJets", &template_nJets);
template_AUX->SetBranchStatus("jetsLVec", 1); template_AUX->SetBranchAddress("jetsLVec", &template_oriJetsVec);
template_AUX->SetBranchStatus("recoJetsBtag_0", 1); template_AUX->SetBranchAddress("recoJetsBtag_0", &template_recoJetsBtagCSVS);
template_AUX->SetBranchStatus("evtWeight", 1); template_AUX->SetBranchAddress("evtWeight", &template_evtWeight);
template_AUX->SetBranchStatus("met", 1); template_AUX->SetBranchAddress("met", &template_met);
template_AUX->SetBranchStatus("nIsoTrks_CUT",1); template_AUX->SetBranchAddress("nIsoTrks_CUT", &template_nIsoTrks_CUT);
template_AUX->SetBranchStatus("metphi", 1); template_AUX->SetBranchAddress("metphi", &template_metphi);
template_AUX->SetBranchStatus("mhtphi", 1); template_AUX->SetBranchAddress("mhtphi", &template_mhtphi);
template_AUX->SetBranchStatus("nMuons_CUT", 1); template_AUX->SetBranchAddress("nMuons_CUT", &template_nMuons);
template_AUX->SetBranchStatus("nElectrons_CUT", 1); template_AUX->SetBranchAddress("nElectrons_CUT", &template_nElectrons);
template_AUX->SetBranchStatus("genDecayLVec", 1); template_AUX->SetBranchAddress("genDecayLVec", &template_genDecayLVec);
template_AUX->SetBranchStatus("genDecayPdgIdVec", 1); template_AUX->SetBranchAddress("genDecayPdgIdVec", &template_genDecayPdgIdVec);
template_AUX->SetBranchStatus("genDecayIdxVec", 1); template_AUX->SetBranchAddress("genDecayIdxVec", &template_genDecayIdxVec);
template_AUX->SetBranchStatus("genDecayMomIdxVec", 1); template_AUX->SetBranchAddress("genDecayMomIdxVec", &template_genDecayMomIdxVec);
template_AUX->SetBranchStatus("genDecayStrVec", 1); template_AUX->SetBranchAddress("genDecayStrVec", &template_genDecayStrVec);
template_AUX->SetBranchStatus("ht", 1); template_AUX->SetBranchAddress("ht", &template_ht);
template_AUX->SetBranchStatus("mht", 1); template_AUX->SetBranchAddress("mht", &template_mht);
template_AUX->SetBranchStatus("loose_isoTrksLVec","1");template_AUX->SetBranchAddress("loose_isoTrksLVec", &template_loose_isoTrksLVec);
template_AUX->SetBranchStatus("loose_isoTrks_iso","1");template_AUX->SetBranchAddress("loose_isoTrks_iso", &loose_isoTrks_iso);
template_AUX->SetBranchStatus("loose_isoTrks_mtw", "1");template_AUX->SetBranchAddress("loose_isoTrks_mtw", &loose_isoTrks_mtw);
template_AUX->SetBranchStatus("loose_nIsoTrks", "1");template_AUX->SetBranchAddress("loose_nIsoTrks", &loose_nIsoTrks);

template_AUX->SetBranchStatus("muonsLVec","1");template_AUX->SetBranchAddress("muonsLVec", &muonsLVec);
template_AUX->SetBranchStatus("muonsMtw","1");template_AUX->SetBranchAddress("muonsMtw", &muonsMtw);
template_AUX->SetBranchStatus("muonsRelIso","1");template_AUX->SetBranchAddress("muonsRelIso", &muonsRelIso);
template_AUX->SetBranchStatus("elesLVec","1");template_AUX->SetBranchAddress("elesLVec", &elesLVec);
template_AUX->SetBranchStatus("elesMtw","1");template_AUX->SetBranchAddress("elesMtw", &elesMtw);
template_AUX->SetBranchStatus("elesRelIso","1");template_AUX->SetBranchAddress("elesRelIso", &elesRelIso);

    template_AUX->SetBranchStatus("W_emuVec","1");template_AUX->SetBranchAddress("W_emuVec", &W_emuVec);
    template_AUX->SetBranchStatus("W_tau_emuVec","1");template_AUX->SetBranchAddress("W_tau_emuVec", &W_tau_emuVec);
    template_AUX->SetBranchStatus("W_tau_prongsVec","1");template_AUX->SetBranchAddress("W_tau_prongsVec", &W_tau_prongsVec);



//template_AUX->SetBranchStatus("nIsoTrks_CUT", "1");template_AUX->SetBranchAddress("nIsoTrks_CUT", &nIsoTrks_CUT);
//template_AUX->SetBranchStatus("trksForIsoVeto_charge","1");template_AUX->SetBranchAddress("trksForIsoVeto_charge", &trksForIsoVeto_charge);
//template_AUX->SetBranchStatus("trksForIsoVeto_dz","1");template_AUX->SetBranchAddress("trksForIsoVeto_dz", &trksForIsoVeto_dz);
//template_AUX->SetBranchStatus("loose_isoTrks_charge","1");template_AUX->SetBranchAddress("loose_isoTrks_charge", &loose_isoTrks_charge);
//template_AUX->SetBranchStatus("loose_isoTrks_dz","1");template_AUX->SetBranchAddress("loose_isoTrks_dz", &loose_isoTrks_dz);
//####template_AUX->SetBranchStatus("trksForIsoVeto_pdgId","1");template_AUX->SetBranchAddress("trksForIsoVeto_pdgId", &trksForIsoVeto_pdgId);
//template_AUX->SetBranchStatus("trksForIsoVeto_idx","1");template_AUX->SetBranchAddress("trksForIsoVeto_idx", &trksForIsoVeto_idx);
//####template_AUX->SetBranchStatus("loose_isoTrks_pdgId","1");template_AUX->SetBranchAddress("loose_isoTrks_pdgId", &loose_isoTrks_pdgId);
//template_AUX->SetBranchStatus("loose_isoTrks_idx","1");template_AUX->SetBranchAddress("loose_isoTrks_idx", &loose_isoTrks_idx);
//####template_AUX->SetBranchStatus("forVetoIsoTrksidx","1");template_AUX->SetBranchAddress("forVetoIsoTrksidx", &forVetoIsoTrksidx);
//template_AUX->SetBranchStatus("trksForIsoVetoLVec","1");template_AUX->SetBranchAddress("trksForIsoVetoLVec", &trksForIsoVetoLVec);

int template_Entries = template_AUX->GetEntries();
cout<<"\n\n"<<keyString.c_str()<<"_Entries : "<<template_Entries<<endl;

if( keyStringT.Contains("Data") ) evtlistFile.open("evtlistData_aftAllCuts.txt");

n_elec_mu_tot=0;
n_tau_had_tot=0;
n_tau_had_tot_fromData=0;

////Loop over all events
for(int ie=0; ie<template_Entries; ie++){

template_AUX->GetEntry(ie);


//A counter
if(ie % 10000 ==0 )printf("-------------------- %d \n",ie);

//if(ie>10000)break;

puWeight = 1.0;
if( !keyStringT.Contains("Signal") && !keyStringT.Contains("Data") ){
// puWeight = weightTruNPV(NumPUInteractions);
}

if( template_oriJetsVec->size() != template_recoJetsBtagCSVS->size() ){
std::cout<<"template_oriJetsVec->size : "<<template_oriJetsVec->size()<<" template_recoJetsBtagCSVS : "<<template_recoJetsBtagCSVS->size()<<std::endl;
}

metLVec.SetPtEtaPhiM(template_met, 0, template_metphi, 0);
if(template_oriJetsVec->size()==0)cntCSVS=0;else cntCSVS = countCSVS((*template_oriJetsVec), (*template_recoJetsBtagCSVS), cutCSVS, bTagArr);
if(template_oriJetsVec->size()==0)cntNJetsPt30=0;else cntNJetsPt30 = countJets((*template_oriJetsVec), pt30Arr);
if(template_oriJetsVec->size()==0)cntNJetsPt30Eta24=0;else cntNJetsPt30Eta24 = countJets((*template_oriJetsVec), pt30Eta24Arr);
if(template_oriJetsVec->size()==0)cntNJetsPt50Eta24=0;else cntNJetsPt50Eta24 = countJets((*template_oriJetsVec), pt50Eta24Arr);
if(template_oriJetsVec->size()==0)cntNJetsPt70Eta24=0;else cntNJetsPt70Eta24 = countJets((*template_oriJetsVec), pt70Eta24Arr);
if(template_oriJetsVec->size()==0){
dPhi0=-99.; dPhi1 =-99.;dPhi2 =-99.;delphi12=-99.;
}
else{ 
dPhiVec = calcDPhi((*template_oriJetsVec), template_mhtphi, 3, dphiArr);
//dPhiVec = calcDPhi((*template_oriJetsVec), template_metphi, 3, dphiArr);
dPhi0 = dPhiVec[0]; dPhi1 = dPhiVec[1]; dPhi2 = dPhiVec[2];
if(template_oriJetsVec->size() > 1)delphi12= fabs(template_oriJetsVec->at(0).Phi()-template_oriJetsVec->at(1).Phi());else delphi12=-99.;
}


///HT calculation. This is because the predefined HT,template_ht, is calculated with jets with pt>50 and eta>2.5. 
HT=0;
vec_Jet_30_24_Lvec.clear();
for(int i=0; i< template_oriJetsVec->size();i++){
double pt=template_oriJetsVec->at(i).Pt();
double eta=template_oriJetsVec->at(i).Eta();
double phi=template_oriJetsVec->at(i).Phi();
double e=template_oriJetsVec->at(i).E();
if(pt>30. && fabs(eta)<2.4){
HT+=pt;
tempLvec.SetPtEtaPhiE(pt,eta,phi,e);
vec_Jet_30_24_Lvec.push_back(tempLvec); // this vector contains the lorentz vector of reconstructed jets with pt>30 and eta< 2.4
}
}

nbtag=0;
//Number of B-jets
for(int i=0; i<template_recoJetsBtagCSVS->size();i++){
double pt=template_oriJetsVec->at(i).Pt();
double eta=template_oriJetsVec->at(i).Eta();
if(template_recoJetsBtagCSVS->at(i) > 0.814 /*0.679*/ && pt > 30 && fabs(eta)<2.4 )nbtag+=1;
}//end of the loop
nLeptons= (int)(template_nElectrons+template_nMuons);

totWeight=template_evtWeight*puWeight;//the 0.56 is because only 56% of tau's decay hadronically. Here 0.9 is acceptance and 0.75 is efficiencies of both reconstruction and isolation. 


/// nIsoTrk_ calculation.
//printf("\n  loose_isoTrksLVec->size(): %d ,loose_isoTrks_mtw->size(): %d ,loose_isoTrks_iso->size(): %d ",template_loose_isoTrksLVec->size(),loose_isoTrks_mtw->size(),loose_isoTrks_iso->size());
nIsoTrk_ =0;
for(int i=0;i< (int) template_loose_isoTrksLVec->size();i++){
double pt = template_loose_isoTrksLVec->at(i).Pt();
double eta = fabs(template_loose_isoTrksLVec->at(i).Eta());
double reliso = loose_isoTrks_iso->at(i);
double mt_w = loose_isoTrks_mtw->at(i);//This is transverse mass of track and missing Et. 
if(pt > 15 && eta < 2.4 && reliso < 0.1 && mt_w < 100)nIsoTrk_++;
}
//cout << "nIso: " << nIsoTrk_ << endl;


///////////////////////////////////////////
/// Lost Lepton Section

    // Apply the NJets baseline-cut
    if( !Selection::nJets(cntNJetsPt30Eta24) ) continue;
    // Apply the HT and MHT baseline-cuts
    if( !Selection::ht(HT) ) continue;
    if( !Selection::mht(template_mht) ) continue;
    // Apply the delta-phi cuts
    if( !Selection::deltaPhi(dPhi0,dPhi1,dPhi2) ) continue;

if(verbose!=0)printf("\n############ \n event: %d \n ",ie);


    // Select only events where the W decayed
    // - into a muon (pdgId 13)
    // - into a tau (pdgId 15) that decays into a muon

    // either the muon from W decay or the moun from tau decay
    double genMuPt=0.;
    double genMuEta=-99.;
    double genMuPhi=-99.;
    int firstMuId=0;
    vector<TVector3> genMuonVec;
    TVector3 temp3vec;
    genMuonVec.clear(); 
    bool isMuon = false;
    if(verbose!=0)printf(" List of particles: \n");
    for(int i=0; i < (int) template_genDecayPdgIdVec->size();i++){///loop over all particles
      int pdgId = template_genDecayPdgIdVec->at(i);
      if(verbose!=0)printf(" pdg: %d \n",pdgId);
      if(std::abs(pdgId)==13){//see if it is muon
        genMuPt = template_genDecayLVec->at(i).Pt();
        genMuEta = template_genDecayLVec->at(i).Eta();
        genMuPhi = template_genDecayLVec->at(i).Phi();
        isMuon=true;
        firstMuId=pdgId;
        temp3vec.SetPtEtaPhi(genMuPt,genMuEta,genMuPhi);
        genMuonVec.push_back(temp3vec);
      }
      if(pdgId!=firstMuId && std::abs(pdgId)==13){//second muon
        genMuPt = template_genDecayLVec->at(i).Pt();
        genMuEta = template_genDecayLVec->at(i).Eta();
        genMuPhi = template_genDecayLVec->at(i).Phi();
        temp3vec.SetPtEtaPhi(genMuPt,genMuEta,genMuPhi);
        genMuonVec.push_back(temp3vec);

      //swap if the second muon is more energetic
        if( genMuonVec[0].Pt() < genMuonVec[1].Pt() ){
          genMuonVec.push_back(genMuonVec[0]);//now the first entry is at 0 and 2 places. 
        //we want to remove the 0 entry
          genMuonVec.erase(genMuonVec.begin());
        }
      }
    }
    if(verbose!=0){
      printf("isMuon: %d \n " ,isMuon);
      for(int j=0; j < genMuonVec.size(); j++){
      printf("Muon # %d, pt: %g, eta: %g, phi: %g \n ",j,genMuonVec[j].Pt(),genMuonVec[j].Eta(),genMuonVec[j].Phi());
      }
    }

    // ask for exactly one muon
    if( genMuonVec.size() > 1 ) continue;


    if( !( isMuon ) ) continue;

    // Acceptance determination 1: Counter for all events
    // with muons at generator level

//    hAccAll->Fill( binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht).c_str()] ); 
    hAccAll->Fill( binMap[utils2::findBin_NoB(cntNJetsPt30Eta24,HT,template_mht).c_str()] );

    // Check if generator-level muon is in acceptance
    if( genMuonVec[0].Pt() > LeptonAcceptance::muonPtMin() && std::abs(genMuonVec[0].Eta()) < LeptonAcceptance::muonEtaMax() ) {
    if(verbose!=0)printf("Muon is in acceptance \n ");
      // Acceptance determination 2: Counter for only those events
      // with generator-level muons inside acceptance
//      hAccPass->Fill( binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht).c_str()] );
      hAccPass->Fill( binMap[utils2::findBin_NoB(cntNJetsPt30Eta24,HT,template_mht).c_str()] );

      // Reconstruction-efficiency determination 1: Counter for all events
      // with generator-level muons inside acceptance, regardless of whether
      // the muon has also been reconstructed or not.
//      hIsoRecoAll->Fill( binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht).c_str()]);
      hIsoRecoAll->Fill( binMap[utils2::findBin_NoB(cntNJetsPt30Eta24,HT,template_mht).c_str()]);

    // Check if the muon has been reconstructed: check if a reconstructed
    // muon is present in the event that matches the generator-level muon
          // Isolation-efficiency determination 1: Counter for all events with a
          // reconstructed muon that has a generator-level muon match inside the
          // the acceptance, regardless of whether the reconstructed muon is also
          // isolated or not.

      // in R and in pt
      int matchedMuonIdx = -1;
      if( findMatchedObject(matchedMuonIdx,genMuonVec[0].Eta(),genMuonVec[0].Phi(),* muonsLVec,deltaRMax,verbose) ) {
        // Muon is reconstructed

        const double relDeltaPtMu = std::abs(genMuonVec[0].Pt() - muonsLVec->at(matchedMuonIdx).Pt() ) / muonsLVec->at(matchedMuonIdx).Pt() ;

        if(verbose!=0)printf(" relDeltaPtMu: %g \n ",relDeltaPtMu);        

        if( relDeltaPtMu < deltaPtMax ) {
          // and matches generated pt
      if(verbose!=0)printf("Muon is reconstructed \n ");


          // Check if the muon is also isolated: check if an isolated muon is present
          // in the event that matches the reconstructed muon in R
          if(verbose!=0)printf("muonsRelIso->at(matchedMuonIdx): %g Selection::muIso(): %g \n ",muonsRelIso->at(matchedMuonIdx), Selection::muIso() );
          if( muonsRelIso->at(matchedMuonIdx) <=  Selection::muIso() ){
            // Muon is isolated
          if(verbose!=0)printf("Muon is isolated \n ");

          // Reconstruction-efficiency determination 2: Counter for those events
          // with generator-level muons inside acceptance where the muon has also
          // been reconstructed.
            // Isolation-efficiency determination 2: Counter for those events where
            // the muon is also isolated.
//            hIsoRecoPass->Fill( binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht).c_str()] );
            hIsoRecoPass->Fill( binMap[utils2::findBin_NoB(cntNJetsPt30Eta24,HT,template_mht).c_str()] );

          } // End of muon is isolated

        } // End of pt matching    
      } // End of reconstructed muon




    } // End of muon in acceptance


///end of lost lepton section
//////////////////////////////////////////

}////end of loop over all events

/////////////////////////
// Lost lepton section

  // Compute acceptance
  TH1* hAcc = static_cast<TH1*>(hAccPass->Clone("hAcc"));
  hAcc->Divide(hAccPass,hAccAll,1,1,"B");// we use B option here because the two histograms are correlated. see TH1 page in the root manual.

  // Compute efficiencies
  TH1* hEff = static_cast<TH1*>(hIsoRecoPass->Clone("hEff"));
  hEff->Divide(hIsoRecoPass,hIsoRecoAll,1,1,"B");

  if(verbose!=0){
    for(int j=1; j<= totNbins; j++){
    printf("hAccAll: %g hAccPass: %g hAcc: %g      hIsoRecoAll: %g hIsoRecoPass: %g hEff: %g \n ",hAccAll->GetBinContent(j),hAccPass->GetBinContent(j),hAcc->GetBinContent(j),hIsoRecoAll->GetBinContent(j),hIsoRecoPass->GetBinContent(j),hEff->GetBinContent(j));
    }
  }


  // --- Save the Histograms to File -----------------------------------
  sprintf(tempname,"%s/LostLepton2_MuonEfficienciesFrom%s_%s.root",Outdir.c_str(),sampleKeyString.c_str(),inputnumber.c_str());
  TFile outFile(tempname,"RECREATE");
  hAcc->Write();
  hEff->Write();
  hAccAll->Write();
  hAccPass->Write();
  hIsoRecoAll->Write();
  hIsoRecoPass->Write();
  outFile.Close();


// End of lost lepton
////////////////////////

}//end of class constructor templatePlotsFunc
};//end of class templatePlotsFunc



int main(int argc, char *argv[]){

/////////////////////////////////////
if (argc != 6)
{
std::cout << "Please enter something like:  ./main \"filelist_WJets_PU20bx25_100_200.txt\" \"WJets_PU20bx25_100_200\" \"Results\" \"00\" \"0\" " << std::endl;
return EXIT_FAILURE;
}
const string InRootList = argv[1];
const string subSampleKey = argv[2];
const string OutDir = argv[3];
const string inputNum = argv[4];
const string verbosity = argv[5];
//////////////////////////////////////


char filenames[500];
vector<string> filesVec;
///read the file names from the .txt files and load them to a vector.
ifstream fin(InRootList.c_str());while(fin.getline(filenames, 500) ){filesVec.push_back(filenames);}
cout<< "\nProcessing " << subSampleKey << " ... " << endl;
TChain *sample_AUX = new TChain("stopTreeMaker/AUX");
for(unsigned int in=0; in<filesVec.size(); in++){ sample_AUX->Add(filesVec.at(in).c_str()); }

templatePlotsFunc(sample_AUX, subSampleKey,atoi(verbosity.c_str()),OutDir,inputNum);

}





int countCSVS(const vector<TLorentzVector> &inputJets, const vector<double> &inputCSVS, const double CSVS, const double *jetCutsArr){
return countCSVS(inputJets, inputCSVS, CSVS, jetCutsArr[0], jetCutsArr[1], jetCutsArr[2], jetCutsArr[3]);
}
int countCSVS(const vector<TLorentzVector> &inputJets, const vector<double> &inputCSVS, const double CSVS, const double minAbsEta, const double maxAbsEta, const double minPt, const double maxPt){
int cntNJets =0;
for(unsigned int ij=0; ij<inputJets.size(); ij++){
double perjetpt = inputJets[ij].Pt(), perjeteta = inputJets[ij].Eta();
if( ( minAbsEta == -1 || fabs(perjeteta) >= minAbsEta )
&& ( maxAbsEta == -1 || fabs(perjeteta) < maxAbsEta )
&& ( minPt == -1 || perjetpt >= minPt )
&& ( maxPt == -1 || perjetpt < maxPt ) ){
if( inputCSVS[ij] > CSVS ) cntNJets ++;
}
}
return cntNJets;
}

int countJets(const vector<TLorentzVector> &inputJets, const double *jetCutsArr){
return countJets(inputJets, jetCutsArr[0], jetCutsArr[1], jetCutsArr[2], jetCutsArr[3]);
}
int countJets(const vector<TLorentzVector> &inputJets, const double minAbsEta, const double maxAbsEta, const double minPt, const double maxPt){
int cntNJets =0;
for(unsigned int ij=0; ij<inputJets.size(); ij++){
double perjetpt = inputJets[ij].Pt(), perjeteta = inputJets[ij].Eta();
if( ( minAbsEta == -1 || fabs(perjeteta) >= minAbsEta )
&& ( maxAbsEta == -1 || fabs(perjeteta) < maxAbsEta )
&& ( minPt == -1 || perjetpt >= minPt )
&& ( maxPt == -1 || perjetpt < maxPt ) ){
cntNJets ++;
}
}
return cntNJets;
}
vector<double> calcDPhi(const vector<TLorentzVector> &inputJets, const double metphi, const int nDPhi, const double *jetCutsArr){
return calcDPhi(inputJets, metphi, nDPhi, jetCutsArr[0], jetCutsArr[1], jetCutsArr[2], jetCutsArr[3]);
}
vector<double> calcDPhi(const vector<TLorentzVector> &inputJets, const double metphi, const int nDPhi, const double minAbsEta, const double maxAbsEta, const double minPt, const double maxPt){
int cntNJets =0;
vector<double> outDPhiVec(nDPhi, 999);
for(unsigned int ij=0; ij<inputJets.size(); ij++){
double perjetpt = inputJets[ij].Pt(), perjeteta = inputJets[ij].Eta();
if( ( minAbsEta == -1 || fabs(perjeteta) >= minAbsEta )
&& ( maxAbsEta == -1 || fabs(perjeteta) < maxAbsEta )
&& ( minPt == -1 || perjetpt >= minPt )
&& ( maxPt == -1 || perjetpt < maxPt ) ){
if( cntNJets < nDPhi ){
double perDPhi = fabs(TVector2::Phi_mpi_pi( inputJets[ij].Phi() - metphi ));
outDPhiVec[cntNJets] = perDPhi;
}
cntNJets ++;
}
}
return outDPhiVec;///this is a vector whose components are delta phi of each jet with met.
}

