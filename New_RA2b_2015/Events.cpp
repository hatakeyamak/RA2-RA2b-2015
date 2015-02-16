#include "Events.h"
#include <vector>
#include "TLorentzVector.h"

  double deltaPhi(double phi1, double phi2) {
    return TVector2::Phi_mpi_pi(phi1-phi2);
  }

  double deltaR(double eta1, double eta2, double phi1, double phi2) {
    double dphi = deltaPhi(phi1,phi2);
    double deta = eta1 - eta2;
    return sqrt( deta*deta + dphi*dphi );
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


//Constructor
  Events::Events(TChain * ttree_, const std::string sampleKeyString) : currentEntry_(-1) {

  //Initialize some varaibles
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
    template_oriJetsVec = new vector<TLorentzVector>();template_recoJetsBtagCSVS = new vector<double>();
    template_genDecayLVec = new vector<TLorentzVector>();
    template_genDecayPdgIdVec =0;template_genDecayIdxVec =0;template_genDecayMomIdxVec =0;
    vector<string> *template_genDecayStrVec =0, *template_smsModelFileNameStrVec =0, *template_smsModelStrVec =0;
    template_genJetsLVec_myak5GenJetsNoNu =0; template_genJetsLVec_myak5GenJetsNoNuNoStopDecays =0;
    template_genJetsLVec_myak5GenJetsNoNuOnlyStopDecays =0;
    W_emuVec=0; W_tau_emuVec=0; W_tau_prongsVec=0;
    template_AUX = ttree_;
    template_AUX->SetBranchStatus("*", 0);

  ///the variables
/*
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
*/    template_AUX->SetBranchStatus("ht", 1); template_AUX->SetBranchAddress("ht", &template_ht);
    template_AUX->SetBranchStatus("mht", 1); template_AUX->SetBranchAddress("mht", &template_mht);/*
    template_AUX->SetBranchStatus("loose_isoTrksLVec","1");template_AUX->SetBranchAddress("loose_isoTrksLVec", &template_loose_isoTrksLVec);
    template_AUX->SetBranchStatus("loose_isoTrks_iso","1");template_AUX->SetBranchAddress("loose_isoTrks_iso", &loose_isoTrks_iso);
    template_AUX->SetBranchStatus("loose_isoTrks_mtw", "1");template_AUX->SetBranchAddress("loose_isoTrks_mtw", &loose_isoTrks_mtw);
    template_AUX->SetBranchStatus("loose_nIsoTrks", "1");template_AUX->SetBranchAddress("loose_nIsoTrks", &loose_nIsoTrks);

    template_AUX->SetBranchStatus("muonsLVec","1");template_AUX->SetBranchAddress("muonsLVec", &muonsLVec);
    template_AUX->SetBranchStatus("muonsMtw","1");template_AUX->SetBranchAddress("muonsMtw", &muonsMtw);
    template_AUX->SetBranchStatus("muonsRelIso","1");template_AUX->SetBranchAddress("muonsRelIso", &muonsRelIso);
    template_AUX->SetBranchStatus("elesLVec","1");template_AUX->SetBranchAddress("elesLVec",&elesLVec);
    template_AUX->SetBranchStatus("elesMtw","1");template_AUX->SetBranchAddress("elesMtw", &elesMtw);
    template_AUX->SetBranchStatus("elesRelIso","1");template_AUX->SetBranchAddress("elesRelIso", &elesRelIso);
    template_AUX->SetBranchStatus("W_emuVec","1");template_AUX->SetBranchAddress("W_emuVec", &W_emuVec);
    template_AUX->SetBranchStatus("W_tau_emuVec","1");template_AUX->SetBranchAddress("W_tau_emuVec", &W_tau_emuVec);
    template_AUX->SetBranchStatus("W_tau_prongsVec","1");template_AUX->SetBranchAddress("W_tau_prongsVec", &W_tau_prongsVec);
*/
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

    template_Entries = template_AUX->GetEntries();


  if( keyStringT.Contains("Data") ) evtlistFile.open("evtlistData_aftAllCuts.txt");

  n_elec_mu_tot=0;
  n_tau_had_tot=0;
  n_tau_had_tot_fromData=0;


/*
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

//<remove
  if(template_oriJetsVec->size()==0){
  dPhi0=-99.; dPhi1 =-99.;dPhi2 =-99.;delphi12=-99.;
  }
  else{
  dPhiVec = calcDPhi((*template_oriJetsVec), template_mhtphi, 3, dphiArr);
  //dPhiVec = calcDPhi((*template_oriJetsVec), template_metphi, 3, dphiArr);
  dPhi0 = dPhiVec[0]; dPhi1 = dPhiVec[1]; dPhi2 = dPhiVec[2];
  if(template_oriJetsVec->size() > 1)delphi12= fabs(template_oriJetsVec->at(0).Phi()-template_oriJetsVec->at(1).Phi());else delphi12=-99.;
  }
//remove>
//<remove
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
//remove>

  // Parsing the gen information ...
  cntgenTop = 0, cntleptons =0;
  for(int iv=0; iv<(int)template_genDecayLVec->size(); iv++){
    int pdgId = template_genDecayPdgIdVec->at(iv);
    if( abs(pdgId) == 6 ) cntgenTop ++;
    if( abs(pdgId) == 11 || abs(pdgId) == 13 || abs(pdgId) == 15 ) cntleptons++;
  }



  nbtag=0;
  //Number of B-jets
  for(int i=0; i<template_recoJetsBtagCSVS->size();i++){
    double pt=template_oriJetsVec->at(i).Pt();
    double eta=template_oriJetsVec->at(i).Eta();
    if(template_recoJetsBtagCSVS->at(i) > cutCSVS && pt > 30 && fabs(eta)<2.4 )nbtag+=1;
  }//end of the loop
  nLeptons= (int)(template_nElectrons+template_nMuons);

  totWeight=template_evtWeight*puWeight*0.64*1/(0.9*0.75);//the 0.56 is because only 56% of tau's decay hadronically. Here 0.9 is acceptance and 0.75 is efficiencies of both reconstruction and isolation.


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

//printf("genTau: %d , Tau: %d \n ",n_tau_had_tot,n_tau_had_tot_fromData);

*/

}//end of class constructor Event


/*
  // Event weight (for luminosity and PU profile)
  double Events::weight(int iee) const {template_AUX->GetEntry(iee); return template_evtWeight; }
*/

  // HT 
  double Events::ht(int iee) {
    template_AUX->SetBranchStatus("jetsLVec", 1); template_AUX->SetBranchAddress("jetsLVec", &template_oriJetsVec);
    template_AUX->GetEntry(iee);

    ///HT calculation. This is because the predefined HT,template_ht, is 
    //calculated with jets with pt>50 and eta>2.5.
    HT=0;
  for(int i=0; i< template_oriJetsVec->size();i++){
    double pt=template_oriJetsVec->at(i).Pt();
    double eta=template_oriJetsVec->at(i).Eta();
    if(pt>30. && fabs(eta)<2.4){
    HT+=pt;
    }
  }
 return HT; }
  
  // MHT
  double Events::mht(int iee) const {template_AUX->GetEntry(iee);                                                return template_mht; }

/*
  double Events::mhtPhi(int iee) const {template_AUX->GetEntry(iee); return template_mhtphi; }*/

  // HT jets
  vector<TLorentzVector>  Events::vLJets(int iee) {
    template_AUX->SetBranchStatus("jetsLVec", 1); template_AUX->SetBranchAddress("jetsLVec", &template_oriJetsVec);
    template_AUX->GetEntry(iee); 
    vec_Jet_30_24_Lvec.clear();

    for(int i=0; i< template_oriJetsVec->size();i++){
      double pt=template_oriJetsVec->at(i).Pt();
      double eta=template_oriJetsVec->at(i).Eta();
      double phi=template_oriJetsVec->at(i).Phi();
      double e=template_oriJetsVec->at(i).E();
      if(pt>30. && fabs(eta)<2.4){
        tempLvec.SetPtEtaPhiE(pt,eta,phi,e);
        vec_Jet_30_24_Lvec.push_back(tempLvec); 
      }
    } 
    return vec_Jet_30_24_Lvec;
  }


  // DeltaPhi between leading three MHT jets and MHT
  vector<double> Events::deltaPhiV(int iee) {
    template_AUX->SetBranchStatus("jetsLVec", 1); template_AUX->SetBranchAddress("jetsLVec", &template_oriJetsVec);
    template_AUX->GetEntry(iee);
    if(template_oriJetsVec->size()==0){
      dPhiVec[0]=-99.;dPhiVec[1]=-99.;dPhiVec[2]=-99.; 
    }
    else{
      dPhiVec = calcDPhi((*template_oriJetsVec), template_mhtphi, 3, dphiArr);
    }
    return dPhiVec; 
  }

/*
  // Generator-level decay information
  vector<int>  *Events::W_emuVec_(int iee) const {template_AUX->GetEntry(iee);return W_emuVec;}
  vector<int>  *Events::W_tau_emuVec_(int iee) const {template_AUX->GetEntry(iee); return W_tau_emuVec; }
  vector<int>  *Events::W_tau_prongsVec_(int iee) const {template_AUX->GetEntry(iee);return W_tau_prongsVec;}
  vector<double>  *Events::muonsMtw_(int iee) const {template_AUX->GetEntry(iee);return muonsMtw;}
  // Rec Muon
  vector<TLorentzVector> *Events::muonsLVec_(int iee) const {template_AUX->GetEntry(iee);return muonsLVec;}
  // gen decay particles
  vector<TLorentzVector> *Events::template_genDecayLVec_(int iee) const {template_AUX->GetEntry(iee);return template_genDecayLVec;}
  vector<int> *Events::template_genDecayPdgIdVec_(int iee) const {template_AUX->GetEntry(iee);return template_genDecayPdgIdVec;}
  vector<int> *Events::template_genDecayIdxVec_(int iee) const {template_AUX->GetEntry(iee);return template_genDecayIdxVec;}
  vector<int> *Events::template_genDecayMomIdxVec_(int iee) const {template_AUX->GetEntry(iee);return template_genDecayMomIdxVec;}
*/

/*
  // Transverse mass of leading isolated muon and MET
  double mt() const { return ; }
  // MET for mt computation
  double met() const { return met_; }
  double metPhi() const { return metPhi_; }

  // Well-reconstructed jets
  int jetsN() const { return jetsN_; }
  double*   jetsPt() const { return jetsPt_; }
  double*   jetsEta() const { return jetsEta_; }
  double*   jetsPhi() const { return jetsPhi_; }
  double*   jetsE() const { return jetsE_; }

  // Well-reconstructed muons
  int muonsN() const { return muonsN_; }
  double*   muonsPt() const { return muonsPt_; }
  double*   muonsEta() const { return muonsEta_; }
  double*   muonsPhi() const { return muonsPhi_; }
  double*   muonsE() const { return muonsE_; }

  // Well-reconstructed and isolated muons
  int isoMuonsN() const { return isoMuonsN_; }
  double*   isoMuonsPt() const { return isoMuonsPt_; }
  double*   isoMuonsEta() const { return isoMuonsEta_; }
  double*   isoMuonsPhi() const { return isoMuonsPhi_; }
  double*   isoMuonsE() const { return isoMuonsE_; }

  // Well-reconstructed electrons
  int electronsN() const { return electronsN_; }
  double*   electronsPt() const { return electronsPt_; }
  double*   electronsEta() const { return electronsEta_; }
  double*   electronsPhi() const { return electronsPhi_; }
  double*   electronsE() const { return electronsE_; }

  // Well-reconstructed and isolated electrons
  int isoElectronsN() const { return isoElectronsN_; }
  double*   isoElectronsPt() const { return isoElectronsPt_; }
  double*   isoElectronsEta() const { return isoElectronsEta_; }
  double*   isoElectronsPhi() const { return isoElectronsPhi_; }
  double*   isoElectronsE() const { return isoElectronsE_; }


  // Generatorl-level letpon from W decay
  double genLeptonPt() const { return genLeptonPt_; }
  double genLeptonEta() const { return genLeptonEta_; }
  double genLeptonPhi() const { return genLeptonPhi_; }
  double genLeptonE() const { return genLeptonE_; }
  Int_t genLeptonPdgId() const { return genLeptonPdgId_; }

  // Generator-level lepton from tau decay
  double genLeptonFromTauPt() const { return genLeptonFromTauPt_; }
  double genLeptonFromTauEta() const { return genLeptonFromTauEta_; }
  double genLeptonFromTauPhi() const { return genLeptonFromTauPhi_; }
  double genLeptonFromTauE() const { return genLeptonFromTauE_; }
  Int_t genLeptonFromTauPdgId() const { return genLeptonFromTauPdgId_; }
*/


