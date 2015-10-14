#include <vector>
#include <cstdio>
#include <string>
#include <map>

CalcUncertainties(){

  char tempname[200];
  
  TFile * fileData = new TFile("TauHad2/Elog359Oct12_HadTauEstimation_data_SingleMuon_v15cd_.root","R");
  TFile * fileExp  = new TFile("TauHad/Stack/GenInfo_HadTauEstimation_stacked.root","R");

  vector<string> histVec;
  histVec.push_back("searchH_b_");
  histVec.push_back("QCD_");
  
  map<int,string> statDir;
  statDir[0]="AccPlus";
  statDir[1]="AccMinus";
  statDir[2]="IsoPlus";
  statDir[3]="IsoMinus";
  statDir[4]="MTPlus";
  statDir[5]="MTMinus";
  statDir[6]="MuFromTauPlus";
  statDir[7]="MuFromTauMinus";
  statDir[8]="MuRecoIsoPlus";
  statDir[9]="MuRecoIsoMinus";
  statDir[10]="BMistag_statPlus";
  statDir[11]="BMistag_statMinus";
  statDir[12]="Tau_BrRatio_Plus";
  statDir[13]="Tau_BrRatio_Minus";
  statDir[14]="DileptonPlus";
  statDir[15]="DileptonMinus";

  map<int,string> sysDir;  
  sysDir[0]="BMistagPlus";
  sysDir[1]="BMistagMinus";
  sysDir[2]="RecoIsoSysPlus";
  sysDir[3]="RecoIsoSysMinus";

  double stat, statPlus, statMinus, sysPlus, sysMinus;
  TH1D *nominal, * hist, * histExp; 
  THStack * stack;
 
  // searchH_b_ 
  nominal=(TH1D*) fileData->Get("allEvents/delphi/searchH_b_")->Clone();
  stack=(THStack*) fileExp->Get("searchH_b")->Clone();
  histExp=(TH1D*)stack->GetStack()->Last();

  for(int ibin=0;ibin<nominal->GetNbinsX()+2;ibin++){
    stat=0.; statPlus=0.; statMinus=0.; sysPlus=0.; sysMinus=0.; statExp=0.;

    // stat error since limited # of events
    stat=nominal->GetBinError(ibin);
    statExp=histExp->GetBinError(ibin);
   
    // loop over stat of weights 
    for(int istat=0; istat < statDir.size();istat++){

      sprintf(tempname,"%s/delphi/searchH_b_",statDir[istat].c_str());
      hist = (TH1D*) fileData->Get(tempname)->Clone();

      if(istat%2==0){//only plus directories
        statPlus+=pow((nominal->GetBinContent(ibin)-hist->GetBinContent(ibin)),2);
      }
      if(istat%2==1){//only plus directories
        statMinus+=pow((nominal->GetBinContent(ibin)-hist->GetBinContent(ibin)),2);
      }
    }
    statPlus=sqrt(statPlus);
    statMinus=sqrt(statMinus);
     
    // loop over systematics 
    for(int isys=0; isys < sysDir.size();isys++){

      sprintf(tempname,"%s/delphi/searchH_b_",sysDir[isys].c_str());
      hist = (TH1D*) fileData->Get(tempname)->Clone();

      if(isys%2==0){//only plus directories
        sysPlus+=pow((nominal->GetBinContent(ibin)-hist->GetBinContent(ibin)),2);
      }
      if(isys%2==1){//only plus directories
        sysMinus+=pow((nominal->GetBinContent(ibin)-hist->GetBinContent(ibin)),2);
      }
    }
    sysPlus=sqrt(sysPlus);
    sysMinus=sqrt(sysMinus);

    
    printf("nominal[%d]: %6.6f +- %3.6f + %3.6f - %3.6f + %3.6f - %3.6f \n",ibin,nominal->GetBinContent(ibin),stat,
           statPlus, statMinus , sysPlus, sysMinus
          );
    printf("nominal[%d]: %6.6f +- %3.6f \n",ibin,histExp->GetBinContent(ibin),statExp);
  

  }  



  // QCD_ 
  nominal=(TH1D*) fileData->Get("allEvents/low_Dphi/QCD_")->Clone();
  stack=(THStack*) fileExp->Get("QCD_Low")->Clone();
  histExp=(TH1D*)stack->GetStack()->Last();

  for(int ibin=0;ibin<nominal->GetNbinsX()+2;ibin++){
    stat=0.; statPlus=0.; statMinus=0.; sysPlus=0.; sysMinus=0.; statExp=0.;

    // stat error since limited # of events
    stat=nominal->GetBinError(ibin);
    statExp=histExp->GetBinError(ibin);
   
    // loop over stat of weights 
    for(int istat=0; istat < statDir.size();istat++){

      sprintf(tempname,"%s/low_Dphi/QCD_",statDir[istat].c_str());
      hist = (TH1D*) fileData->Get(tempname)->Clone();

      if(istat%2==0){//only plus directories
        statPlus+=pow((nominal->GetBinContent(ibin)-hist->GetBinContent(ibin)),2);
      }
      if(istat%2==1){//only plus directories
        statMinus+=pow((nominal->GetBinContent(ibin)-hist->GetBinContent(ibin)),2);
      }
    }
    statPlus=sqrt(statPlus);
    statMinus=sqrt(statMinus);
     
    // loop over systematics 
    for(int isys=0; isys < sysDir.size();isys++){

      sprintf(tempname,"%s/low_Dphi/QCD_",sysDir[isys].c_str());
      hist = (TH1D*) fileData->Get(tempname)->Clone();

      if(isys%2==0){//only plus directories
        sysPlus+=pow((nominal->GetBinContent(ibin)-hist->GetBinContent(ibin)),2);
      }
      if(isys%2==1){//only plus directories
        sysMinus+=pow((nominal->GetBinContent(ibin)-hist->GetBinContent(ibin)),2);
      }
    }
    sysPlus=sqrt(sysPlus);
    sysMinus=sqrt(sysMinus);

    
    printf("nominal[%d]: %6.6f +- %3.6f + %3.6f - %3.6f + %3.6f - %3.6f \n",ibin,nominal->GetBinContent(ibin),stat,
           statPlus, statMinus , sysPlus, sysMinus
          );
    printf("nominal[%d]: %6.6f +- %3.6f \n",ibin,histExp->GetBinContent(ibin),statExp);
  

  }  





}
