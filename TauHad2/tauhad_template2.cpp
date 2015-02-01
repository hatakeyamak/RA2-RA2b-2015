// Data-based prediction. In case of W+jets MC, perform closure test

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

double deltaPhi(double phi1, double phi2) {
return TVector2::Phi_mpi_pi(phi1-phi2);
}

double deltaR(double eta1, double eta2, double phi1, double phi2) {
double dphi = deltaPhi(phi1,phi2);
double deta = eta1 - eta2;
return sqrt( deta*deta + dphi*dphi );
}

void TauResponse_checkPtBin(unsigned int ptBin) {
if( ptBin > 3 ) {
std::cerr << "\n\nERROR in TauResponse: pt bin " << ptBin << " out of binning" << std::endl;
throw std::exception();
}
}

TString TauResponse_name(unsigned int ptBin) {
TauResponse_checkPtBin(ptBin);
TString name = "hTauResp_";
name += ptBin;
return name;
}

unsigned int TauResponse_ptBin(double pt) {
if( pt < 10.) {
std::cerr << "\n\nERROR in TauResponse::ptBin" << std::endl;
std::cerr << " No response available for pt = " << pt << " < " << 10 << std::endl;
throw std::exception();
}

unsigned int bin = 0;
if( pt > 30. ) bin = 1;
if( pt > 50. ) bin = 2;
if( pt > 100. ) bin = 3;
return bin;
}

bool bg_type(string bg_ ,vector<TLorentzVector> * pvec){
if(bg_=="allEvents"){return 1;}
} //end of function bg_type

