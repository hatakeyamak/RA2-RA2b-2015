
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
    vector<TH1*> vec_resp;
    vector<TVector3> vec_recoMuon3vec;
    vector<TVector3> vec_recoElec3vec;
    TVector3 temp3vec;
    double muPt;
    double muEta;
    double muPhi;
    double simTauJetPt;
    double simTauJetEta;
    double simTauJetPhi;

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
    TH1* searchH = new TH1D("searchH","search bin histogram",totNbins,1,totNbins);
    searchH->Sumw2();

    // Introduce search bin histogram with bTag bins
    map<string,int> binMap_b = utils2::BinMap();
    int totNbins_b=binMap_b.size();
    TH1* searchH_b = new TH1D("searchH_b","search bin histogram",totNbins_b,1,totNbins_b);
    searchH_b->Sumw2();   
 
    // Determine correlation between original and recalculated variables
    TH2 * hCorSearch = new TH2D("hCorSearch","original vs. recalculated SearchBin",totNbins,1,totNbins,totNbins,1,totNbins);
    TH2 * hCorHT = new TH2D("hCorHT","original vs. recalculated HT",50,0,5000,50,0,5000);
    TH2 * hCorMHT = new TH2D("hCorMHT","original vs. recalculated MHT",100,0,5000,100,0,5000);
    TH2 * hCorNJet = new TH2D("hCorNJet","original vs. recalculated NJet",20,0,20,20,0,20);
    TH2 * hCorNBtag = new TH2D("hCorNBtag","original vs. recalculated NBtag",20,0,20,20,0,20);

    // Determine correlation between original and recalculated variables + nB info
    TH2 * hCorSearch_noW = new TH2D("hCorSearch_noW","original vs. recalculated SearchBin",totNbins,1,totNbins,totNbins,1,totNbins);
    TH2 * hCorHT_noW = new TH2D("hCorHT_noW","original vs. recalculated HT",50,0,5000,50,0,5000);
    TH2 * hCorMHT_noW = new TH2D("hCorMHT_noW","original vs. recalculated MHT",100,0,5000,100,0,5000);
    TH2 * hCorNJet_noW = new TH2D("hCorNJet_noW","original vs. recalculated NJet",20,0,20,20,0,20);
    TH2 * hCorNBtag_noW = new TH2D("hCorNBtag_noW","original vs. recalculated NBtag",20,0,20,20,0,20);

    // Determine correlation between original and recalculated variables + nB info
    TH2 * hCorSearch_noW_b = new TH2D("hCorSearch_noW_b","original vs. recalculated SearchBin",totNbins_b,1,totNbins_b,totNbins_b,1,totNbins_b);


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
    TFile * bRateFile = new TFile("TauHad/TauBtaggedRate_TTbar_.root","R");
    sprintf(histname,"TauBtaggedRate");
    TH1D * bRateHist = (TH1D * ) bRateFile->Get(histname)->Clone();

    // Probability of muon coming from Tau
    TFile * Prob_Tau_mu_file = new TFile("TauHad/Probability_Tau_mu_TTbar_.root","R");
    sprintf(histname,"hProb_Tau_mu");
    TH1D * hProb_Tau_mu =(TH1D *) Prob_Tau_mu_file->Get(histname)->Clone();

/* Ahmad33 
    // Acceptance and efficiencies
    TFile * MuEffAcc_file = new TFile("LostLepton/LostLepton2_MuonEfficienciesFromTTbar_.root","R");
    sprintf(histname,"hAcc");
    TH1D * hAcc =(TH1D *) MuEffAcc_file->Get(histname)->Clone();
    TH1D * hEff =(TH1D *) MuEffAcc_file->Get("hEff")->Clone();

Ahmad33 */

    TFile * MuIsoEff_Arne = new TFile("TauHad/Efficiencies_Arne.root","R");
    TH2F *hMuRecoPTActivity_Arne = (TH2F*)MuIsoEff_Arne->Get("Efficiencies/MuRecoPTActivity");
    TH2F *hMuIsoPTActivity_Arne = (TH2F*)MuIsoEff_Arne->Get("Efficiencies/MuIsoPTActivity");


    // Use Ahmad's tau template
    TFile * resp_file = new TFile("TauHad/HadTau_TauResponseTemplates_TTbar_.root","R");
    for(int i=0; i<TauResponse_nBins; i++){
      sprintf(histname,"hTauResp_%d",i);
      vec_resp.push_back( (TH1D*) resp_file->Get( histname )->Clone() );
    }

