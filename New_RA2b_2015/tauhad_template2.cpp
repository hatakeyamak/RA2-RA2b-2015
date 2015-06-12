
#include "Events.h"
#include "Selection.h"
#include "utils.h"
#include "LeptonEfficiency.h"
#include "LeptonAcceptance.h"
#include "utils2.h"
#include "Lepton_Selection.h"

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
#include <stdio.h>
#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TRandom3.h"

using namespace std;

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

  // Prototype a function // See AN-15-003 for more info.
  double DeltaT(unsigned int i, vector<TVector3> Jet3vec );

  int main(int argc, char *argv[]){
    /////////////////////////////////////
    if (argc != 6)
    {
      std::cout << "Please enter something like: ./run \"filelist_WJets_PU20bx25_100_200.txt\" \"WJets_PU20bx25_100_200\" \"Results\" \"00\" \"0\" " << std::endl;
      return EXIT_FAILURE;
    }
    //get the inputs from user
    const string InRootList = argv[1];
    const string subSampleKey = argv[2];
    const string Outdir = argv[3];
    const string inputnumber = argv[4];
    const string verbosity = argv[5];
    //////////////////////////////////////
    int verbose = atoi(verbosity.c_str());

     //some varaibles
    char filenames[500];
    vector<string> filesVec;
    ifstream fin(InRootList.c_str());
    TChain *sample_AUX = new TChain("TreeMaker2/PreSelection");

    char tempname[200];
    char histname[200];
    vector<TH1D > vec;
    map<int, string> eventType;
    map<string , vector<TH1D> > cut_histvec_map;
    map<string, map<string , vector<TH1D> > > map_map;
    map<string, histClass> histobjmap;
    histClass histObj;
    int TauResponse_nBins=4;
    vector<TH1*> vec_resp, vec_resp_x,vec_resp_y;
    vector<TH2*> vec_resp_xy;
    vector<TVector3> vec_recoMuon3vec;
    vector<TVector3> vec_recoElec3vec;
    TVector3 temp3vec;
    double muPt;
    double muEta;
    double muPhi;
    double simTauJetPt,simTauJetPt_x,simTauJetPt_y,simTauJetPt_xy;
    double simTauJetEta;
    double simTauJetPhi,simTauJetPhi_xy;

    //build a vector of histograms
    TH1D weight_hist = TH1D("weight", "Weight Distribution", 5,0,5);
    vec.push_back(weight_hist);
    TH1D RA2HT_hist = TH1D("HT","HT Distribution",50,0,5000);
    RA2HT_hist.Sumw2();
    vec.push_back(RA2HT_hist);
    TH1D RA2MHT_hist = TH1D("MHT","MHT Distribution",100,0,5000);
    RA2MHT_hist.Sumw2();
    vec.push_back(RA2MHT_hist);
    TH1D RA2MET_hist = TH1D("MET","MET Distribution",100,0,5000);
    RA2MET_hist.Sumw2();
    vec.push_back(RA2MET_hist);
    TH1D RA2DelPhiN_hist = TH1D("DelPhiN","DelPhiN Distribution",20,0,20);
    RA2DelPhiN_hist.Sumw2();
    vec.push_back(RA2DelPhiN_hist);
    TH1D RA2DelPhi1_hist = TH1D("DelPhi1","DelPhi1 Distribution",50,0,5);
    RA2DelPhi1_hist.Sumw2();
    vec.push_back(RA2DelPhi1_hist);
    TH1D RA2DelPhi2_hist = TH1D("DelPhi2","DelPhi2 Distribution",50,0,5);
    RA2DelPhi2_hist.Sumw2();
    vec.push_back(RA2DelPhi2_hist);
    TH1D RA2DelPhi3_hist = TH1D("DelPhi3","DelPhi3 Distribution",50,0,5);
    RA2DelPhi3_hist.Sumw2();
    vec.push_back(RA2DelPhi3_hist);
    TH1D RA2NJet_hist = TH1D("NJet","Number of Jets Distribution",20,0,20);
    RA2NJet_hist.Sumw2();
    vec.push_back(RA2NJet_hist);
    TH1D RA2NBtag_hist = TH1D("NBtag","Number of Btag Distribution",20,0,20);
    RA2NBtag_hist.Sumw2();
    vec.push_back(RA2NBtag_hist);
    TH1D nB_hist = TH1D("nB","Number of B Distribution",20,0,20);
    nB_hist.Sumw2();
    vec.push_back(nB_hist);
    TH1D nB_new_hist = TH1D("nB_new","Number of recalculated B",20,0,20);
    nB_new_hist.Sumw2();
    vec.push_back(nB_new_hist);
    TH1D RA2MuonPt_hist = TH1D("MuonPt","Pt of muon Distribution",80,0,400);
    RA2MuonPt_hist.Sumw2();
    vec.push_back(RA2MuonPt_hist);
    TH1D simTauJetPt_hist = TH1D("simTauJetPt","Pt of simulated tau Jet",80,0,400);
    simTauJetPt_hist.Sumw2();
    vec.push_back(simTauJetPt_hist);
    /*TH1D RA2MtW_hist = TH1D("MtW","Mt of W Distribution",10,0,120);
    RA2MtW_hist.Sumw2();
    vec.push_back(RA2MtW_hist);
    TH1D Bjet_mu_hist = TH1D("Bjet_mu_hist","Is Muon from Bjet? ",2,0,2);
    Bjet_mu_hist.Sumw2();
    vec.push_back(Bjet_mu_hist);*/

    int Nhists=((int)(vec.size())-1);//-1 is because weight shouldn't be counted.


    // Introduce search bin histogram
    map<string,int> binMap_mht_nj = utils2::BinMap_mht_nj();

    // Introduce search bin histogram
    map<string,int> binMap = utils2::BinMap_NoB();
    int totNbins=binMap.size();
    TH1* searchH = new TH1D("searchH","search bin histogram",totNbins,1,totNbins+1);
    searchH->Sumw2();

    // Introduce search bin histogram with bTag bins
    map<string,int> binMap_b = utils2::BinMap();
    int totNbins_b=binMap_b.size();
    TH1* searchH_b = new TH1D("searchH_b","search bin histogram",totNbins_b,1,totNbins_b+1);
    searchH_b->Sumw2();   
 
    // Determine correlation between original and recalculated variables
    TH2 * hCorSearch = new TH2D("hCorSearch","original vs. recalculated SearchBin",totNbins,1,totNbins+1,totNbins,1,totNbins+1);
    TH2 * hCorHT = new TH2D("hCorHT","original vs. recalculated HT",50,0,5000,50,0,5000);
    TH2 * hCorMHT = new TH2D("hCorMHT","original vs. recalculated MHT",100,0,5000,100,0,5000);
    TH2 * hCorNJet = new TH2D("hCorNJet","original vs. recalculated NJet",20,0,20,20,0,20);
    TH2 * hCorNBtag = new TH2D("hCorNBtag","original vs. recalculated NBtag",20,0,20,20,0,20);

    // Determine correlation between original and recalculated variables + nB info
    TH2 * hCorSearch_noW = new TH2D("hCorSearch_noW","original vs. recalculated SearchBin",totNbins,1,totNbins+1,totNbins,1,totNbins+1);
    TH2 * hCorHT_noW = new TH2D("hCorHT_noW","original vs. recalculated HT",50,0,5000,50,0,5000);
    TH2 * hCorMHT_noW = new TH2D("hCorMHT_noW","original vs. recalculated MHT",100,0,5000,100,0,5000);
    TH2 * hCorNJet_noW = new TH2D("hCorNJet_noW","original vs. recalculated NJet",20,0,20,20,0,20);
    TH2 * hCorNBtag_noW = new TH2D("hCorNBtag_noW","original vs. recalculated NBtag",20,0,20,20,0,20);

    // Determine correlation between original and recalculated variables + nB info
    TH2 * hCorSearch_noW_b = new TH2D("hCorSearch_noW_b","original vs. recalculated SearchBin",totNbins_b,1,totNbins_b+1,totNbins_b,1,totNbins_b+1);


    // The tau response templates
    Utils * utils = new Utils();

    ///read the file names from the .txt files and load them to a vector.
    while(fin.getline(filenames, 500) ){filesVec.push_back(filenames);}
    cout<< "\nProcessing " << subSampleKey << " ... " << endl;
    for(unsigned int in=0; in<filesVec.size(); in++){ sample_AUX->Add(filesVec.at(in).c_str()); }


    // --- Analyse the events --------------------------------------------

    // Interface to the event content
    Events * evt = new Events(sample_AUX, subSampleKey,verbose);

    // Get a pointer to the Selection class
    Selection * sel = new Selection();

    // For each selection, cut, make a vector containing the same histograms as those in vec
    for(int i=0; i<(int) sel->cutName().size();i++){
      cut_histvec_map[sel->cutName()[i]]=vec;
    }

    // Define different event categories
    eventType[0]="allEvents";

    //initialize a map between string and maps. copy the map of histvecs into each
    for(int i=0; i< eventType.size();i++){
      map_map[eventType[i]]=cut_histvec_map;
    }

    //initialize histobjmap
    for(map<string , vector<TH1D> >::iterator it=cut_histvec_map.begin(); it!=cut_histvec_map.end();it++){
      histobjmap[it->first]=histObj;
    }


    // Open some files and get the histograms ........................................//


    // Rate of bTagged tau jet
    TFile * bRateFile = new TFile("TauHad/TauBtaggedRate_TTbar_Elog195.root","R");
    sprintf(histname,"TauBtaggedRate");
    TH1D * bRateHist = (TH1D * ) bRateFile->Get(histname)->Clone();

    // Probability of muon coming from Tau
    TFile * Prob_Tau_mu_file = new TFile("TauHad/Probability_Tau_mu_TTbar_Elog195.root","R");
    sprintf(histname,"hProb_Tau_mu");
    TH1D * hProb_Tau_mu =(TH1D *) Prob_Tau_mu_file->Get(histname)->Clone();

    // Acceptance and efficiencies
//    TFile * MuEffAcc_file = new TFile("LostLepton/LostLepton2_MuonEfficienciesFromTTbar_Elog195.root","R");
    TFile * MuEffAcc_file = new TFile("LostLepton/LostLepton2_MuonEfficienciesFromTTbar_Elog212.root","R");
    TFile * MuAcc_file = new TFile("TauHad/LostLepton2_MuonEfficienciesFromTTbar_Elog213.root","R");
    sprintf(histname,"hAcc");
    TH1D * hAcc =(TH1D *) MuAcc_file->Get(histname)->Clone();
    TH1D * hEff =(TH1D *) MuEffAcc_file->Get("hEff")->Clone();


    TFile * MuIsoEff_Arne = new TFile("TauHad/Efficiencies_Arne.root","R");
    TH2F *hMuRecoPTActivity_Arne = (TH2F*)MuIsoEff_Arne->Get("Efficiencies/MuRecoPTActivity");
    TH2F *hMuIsoPTActivity_Arne = (TH2F*)MuIsoEff_Arne->Get("Efficiencies/MuIsoPTActivity");


    // Use Ahmad's tau template
//    TFile * resp_file = new TFile("TauHad/HadTau_TauResponseTemplates_TTbar_.root","R");
    TFile * resp_file = new TFile("TauHad/HadTau_TauResponseTemplates_TTbar_Elog195WithDirectionalTemplates.root","R");
    for(int i=0; i<TauResponse_nBins; i++){
      sprintf(histname,"hTauResp_%d",i);
      vec_resp.push_back( (TH1D*) resp_file->Get( histname )->Clone() );
      sprintf(histname,"hTauResp_%d_x",i);
      vec_resp_x.push_back( (TH1D*) resp_file->Get( histname )->Clone() );
      sprintf(histname,"hTauResp_%d_y",i);
      vec_resp_y.push_back( (TH1D*) resp_file->Get( histname )->Clone() );
      sprintf(histname,"hTauResp_%d_xy",i);
      vec_resp_xy.push_back( (TH2D*) resp_file->Get( histname )->Clone() );
    }

/*
    // Use Rishi's tau template 
    TFile * resp_file = new TFile("TauHad/HadTau_TauResponseTemplates_GenTau_Matching04.root","R");
    for(int i=0; i<TauResponse_nBins; i++){
      sprintf(histname,"hTauResp_%d",i);
      vec_resp.push_back( (TH1D*) resp_file->Get( histname )->Clone() );
    }
*/

    // Some variable for nBtag recalculation
    int c1=0,c2=0,c3=0;
    int nB_new;

    // see how often gen mu doesn't match reco mu
    int GenRecMu_all=0,GenRecMu_fail=0;

    // see how often there are two leptons in the the event
    int dilepton_all=0, dilepton_pass=0;
    int nCleanEve=0;

    // how often a muon does not match a jet
    double muBin[]={0,20,40,60,80,100,1000};
    int muNbin = sizeof(muBin)/sizeof(muBin[0]) -1 ; 
    TH1 * MuJet_all  = new TH1D("MuJet_all","mu match jet vs. pT -- all",muNbin,muBin);
    TH1 * MuJet_fail = new TH1D("MuJet_fail","mu match jet vs. pT -- fail",muNbin,muBin);

    // Determine which model to work with
    int TauHadModel=utils2::TauHadModel;    

    if(TauHadModel!=0 && TauHadModel!=1 && TauHadModel!=2 && TauHadModel!=3 && TauHadModel!=4){
      cout << " The model is not recognized! Please check utils2.h \n ";
      return 1;
    }

    // bootstrap or not ?
    int nLoops;  
    if(utils2::bootstrap)nLoops=50;
    else nLoops=1;

    int testN=0;

    int eventN=0;
    while( evt->loadNext() ){
      eventN++;

      if(eventN>1000000)break;

      // Through out an event that contains HTjets with bad id
      if(evt->JetId()==0)continue;

      nCleanEve++;

      /////////////////////////////////////////////////////////////////////////////////////
      // Select the control sample:
      // - select events with exactly one well-reconstructed, isolated muon
      // Use the muon to predict the energy deposits of the
      // hadronically decaying tau:
      // - scale the muon pt by a random factor drawn from the
      // tau-reponse template to simulate the tau measurement
      // - use the simulated tau-pt to predict HT, MHT, and N(jets)

      if(verbose!=0)printf("@@@@@@@@@@@@@@@@@@@@@@@@ \n eventN: %d \n ",eventN);


      // select muons with pt>20. eta<2.1 relIso<.2
      // vec_recoMuMTW.clear(); ????????????
      vec_recoMuon3vec.clear();
        

vector<int> MuFromTauVec;//Ahmad33
MuFromTauVec.clear();//Ahmad33


/* Ahmad33
      for(int i=0; i< evt->MuPtVec_().size(); i++){
        double pt=evt->MuPtVec_().at(i);
        double eta=evt->MuEtaVec_().at(i);
        double phi=evt->MuPhiVec_().at(i);
Ahmad33 */

      if(TauHadModel>=3){
        for(int i=0; i< evt->MuPtVec_().size(); i++){ // Ahmad33
          double pt=evt->MuPtVec_().at(i); // Ahmad33
          double eta=evt->MuEtaVec_().at(i); // Ahmad33
          double phi=evt->MuPhiVec_().at(i); // Ahmad33
          // double mu_mt_w =muonsMtw->at(i);  ????
          if( pt> LeptonAcceptance::muonPtMin()  && fabs(eta)< LeptonAcceptance::muonEtaMax()  ){
            if(verbose==2)printf(" \n Muons: \n pt: %g eta: %g phi: %g \n ",pt,eta,phi);
            temp3vec.SetPtEtaPhi(pt,eta,phi);
            vec_recoMuon3vec.push_back(temp3vec);
            // vec_recoMuMTW.push_back(mu_mt_w); ???????
          }
        }

      }
      else{
        for(int i=0; i< evt->GenMuPtVec_().size(); i++){ // Ahmad33
          double pt=evt->GenMuPtVec_().at(i); // Ahmad33
          double eta=evt->GenMuEtaVec_().at(i); // Ahmad33
          double phi=evt->GenMuPhiVec_().at(i); // Ahmad33
          // double mu_mt_w =muonsMtw->at(i);  ????
          if( pt> LeptonAcceptance::muonPtMin()  && fabs(eta)< LeptonAcceptance::muonEtaMax()  ){
            if(verbose==2)printf(" \n Muons: \n pt: %g eta: %g phi: %g \n ",pt,eta,phi);
            temp3vec.SetPtEtaPhi(pt,eta,phi);
            vec_recoMuon3vec.push_back(temp3vec);
            MuFromTauVec.push_back(evt->GenMuFromTauVec_()[i]);//Ahmad33
            // vec_recoMuMTW.push_back(mu_mt_w); ???????
          }
        }
      }

      ///select electrons with pt>10. eta<2.5 relIso<.2
      vec_recoElec3vec.clear();
/* Ahmad33
      for(int i=0; i< evt->ElecPtVec_().size(); i++){
        double pt=evt->ElecPtVec_().at(i);
        double eta=evt->ElecEtaVec_().at(i);
        double phi=evt->ElecPhiVec_().at(i);
        // double mu_mt_w =muonsMtw->at(i);  ????
//        if( pt>10. && fabs(eta)< 2.5 ){   // These are applied at the treemaker level. Also,
          // we suppose to use supercluster eta. While here for the cut, we are using gsf. 
Ahmad33 */
      for(int i=0; i< evt->GenElecPtVec_().size(); i++){// Ahmad33
        double pt=evt->GenElecPtVec_().at(i); // Ahmad33
        double eta=evt->GenElecEtaVec_().at(i); // Ahmad33 
        double phi=evt->GenElecPhiVec_().at(i); // Ahmad33

          if(verbose==2)printf(" \n Electrons: \n pt: %g eta: %g phi: %g \n ",pt,eta,phi);
          temp3vec.SetPtEtaPhi(pt,eta,phi);
          vec_recoElec3vec.push_back(temp3vec);

//        }

      }

      if(verbose==1)printf(" \n **************************************** \n #Muons: %d #Electrons: %d \n ****************************** \n ",vec_recoMuon3vec.size(),vec_recoElec3vec.size());

      //if( template_nMuons == 1 && template_nElectrons == 0 ) {
      bool pass1=false;
      if(TauHadModel>=2){if( vec_recoMuon3vec.size() == 1)pass1=true;}
      else {if( vec_recoMuon3vec.size() == 1 && vec_recoElec3vec.size() == 0 )pass1=true;} // recoElec is realy GenElec here

      if(pass1){
        muPt = vec_recoMuon3vec[0].Pt();
        muEta = vec_recoMuon3vec[0].Eta();
        muPhi = vec_recoMuon3vec[0].Phi();
        // muMtW = vec_recoMuMTW[0]; ???????


// Ahmad33
      dilepton_all++;
      bool pass1_1=false;
      if(TauHadModel>=2){if(evt->MuPtVec_().size()>1 || evt->ElecPtVec_().size()>0)pass1_1=true;}
      else{ if(evt->GenMuPtVec_().size()>1 || evt->GenElecPtVec_().size()>0)pass1_1=true;}
      if(pass1_1)continue;
      dilepton_pass++;
// Ahmad33


        // The muon we are using is already part of a jet. (Note: the muon is isolated by 0.2 but jet is much wider.) And,
        // its momentum is used in HT and MHT calculation. We need to subtract this momentum and add the contribution from the simulated tau jet.

        //Identify the jet containing the muon
        const double deltaRMax = 0.4; // 0.4 is delR of jet
        int JetIdx=-1;
        if(verbose!=0 && utils->findMatchedObject(JetIdx,muEta,muPhi,evt->JetsPtVec_(), evt->JetsEtaVec_(), evt->JetsPhiVec_(),deltaRMax,verbose) ){
          printf(" \n **************************************** \n JetIdx: %d \n ",JetIdx);
        }

        GenRecMu_all++;
        // If muon does not match a GenMuon, drop the event. 
        int GenMuIdx=-1;
        if(!utils->findMatchedObject(GenMuIdx,muEta,muPhi,evt->GenMuPtVec_(), evt->GenMuEtaVec_(), evt->GenMuPhiVec_(),deltaRMax,verbose)){
          GenRecMu_fail++;
          if(eventN < 100000){
            printf(" Warning! There is no Gen Muon \n ");
            printf("@@@@@@@@@@@@@@@@@@\n eventN: %d \n MuPt: %g MuEta: %g MuPhi: %g \n ",eventN,muPt,muEta,muPhi);
          }
          for(int i=0; i<evt->GenMuPtVec_().size(); i++){
//          if( evt->GenMuPtVec_()[i] >10. && fabs(evt->GenMuEtaVec_()[i])<2.5 )printf("GenMu#: %d \n GenMuPt: %g GenMuEta: %g GenMuPhi: %g \n ", i,evt->GenMuPtVec_()[i],evt->GenMuEtaVec_()[i],evt->GenMuPhiVec_()[i] );
          }
          continue;
        }



        // start of bootstrapping ( if is on ) 
        for(int l=1; l<=nLoops;l++){
          
          // Get random number from tau-response template
          // or if bootstrap is on read the whole template
          // The template is chosen according to the muon pt
          double scale;
          if(utils2::bootstrap) scale = utils->GetBinValue(muPt,vec_resp,l );
          else scale = utils->getRandom(muPt,vec_resp );
          Double_t scale_x=0,scale_y=0;
          utils->getRandom2(muPt,vec_resp_xy,scale_x,scale_y );

    
          simTauJetPt = scale * muPt;
          simTauJetEta = muEta;
          simTauJetPhi = muPhi;

          double simTauJetPt_x = scale_x * muPt;  
          double simTauJetPt_y = scale_y * muPt;
          simTauJetPhi_xy = muPhi + TMath::ATan2(simTauJetPt_y,simTauJetPt_x);
          simTauJetPt_xy = sqrt( pow(simTauJetPt_x,2)+pow(simTauJetPt_y,2) ); 

          // when bootstapping we work with 1D template. 
          // It was good if we could use 2D ( we are short in time now ) 
          if(utils2::bootstrap){
            simTauJetPhi_xy=simTauJetPhi;
            simTauJetPt_xy=simTauJetPt; 
          } 

          if(verbose!=0)printf(" \n ######### \n scale_x: %g scale_y: %g \n simTauJetPt_x: %g simTauJetPt_y: %g \n simTauJetPt_xy: %g simTauJetPt: %g \n simTauJetPhi_xy: %g simTauJetPhi: %g \n",scale_x,scale_y,simTauJetPt_x,simTauJetPt_y,simTauJetPt_xy,simTauJetPt,simTauJetPhi_xy,simTauJetPhi);


  //######################################################################

          // 3Vec of muon and scaledMu 
          TVector3 SimTauJet3Vec,NewTauJet3Vec,Muon3Vec;
          SimTauJet3Vec.SetPtEtaPhi(simTauJetPt_xy,simTauJetEta,simTauJetPhi_xy);
          Muon3Vec.SetPtEtaPhi(muPt,muEta,muPhi);

          // New ht and mht 
          vector<TVector3> HT3JetVec,MHT3JetVec;
          HT3JetVec.clear();
          MHT3JetVec.clear();
          TVector3 temp3Vec;
          int slimJetIdx=-1;
          MuJet_all->Fill(muPt);
          utils->findMatchedObject(slimJetIdx,muEta,muPhi,evt->slimJetPtVec_(),evt->slimJetEtaVec_(), evt->slimJetPhiVec_(),deltaRMax,verbose);
          // If there is no match, add the tau jet as a new one
          if(slimJetIdx==-1){
            MuJet_fail->Fill(muPt);
            NewTauJet3Vec=SimTauJet3Vec;
            if(NewTauJet3Vec.Pt()>30. && fabs(NewTauJet3Vec.Eta())<2.4)HT3JetVec.push_back(NewTauJet3Vec);
            if(NewTauJet3Vec.Pt()>30. && fabs(NewTauJet3Vec.Eta())<5.)MHT3JetVec.push_back(NewTauJet3Vec);
          }
          for(int i=0;i<evt->slimJetPtVec_().size();i++){
            if(i!=slimJetIdx){
              temp3Vec.SetPtEtaPhi(evt->slimJetPtVec_()[i],evt->slimJetEtaVec_()[i],evt->slimJetPhiVec_()[i]);
              if(evt->slimJetPtVec_()[i]>30. && fabs(evt->slimJetEtaVec_()[i])<2.4)HT3JetVec.push_back(temp3Vec);
              if(evt->slimJetPtVec_()[i]>30. && fabs(evt->slimJetEtaVec_()[i])<5.)MHT3JetVec.push_back(temp3Vec);
            }
            else if(i==slimJetIdx){
              temp3Vec.SetPtEtaPhi(evt->slimJetPtVec_()[i],evt->slimJetEtaVec_()[i],evt->slimJetPhiVec_()[i]);
              NewTauJet3Vec=temp3Vec-Muon3Vec+SimTauJet3Vec;
              if(NewTauJet3Vec.Pt()>30. && fabs(NewTauJet3Vec.Eta())<2.4)HT3JetVec.push_back(NewTauJet3Vec);
              if(NewTauJet3Vec.Pt()>30. && fabs(NewTauJet3Vec.Eta())<5.)MHT3JetVec.push_back(NewTauJet3Vec);
            }
            
          }

          // Order the HT3JetVec and MHT3JetVec based on their pT
          HT3JetVec = utils->Order_the_Vec(HT3JetVec); 
          MHT3JetVec = utils->Order_the_Vec(MHT3JetVec);
  /*
          for(int i=0; i<HT3JetVec.size();i++){
          printf("HT3JetVec[i].Pt(): %g HT3JetVec[i].Eta(): %g HT3JetVec[i].Phi(): %g \n ",HT3JetVec[i].Pt(),HT3JetVec[i].Eta(),HT3JetVec[i].Phi());
          }
          for(int i=0; i<MHT3JetVec.size();i++){
          printf("MHT3JetVec[i].Pt(): %g MHT3JetVec[i].Eta(): %g MHT3JetVec[i].Phi(): %g \n ",MHT3JetVec[i].Pt(),MHT3JetVec[i].Eta(),MHT3JetVec[i].Phi());
          }
  */

          double newHT=0,newMHT=0,newMHTPhi=-1;
          TVector3 newMHT3Vec;
          for(int i=0;i<HT3JetVec.size();i++){
            newHT+=HT3JetVec[i].Pt();
          }        
          for(int i=0;i<MHT3JetVec.size();i++){
            newMHT3Vec-=MHT3JetVec[i];
          }        
          newMHT=newMHT3Vec.Pt();
          newMHTPhi=newMHT3Vec.Phi();

          if(verbose==1)printf("newHT: %g newMHT: %g newMHTPhi: %g \n ",newHT,newMHT,newMHTPhi);

  //######################################################################




          // Do not write number of B if the muon jet is btagged. 
          int nB=evt->nBtags();
          if(JetIdx!=-1 && evt->csvVec()[JetIdx]> 0.814)nB=-1; 
          // Recalculate nBtag
          // From tauhad_template.cpp we know that in 0% of 0B events
          // 2.7% of 1B events, 7.6% of 2B events and 23% of 3+B
          // events, tau jet is btagged(mistagging). On the other hand
          // from nB and evt->nBtags() we know almost none of muon jets
          // are bTagged.
          // This means we should recalculate #Btags. 
          if(evt->nBtags()==0){
            nB_new=evt->nBtags();
          }else if(evt->nBtags()==1){
            nB_new=evt->nBtags();
            c1++;
            if(c1<=3)nB_new++;
            if(c1==100)c1=0;
          }else if(evt->nBtags()==2){
            nB_new=evt->nBtags();
            c2++;
            if(c2<=8)nB_new++;
            if(c2==100)c2=0;
          }else if(evt->nBtags()>=3){
            nB_new=evt->nBtags();
            c3++;
            if(c3<=23)nB_new++;
            if(c3==100)c3=0;
          }         
          
          // New #b
          double NewNB=evt->nBtags();
          // get the rate of tau jet mistaggign as a function of pT.
          double bRate =bRateHist->GetBinContent(bRateHist->GetXaxis()->FindBin(NewTauJet3Vec.Pt()));
          // get a random number between 0 and 1
          TRandom3 * ran = new TRandom3(0);
          double rn = ran->Rndm();
          // If statistics is high enough, in bRate*100 % of cases the random number is smaller than bRate. 
          if(rn < bRate )NewNB++; 
          delete ran;


          if(verbose==2){
            double directHT=0,directMHTX=0,directMHTY=0,directMHT=0;
            printf(" ========\n Jets section: \n ");
            for(int i=0;i<evt->slimJetPtVec_().size();i++){
              printf(" jet#: %d pt: %g eta: %g phi: %g JetID: %d \n ",i+1,evt->slimJetPtVec_()[i],evt->slimJetEtaVec_()[i],evt->slimJetPhiVec_()[i],evt->slimJetID_()[i]);
              if(evt->slimJetPtVec_()[i]>30. && fabs(evt->slimJetEtaVec_()[i]) < 5.){
                directMHTX-=evt->slimJetPtVec_()[i]*cos(evt->slimJetPhiVec_()[i]);
                directMHTY-=evt->slimJetPtVec_()[i]*sin(evt->slimJetPhiVec_()[i]);
              }
              if(evt->slimJetPtVec_()[i]>30. && fabs(evt->slimJetEtaVec_()[i]) < 2.4){
                directHT+=evt->slimJetPtVec_()[i];
              }

            }
            printf("========== \n");
            for(int i=0;i<evt->JetsPtVec_().size();i++){
              printf(" jet#: %d pt: %g eta: %g phi: %g \n ",i+1,evt->JetsPtVec_()[i],evt->JetsEtaVec_()[i],evt->JetsPhiVec_()[i]);
            }
            printf("========== \n");
            directMHT = pow( (directMHTX*directMHTX+directMHTY*directMHTY) ,.5);
            printf("directHT: %g directMHT: %g \n",directHT,directMHT);
            if((int) directHT != (int) evt->ht() )cout << " Warning in HT calc. \n " ;
            if((int) directMHT != (int) evt->mht())cout << " Warning in MHT calc. \n " ;
          }

               
              
          //New MET
          double metX = evt->met()*cos(evt->metphi())-simTauJetPt_xy*cos(simTauJetPhi_xy)+muPt*cos(muPhi);///the minus sign is because of Mht definition.
          double metY = evt->met()*sin(evt->metphi())-simTauJetPt_xy*cos(simTauJetPhi_xy)+muPt*sin(muPhi);

          if(verbose==1)printf("############ \n metX: %g, metY: %g \n",metX,metY);
          if(verbose==1)printf("evt->met: %g, evt->metphi: %g,muPt: %g simTauJetPt: %g, simTauJetPhi_xy: %g \n",evt->met(),evt->metphi(),muPt,simTauJetPt,simTauJetPhi_xy);

          double newMet = sqrt(pow(metX,2)+pow(metY,2));
          double newMetphi=-99.;
          newMetphi=TMath::ATan2(metY,metX);

          if(verbose==1)printf("\n evt->ht(): %g evt->mht(): %g, evt->mhtphi(): %g \n ",evt->ht(),evt->mht(),evt->mhtphi());
          if(verbose==1)printf("\n newMet: %g, newMetphi: %g \n ", newMet,newMetphi);

          // New minDelPhi_N
          double dpnhat[3]; 
          unsigned int goodcount=0;
          for(unsigned int i=0; i< HT3JetVec.size();i++){
            if(goodcount<3 && HT3JetVec[i].Pt() > 30. && fabs( HT3JetVec[i].Eta() ) < 5. ){ 
              float dphi=std::abs(TVector2::Phi_mpi_pi(HT3JetVec[i].Phi() - newMetphi));
              float dT=DeltaT(i,HT3JetVec);
              if(dT/newMet>=1.0)dpnhat[goodcount]=dphi/(TMath::Pi()/2.0);
              else dpnhat[goodcount]=dphi/asin(dT/newMet);
              ++goodcount;
            }
          }// end loop over jets
          float mindpn=9999;
          for(int i=0; i<3; ++i){
            if(mindpn>fabs(dpnhat[i]))mindpn=fabs(dpnhat[i]);
          } 

          if(verbose==1) cout << "\n evt->minDeltaPhiN(): " << evt->minDeltaPhiN() << " mindpn: " << mindpn << endl;



  //#############################################################
          //New #Jet

          int newNJet = HT3JetVec.size(); 
          if(verbose==1)printf("newNJet: %d \n ",newNJet);

  //#############################################################

          // If the jet is dropped, Nbtag should stay the same. Since the muon jet is not btagged, dropping it should not change #b. 
          if( (int) HT3JetVec.size() < (int) evt->nJets() )NewNB=evt->nBtags(); 

          // New dphi1, dphi2, and dphi3
          double newDphi1=-99.,newDphi2=-99.,newDphi3=-99.;
          //first order the jets based on their pT
          double p1=0,p2=0,p3=0;
          int i1=-1,i2=-1,i3=-1;
          for(int i=0; i < HT3JetVec.size(); i++ ){
            if(HT3JetVec[i].Pt()>p1){
              p1=HT3JetVec[i].Pt();
              i1=i;
            }
          }
          for(int i=0; i < HT3JetVec.size(); i++ ){
            if(i==i1)continue;
            if(HT3JetVec[i].Pt()>p2){
              p2=HT3JetVec[i].Pt();
              i2=i;
            }
          }
          for(int i=0; i < HT3JetVec.size(); i++ ){
            if(i==i1 || i==i2)continue;
            if(HT3JetVec[i].Pt()>p3){
              p3=HT3JetVec[i].Pt();
              i3=i;
            }
          }

          if(i1!=-1)newDphi1=fabs(TVector2::Phi_mpi_pi(HT3JetVec[i1].Phi() - newMHTPhi ));
          if(i2!=-1)newDphi2=fabs(TVector2::Phi_mpi_pi(HT3JetVec[i2].Phi() - newMHTPhi ));
          if(i3!=-1)newDphi3=fabs(TVector2::Phi_mpi_pi(HT3JetVec[i3].Phi() - newMHTPhi ));
          
          if(verbose!=0){
            printf("newDphi1: %g newDphi2: %g newDphi3: %g \n ",newDphi1,newDphi2,newDphi3);
            printf("i1: %d p1: %g i2: %d p2: %g i3: %d p3: %g \n ",i1,p1,i2,p2,i3,p3);
            for(int i=0; i < HT3JetVec.size(); i++){
              printf("i: %d HT3JetVec[i].Pt(): %g \n ",i,HT3JetVec[i].Pt());
            }
          }


          // get the effieciencies and acceptance
          // if baseline cuts on the main variables are passed then calculate the efficiencies otherwise simply take 0.75 as the efficiency.
          double Eff,Eff_Arne;

          double activity= utils->MuActivity(muEta,muPhi,evt->JetsPtVec_(),evt->JetsEtaVec_(),evt->JetsPhiVec_(),evt->Jets_chargedEmEnergyFraction_(),evt->Jets_chargedHadronEnergyFraction_());
          if(verbose!=0)cout << " activity: " << activity << endl;

          // Here Eff is not a good naming. What this really mean is efficiency and also isolation together
          Eff_Arne=hMuRecoPTActivity_Arne->GetBinContent(hMuRecoPTActivity_Arne->GetXaxis()->FindBin(muPt),hMuRecoPTActivity_Arne->GetYaxis()->FindBin(activity));

          Eff_Arne*=hMuIsoPTActivity_Arne->GetBinContent(hMuRecoPTActivity_Arne->GetXaxis()->FindBin(muPt),hMuRecoPTActivity_Arne->GetYaxis()->FindBin(activity));


          if(newNJet>=4 && newHT >= 500 && newMHT >= 200){
            // Eff = hEff->GetBinContent(binMap_b[utils2::findBin(newNJet,NewNB,newHT,newMHT)]);
            Eff = hEff->GetBinContent(binMap[utils2::findBin_NoB(newNJet,newHT,newMHT)]); 
          }else{
            Eff=0.75;
          }

          // if baseline cuts on the main variables are passed then calculate the acceptance otherwise simply take 0.9 as the acceptance.
          double Acc;

          if(newNJet>=4 && newHT >= 500 && newMHT >= 200){
            // Acc = hAcc->GetBinContent(binMap_b[utils2::findBin_b(newNJet,NewNB,newHT,newMHT)]);
            // Acc = hAcc->GetBinContent(binMap[utils2::findBin_NoB(newNJet,newHT,newMHT)]);
            Acc = hAcc->GetBinContent(binMap_mht_nj[utils2::findBin_mht_nj(newNJet,newMHT)]);

            // use original ht mht njet to get acc. Becaue mht is different in 1mu event than hadronic event 
            // Or use recomputed ht mht ... when making Acc. 
            //Acc = hAcc->GetBinContent(binMap_mht_nj[utils2::findBin_mht_nj(evt->nJets(),evt->mht())]);
          }else{
            Acc=0.9;
          }

          if(verbose==2 && newNJet>=4 && newHT >= 500 && newMHT >= 200)printf("Eff: %g Acc: %g njet: %d nbtag: %d ht: %g mht: %g binN: %d \n ",Eff,Acc, newNJet,evt->nBtags(),newHT,newMHT, binMap_mht_nj[utils2::findBin_mht_nj(newNJet,newMHT)]);
          if(verbose==2 && newNJet>=4 && newHT >= 500 && newMHT >= 200)printf("Eff_Arne: %g \n" ,Eff_Arne);

          if(Acc==0 || Eff==0){printf("eventN: %d Acc or Eff =0 \n Eff: %g Acc: %g njet: %d nbtag: %d ht: %g mht: %g \n ",eventN,Eff,Acc, newNJet,evt->nBtags(),newHT,newMHT);}
          if(Acc==0)Acc=0.9;
          if(Eff==0)Eff=0.75;
          if(Eff_Arne==0)Eff_Arne=0.75;


          // Not all the muons are coming from W. Some of them are coming from Tau which should not be considered in our estimation.
          double Prob_Tau_mu = hProb_Tau_mu->GetBinContent(hProb_Tau_mu->GetXaxis()->FindBin(muPt));

  //Ahmad33
          if(TauHadModel<4)Acc=1.; 
  //Ahmad33
          if(TauHadModel<3)Eff_Arne=1.; 
  //Ahmad33
          if(TauHadModel < 1)Prob_Tau_mu=0; 

  //        double totWeight=evt->weight()*1*0.64*(1/(Acc*Eff_Arne))*(1-Prob_Tau_mu);
          double totWeight=1*0.64*(1/(Acc*Eff_Arne))*(1-Prob_Tau_mu);//the 0.64 is because only 64% of tau's decay hadronically. Here 0.9 is acceptance and 0.75 is efficiencies of both reconstruction and isolation.

          // dilepton contamination
          if(TauHadModel>=3)totWeight*=1./1.045;

          // if bootstrap is on weigh the events such that 
          // the total number of events remains the same.
          // That means the sum over bootstrapWeights = 1
          // Our templates are made such that area under them = 1

          if(utils2::bootstrap){
            double bootstrapWeight = utils->GetBinContent(muPt,vec_resp,l) * utils->GetBinWidth(muPt,vec_resp,l);
            totWeight*=bootstrapWeight;
          }

          // Apply baseline cuts
          if(newHT>=500. && newMHT >= 200. && newDphi1>0.5 && newDphi2>0.5 && newDphi3>0.3 && newNJet >= 4   ){

            // Fill Search bin histogram 
            searchH->Fill( binMap[utils2::findBin_NoB(newNJet,newHT,newMHT).c_str()],totWeight);

            searchH_b->Fill( binMap_b[utils2::findBin(newNJet,NewNB,newHT,newMHT).c_str()],totWeight);

            hCorSearch->Fill(binMap[utils2::findBin_NoB(evt->nJets(),evt->ht(),evt->mht()).c_str()],binMap[utils2::findBin_NoB(newNJet,newHT,newMHT).c_str()],totWeight);
            hCorHT->Fill(evt->ht(),newHT,totWeight);
            hCorMHT->Fill(evt->mht(),newMHT,totWeight);
            hCorNJet->Fill(evt->nJets(),newNJet,totWeight);
            hCorNBtag->Fill(evt->nBtags(),NewNB,totWeight);

            hCorSearch_noW->Fill(binMap[utils2::findBin_NoB(evt->nJets(),evt->ht(),evt->mht()).c_str()],binMap[utils2::findBin_NoB(newNJet,newHT,newMHT).c_str()]);
            hCorHT_noW->Fill(evt->ht(),newHT);
            hCorMHT_noW->Fill(evt->mht(),newMHT);
            hCorNJet_noW->Fill(evt->nJets(),newNJet);
            hCorNBtag_noW->Fill(evt->nBtags(),NewNB);

            hCorSearch_noW_b->Fill(binMap_b[utils2::findBin(evt->nJets(),evt->nBtags(),evt->ht(),evt->mht()).c_str()],binMap_b[utils2::findBin(newNJet,NewNB,newHT,newMHT).c_str()]);

       
          }



          //build and array that contains the quantities we need a histogram for. Here order is important and must be the same as RA2nocutvec

          double eveinfvec[] = {totWeight, newHT, newMHT, newMet,mindpn,newDphi1,newDphi2,newDphi3,(double) newNJet,(double)NewNB,(double)nB,(double)nB_new ,(double) muPt, simTauJetPt_xy};

          bool pass0=false;
          if(TauHadModel >= 1)pass0=true;
          else if(MuFromTauVec[0]==0)pass0=true; // Ahmad33
          if(pass0){
            //loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
            for(map<string, map<string , vector<TH1D> > >::iterator itt=map_map.begin(); itt!=map_map.end();itt++){//this will be terminated after the cuts

              ////determine what type of background should pass
              if(itt->first=="allEvents"){//all the cuts are inside this

                //Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts

                //////loop over cut names and fill the histograms
                for(map<string , vector<TH1D> >::iterator ite=cut_histvec_map.begin(); ite!=cut_histvec_map.end();ite++){


    //              if(sel->checkcut_HadTau(ite->first,newHT,newMHT,mindpn,newNJet,NewNB,evt->nLeptons(),evt->nIsoElec(),evt->nIsoMu(),evt->nIsoPion())==true){
testN++;
                  if(sel->checkcut_HadTau(ite->first,newHT,newMHT,newDphi1,newDphi2,newDphi3,newNJet,NewNB,evt->nLeptons(),evt->nIsoElec(),evt->nIsoMu(),evt->nIsoPion())==true){

                    histobjmap[ite->first].fill(Nhists,&eveinfvec[0] ,&itt->second[ite->first][0]);

                }//end of loop over cut names

                  }
                ////EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts
                
              }//end of bg_type determination
            }//end of loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
          } //Ahmad33
        } // end of bootstrapping

      } // End if exactly one muon

    } // end of loop over events

cout << " testN: " << testN << endl;  

    double GenRecMu_rate = (double)GenRecMu_fail /((double)GenRecMu_all);
    printf("GenRecMu_all: %d GenRecMu_fail: %d fail rate: %g \n ",GenRecMu_all,GenRecMu_fail,GenRecMu_rate);
    printf("nCleanEve: %d dilepton_all: %d dilepton_pass: %d \n ",nCleanEve,dilepton_all,dilepton_pass);  

    // calculate muon_jet match failure and write the histograms
    TH1D * MuJet_rate = static_cast<TH1D*>(MuJet_fail->Clone("MuJet_rate"));
    MuJet_rate->Divide(MuJet_fail,MuJet_all,1,1,"B");
    //Write
    sprintf(tempname,"TauHad2/MuJetMatchRate_%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
    TFile MuJetfile(tempname,"RECREATE");
    MuJet_rate->Write();
    MuJet_fail->Write();
    MuJet_all->Write();
    MuJetfile.Close();

    // open a file to write the histograms
    sprintf(tempname,"TauHad2/HadTauEstimation_%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
    TFile *resFile = new TFile(tempname, "RECREATE");
    searchH->Write();
    searchH_b->Write();
    hCorSearch->Write();
    hCorHT->Write();
    hCorMHT->Write();
    hCorNJet->Write();
    hCorNBtag->Write();
    hCorSearch_noW->Write();
    hCorSearch_noW_b->Write();
    hCorHT_noW->Write();
    hCorMHT_noW->Write();
    hCorNJet_noW->Write();
    hCorNBtag_noW->Write();
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
          for(int i=0; i< (int)sel->cutName().size();i++){
            for(map<string , vector<TH1D> >::iterator it=itt->second.begin(); it!=itt->second.end();it++){
              if (sel->cutName()[i]==it->first){
                cdtoit = cdtoitt->mkdir((it->first).c_str());
                cdtoit->cd();
                int nHist = it->second.size();
                for(int ii=0; ii<nHist; ii++){//since we only have 4 type of histograms
                  sprintf(tempname,"%s_%s_%s",it->second[ii].GetName(),(it->first).c_str(),(itt->first).c_str());
                  it->second[ii].Write(tempname);
                }
                cdtoitt->cd();
              }
            }
          }
        }
      }
    }

    delete resp_file;


  } // end of main

  double DeltaT(unsigned int i, vector<TVector3> Jet3vec ){

      double deltaT=0;
      float jres=0.1;
      double sum=0;
      double Jpx_i= Jet3vec[i].Pt()*cos(Jet3vec[i].Phi());
      double Jpy_i= Jet3vec[i].Pt()*sin(Jet3vec[i].Phi());

      for(unsigned int j=0; j< Jet3vec.size(); ++j){
          if(j==i)continue;
          double Jpx_j= Jet3vec[j].Pt()*cos(Jet3vec[j].Phi());
          double Jpy_j= Jet3vec[j].Pt()*sin(Jet3vec[j].Phi());

          sum=sum+(Jpx_i*Jpy_j-Jpx_j*Jpy_i) * (Jpx_i*Jpy_j-Jpx_j*Jpy_i);
      }
      deltaT=jres*sqrt(sum)/Jet3vec[i].Pt();

      return deltaT;
  }
