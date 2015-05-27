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

using namespace std;

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
    const double deltaRMax = 0.1;
    const double deltaPtMax = 0.2;

    map<string,int> binMap = utils2::BinMap_NoB();
    int totNbins=binMap.size();
    map<string,int> binMap_mht_nj = utils2::BinMap_mht_nj();
    int totNbins_mht_nj=binMap_mht_nj.size();
    TH1* hAccAll = new TH1D("hAccAll","Acceptance -- All",totNbins_mht_nj,1,totNbins_mht_nj);
    TH1* hIsoRecoAll = new TH1D("hIsoRecoAll","Efficiency -- All",totNbins,1,totNbins);
    TH1* hAccPass = new TH1D("hAccPass","Acceptance -- Pass",totNbins_mht_nj,1,totNbins_mht_nj);
    TH1* hIsoRecoPass = new TH1D("hIsoRecoPass","Efficiency -- Pass",totNbins,1,totNbins);
    hAccAll->Sumw2();
    hIsoRecoAll->Sumw2();
    hAccPass->Sumw2();
    hIsoRecoPass->Sumw2();


    ///read the file names from the .txt files and load them to a vector.
    while(fin.getline(filenames, 500) ){filesVec.push_back(filenames);}
    cout<< "\nProcessing " << subSampleKey << " ... " << endl;
    for(unsigned int in=0; in<filesVec.size(); in++){ sample_AUX->Add(filesVec.at(in).c_str()); }


    // --- Analyse the events --------------------------------------------
    Selection * sel = new Selection();
    Utils * utils = new Utils();

    // Interface to the event content
    Events * evt = new Events(sample_AUX, subSampleKey,verbose);

    // Loop over the events (tree entries)
    int eventN=0;
    while( evt->loadNext() ){
//      if(eventN>10000)break;
      eventN++;

      // Through out an event that contains HTjets with bad id
      if(evt->JetId()==0)continue;

//printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@  \n event: %d \n Njet: %d HT: %g MHT: %g dphi1: %g dphi2: %g dphi3: %g  \n ",eventN-1,evt->nJets(),evt->ht(),evt->mht(),evt->deltaPhi1(),evt->deltaPhi2(),evt->deltaPhi3()); //Ahmad3

      // Apply the NJets baseline-cut
      if( !sel->Njet_4(evt->nJets()) ) continue;
      // Apply the HT and MHT baseline-cuts
      if( !sel->ht_500(evt->ht()) ) continue;
      if( !sel->mht_200(evt->mht()) ) continue;
      // Apply the delta-phi cuts
      if( !sel->dphi(evt->minDeltaPhiN()) ) continue;

      if(verbose!=0)printf("\n############ \n event: %d \n ",eventN-1);

      double genMuPt=0.;
      double genMuEta=-99.;
      double genMuPhi=-99.;
      int firstMuId=0;
      vector<TVector3> genMuonVec;
      TVector3 temp3vec;
      genMuonVec.clear();
      bool isMuon = false;

      for(int i=0; i< evt->GenMuPtVec_().size(); i++){
        if(evt->GenMuFromTauVec_()[i]==0){
          genMuPt = evt->GenMuPtVec_().at(i);
          genMuEta = evt->GenMuEtaVec_().at(i);
          genMuPhi = evt->GenMuPhiVec_().at(i);
          isMuon=true;
          temp3vec.SetPtEtaPhi(genMuPt,genMuEta,genMuPhi);
          genMuonVec.push_back(temp3vec);
        }
        
        if(verbose!=0){
          printf("Muon # %d, pt: %g, eta: %g, phi: %g \n ",i,genMuPt,genMuEta,genMuPhi);
        }

        break; // if more than one muon exist, pick the energetic one. 
      }

      // ask for exactly one muon
      if( evt->GenMuPtVec_().size() > 1 ) continue;

      if( !( isMuon ) ) continue;

      // Acceptance determination 1: Counter for all events
      // with muons at generator level
      hAccAll->Fill( binMap_mht_nj[utils2::findBin_mht_nj(evt->nJets(),evt->mht()).c_str()] );

      // Check if generator-level muon is in acceptance
      if( genMuPt > LeptonAcceptance::muonPtMin() && std::abs(genMuEta) < LeptonAcceptance::muonEtaMax() ) {
        if(verbose!=0)printf("Muon is in acceptance \n ");
        // Acceptance determination 2: Counter for only those events
        // with generator-level muons inside acceptance
        // hAccPass->Fill( binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht).c_str()] );
        hAccPass->Fill( binMap_mht_nj[utils2::findBin_mht_nj(evt->nJets(),evt->mht()).c_str()] );

        // Reconstruction-efficiency determination 1: Counter for all events
        // with generator-level muons inside acceptance, regardless of whether
        // the muon has also been reconstructed or not.
        // hIsoRecoAll->Fill( binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht).c_str()]);
        hIsoRecoAll->Fill( binMap[utils2::findBin_NoB(evt->nJets(),evt->ht(),evt->mht()).c_str()]);

        // Check if the muon has been reconstructed: check if a reconstructed
        // muon is present in the event that matches the generator-level muon
        // Isolation-efficiency determination 1: Counter for all events with a
        // reconstructed muon that has a generator-level muon match inside the
        // the acceptance, regardless of whether the reconstructed muon is also
        // isolated or not.

//if( evt->MuPtVec_().size()>0 )printf(" RecoMu--> Pt: %g eta: %g phi: %g deltaRMax: %g ",evt->MuPtVec_()[0],evt->MuEtaVec_()[0],evt->MuPhiVec_()[0],deltaRMax); // Ahmad3
//else cout << " Muon size is 0 \n " ;
        // in R and in pt
        int matchedMuonIdx = -1;
        if(evt->MuPtVec_().size()>0 && utils->findMatchedObject(matchedMuonIdx,genMuEta,genMuPhi,evt->MuPtVec_(),evt->MuEtaVec_(),evt->MuPhiVec_(),deltaRMax,verbose) ) {
          // Muon is reconstructed
          const double relDeltaPtMu = std::abs(genMuPt - evt->MuPtVec_().at(matchedMuonIdx) ) / evt->MuPtVec_().at(matchedMuonIdx) ;
          if(verbose!=0)printf(" relDeltaPtMu: %g \n ",relDeltaPtMu);
          if( relDeltaPtMu < deltaPtMax ) {
            // and matches generated pt
            if(verbose!=0)printf("Muon is reconstructed \n ");
            // Check if the muon is also isolated: check if an isolated muon is present
            // in the event that matches the reconstructed muon in R
            if( /*muonsRelIso->at(matchedMuonIdx) <= Selection::muIso()*/ true ){
                //.................//.................//
                // Currently muons are picked if they are isolated.
                // So we don't need to put a cut here.     
                //.................//.................//
              // Muon is isolated
              if(verbose!=0)printf("Muon is isolated \n ");
              // Reconstruction-efficiency determination 2: Counter for those events
              // with generator-level muons inside acceptance where the muon has also
              // been reconstructed.
              // Isolation-efficiency determination 2: Counter for those events where
              // the muon is also isolated.
              // hIsoRecoPass->Fill( binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht).c_str()] );
              hIsoRecoPass->Fill( binMap[utils2::findBin_NoB(evt->nJets(),evt->ht(),evt->mht()).c_str()] );
            } // End of muon is isolated
          } // End of pt matching
        } // End of reconstructed muon
      } // End of muon in acceptance



    } // end of loop over events


     // Compute acceptance
    TH1* hAcc = static_cast<TH1*>(hAccPass->Clone("hAcc"));
    hAcc->Divide(hAccPass,hAccAll,1,1,"B");// we use B option here because the two histograms are correlated. see TH1 page in the root manual.

    // Compute efficiencies
    TH1* hEff = static_cast<TH1*>(hIsoRecoPass->Clone("hEff"));
    hEff->Divide(hIsoRecoPass,hIsoRecoAll,1,1,"B");

    if(verbose!=0){
      for(int j=1; j<= totNbins; j++){
        printf("hAccAll: %g hAccPass: %g hAcc: %g hIsoRecoAll: %g hIsoRecoPass: %g hEff: %g \n ",hAccAll->GetBinContent(j),hAccPass->GetBinContent(j),hAcc->GetBinContent(j),hIsoRecoAll->GetBinContent(j),hIsoRecoPass->GetBinContent(j),hEff->GetBinContent(j));
      }
    }


    // --- Save the Histograms to File -----------------------------------
    sprintf(tempname,"LostLepton/LostLepton2_MuonEfficienciesFrom%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
    TFile outFile(tempname,"RECREATE");
    hAcc->Write();
    hEff->Write();
    hAccAll->Write();
    hAccPass->Write();
    hIsoRecoAll->Write();
    hIsoRecoPass->Write();
    outFile.Close();




  } // end of main
