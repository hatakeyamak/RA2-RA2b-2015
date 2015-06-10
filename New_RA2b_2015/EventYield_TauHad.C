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
    // search regions
    cutname[13]="search1";cutname[14]="search2";cutname[15]="search3";
    cutname[16]="search4";cutname[17]="search5";cutname[18]="search6";
    cutname[19]="search7";cutname[20]="search8";cutname[21]="search9";
    cutname[22]="search10";cutname[23]="search11";cutname[24]="search12";
    cutname[25]="search13";cutname[26]="search14";cutname[27]="search15";
    cutname[28]="search16";cutname[29]="search17";cutname[30]="search18";



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
