
//Lost Lepton Efficiency and Acceptance maps
#include "Events.h"
#include "Selection.h"
#include "TTree.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "TChain.h"
#include <cmath>
#include <map>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "TLorentzVector.h"
#include <stdio.h>
#include "TColor.h"
#include "TF1.h"
#include "TLegend.h"
#include "TVector3.h"
#include "TFile.h"
#include "TH1.h"
#include "TVector2.h"
#include "TCanvas.h"
#include "TH2.h"

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
  vector<TH1D > vec;
  map<int, string> eventType;
  map<string , vector<TH1D> > cut_histvec_map;
  map<string, map<string , vector<TH1D> > > map_map;
  map<string, histClass> histobjmap;
  histClass histObj;

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
  TH1D NLostLep_hist = TH1D("NLostLep","Number of Lost Lepton Distribution",20,0,20);
  vec.push_back(NLostLep_hist);
  int Nhists=((int)(vec.size())-1);//-1 is because weight shouldn't be counted.

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

  // Veto Events with bad jets?
  bool JetIdSwitch=false;
  
  // Count muon, electron, jets? 
  bool counterSwitch=true;

  // To calculate JetId efficiency
  int nTotEvent=0 , nFailJetIdEvent=0;

  // Counter for muon
  int NSlimMu=0,NSlimMuEta=0,NSlimMuPt=0,NMuID=0,NMuIDIso=0;
  int MuEve_noCut=0,MuEve_Eta=0,MuEve_Pt=0,MuEve_ID=0,MuEve_IDIso=0;
  // Counter for electron
  int NSlimElec=0,NSlimElecEta=0,NSlimElecPt=0,NElecID=0,NElecIDIso=0;
  int ElecEve_noCut=0,ElecEve_Eta=0,ElecEve_Pt=0,ElecEve_ID=0,ElecEve_IDIso=0;
  // Counter for jet
  int NSlimJet=0,NSlimJetEtaPt=0,NSlimJetID=0;
  int JetEve_noCut=0,JetEve_EtaPt=0,JetEve_ID=0;
  // Counter for IsoTrks
  int NIsoElec=0,NIsoMu=0,NIsoPion=0;
  int IsoElecEve=0,IsoMuEve=0,IsoPionEve=0;

  // Loop over the events (tree entries)
  int eventN=0;
  while( evt->loadNext() ){

    if(counterSwitch){
      // Muon count 
      NSlimMu+=evt->slimmedMuPtVec_().size(); 
      for(int i=0; i<evt->slimmedMuPtVec_().size();i++){
        if(abs(evt->slimmedMuEtaVec_()[i])<2.4){
          NSlimMuEta++;
          if(evt->slimmedMuPtVec_()[i]>10.){
            NSlimMuPt++;
          }
        }
      }
      NMuID+=evt->MuNoIsoPtVec_().size();
      NMuIDIso+=evt->MuPtVec_().size();
      if(evt->slimmedMuPtVec_().size()>0)MuEve_noCut++;
      for(int i=0; i<evt->slimmedMuPtVec_().size();i++){
        if(abs(evt->slimmedMuEtaVec_()[i])<2.4){
          MuEve_Eta++;
          break;
        }
      }
      for(int i=0; i<evt->slimmedMuPtVec_().size();i++){
        if(evt->slimmedMuPtVec_()[i]>10. && abs(evt->slimmedMuEtaVec_()[i])<2.4){
          MuEve_Pt++;
          break;
        }
      }
      if(evt->MuNoIsoPtVec_().size()>0)MuEve_ID++;
      if(evt->MuPtVec_().size()>0)MuEve_IDIso++;

      // Elecon count
      NSlimElec+=evt->slimmedElecPtVec_().size();
      for(int i=0; i<evt->slimmedElecPtVec_().size();i++){
        if(abs(evt->slimmedElecEtaVec_()[i])<2.5){
          NSlimElecEta++;
          if(evt->slimmedElecPtVec_()[i]>10.){
            NSlimElecPt++;
          }
        }
      }
      NElecID+=evt->ElecNoIsoPtVec_().size();
      NElecIDIso+=evt->ElecPtVec_().size();
      if(evt->slimmedElecPtVec_().size()>0)ElecEve_noCut++;
      for(int i=0; i<evt->slimmedElecPtVec_().size();i++){
        if(abs(evt->slimmedElecEtaVec_()[i])<2.5){
          ElecEve_Eta++;
          break;
        }
      }
      for(int i=0; i<evt->slimmedElecPtVec_().size();i++){
        if(evt->slimmedElecPtVec_()[i]>10. && abs(evt->slimmedElecEtaVec_()[i])<2.5){
          ElecEve_Pt++;
          break;
        }
      }
      if(evt->ElecNoIsoPtVec_().size()>0)ElecEve_ID++;
      if(evt->ElecPtVec_().size()>0)ElecEve_IDIso++;

      // Jet count
      for(int i=0; i< evt->slimJetPtVec_().size(); i++){
        if(evt->slimJetPtVec_()[i] > 10.){
          NSlimJet++;
          if( evt->slimJetPtVec_()[i] > 30. && fabs(evt->slimJetEtaVec_()[i])<5.){
            NSlimJetEtaPt++;    
            if(evt->slimJetID_().at(i)==1)NSlimJetID++;
          }
        }
      }
      for(int i=0; i< evt->slimJetPtVec_().size(); i++){
        if(evt->slimJetPtVec_()[i] > 10.){
          JetEve_noCut++;    
          break;
        }
      }
      for(int i=0; i< evt->slimJetPtVec_().size(); i++){
        if(evt->slimJetPtVec_()[i] > 30. && fabs(evt->slimJetEtaVec_()[i])<5.){
          JetEve_EtaPt++;
          break;
        }
      }
      for(int i=0; i< evt->slimJetPtVec_().size(); i++){
        if(evt->slimJetPtVec_()[i] > 30. && fabs(evt->slimJetEtaVec_()[i])<5. && evt->slimJetID_().at(i)==1){
          JetEve_ID++;
          break;
        }
      }

      // IsoTrk count
      NIsoElec+=evt->nIsoElec();
      NIsoMu+=evt->nIsoMu();
      NIsoPion+=evt->nIsoPion();
      if(evt->nIsoElec()>0)IsoElecEve++;
      if(evt->nIsoMu()>0)IsoMuEve++;
      if(evt->nIsoPion()>0)IsoPionEve++;
    }



    // Print out some information
    if(verbose!=0){
      printf(" ########################### \n event #: %d \n",eventN);
      printf(" ht: %g mht: %g nJets: %d nBtags: %d nIsoElec: %d nIsoMu: %d nIsoPion: %d nLeptons: %d \n ",evt->ht(),evt->mht(),evt->nJets(),evt->nBtags(),evt->nIsoElec(),evt->nIsoMu(),evt->nIsoPion(),evt->nLeptons());
      printf(" @@@@\n Jets section: \n Njets: %d \n ", evt->nJets());
      for(int i=0;i<evt->JetsPtVec_().size();i++){
        printf("jet#: %d pt: %g eta: %g phi: %g \n ",i+1,evt->JetsPtVec_()[i],evt->JetsEtaVec_()[i],evt->JetsPhiVec_()[i]);
      }
      printf(" @@@@\n Muons section: \n Nmuons: %d \n ", evt->MuPtVec_().size());
      for(int i=0;i<evt->MuPtVec_().size();i++){
        printf("Muon#: %d pt: %g eta: %g phi: %g \n ",i+1,evt->MuPtVec_()[i],evt->MuEtaVec_()[i],evt->MuPhiVec_()[i]);
      }
    }

    // JetId efficiency 
    // We want this after the baseline cuts
    if( verbose > 1 && evt->nJets() >= 4 && evt->ht() >= 500. && evt->mht() >= 200. && evt->nLeptons()==0 && evt->minDeltaPhiN() > 4.){
      for(int i=0; i< evt->slimJetPtVec_().size(); i++){
        if( evt->slimJetPtVec_()[i] > 30. && fabs(evt->slimJetEtaVec_()[i])<5. && evt->slimJetID_().at(i)==0){
          printf("event#: %d pt: %g eta: %g phi: %g jetId: %d \n ",eventN,evt->slimJetPtVec_()[i],evt->slimJetEtaVec_()[i],evt->slimJetPhiVec_()[i],evt->slimJetID_()[i]);
          nFailJetIdEvent++;
          break;
        }
      }
      nTotEvent++;
    }
    // Print out some information about slimJets
    if(verbose > 1){
      printf(" @@@@\n slimJets section: \n NSlimJets: %d \n ", evt->slimJetPtVec_().size());
      for(int i=0;i<evt->slimJetPtVec_().size();i++){
        printf("jet#: %d pt: %g eta: %g phi: %g jetId: %d \n ",i+1,evt->slimJetPtVec_()[i],evt->slimJetEtaVec_()[i],evt->slimJetPhiVec_()[i],evt->slimJetID_()[i]);
      }

    }

    // Through out an event that contains HTjets with bad id
    if(JetIdSwitch && evt->JetId()==0)continue;

    // Total weight
    double totWeight = evt->weight()*1.;

    //printf(" mu from tau: %d elec from tau : %d hadronicTau: %d \n ", evt->GenMu_GenMuFromTau_(), evt->GenElec_GenElecFromTau_(),evt->GenTau_GenTauHad_());
    //printf(" #Mu: %d #Tau: %d \n ", evt->GenMuPtVec_().size(), evt->GenTauPtVec_().size());

    // Build and array that contains the quantities we need a histogram for.
    // Here order is important and must be the same as RA2nocutvec
    double eveinfvec[] = {totWeight,(double) evt->ht(),(double) evt->mht() ,(double) evt->nJets(),(double) evt->nBtags(),(double) evt->nLeptons() }; //the last one gives the RA2 defined number of jets.     


    //loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
    for(map<string, map<string , vector<TH1D> > >::iterator itt=map_map.begin(); itt!=map_map.end();itt++){//this will be terminated after the cuts

      ////determine what type of background should pass
      if(itt->first=="allEvents"){//all the cuts are inside this

        //Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts

        //////loop over cut names and fill the histograms
        for(map<string , vector<TH1D> >::iterator ite=cut_histvec_map.begin(); ite!=cut_histvec_map.end();ite++){

//          if(sel->checkcut(ite->first,evt->ht(),evt->mht(),evt->minDeltaPhiN(),evt->nJets(),evt->nBtags(),evt->nLeptons(),evt->nIsoElec(),evt->nIsoMu(),evt->nIsoPion())==true){
          if(sel->checkcut(ite->first,evt->ht(),evt->mht(),evt->deltaPhi1(),evt->deltaPhi2(),evt->deltaPhi3(),evt->nJets(),evt->nBtags(),evt->nLeptons(),evt->nIsoElec(),evt->nIsoMu(),evt->nIsoPion())==true){
            histobjmap[ite->first].fill(Nhists,&eveinfvec[0] ,&itt->second[ite->first][0]);
          } 
        }//end of loop over cut names

        ////EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts

      }//end of bg_type determination
    }//end of loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"


    eventN++;
  } // End of loop over events

  if(counterSwitch){
    // Print out muon informations
    printf("NSlimMu: %d NSlimMuEta: %d NSlimMuPt: %d NMuID: %d NMuIDIso: %d \n ",NSlimMu,NSlimMuEta,NSlimMuPt,NMuID,NMuIDIso);
    printf("MuEve_noCut: %d MuEve_Eta: %d MuEve_Pt: %d MuEve_ID: %d MuEve_IDIso: %d \n ",MuEve_noCut,MuEve_Eta,MuEve_Pt,MuEve_ID,MuEve_IDIso);
    // Print out electron informations
    printf("NSlimElec: %d NSlimElecEta: %d NSlimElecPt: %d NElecID: %d NElecIDIso: %d \n ",NSlimElec,NSlimElecEta,NSlimElecPt,NElecID,NElecIDIso);
    printf("ElecEve_noCut: %d ElecEve_Eta: %d ElecEve_Pt: %d ElecEve_ID: %d ElecEve_IDIso: %d \n ",ElecEve_noCut,ElecEve_Eta,ElecEve_Pt,ElecEve_ID,ElecEve_IDIso);
    // Print out jet information
    printf("NSlimJet: %d NSlimJetEtaPt: %d NSlimJetID: %d \n ",NSlimJet,NSlimJetEtaPt,NSlimJetID);
    printf("JetEve_noCut: %d ,JetEve_EtaPt: %d ,JetEve_ID: %d \n ",JetEve_noCut,JetEve_EtaPt,JetEve_ID);
    printf("NIsoElec: %d NIsoMu: %d NIsoPion: %d \n",NIsoElec,NIsoMu,NIsoPion);
    printf("IsoElecEve: %d IsoMuEve: %d IsoPionEve: %d \n ",IsoElecEve,IsoMuEve,IsoPionEve);

  }


  // Calculate JetId efficiency
//  double JetIdEff = ((double)nFailJetIdEvent/nTotEvent)*100 ;
//  printf(" # totalEvents: %d # events that fail JetId: %d  Percent of failed JetId: %g \n ",nTotEvent,nFailJetIdEvent,JetIdEff);

  //open a file to write the histograms
  sprintf(tempname,"%s/results_%s_%s.root",Outdir.c_str(),subSampleKey.c_str(),inputnumber.c_str());
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




}