/*
    // Use Rishi's tau template 
    TFile * resp_file = new TFile("TauHad/Rishi_TauTemplate.root","R");
    for(int i=0; i<TauResponse_nBins; i++){
      sprintf(histname,"response%d",i+2);
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

    // how often a muon does not match a jet
    double muBin[]={0,20,40,60,80,100,1000};
    int muNbin = sizeof(muBin)/sizeof(muBin[0]) -1 ; 
    TH1 * MuJet_all  = new TH1D("MuJet_all","mu match jet vs. pT -- all",muNbin,muBin);
    TH1 * MuJet_fail = new TH1D("MuJet_fail","mu match jet vs. pT -- fail",muNbin,muBin);

    int eventN=0;
    while( evt->loadNext() ){
      eventN++;

      // Through out an event that contains HTjets with bad id
      if(evt->JetId()==0)continue;


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
      if( vec_recoMuon3vec.size() == 1 && vec_recoElec3vec.size() == 0 ){
        muPt = vec_recoMuon3vec[0].Pt();
        muEta = vec_recoMuon3vec[0].Eta();
        muPhi = vec_recoMuon3vec[0].Phi();
        // muMtW = vec_recoMuMTW[0]; ???????


// Ahmad33
dilepton_all++;
if(evt->GenMuPtVec_().size()>1 || evt->GenElecPtVec_().size()>0)continue;
dilepton_pass++;
// Ahmad33


        // Get random number from tau-response template
        // The template is chosen according to the muon pt
        const double scale = utils->getRandom(muPt,vec_resp );

        simTauJetPt = scale * muPt;
        simTauJetEta = muEta;
        simTauJetPhi = muPhi;

        // The muon we are using is already part of a jet. (Note: the muon is isolated by 0.2 but jet is much wider.) And,
        // its momentum is used in HT and MHT calculation. We need to subtract this momentum and add the contribution from the simulated tau jet.

        //Identify the jet containing the muon
        const double deltaRMax = muPt < 50. ? 0.2 : 0.1; // Increase deltaRMax at low pt to maintain high-enought matching efficiency
        int JetIdx=-1;
        if(verbose==1 && utils->findMatchedObject(JetIdx,muEta,muPhi,evt->JetsPtVec_(), evt->JetsEtaVec_(), evt->JetsPhiVec_(),deltaRMax,verbose) ){
          printf(" \n **************************************** \n JetIdx: %d \n ",JetIdx);
        }

        GenRecMu_all++;
        // If muon does not match a GenMuon, drop the event. 
        int GenMuIdx=-1;
        if(!utils->findMatchedObject(GenMuIdx,muEta,muPhi,evt->GenMuPtVec_(), evt->GenMuEtaVec_(), evt->GenMuPhiVec_(),deltaRMax,verbose)){
          GenRecMu_fail++;
          printf(" Warning! There is no Gen Muon \n ");
          printf("@@@@@@@@@@@@@@@@@@\n eventN: %d \n MuPt: %g MuEta: %g MuPhi: %g \n ",eventN,muPt,muEta,muPhi);
          for(int i=0; i<evt->GenMuPtVec_().size(); i++){
//          if( evt->GenMuPtVec_()[i] >10. && fabs(evt->GenMuEtaVec_()[i])<2.5 )printf("GenMu#: %d \n GenMuPt: %g GenMuEta: %g GenMuPhi: %g \n ", i,evt->GenMuPtVec_()[i],evt->GenMuEtaVec_()[i],evt->GenMuPhiVec_()[i] );
          }
          continue;
        }



//######################################################################

        // 3Vec of muon and scaledMu 
        TVector3 SimTauJet3Vec,NewTauJet3Vec,Muon3Vec;
        SimTauJet3Vec.SetPtEtaPhi(simTauJetPt,simTauJetEta,simTauJetPhi);
        Muon3Vec.SetPtEtaPhi(muPt,muEta,muPhi);

        // New ht and mht 
        vector<TVector3> HT3JetVec,MHT3JetVec;
        HT3JetVec.clear();
        MHT3JetVec.clear();
        TVector3 temp3Vec;
        int slimJetIdx=-1;
        MuJet_all->Fill(muPt);
        utils->findMatchedObject(slimJetIdx,muEta,muPhi,evt->slimJetPtVec_(),evt->slimJetEtaVec_(), evt->slimJetPhiVec_(),0.4,verbose);
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
        double metX = evt->met()*cos(evt->metphi())-(simTauJetPt-muPt)*cos(simTauJetPhi);///the minus sign is because of Mht definition.
        double metY = evt->met()*sin(evt->metphi())-(simTauJetPt-muPt)*sin(simTauJetPhi);

        if(verbose==1)printf("############ \n metX: %g, metY: %g \n",metX,metY);
        if(verbose==1)printf("evt->met: %g, evt->metphi: %g,muPt: %g simTauJetPt: %g, simTauJetPhi: %g \n",evt->met(),evt->metphi(),muPt,simTauJetPt,simTauJetPhi);

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



        // get the effieciencies and acceptance
        // if baseline cuts on the main variables are passed then calculate the efficiencies otherwise simply take 0.75 as the efficiency.
        double Eff,Eff_Arne;

        double activity= utils->MuActivity(muEta,muPhi,evt->JetsPtVec_(),evt->JetsEtaVec_(),evt->JetsPhiVec_(),evt->Jets_chargedEmEnergyFraction_(),evt->Jets_chargedHadronEnergyFraction_());
        if(verbose!=0)cout << " activity: " << activity << endl;

        // Here Eff is not a good naming. What this really mean is efficiency and also isolation together
        Eff_Arne=hMuRecoPTActivity_Arne->GetBinContent(hMuRecoPTActivity_Arne->GetXaxis()->FindBin(muPt),hMuRecoPTActivity_Arne->GetYaxis()->FindBin(activity));
/* Ahmad33

        Eff_Arne*=hMuIsoPTActivity_Arne->GetBinContent(hMuRecoPTActivity_Arne->GetXaxis()->FindBin(muPt),hMuRecoPTActivity_Arne->GetYaxis()->FindBin(activity));

        if(newNJet>=4 && newHT >= 500 && newMHT >= 200){
          // Eff = hEff->GetBinContent(binMap_b[utils2::findBin(newNJet,NewNB,newHT,newMHT)]);
          Eff = hEff->GetBinContent(binMap[utils2::findBin_NoB(newNJet,newHT,newMHT)]); 
        }else{
          Eff=0.75;
        }

Ahmad33*/
        // if baseline cuts on the main variables are passed then calculate the acceptance otherwise simply take 0.9 as the acceptance.
        double Acc;
