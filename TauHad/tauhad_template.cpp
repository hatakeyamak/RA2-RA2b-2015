// Determine the tau response templates which are distribution functions of the ratio (tauJet pt)/(reconstructed Jet pt) at diffrent pt. 
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
if( pt < 20.) {
std::cerr << "\n\nERROR in TauResponse::ptBin" << std::endl;
std::cerr << " No response available for pt = " << pt << " < " << 20 << std::endl;
throw std::exception();
}

unsigned int bin=0;
if( pt > 30. ) bin = 1;
if( pt > 50. ) bin = 2;
if( pt > 100. ) bin = 3;
return bin;
}


bool bg_type(string bg_ ,vector<TLorentzVector> * pvec){
if(bg_=="EventsWith_0RecoMuon_0RecoElectron_1tauJet"){return 1;}
} //end of function bg_type

class templatePlotsFunc{///this is the main class

///Some functions

bool findMatchedObject(int &matchedObjIdx,double genTauEta, double genTauPhi,vector<TLorentzVector> vecLvec, double deltaRMax, int ver){
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

if(ver!=0)printf("\n Mathed recoJet info: deltaRMin: %g matchedIdx: %d Pt: %g eta: %g phi: %g \n ",deltaRMin,matchedObjIdx,vecLvec[matchedObjIdx].Pt(),vecLvec[matchedObjIdx].Eta(),vecLvec[matchedObjIdx].Phi());

} else {
matchedObjIdx = -1;
}

return match;
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
vector<TH1D > vec;
map<int, string> cutname;
map<int, string> eventType;
map<string , vector<TH1D> > cut_histvec_map;
map<string, map<string , vector<TH1D> > > map_map;
map<string, histClass> histobjmap;
histClass histObj;
int Nhists,n_elec_mu,n_elec_mu_tot,n_tau_had,n_2tau_had_tot,n_tau_had_tot,nLostLepton;

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
vector<int>  *W_emuVec; /// gen info. electron and muon from W. 
vector<int>  *W_tau_emuVec; /// gen info. tau from W.
vector<int>  *W_tau_prongsVec; // gen info. 

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
double puWeight, totWeight, delphi12, HT;
int cntCSVS, cntNJetsPt30, cntNJetsPt30Eta24, cntNJetsPt50Eta24, cntNJetsPt70Eta24, cntgenTop, cntleptons;
TLorentzVector metLVec;
vector<double> dPhiVec;

double genTauEta;
double genTauPt;
double genTauPhi;
vector<TLorentzVector> vec_Jet_30_24_Lvec;
TLorentzVector tempLvec;
int TauResponse_nBins,Nfailed;

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
bool nomuon(){if(template_nMuons==0)return true; return false;}
bool nolep(){if(template_nElectrons==0 && template_nMuons==0)return true; return false;}
bool Njet_4(){if(cntNJetsPt30Eta24 >= 4)return true; return false;}
bool Njet_4_6(){if(cntNJetsPt30Eta24 >= 4 && cntNJetsPt30Eta24 <= 6)return true; return false;}
bool Njet_7_8(){if(cntNJetsPt30Eta24 >= 7 && cntNJetsPt30Eta24 <= 8)return true; return false;}
bool Njet_9(){if(cntNJetsPt30Eta24 >= 9)return true; return false;}
bool btag_0(){if(nbtag == 0)return true; return false;}
bool btag_1(){if(nbtag == 1)return true; return false;}
bool btag_2(){if(nbtag == 2)return true; return false;}
bool btag_3(){if(nbtag >= 3)return true; return false;}
bool isoTrk(){if(nIsoTrk_ ==0)return true; return false;}

///apply the cuts here
bool checkcut(string ss){
if(ss == cutname[0]){return true;}

if(ss== cutname[1]){if(Njet_4())return true;}
if(ss== cutname[2]){if(Njet_4() && ht_500())return true;}
if(ss== cutname[3]){if(Njet_4()&&ht_500()&&mht_200())return true;}
if(ss== cutname[4]){if(Njet_4()&&ht_500()&&mht_200()&&dphi())return true;}
if(ss== cutname[5]){if(Njet_4()&&ht_500()&&mht_200()&&dphi()&&isoTrk())return true;}

if(ss== cutname[6]){if(Njet_4()&&ht_500()&&mht_200()&&dphi()&&btag_0())return true;}
if(ss== cutname[7]){if(Njet_4()&&ht_500()&&mht_200()&&dphi()&&btag_1())return true;}
if(ss== cutname[8]){if(Njet_4()&&ht_500()&&mht_200()&&dphi()&&btag_2())return true;}
if(ss== cutname[9]){if(Njet_4()&&ht_500()&&mht_200()&&dphi()&&btag_3())return true;}



return false;
}


public:
//constructor
templatePlotsFunc(TTree * ttree_, const std::string sampleKeyString="ttbar", int verbose=0, string Outdir="Results", string inputnumber="00"){

genTauEta=-999.0;
genTauPt=-999.0;
genTauPhi=-999.0;
TauResponse_nBins=4;

//build a vector of histograms
TH1D weight_hist = TH1D("weight", "Weight Distribution", 5,0,5);
vec.push_back(weight_hist);
TH1D RA2HT_hist = TH1D("HT","HT Distribution",50,0,5000);
RA2HT_hist.Sumw2();
vec.push_back(RA2HT_hist);
TH1D RA2MHT_hist = TH1D("MHT","MHT Distribution",100,0,5000);
RA2MHT_hist.Sumw2();
vec.push_back(RA2MHT_hist);
TH1D RA2NJet_hist = TH1D("NJet","Number of Jets Distribution",20,0,20);
RA2NJet_hist.Sumw2();
vec.push_back(RA2NJet_hist);
TH1D RA2NBtag_hist = TH1D("NBtag","Number of Btag Distribution",20,0,20);
RA2NBtag_hist.Sumw2();
vec.push_back(RA2NBtag_hist);
TH1D NLostLep_hist = TH1D("NLostLep","Number of Lost Lepton Distribution",20,0,20);
NLostLep_hist.Sumw2();
vec.push_back(NLostLep_hist);
TH1D nGenTauHad_hist = TH1D("nGenTauHad","Number of Gen. Had. Tau",20,0,20);
nGenTauHad_hist.Sumw2();
vec.push_back(nGenTauHad_hist);

Nhists=((int)(vec.size())-1);//-1 is because weight shouldn't be counted.

//initialize a map between string=cutnames and histvecs. copy one histvec into all of them. The histograms, though, will be filled differently.
cutname[0]="nocut";cutname[1]="Njet_4";cutname[2]="ht_500" ;cutname[3]="mht_200";
cutname[4]="delphi";cutname[5]="iso";
/////////////////////////////////////////////////////////////////////////////////
cutname[6]="CSVM_0";
cutname[7]="CSVM_1";
cutname[8]="CSVM_2";
cutname[9]="CSVM_3";
//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
for(int i=0; i<(int) cutname.size();i++){
cut_histvec_map[cutname[i]]=vec;
}

////////////////////////////////////////////////////////////////////////////////////////
eventType[0]="EventsWith_0RecoMuon_0RecoElectron_1tauJet";

//initialize a map between string and maps. copy the map of histvecs into each
for(int i=0; i< eventType.size();i++){
map_map[eventType[i]]=cut_histvec_map;
}

//initialize histobjmap
for(map<string , vector<TH1D> >::iterator it=cut_histvec_map.begin(); it!=cut_histvec_map.end();it++){
histobjmap[it->first]=histObj;
}



/////////////////////////////////////////////
 // The tau response templates
// They are filled for different bins in generated tau-lepton pt.
std::vector<TH1*> hTauResp(TauResponse_nBins);
for(unsigned int i = 0; i < TauResponse_nBins; ++i){
hTauResp.at(i) = new TH1D(TauResponse_name(i),";p_{T}(visible) / p_{T}(generated-#tau);Probability",50,0.,2.5);
hTauResp.at(i)->Sumw2();
}
/////////////////////////////////////
///The Purpose of the following two histograms is to find the probability as function of pt with wich a tau lepton decays hadronically. One is filled with any tau in the event while the other with only hadronic tau. At the end we divide them. That gives a distributions wich will be used later when simulating Jet_tau's with muons.
TH1D * genTauPtHist = new TH1D("genTauPtHist","genTauPt",10,0,250);
TH1D * genHadTauPtHist = new TH1D("genHadTauPtHist","genHadTauPt",10,0,250);
/////////////////////////////////////


/////////////////////////////////////////////
isData = false;
keyString = sampleKeyString;
TString keyStringT(keyString);
//KH---begins - prepares a few vectors
template_loose_isoTrksLVec = new vector<TLorentzVector>();
loose_isoTrks_iso = new vector<double>();
loose_isoTrks_mtw = new vector<double>();
//KH---ends
template_oriJetsVec = new vector<TLorentzVector>();template_recoJetsBtagCSVS = new vector<double>();
template_genDecayLVec =0;
template_genDecayPdgIdVec =0;template_genDecayIdxVec =0;template_genDecayMomIdxVec =0;
vector<string> *template_genDecayStrVec =0, *template_smsModelFileNameStrVec =0, *template_smsModelStrVec =0;
template_genJetsLVec_myak5GenJetsNoNu =0; template_genJetsLVec_myak5GenJetsNoNuNoStopDecays =0; template_genJetsLVec_myak5GenJetsNoNuOnlyStopDecays =0;
W_emuVec=0; W_tau_emuVec=0; W_tau_prongsVec=0;  

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
n_2tau_had_tot=0;
n_tau_had_tot=0;
Nfailed=0;

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
//
n_tau_had=0;
int tempN=0;///test99 
if(verbose!=0)printf("\n############ \n event: %d \n ",ie);///test99
for(int iv=0; iv<(int)template_genDecayLVec->size(); iv++){
int pdgId = template_genDecayPdgIdVec->at(iv);
if( abs(pdgId) == 15 ){
if(verbose!=0)tempN+=1;///test99
genTauPt=template_genDecayLVec->at(iv).Pt();
genTauEta=template_genDecayLVec->at(iv).Eta();
genTauPhi=template_genDecayLVec->at(iv).Phi();
genTauPtHist->Fill(genTauPt);
int index=template_genDecayIdxVec->at(iv);
for(int ivv=0; ivv<(int)template_genDecayLVec->size(); ivv++){
int secpdg = template_genDecayPdgIdVec->at(ivv);
int MomIndex=template_genDecayMomIdxVec->at(ivv);
if(verbose!=0){////////////test99
if(tempN==1){printf("index: %d  pdgID: %d  MomIndex: %d  pt: %g  phi: %g  eta: %g \n ",template_genDecayIdxVec->at(ivv),secpdg,MomIndex,template_genDecayLVec->at(ivv).Pt(),template_genDecayLVec->at(ivv).Phi(),template_genDecayLVec->at(ivv).Eta());
}}
///////////
if(MomIndex==index && abs(secpdg) > 40){ ///pdgID of hadrons are higher than 40. 
if(verbose!=0){printf("\n \n Found a Hadronic Tau \n \n TauIndex: %d, TauDaughterID: %d  pt: %g  phi: %g  eta: %g \n\n",MomIndex, secpdg,template_genDecayLVec->at(ivv).Pt(),template_genDecayLVec->at(ivv).Phi(),template_genDecayLVec->at(ivv).Eta());} //test99
n_tau_had++;
genHadTauPtHist->Fill(genTauPt);
}
}
}
}
///what is missed in this process of identifying the hadronic tau is when tau decays to w again and the w decays to hadrons. Anyways in this way also there are some netrinos emitted and this events also enters our search region. So we better use W_tau_prongsVec->size(). If it is not zero then we have hadronic tau. 

if(n_tau_had==1  && verbose!=0)n_tau_had_tot+=1;
if(n_tau_had>1 && verbose!=0){
n_2tau_had_tot+=1;
printf("\n Event: %d,  Warning! \n Warning! There  are more than one hadronic tau in the event \n Warning \n Warning! There are are more than one hadronic tau in the event \n ",ie);

}

//printf("W_emuVec size: %d W_tau_emuVec size: %d W_tau_prongsVec size: %d  \n ",W_emuVec->size(),W_tau_emuVec->size(),W_tau_prongsVec->size());

//we are interested in hadronically decaying taus only
if(W_tau_prongsVec->size()==0)continue;

///we want no muon and electron in the event
if(W_emuVec->size()!=0 || W_tau_emuVec->size()!=0)continue;

// Use only events where the tau is inside the muon acceptance
// because lateron we will apply the response to muon+jet events
////////////////////////////////////////////////////////////////////////////if( genTauPt < 20. ) continue;
////////////////////////////////////////////////////////////////////////////if( std::abs(genTauEta) > 2.1 ) continue;

// Do the matching
int tauJetIdx = -1;
const double deltaRMax = genTauPt < 50. ? 0.2 : 0.1; // Increase deltaRMax at low pt to maintain high-enought matching efficiency

//if( !findMatchedObject(tauJetIdx,genTauEta,genTauPhi,vec_Jet_30_24_Lvec,deltaRMax) ) continue;//this also determines tauJetIdx

//cout << "Matched: " << findMatchedObject(tauJetIdx,genTauEta,genTauPhi,* template_oriJetsVec,deltaRMax,verbose) << endl;

if( !findMatchedObject(tauJetIdx,genTauEta,genTauPhi,* template_oriJetsVec,deltaRMax,verbose) ){
if(genTauPt >= 20. && std::abs(genTauEta) <= 2.1 )Nfailed+=1; 
continue;}//this also determines tauJetIdx

if(verbose!=0){printf("Event: %d, tauJetIdx: %d \n",ie,tauJetIdx);
if(tauJetIdx!=-1){
printf("vec_Jet_30_24_Lvec[tauJetIdx].Eta(): %g ,vec_Jet_30_24_Lvec[tauJetIdx].Phi(): %g ,vec_Jet_30_24_Lvec[tauJetIdx].Pt(): %g \n genTauEta: %g, genTauPhi: %g, genTauPt: %g \n",vec_Jet_30_24_Lvec[tauJetIdx].Eta(),vec_Jet_30_24_Lvec[tauJetIdx].Phi(),vec_Jet_30_24_Lvec[tauJetIdx].Pt(),genTauEta,genTauPhi,genTauPt);
}}



nbtag=0;
//Number of B-jets
for(int i=0; i<template_recoJetsBtagCSVS->size();i++){
double pt=template_oriJetsVec->at(i).Pt();
double eta=template_oriJetsVec->at(i).Eta();
if(template_recoJetsBtagCSVS->at(i) > 0.814 /*0.679*/ && pt > 30 && fabs(eta)<2.4 )nbtag+=1;
}//end of the loop
nLeptons= (int)(template_nElectrons+template_nMuons);




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




///////////////////////////////
///////////Closure Test Section
///////////////////////////////

totWeight=template_evtWeight*puWeight;

//build and array that contains the quantities we need a histogram for. Here order is important and must be the same as RA2nocutvec
double eveinfvec[] = {totWeight, HT, template_mht ,(double) cntNJetsPt30Eta24,(double) nbtag};

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



///////////////////////////////
////End of Closure Test Section
///////////////////////////////


// Use only events where the tau is inside the muon acceptance
// because lateron we will apply the response to muon+jet events
if( genTauPt < 20. ) continue;
if( std::abs(genTauEta) > 2.1 ) continue;



// Calculate RA2 selection-variables from "cleaned" jets, i.e. jets withouth the tau-jet
int selNJet = 0; // Number of HT jets (jets pt > 50 GeV and |eta| < 2.5)
for(int jetIdx = 0; jetIdx <(int) vec_Jet_30_24_Lvec.size(); ++jetIdx) { // Loop over reco jets
// Skip this jet if it is the tau
if( jetIdx == tauJetIdx ) continue;
// Calculate NJet
if(  vec_Jet_30_24_Lvec[jetIdx].Pt() > 30. && std::abs(vec_Jet_30_24_Lvec[jetIdx].Eta()) < 2.4 ) selNJet++;
} // End of loop over reco jets

// Select only events with at least 2 HT jets
if( selNJet < 2 ) continue;



// Fill histogram with relative visible energy of the tau
// ("tau response template") for hadronically decaying taus
for(int jetIdx = 0; jetIdx < (int) template_oriJetsVec->size(); ++jetIdx) { // Loop over reco jets
// Select tau jet
if( jetIdx == tauJetIdx ) {
// Get the response pt bin for the tau
const double tauJetPt = template_oriJetsVec->at(jetIdx).Pt();
const unsigned int ptBin = TauResponse_ptBin(genTauPt);
// Fill the corresponding response template
hTauResp.at(ptBin)->Fill( tauJetPt / genTauPt );
break; // End the jet loop once the tau jet has been found
}
} // End of loop over reco jets




}////end of loop over all events

printf(" \n \n We have failed %d times to match a jet with the hadronic GenTau. Number of successful attemts is the number of entries in the nocut histogram. \n \n",Nfailed);

if(verbose!=0){
printf(" \n # of times tau hadronic were in the event: %d \n ",n_tau_had_tot);
printf(" \n # of times 2 tau hadronic were in the event: %d \n ",n_2tau_had_tot);
}
//open a file to write the histograms
sprintf(tempname,"%s/GenInfo_HadTauEstimation_%s_%s.root",Outdir.c_str(),sampleKeyString.c_str(),inputnumber.c_str());
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


///calculate the probability with which tau decays hadronically as function of pt
genHadTauPtHist->Divide(genTauPtHist);

 // Normalize the response distributions to get the probability density
for(unsigned int i = 0; i < hTauResp.size(); ++i) {
if( hTauResp.at(i)->Integral("width") > 0. ) {
////////////////////////////////////if option "width" is specified, the integral is the sum of the bin contents multiplied by the bin width in x.
hTauResp.at(i)->Scale(1./hTauResp.at(i)->Integral("width"));
}
}

// --- Save the Histograms to File -----------------------------------
TFile outFile("HadTau_TauResponseTemplates.root","RECREATE");
TCanvas *c1 = new TCanvas("c1","TauResponseTemplates",10,10,700,900);
for(unsigned int i = 0; i < hTauResp.size(); ++i) {
hTauResp.at(i)->Write();
hTauResp.at(i)->SetLineColor(i);
//hTauResp.at(i)->Draw("same");
}
//c1->Print("HadTau_TauResponseTemplates.pdf");
genHadTauPtHist->Write();
genHadTauPtHist->Draw();
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

