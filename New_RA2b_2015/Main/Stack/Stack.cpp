#include "Selection.h"

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


int main(){

  char tempname[200];
  vector<TFile *> T_inputfilevec,WJet_inputfilevec, TTbar_inputfilevec, ZJet_inputfilevec, QCD_inputfilevec;
  map<int, string> cutname, histname, Hname;
  TFile *file, *file2, *file30, *file3;
  TH1D *temphist, *temphist2, * temphist30, *temphistI, *temphistII, *temphistIII, *temphistI_lowDphi, *temphistII_lowDphi, *temphistIII_lowDphi;
  THStack * tempstack;
  TDirectory *cdtoitt, *cdtoit;
  Selection * sel = new Selection();
  cutname = sel->cutName();
  map<int, string> Ttype, WJettype, TTbartype, ZJettype, QCDtype;
  WJettype[0]="allEvents";
  TTbartype[0]="allEvents";
  Ttype[0]="allEvents";
  ZJettype[0]="allEvents";
  QCDtype[0]="allEvents";

  int qcdHT=7, zjnHT=4, ttbarnHT=1, wjnHT=7, tnHT=4;


// ..............................................................................................................//
// QCD Section
// .............................................................................................................//

  for(int i=1; i<=qcdHT ; i++){
    if(i==1)sprintf(tempname,"../results_filelist_Spring15_QCD_HT_200_300_.root");
    else if(i==2)sprintf(tempname,"../results_filelist_Spring15_QCD_HT_300_500_.root");
    else if(i==3)sprintf(tempname,"../results_filelist_Spring15_QCD_HT_500_700_.root");
    else if(i==4)sprintf(tempname,"../results_filelist_Spring15_QCD_HT_700_1000_.root");
    else if(i==5)sprintf(tempname,"../results_filelist_Spring15_QCD_HT_1000_1500_.root");
    else if(i==6)sprintf(tempname,"../results_filelist_Spring15_QCD_HT_1500_2000_.root");
    else if(i==7)sprintf(tempname,"../results_filelist_Spring15_QCD_HT_2000_Inf_.root");
    else{cout << " Error!! There are only 4 QCD ht binned sample " << endl;}
    QCD_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins


  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"results_filelist_Spring15_QCD_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="searchH_";
  histname[6]="searchH_b_";

  Hname.clear();
  Hname[0]="yield_tauId";
  Hname[1]="yield_tauId_trk";
  Hname[2]="cutflow_preselection";

  for(int j=0; j< Hname.size(); j++){

    for(int i=0; i<qcdHT ; i++){                                                  // loop over different HT bins

      sprintf(tempname,"%s",(Hname[j]).c_str());
      temphist = (TH1D *) QCD_inputfilevec.at(i)->Get(tempname)->Clone();
      //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
      temphist->SetFillColor(i+2);
      tempstack->Add(temphist);

    }//end of loop over HTbins 1..7
    sprintf(tempname,"%s",(Hname[j]).c_str());
    tempstack->Write(tempname);

    delete tempstack;
    tempstack = new THStack("stack","Binned Sample Stack");

  }

    for(map<int , string >::iterator itt=QCDtype.begin(); itt!=QCDtype.end();itt++){        // loop over different event types

    cdtoitt = file->mkdir((itt->second).c_str());
    cdtoitt->cd();

    for(map<int , string >::iterator it=cutname.begin(); it!=cutname.end();it++){   // loop over different cutnames

      cdtoit =  cdtoitt->mkdir((it->second).c_str());
      cdtoit->cd();

      for(int j=0; j<histname.size(); j++){                                        // loop over different histograms

        for(int i=0; i<qcdHT ; i++){                                                  // loop over different HT bins
          //cout << "================================" << endl;
          //cout << "HT#: " <<i << ", WJtype: " << itt->second << ", cutname: " << it->second << ", hist#: " << j << endl;
          if(j>=5)sprintf(tempname,"%s/%s/%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str());
          else sprintf(tempname,"%s/%s/%s_%s_%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str(),(it->second).c_str(),(itt->second).c_str());
          temphist = (TH1D *) QCD_inputfilevec.at(i)->Get(tempname)->Clone();
          //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
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
  printf("QCD main histograms stacked \n ");





// ..............................................................................................................//
// ZJet Section
// .............................................................................................................//

  for(int i=1; i<=zjnHT ; i++){
    if(i==1)sprintf(tempname,"../results_filelist_Spring15_ZJet_HT_100_200_.root");
    else if(i==2)sprintf(tempname,"../results_filelist_Spring15_ZJet_HT_200_400_.root");
    else if(i==3)sprintf(tempname,"../results_filelist_Spring15_ZJet_HT_400_600_.root");
    else if(i==4)sprintf(tempname,"../results_filelist_Spring15_ZJet_HT_600_Inf_.root");
    else{cout << " Error!! There are only 4 ZJet ht binned sample " << endl;}
    ZJet_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins


  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"results_filelist_Spring15_ZJet_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="searchH_";
  histname[6]="searchH_b_";

  Hname.clear();
  Hname[0]="yield_tauId";
  Hname[1]="yield_tauId_trk";
  Hname[2]="cutflow_preselection";


  for(int j=0; j< Hname.size(); j++){

    for(int i=0; i<zjnHT ; i++){                                                  // loop over different HT bins

      sprintf(tempname,"%s",(Hname[j]).c_str());
      temphist = (TH1D *) ZJet_inputfilevec.at(i)->Get(tempname)->Clone();
      //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
      temphist->SetFillColor(i+2);
      tempstack->Add(temphist);

    }//end of loop over HTbins 1..7
    sprintf(tempname,"%s",(Hname[j]).c_str());
    tempstack->Write(tempname);

    delete tempstack;
    tempstack = new THStack("stack","Binned Sample Stack");

  }

    for(map<int , string >::iterator itt=ZJettype.begin(); itt!=ZJettype.end();itt++){        // loop over different event types

    cdtoitt = file->mkdir((itt->second).c_str());
    cdtoitt->cd();

    for(map<int , string >::iterator it=cutname.begin(); it!=cutname.end();it++){   // loop over different cutnames

      cdtoit =  cdtoitt->mkdir((it->second).c_str());
      cdtoit->cd();

      for(int j=0; j<histname.size(); j++){                                        // loop over different histograms

        for(int i=0; i<zjnHT ; i++){                                                  // loop over different HT bins

          //cout << "================================" << endl;
          //cout << "HT#: " <<i << ", WJtype: " << itt->second << ", cutname: " << it->second << ", hist#: " << j << endl;
          if(j>=5)sprintf(tempname,"%s/%s/%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str());
          else sprintf(tempname,"%s/%s/%s_%s_%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str(),(it->second).c_str(),(itt->second).c_str());
          temphist = (TH1D *) ZJet_inputfilevec.at(i)->Get(tempname)->Clone();
          //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
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
  printf("ZJet main histograms stacked \n ");



// .....................................................................................................................................................//
// TTbar Section
// .....................................................................................................................................................//

  // Load the files to a vector
  // These are the HT, MHT, .. variables
  for(int i=1; i<=ttbarnHT ; i++){
    if(i==1)sprintf(tempname,"../results_filelist_Spring15_TTbar_.root");
    else{cout << " Error!! There are only 1 TTbaret ht binned sample " << endl;}
    TTbar_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins

  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"results_filelist_Spring15_TTbar_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="searchH_";
  histname[6]="searchH_b_";

  Hname.clear();
  Hname[0]="yield_tauId";
  Hname[1]="yield_tauId_trk";
  Hname[2]="cutflow_preselection";

  for(int j=0; j< Hname.size(); j++){

    for(int i=0; i<ttbarnHT ; i++){                                                  // loop over different HT bins

      sprintf(tempname,"%s",(Hname[j]).c_str());
      temphist = (TH1D *) TTbar_inputfilevec.at(i)->Get(tempname)->Clone();
      //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
      temphist->SetFillColor(i+2);
      tempstack->Add(temphist);

    }//end of loop over HTbins 1..7
    sprintf(tempname,"%s",(Hname[j]).c_str());
    tempstack->Write(tempname);

    delete tempstack;
    tempstack = new THStack("stack","Binned Sample Stack");

  }

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
          if(j>=5)sprintf(tempname,"%s/%s/%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str());
          else sprintf(tempname,"%s/%s/%s_%s_%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str(),(it->second).c_str(),(itt->second).c_str());
          temphist = (TH1D *) TTbar_inputfilevec.at(i)->Get(tempname)->Clone();
          //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
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




// ..............................................................................................................//
// WJet Section
// .............................................................................................................//

  for(int i=1; i<=wjnHT ; i++){
    if(i==1)sprintf(tempname,"../results_filelist_Spring15_WJet_HT_100_200_.root");
    else if(i==2)sprintf(tempname,"../results_filelist_Spring15_WJet_HT_200_400_.root");
    else if(i==3)sprintf(tempname,"../results_filelist_Spring15_WJet_HT_400_600_.root");
    else if(i==4)sprintf(tempname,"../results_filelist_Spring15_WJet_HT_600_800_.root");
    else if(i==5)sprintf(tempname,"../results_filelist_Spring15_WJet_HT_800_1200_.root");
    else if(i==6)sprintf(tempname,"../results_filelist_Spring15_WJet_HT_1200_2500_.root");
    else if(i==7)sprintf(tempname,"../results_filelist_Spring15_WJet_HT_2500_Inf_.root");
    else{cout << " Error!! There are only 4 WJet ht binned sample " << endl;}
    WJet_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins


  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"results_filelist_Spring15_WJet_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="searchH_";
  histname[6]="searchH_b_";

  Hname.clear();
  Hname[0]="yield_tauId";
  Hname[1]="yield_tauId_trk";
  Hname[2]="cutflow_preselection";


  for(int j=0; j< Hname.size(); j++){

    for(int i=0; i<wjnHT ; i++){                                                  // loop over different HT bins

      sprintf(tempname,"%s",(Hname[j]).c_str());
      temphist = (TH1D *) WJet_inputfilevec.at(i)->Get(tempname)->Clone();
      //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
      temphist->SetFillColor(i+2);
      tempstack->Add(temphist);

    }//end of loop over HTbins 1..7
    sprintf(tempname,"%s",(Hname[j]).c_str());
    tempstack->Write(tempname);

    delete tempstack;
    tempstack = new THStack("stack","Binned Sample Stack");

  }

    for(map<int , string >::iterator itt=WJettype.begin(); itt!=WJettype.end();itt++){        // loop over different event types

    cdtoitt = file->mkdir((itt->second).c_str());
    cdtoitt->cd();

    for(map<int , string >::iterator it=cutname.begin(); it!=cutname.end();it++){   // loop over different cutnames

      cdtoit =  cdtoitt->mkdir((it->second).c_str());
      cdtoit->cd();

      for(int j=0; j<histname.size(); j++){                                        // loop over different histograms

        for(int i=0; i<wjnHT ; i++){                                                  // loop over different HT bins

          //cout << "================================" << endl;
          //cout << "HT#: " <<i << ", WJtype: " << itt->second << ", cutname: " << it->second << ", hist#: " << j << endl;
          if(j>=5)sprintf(tempname,"%s/%s/%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str());
          else sprintf(tempname,"%s/%s/%s_%s_%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str(),(it->second).c_str(),(itt->second).c_str());
          temphist = (TH1D *) WJet_inputfilevec.at(i)->Get(tempname)->Clone();
          //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
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
  printf("WJet main histograms stacked \n ");

// ..............................................................................................................................//
// Single Top Section
// ..............................................................................................................................//

  for(int i=1; i<=tnHT ; i++){
    if     (i==1)sprintf(tempname,"../results_filelist_Spring15_ST_t_top_.root");
    else if(i==2)sprintf(tempname,"../results_filelist_Spring15_ST_t_antitop_.root");
    else if(i==3)sprintf(tempname,"../results_filelist_Spring15_ST_tW_top_.root");
    else if(i==4)sprintf(tempname,"../results_filelist_Spring15_ST_tW_antitop_.root");
    //else if(i==5)sprintf(tempname,"../");
    //else if(i==6)sprintf(tempname,"../");
    else{cout << " Error!! There are only 6 T ht binned sample " << endl;}
    T_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins


  // Stack
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"results_filelist_Spring15_T_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="searchH_";
  histname[6]="searchH_b_";

  Hname.clear();
  Hname[0]="yield_tauId";
  Hname[1]="yield_tauId_trk";
  Hname[2]="cutflow_preselection";

  // Loop over Hname
  for(int j=0; j< Hname.size(); j++){

    for(int i=0; i<tnHT ; i++){                                                  // loop over different HT bins

      sprintf(tempname,"%s",(Hname[j]).c_str());
      temphist = (TH1D *) T_inputfilevec.at(i)->Get(tempname)->Clone();
      //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
      temphist->SetFillColor(i+2);
      tempstack->Add(temphist);

    }//end of loop over HTbins 1..7
    sprintf(tempname,"%s",(Hname[j]).c_str());
    tempstack->Write(tempname);

    delete tempstack;
    tempstack = new THStack("stack","Binned Sample Stack");

  }

  // Loop over event types, cutnames, etc
  for(map<int , string >::iterator itt=Ttype.begin(); itt!=Ttype.end();itt++){        // loop over different event types

    cdtoitt = file->mkdir((itt->second).c_str());
    cdtoitt->cd();

    for(map<int , string >::iterator it=cutname.begin(); it!=cutname.end();it++){   // loop over different cutnames

      cdtoit =  cdtoitt->mkdir((it->second).c_str());
      cdtoit->cd();

      for(int j=0; j<histname.size(); j++){                                        // loop over different histograms

        for(int i=0; i<tnHT ; i++){                                                  // loop over different HT bins

          //cout << "================================" << endl;
          //cout << "HT#: " <<i << ", WJtype: " << itt->second << ", cutname: " << it->second << ", hist#: " << j << endl;
          if(j>=5)sprintf(tempname,"%s/%s/%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str());
          else sprintf(tempname,"%s/%s/%s_%s_%s",(itt->second).c_str(),(it->second).c_str(),(histname[j]).c_str(),(it->second).c_str(),(itt->second).c_str());
          temphist = (TH1D *) T_inputfilevec.at(i)->Get(tempname)->Clone();
          //if (luminosity>0&&!doScale) temphist->Scale(scalefactor);
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
  printf("T main histograms stacked \n ");


// ..................................................................................................................................................... //
// Stack main histograms from TTbar and WJet and Single Top and ZJet and QCD
// ..................................................................................................................................................... //

  // There are three contributors 1-TTbar and 2-WJet 3-T
  int NSamples=5;

  // A vector that contains all the samples
  vector<TFile*> sample_inputfilevec;

  THStack * tempstack2 = new THStack("stack","Binned Sample Stack");

  // Load the files to a vector
  // These are the HT, MHT, .. variables
  for(int i=1; i<=NSamples ; i++){
    if(i==1)sprintf(tempname,"results_filelist_Spring15_TTbar_stacked.root");
    else if(i==2)sprintf(tempname,"results_filelist_Spring15_WJet_stacked.root");
    else if(i==3)sprintf(tempname,"results_filelist_Spring15_T_stacked.root");
    else if(i==4)sprintf(tempname,"results_filelist_Spring15_ZJet_stacked.root");
    else if(i==5)sprintf(tempname,"results_filelist_Spring15_QCD_stacked.root");
    else{cout << " Error!! There are only 3 contributors! " << endl;}
    sample_inputfilevec.push_back(TFile::Open(tempname,"R"));
  }//end of loop over HTbins


  // Stack
  delete tempstack;
  tempstack = new THStack("stack","Binned Sample Stack");
  sprintf(tempname,"results_filelist_Spring15_stacked.root");
  file = new TFile(tempname,"RECREATE");
  histname.clear();
  histname[0]="weight";
  histname[1]="HT";
  histname[2]="MHT";
  histname[3]="NJet";
  histname[4]="NBtag";
  histname[5]="searchH_";
  histname[6]="searchH_b_";


  for(int j=0; j< Hname.size(); j++){

    for(int i=0; i<NSamples ; i++){                                                  // loop over different HT bins

      sprintf(tempname,"%s",(Hname[j]).c_str());
      tempstack2 = (THStack *) sample_inputfilevec.at(i)->Get(tempname)->Clone();
      temphist = (TH1D*)tempstack2->GetStack()->Last();

      temphist->SetFillColor(i+2);
      tempstack->Add(temphist);



    }//end of loop over HTbins 1..7
    sprintf(tempname,"%s",(Hname[j]).c_str());
    tempstack->Write(tempname);

    delete tempstack;
    tempstack = new THStack("stack","Binned Sample Stack");

  }

  for(map<int , string >::iterator itt=WJettype.begin(); itt!=WJettype.end();itt++){        // loop over different event types

    cdtoitt = file->mkdir((itt->second).c_str());
    cdtoitt->cd();

    for(map<int , string >::iterator it=cutname.begin(); it!=cutname.end();it++){   // loop over different cutnames

      cdtoit =  cdtoitt->mkdir((it->second).c_str());
      cdtoit->cd();


      for(int j=0; j<histname.size(); j++){                                        // loop over different histograms

        for(int i=0; i<NSamples ; i++){                                                  // loop over different HT bins

          //cout << "================================" << endl;
          //cout << "HT#: " <<i << ", WJettype: " << itt->second << ", cutname: " << it->second << ", hist#: " << j << endl;
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





}
