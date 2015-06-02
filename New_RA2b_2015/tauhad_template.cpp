#include "LeptonAcceptance.h"
#include "Events.h"
#include "Selection.h"
#include "utils.h"
#include "utils2.h"

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

    double w_mu=0, w_tau=0; //Ahmad3
    
    // Inroduce two histogram to understand the probability of a muon coming from tau.
    int MaxMuPt=100*10;
    int NMuPtBins=MaxMuPt/10;
    TH1D * hW_mu = new TH1D("hW_mu","Pt of mu from W",NMuPtBins,0,MaxMuPt);
    hW_mu->Sumw2();
    TH1D * hTau_mu = new TH1D("hTau_mu","Pt of mu from Tau",NMuPtBins,0,MaxMuPt);
    hTau_mu->Sumw2();

    // Introduce two histograms to understand how often a gen tau does not match any jet
    TH1D * GenTau_Jet_all = new TH1D("GenTau_Jet_all","Pt of Gen Tau",NMuPtBins,0,MaxMuPt);
    GenTau_Jet_all->Sumw2();
    TH1D * GenTau_Jet_fail = new TH1D("GenTau_Jet_fail","Pt of Gen Tau",NMuPtBins,0,MaxMuPt);
    GenTau_Jet_fail->Sumw2();

    // Two histograms to find rate of btagged(mistagged) tau jets as a function of pT. 
    TH1D * B_rate_all = new TH1D("B_rate_all","Pt of all matched tau jets",NMuPtBins,0,MaxMuPt);
    B_rate_all->Sumw2();
    TH1D * B_rate_tagged = new TH1D("B_rate_tagged","Pt of bTagged tau jets",NMuPtBins,0,MaxMuPt);
    B_rate_tagged->Sumw2();


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
    TH1D NB_hist = TH1D("nB","Number of B Distribution",20,0,20);
    NB_hist.Sumw2();
    vec.push_back(NB_hist);
    TH1D NLostLep_hist = TH1D("NLostLep","Number of Lost Lepton Distribution",20,0,20);
    NLostLep_hist.Sumw2();
    vec.push_back(NLostLep_hist);
    TH1D nGenTauHad_hist = TH1D("nGenTauHad","Number of Gen. Had. Tau",20,0,20);
    nGenTauHad_hist.Sumw2();
    vec.push_back(nGenTauHad_hist);

    int Nhists=((int)(vec.size())-1);//-1 is because weight shouldn't be counted.

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


    // The tau response templates
    Utils * utils = new Utils();
    
    // They are filled for different bins in generated tau-lepton pt.
    std::vector<TH1*> hTauResp(utils->TauResponse_nBins_());
    for(unsigned int i = 0; i < utils->TauResponse_nBins_(); ++i){
      hTauResp.at(i) = new TH1D(utils->TauResponse_name(i),";p_{T}(visible) / p_{T}(generated-#tau);Probability",50,0.,2.5);
      hTauResp.at(i)->Sumw2();
    }

    // The Purpose of the following two histograms is to find the probability as function of
    // pt with wich a tau lepton decays hadronically. One is filled with any tau in the event
    // while the other with only hadronic tau. At the end we divide them. That gives a
    // distributions wich will be used later when simulating Jet_tau's with muons.

    TH1D * genTauPtHist = new TH1D("genTauPtHist","genTauPt",10,0,250);
    TH1D * genHadTauPtHist = new TH1D("genHadTauPtHist","genHadTauPt",10,0,250);
      
    // We would like also to have the pt distribution of the tau Jets
    TH1D * tauJetPtHist = new TH1D("tauJetPtHist","Pt of the tau hadronic jets",80,0,400);


    // Because of bad reconstruction or so, sometimes no jet matches a Gen. hadronic tau. 
    // So we need to add into account the fail rate here. 
    // First open the fail rate histogram
    sprintf(tempname,"TauHad/FailRate_GenTau_jet_TTbar_%s.root",inputnumber.c_str());
    TFile * FailRateGenTau_Jet_file = new TFile(tempname,"R");
    sprintf(histname,"FailRate_GenTau_jet");
    TH1D * hFailRate_GenTau_Jet =(TH1D *) FailRateGenTau_Jet_file->Get(histname)->Clone();
 

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

    // Loop over the events (tree entries)
    int eventN=0;
    while( evt->loadNext() ){
      eventN++;
    //  if(eventN>100)break;

      // Through out an event that contains HTjets with bad id
      if(evt->JetId()==0)continue;

      // Here we determine how often the /<<<< W --> tau --> W --> mu >>>>/
      // comparing with /<<<< w--> mu >>>>/
      // First we restrict ourselves to events with one muon and no electron
      // just like the control sample in the data driven method.
      // Introduce two histograms of Pt distributions. One to be filled in
      // any case when one muon and no electron exist. The other, when muon
      // is coming from tau.
      // At the end dividing the two histograms give the percentage as a function
      // transverse momentum.
      int muN=evt->GenMuPtVec_().size();

      // Since we don't acount for efficiency and acceptance of Reco. electrons,
      // for the sake of consistency, apply the same pT and eta cuts on the gen.
      // electrons as those applied to Reco. electrons.  
      int eleN=0;
      for(int i=0;i<evt->GenElecPtVec_().size();i++){
        double elept=evt->GenElecPtVec_()[i];
        double eleeta=evt->GenElecEtaVec_()[i];
// Ahmad33        if(elept > LeptonAcceptance::electronPtMin() && std::abs(eleeta) < LeptonAcceptance::electronEtaMax())eleN++;
      eleN++; // Ahmad33
      }

      double muPt=-99;

      //we want to consider events that pass the baseline cuts
      if( evt->ht() >=500 && evt->mht() >=200 && evt->nJets() >=4 ){

        if(verbose!=0)printf("============================================================= \n eventN: %d \n ",eventN);
        if(verbose!=0 && eleN==0 && muN==1)printf("#####################\nNo elec and 1 muon event \n eventN: %d \n ",eventN);
        if(muN==1)muPt=evt->GenMuPtVec_().at(0);
    
        // If no elec and 1 muon
        // Fill the hW_mu anyways.
        // See what is the parent of the mu. if tau fill the tau hist.
        // If w, see where w is coming from, if tau again, fill the tau hist.
        if( eleN==0 && muN==1 )hW_mu->Fill(muPt);

        bool isTau_mu=false;

        if(muN==1){ 
          if(evt->GenMuFromTauVec_()[0]==1)isTau_mu=true;
        }
        
        if( eleN==0 && muN==1 && isTau_mu==true )hTau_mu->Fill(muPt);
        
      } // end of baseline cuts




      // We are interested in hadronically decaying taus only
      bool hadTau=false; 
      double genTauPt=-1;
      double genTauPt0=-1;
      double genTauEta=-99;
      double genTauPhi=-99;
      for(int i=0; i<evt->GenTauHadVec_().size();i++){
        genTauPt0=evt->GenTauPtVec_()[0];
        if(evt->GenTauHadVec_()[i]==1){
          genTauPt0=evt->GenTauPtVec_()[i];
          hadTau=true;
          genTauPt = evt->GenTauPtVec_()[i];
          genTauEta = evt->GenTauEtaVec_()[i];
          genTauPhi = evt->GenTauPhiVec_()[i];
          break; // This is to pick the more energetic tau in the event if there are more than one. 
        }
      }      
      
      genTauPtHist->Fill(genTauPt0);

      if(hadTau==false)continue;
      genHadTauPtHist->Fill(genTauPt);   

 
      // We want no muon and electron in the event
      if(evt->GenMuPtVec_().size()!=0 || eleN!=0)continue;
      if(verbose!=0){
      printf(" ####################### \n event#: %d \n ",eventN-1); 
      
            printf(" @@@@\n Jets section: \n ");
            for(int i=0;i<evt->slimJetPtVec_().size();i++){
              printf("jet#: %d pt: %g eta: %g phi: %g \n ",i+1,evt->slimJetPtVec_()[i],evt->slimJetEtaVec_()[i],evt->slimJetPhiVec_()[i]);
            }
            printf(" @@@@\n Tau section: \n ");
            for(int i=0;i<evt->GenTauPtVec_().size();i++){
              printf("GenTau#: %d pt: %g eta: %g phi: %g \n ",i+1,evt->GenTauPtVec_()[i],evt->GenTauEtaVec_()[i],evt->GenTauPhiVec_()[i]);
            }
            printf(" @@@@\n TauNu section: \n ");
            for(int i=0;i<evt->GenTauNuPtVec_().size();i++){
              printf("GenTauNu # : %d pt: %g eta: %g phi: %g \n ",i+1,evt->GenTauNuPtVec_()[i],evt->GenTauNuEtaVec_()[i],evt->GenTauNuPhiVec_()[i]);
            }
            printf(" @@@@\n Mom of TauNu section: \n ");
            for(int i=0;i<evt->TauNuMomPt().size();i++){
              printf("MomofTauNu # : %d pt: %g \n ",i+1,evt->TauNuMomPt()[i]);
            }



       
      }

      int jet_index=-99;
      int nB = evt->nBtags();
      double deltaR = genTauPt < 50. ? 0.2 : 0.1;
      // We don't write the event for nB if the matched tau jet is btaged. 
      if(utils->findMatchedObject(jet_index,genTauEta,genTauPhi, evt->JetsPtVec_(),evt->JetsEtaVec_(),evt->JetsPhiVec_(),deltaR,verbose)){
        B_rate_all->Fill(evt->JetsPtVec_()[jet_index]);
        if(evt->csvVec()[jet_index]>0.814){
          nB=-1;
          B_rate_tagged->Fill(evt->JetsPtVec_()[jet_index]);
        }
      }
      

      // Total weight
      // double totWeight = evt->weight()*1.;
      double totWeight = 1.;

        // Apply baseline cuts
        if(evt->ht() >500. && evt->mht() > 200. && evt->minDeltaPhiN() > 4. && evt->nJets() >= 4   ){

          // Fill Search bin histogram
          searchH->Fill( binMap[utils2::findBin_NoB(evt->nJets(),evt->ht(),evt->mht()).c_str()],totWeight);
          searchH_b->Fill( binMap_b[utils2::findBin(evt->nJets(),evt->nBtags(),evt->ht(),evt->mht()).c_str()],totWeight);

        }

      // Build and array that contains the quantities we need a histogram for.
      // Here order is important and must be the same as RA2nocutvec
      double eveinfvec[] = {totWeight,(double) evt->ht(),(double) evt->mht() ,(double) evt->nJets(),(double) evt->nBtags(),(double)nB }; //the last one gives the RA2 defined number of jets.


// Ahmad33 this is to remove acceptance role to check other sources of error. 
if( genTauPt > LeptonAcceptance::muonPtMin() && std::abs(genTauEta) < LeptonAcceptance::muonEtaMax() ){


      //loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
      for(map<string, map<string , vector<TH1D> > >::iterator itt=map_map.begin(); itt!=map_map.end();itt++){//this will be terminated after the cuts

        ////determine what type of background should pass
        if(itt->first=="allEvents"){//all the cuts are inside this

          //Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts

          //////loop over cut names and fill the histograms
          for(map<string , vector<TH1D> >::iterator ite=cut_histvec_map.begin(); ite!=cut_histvec_map.end();ite++){

            if(sel->checkcut_HadTau(ite->first,evt->ht(),evt->mht(),evt->minDeltaPhiN(),evt->nJets(),evt->nBtags(),evt->nLeptons(),evt->nIsoElec(),evt->nIsoMu(),evt->nIsoPion())==true){
              histobjmap[ite->first].fill(Nhists,&eveinfvec[0] ,&itt->second[ite->first][0]);
            }
          }//end of loop over cut names

          ////EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts
          
        }//end of bg_type determination
      }//end of loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"

      ///////////////////////////////
      ////End of Closure Test Section
      ///////////////////////////////

} // Ahmad33

      // Do the matching
      int tauJetIdx = -1;
      double deltaRMax = genTauPt < 50. ? 0.2 : 0.1; // Increase deltaRMax at low pt to maintain high-enought matching efficiency
      if(inputnumber=="LargerDelR")deltaRMax = genTauPt < 50. ? 0.4 : 0.2; // Increase deltaRMax at low pt to maintain high-enought matching efficiency

      // Lets write all the gen tau events regardless of if they match a jet or not.
      //we want to consider events that pass the baseline cuts
      if(genTauPt >= 20. && std::abs(genTauEta) <= 2.1 && evt->nJets() >2 )GenTau_Jet_all->Fill(genTauPt);

      // 
      TVector3 TauNu3Vec,Tau3Vec,Visible3Vec;
      for(int i=0; i < evt->GenTauNuPtVec_().size(); i++){
        if(evt->TauNuMomPt()[i]==genTauPt){
          TauNu3Vec.SetPtEtaPhi(evt->GenTauNuPtVec_()[i],evt->GenTauNuEtaVec_()[i],evt->GenTauNuPhiVec_()[i]);
        }
      }
      Tau3Vec.SetPtEtaPhi(genTauPt,genTauEta,genTauPhi);
      Visible3Vec=Tau3Vec-TauNu3Vec;

      if(verbose!=0){      
        printf("TauNu3Vec: pt: %g eta: %g phi: %g \n Tau3Vec: pt: %g eta: %g phi: %g \n",TauNu3Vec.Pt(),TauNu3Vec.Eta(),TauNu3Vec.Phi(),Tau3Vec.Pt(),Tau3Vec.Eta(),Tau3Vec.Phi());
        printf("Visible3Vec: pt: %g eta: %g phi: %g \n ",Visible3Vec.Pt(),Visible3Vec.Eta(),Visible3Vec.Phi());
      }

      if( !utils->findMatchedObject(tauJetIdx,Visible3Vec.Eta(),Visible3Vec.Phi(), evt->slimJetPtVec_(), evt->slimJetEtaVec_(), evt->slimJetPhiVec_(),deltaRMax,verbose) ){
        if(genTauPt >= 20. && std::fabs(genTauEta) <= 2.1 && evt->nJets() >2 )GenTau_Jet_fail->Fill(genTauPt);
        continue;
      } // this also determines tauJetIdx


      if(verbose!=0){printf("Event: %d, tauJetIdx: %d \n",eventN,tauJetIdx);
        if(tauJetIdx!=-1){
          printf("JetEta: %g ,JetPhi(): %g ,JetPt(): %g \n genTauEta: %g, genTauPhi: %g, genTauPt: %g \n",evt->JetsEtaVec_()[tauJetIdx],evt->JetsPhiVec_()[tauJetIdx],evt->JetsPtVec_()[tauJetIdx],genTauEta,genTauPhi,genTauPt);
        }
      }

      // Fill tauJet Pt histogram
      double failRate = hFailRate_GenTau_Jet->GetBinContent(hFailRate_GenTau_Jet->GetXaxis()->FindBin(genTauPt));
      // We know N_tot = N_pass + N_fail. And, failRate=N_fial/N_tot ==> N_tot = 1/(1-failRate) N_pass
      double tauJetWeight = totWeight * 1/(1-failRate);
      for(int jetIdx = 0; jetIdx < (int) evt->slimJetPtVec_().size(); ++jetIdx){ // Loop over reco jets
        // Select tau jet
        if( jetIdx == tauJetIdx ) {
          // Fill the tauJetPtHist after the cut "delphi" 
          if(sel->checkcut("delphi",evt->ht(),evt->mht(),evt->minDeltaPhiN(),evt->nJets(),evt->nBtags(),evt->nLeptons(),evt->nIsoElec(),evt->nIsoMu(),evt->nIsoPion())==true)tauJetPtHist->Fill( evt->slimJetPtVec_().at(jetIdx), tauJetWeight);// this is tauJetPt that later is defined.

          break; // End the jet loop once the tau jet has been found
        }
      } // End of loop over reco jets


      // Use only events where the tau is inside the muon acceptance
      // because lateron we will apply the response to muon+jet events
      if(verbose!=0)printf("genTauPt:%g genTauEta: %g  \n ",genTauPt,genTauEta); 

      if( genTauPt < 20. ) continue; // 10.
      if( std::abs(genTauEta) > 2.1 ) continue; // 2.4

      if(verbose!=0)printf("genTauPt>20 and eta< 2.1 passed \n ");  



      // Calculate RA2 selection-variables from "cleaned" jets, i.e. jets withouth the tau-jet
      int selNJet = 0; // Number of HT jets (jets pt > 50 GeV and |eta| < 2.5)
      for(int jetIdx = 0; jetIdx <(int) evt->JetsPtVec_().size(); ++jetIdx) { // Loop over reco jets
        // Skip this jet if it is the tau
        if( jetIdx == tauJetIdx ) continue;
        // Calculate NJet
        if( evt->JetsPtVec_()[jetIdx] > 30. && std::abs(evt->JetsEtaVec_()[jetIdx]) < 2.4 ) selNJet++;
      } // End of loop over reco jets


      // Select only events with at least 2 HT jets
      if( selNJet < 2 ) continue;

      if(verbose!=0)printf("selNJet > 2 passed \n " );  

      // Fill histogram with relative visible energy of the tau
      // ("tau response template") for hadronically decaying taus
      for(int jetIdx = 0; jetIdx < (int) evt->slimJetPtVec_().size(); ++jetIdx) { // Loop over reco jets
        // Select tau jet
        if( jetIdx == tauJetIdx ) {
          // Get the response pt bin for the tau
          const double tauJetPt = evt->slimJetPtVec_().at(jetIdx);
          const unsigned int ptBin = utils->TauResponse_ptBin(genTauPt);
          // Fill the corresponding response template
          hTauResp.at(ptBin)->Fill( tauJetPt / genTauPt );

          if(verbose!=0)printf("ptBin: %d tauJetPt: %g genTauPt: %g \n ",ptBin,tauJetPt,genTauPt); 

          break; // End the jet loop once the tau jet has been found
        }
      } // End of loop over reco jets



    } // End of loop over events  



    //open a file to write the histograms
    sprintf(tempname,"TauHad/GenInfo_HadTauEstimation_%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
    TFile *resFile = new TFile(tempname, "RECREATE");
    searchH->Write();
    searchH_b->Write();
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

    // Calculate tau mistagged(btagged) rate
    TH1D * TauBtaggedRate = static_cast<TH1D*>(B_rate_tagged->Clone("TauBtaggedRate"));
    TauBtaggedRate->Divide(B_rate_tagged,B_rate_all,1,1,"B");
    // Write the histogram 
    sprintf(tempname,"TauHad/TauBtaggedRate_%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
    TFile btagfile(tempname,"RECREATE");
    TauBtaggedRate->Write();
    B_rate_tagged->Write();
    B_rate_all->Write();
    btagfile.Close();

    // Calculate the probability of muon coming from Tau
    TH1D * hProb_Tau_mu = static_cast<TH1D*>(hTau_mu->Clone("hProb_Tau_mu"));
    hProb_Tau_mu->Divide(hTau_mu,hW_mu,1,1,"B");
    // Write the histograms
    sprintf(tempname,"TauHad/Probability_Tau_mu_%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
    TFile fTau_mu(tempname,"RECREATE");
    hProb_Tau_mu->Write();
    hTau_mu->Write();
    hW_mu->Write();
    fTau_mu.Close();


    // Calculate how often a gen tau does not match a jet (in a hadronic tau event)
    TH1D * FailRate_GenTau_jet = static_cast<TH1D*>(GenTau_Jet_fail->Clone("FailRate_GenTau_jet"));
    FailRate_GenTau_jet->Divide(GenTau_Jet_fail,GenTau_Jet_all,1,1,"B");
    // Write the histograms
    sprintf(tempname,"TauHad/FailRate_GenTau_jet_%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
    TFile fgentTau_jet(tempname,"RECREATE");
    FailRate_GenTau_jet->Write();
    GenTau_Jet_fail->Write();
    GenTau_Jet_all->Write();
    fgentTau_jet.Close();


    // calculate the probability with which tau decays hadronically as function of pt
    TH1D * genHadTauPtHist2 = static_cast<TH1D*>(genHadTauPtHist->Clone("genHadTauPtHist2"));
    genHadTauPtHist2->Divide(genHadTauPtHist,genTauPtHist,1,1,"");

    // Normalize the response distributions to get the probability density
    for(unsigned int i = 0; i < hTauResp.size(); ++i) {
      if( hTauResp.at(i)->Integral("width") > 0. ) {
        // if option "width" is specified, the integral is the sum of the bin contents multiplied by the bin width in x.
        hTauResp.at(i)->Scale(1./hTauResp.at(i)->Integral("width"));
      }
    }

    // --- Save the Histograms to File -----------------------------------
    sprintf(tempname,"TauHad/HadTau_TauResponseTemplates_%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
    TFile outFile(tempname,"RECREATE");
    TCanvas *c1 = new TCanvas("c1","TauResponseTemplates",10,10,700,900);
    for(unsigned int i = 0; i < hTauResp.size(); ++i) {
      hTauResp.at(i)->Write();
      hTauResp.at(i)->SetLineColor(i);
    }
    //c1->Print("HadTau_TauResponseTemplates.pdf");
    genHadTauPtHist2->Write();

    tauJetPtHist->Write();

  }// end of main
