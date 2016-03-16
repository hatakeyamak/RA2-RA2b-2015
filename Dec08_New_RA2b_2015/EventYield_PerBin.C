#include "Selection.h"
#include <map>
#include <cstdio>
#include <string>

/*
root.exe -b -q 'EventYield_TauHad.C("TTbar_")'
root.exe -b -q 'EventYield_TauHad.C("WJet_600_inf_")'

root.exe -b -q 'EventYield_TauHad.C("stacked")'
root.exe -b -q 'EventYield_TauHad.C("TTbar_stacked")'
root.exe -b -q 'EventYield_TauHad.C("WJet_stacked")'
root.exe -b -q 'EventYield_TauHad.C("T_stacked")'
*/

EventYield_PerBin(string sample="TTbar_",string histname="MHT"){
  char tempname[200];
  TH1D * tempHist;
  THStack * tempstack;
  TH1D * expHist_iso, * expHist_phi, * expHist_lowphi;
  TH1D * preHist_iso, * preHist_phi, * preHist_lowphi;

  if(sample.find("stack")==string::npos)sprintf(tempname,"TauHad/GenInfo_HadTauEstimation_%s.root",sample.c_str());
  else sprintf(tempname,"TauHad/Stack/GenInfo_HadTauEstimation_%s.root",sample.c_str()); 
  TFile * exp_f = new TFile(tempname,"R");
  std::cout << tempname << std::endl;
  if(sample.find("stack")==string::npos)sprintf(tempname,"TauHad2/HadTauEstimation_%s.root",sample.c_str());
  else sprintf(tempname,"TauHad2/Stack/HadTauEstimation_%s.root",sample.c_str());
  TFile * pre_f = new TFile(tempname,"R");
  std::cout << tempname << std::endl;


  //
  // Beyond Preselection
  //





    sprintf(tempname,"allEvents/isoPion/%s_isoPion_allEvents",histname.c_str());
    if(sample.find("stack")!=string::npos){
      tempstack=(THStack*) exp_f->Get(tempname)->Clone();
      expHist_iso= (TH1D*) tempstack->GetStack()->Last();
      tempstack=(THStack*) pre_f->Get(tempname)->Clone();
      preHist_iso= (TH1D*) tempstack->GetStack()->Last();
    }
    else{
      expHist_iso=(TH1D*) exp_f->Get(tempname)->Clone();
      preHist_iso=(TH1D*) pre_f->Get(tempname)->Clone();
    }   

    sprintf(tempname,"allEvents/delphi/%s_delphi_allEvents",histname.c_str());
    if(sample.find("stack")!=string::npos){
      tempstack=(THStack*) exp_f->Get(tempname)->Clone();
      expHist_phi= (TH1D*) tempstack->GetStack()->Last();
      tempstack=(THStack*) pre_f->Get(tempname)->Clone();
      preHist_phi= (TH1D*) tempstack->GetStack()->Last();
    }
    else{
      expHist_phi=(TH1D*) exp_f->Get(tempname)->Clone();
      preHist_phi=(TH1D*) pre_f->Get(tempname)->Clone();
    }

    sprintf(tempname,"allEvents/low_Dphi/%s_low_Dphi_allEvents",histname.c_str());
    if(sample.find("stack")!=string::npos){
      tempstack=(THStack*) exp_f->Get(tempname)->Clone();
      expHist_lowphi= (TH1D*) tempstack->GetStack()->Last();
      tempstack=(THStack*) pre_f->Get(tempname)->Clone();
      preHist_lowphi= (TH1D*) tempstack->GetStack()->Last();
    }
    else{
      expHist_lowphi=(TH1D*) exp_f->Get(tempname)->Clone();
      preHist_lowphi=(TH1D*) pre_f->Get(tempname)->Clone();
    }


  
    for (int ibin=0; ibin<=preHist_iso->GetNbinsX(); ibin++){

      if(preHist_iso->GetBinContent(ibin)!=0){

cout << " ################ \n ";

printf(" prediction[%d]:isoPion: %12.10f delphi: (%2.0f%) low_Dphi: (%2.0f%) \n ",ibin,preHist_iso->GetBinContent(ibin),(preHist_phi->GetBinContent(ibin)/preHist_iso->GetBinContent(ibin))*100,(preHist_lowphi->GetBinContent(ibin)/preHist_iso->GetBinContent(ibin))*100);

printf(" exppectation[%d]:isoPion: %12.10f delphi: (%2.0f%) low_Dphi: (%2.0f%) \n ",ibin,expHist_iso->GetBinContent(ibin),(expHist_phi->GetBinContent(ibin)/expHist_iso->GetBinContent(ibin))*100,(expHist_lowphi->GetBinContent(ibin)/expHist_iso->GetBinContent(ibin))*100);

      }
    }


}