class templatePlotsFunc{///this is the main class

///Some functions

bool findMatchedObject(int &matchedObjIdx,double genTauEta, double genTauPhi,vector<TLorentzVector> vecLvec, double deltaRMax){
matchedObjIdx = -1;
double deltaRMin = 100000.;

for(int objIdx = 0; objIdx < (int) vecLvec.size(); ++objIdx){
const double dr = deltaR(genTauEta,vecLvec[objIdx].Eta(),genTauPhi,vecLvec[objIdx].Phi());
if( dr < deltaRMin ){
deltaRMin = dr;
matchedObjIdx = objIdx;
}
}//end of loop over vec_Jet_30_24_Lvec

bool match = false;
if( deltaRMin < deltaRMax ) {
match = true;
} else {
matchedObjIdx = -1;
}

return match;
}

double getRandom(double muPt_){
int bin = TauResponse_ptBin(muPt_);
return vec_resp[bin]->GetRandom();
}

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
int TauResponse_nBins;
vector<TLorentzVector> vec_recoMuonLvec;
vector<TLorentzVector> vec_recoElecLvec;
double muPt;
double muEta;
double muPhi;
vector<TH1*> vec_resp;
double simTauJetPt; 
double simTauJetEta;
double simTauJetPhi;

public:
//constructor
templatePlotsFunc(TTree * ttree_, const std::string sampleKeyString="ttbar", int verbose=0, string Outdir="Results", string inputnumber="00"){

TauResponse_nBins=4;

//build a vector of histograms
TH1D weight_hist = TH1D("weight", "Weight Distribution", 5,0,5);
vec.push_back(weight_hist);
TH1D RA2HT_hist = TH1D("HT","HT Distribution",50,0,5000);
vec.push_back(RA2HT_hist);
TH1D RA2MHT_hist = TH1D("MHT","MHT Distribution",100,0,5000);
vec.push_back(RA2MHT_hist);
TH1D RA2NJet_hist = TH1D("NJet","Number of Jets Distribution",10,0,20);
vec.push_back(RA2NJet_hist);
TH1D RA2NBtag_hist = TH1D("NBtag","Number of Btag Distribution",20,0,20);
vec.push_back(RA2NBtag_hist);
TH1D NLostLep_hist = TH1D("NLostLep","Number of Lost Lepton Distribution",20,0,20);
vec.push_back(NLostLep_hist);
TH1D nGenTauHad_hist = TH1D("nGenTauHad","Number of Gen. Had. Tau",20,0,20);
vec.push_back(nGenTauHad_hist);

Nhists=((int)(vec.size())-1);//-1 is because weight shouldn't be counted.

////////////////////////////////////////////////////////////////////////////////////////
eventType[0]="allEvents";

/////////////////////////////////////////////
TFile * resp_file = new TFile("../TauHad/HadTau_TauResponseTemplates.root","R");
for(int i=0; i<TauResponse_nBins; i++){
sprintf(histname,"hTauResp_%d",i);
vec_resp.push_back( (TH1D*) resp_file->Get( histname )->Clone() );
}

const TString &respTempl = "../TauHad/HadTau_TauResponseTemplates.root";


const bool isMC = true;

// --- Declare the Output Histograms ---------------------------------
const TString title = isMC ? "Hadronic-Tau Closure Test" : "Hadronic-Tau Prediction";

/*
 // Control plot: muon pt in the control sample
TH1* hMuonPt = new TH1D("hMuonPt",title+";p_{T}(#mu^{gen}) [GeV];N(events)",50,0.,500.);
hMuonPt->Sumw2();

 // Predicted distributions
TH1* hPredHt = new TH1D("hPredHt",title+";H_{T} [GeV];N(events)",25,500.,3000.);
hPredHt->Sumw2();
TH1* hPredMht = new TH1D("hPredMht",title+";#slash{H}_{T} [GeV];N(events)",20,200.,1200.);
hPredMht->Sumw2();
TH1* hPredNJets = new TH1D("hPredNJets",title+";N(jets);N(events)",9,3,12);
hPredNJets->Sumw2();
// In case of MC: true distributions
TH1* hTrueHt = static_cast<TH1*>(hPredHt->Clone("hTrueHt")); /// here "hTrueHt" is the new name. 
TH1* hTrueMht = static_cast<TH1*>(hPredMht->Clone("hTrueMht"));
TH1* hTrueNJets = static_cast<TH1*>(hPredNJets->Clone("hTrueNJets"));

 // Event yields in the different RA2 search bins
// First bin (around 0) is baseline selection
TH1* hPredYields = new TH1D("hPredYields",title+";;N(events)",37,-0.5,36.5);
hPredYields->Sumw2();
hPredYields->GetXaxis()->SetBinLabel(1,"baseline");
for(int bin = 2; bin <= hPredYields->GetNbinsX(); ++bin) {
TString label = "Bin ";
label += bin-1;
hPredYields->GetXaxis()->SetBinLabel(bin,label);
}
TH1* hTrueYields = static_cast<TH1*>(hPredYields->Clone("hTrueYields"));
*/



/////////////////////////////////////////////
isData = false;
keyString = sampleKeyString;
TString keyStringT(keyString);
//KH---begins - prepares a few vectors
template_loose_isoTrksLVec = new vector<TLorentzVector>();
muonsLVec  = new vector<TLorentzVector>();
muonsMtw = 0;
muonsRelIso = 0;
elesLVec  = new vector<TLorentzVector>();
elesMtw = 0;
elesRelIso = 0;
loose_isoTrks_iso = new vector<double>();
loose_isoTrks_mtw = new vector<double>();
//KH---ends
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

//////////////
//Temporary
//int ie;
//for(int is=0; is < 26; is++){
//ie=spike[is];
/////////////

template_AUX->GetEntry(ie);


//A counter
if(ie % 10000 ==0 )printf("-------------------- %d \n",ie);

if(ie>100000)break;

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


// Parsing the gen information ...
cntgenTop = 0, cntleptons =0;
for(int iv=0; iv<(int)template_genDecayLVec->size(); iv++){
int pdgId = template_genDecayPdgIdVec->at(iv);
if( abs(pdgId) == 6 ) cntgenTop ++;
if( abs(pdgId) == 11 || abs(pdgId) == 13 || abs(pdgId) == 15 ) cntleptons++;
}
if( verbose >=1 ){
std::cout<<"\nie : "<<ie<<std::endl;
std::cout<<"genDecayStr : "<<template_genDecayStrVec->front().c_str()<<std::endl;
printf("((pdgId,index/MomIndex):(E/Pt)) \n");
for(int iv=0; iv<(int)template_genDecayLVec->size(); iv++){
int pdgId = template_genDecayPdgIdVec->at(iv);
printf("((%d,%d/%d):(%6.2f/%6.2f)) ", pdgId, template_genDecayIdxVec->at(iv), template_genDecayMomIdxVec->at(iv), template_genDecayLVec->at(iv).E(), template_genDecayLVec->at(iv).Pt());
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////
////Isolated track section
/*if(ie<100){
 * cout << "event#: " << ie << endl;
 * printf("loose_nIsoTrks: %d, nIsoTrks_CUT: %d, trksForIsoVeto_charge.size(): %d, loose_isoTrks_charge.size(): %d, loose_isoTrks_iso.size(): %d, trksForIsoVeto_pdgId->size(): %d, loose_isoTrks_pdgId->size(): %d, forVetoIsoTrksidx->size(): %d, loose_isoTrksLVec->size(): %d \n",loose_nIsoTrks,nIsoTrks_CUT,trksForIsoVeto_charge->size(),loose_isoTrks_charge->size(),loose_isoTrks_iso->size(),trksForIsoVeto_pdgId->size(),loose_isoTrks_pdgId->size(), forVetoIsoTrksidx->size(),template_loose_isoTrksLVec->size());
 * }
 * */

///In this part we would like to identify lost leptons and hadronic taus. To do so we use the generator truth information. We first check how many leptons(e and mu) are in the event and compare with the isolated+reconstructed ones.
n_elec_mu=0;
for(int iv=0; iv<(int)template_genDecayLVec->size(); iv++){
int pdgId = template_genDecayPdgIdVec->at(iv);
if( abs(pdgId) == 11 || abs(pdgId) == 13 ) n_elec_mu++;
}
n_elec_mu_tot+=n_elec_mu;
/*if(ie < 100){
 * printf("event#: %d, #recElec: %d, #recMu: %d, #trueElecMu: %d \n", ie , template_nElectrons , template_nMuons , n_elec_mu);
 * }*/


n_tau_had=0;
for(int iv=0; iv<(int)template_genDecayLVec->size(); iv++){
int pdgId = template_genDecayPdgIdVec->at(iv);
if( abs(pdgId) == 15 ){
int index=template_genDecayIdxVec->at(iv);
for(int ivv=0; ivv<(int)template_genDecayLVec->size(); ivv++){
int secpdg = template_genDecayPdgIdVec->at(ivv);
int MomIndex=template_genDecayMomIdxVec->at(ivv);
if(MomIndex==index && secpdg > 40){ ///pdgID of hadrons are higher than 40. 
//printf("This is a tau. TauIndex: %d, TauDaughterID: %d \n",MomIndex, secpdg);
n_tau_had++;
}
}
}
}

n_tau_had_tot+=n_tau_had;


/////////////////////////////////////////////////////////////////////////////////////
 // Select the control sample:
// - select events with exactly one well-reconstructed, isolated muon
// Use the muon to predict the energy deposits of the
// hadronically decaying tau:
// - scale the muon pt by a random factor drawn from the
// tau-reponse template to simulate the tau measurement
// - use the simulated tau-pt to predict HT, MHT, and N(jets)

///select muons with pt>10. eta<2.4 relIso<.2
vec_recoMuonLvec.clear();
for(int i=0; i< muonsLVec->size(); i++){ 
double pt=muonsLVec->at(i).Pt();
double eta=muonsLVec->at(i).Eta();
double phi=muonsLVec->at(i).Phi();
double e=muonsLVec->at(i).E();
double relIso=muonsRelIso->at(i);
if(pt>10. && fabs(eta)<2.4 && relIso < 0.2){
tempLvec.SetPtEtaPhiE(pt,eta,phi,e);
vec_recoMuonLvec.push_back(tempLvec);
}
}

///select eles with pt>10. eta<2.5 relIso<.2
vec_recoElecLvec.clear();
for(int i=0; i< elesLVec->size(); i++){
double pt=elesLVec->at(i).Pt();
double eta=elesLVec->at(i).Eta();
double phi=elesLVec->at(i).Phi();
double e=elesLVec->at(i).E();
double relIso=elesRelIso->at(i);
if(pt>10. && fabs(eta)<2.5/* && relIso < 0.2*/){
tempLvec.SetPtEtaPhiE(pt,eta,phi,e);
vec_recoElecLvec.push_back(tempLvec);
}
}

//if( template_nMuons == 1 && template_nElectrons == 0 ) {
if( vec_recoMuonLvec.size() == 1 && vec_recoElecLvec.size() == 0 ){
muPt =  vec_recoMuonLvec[0].Pt();
muEta = vec_recoMuonLvec[0].Eta();
muPhi = vec_recoMuonLvec[0].Phi();

// Get random number from tau-response template
// The template is chosen according to the muon pt
const double scale = getRandom(muPt);

simTauJetPt = scale * muPt;
simTauJetEta = muEta;
simTauJetPhi = muPhi;

///From now on we assume there is no muon in the event but we have an extra jet. 


//New HT:
HT+=simTauJetPt;

//New MHT
double mhtX = template_mht*cos(template_mhtphi)-simTauJetPt*cos(simTauJetPhi);///the minus sign is because of Mht definition.
double mhtY = template_mht*sin(template_mhtphi)-simTauJetPt*sin(simTauJetPhi);

//printf("############ \n  mhtX: %g, mhtY: %g \n",mhtX,mhtY);
//printf("template_mht: %g, template_mhtphi: %g, simTauJetPt: %g, simTauJetPhi: %g \n",template_mht,template_mhtphi,simTauJetPt,simTauJetPhi);

template_mht = sqrt(pow(mhtX,2)+pow(mhtY,2));
if(mhtX>0)template_mhtphi = atan(mhtY/mhtX);
else{
if(mhtY>0) template_mhtphi = 3.14+atan(mhtY/mhtX);
else template_mhtphi = -3.14+atan(mhtY/mhtX);
}

//printf("\n template_mht: %g, template_mhtphi: %g \n ", template_mht,template_mhtphi);

/////Now apply the cuts
//lepton veto is already applied. So apply HT and MHT and delPhi, ...


///////??????????????????????????????????????????? We have assumed all the tau's decay hadronically while it is not correct. It should be implementedhere. 

n_tau_had_tot_fromData+=1;


} // End if exactly one muon


/////////////////////////////////////////////////////////////////////////////////////

nbtag=0;
//Number of B-jets
for(int i=0; i<template_recoJetsBtagCSVS->size();i++){
double pt=template_oriJetsVec->at(i).Pt();
double eta=template_oriJetsVec->at(i).Eta();
if(template_recoJetsBtagCSVS->at(i) > 0.814 /*0.679*/ && pt > 30 && fabs(eta)<2.4 )nbtag+=1;
}//end of the loop
nLeptons= (int)(template_nElectrons+template_nMuons);

totWeight=template_evtWeight*puWeight;



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

}////end of loop over all events
printf("genTau: %d , Tau: %d \n ",n_tau_had_tot,n_tau_had_tot_fromData);

delete resp_file;

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

