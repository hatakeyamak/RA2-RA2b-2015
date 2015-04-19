
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
  double DeltaT(unsigned int i, vector<double>JetPtvec,vector<double>JetPhivec );


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

    // Probability of muon coming from Tau
    TFile * Prob_Tau_mu_file = new TFile("TauHad/Probability_Tau_mu_TTbar_.root","R");
    sprintf(histname,"hProb_Tau_mu");
    TH1D * hProb_Tau_mu =(TH1D *) Prob_Tau_mu_file->Get(histname)->Clone();

    // Acceptance and efficiencies
    TFile * MuEffAcc_file = new TFile("LostLepton/LostLepton2_MuonEfficienciesFromTTbar_.root","R");
    sprintf(histname,"hAcc");
    TH1D * hAcc =(TH1D *) MuEffAcc_file->Get(histname)->Clone();
    TH1D * hEff =(TH1D *) MuEffAcc_file->Get("hEff")->Clone();
    // get the map between the strings repressenting the bins and the bin numbers
    // map<string,int> binMap = utils2::BinMap();
    map<string,int> binMap = utils2::BinMap_NoB();

    TFile * resp_file = new TFile("TauHad/HadTau_TauResponseTemplates_TTbar_.root","R");
    for(int i=0; i<TauResponse_nBins; i++){
      sprintf(histname,"hTauResp_%d",i);
      vec_resp.push_back( (TH1D*) resp_file->Get( histname )->Clone() );
    }

    int eventN=0;
    while( evt->loadNext() ){
      eventN++;

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
      for(int i=0; i< evt->MuPtVec_().size(); i++){
        double pt=evt->MuPtVec_().at(i);
        double eta=evt->MuEtaVec_().at(i);
        double phi=evt->MuPhiVec_().at(i);
        // double mu_mt_w =muonsMtw->at(i);  ????
        if( pt>20. && fabs(eta)< 2.1  ){
          if(verbose!=0)printf(" \n Muons: \n pt: %g eta: %g phi: %g \n ",pt,eta,phi);
          temp3vec.SetPtEtaPhi(pt,eta,phi);
          vec_recoMuon3vec.push_back(temp3vec);
          // vec_recoMuMTW.push_back(mu_mt_w); ???????
        }
      }

      ///select electrons with pt>10. eta<2.5 relIso<.2
      vec_recoElec3vec.clear();
      for(int i=0; i< evt->ElecPtVec_().size(); i++){
        double pt=evt->ElecPtVec_().at(i);
        double eta=evt->ElecEtaVec_().at(i);
        double phi=evt->ElecPhiVec_().at(i);
        // double mu_mt_w =muonsMtw->at(i);  ????
        if( pt>10. && fabs(eta)< 2.5 ){
          if(verbose!=0)printf(" \n Electrons: \n pt: %g eta: %g phi: %g \n ",pt,eta,phi);
          temp3vec.SetPtEtaPhi(pt,eta,phi);
          vec_recoElec3vec.push_back(temp3vec);
        }
      }

      if(verbose!=0)printf(" \n **************************************** \n #Muons: %d #Electrons: %d \n ****************************** \n ",vec_recoMuon3vec.size(),vec_recoElec3vec.size());

      //if( template_nMuons == 1 && template_nElectrons == 0 ) {
      if( vec_recoMuon3vec.size() == 1 && vec_recoElec3vec.size() == 0 ){
        muPt = vec_recoMuon3vec[0].Pt();
        muEta = vec_recoMuon3vec[0].Eta();
        muPhi = vec_recoMuon3vec[0].Phi();
        // muMtW = vec_recoMuMTW[0]; ???????

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
        int JetIdx=-99;
        utils->findMatchedObject(JetIdx,muEta,muPhi,evt->JetsPtVec_(), evt->JetsEtaVec_(), evt->JetsPhiVec_(),deltaRMax,verbose);
        if(verbose!=0){printf(" \n **************************************** \n JetIdx: %d \n ",JetIdx);
        }

        //New HT:
        double HT = evt->ht() + simTauJetPt-muPt;

        //New MHT
        double mhtX = evt->mht()*cos(evt->mhtphi())-(simTauJetPt-muPt)*cos(simTauJetPhi);///the minus sign is because of Mht definition.
        double mhtY = evt->mht()*sin(evt->mhtphi())-(simTauJetPt-muPt)*sin(simTauJetPhi);

        if(verbose!=0)printf("############ \n mhtX: %g, mhtY: %g \n",mhtX,mhtY);
        if(verbose!=0)printf("evt->mht: %g, evt->mhtphi: %g, simTauJetPt: %g, simTauJetPhi: %g \n",evt->mht(),evt->mhtphi(),simTauJetPt,simTauJetPhi);

printf("simTauJetPt: %g simTauJetEta: %g simTauJetPhi: %g \n",simTauJetPt,simTauJetEta,simTauJetPhi);

        double template_mht = sqrt(pow(mhtX,2)+pow(mhtY,2));
        double template_mhtphi=-99.;
        if(mhtX>0)template_mhtphi = atan(mhtY/mhtX);
        else{
          if(mhtY>0) template_mhtphi = 3.14+atan(mhtY/mhtX);
          else template_mhtphi = -3.14+atan(mhtY/mhtX);
        }

        //New MET
        double metX = evt->met()*cos(evt->metphi())-(simTauJetPt-muPt)*cos(simTauJetPhi);///the minus sign is because of Mht definition.
        double metY = evt->met()*sin(evt->metphi())-(simTauJetPt-muPt)*sin(simTauJetPhi);

        if(verbose!=0)printf("############ \n metX: %g, metY: %g \n",metX,metY);
        if(verbose!=0)printf("evt->met: %g, evt->metphi: %g, simTauJetPt: %g, simTauJetPhi: %g \n",evt->met(),evt->metphi(),simTauJetPt,simTauJetPhi);

        double template_met = sqrt(pow(metX,2)+pow(metY,2));
        double template_metphi=-99.;
        if(metX>0)template_metphi = atan(metY/metX);
        else{
          if(metY>0) template_metphi = 3.14+atan(metY/metX);
          else template_metphi = -3.14+atan(metY/metX);
        }

        if(verbose!=0)printf("\n template_mht: %g, template_mhtphi: %g \n ", template_mht,template_mhtphi);
        if(verbose!=0)printf("\n template_met: %g, template_metphi: %g \n ", template_met,template_metphi);
        
        // New Jet(Pt/Eta/Phi)Vec
        vector<double> NewJetPtVec = evt->JetsPtVec_();
        vector<double> NewJetEtaVec = evt->JetsEtaVec_();
        vector<double> NewJetPhiVec = evt->JetsPhiVec_();
        if(fabs(simTauJetEta)<2.4 && (simTauJetPt-muPt)>30.){
          NewJetPtVec.push_back(simTauJetPt-muPt);
          NewJetEtaVec.push_back(simTauJetEta);
          NewJetPhiVec.push_back(simTauJetPhi);
        }

        // New minDelPhi_N
        double dpnhat[3]; 
        unsigned int goodcount=0;
        for(unsigned int i=0; i< NewJetPtVec.size();i++){
          if(goodcount<3 && NewJetPtVec[i] > 30. && fabs( NewJetEtaVec[i] ) < 5. ){ 
            float dphi=std::abs(TVector2::Phi_mpi_pi(NewJetPhiVec[i] - evt->metphi()));
            float dT=DeltaT(i, NewJetPtVec,NewJetPhiVec);
            if(dT/evt->met()>=1.0)dpnhat[goodcount]=dphi/(TMath::Pi()/2.0);
            else dpnhat[goodcount]=dphi/asin(dT/evt->met());
            ++goodcount;
          }
        }// end loop over jets
        float mindpn=9999;
        for(int i=0; i<3; ++i){
          if(mindpn>fabs(dpnhat[i]))mindpn=fabs(dpnhat[i]);
        } 

        if(verbose!=0) cout << "\n evt->minDeltaPhiN(): " << evt->minDeltaPhiN() << " mindpn: " << mindpn << endl;

        //add the simTau Jet to the list if it satisfy the conditions
        double cntNJetsPt30Eta24=(double) NewJetPhiVec.size();
        if(verbose!=0){
          cout << " NewJetPhiVec.size(): " <<(int) NewJetPhiVec.size() << endl;
          cout << " cntNJetsPt30Eta24: " << (int)cntNJetsPt30Eta24 << endl;
        }

        // get the effieciencies and acceptance
        // if baseline cuts on the main variables are passed then calculate the efficiencies otherwise simply take 0.75 as the efficiency.
        double Eff;
        if(cntNJetsPt30Eta24>=4 && HT >= 500 && template_mht >= 200){
          // Eff = hEff->GetBinContent(binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht)]);
          Eff = hEff->GetBinContent(binMap[utils2::findBin_NoB(cntNJetsPt30Eta24,HT,template_mht)]);
        }else{
          Eff=0.75;
        }

        // if baseline cuts on the main variables are passed then calculate the acceptance otherwise simply take 0.9 as the acceptance.
        double Acc;
        if(cntNJetsPt30Eta24>=4 && HT >= 500 && template_mht >= 200){
          // Acc = hAcc->GetBinContent(binMap[utils2::findBin(cntNJetsPt30Eta24,nbtag,HT,template_mht)]);
          Acc = hAcc->GetBinContent(binMap[utils2::findBin_NoB(cntNJetsPt30Eta24,HT,template_mht)]);
        }else{
          Acc=0.9;
        }

        if(verbose!=0)printf("Eff: %g Acc: %g njet: %d nbtag: %d ht: %g mht: %g binN: %d \n ",Eff,Acc, cntNJetsPt30Eta24,evt->nBtags(),HT,template_mht, binMap[utils2::findBin_NoB(cntNJetsPt30Eta24,HT,template_mht)]);

        if(Acc==0 || Eff==0){printf("eventN: %d Acc or Eff =0 \n Eff: %g Acc: %g njet: %d nbtag: %d ht: %g mht: %g \n ",eventN,Eff,Acc, cntNJetsPt30Eta24,evt->nBtags(),HT,template_mht);}
        if(Acc==0)Acc=0.9;
        if(Eff==0)Eff=0.75;

        // Not all the muons are coming from W. Some of them are coming from Tau which should not be considered in our estimation.
        double Prob_Tau_mu = hProb_Tau_mu->GetBinContent(hProb_Tau_mu->GetXaxis()->FindBin(muPt));

        double totWeight=evt->weight()*1*0.64*(1/(Acc*Eff))*(1-Prob_Tau_mu);//the 0.64 is because only 64% of tau's decay hadronically. Here 0.9 is acceptance and 0.75 is efficiencies of both reconstruction and isolation.
        //build and array that contains the quantities we need a histogram for. Here order is important and must be the same as RA2nocutvec

        double eveinfvec[] = {totWeight, HT, template_mht ,(double) cntNJetsPt30Eta24,(double)evt->nBtags() ,(double) muPt, simTauJetPt};


        //loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"
        for(map<string, map<string , vector<TH1D> > >::iterator itt=map_map.begin(); itt!=map_map.end();itt++){//this will be terminated after the cuts

          ////determine what type of background should pass
          if(itt->first=="allEvents"){//all the cuts are inside this

            //Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts//Cuts

            //////loop over cut names and fill the histograms
            for(map<string , vector<TH1D> >::iterator ite=cut_histvec_map.begin(); ite!=cut_histvec_map.end();ite++){


              if(sel->checkcut_HadTau(ite->first,HT,template_mht,mindpn,cntNJetsPt30Eta24,evt->nBtags(),evt->nLeptons(),evt->nIso())==true){

                histobjmap[ite->first].fill(Nhists,&eveinfvec[0] ,&itt->second[ite->first][0]);

            }//end of loop over cut names

              }
            ////EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts//EndOfCuts
            
          }//end of bg_type determination
        }//end of loop over all the different backgrounds: "allEvents", "Wlv", "Zvv"

      } // End if exactly one muon

    } // end of loop over events


    //open a file to write the histograms
    sprintf(tempname,"TauHad2/HadTauEstimation_%s_%s.root",subSampleKey.c_str(),inputnumber.c_str());
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

    delete resp_file;



  } // end of main


  double DeltaT(unsigned int i, vector<double>JetPtvec,vector<double>JetPhivec ){

      double deltaT=0;
      float jres=0.1;
      double sum=0;
      double Jpx_i= JetPtvec[i]*cos(JetPhivec[i]);
      double Jpy_i= JetPtvec[i]*sin(JetPhivec[i]);

      for(unsigned int j=0; j< JetPtvec.size(); ++j){
          if(j==i)continue;
          double Jpx_j= JetPtvec[j]*cos(JetPhivec[j]);
          double Jpy_j= JetPtvec[j]*sin(JetPhivec[j]);

          sum=sum+(Jpx_i*Jpy_j-Jpx_j*Jpy_i) * (Jpx_i*Jpy_j-Jpx_j*Jpy_i);
      }
      deltaT=jres*sqrt(sum)/JetPtvec[i];

      return deltaT;
  }