/* Ahmad33

        if(newNJet>=4 && newHT >= 500 && newMHT >= 200){
          // Acc = hAcc->GetBinContent(binMap_b[utils2::findBin_b(newNJet,NewNB,newHT,newMHT)]);
          // Acc = hAcc->GetBinContent(binMap[utils2::findBin_NoB(newNJet,newHT,newMHT)]);
          Acc = hAcc->GetBinContent(binMap_mht_nj[utils2::findBin_mht_nj(newNJet,newMHT)]);
        }else{
          Acc=0.9;
        }

        if(verbose==2 && newNJet>=4 && newHT >= 500 && newMHT >= 200)printf("Eff: %g Acc: %g njet: %d nbtag: %d ht: %g mht: %g binN: %d \n ",Eff,Acc, newNJet,evt->nBtags(),newHT,newMHT, binMap_mht_nj[utils2::findBin_mht_nj(newNJet,newMHT)]);
        if(verbose==2 && newNJet>=4 && newHT >= 500 && newMHT >= 200)printf("Eff_Arne: %g \n" ,Eff_Arne);

        if(Acc==0 || Eff==0){printf("eventN: %d Acc or Eff =0 \n Eff: %g Acc: %g njet: %d nbtag: %d ht: %g mht: %g \n ",eventN,Eff,Acc, newNJet,evt->nBtags(),newHT,newMHT);}
        if(Acc==0)Acc=0.9;
        if(Eff==0)Eff=0.75;
        if(Eff_Arne==0)Eff_Arne=0.75;

Ahmad33
*/

        // Not all the muons are coming from W. Some of them are coming from Tau which should not be considered in our estimation.
        double Prob_Tau_mu = hProb_Tau_mu->GetBinContent(hProb_Tau_mu->GetXaxis()->FindBin(muPt));

//Ahmad33
Acc=1.; // temporary
//Ahmad33
Eff_Arne=1.; // temporary 
//Ahmad33
Prob_Tau_mu=0; // temporary



//        double totWeight=evt->weight()*1*0.64*(1/(Acc*Eff_Arne))*(1-Prob_Tau_mu);
        double totWeight=1*0.64*(1/(Acc*Eff_Arne))*(1-Prob_Tau_mu);//the 0.64 is because only 64% of tau's decay hadronically. Here 0.9 is acceptance and 0.75 is efficiencies of both reconstruction and isolation.

        // Apply baseline cuts
        if(newHT>500. && newMHT > 200. && mindpn > 4. && newNJet >= 4   ){

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

        double eveinfvec[] = {totWeight, newHT, newMHT ,(double) newNJet,(double)NewNB,(double)nB,(double)nB_new ,(double) muPt, simTauJetPt};

if(MuFromTauVec[0]==0){ // Ahmad33

        //loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
        for(map<string, map<string , vector<TH1D> > >::iterator itt=map_map.begin(); itt!=map_map.end();itt++){//this will be terminated after the cuts

          ////determine what type of background should pass
          if(itt->first=="allEvents"){//all the cuts are inside this

            //Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts

            //////loop over cut names and fill the histograms
            for(map<string , vector<TH1D> >::iterator ite=cut_histvec_map.begin(); ite!=cut_histvec_map.end();ite++){


              if(sel->checkcut_HadTau(ite->first,newHT,newMHT,mindpn,newNJet,NewNB,evt->nLeptons(),evt->nIsoElec(),evt->nIsoMu(),evt->nIsoPion())==true){

                histobjmap[ite->first].fill(Nhists,&eveinfvec[0] ,&itt->second[ite->first][0]);

            }//end of loop over cut names

              }
            ////EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts
            
          }//end of bg_type determination
        }//end of loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
} //Ahmad33

      } // End if exactly one muon

    } // end of loop over events
  
    double GenRecMu_rate = (double)GenRecMu_fail /((double)GenRecMu_all);
    printf("GenRecMu_all: %d GenRecMu_fail: %d fail rate: %g \n ",GenRecMu_all,GenRecMu_fail,GenRecMu_rate);
    printf("dilepton_all: %d dilepton_pass: %d \n ",dilepton_all,dilepton_pass);  

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
