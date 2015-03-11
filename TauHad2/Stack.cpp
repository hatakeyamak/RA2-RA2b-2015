#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "THStack.h"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"



using namespace std;

class mainClass{

  // Some variables
  double tempvalue;
  char tempname[200];
  vector<double> WJ_scalevec, TTbar_scalevec;
  vector<TFile *> WJ_inputfilevec, TTbar_inputfilevec;
  map<int, string> cutname, histname;
  map<int, string> WJtype, TTbartype;
  TFile *file, *file2, *file3;
  TH1D *temphist, *temphist2;
  THStack * tempstack;
  TDirectory *cdtoitt, *cdtoit;

public:
mainClass(int luminosity=5000){ // luminosity is in /pb unit



  cutname[0]="nocut";cutname[1]="Njet_4";cutname[2]="ht_500" ;cutname[3]="mht_200";
  cutname[4]="delphi";cutname[5]="iso";
  cutname[6]="CSVM_0";
  cutname[7]="CSVM_1";
  cutname[8]="CSVM_2";
  cutname[9]="CSVM_3";

  WJtype[0]="EventsWith_1RecoMuon_0RecoElectron";
  TTbartype[0]="EventsWith_1RecoMuon_0RecoElectron";



// .....................................................................................................................................................//
// WJ Section
// .....................................................................................................................................................//

  //build a vector of scale factors
  //first load the cross sections into a vector
  vector<double> WJ_xs_vec;

  WJ_xs_vec.push_back(1817.0); // HT 100-200
  WJ_xs_vec.push_back(471.6);  // HT 200-400
  WJ_xs_vec.push_back(55.61);  // HT 400-600
  WJ_xs_vec.push_back(18.81);  // HT 600-Inf

  const int wjnHT = (int) WJ_xs_vec.size();   // Total number of HT bin samples

  for(int i=1; i<=wjnHT ; i++){
    if(i==1)sprintf(tempname,"../TauHad/GenInfo_HadTauEstimation_WJ_HT-100to200_.root");
    else if(i==2)sprintf(tempname,"../TauHad/GenInfo_HadTauEstimation_WJ_HT-200to400_.root");
    else if(i==3)sprintf(tempname,"../TauHad/GenInfo_HadTauEstimation_WJ_HT-400to600_.root");
    else if(i==4)sprintf(tempname,"../TauHad/GenInfo_HadTauEstimation_WJ_HT-600toInf_.root");
    else{cout << " Error!! There are only 4 WJet ht binned sample " << endl;}
    file = new TFile(tempname, "R");
    sprintf(tempname,"EventsWith_0RecoMuon_0RecoElectron_1tauJet/nocut/MHT_nocut_EventsWith_0RecoMuon_0RecoElectron_1tauJet");
    tempvalue = (luminosity*WJ_xs_vec[i-1])/((* (TH1D* ) file->Get(tempname)).GetEntries());
    WJ_scalevec.push_back(tempvalue);
  }//end of loop over HTbins 
  std::cout << "WJ normalization scale factor determination done \n " << std::endl;




//..........................................//
// main histograms like HT, MHT, ...
//..........................................//

  // Load the files to a vector 
  // These are the HT, MHT, .. variables
  for(int i=1; i<=wjnHT ; i++){
    if(i==1)sprintf(tempname,"HadTauEstimation_WJ_HT-100to200_.root");
    else if(i==2)sprintf(tempname,"HadTauEstimation_WJ_HT-200to400_.root");
    else if(i==3)sprintf(tempname,"HadTauEstimation_WJ_HT-400to600_.root");
    else if(i==4)sprintf(tempname,"HadTauEstimation_WJ_HT-600toInf_.root");
    else{cout << " Error!! There are only 4 WJet ht binned sample " << endl;}
    WJ_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins 

  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"HadTauEstimation_WJ_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="MuonPt";
  histname[6]="MtW";

  for(map<int , string >::iterator itt=WJtype.begin(); itt!=WJtype.end();itt++){        // loop over different event types

    cdtoitt = file->mkdir((itt->second).c_str());
    cdtoitt->cd();

    for(map<int , string >::iterator it=cutname.begin(); it!=cutname.end();it++){   // loop over different cutnames

      cdtoit =  cdtoitt->mkdir((it->second).c_str());
      cdtoit->cd();

      for(int j=0; j<histname.size(); j++){                                        // loop over different histograms

        for(int i=0; i<wjnHT ; i++){                                                  // loop over different HT bins

          //cout << "================================" << endl;
          //cout << "HT#: " <<i << ", WJtype: " << itt->second << ", cutname: " << it->second << ", hist#: " << j << endl;  
          sprintf(tempname,"%s/%s/%s_%s_%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str(),(it->second).c_str(),(itt->second).c_str());
          temphist = (TH1D *) WJ_inputfilevec.at(i)->Get(tempname)->Clone();
          temphist->Scale(WJ_scalevec[i]);
          temphist->SetFillColor(i+2);
          tempstack->Add(temphist);

        }//end of loop over HTbins 1..7

        sprintf(tempname,"%s_%s_%s",histname[j].c_str(),(it->second).c_str(),(itt->second).c_str());
        tempstack->Write(tempname);

        delete tempstack;
        tempstack = new THStack("stack","Binned Sample Stack");

      }//end of loop over histograms

    }//end of loop over cutnames 

  }//end of loop over event types

  file->Close();
  printf("WJ main histograms stacked \n ");






// .....................................................................................................................................................//
// TTbar Section
// .....................................................................................................................................................//

  //build a vector of scale factors
  //first load the cross sections into a vector
  vector<double> TTbar_xs_vec;

  TTbar_xs_vec.push_back(806.1); // 

  const int ttbarnHT = (int) TTbar_xs_vec.size();   // Total number of HT bin samples

  for(int i=1; i<=ttbarnHT ; i++){
    if(i==1)sprintf(tempname,"../TauHad/GenInfo_HadTauEstimation_TTbar_.root");
    else{cout << " Error!! There are only 1 TTbaret ht binned sample " << endl;}
    file = new TFile(tempname, "R");
    sprintf(tempname,"EventsWith_0RecoMuon_0RecoElectron_1tauJet/nocut/MHT_nocut_EventsWith_0RecoMuon_0RecoElectron_1tauJet");
    tempvalue = (luminosity*TTbar_xs_vec[i-1])/((* (TH1D* ) file->Get(tempname)).GetEntries());
    TTbar_scalevec.push_back(tempvalue);
  }//end of loop over HTbins 
  std::cout << "TTbar normalization scale factor determination done \n " << std::endl;
  



//..........................................//
// main histograms like HT, MHT, ...
//..........................................//

  // Load the files to a vector 
  // These are the HT, MHT, .. variables
  for(int i=1; i<=ttbarnHT ; i++){
    if(i==1)sprintf(tempname,"HadTauEstimation_TTbar_.root");
    else{cout << " Error!! There are only 1 TTbaret ht binned sample " << endl;}
    TTbar_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins 

  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"HadTauEstimation_TTbar_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="MuonPt";
  histname[6]="MtW";

  for(map<int , string >::iterator itt=TTbartype.begin(); itt!=TTbartype.end();itt++){        // loop over different event types

    cdtoitt = file->mkdir((itt->second).c_str());
    cdtoitt->cd();

    for(map<int , string >::iterator it=cutname.begin(); it!=cutname.end();it++){   // loop over different cutnames

      cdtoit =  cdtoitt->mkdir((it->second).c_str());
      cdtoit->cd();

      for(int j=0; j<histname.size(); j++){                                        // loop over different histograms

        for(int i=0; i<ttbarnHT ; i++){                                                  // loop over different HT bins

          //cout << "================================" << endl;
          //cout << "HT#: " <<i << ", TTbartype: " << itt->second << ", cutname: " << it->second << ", hist#: " << j << endl;  
          sprintf(tempname,"%s/%s/%s_%s_%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str(),(it->second).c_str(),(itt->second).c_str());
          temphist = (TH1D *) TTbar_inputfilevec.at(i)->Get(tempname)->Clone();
          temphist->Scale(TTbar_scalevec[i]);
          temphist->SetFillColor(i+2);
          tempstack->Add(temphist);

        }//end of loop over HTbins 1..7

        sprintf(tempname,"%s_%s_%s",histname[j].c_str(),(it->second).c_str(),(itt->second).c_str());
        tempstack->Write(tempname);
        delete tempstack;
        tempstack = new THStack("stack","Binned Sample Stack");

      }//end of loop over histograms

    }//end of loop over cutnames 

  }//end of loop over event types

  file->Close();
  printf("TTbar main histograms stacked \n ");



// ..................................................................................................................................................... //
// Stack main histograms from TTbar and WJet
// ..................................................................................................................................................... //

  // There are two contributors 1-TTbar and 2-WJ
  int NSamples=2;

  // A vector that contains all the samples
  vector<TFile*> sample_inputfilevec;

  THStack * tempstack2 = new THStack("stack","Binned Sample Stack");

  // Load the files to a vector 
  // These are the HT, MHT, .. variables
  for(int i=1; i<=NSamples ; i++){
    if(i==1)sprintf(tempname,"HadTauEstimation_TTbar_stacked.root");
    else if(i==2)sprintf(tempname,"HadTauEstimation_WJ_stacked.root");
    else{cout << " Error!! There are only 2 contributors! " << endl;}
    sample_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins 

  // Stack
  delete tempstack;
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"HadTauEstimation_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="MuonPt";
  histname[6]="MtW";

  for(map<int , string >::iterator itt=WJtype.begin(); itt!=WJtype.end();itt++){        // loop over different event types

    cdtoitt = file->mkdir((itt->second).c_str());
    cdtoitt->cd();

    for(map<int , string >::iterator it=cutname.begin(); it!=cutname.end();it++){   // loop over different cutnames

      cdtoit =  cdtoitt->mkdir((it->second).c_str());
      cdtoit->cd();


      for(int j=0; j<histname.size(); j++){                                        // loop over different histograms

        for(int i=0; i<NSamples ; i++){                                                  // loop over different HT bins

          //cout << "================================" << endl;
          //cout << "HT#: " <<i << ", WJtype: " << itt->second << ", cutname: " << it->second << ", hist#: " << j << endl;  
          sprintf(tempname,"%s/%s/%s_%s_%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str(),(it->second).c_str(),(itt->second).c_str());
          tempstack2 = (THStack *) sample_inputfilevec.at(i)->Get(tempname)->Clone();
          temphist = (TH1D*)tempstack2->GetStack()->Last(); 
          
          temphist->SetFillColor(i+2);
          tempstack->Add(temphist);

        }//end of loop over HTbins 1..7

        sprintf(tempname,"%s_%s_%s",histname[j].c_str(),(it->second).c_str(),(itt->second).c_str());
        tempstack->Write(tempname);
        delete tempstack;
        tempstack = new THStack("stack","Binned Sample Stack");

      }//end of loop over histograms

    }//end of loop over cutnames 

  }//end of loop over event types

  file->Close();
  printf("All samples main histograms stacked \n ");






} // End of the constructor 

}; // End of the class 

int main(int argc, char *argv[]){

/////////////////////////////////////
if (argc != 2)
{
std::cout << "Please enter something like: ./Stack \"5000\" " << std::endl;
return EXIT_FAILURE;
}
const string lum = argv[1];
/////////////////////////////////////

int luminosity = atoi(lum.c_str());

mainClass mainObj(luminosity);

}
