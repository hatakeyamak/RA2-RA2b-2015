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
#include "tophead.h"
#include "tdrstyle.C"
#include "TColor.h"
#include "TF1.h"
#include "TLegend.h"
#include "TVector3.h"


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

bool bg_type(string bg_ ,vector<TLorentzVector> * pvec){
if(bg_=="allEvents"){return 1;}
} //end of function bg_type

class templatePlotsFunc{///this is the main class
///Some variables
int template_run, template_event, template_lumi, template_nm1, template_n0, template_np1, template_vtxSize;
double template_avg_npv, template_tru_npv;
int template_nJets , nbtag ;
double template_evtWeight;
double template_met, template_metphi;
double template_mht, template_ht, template_mhtphi;
int template_nMuons, template_nElectrons, template_nIsoTrks_CUT,nLeptons;
double dPhi0, dPhi1, dPhi2; /// delta phi of first three jet with respect to MHT?????????
//double delphi12;
char tempname[200];
vector<TH1D > vec;
map<int, string> cutname;
map<int, string> eventType;
map<string , vector<TH1D> > cut_histvec_map;
map<string, map<string , vector<TH1D> > > map_map;
map<string, histClass> histobjmap;
histClass histObj;
int Nhists,n_elec_mu,n_elec_mu_tot,n_tau_had,n_tau_had_tot,nLostLepton;

int loose_nIsoTrks; // number of isolated tracks with Pt>5 GeV and relIso < 0.5
vector<double> *loose_isoTrks_charge; // charge of the loose isolated tracks (see loose_nIsoTrks)
vector<double> *loose_isoTrks_iso; // isolation values (divided by Pt to get relIso) for the loose isolated tracks
vector<int> *loose_isoTrks_pdgId; // pdg id of the loose isolated tracks
vector<TLorentzVector> *loose_isoTrksLVec; // TLorentzVector of the loose isolated tracks (see loose_nIsoTrks)
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
vector<double> *template_recoJetsBtagCSVS;
vector<TLorentzVector> *template_genDecayLVec;
vector<int> *template_genDecayPdgIdVec, *template_genDecayIdxVec, *template_genDecayMomIdxVec;
vector<string>*template_genDecayStrVec,*template_smsModelFileNameStrVec,
*template_smsModelStrVec;
double template_smsModelMotherMass, template_smsModelDaughterMass;
vector<TLorentzVector> *template_genJetsLVec_myak5GenJetsNoNu, *template_genJetsLVec_myak5GenJetsNoNuNoStopDecays, *template_genJetsLVec_myak5GenJetsNoNuOnlyStopDecays;
TTree * template_AUX;
ofstream evtlistFile;
double puWeight, totWeight, delphi12;
int cntCSVS, cntNJetsPt30, cntNJetsPt30Eta24, cntNJetsPt50Eta24, cntNJetsPt70Eta24, cntgenTop, cntleptons;
TLorentzVector metLVec;
vector<double> dPhiVec;



//define different cuts here
bool threejet(){if(template_nJets>=3)return true; return false;}
bool ht(){if(template_ht>=500) return true; return false;}
bool mht(){if(template_mht>=200)return true; return false;}
bool dphi(){if(dPhi0>0.5 && dPhi1>0.3 && dPhi2>0.3)return true; return false;}
bool nolep(){if(template_nElectrons==0 && template_nMuons==0)return true; return false;}
bool fourjet(){if(template_nJets >= 4)return true; return false;}
bool fivejet(){if(template_nJets >= 5)return true; return false;}
bool sixjet(){if(template_nJets >= 6)return true; return false;}
bool highMht(){if(template_mht>=1000)return true; return false;}
bool highHt(){if(template_ht>=2500)return true; return false;}
bool btag_2(){if(nbtag >= 2)return true; return false;}
bool isoTrk(){if(loose_nIsoTrks!=0)return true; return false;}

///apply the cuts here
bool checkcut(string ss){
if(ss == cutname[0])return true;
if(ss== cutname[1]){if(threejet())return true;}
if(ss== cutname[2]){if(threejet() && ht())return true;}
if(ss== cutname[3]){if(threejet()&&ht()&&mht())return true;}
if(ss== cutname[4]){if(threejet()&&ht()&&mht()&&dphi())return true;}
if(ss== cutname[5]){if(threejet()&&ht()&&mht()&&dphi()&&nolep())return true;}
if(ss== cutname[6]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&fourjet())return true;}
if(ss== cutname[7]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&fivejet())return true;}
if(ss== cutname[8]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet())return true;}
if(ss== cutname[9]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highMht())return true;}
if(ss== cutname[10]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highHt())return true;}
if(ss== cutname[11]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highHt()&&highMht())return true;}
if(ss== cutname[12]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&isoTrk())return true;}
if(ss== cutname[13]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&fourjet()&&isoTrk())return true;}
if(ss== cutname[14]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&fivejet()&&isoTrk())return true;}
if(ss== cutname[15]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&isoTrk())return true;}
if(ss== cutname[16]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highMht()&&isoTrk())return true;}
if(ss== cutname[17]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highHt()&&isoTrk())return true;}
if(ss== cutname[18]){if(threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highHt()&&highMht()&&isoTrk())return true;}
if(ss== cutname[19]){if(btag_2())return true;}
if(ss== cutname[20]){if(btag_2()&&threejet())return true;}
if(ss== cutname[21]){if(btag_2()&&threejet() && ht())return true;}
if(ss== cutname[22]){if(btag_2()&&threejet()&&ht()&&mht())return true;}
if(ss== cutname[23]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi())return true;}
if(ss== cutname[24]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep())return true;}
if(ss== cutname[25]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&fourjet())return true;}
if(ss== cutname[26]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&fivejet())return true;}
if(ss== cutname[27]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet())return true;}
if(ss== cutname[28]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highMht())return true;}
if(ss== cutname[29]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highHt())return true;}
if(ss== cutname[30]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highHt()&&highMht())return true;}
if(ss== cutname[31]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&isoTrk())return true;}
if(ss== cutname[32]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&fourjet()&&isoTrk())return true;}
if(ss== cutname[33]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&fivejet()&&isoTrk())return true;}
if(ss== cutname[34]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&isoTrk())return true;}
if(ss== cutname[35]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highMht()&&isoTrk())return true;}
if(ss== cutname[36]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highHt()&&isoTrk())return true;}
if(ss== cutname[37]){if(btag_2()&&threejet()&&ht()&&mht()&&dphi()&&nolep()&&sixjet()&&highHt()&&highMht()&&isoTrk())return true;}
return false;
}

