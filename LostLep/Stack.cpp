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
  std::cout << "WJ normalization scale factor determination done" << std::endl;



//..........................................//
// Muon From Tau 
//..........................................//

  // Load the files to a vector 
  // These are tau template files

  WJ_inputfilevec.clear();

  for(int i=1; i<=wjnHT ; i++){
    if(i==1)sprintf(tempname,"LostLepton2_MuonEfficienciesFromWJ_HT-100to200_.root");
    else if(i==2)sprintf(tempname,"LostLepton2_MuonEfficienciesFromWJ_HT-200to400_.root");
    else if(i==3)sprintf(tempname,"LostLepton2_MuonEfficienciesFromWJ_HT-400to600_.root");
    else if(i==4)sprintf(tempname,"LostLepton2_MuonEfficienciesFromWJ_HT-600toInf_.root");
    else{cout << " Error!! There are only 4 WJet ht binned sample " << endl;}
    WJ_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins 

  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"LostLepton2_MuonEfficienciesFromWJ_stacked.root");
  file = new TFile(tempname,"RECREATE");

  histname.clear();
  histname[0]="hAcc";
  histname[1]="hEff";
  histname[2]="hAccAll";
  histname[3]="hAccPass";
  histname[4]="hIsoRecoAll";
  histname[5]="hIsoRecoPass";


  for(int j=0; j<histname.size(); j++){

    if(j==0 || j==1)continue; // Stacking probability histograms has no meaning.
    sprintf(tempname,"%s",(histname[j]).c_str());

    for(int i=0; i<wjnHT ; i++){ // loop over different HT bins

      temphist = (TH1D *) WJ_inputfilevec.at(i)->Get(tempname)->Clone();
      temphist->Scale(WJ_scalevec[i]);
      temphist->SetFillColor(i+2);
      tempstack->Add(temphist);

    }//end of loop over HTbins 1..7

    temphist = (TH1D *) tempstack->GetStack()->Last();
    temphist->Write(tempname);
    delete tempstack;
    tempstack = new THStack("stack","Binned Sample Stack");


  }

  file->Close();
  printf("WJ Acc and Eff calculated. \n ");





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
  std::cout << "TTbar normalization scale factor determination done" << std::endl;
  



//..........................................//
// Muon From Tau 
//..........................................//

  // Load the files to a vector 
  // These are tau template files

  TTbar_inputfilevec.clear();

  for(int i=1; i<=ttbarnHT ; i++){
    if(i==1)sprintf(tempname,"LostLepton2_MuonEfficienciesFromTTbar_.root");
    else{cout << " Error!! There are only 1 TTbaret ht binned sample " << endl;}
    TTbar_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins 

  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"LostLepton2_MuonEfficienciesFromTTbar_stacked.root");
  file = new TFile(tempname,"RECREATE");

  histname.clear();
  histname[0]="hAcc";
  histname[1]="hEff";
  histname[2]="hAccAll";
  histname[3]="hAccPass";
  histname[4]="hIsoRecoAll";
  histname[5]="hIsoRecoPass";

  for(int j=0; j<histname.size(); j++){

    if(j==0 || j==1)continue; // Stacking probability histograms has no meaning.
    sprintf(tempname,"%s",(histname[j]).c_str());

    for(int i=0; i<ttbarnHT ; i++){ // loop over different HT bins

      temphist = (TH1D *) TTbar_inputfilevec.at(i)->Get(tempname)->Clone();
      temphist->Scale(TTbar_scalevec[i]);
      temphist->SetFillColor(i+2);
      tempstack->Add(temphist);

    }//end of loop over HTbins 1..7

    temphist = (TH1D *) tempstack->GetStack()->Last();
    temphist->Write(tempname);
    delete tempstack;
    tempstack = new THStack("stack","Binned Sample Stack");


  }

  file->Close();
  printf("TTbar Acc and Eff calculated. \n ");




// ..................................................................................................................................................... //
// Calcualte the rate of muons coming from tau
// ..................................................................................................................................................... //

  // Open the files to read
  sprintf(tempname,"LostLepton2_MuonEfficienciesFromTTbar_stacked.root");
  file = new TFile(tempname,"R");
  sprintf(tempname,"LostLepton2_MuonEfficienciesFromWJ_stacked.root");
  file2 = new TFile(tempname,"R");

  // Open a file to write
  sprintf(tempname,"LostLepton2_MuonEfficiencies_stacked.root");
  file3 = new TFile(tempname,"RECREATE");


  histname.clear();
  histname[0]="hAccAll";
  histname[1]="hAccPass";
  histname[2]="hIsoRecoAll";
  histname[3]="hIsoRecoPass";

  for(int j=0; j<histname.size(); j++){

    sprintf(tempname,"%s",(histname[j]).c_str());
    temphist = (TH1D *) file->Get(tempname)->Clone();
    temphist2 = (TH1D *) file2->Get(tempname)->Clone();

    temphist->Add(temphist,temphist2,1,1);

  temphist->Write();

  }
  file3->Close();
  file2->Close();
  file->Close();

  // Open a file to write
  sprintf(tempname,"LostLepton2_MuonEfficiencies_stacked.root");
  file2 = new TFile(tempname,"R");
  file = new TFile(tempname,"UPDATE");
  
  sprintf(tempname,"hAccPass");
  temphist = (TH1D *) file->Get(tempname)->Clone();
  sprintf(tempname,"hAccAll");
  temphist2 = (TH1D *) file2->Get(tempname)->Clone();

  temphist->Divide(temphist,temphist2,1,1,"B");
  temphist->SetName("hAcc");
  temphist->SetTitle("Acceptance");
  temphist->Write();



  sprintf(tempname,"hIsoRecoPass");
  temphist = (TH1D *) file->Get(tempname)->Clone();
  sprintf(tempname,"hIsoRecoAll");
  temphist2 = (TH1D *) file2->Get(tempname)->Clone();

  temphist->Divide(temphist,temphist2,1,1,"B");
  temphist->SetName("hEff");
  temphist->SetTitle("Efficiency");
  temphist->Write();


  file->Close();
  file2->Close();



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
