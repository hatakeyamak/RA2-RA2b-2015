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
#include "TH1.h"
#include "TLegend.h"
#include "TVector3.h"
#include "TFile.h"
#include "TChain.h"


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
int template_nMuons, template_nElectrons, template_nIsoTrks_CUT,nIsoTrk_,nLeptons;
double dPhi0, dPhi1, dPhi2; /// delta phi of first three jet with respect to MHT?????????
//double delphi12;
char tempname[200];
vector<TH1D > vec;
map<int, string> eventType;
map<string , vector<TH1D> > cut_histvec_map;
map<string, map<string , vector<TH1D> > > map_map;
int Nhists,n_elec_mu,n_elec_mu_tot,n_tau_had,n_tau_had_tot,nLostLepton;

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

public:
//constructor
templatePlotsFunc(TTree * ttree_, const std::string sampleKeyString="ttbar", int verbose=0, string Outdir="Results", string inputnumber="00"){
//////
genTauEta=-999.0;
genTauPt=-999.0;
genTauPhi=-999.0;

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

eventType[0]="allEvents";

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
cout << " hello " << endl;
cout<<"\n\n"<<keyString.c_str()<<"_Entries : "<<template_Entries<<endl;

if( keyStringT.Contains("Data") ) evtlistFile.open("evtlistData_aftAllCuts.txt");

n_elec_mu_tot=0;
n_tau_had_tot=0;

////Loop over all events
for(int ie=0; ie<template_Entries; ie++){

template_AUX->GetEntry(ie);


//A counter
if(ie % 10000 ==0 )printf("-------------------- %d \n",ie);

if(ie>50000)break;

puWeight = 1.0;
if( !keyStringT.Contains("Signal") && !keyStringT.Contains("Data") ){
// puWeight = weightTruNPV(NumPUInteractions);
}

if( template_oriJetsVec->size() != template_recoJetsBtagCSVS->size() ){
std::cout<<"template_oriJetsVec->size : "<<template_oriJetsVec->size()<<" template_recoJetsBtagCSVS : "<<template_recoJetsBtagCSVS->size()<<std::endl;
}

metLVec.SetPtEtaPhiM(template_met, 0, template_metphi, 0);

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

n_elec_mu=0;
for(int iv=0; iv<(int)template_genDecayLVec->size(); iv++){
int pdgId = template_genDecayPdgIdVec->at(iv);
if( abs(pdgId) == 11 || abs(pdgId) == 13 ) n_elec_mu++;
}
n_elec_mu_tot+=n_elec_mu;

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

genTauEta=template_genDecayLVec->at(iv).Eta();



}
}
cout << " # tau hadronic: " << n_tau_had  << endl;
nbtag=0;
//Number of B-jets
for(int i=0; i<template_recoJetsBtagCSVS->size();i++){
double pt=template_oriJetsVec->at(i).Pt();
double eta=template_oriJetsVec->at(i).Eta();
if(template_recoJetsBtagCSVS->at(i) > 0.814 /*0.679*/ && pt > 30 && fabs(eta)<2.4 )nbtag+=1;
}//end of the loop
nLeptons= (int)(template_nElectrons+template_nMuons);

totWeight=template_evtWeight*puWeight;

///HT calculation. This is because the predefined HT,template_ht, is calculated with jets with pt>50 and eta>2.5. 
HT=0;
for(int i=0; i< template_oriJetsVec->size();i++){
double pt=template_oriJetsVec->at(i).Pt();
double eta=template_oriJetsVec->at(i).Eta();
if(pt>30. && fabs(eta)<2.4)HT+=pt;
}

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


//loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
for(map<string, map<string , vector<TH1D> > >::iterator itt=map_map.begin(); itt!=map_map.end();itt++){//this will be terminated after the cuts

////determine what type of background should pass
if(bg_type(itt->first , template_genDecayLVec)==true){//all the cuts are inside this
//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts


////EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts

}//end of bg_type determination

}//end of loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"


////////////////////////////// End of maintenance section


}////end of loop over all events
/*
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
*/

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



