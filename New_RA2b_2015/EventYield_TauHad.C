#include <map>
#include <cstdio>

EventYield_TauHad(){
  char tempname[200];
  TH1D * tempHist;
  
  TFile * exp_f = new TFile("TauHad/GenInfo_HadTauEstimation_TTbar_.root","R");
  TFile * pre_f = new TFile("TauHad2/HadTauEstimation_TTbar_.root","R");

  map<int,string> cutname;

    cutname[0]="nocut";cutname[1]="Njet_4";cutname[2]="ht_500";
    cutname[3]="mht_200";cutname[4]="nolep";
    cutname[5]="isoMu";cutname[6]="isoElec";cutname[7]="isoPion";
    cutname[8]="delphi";cutname[9]="CSVM_0";
    cutname[10]="CSVM_1";cutname[11]="CSVM_2";cutname[12]="CSVM_3";

  double exp=0,pre=0;

  cout<< " nocut(corresponding with \"if(MuFromTauVec[0]==0){\" in elog 183 ) for prediction and with \"if( genTauPt > LeptonAcceptance::muonPtMin() && std::abs(genTauEta) < LeptonAcceptance::muonEtaMax() ){\" for expectation )\n";
  for(int i=0; i<cutname.size();i++){
    sprintf(tempname,"allEvents/%s/HT_%s_allEvents",cutname[i].c_str(),cutname[i].c_str());
    tempHist=(TH1D*)exp_f->Get(tempname)->Clone();
    exp=tempHist->GetEntries();
    tempHist=(TH1D*)pre_f->Get(tempname)->Clone();
    pre=tempHist->GetEntries();

    printf("cutname: %s ==>> prediction: %g *0.64 = %g expectation: %g Pre*0.64/Exp: %g \n \n ",cutname[i].c_str(),pre,pre*0.64,exp,(pre*0.64/exp));

  }





}