public:
//constructor
templatePlotsFunc(TTree * ttree_, const std::string sampleKeyString="ttbar", int verbose=0, string Outdir="Results", string inputnumber="00"){

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

//initialize a map between string=cutnames and histvecs. copy one histvec into all of them. The histograms, though, will be filled differently.
cutname[0]="RA2nocut";cutname[1]="RA23Jetcut";cutname[2]="RA2HT500cut" ;
cutname[3]="RA2MHT200cut" ;cutname[4]="RA2delphicut" ;
cutname[5]="RA2noleptoncut" ;
cutname[6]="RA24Jetcut" ;cutname[7]="RA25Jetcut" ;
cutname[8]="RA26Jetcut" ;cutname[9]="RA2allbutHT2500cut" ;
cutname[10]="RA2allbutMHT1000cut";cutname[11]= "RA2allcut";

cutname[12]="RA2noleptoncut_isoTrk" ;
cutname[13]="RA24Jetcut_isoTrk" ;cutname[14]="RA25Jetcut_isoTrk" ;
cutname[15]="RA26Jetcut_isoTrk" ;cutname[16]="RA2allbutHT2500cut_isoTrk" ;
cutname[17]="RA2allbutMHT1000cut_isoTrk";cutname[18]= "RA2allcut_isoTrk";

cutname[19]="2b";cutname[20]="b2_3Jetcut";cutname[21]="b2_HT500cut" ;
cutname[22]="b2_MHT200cut" ;cutname[23]="b2_delphicut" ;cutname[24]="b2_noleptoncut" ;
cutname[25]="b2_4Jetcut" ;cutname[26]="b2_5Jetcut" ;cutname[27]="b2_6Jetcut" ;
cutname[28]="b2_allbutHT2500cut" ;cutname[29]="b2_allbutMHT1000cut";cutname[30]= "b2_allcut";

cutname[31]="b2_noleptoncut_isoTrk" ;
cutname[32]="b2_4Jetcut_isoTrk" ;cutname[33]="b2_5Jetcut_isoTrk" ;cutname[34]="b2_6Jetcut_isoTrk" ;
cutname[35]="b2_allbutHT2500cut_isoTrk" ;cutname[36]="b2_allbutMHT1000cut_isoTrk";cutname[37]= "b2_allcut_isoTrk";


for(int i=0; i<(int) cutname.size();i++){
cut_histvec_map[cutname[i]]=vec;
}

eventType[0]="allEvents";

//initialize a map between string and maps. copy the map of histvecs into each
for(int i=0; i< eventType.size();i++){
map_map[eventType[i]]=cut_histvec_map;
}

//initialize histobjmap
for(map<string , vector<TH1D> >::iterator it=cut_histvec_map.begin(); it!=cut_histvec_map.end();it++){
histobjmap[it->first]=histObj;
}

isData = false;
keyString = sampleKeyString;
TString keyStringT(keyString);
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

template_AUX->SetBranchStatus("loose_nIsoTrks", "1");template_AUX->SetBranchAddress("loose_nIsoTrks", &loose_nIsoTrks);
//template_AUX->SetBranchStatus("nIsoTrks_CUT", "1");template_AUX->SetBranchAddress("nIsoTrks_CUT", &nIsoTrks_CUT);
//template_AUX->SetBranchStatus("trksForIsoVeto_charge","1");template_AUX->SetBranchAddress("trksForIsoVeto_charge", &trksForIsoVeto_charge);
//template_AUX->SetBranchStatus("trksForIsoVeto_dz","1");template_AUX->SetBranchAddress("trksForIsoVeto_dz", &trksForIsoVeto_dz);
//template_AUX->SetBranchStatus("loose_isoTrks_charge","1");template_AUX->SetBranchAddress("loose_isoTrks_charge", &loose_isoTrks_charge);
//template_AUX->SetBranchStatus("loose_isoTrks_dz","1");template_AUX->SetBranchAddress("loose_isoTrks_dz", &loose_isoTrks_dz);
//template_AUX->SetBranchStatus("loose_isoTrks_iso","1");template_AUX->SetBranchAddress("loose_isoTrks_iso", &loose_isoTrks_iso);
//template_AUX->SetBranchStatus("loose_isoTrks_mtw", "1");template_AUX->SetBranchAddress("loose_isoTrks_mtw", &loose_isoTrks_mtw);
//####template_AUX->SetBranchStatus("trksForIsoVeto_pdgId","1");template_AUX->SetBranchAddress("trksForIsoVeto_pdgId", &trksForIsoVeto_pdgId);
//template_AUX->SetBranchStatus("trksForIsoVeto_idx","1");template_AUX->SetBranchAddress("trksForIsoVeto_idx", &trksForIsoVeto_idx);
//####template_AUX->SetBranchStatus("loose_isoTrks_pdgId","1");template_AUX->SetBranchAddress("loose_isoTrks_pdgId", &loose_isoTrks_pdgId);
//template_AUX->SetBranchStatus("loose_isoTrks_idx","1");template_AUX->SetBranchAddress("loose_isoTrks_idx", &loose_isoTrks_idx);
//####template_AUX->SetBranchStatus("forVetoIsoTrksidx","1");template_AUX->SetBranchAddress("forVetoIsoTrksidx", &forVetoIsoTrksidx);
//template_AUX->SetBranchStatus("trksForIsoVetoLVec","1");template_AUX->SetBranchAddress("trksForIsoVetoLVec", &trksForIsoVetoLVec);
//####template_AUX->SetBranchStatus("loose_isoTrksLVec","1");template_AUX->SetBranchAddress("loose_isoTrksLVec", &loose_isoTrksLVec);

int template_Entries = template_AUX->GetEntries();
cout<<"\n\n"<<keyString.c_str()<<"_Entries : "<<template_Entries<<endl;

if( keyStringT.Contains("Data") ) evtlistFile.open("evtlistData_aftAllCuts.txt");

n_elec_mu_tot=0;
n_tau_had_tot=0;

//////////////
//Temporary
//int spike[]={1744747,5677166,6998579,11914191,12697016,12855489,12855744,12882112,12929634,13590915,13775071,13813924,13937866,14147203,15404604,15506060,15800935,16042143,16275974,16731997,16939446,17544423,20226465,20906872,23449833,23812799};
/////////////

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
 * printf("loose_nIsoTrks: %d, nIsoTrks_CUT: %d, trksForIsoVeto_charge.size(): %d, loose_isoTrks_charge.size(): %d, loose_isoTrks_iso.size(): %d, trksForIsoVeto_pdgId->size(): %d, loose_isoTrks_pdgId->size(): %d, forVetoIsoTrksidx->size(): %d, loose_isoTrksLVec->size(): %d \n",loose_nIsoTrks,nIsoTrks_CUT,trksForIsoVeto_charge->size(),loose_isoTrks_charge->size(),loose_isoTrks_iso->size(),trksForIsoVeto_pdgId->size(),loose_isoTrks_pdgId->size(), forVetoIsoTrksidx->size(),loose_isoTrksLVec->size());
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
nLostLepton=n_elec_mu-template_nElectrons-template_nMuons;

n_tau_had=0;
for(int iv=0; iv<(int)template_genDecayLVec->size(); iv++){
int pdgId = template_genDecayPdgIdVec->at(iv);
if( abs(pdgId) == 15 ){
int index=template_genDecayIdxVec->at(iv);
for(int ivv=0; ivv<(int)template_genDecayLVec->size(); ivv++){
int MomIndex=template_genDecayMomIdxVec->at(ivv);
int secpdg = template_genDecayPdgIdVec->at(ivv);
if(MomIndex==index && secpdg > 40){
//printf("This is a tau. TauIndex: %d, TauDaughterID: %d \n",MomIndex, secpdg);
n_tau_had++;
}
}
}
}
n_tau_had_tot+=n_tau_had;

nbtag=0;
//Number of B-jets
for(int i=0; i<template_recoJetsBtagCSVS->size();i++){
if(template_recoJetsBtagCSVS->at(i) > 0.679)nbtag+=1;
}//end of the loop
nLeptons= (int)(template_nElectrons+template_nMuons);

totWeight=template_evtWeight*puWeight;

//build and array that contains the quantities we need a histogram for. Here order is important and must be the same as RA2nocutvec
double eveinfvec[] = {totWeight, template_ht, template_mht ,(double) cntNJetsPt50Eta24,(double) nbtag,(double) nLostLepton,(double) n_tau_had }; //the last one gives the RA2 defined number of jets.

//loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
for(map<string, map<string , vector<TH1D> > >::iterator itt=map_map.begin(); itt!=map_map.end();itt++){//this will be terminated after the cuts

////determine what type of background should pass
if(bg_type(itt->first , template_genDecayLVec)==true){//all the cuts are inside this
//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts

//////loop over cut names and fill the histograms
for(map<string , vector<TH1D> >::iterator ite=cut_histvec_map.begin(); ite!=cut_histvec_map.end();ite++){
if(checkcut(ite->first)==true){histobjmap[ite->first].fill(Nhists,&eveinfvec[0] ,&itt->second[ite->first][0]);}
}//end of loop over cut names

////EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts

}//end of bg_type determination

}//end of loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"

//////////////////In this section we would like to find the problematic events, spikes, etc. This section should be commented when maintenance is not needed.
if(template_ht > 4000. && template_mht>200.){
  printf("event#: %d ############################ \n HighMET : MET:%8.1f, MHT:%8.1f \n",ie,template_met,template_mht);
  if(template_recoJetsBtagCSVS->size()!=template_oriJetsVec->size())printf("There is something wrong with the jet and btga vector sizes. \n");
  for(int i = 0; i < cntNJetsPt50Eta24; ++i){
  printf("HighMET : Jet Pt:%8.2f Eta:%5.2f Phi:%5.2f  Beta:%8.2f BTag Value:%g \n",template_oriJetsVec->at(i).Pt(),template_oriJetsVec->at(i).Eta(),template_oriJetsVec->at(i).Phi(),template_oriJetsVec->at(i).Beta(),template_recoJetsBtagCSVS->at(i));
  }
 
 printf("dPhi0: %g dPhi1: %g dPhi2: %g \n",dPhi0,dPhi1,dPhi2);
 printf("delphi12: %g \n",delphi12);


 }

////////////////////////////// End of maintenance section


}////end of loop over all events

//open a file to write the histograms
sprintf(tempname,"%s/results_%s_%s.root",Outdir.c_str(),sampleKeyString.c_str(),inputnumber.c_str());
TFile *resFile = new TFile(tempname, "RECREATE");
TDirectory *cdtoitt;
TDirectory *cdtoit;
// Loop over different event categories (e.g. "All events, Wlnu, Zll, Zvv, etc")
for(int iet=0;iet<(int)eventType.size();iet++){
for(map<string, map<string , vector<TH1D> > >::iterator itt=map_map.begin(); itt!=map_map.end();itt++){
if (eventType[iet]==itt->first){
//KH
////std::cout << (itt->first).c_str() << std::endl;
cdtoitt = resFile->mkdir((itt->first).c_str());
cdtoitt->cd();
for(int i=0; i< (int)cutname.size();i++){
for(map<string , vector<TH1D> >::iterator it=itt->second.begin(); it!=itt->second.end();it++){
if (cutname[i]==it->first){
cdtoit = cdtoitt->mkdir((it->first).c_str());
cdtoit->cd();
int nHist = it->second.size();
for(int i=0; i<nHist; i++){//since we only have 4 type of histograms
sprintf(tempname,"%s_%s_%s",it->second[i].GetName(),(it->first).c_str(),(itt->first).c_str());
it->second[i].Write(tempname);
}
cdtoitt->cd();
}
}
}
}
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

initPUinput("PUData_dist.root", "pileup"); //Handles pileup. Coudln't figure out how. For later ???????????????????????????????

char filenames[500];
vector<string> filesVec;
///read the file names from the .txt files and load them to a vector.
ifstream fin(InRootList.c_str());while(fin.getline(filenames, 500) ){filesVec.push_back(filenames);}
cout<< "\nProcessing " << subSampleKey << " ... " << endl;
TChain *sample_AUX = new TChain("stopTreeMaker/AUX");
for(unsigned int in=0; in<filesVec.size(); in++){ sample_AUX->Add(filesVec.at(in).c_str()); }

templatePlotsFunc(sample_AUX, subSampleKey,atoi(verbosity.c_str()),OutDir,inputNum);

}




int initPUinput(const std::string &puDatafileName, const std::string &puDatahistName){
puWeights_.clear();
TFile *puDatafile = new TFile(puDatafileName.c_str());
TH1D *data_npu_estimated = (TH1D*) puDatafile->Get(puDatahistName.c_str());
double Summer12_S10[60] = {
2.560E-06,
5.239E-06,
1.420E-05,
5.005E-05,
1.001E-04,
2.705E-04,
1.999E-03,
6.097E-03,
1.046E-02,
1.383E-02,
1.685E-02,
2.055E-02,
2.572E-02,
3.262E-02,
4.121E-02,
4.977E-02,
5.539E-02,
5.725E-02,
5.607E-02,
5.312E-02,
5.008E-02,
4.763E-02,
4.558E-02,
4.363E-02,
4.159E-02,
3.933E-02,
3.681E-02,
3.406E-02,
3.116E-02,
2.818E-02,
2.519E-02,
2.226E-02,
1.946E-02,
1.682E-02,
1.437E-02,
1.215E-02,
1.016E-02,
8.400E-03,
6.873E-03,
5.564E-03,
4.457E-03,
3.533E-03,
2.772E-03,
2.154E-03,
1.656E-03,
1.261E-03,
9.513E-04,
7.107E-04,
5.259E-04,
3.856E-04,
2.801E-04,
2.017E-04,
1.439E-04,
1.017E-04,
7.126E-05,
4.948E-05,
3.405E-05,
2.322E-05,
1.570E-05,
5.005E-06
};
puWeights_.resize(60);
double s = 0.0;
for (int npu = 0; npu < 60; ++npu) {
double npu_estimated = data_npu_estimated->GetBinContent(data_npu_estimated->GetXaxis()->FindBin(npu));
puWeights_[npu] = npu_estimated / Summer12_S10[npu];
s += npu_estimated;
}
// normalize weights such that the total sum of weights over the whole sample is 1.0, i.e., sum_i puWeights_[i] * Summer2012[i] should be 1.0 (!)
for (int npu = 0; npu < 60; ++npu) {
puWeights_[npu] /= s;
}
puDatafile->Close();
return 1;
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

